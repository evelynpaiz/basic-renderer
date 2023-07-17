#pragma once

/**
 * Represents a model used for rendering geometry.
 *
 * The `Model` class serves as a base class for defining models and provides functionality for loading and rendering
 * meshes that make up the model. It encapsulates the necessary information, such as the file path and a collection of
 * meshes, required to load and render a model.
 *
 * @tparam VertexData The type of vertex data used by the meshes in the model.
 */
template<typename VertexData>
class Model
{
public:
    // Destructor
    // ----------------------------------------
    /// @brief Delete the model.
    virtual ~Model() = default;
    
    // Loading
    // ----------------------------------------
    /// @brief Load the model from the specified file path.
    /// @param filePath The path to the model file.
    virtual void LoadModel(const std::filesystem::path& filePath) {};
    
    // Render
    // ----------------------------------------
    /// @brief Draw the model using the specified transformation matrix.
    /// @param transform The transformation matrix for the model.
    void DrawModel(const glm::mat4& transform = glm::mat4(1.0f))
    {
        for(unsigned int i = 0; i < m_Meshes.size(); i++)
            m_Meshes[i].DrawMesh(transform);
    }
    
    // Setter(s)
    // ----------------------------------------
    /// @brief Sets the material for all the meshes in the model.
    /// @param material The material defining the surface of the meshes.
    void SetMaterial(const std::shared_ptr<Material>& material)
    {
        for(unsigned int i = 0; i < m_Meshes.size(); i++)
            m_Meshes[i].SetMaterial(material);
    }
    
protected:
    // Constructor(s)
    // ----------------------------------------
    /// @brief Define a model.
    Model() = default;
    /// @brief Define a model from a file source.
    /// @param filePath The path to the model file.
    Model(const std::filesystem::path& filePath) { LoadModel(filePath); }
    
    // Model variables
    // ----------------------------------------
protected:
    ///< Path to the file.
    std::filesystem::path m_FilePath;
    
    ///< Set of meshes defining the model.
    std::vector<Mesh<VertexData>> m_Meshes;
};
