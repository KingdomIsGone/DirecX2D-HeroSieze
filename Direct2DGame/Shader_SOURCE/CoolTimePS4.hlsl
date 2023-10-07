#include "globals.hlsli"

struct VSIn
{
    float3 Pos : POSITION; //���ؽ� ��ġ
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position; //�ȼ� ��ġ
    float3 WorldPos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};


float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float4) 0.0f;
    
    // -540 + 1200 
    color = albedoTexture.Sample(anisotropicSampler, In.UV);
    
    float4 lightColor = float4(0.2f, 0.2f, 0.2f, 1.f);
    
    for (int i = 0; i < 2; i++)
    {
        CalculateLight2D(lightColor, In.WorldPos, i);
    }
    
    
    color *= lightColor;
    
    if (In.UV.y >= 1 - CoolTimePercent4) //���ۼ�Ʈ�� 1���� 0���� ��������.
        color += float4(-0.7f, -0.7f, -0.7f, 1.f);
    
    return color;
}