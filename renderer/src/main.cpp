#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/**
 * Representation of a shader program (vertex & fragment sources).
 */
struct ShaderProgramSource
{
    std::string vertexSource;
    std::string fragmentSource;
    
    /// Constructor.
    ShaderProgramSource(const std::string& vs, const std::string& fs)
        : vertexSource(vs), fragmentSource(fs)
    {}
};

/**
 * Compile a shader input source.
 *
 * @param type Shader type.
 * @param source Shader input source.
 *
 * @returns Id of shader compiled shader source.
 */
static unsigned int CompileShader(unsigned int type, const std::string& source)
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
static unsigned int CreateShader(const std::string& vertexShader,
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
static ShaderProgramSource ParseShader(const std::string& filepath)
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

/**
 * Main function.
 */
int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }
    
    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    
    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window;
    window = glfwCreateWindow(800, 600, "Basic Renderer", nullptr, nullptr);
    
    if (!window)
    {
        std::cout << "Failed to create a GLFW window!" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    // Make the window's context current
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW!" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    // Display the version of OpenGL
    std::cout << glGetString(GL_VERSION) << std::endl;
    
    // Define the data to be drawn (vertices and indices)
    float vertices[] = {
        -0.5f, -0.5f,   // bottom left (0)
         0.5f, -0.5f,   // bottom right (1)
         0.5f,  0.5f,   // top right (2)
        -0.5f,  0.5f    // top left (3)
    };
    
    unsigned int indices[] = {
        0, 1, 2,        // first triangle
        2, 3, 0         // second triangle
    };
    
    // Generate data handlers (VBO, VAO, and EBO)
    unsigned int VBO, IBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);
    
    // Bind the vertex array object
    glBindVertexArray(VAO);
    // Copy the vertex data in the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Copy the index data in the index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // Set the vertex attribute pointers
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    // Build and compile the shader program to be used
    ShaderProgramSource source = ParseShader("resource/shader/basic.glsl");
    unsigned int shader = CreateShader(source.vertexSource, source.fragmentSource);
    glUseProgram(shader);
    
    // Define the shader uniforms
    int location = glGetUniformLocation(shader, "u_Color");
    glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f);
    
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Render
        glClearColor(0.93f, 0.93f, 0.93f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        
        // Swap front and back buffers
        glfwSwapBuffers(window);
        
        // Poll for and process events
        glfwPollEvents();
    }
    
    // De-allocate all resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
    glDeleteProgram(shader);
    
    // Terminate (GLFW)
    glfwTerminate();
}
