#GLSL
#shader vertex
#version 420 core

layout(location = 0) in vec4 v_position;
layout(location = 2) in vec3 v_normal;

layout(std140, binding = 0) uniform ConstantBuffer
{
	mat4 u_projection;
	mat4 u_view;
	mat4 u_model;
};

out vec3 Normal;
out vec3 FragPos;

void main()
{
	gl_Position = ((u_projection * u_view) * u_model) * v_position;
	FragPos = vec3(u_model * vec4(v_position));
	//this should be moved to the cpu at some point
	Normal = mat3(transpose(inverse(u_model))) * v_normal;
}

#shader fragment
#version 420 core

in vec3 Normal;
in vec3 FragPos;

// layout(std140, binding = 1) uniform LightBuffer
// {
// 	vec3 u_lightPos;
// };

out vec4 FragColor;

vec3 lightColor = vec3(1.0,0.5,.31);
vec3 objectColor = vec3(1.0);
vec3 u_lightPos = vec3(-1.2,100.0,200.2);

void main()
{
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(u_lightPos - FragPos);
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = diff * lightColor;

	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;
	vec3 result = (ambient + diffuse) * objectColor;
	FragColor = vec4(result,1.0);
}
#END

#HLSL
#shader vertex

cbuffer ConstantBuffer : register(b0)
{
	matrix u_projection;
	matrix u_view;
	matrix u_model;
};

struct VOut
{
	float4 p_position : SV_POSITION;
};

VOut VShader(float4 position : POSITION)
{
	VOut output;

    output.p_position = mul(mul(mul(u_projection,u_view),u_model),position);

	return output;
}

#shader fragment

float4 PShader(float4 position : SV_POSITION) : SV_TARGET
{
	return float4(1,0,0,1);
}
#END