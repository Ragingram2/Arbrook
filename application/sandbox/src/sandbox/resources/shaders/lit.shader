#GLSL
#shader vertex
#version 420 core

layout(location = 0) in vec4 v_position;
layout(location = 1) in vec3 v_normal;

layout(std140, binding = 0) uniform CameraBuffer
{
	vec3 u_viewPosition;
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

layout(std140, binding = 0) uniform CameraBuffer
{
	vec3 u_viewPosition;
	mat4 u_projection;
	mat4 u_view;
	mat4 u_model;
};

layout(std140, binding = 1) uniform LightBuffer
{
	vec3 u_lightPos;
	vec3 u_lightColor;
};

out vec4 FragColor;

void main()
{
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * u_lightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(u_lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * u_lightColor;

	float specularStrength = 0.5;
	vec3 viewDir = normalize(u_viewPosition - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir),0.0),32);
	vec3 specular = specularStrength * spec * u_lightColor;

	vec3 result = (ambient + diffuse + specular) * vec3(1.0);
	FragColor = vec4(result, 1.0);
	//FragColor = vec4(Normal, 1.0);
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