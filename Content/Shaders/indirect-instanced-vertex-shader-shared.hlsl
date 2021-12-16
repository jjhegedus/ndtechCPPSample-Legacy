
struct InstanceRenderingData
{
    float4x4 world;
};
RWStructuredBuffer<InstanceRenderingData> instanceRenderingData : register(u1);

// A constant buffer that stores the model transform.
cbuffer ModelConstantBuffer : register(b0)
{
  float4x4 model;
  float instanceId;
  float pad1;
  float pad2;
  float pad3;
};

// A constant buffer that stores each set of view and projection matrices in column-major format.
cbuffer ViewProjectionConstantBuffer : register(b1)
{
  float4x4 viewProjection[2];
};

// Per-vertex data used as input to the vertex shader.
struct VertexShaderInput
{
  min16float3 pos     : POSITION;
  min16float3 color   : COLOR0;
  uint        instId  : SV_InstanceID;
  uint        vid     : SV_VertexID;
};

// Simple shader to do vertex processing on the GPU.
VertexShaderOutput main(VertexShaderInput input)
{
  VertexShaderOutput output;
  float4 pos = float4(input.pos, 1.0f);

  // Note which view this vertex has been sent to. Used for matrix lookup.
  // Taking the modulo of the instance ID allows geometry instancing to be used
  // along with stereo instanced drawing; in that case, two copies of each 
  // instance would be drawn, one for left and one for right.
  int idx = input.instId % 2;

  //float4x4 mdl = instanceRenderingData[instanceId].world;
  // Transform the vertex position into world space.
  pos = mul(pos, model);
  float4x4 mdl = instanceRenderingData[instanceId].world;
  //pos = mul(pos, mdl);

  // Correct for perspective and project the vertex position onto the screen.
  pos = mul(pos, viewProjection[idx]);
  output.pos = (min16float4)pos;

  // Pass the color through without modification.
  output.color = input.color;


  //int column = fmod(input.instId, 4);


  //if (column == 0) {
  //  output.color = float3(0, 0, 1);
  //}
  //else if (column == 1) {
  //  output.color = float3(0, 1, 0);
  //}
  //else if (column == 2) {
  //  output.color = float3(1, 0, 0);
  //}
  //else {
  //  output.color = float3(1, 1, 0);
  //}

  // Set the render target array index.
  output.viewId = idx;

  return output;
}
