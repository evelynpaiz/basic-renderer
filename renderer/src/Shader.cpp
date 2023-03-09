#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>

// --------------------------------------------
// Shader program source
// --------------------------------------------

/**
 * Define the shader program source.
 */
ShaderProgramSource::ShaderProgramSource(const std::string& vs, const std::string& fs)
    : vertexSource(vs), fragmentSource(fs)
{}

// --------------------------------------------
// Shader
// --------------------------------------------

/**
 * Generate a shader program.
 */
Shader::Shader(const std::filesystem::path& filepath)
    : m_FilePath(filepath), m_ID(0)
{
    ShaderProgramSource source = ParseShader(filepath);
    m_ID = CreateShader(source.vertexSource, source.fragmentSource);
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
 * @returns Uniform location.
 */
int Shader::GetUniformLocation(const std::string& name)
{
    // Verify that the location of the uniform is not cached
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];
    
    // Retrieve the location of the uniform and cache it too
    int location = glGetUniformLocation(m_ID, name.c_str());
    if (location == -1)
        std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;
    
    m_UniformLocationCache[name] = location;
    return location;
}

/**
 * Set the value of a uniform (type vector 4).
 *
 * @param name Uniform name.
 * @param x Uniform value x.
 * @param y Uniform value y.
 * @param z Uniform value z.
 * @param w Uniform value w.
 */
void Shader::SetVec4(const std::string& name, float x, float y, float z, float w)
{
    glUniform4f(GetUniformLocation(name), x, y, z, w);
}

/**
 * Compile the shader from its input file source.
 *
 * @param type Shader type.
 * @param source Shader input source.
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
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!" << std::endl;
        std::cout << message << std::endl;
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
 * @returns Id of shader program.
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
