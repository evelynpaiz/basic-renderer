#pragma once

// --------------------------------------------
// Logger
// --------------------------------------------
#include "Core/Log.h"
#include "Core/Assert.h"

// --------------------------------------------
// Application
// --------------------------------------------
#include "Core/Window.h"
#include "Core/Application.h"

// --------------------------------------------
// Inputs
// --------------------------------------------
#include "Input/Input.h"
#include "Input/KeyCodes.h"
#include "Input/MouseCodes.h"

// --------------------------------------------
// Events
// --------------------------------------------
#include "Event/Event.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"
#include "Event/WindowEvent.h"

// --------------------------------------------
// Base Layer(s)
// --------------------------------------------
#include "Layer/Layer.h"
#include "Layer/GuiLayer.h"

#include "Layer/DrawUtils.h"

// --------------------------------------------
// Renderer
// --------------------------------------------
#include "Renderer/Buffer/VertexBuffer.h"
#include "Renderer/Buffer/IndexBuffer.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Buffer/FrameBuffer.h"

#include "Renderer/Shader/Shader.h"
#include "Renderer/Texture/Texture.h"
#include "Renderer/Texture/Texture1D.h"
#include "Renderer/Texture/Texture2D.h"
#include "Renderer/Texture/Texture3D.h"
#include "Renderer/Texture/TextureCube.h"

#include "Renderer/Light/ShadowCamera.h"
#include "Renderer/Light/Light.h"
#include "Renderer/Light/PositionalLight.h"
#include "Renderer/Light/DirectionalLight.h"
#include "Renderer/Light/EnvironmentLight.h"

#include "Renderer/Material/Material.h"
#include "Renderer/Material/LightedMaterial.h"
#include "Renderer/Material/OcclusionMaterial.h"
#include "Renderer/Material/SimpleMaterial.h"
#include "Renderer/Material/PhongMaterial.h"

#include "Renderer/Mesh/Mesh.h"
#include "Renderer/Model/Model.h"
#include "Renderer/Model/AssimpModel.h"

#include "Renderer/Mesh/MeshUtils.h"
#include "Renderer/Model/ModelUtils.h"

#include "Renderer/Camera/PerspectiveCamera.h"
#include "Renderer/Camera/OrthographicCamera.h"

#include "Renderer/Renderer.h"

// --------------------------------------------
// Rendering Context & Scene
// --------------------------------------------
#include "Scene/Scene.h"

#include "Context/Viewport.h"
#include "Context/RenderContext.h"
