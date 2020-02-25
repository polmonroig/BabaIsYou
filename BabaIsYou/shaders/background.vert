#version 330

uniform mat4 projectionMatrix, modelViewMatrix;

in vec2 position;

void main(){
	gl_Position = projectionMatrix * modelViewMatrix * vec4(position, -10, 1.0);
}
