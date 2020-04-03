#version 330

uniform mat4 projectionMatrix, modelViewMatrix;

in vec3 position;
in vec2 texCoord;

out vec2 vtexCoord;

void main(){
	vtexCoord = texCoord;
	gl_Position = projectionMatrix * modelViewMatrix * vec4(position,  1.0);
}
