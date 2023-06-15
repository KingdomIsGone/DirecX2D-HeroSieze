struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
};

cbuffer Transform : register(b0)
{
    float4 Pos;
    float4 Color;
    float4 Scale;
}

VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.0f;
    
    Out.Pos = float4(In.Pos, 1.0f);
    //Out.Pos.x += 0.4f; //inputPosx; -> 상수버퍼를 통해서 이 데이터가 넘어와야한다.
    
    Out.Pos.x = Out.Pos.x * Scale.x;
    Out.Pos.y = Out.Pos.y * Scale.y;
    
    Out.Pos += Pos;
    
    Out.Color = Color;
    
    // sin();
    
    return Out;
}