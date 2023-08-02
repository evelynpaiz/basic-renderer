#include "enginepch.h"
#include "Renderer/Shader/Shader.h"

#include <GL/glew.h>

/**
 * Generate a shader program.
 *
 * @param filePath Path to the source file.
 */
Shader::Shader(const std::filesystem::path& filePath)
    : m_FilePath(filePath)
{
    ShaderProgramSource source = ParseShader(filePath);
    m_ID = CreateShader(source.VertexSource, source.FragmentSource);
}

/**
 * Delete the shader program.
 */
Shader::~Shader()
{
    glDeleteProgram(m_ID);
}

/**
 * Activate the shader.
 */
void Shader::Bind() const
{
    glUseProgram(m_ID);
}

/**
 * Deactivate the shader.
 */
void Shader::Unbind() const
{
    glUseProgram(0);
}

/**
 * Get the location number of a uniform.
 *
 * @param name Name of the uniform.
 *
 * @return Uniform location.
 */
int Shader::GetUniformLocation(const std::string& name)
{
    // Verify that the location of the uniform is not cached
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];
    
    // Retrieve the location of the uniform and cache it too
    int location = glGetUniformLocation(m_ID, name.c_str());
    if (location == -1)
        CORE_WARN("Uniform " + name + " doesn't exist!");
    
    m_UniformLocationCache[name] = location;
    return location;
}

/**
 * Set the uniform with a bool value.
 *
 * @param name Uniform name.
 * @param value Uniform value.
 */
void Shader::SetBool(const std::string& name, bool value)
{
    glUniform1i(GetUniformLocation(name), (int)value);
}

/**
 * Set the uniform with an integer value.
 *
 * @param name Uniform name.
 * @param value Uniform value.
 */
void Shader::SetInt(const std::string& name, int value)
{
    glUniform1i(GetUniformLocation(name), value);
}

/**
 * Set the uniform with a float value.
 *
 * @param name Uniform name.
 * @param value Uniform value.
 */
void Shader::SetFloat(const std::string& name, float value)
{
    glUniform1f(GetUniformLocation(name), value);
}

/**
 * Set the uniform with a vector with 2 values (x, y).
 *
 * @param name Uniform name.
 * @param value Vector input value.
 */
void Shader::SetVec2(const std::string& name, const glm::vec2& value)
{
    glUniform2fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
}

/**
 * Set the uniform with a vector with 3 values (x, y, z).
 *
 * @param name Uniform name.
 * @param value Vector input value.
 */
void Shader::SetVec3(const std::string& name, const glm::vec3& value)
{
    glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
}

/**
 * Set the uniform with a vector with 4 values (x, y, z, w).
 *
 * @param name Uniform name.
 * @param value Vector input value.
 */
void Shader::SetVec4(const std::string& name, const glm::vec4& value)
{
    glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
}

/**
 * Set the uniform with a matrix with 2x2 values.
 *
 * @param name Uniform name.
 * @param value Matrix input value.
 */
void Shader::SetMat2(const std::string& name, const glm::mat2& value)
{
    glUniformMatrix2fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

/**
 * Set the uniform with a matrix with 3x3 values.
 *
 * @param name Uniform name.
 * @param value Matrix input value.
 */
void Shader::SetMat3(const std::string& name, const glm::mat3& value)
{
    glUniformMatrix3fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

/**
 * Set the uniform with a matrix with 4x4 values.
 *
 * @param name Uniform name.
 * @param value Matrix input value.
 */
void Shader::SetMat4(const std::string& name, const glm::mat4& value)
{
    glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

/**
 * Compile the shader from its input file source.
 *
 * @param type Shader type.
 * @param source Shader input source.
 *
 * @return the ID of the shader program.
 */
unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    // Define the shader from the input source and compile
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::string t = (type == GL_VERTEX_SHADER ? "vertex" : "fragment");
        
        CORE_ERROR("Failed to compile " + t + " shader!");
        CORE_ASSERT(result == GL_TRUE, message);
        glDeleteShader(id);
        return 0;
    }
    
    return id;
}

/**
 * Generate a shader program from vertex and fragment inputs.
 *
 * @param vertexShader Source of vertex shader.
 * @param fragmentShader Source of fragment shader.
 *
 * @return ID of the shader program.
 */
unsigned int Shader::CreateShader(const std::string& vertexShader,
                        const std::string& fragmentShader) {
    // Define a shader program
    unsigned int program = glCreateProgram();
    
    // Vertex shader
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    // Fragment shader
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
    // Link shaders
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    
    // De-allocate the shader resources
    glDeleteShader(vs);
    glDeleteShader(fs);
    
    // Return the shader program
    return program;
}

/**
 * Parse shader input file.
 *
 * @param filepath Path to the shader file.
 *
 * @return The vertex and fragment program source.
 */
ShaderProgramSource Shader::ParseShader(const std::filesystem::path& filepath)
{
    // Open the file
    std::ifstream stream(filepath);
    
    // Define the different shader classes available
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    
    // Parse the file
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            // Set mode to vertex
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            // Set mode to fragment
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }
    
    // Return the shader sources
    return ShaderProgramSource(ss[0].str(), ss[1].str());
}