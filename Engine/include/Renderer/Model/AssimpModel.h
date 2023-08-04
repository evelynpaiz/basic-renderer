#pragma once

#include "Renderer/Mesh/Mesh.h"
#include "Renderer/Model/Model.h"

#include <glm/glm.hpp>

struct aiNode;
struct aiScene;
struct aiMesh;

/**
 * Represents the different data that a vertex from an assimp model contains.
 */
struct AssimpVertexData
{
    glm::vec4 position;         ///< Vertex position.
    glm::vec2 uv;               ///< Texture coordinate.
    glm::vec3 normal;           ///< Normal vector.
};

/**
 * Represents a model loaded using the ASSIMP library.
 *
 * The `AssimpModel` class extends the base `Model` class and provides functionality for loading
 *  and processing models. It inherits the ability to load and render meshes from the base class and
 * adds specific processing using ASSIMP, such as parsing nodes and meshes from an ASSIMP scene.
 */
class AssimpModel : public LoadedModel<AssimpVertexData>
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    /// @brief Generate a model.
    AssimpModel() : LoadedModel<AssimpVertexData>() {}
    AssimpModel(const std::filesystem::path& filePath);
    
    /// @brief Delete the model.
    virtual ~AssimpModel() override = default;
    
    // Loading
    // ----------------------------------------
    virtual void LoadModel(const std::filesystem::path& filePath) override;
    
private:
    // Mesh processing
    // ----------------------------------------
    void ProcessNode(aiNode *node, const aiScene *scene);
    Mesh<AssimpVertexData> ProcessMesh(aiMesh *mesh);
};
