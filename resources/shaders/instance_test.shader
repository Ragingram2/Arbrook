#GLSL
#shader vertex
#version 420 core

layout(location = 0) in vec3 v_position;

void main()
{
	gl_Position = vec4(v_position, 1.0);
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

struct VIn
{
	float3 position : POSITION;
};

struct VOut
{
	float4 p_position : SV_POSITION;
};

VOut VShader(VIn vin, uint instanceID : SV_InstanceID)
{
	VOut output;

	output.p_position = float4(vin.position + float3((float)(instanceID)/10.0, 0, 0), 1);

	return output;
}

#shader fragment

float4 PShader(float4 position : SV_POSITION) : SV_TARGET
{
	return float4(1,0,0,1);
}
#END