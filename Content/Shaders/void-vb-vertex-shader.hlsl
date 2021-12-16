

// Per-vertex data passed to the geometry shader.
// Note that the render target array index will be set by the geometry shader
// using the value of viewId.
struct VertexShaderOutput
{
  min16float4 pos     : SV_POSITION;
  min16float3 color   : COLOR0;
  uint        viewId  : TEXCOORD0;  // SV_InstanceID % 2
};

#include "void-vb-vertex-shader-shared.hlsl"