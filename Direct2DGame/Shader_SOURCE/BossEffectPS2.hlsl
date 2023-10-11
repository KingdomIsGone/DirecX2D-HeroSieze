#include "globals.hlsli"

struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float3 WorldPos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};


float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float4) 0.0f;
    
    // 1200 1032 // 120 130
    // 1080 -> 540
    // -540 + 1200 
    color = albedoTexture.Sample(anisotropicSampler, In.UV);
    
    if (animationType == 1)
    {
        float2 diff = (AtlasSize - SpriteSize) / 2.0f;
        float2 UV = (SpriteLeftTop - diff - SpriteOffset)
                + (AtlasSize * In.UV);
    
        if (UV.x < SpriteLeftTop.x || UV.x > SpriteLeftTop.x + SpriteSize.x
            || UV.y < SpriteLeftTop.y || UV.y > SpriteLeftTop.y + SpriteSize.y)
            discard;
        
        color = atlasTexture.Sample(anisotropicSampler, UV);
    }
    
    //float4 lightColor = float4(0.2f, 0.2f, 0.2f, 1.0f);
    float4 lightColor = float4(0.1f, 0.1f, 0.1f, 1.0f);
    
    for (int i = 0; i < 2; i++)
    {
        CalculateLight2D(lightColor, In.WorldPos, i);
    }
    
    color *= lightColor;
    
    //custom
    //if(color.a > 0.0f)
    //    color.a = 0.5f;
    
    if (color.x <= 0.22f && color.y <= 0.22f && color.z <= 0.22f)
        color.w = 0.0f;
    else
    {
        color.x += Radd2;
        color.y += Gadd2;
        color.z += Badd2;
        color.w = A2;
    }
    
    
    if (color.w <= 0.0f)
        discard;
    
    
    return color;
}