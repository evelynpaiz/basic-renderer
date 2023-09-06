/**
 * Calculate the view space position of a point in a depth map.
 *
 * This function takes a depth map, 2D coordinates, and a transformation matrix
 * to calculate the view space position of a point in the depth map.
 *
 * @param depthMap The depth map texture.
 * @param coords The 2D coordinates of the point in the depth map.
 * @param transform The transformation matrix to convert coordinates to view space.
 * @return The view space position of the point.
 */
vec3 calculateViewPosition(sampler2D depthMap, vec2 coords, mat4 transform) {
    // Get the depth value
    float depth = texture(depthMap, coords).r;
    // Convert to normalized position coordinates
    vec4 ndc = vec4(vec3(coords, depth) * 2.0f - 1.0f, 1.0f);
    // Transform to view space
    vec4 position = transform * ndc;
    // Perform perspective divide
    return position.xyz / position.w;
}
