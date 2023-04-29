#GLSL
#shader vertex
#version 420 core

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec4 v_color;
layout(location = 2) in vec2 v_texCoord;

layout(std140, binding = 0) uniform ConstantBuffer
{
	vec3 u_position;
	float u_time;
};

out vec4 aColor;
out vec2 TexCoord;

void main()
{
	vec3 offset = vec3(0, sin(u_time), 0);
	gl_Position = vec4((v_position * 1.25) + u_position + offset, 1);
	aColor = v_color;
}

#shader fragment
#version 420 core

in vec4 aColor;
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
	//vec4 tColor = texture(ourTexture, TexCoord);
	FragColor = aColor;
}
#END

#HLSL
#shader vertex
cbuffer ConstantBuffer : register(b0)
{
	float3 u_position;
	float u_time;
};

struct VOut
{
	float4 p_position : SV_POSITION;
	float4 p_color : COLOR;
	float2 p_texcoord : TEXCOORD;
};

VOut VShader(float3 position : POSITION, float4 color : COLOR, float2 texCoord : TEXCOORD)
{
	VOut output;

	float3 offset = float3(0, sin(u_time), 0);
	output.p_position = float4((position * 1.25) + u_position + offset, 1);
	output.p_color = color;
	output.p_texcoord = texCoord;

	return output;
}

#shader fragment
Texture2D m_texture;
SamplerState m_sampler;

float4 PShader(float4 position : SV_POSITION, float4 color : COLOR, float2 texCoord : TEXCOORD) : SV_TARGET
{
	//return m_texture.Sample(m_sampler, texCoord);
	return color;
}
#END
