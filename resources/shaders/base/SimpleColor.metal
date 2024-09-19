#include <metal_stdlib>
using namespace metal;

// Include buffer indices enumeration
#import "Resources/shaders/shared/enum/buffer/Buffer.metal"

// Include transformation matrices
#import "Resources/shaders/shared/structure/matrix/SimpleMatrix.metal"

// Include vertex shader
#import "Resources/shaders/shared/chunk/vertex/Pos.vs.metal"

// Include material properties
#import "Resources/shaders/shared/structure/material/ColorMaterial.metal"

fragment float4 fragment_main(constant Material &u_Material [[ buffer(BufferIndex::Materials) ]])
{
    return u_Material.Color;
}
