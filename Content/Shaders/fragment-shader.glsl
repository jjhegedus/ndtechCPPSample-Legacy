#version 430 core
in vec4 fragmentColor;
out vec4 color;
uniform mat4 RotationMatrix;
uniform vec3 OverrideColor;

void main(){
  
//  color = vec3(1,0,0);
  color = fragmentColor;
//  color = vec3(RotationMatrix[0][0], RotationMatrix[0][1], RotationMatrix[0][2]);

//  color = OverrideColor;
}