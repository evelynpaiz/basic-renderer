#pragma once

#include <glm/glm.hpp>

/**
 * Define a default vertex structure that represents the different data that a vertex may contain.
 * 
 * @tparam Components The components of the vertex structure.
 */
template<typename... Components>
struct GeoVertexData {};

/**
 * Specialization of VertexData for 3D vertices with position information.
 */
template<>
struct GeoVertexData<glm::vec4>
{
    glm::vec4 position;         ///< Vertex position.
};

/**
 * Specialization of VertexData for 3D vertices with position and UV coordinate information.
 */
template<>
struct GeoVertexData<glm::vec4, glm::vec2>
{
    glm::vec4 position;         ///< Vertex position.
    glm::vec2 uv;               ///< Texture coordinate.
};

/**
 * Specialization of VertexData for 3D vertices with position and normal vector information.
 */
template<>
struct GeoVertexData<glm::vec4, glm::vec3>
{
    glm::vec4 position;         ///< Vertex position.
    glm::vec3 normal;           ///< Normal vector.
};

/**
 * Specialization of VertexData for 3D vertices with position, UV coordinate, and normal vector information.
 */
template<>
struct GeoVertexData<glm::vec4, glm::vec2, glm::vec3>
{
    glm::vec4 position;         ///< Vertex position.
    glm::vec2 uv;               ///< Texture coordinate.
    glm::vec3 normal;           ///< Normal vector.
};

/**
 * A utility class for defining and creating different geometries in 3D space.
 *
 * The `Geometry` class provides static functions to define and create various geometries, such as planes and cubes,
 * with different vertex data configurations (e.g., position-only, position and texture coordinates, position, texture coordinates,
 * and normals). The class serves as a utility to encapsulate the creation of common geometric shapes for rendering purposes.
 */
class Geometry
{
public:
    // Plane geometry
    // ----------------------------------------
    static void DefinePlaneGeometry(std::vector<GeoVertexData<glm::vec4>>& vertices,
                                    std::vector<unsigned int>& indices);
    static void DefinePlaneGeometry(std::vector<GeoVertexData<glm::vec4, glm::vec2>>& vertices,
                                    std::vector<unsigned int>& indices);
    static void DefinePlaneGeometry(std::vector<GeoVertexData<glm::vec4, glm::vec3>>& vertices,
                                    std::vector<unsigned int>& indices);
    static void DefinePlaneGeometry(std::vector<GeoVertexData<glm::vec4, glm::vec2, glm::vec3>>& vertices,
                                    std::vector<unsigned int>& indices);
    
    // Cube geometry
    // ----------------------------------------
    static void DefineCubeGeometry(std::vector<GeoVertexData<glm::vec4>>& vertices,
                           std::vector<unsigned int>& indices);
    static void DefineCubeGeometry(std::vector<GeoVertexData<glm::vec4, glm::vec2>>& vertices,
                           std::vector<unsigned int>& indices);
    static void DefineCubeGeometry(std::vector<GeoVertexData<glm::vec4, glm::vec3>>& vertices,
                           std::vector<unsigned int>& indices);
    static void DefineCubeGeometry(std::vector<GeoVertexData<glm::vec4, glm::vec2, glm::vec3>>& vertices,
                           std::vector<unsigned int>& indices);
    
private:
    // Geometry indices
    // ----------------------------------------
    static void SetPlaneIndices(std::vector<unsigned int>& indices);
    static void SetBasicCubeIndices(std::vector<unsigned int>& indices);
    static void SetCubeIndices(std::vector<unsigned int>& indices);
};
