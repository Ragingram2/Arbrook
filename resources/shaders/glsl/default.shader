#shader vertex
#version 330 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec2 vTexCoord;

out vec3 aColor;
out vec2 TexCoord;

uniform vec2 u_position;
uniform float u_time;

void main()
{
	vec2 offset = vec2(0, sin(u_time));
	gl_Position = vPosition + vec4(u_position + offset, 0, 0);
	aColor = vColor;
	TexCoord = vTexCoord;
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
	vec4 tColor = texture(ourTexture, TexCoord);
	//float a = 0.0f;
	//vec3 oColor = tColor.xyz + u_color.xyz;
	//float len = dot(oColor , oColor);
	FragColor = tColor;
}