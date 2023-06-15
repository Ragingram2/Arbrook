#GLSL
#shader vertex
#version 420 core

layout(location = 0) in vec3 v_position;

layout(std140, binding = 0) uniform ConstantBuffer
{
	mat4 u_view;
	mat4 u_projection;
	mat4 u_model;
};

void main()
{
	gl_Position = u_projection * u_view * u_model * vec4(v_position, 1.0f);
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

VOut VShader(float3 position : POSITION)
{
	VOut output;

	output.p_position = u_projection * u_view * u_model * float4(position, 1.0f);

	return output;
}

#shader fragment

float4 PShader(float4 position : SV_POSITION) : SV_TARGET
{
	return float4(1,0,0,1);
}
#END