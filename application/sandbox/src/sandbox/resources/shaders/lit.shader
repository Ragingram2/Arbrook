#GLSL
#shader vertex
#version 420 core

layout (location = 0) in vec4 v_position;
layout (location = 1) in vec3 v_normal;
layout (location = 2) in vec2 v_texcoords;

layout(std140, binding = 0) uniform CameraBuffer
{
	vec3 u_viewPosition;
	mat4 u_projection;
	mat4 u_view;
	mat4 u_model;
};

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

void main()
{
	gl_Position = ((u_projection * u_view) * u_model) * v_position;
	FragPos = vec3(u_model * vec4(v_position));
	//this should be moved to the cpu at some point
	Normal = mat3(transpose(inverse(u_model))) * v_normal;
	TexCoords = v_texcoords;
}

#shader fragment
#version 420 core

struct Light
{
	vec4 direction;
	vec4 position;
	vec4 color;
	float range;
	float intensity;
};

#define NR_POINT_LIGHTS 8

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D Diffuse;
uniform sampler2D Specular;

layout(std140, binding = 0) uniform CameraBuffer
{
	vec3 u_viewPosition;
	mat4 u_projection;
	mat4 u_view;
	mat4 u_model;
};

layout(std140, binding = 1) uniform LightBuffer
{
	Light u_lights[NR_POINT_LIGHTS + 1];
} lightBuffer;

layout(std140, binding = 2) uniform MaterialBuffer
{
	float u_shininess;
} material;

out vec4 FragColor;

float Attenuation(vec3 lightPosition, vec3 fragPos, float attenuationRadius, float lightIntensity)
{
	float sqrlightDistance = pow(length(lightPosition - fragPos),2);
	float attenuation = pow(max(1.0 - (sqrlightDistance / (attenuationRadius * attenuationRadius)), 0.0), 2);
	return attenuation * lightIntensity;
}

vec3 CalcDirLight(Light light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction.xyz);

	//diffuse
	float diff = max(dot(normal, lightDir), 0.0);
	//specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir),0.0), material.u_shininess);

	//combine results
	vec3 ambient = light.color.rgb * vec3(texture(Diffuse, TexCoords));
	vec3 diffuse = light.color.rgb * diff * vec3(texture(Diffuse, TexCoords));
	vec3 specular = light.color.rgb * spec * vec3(texture(Specular, TexCoords));
	
	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position.xyz - fragPos);

	//diffuse
	float diff = max(dot(normal, lightDir), 0.0);
	//specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir),0.0), material.u_shininess);

	//attenuation
	float attenuation = Attenuation(light.position.xyz, fragPos, light.range, light.intensity);
	if(attenuation <= 0)
    	return vec3(0);

	//combine results
	vec3 ambient = light.color.rgb * vec3(texture(Diffuse, TexCoords));
	vec3 diffuse = light.color.rgb * diff * vec3(texture(Diffuse, TexCoords));
	vec3 specular = light.color.rgb * spec * vec3(texture(Specular, TexCoords));

	ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
	
	return (ambient + diffuse + specular);
}

void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(u_viewPosition - FragPos);

	vec3 result = CalcDirLight(lightBuffer.u_lights[0], norm, viewDir);

	for(int i = 1; i < NR_POINT_LIGHTS+1; i++)
		result += CalcPointLight(lightBuffer.u_lights[i], norm, FragPos, viewDir);	

	FragColor = vec4(result, 1.0);
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