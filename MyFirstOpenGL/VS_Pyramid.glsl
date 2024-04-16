#version 440 core

layout(location = 0) in vec3 position;

uniform mat4 translationMatrix;
uniform mat4 rotationMatrixX;
uniform mat4 rotationMatrixY;
uniform mat4 scaleMatrix;

void main() {

    mat4 model = translationMatrix * rotationMatrixX * rotationMatrixY * scaleMatrix;

    gl_Position = model * vec4(position, 1.0);
}