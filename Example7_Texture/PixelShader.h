float fTime;			  // Time parameter. This keeps increasing

sampler2D tex0;

struct PS_INPUT
{
	float2 TexCoords : TEXCOORD0;   // texture coordiinates
};

struct PS_OUTPUT
{
	float4 Diffuse : COLOR0;     // vertex diffuse color
};

PS_OUTPUT MainPS(PS_INPUT Input)
{
	PS_OUTPUT Output;

	float4 texColor = tex2D(tex0, Input.TexCoords);

	Output.Diffuse.rgb = texColor.rgb * texColor.aaa;
	Output.Diffuse.a = 1.0f;

	return Output;
}


