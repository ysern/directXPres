float fTime;			  // Time parameter. This keeps increasing

struct PS_INPUT
{
	float3 VertexCoords : TEXCOORD0;   // vertex coordiinates
};

struct PS_OUTPUT
{
	float4 Diffuse : COLOR0;     // vertex diffuse color
};

PS_OUTPUT MainPS(PS_INPUT Input)
{
	PS_OUTPUT Output;

	float fSin, fCos;
	float x = length(Input.VertexCoords) * sin(fTime) * 100.0f;

	// This HLSL intrinsic computes returns both the sine and cosine of x
	sincos(x, fSin, fCos);

	// Output the diffuse color as function of time and 
	// the vertex's object space position
	Output.Diffuse = 0.5f - 0.5f * fCos;

	return Output;
}


