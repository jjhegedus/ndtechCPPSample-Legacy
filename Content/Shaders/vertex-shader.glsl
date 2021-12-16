#version 430 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 color;

uniform mat4 ViewProjectionMatrix;
uniform mat4 ModelWorldMatrix;

out vec4 fragmentColor;

void main() {
  gl_Position = ViewProjectionMatrix * ModelWorldMatrix * vec4(vertexPosition_modelspace, 1.0);

  fragmentColor = vec4(color.x, color.y, color.z, 1);
}