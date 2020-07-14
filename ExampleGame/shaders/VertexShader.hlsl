//struct that holds position and color
struct VOut
{
    float4 color : COLOR;
    float4 position : SV_POSITION;
    
};

//cbuffer that holds a matrix defining rotation around the Z-axis
cbuffer YawRot
{
    row_major matrix transform;
};

VOut main(float4 position : POSITION, float4 color : COLOR)
{
    VOut output;

    output.position = mul(position, transform);//multiply position by rotation matrix
    output.color = mul(color, transform); //multiply color by rotation matrix

    return output;
}
