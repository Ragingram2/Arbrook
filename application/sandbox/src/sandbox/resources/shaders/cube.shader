#GLSL
#shader vertex
#version 420 core

layout(location = 0) in vec4 v_position;
//layout(location = 1) in vec3 v_normal;

//out vec3 f_normal;
out vec3 f_pos;

layout(std140, binding = 0) uniform ConstantBuffer
{
	mat4 u_mvp;
};

void main()
{
	gl_Position = u_mvp * (v_position);
	//f_normal = v_normal;
}

#shader fragment
#version 420 core

//in vec3 f_normal;
out vec4 FragColor;

// vec3 lightPos = vec3(0.0,0,-3.0);
// vec3 viewPos = vec3(0.0,0.0,-3.0);
// vec3 lightColor = vec3(1.0,1.0,1.0);
// vec3 objectColor = vec3(1.0,0.0,0.0);

void main()
{
	// //ambient
	// float ambientStrength = 0.2;
	// vec3 ambient = ambientStrength * lightColor;

	// //diffuse
	// vec3 norm = normalize(f_normal);
	// vec3 lightDir = normalize(lightPos-gl_FragCoord.xyz);
	// float diff = max(dot(norm, lightDir),0.0);
	// vec3 diffuse = diff*lightColor;

	// //specular
	// float specularStrength = 0.8;
	// vec3 viewDir = normalize(viewPos-gl_FragCoord.xyz);
	// vec3 reflectDir = reflect(-lightDir, norm);
	// float spec = pow(max(dot(viewDir, reflectDir),0.0),32);
	// vec3 specular = specularStrength*spec*lightColor;

	// vec3 result = (ambient+diffuse+specular)*objectColor;

	//FragColor = vec4(result, 1.0);

	FragColor = vec4(1.0,0.0,0.0,1.0);
}
#END

#HLSL
#shader vertex

cbuffer ConstantBuffer : register(b0)
{
	matrix u_mvp;
};

struct VOut
{
	float4 p_position : SV_POSITION;
};

VOut VShader(float3 position : POSITION)
{
	VOut output;

    output.p_position = mul(float4(position, 1.0f), transpose(u_mvp));

	return output;
}

#shader fragment

float4 PShader(float4 position : SV_POSITION) : SV_TARGET
{
	return float4(1,0,0,1);
}
#END