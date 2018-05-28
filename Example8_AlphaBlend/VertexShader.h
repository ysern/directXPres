struct VS_INPUT
{
	float3 Position : POSITION;   // vertex position 
	float2 TexCoords : TEXCOORD0;   // texture coordiinates
};

struct VS_OUTPUT
{
	float4 Position : POSITION;   // vertex position 
	float2 TexCoords : TEXCOORD0;   // texture coordiinates
};

VS_OUTPUT MainVS(VS_INPUT Input)
{
	VS_OUTPUT Output;

	// Pass original value of the position
	Output.Position = float4(Input.Position, 1.0f);

	// Pass original value of the texture coordinates
	Output.TexCoords = Input.TexCoords;

	return Output;
}


