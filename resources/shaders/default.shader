#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

uniform vec3 u_position;

void main()
{
	gl_Position = position + vec4(u_position, 0);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_color;

void main()
{
	color = u_color;
}