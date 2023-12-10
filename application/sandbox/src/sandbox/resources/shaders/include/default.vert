    cbuffer CameraBuffer : register(b0)
    {
        float4 u_viewPosition;
        matrix u_projection;
        matrix u_view;
        matrix u_model;
    };

    struct VIn
    {
        float3 normal : NORMAL;
        float2 texCoords : TEXCOORD;
    };

    struct VOut
    {
        float4 p_position : SV_POSITION;
        float3 p_normal : NORMAL;
        float2 p_texCoords : TEXCOORD;


        float3 p_fragPos : TEXCOORD1;
    };

    VOut main(float4 position : POSITION, VIn input)
    {
        VOut output;

        output.p_position = mul(mul(mul(u_projection, u_view), u_model), position);
        output.p_fragPos = mul(u_model, position).rgb;
        //output.p_normal = normalize(mul(input.normal, (float3x3)transpose(inverse(u_model))));
        output.p_normal = normalize(input.normal);
        output.p_texCoords = input.texCoords;

        return output;
    }