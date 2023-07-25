#include "enginepch.h"
#include "Renderer/Mesh/Geometry.h"

/**
 * Define the geometry of a plane with only position information.
 *
 * @param vertices Vector to store the vertex data for the plane (position-only vertices).
 * @param indices Vector to store the indices of the vertices to form triangles.
 */
void Geometry::DefinePlaneGeometry(std::vector<GeoVertexData<glm::vec4>>& vertices,
                                   std::vector<unsigned int>& indices)
{
    vertices = {
        // { position }
        { {-0.5f, -0.5f, 0.0f, 1.0f} },     // bottom left (0)
        { { 0.5f, -0.5f, 0.0f, 1.0f} },     // bottom right (1)
        { { 0.5f,  0.5f, 0.0f, 1.0f} },     // top right (2)
        { {-0.5f,  0.5f, 0.0f, 1.0f} }      // top left (3)
    };
    
    SetPlaneIndices(indices);
}

/**
 * Define the geometry of a plane with position and texture coordinate information.
 * 
 * @param vertices Vector to store the vertex data for the plane (position and texture coordinate vertices).
 * @param indices Vector to store the indices of the vertices to form triangles.
 */
void Geometry::DefinePlaneGeometry(std::vector<GeoVertexData<glm::vec4, glm::vec2>>& vertices,
                                   std::vector<unsigned int>& indices)
{
    vertices = {
        // { position, texture coords }
        { {-0.5f, -0.5f, 0.0f, 1.0f}, {0.0f,  0.0f} },     // bottom left (0)
        { { 0.5f, -0.5f, 0.0f, 1.0f}, {1.0f,  0.0f} },     // bottom right (1)
        { { 0.5f,  0.5f, 0.0f, 1.0f}, {1.0f,  1.0f} },     // top right (2)
        { {-0.5f,  0.5f, 0.0f, 1.0f}, {0.0f,  1.0f} }      // top left (3)
    };
    
    SetPlaneIndices(indices);
}

/**
 * Define the geometry of a plane with position and normal vector information.
 *
 * @param vertices Vector to store the vertex data for the plane (position and normal vector vertices).
 * @param indices Vector to store the indices of the vertices to form triangles.
 */
void Geometry::DefinePlaneGeometry(std::vector<GeoVertexData<glm::vec4, glm::vec3>>& vertices,
                                   std::vector<unsigned int>& indices)
{
    vertices = {
        // { position, normal }
        { {-0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f} },     // bottom left (0)
        { { 0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f} },     // bottom right (1)
        { { 0.5f,  0.5f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f} },     // top right (2)
        { {-0.5f,  0.5f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f} }      // top left (3)
    };
    
    SetPlaneIndices(indices);
}

/**
 * Define the geometry of a plane with position, texture coordinate, and normal vector information.
 *
 * @param vertices Vector to store the vertex data for the plane (position, texture coordinate, and normal vector vertices).
 * @param indices Vector to store the indices of the vertices to form triangles.
 */
void Geometry::DefinePlaneGeometry(std::vector<GeoVertexData<glm::vec4, glm::vec2, glm::vec3>>& vertices,
                                   std::vector<unsigned int>& indices)
{
    vertices = {
        // { position, texture coords, normal }
        { {-0.5f, -0.5f, 0.0f, 1.0f}, {0.0f,  0.0f}, {0.0f, 0.0f, 1.0f} },     // bottom left (0)
        { { 0.5f, -0.5f, 0.0f, 1.0f}, {1.0f,  0.0f}, {0.0f, 0.0f, 1.0f} },     // bottom right (1)
        { { 0.5f,  0.5f, 0.0f, 1.0f}, {1.0f,  1.0f}, {0.0f, 0.0f, 1.0f} },     // top right (2)
        { {-0.5f,  0.5f, 0.0f, 1.0f}, {0.0f,  1.0f}, {0.0f, 0.0f, 1.0f} }      // top left (3)
    };
    
    SetPlaneIndices(indices);
}

/**
 * Define the geometry of a cube with only position information.
 *
 * @param vertices Vector to store the vertex data for the cube (position-only vertices).
 * @param indices Vector to store the indices of the vertices to form triangles.
 */
