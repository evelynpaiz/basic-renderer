#include "enginepch.h"
#include "Gui/GuiLayer.h"

#include "Core/Application.h"

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

/**
 * Define a GUI layer.
 */
GuiLayer::GuiLayer()
    : Layer("GUI Layer")
{}

/**
 * Attach (add) the GUI layer to the rendering engine.
 */
void GuiLayer::OnAttach()
{
    // Set the imgui context
    IMGUI_CHECKVERSION();
    m_GuiContext = ImGui::CreateContext();
    
    // Define imgui flags
    ImGuiIO &io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
    
    // Define the current window
    Application &app = Application::Get();
    GLFWwindow *window = static_cast<GLFWwindow *>(app.GetWindow().GetNativeWindow());
    
    // Initialize
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

/**
 * Detach (remove) the GUI layer from the rendering engine.
 */
void GuiLayer::OnDetach()
{}

/**
 * Render the GUI layer.
 * @param deltaTime Times passed since the last update.
 */
void GuiLayer::OnUpdate(float deltaTime)
{
    ImGuiIO &io = ImGui::GetIO();
    Application &app = Application::Get();
    
    io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
    io.DeltaTime = deltaTime;
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    
    //ImGui::ShowDemoWindow();
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

/**
 * Handle an event that possibly occurred inside the GUI layer.
 * @param e Event.
 */
void GuiLayer::OnEvent(Event& event)
{}
