
#version 330 core

layout (location = 0) in vec3 a_position;

layout(std140) uniform cameraBlock
{
	mat4 u_viewProjection;
};

void main()
{        
    gl_Position = u_viewProjection * vec4(a_position, 1.0);
}