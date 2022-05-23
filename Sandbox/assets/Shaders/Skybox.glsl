#type vertex
#version 330 core

layout (location = 0) in vec3 a_VertexPosition;

uniform mat4 u_CustomViewMatrix;
uniform mat4 u_Projection;

out vec3 UV;

void main()
{
    UV = a_VertexPosition;
    vec4 pos = u_Projection * u_CustomViewMatrix * vec4(a_VertexPosition, 1.0);
    gl_Position = pos.xyww;
}

////////////////////////////////////////////////
////// Pixel shader ////////////////////////////
////////////////////////////////////////////////

#type pixel
#version 330 core

out vec4 PixelColor;

in vec3 UV;

uniform samplerCube u_Skybox;

void main()
{
    PixelColor = texture(u_Skybox, UV);
}