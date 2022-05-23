#type vertex
#version 330 core

layout (location = 0) in vec3 a_VertexPosition;
layout (location = 1) in vec2 a_UV;
layout (location = 2) in vec3 a_Normal;

layout (std140) uniform SceneData
{
    mat4 u_ViewProjection;
    vec3 u_LightPosition;
    vec3 u_ViewPosition;
};

uniform mat4 u_Transform;

out vec2 v_UV;

void main()
{
    v_UV = a_UV;
    gl_Position = u_ViewProjection * u_Transform * vec4(a_VertexPosition, 1.0);
}

////////////////////////////////////////////////
////// Pixel shader ////////////////////////////
////////////////////////////////////////////////

#type pixel
#version 330 core

out vec4 PixelColor;

in vec2 v_UV;

uniform sampler2D u_Texture;

void main()
{
    PixelColor = texture(u_Texture, v_UV);
}