#version 430 core
#extension GL_ARB_shader_storage_buffer_object : require

#define MODEL_VERTICES 0
#define MATERIAL_BUFFER 1
#define PER_VERTEX_BUFFER 2
#define PER_INSTANCE_BUFFER 3

uniform mat4 ViewProjectionMatrix;
uniform mat4 ModelWorldMatrix;

//Start Void VB specific
struct ModelVertex {
  vec3 position;
  float pad;
};

layout(std430, binding = MODEL_VERTICES) buffer modelVertices
{
  ModelVertex modelVertex[];
};

struct Material {
  vec4 color;
};

layout(std430, binding = MATERIAL_BUFFER) buffer materials
{
  Material materialData[];
} Materials;

//struct MaterialsData {
//  Material materialData[3];
//};


struct PerVertexData {
  unsigned int instanceId;
  unsigned int index;
  unsigned int eye;
  unsigned int materialId;
};

layout(std430, binding = PER_VERTEX_BUFFER) buffer perVertexBuffer
{
  PerVertexData perVertexData[];
} PerVertexBuffer;

//struct PerVertexBufferData {
//  PerVertexData perVertexData[72];
//};

struct PerInstanceData {
  mat4 world;
};

layout(std430, binding = PER_INSTANCE_BUFFER) buffer perInstanceBuffer
{
  PerInstanceData perInstanceData[];
} PerInstanceBuffer;

//End Void VB specific


out vec4 fragmentColor;

