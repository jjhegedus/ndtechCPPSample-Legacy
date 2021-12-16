// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
	min16float4 pos     : SV_POSITION;
	//min16float3 posW    : POSITION;
	min16float3 color   : COLOR0;
	//min16float3 normal  : NORMAL;
	//min16float2 tex     : TEXCOORD;
	//min16float3 size    : SIZE;
};

// The pixel shader passes through the color data. The color data from 
// is interpolated and assigned to a pixel at the rasterization step.
min16float4 main(PixelShaderInput input) : SV_TARGET
{
	//min16float4 p = input.pos;
	//min16float3 pw = input.posW;
	//min16float3 pc = input.color;
	//min16float3 pn = input.normal;
	//min16float2 pt = input.tex;

	////return ((input.posW.x * input.posW.x) + (input.posW.y * input.posW.y)) < (input.size.x * input.size.x) ? min16float4(input.color, 1.0f) : min16float4(0.f, 0.f, 0.f, 0.f);
	return min16float4(input.color, 1.0f);
	//return min16float4(1.0f, 0.0f, 0.0f, 1.0f);
}