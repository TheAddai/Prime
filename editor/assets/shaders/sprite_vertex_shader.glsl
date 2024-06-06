
#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec4 a_color;
layout (location = 2) in vec2 a_textureCoords;
layout (location = 3) in float a_textureIndex;

out vec4 v_color;
out vec2 v_textureCoords;
out float v_textureIndex;

layout(std140) uniform cameraBlock
{
	mat4 u_viewProjection;
};

void main()
{        
    v_color = a_color;
    v_textureCoords = a_textureCoords;
    v_textureIndex = a_textureIndex;

    gl_Position = u_viewProjection * vec4(a_position, 1.0);
}