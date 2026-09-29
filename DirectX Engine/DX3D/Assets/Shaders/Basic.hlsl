struct VSInput
{
    float3 position : POSITION0 ;
    float4 color : COLOR0 ;
};
/**
POSTION[n] and COLOR[n] are "semantics"
*/

struct VSOutput
{
    float4 position : SV_Position ; // clip space position
    float4 color : COLOR0 ;
};


cbuffer ConstantData : register(b0) {
  row_major float4x4 world;  
};


VSOutput VSMain(VSInput input) 
{
    VSOutput output;
    output.position = mul(float4(input.position, 1),world);
    output.color = input.color;
    return output;
}
float4 PSMain(VSOutput input) : SV_Target
{
    return input.color;
}
