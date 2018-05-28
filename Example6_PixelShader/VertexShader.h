struct VS_OUTPUT
{
	float4 Position : POSITION;   // vertex position 
	float3 VertexCoords : TEXCOORD0;   // vertex coordiinates
};

VS_OUTPUT MainVS(in float4 vPosition : POSITION)
{
	VS_OUTPUT Output;

	// Simply pass original value of the position
	Output.Position = vPosition;

	// Pass original value of the position as vertex coordinates
	Output.VertexCoords = vPosition;

	return Output;
}


