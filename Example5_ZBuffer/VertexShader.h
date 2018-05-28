float4 vColor;			  // Time parameter. This keeps increasing
float3 vPosOffest;

struct VS_OUTPUT
{
	float4 Position : POSITION;   // vertex position 
	float4 Diffuse : COLOR0;     // vertex diffuse color
};

VS_OUTPUT MainVS(in float4 vPosition : POSITION)
{
	VS_OUTPUT Output;

	// Set original value of the position
	Output.Position = vPosition;
	// Offset it by value from vPosOffest constant
	Output.Position.xyz += vPosOffest;

	// Output vaue form vColor constant as final color
	Output.Diffuse = vColor;

	return Output;
}


