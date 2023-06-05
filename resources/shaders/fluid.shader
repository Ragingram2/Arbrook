#GLSL
#shader vertex
#version 420 core

void main()
{

}

#shader fragment
#version 420 core

void main()
{

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