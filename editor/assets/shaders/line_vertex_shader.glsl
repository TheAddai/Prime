
#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec4 a_color;

out vec4 v_color;

layout(std140) uniform cameraBlock
{
	mat4 u_viewProjection;
};

void main()
{        
    v_color = a_color;

    gl_Position = u_viewProjection * vec4(a_position, 1.0);
}