void Geometry::DefineCubeGeometry(std::vector<GeoVertexData<glm::vec4>>& vertices,
                        std::vector<unsigned int>& indices)
{
    vertices = {
        // Front face
        { {-0.5f, -0.5f,  0.5f, 1.0f} },     // bottom left (0)
        { { 0.5f, -0.5f,  0.5f, 1.0f} },     // bottom right (1)
        { { 0.5f,  0.5f,  0.5f, 1.0f} },     // top right (2)
        { {-0.5f,  0.5f,  0.5f, 1.0f} },     // top left (3)
        // Back face
        { {-0.5f, -0.5f, -0.5f, 1.0f} },     // bottom left (4)
        { { 0.5f, -0.5f, -0.5f, 1.0f} },     // bottom right (5)
        { { 0.5f,  0.5f, -0.5f, 1.0f} },     // top right (6)
        { {-0.5f,  0.5f, -0.5f, 1.0f} },     // top left (7)
    };
    
    SetBasicCubeIndices(indices);
}

/**
 * Define the geometry of a cube with position and texture coordinate information.
 *
 * @param vertices Vector to store the vertex data for the cube (position and texture coordinate vertices).
 * @param indices Vector to store the indices of the vertices to form triangles.
 */
void Geometry::DefineCubeGeometry(std::vector<GeoVertexData<glm::vec4, glm::vec2>>& vertices,
                        std::vector<unsigned int>& indices)
{
    vertices = {
        // Front face
        { {-0.5f, -0.5f,  0.5f, 1.0f}, {0.0f, 0.0f} },     // bottom left (0)
        { { 0.5f, -0.5f,  0.5f, 1.0f}, {1.0f, 0.0f} },     // bottom right (1)
        { { 0.5f,  0.5f,  0.5f, 1.0f}, {1.0f, 1.0f} },     // top right (2)
        { {-0.5f,  0.5f,  0.5f, 1.0f}, {0.0f, 1.0f} },     // top left (3)
        // Back face
        { {-0.5f, -0.5f, -0.5f, 1.0f}, {0.0f, 0.0f} },     // bottom left (4)
        { { 0.5f, -0.5f, -0.5f, 1.0f}, {1.0f, 0.0f} },     // bottom right (5)
        { { 0.5f,  0.5f, -0.5f, 1.0f}, {1.0f, 1.0f} },     // top right (6)
        { {-0.5f,  0.5f, -0.5f, 1.0f}, {0.0f, 1.0f} },     // top left (7)
    };
    
    SetBasicCubeIndices(indices);
}

/**
 * Define the geometry of a cube with position and normal vector information.
 *
 * @param vertices Vector to store the vertex data for the cube (position and normal vector vertices).
 * @param indices Vector to store the indices of the vertices to form triangles.
 */
void Geometry::DefineCubeGeometry(std::vector<GeoVertexData<glm::vec4, glm::vec3>>& vertices,
                        std::vector<unsigned int>& indices)
{
    // Define the vertices with positions and normals
    vertices = {
        // Front face
        { {-0.5f, -0.5f,  0.5f, 1.0f}, {0.0f, 0.0f, 1.0f} },     // bottom left (0)
        { { 0.5f, -0.5f,  0.5f, 1.0f}, {0.0f, 0.0f, 1.0f} },     // bottom right (1)
        { { 0.5f,  0.5f,  0.5f, 1.0f}, {0.0f, 0.0f, 1.0f} },     // top right (2)
        { {-0.5f,  0.5f,  0.5f, 1.0f}, {0.0f, 0.0f, 1.0f} },     // top left (3)
        // Back face
        { {-0.5f, -0.5f, -0.5f, 1.0f}, {0.0f, 0.0f, -1.0f} },     // bottom left (4)
        { { 0.5f, -0.5f, -0.5f, 1.0f}, {0.0f, 0.0f, -1.0f} },     // bottom right (5)
        { { 0.5f,  0.5f, -0.5f, 1.0f}, {0.0f, 0.0f, -1.0f} },     // top right (6)
        { {-0.5f,  0.5f, -0.5f, 1.0f}, {0.0f, 0.0f, -1.0f} },     // top left (7)
        // Right face
        { { 0.5f, -0.5f,  0.5f, 1.0f}, {1.0f, 0.0f, 0.0f} },     // bottom left (8)
        { { 0.5f, -0.5f, -0.5f, 1.0f}, {1.0f, 0.0f, 0.0f} },     // bottom right (9)
        { { 0.5f,  0.5f, -0.5f, 1.0f}, {1.0f, 0.0f, 0.0f} },     // top right (10)
        { { 0.5f,  0.5f,  0.5f, 1.0f}, {1.0f, 0.0f, 0.0f} },     // top left (11)
        // Left face
        { {-0.5f, -0.5f, -0.5f, 1.0f}, {-1.0f, 0.0f, 0.0f} },     // bottom left (12)
        { {-0.5f, -0.5f,  0.5f, 1.0f}, {-1.0f, 0.0f, 0.0f} },     // bottom right (13)
        { {-0.5f,  0.5f,  0.5f, 1.0f}, {-1.0f, 0.0f, 0.0f} },     // top right (14)
        { {-0.5f,  0.5f, -0.5f, 1.0f}, {-1.0f, 0.0f, 0.0f} },     // top left (15)
        // Top face
        { {-0.5f,  0.5f,  0.5f, 1.0f}, {0.0f, 1.0f, 0.0f} },     // bottom left (16)
        { { 0.5f,  0.5f,  0.5f, 1.0f}, {0.0f, 1.0f, 0.0f} },     // bottom right (17)
        { { 0.5f,  0.5f, -0.5f, 1.0f}, {0.0f, 1.0f, 0.0f} },     // top right (18)
        { {-0.5f,  0.5f, -0.5f, 1.0f}, {0.0f, 1.0f, 0.0f} },     // top left (19)
        // Bottom face
        { {-0.5f, -0.5f, -0.5f, 1.0f}, {0.0f, -1.0f, 0.0f} },     // bottom left (20)
        { { 0.5f, -0.5f, -0.5f, 1.0f}, {0.0f, -1.0f, 0.0f} },     // bottom right (21)
        { { 0.5f, -0.5f,  0.5f, 1.0f}, {0.0f, -1.0f, 0.0f} },     // top right (22)
        { {-0.5f, -0.5f,  0.5f, 1.0f}, {0.0f, -1.0f, 0.0f} }      // top left (23)
    };
    
    SetCubeIndices(indices);
}

