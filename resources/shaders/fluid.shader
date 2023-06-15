#GLSL
#shader vertex
#version 420 core

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec2 v_texCoord;

out vec2 TexCoord;

void main()
{
	gl_Position = vec4(v_position, 1);
	TexCoord = v_texCoord;
}

#shader fragment
#version 420 core

layout(std140, binding = 0) uniform ConstantBuffer
{
		int size;
		float deltaTime;
		float diffusion;
		float viscosity;

		float source[64];
		float density[64];

		float Velx[64];
		float Vely[64];

		float Velx0[64];
		float Vely0[64];
};

in vec2 TexCoord;
out vec4 FragColor;

void main()
{
	int idx = int((TexCoord.x * 8.0) + (TexCoord.y * 8.0)); 
	FragColor = vec4(density[idx],density[idx]/.5,density[idx],1.0); 
}
#END

#HLSL
#shader vertex

struct VOut()
{

};

VOut VShader()
{
	VOut output;
	return output;
}

#shader fragment
Texture2D m_texture;
SamplerState m_sampler;

float4 PShader(float4 position : SV_POSITION) : SV_TARGET
{
	return float4(0.f);
}
#END