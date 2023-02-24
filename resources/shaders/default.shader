#shader vertex
#version 330 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec2 vTexCoord;

out vec3 aColor;
out vec2 TexCoord;

uniform vec2 u_position;

void main()
{
	gl_Position = vPosition + vec4(u_position, 0, 0);
	aColor = vColor;
	//TexCoord = vTexCoord;
}

#shader fragment
#version 330 core

in vec3 aColor;
in vec2 TexCoord;
out vec4 FragColor;

uniform vec4 u_color;
uniform sampler2D ourTexture;

void main()
{
	FragColor = u_color;
	//FragColor = vec4(aColor, 1.0);
	//FragColor = texture(ourTexture, TexCoord);
}