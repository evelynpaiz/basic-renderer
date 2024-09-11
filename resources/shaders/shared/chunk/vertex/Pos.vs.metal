/**
 * Represents the layout of incoming vertex data.
 */
struct VertexIn
{
    float4 position [[ attribute(0) ]];     ///< Vertex position in model space.
};

// Entry point of the vertex shader
vertex float4 vertex_main(const VertexIn vertex_in [[ stage_in ]],
                          constant Transform &u_Transform [[buffer(BufferIndex::Transformations)]])
{
    // Calculate the final position of the vertex in clip space
    // by transforming the vertex position from object space to clip space
    float4 position = u_Transform.Projection * u_Transform.View * u_Transform.Model * vertex_in.position;
    return position;
}