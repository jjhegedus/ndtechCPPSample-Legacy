
//struct InstanceRenderingData
//{
//  float4x4 world;
//};
//RWStructuredBuffer<InstanceRenderingData> instanceRenderingData : register(u1);

struct ModelVertex {
  float3 position;
  float pad;
};
StructuredBuffer<ModelVertex>      modelVertex : register(t0);

struct Material {
  float3 color;
};
StructuredBuffer<Material>      materials : register(t1);

struct PerInstanceData {
  float4x4 world;
};
StructuredBuffer<PerInstanceData>      perInstanceData : register(t2);

struct PerVertexData {
  unsigned int instanceId;
  unsigned int index;
  unsigned int eye;
  unsigned int materialId;
};
StructuredBuffer<PerVertexData>      perVertexData : register(t3);

struct DirectionalLight {
  float3 color;
  float  intensity;
  float3 direction;
};
StructuredBuffer<DirectionalLight>  directionalLights : register(t4);

// A constant buffer that stores each set of view and projection matrices in column-major format.
cbuffer ViewProjectionConstantBuffer : register(b1)
{
  float4x4 viewProjection[2];
};

// Per-vertex data used as input to the vertex shader.
struct VertexShaderInput
{
  uint        vid     : SV_VertexID;
};

// Simple shader to do vertex processing on the GPU.
VertexShaderOutput main(VertexShaderInput input)
{
  VertexShaderOutput output;

  PerVertexData vertexData = perVertexData[input.vid];
  PerInstanceData instanceData = perInstanceData[vertexData.instanceId];

  float4 pos = float4(modelVertex[vertexData.index].position, 1);

  // Transform the vertex position into world space.
  pos = mul(pos, transpose(instanceData.world));

  // Correct for perspective and project the vertex position onto the screen.
  pos = mul(pos, viewProjection[vertexData.eye]);
  output.pos = (min16float4)pos;

  // Set the output color based on the material color
  output.color = float4(materials[vertexData.materialId], 1.0);

  output.viewId = vertexData.eye;

  uint numLights = 0;
  uint stride = 0;

  directionalLights.GetDimensions(numLights, stride);
  
  //uint lightNumber = 0;
  //for (lightNumber = 0; lightNumber < numLights) {

  //}

  //if (numLights >= 1) {
  //  if (directionalLights[0].color.y == 0.0) {
  //    output.color = float4(1.0, 0.0, 0.0, 1.0);
  //  }
  //}

  return output;
}
