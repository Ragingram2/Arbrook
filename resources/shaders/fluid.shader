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

#define SIZE 32.0

layout(std140, binding = 0) uniform ConstantBuffer
{
		vec4 source[256];
};

in vec2 TexCoord;
out vec4 FragColor;

void main()
{
	int x = int((TexCoord.x) * SIZE);
	int y = int((TexCoord.y) * SIZE);

	int idx = int(x + (y * SIZE));
	float val = source[idx / 4][idx % 4];
	FragColor = vec4(vec3(val/SIZE), 1.0);
	//FragColor = vec4(vec3(idx)/(SIZE*SIZE),1.0);
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