// Specify the output color of the fragment shader
layout (location = 0) out vec4 color;

// Uniform buffer blocks
uniform View u_View;            // View information
uniform Light u_Light;          // Light information
uniform Material u_Material;    // Material properties

// Input variables from the vertex shader
in vec3 v_Position;             // Vertex position in world space
in vec3 v_Normal;               // Vertex normal in world space
