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

		float source[256];
		float density[256];

		float Velx[256];
		float Vely[256];

		float Velx0[256];
		float Vely0[256];
};

in vec2 TexCoord;
out vec4 FragColor;

void main()
{
	//int x = int(TexCoord.x * 10)*size;
	//int y = int(TexCoord.y * 10)*size;
	//int idx = x + y; 
	//float val = density[0];
	//FragColor = vec4(val,val,val,1.0); 
	if(TexCoord.x < 0.1 && TexCoord.y < 0.1)
		FragColor = vec4(density[0]);
	else
		FragColor = vec4(TexCoord.x, TexCoord.y,0,1.0);
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