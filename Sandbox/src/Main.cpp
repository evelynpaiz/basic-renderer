#include <iostream>

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

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
        -0.5f, -0.5f,  0.0f,  0.0f,     // bottom left (0)
         0.5f, -0.5f,  1.0f,  0.0f,     // bottom right (1)
         0.5f,  0.5f,  1.0f,  1.0f,     // top right (2)
        -0.5f,  0.5f,  0.0f,  1.0f      // top left (3)
    };
    
    unsigned int indices[] = {
        0, 1, 2,        // first triangle
        2, 3, 0         // second triangle
    };
    
    // Generate a vertex array
    VertexArray vao;
    // Copy the vertex data in the vertex buffer
    VertexBuffer vbo(vertices, sizeof(vertices));
    // Copy the index data in the index buffer
    IndexBuffer ibo(indices, sizeof(indices) / sizeof(unsigned int));
    // Set the layout of the vertex buffer
    BufferLayout layout = {
        { "a_Position", DataType::Float2 },
        { "a_TextureCoord", DataType::Float2 }
    };
    vbo.SetLayout(layout);
    // Add the buffers information to the vertex array
    vao.AddVertexBuffer(vbo);
    
    // Build and compile the shader program to be used
    Shader shader("resource/shader/basic.glsl");
    shader.Bind();
    
    // Define the texture
    Texture texture("resource/texture/container.jpg");
    texture.Bind();
    
    // Define the shader uniforms
    shader.SetFloat4("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
    shader.SetInt("u_Texture", 0);
    
    vao.Unbind();
    vbo.Unbind();
    ibo.Unbind();
    shader.Unbind();
    
    // Start the rendering engine
    Renderer renderer;
    
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Render
        renderer.Clear();
        renderer.Draw(vao, ibo, shader);
        
        // Swap front and back buffers
        glfwSwapBuffers(window);
        
        // Poll for and process events
        glfwPollEvents();
    }
    
    // Terminate (GLFW)
    glfwTerminate();
}
