#shader vertex
#version 330 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec3 vColor;

out vec3 aColor;
uniform vec2 u_position;

void main()
{
	aColor = vColor;
	gl_Position = vPosition + vec4(u_position, 0, 0);
}

#shader fragment
#version 330 core

in vec3 aColor;
out vec4 FragColor;

uniform vec4 u_color;

void main()
{
	FragColor = vec4(aColor, 1.0);
}