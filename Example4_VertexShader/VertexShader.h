float fTime;			  // Time parameter. This keeps increasing

struct VS_OUTPUT
{
	float4 Position : POSITION;   // vertex position 
	float4 Diffuse : COLOR0;     // vertex diffuse color
};

VS_OUTPUT MainVS(in float4 vPosition : POSITION)
{
	VS_OUTPUT Output;

	// Simply pass original value of the position
	Output.Position = vPosition;

	// Output the final color as function of time in RED channel
	Output.Diffuse = float4(fTime, 0.0f, 0.0f, 1.0f);

	return Output;
}


