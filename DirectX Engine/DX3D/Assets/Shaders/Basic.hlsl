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
  float scale;  
};


VSOutput VSMain(VSInput input) 
{
    VSOutput output;
    output.position = float4(input.position * scale, 1);
    output.color = input.color;
    return output;
}
float4 PSMain(VSOutput input) : SV_Target
{
    return input.color;
}
