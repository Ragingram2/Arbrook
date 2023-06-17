#GLSL
#shader vertex
#version 420 core


layout(location = 0) in vec4 v_position;
layout(location = 1) in mat4 v_model;


layout(std140, binding = 0) uniform ConstantBuffer
{
	mat4 u_view;
	mat4 u_projection;
	mat4 u_model;
};

void main()
{
	gl_Position = (u_projection * u_view * v_model * v_position);
}

#shader fragment
#version 420 core

out vec4 FragColor;

void main()
{
	FragColor = vec4(1, 0, 0, 1);
}
#END

#HLSL
#shader vertex

cbuffer ConstantBuffer : register(b0)
{
	float4x4 u_view;
	float4x4 u_projection;
	float4x4 u_model;
};

struct VOut
{
	float4 p_position : SV_POSITION;
};

VOut VShader(float3 position : POSITION, column_major float4x4 model : MODEL)
{
	VOut output;

	output.p_position = mul(u_projection * u_view * model, float4(position, 1.0));

	return output;
}

#shader fragment

float4 PShader(float4 position : SV_POSITION) : SV_TARGET
{
	return float4(1,0,0,1);
}
#END