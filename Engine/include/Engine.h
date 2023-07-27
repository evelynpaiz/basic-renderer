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

// --------------------------------------------
// Renderer
// --------------------------------------------
#include "Renderer/Buffer/VertexBuffer.h"
#include "Renderer/Buffer/IndexBuffer.h"
#include "Renderer/Buffer/VertexArray.h"

#include "Renderer/Shader/Shader.h"
#include "Renderer/Texture/Texture.h"

#include "Renderer/Light/Light.h"
#include "Renderer/Light/PointLight.h"

#include "Renderer/Material/Material.h"
#include "Renderer/Material/SimpleMaterial.h"
#include "Renderer/Material/PhongMaterial.h"

#include "Renderer/Mesh/Geometry.h"
#include "Renderer/Mesh/Mesh.h"
#include "Renderer/Model/Model.h"
#include "Renderer/Model/AssimpModel.h"

#include "Renderer/Camera/PerspectiveCamera.h"

#include "Renderer/Renderer.h"
