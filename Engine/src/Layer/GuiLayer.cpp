#include "enginepch.h"
#include "Layer/GuiLayer.h"

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
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // enable keyboard controls
    
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
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

/**
 * Render the GUI layer.
 *
 * @param deltaTime Times passed since the last update.
 */
void GuiLayer::OnUpdate(float deltaTime)
{
    Begin();
    
    ImGui::ShowDemoWindow();
    
    End();
}

/**
 * Handle an event that possibly occurred inside the GUI layer.
 * 
 * @param e Event.
 */
void GuiLayer::OnEvent(Event& e)
{
    // Do not handle the event if there is no blocking of the dispatchment
    // to other layers
    if (!m_BlockEvents)
        return;
    
    // Handle the event
    ImGuiIO& io = ImGui::GetIO();
    e.Handled |= e.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
    e.Handled |= e.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
}

/**
 * Begin a new rendering frame for the GUI.
 */
void GuiLayer::Begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

/**
 * Render the current defined data of the GUI in the current frame.
 */
void GuiLayer::End()
{
    // Define the application information
    Application &app = Application::Get();
    
    ImGuiIO &io = ImGui::GetIO();
    io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
    
    // Render
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