void main() {

  //MaterialsData Materials;
  //Materials.materialData[0].color = vec4(1, 0, 0, 1);
  //Materials.materialData[1].color = vec4(0, 1, 0, 1);
  //Materials.materialData[2].color = vec4(0, 0, 1, 1);


  //PerVertexBufferData PerVertexBuffer;

  //// Left Eye
  //PerVertexBuffer.perVertexData[0] = PerVertexData(0, 0, 0, 1);
  //PerVertexBuffer.perVertexData[1] = PerVertexData(0, 1, 0, 1);
  //PerVertexBuffer.perVertexData[2] = PerVertexData(0, 2, 0, 1);

  //PerVertexBuffer.perVertexData[3] = PerVertexData(0, 1, 0, 0);
  //PerVertexBuffer.perVertexData[4] = PerVertexData(0, 3, 0, 0);
  //PerVertexBuffer.perVertexData[5] = PerVertexData(0, 2, 0, 0);

  //PerVertexBuffer.perVertexData[6] = PerVertexData(0, 5, 0, 0);
  //PerVertexBuffer.perVertexData[7] = PerVertexData(0, 1, 0, 0);
  //PerVertexBuffer.perVertexData[8] = PerVertexData(0, 4, 0, 0);

  //PerVertexBuffer.perVertexData[9] = PerVertexData(0, 1, 0, 0);
  //PerVertexBuffer.perVertexData[10] = PerVertexData(0, 0, 0, 0);
  //PerVertexBuffer.perVertexData[11] = PerVertexData(0, 4, 0, 0);

  //PerVertexBuffer.perVertexData[12] = PerVertexData(0, 1, 0, 0);
  //PerVertexBuffer.perVertexData[13] = PerVertexData(0, 5, 0, 0);
  //PerVertexBuffer.perVertexData[14] = PerVertexData(0, 7, 0, 0);

  //PerVertexBuffer.perVertexData[15] = PerVertexData(0, 1, 0, 0);
  //PerVertexBuffer.perVertexData[16] = PerVertexData(0, 7, 0, 0);
  //PerVertexBuffer.perVertexData[17] = PerVertexData(0, 3, 0, 0);

  //PerVertexBuffer.perVertexData[18] = PerVertexData(0, 0, 0, 0);
  //PerVertexBuffer.perVertexData[19] = PerVertexData(0, 2, 0, 0);
  //PerVertexBuffer.perVertexData[20] = PerVertexData(0, 6, 0, 0);

  //PerVertexBuffer.perVertexData[21] = PerVertexData(0, 0, 0, 0);
  //PerVertexBuffer.perVertexData[22] = PerVertexData(0, 6, 0, 0);
  //PerVertexBuffer.perVertexData[23] = PerVertexData(0, 4, 0, 0);

  //PerVertexBuffer.perVertexData[24] = PerVertexData(0, 2, 0, 0);
  //PerVertexBuffer.perVertexData[25] = PerVertexData(0, 3, 0, 0);
  //PerVertexBuffer.perVertexData[26] = PerVertexData(0, 7, 0, 0);

  //PerVertexBuffer.perVertexData[27] = PerVertexData(0, 2, 0, 0);
  //PerVertexBuffer.perVertexData[28] = PerVertexData(0, 7, 0, 0);
  //PerVertexBuffer.perVertexData[29] = PerVertexData(0, 6, 0, 0);

  //PerVertexBuffer.perVertexData[30] = PerVertexData(0, 6, 0, 0);
  //PerVertexBuffer.perVertexData[31] = PerVertexData(0, 7, 0, 0);
  //PerVertexBuffer.perVertexData[32] = PerVertexData(0, 5, 0, 0);

  //PerVertexBuffer.perVertexData[33] = PerVertexData(0, 6, 0, 0);
  //PerVertexBuffer.perVertexData[34] = PerVertexData(0, 5, 0, 0);
  //PerVertexBuffer.perVertexData[35] = PerVertexData(0, 4, 0, 0);

  //// Right Eye
  //PerVertexBuffer.perVertexData[36] = PerVertexData(0, 0, 1, 1);
  //PerVertexBuffer.perVertexData[37] = PerVertexData(0, 1, 1, 1);
  //PerVertexBuffer.perVertexData[38] = PerVertexData(0, 2, 1, 1);

  //PerVertexBuffer.perVertexData[39] = PerVertexData(0, 1, 1, 0);
  //PerVertexBuffer.perVertexData[40] = PerVertexData(0, 3, 1, 0);
  //PerVertexBuffer.perVertexData[41] = PerVertexData(0, 2, 1, 0);

  //PerVertexBuffer.perVertexData[42] = PerVertexData(0, 5, 1, 0);
  //PerVertexBuffer.perVertexData[43] = PerVertexData(0, 1, 1, 0);
  //PerVertexBuffer.perVertexData[44] = PerVertexData(0, 4, 1, 0);

  //PerVertexBuffer.perVertexData[45] = PerVertexData(0, 1, 1, 0);
  //PerVertexBuffer.perVertexData[46] = PerVertexData(0, 0, 1, 0);
  //PerVertexBuffer.perVertexData[47] = PerVertexData(0, 4, 1, 0);

  //PerVertexBuffer.perVertexData[48] = PerVertexData(0, 1, 1, 0);
  //PerVertexBuffer.perVertexData[49] = PerVertexData(0, 5, 1, 0);
  //PerVertexBuffer.perVertexData[50] = PerVertexData(0, 7, 1, 0);

  //PerVertexBuffer.perVertexData[51] = PerVertexData(0, 1, 1, 0);
  //PerVertexBuffer.perVertexData[52] = PerVertexData(0, 7, 1, 0);
  //PerVertexBuffer.perVertexData[53] = PerVertexData(0, 3, 1, 0);

  //PerVertexBuffer.perVertexData[54] = PerVertexData(0, 0, 1, 0);
  //PerVertexBuffer.perVertexData[55] = PerVertexData(0, 2, 1, 0);
  //PerVertexBuffer.perVertexData[56] = PerVertexData(0, 6, 1, 0);

  //PerVertexBuffer.perVertexData[57] = PerVertexData(0, 0, 1, 0);
  //PerVertexBuffer.perVertexData[58] = PerVertexData(0, 6, 1, 0);
  //PerVertexBuffer.perVertexData[59] = PerVertexData(0, 4, 1, 0);

  //PerVertexBuffer.perVertexData[60] = PerVertexData(0, 2, 1, 0);
  //PerVertexBuffer.perVertexData[61] = PerVertexData(0, 3, 1, 0);
  //PerVertexBuffer.perVertexData[62] = PerVertexData(0, 7, 1, 0);

  //PerVertexBuffer.perVertexData[63] = PerVertexData(0, 2, 1, 0);
  //PerVertexBuffer.perVertexData[64] = PerVertexData(0, 7, 1, 0);
  //PerVertexBuffer.perVertexData[65] = PerVertexData(0, 6, 1, 0);

  //PerVertexBuffer.perVertexData[66] = PerVertexData(0, 6, 1, 0);
  //PerVertexBuffer.perVertexData[67] = PerVertexData(0, 7, 1, 0);
  //PerVertexBuffer.perVertexData[68] = PerVertexData(0, 5, 1, 0);

  //PerVertexBuffer.perVertexData[69] = PerVertexData(0, 6, 1, 0);
  //PerVertexBuffer.perVertexData[70] = PerVertexData(0, 5, 1, 0);
  //PerVertexBuffer.perVertexData[71] = PerVertexData(0, 4, 1, 0);





  PerVertexData vertexData = PerVertexBuffer.perVertexData[gl_VertexID];
  PerInstanceData instanceData = PerInstanceBuffer.perInstanceData[vertexData.instanceId];
  Material material = Materials.materialData[vertexData.materialId];
  gl_Position = ViewProjectionMatrix * instanceData.world * vec4(modelVertex[vertexData.index].position, 1);
  //gl_Position = ViewProjectionMatrix * ModelWorldMatrix * vec4(modelVertex[vertexData.index].position, 1);

  //if (gl_VertexID == 0) {
  //  gl_Position = ViewProjectionMatrix * instanceData.world * vec4(0.2, 0, -2.0, 1.0);
  //}
  //else if (gl_VertexID == 1) {
  //  gl_Position = ViewProjectionMatrix * instanceData.world * vec4(0.5, 0.6, -2.0, 1.0);
  //}
  //else if (gl_VertexID == 2) {
  //  gl_Position = ViewProjectionMatrix * instanceData.world * vec4(0.8, 0, -2.0, 1.0);
  //}
  //else {
  //  gl_Position = vec4(0, 0, 0, 1);
  //}

  //fragmentColor.x = tmpColor.x;

  //if (material.color.x == 1) {
  //  fragmentColor = vec4(0, 0, 1, 1);
  //}
  //else {
  //  fragmentColor = vec4(1, 0, 0, 1);
  //}

  //fragmentColor = vec4(vertexData.materialId, 0, 0, 1);

  //fragmentColor = vec4(color.x, color.y, color.z, 1);

  //fragmentColor = Materials.materialData[gl_VertexID].color;
  fragmentColor = material.color;
  //fragmentColor = vec4(0, 0, 1, 1);
  //fragmentColor = vec4(0, 0, 0, 1);
  //fragmentColor.r = vertexData.index;
  //fragmentColor = vec4(modelVertex[vertexData.index].position, 1);
}



//#version 330 core
//layout(location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
//out vec2 TexCoords;
//
//uniform mat4 projection;
//
//void main()
//{
//  gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
//  TexCoords = vertex.zw;
//}