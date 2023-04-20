#GLSL
#shader vertex
#version 420 core

struct vertex
{
	vec3 position;
	vec4 color;
	vec2 texCoord;
};

layout(location = 0) in vertex vtx;

layout(std140, binding = 0) uniform cBuffer
{
	vec3 u_position;
	float u_time;
};

out vec4 aColor;
out vec2 TexCoord;

void main()
{
	vec3 offset = vec3(0, sin(u_time), 0);
	gl_Position = vec4(vtx.position + u_position + offset, 1);
	//aColor = vColor;
	aColor = vtx.color;
	TexCoord = vtx.texCoord;
}

#shader fragment
#version 420 core

in vec4 aColor;
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

	float3 offset = float3(0, sin(u_time), 0);
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