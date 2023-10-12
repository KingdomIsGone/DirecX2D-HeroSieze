#include "globals.hlsli"



struct GSOut
{
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD;
};

float4 main(GSOut In) : SV_TARGET
{
    float4 Color = (float4) 0.0f;
    
    Color = albedoTexture.Sample(anisotropicSampler, In.UV);
    
    if (Color.w <= 0.0f)
        discard;
    
    //Color.w = ParticleAlpha;
    Color.w = 1.f;
    
    return Color;

}