struct VOut
{
    float4 color : COLOR;
    float4 position : SV_POSITION;
    
};

cbuffer ConstantBuffer
{
    row_major matrix transform;
};

VOut main(float4 position : POSITION, float4 color : COLOR)
{
    VOut output;

    output.position = mul(position, transform);
    output.color = color;

    return output;
}
