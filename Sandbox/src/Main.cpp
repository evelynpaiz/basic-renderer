#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Core/Log.h"
#include "Core/Assert.h"
#include "Core/Window.h"

#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"

/**
 * Main function.
 */
int main()
{
    // Initialize the logging manager
    Log::Init();
    
    // Define a window for the renderer
    auto window = std::make_unique<Window>("Basic Renderer", 800, 600);
    
    // Define the layout of the data to be defined:
    // position : (x, y)
    // texture coords : (u, v)
    BufferLayout layout = {
        { "a_Position", DataType::Vec2 },
        { "a_TextureCoord", DataType::Vec2 }
    };
    
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
    auto vao = std::make_shared<VertexArray>();
    // Copy the vertex data in the vertex buffer
    auto vbo = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
    vbo->SetLayout(layout);
    // Copy the index data in the index buffer
    auto ibo = std::make_shared<IndexBuffer>(indices, sizeof(indices) / sizeof(unsigned int));
    // Add the buffers information to the vertex array
    vao->AddVertexBuffer(vbo);
    vao->SetIndexBuffer(ibo);
    
    // Build and compile the shader program to be used
    auto shader = std::make_shared<Shader>("resource/shader/basic.glsl");
    shader->Bind();
    
    // Define the texture(s)
    auto texture = std::make_shared<Texture>("resource/texture/container.jpg");
    
    // Define the shader uniforms
    shader->SetVec4("u_Color", glm::vec4(0.2f, 0.3f, 0.8f, 1.0f));
    
    texture->Bind(0);
    shader->SetInt("u_Texture", 0);
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    
    //glm::mat4 proj = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, -1.0f, 100.0f);
    glm::mat4 proj = glm::perspective(glm::radians(45.0f),
        (float)window->GetWidth()/(float)window->GetHeight(), 0.1f, 100.0f);
    
    shader->SetMat4("u_Transform", proj * view * model);

    // Unbind the resources
    vao->Unbind();
    vbo->Unbind();
    ibo->Unbind();
    shader->Unbind();
    
    // Start the rendering engine
    Renderer renderer;
    
    // Loop until the user closes the window
    while (!glfwWindowShouldClose((GLFWwindow*)window->GetNativeWindow()))
    {
        // Render
        renderer.Clear(glm::vec4(0.93f, 0.93f, 0.93f, 1.0f));
        renderer.Draw(vao, shader);
        
        // Update the window
        window->OnUpdate();
    }
}