/**
 * Define the geometry of a cube with position, texture coordinate, and normal vector information.
 *
 * @param vertices Vector to store the vertex data for the cube (position, texture coordinate, and normal vector vertices).
 * @param indices Vector to store the indices of the vertices to form triangles.
 */
void Geometry::DefineCubeGeometry(std::vector<GeoVertexData<glm::vec4, glm::vec2, glm::vec3>>& vertices,
                        std::vector<unsigned int>& indices)
{
    vertices = {
        // Front face
        { {-0.5f, -0.5f,  0.5f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f} },     // bottom left (0)
        { { 0.5f, -0.5f,  0.5f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f} },     // bottom right (1)
        { { 0.5f,  0.5f,  0.5f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f} },     // top right (2)
        { {-0.5f,  0.5f,  0.5f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 1.0f} },     // top left (3)
        // Back face
        { {-0.5f, -0.5f, -0.5f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f} },     // bottom left (4)
        { { 0.5f, -0.5f, -0.5f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, -1.0f} },     // bottom right (5)
        { { 0.5f,  0.5f, -0.5f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, -1.0f} },     // top right (6)
        { {-0.5f,  0.5f, -0.5f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, -1.0f} },     // top left (7)
    };
    
    SetCubeIndices(indices);
}

/**
 * @brief Set the indices for a plane geometry, which consists of two triangles forming a rectangle.
 * @param indices A reference to a vector to store the indices.
 */
void Geometry::SetPlaneIndices(std::vector<unsigned int>& indices)
{
    indices = {
        0, 1, 2,    // first triangle
        2, 3, 0,    // second triangle
    };
}

/**
 * @brief Set the indices for a basic cube geometry, consisting of 12 triangles forming 6 faces.
 * @param indices A reference to a vector to store the indices.
 */
void Geometry::SetBasicCubeIndices(std::vector<unsigned int>& indices)
{
    indices = {
        // Front face
        0, 1, 2, // first triangle
        2, 3, 0, // second triangle
        // Back face
        5, 4, 7, // first triangle
        7, 6, 5, // second triangle
        // Right face
        1, 5, 6, // first triangle
        6, 2, 1, // second triangle
        // Left face
        4, 0, 3, // first triangle
        3, 7, 4, // second triangle
        // Top face
        3, 2, 6, // first triangle
        6, 7, 3, // second triangle
        // Bottom face
        4, 5, 1, // first triangle
        1, 0, 4, // second triangle
    };
}

/**
 * @brief Set the indices for a cube geometry, consisting of 12 triangles forming 6 faces.
 * @param indices A reference to a vector to store the indices.
 */
void Geometry::SetCubeIndices(std::vector<unsigned int>& indices)
{
    indices = {
        // Front face
        0, 1, 2, // first triangle
        2, 3, 0, // second triangle
        // Back face
        5, 4, 7, // first triangle
        7, 6, 5, // second triangle
        // Right face
        8, 9, 10, // first triangle
        10, 11, 8, // second triangle
        // Left face
        12, 13, 14, // first triangle
        14, 15, 12, // second triangle
        // Top face
        16, 17, 18, // first triangle
        18, 19, 16, // second triangle
        // Bottom face
        20, 21, 22, // first triangle
        22, 23, 20  // second triangle
    };
}
