#include <metal_stdlib>
using namespace metal;

struct VertexIn 
{
    float4 position [[ attribute(0) ]];
};

struct VertexOut
{
    float4 position [[position]];
    float3 color;
};

struct Transform {
    float4x4 Model;
    float4x4 View;
    float4x4 Projection;
};

vertex VertexOut vertex_main(const VertexIn vertex_in [[ stage_in ]],
                             constant Transform &u_Transform [[buffer(11)]],
                             constant float3 &u_Color [[buffer(12)]])
{
    float4 position = u_Transform.Projection * u_Transform.View * u_Transform.Model * vertex_in.position;
    
    VertexOut vertex_out {
      .position = position,
      .color = u_Color
    };
    return vertex_out;
}

fragment float4 fragment_main(VertexOut vertex_in [[ stage_in ]],
                              constant float3 &u_Color [[buffer(12)]])
{
    return float4(u_Color * vertex_in.color, 1);
}
