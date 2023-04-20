#GLSL
#shader vertex
#version 450 core


layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;
layout(location = 2) in vec2 vTexCoord;

layout(std140) uniform cBuffer
{
	vec3 u_position;
	float u_time;
};

out vec4 aColor;
out vec2 TexCoord;

void main()
{
	vec3 offset = vec3(0, sin(u_time), 0);
	gl_Position = vec4(vPosition.xyz + u_position + offset, 0);
	aColor = vColor;
	TexCoord = vTexCoord;
}

#shader fragment
#version 330 core

in vec3 aColor;
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
	vec4 tColor = texture(ourTexture, TexCoord);
	FragColor = tColor;
}
#END

#HLSL
#shader vertex
cbuffer myCbuffer : register(b0)
{
	float3 u_position;
	float u_time;
};

struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

VOut VShader(float4 position : POSITION, float4 color : COLOR)
{
	VOut output;

	float3 offset = float3(0, sin(u_time),0);
	output.position = position + float4(u_position + offset, 0);
	output.color = color;

	return output;
}

#shader fragment
float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET
{
	return color;
}
#END