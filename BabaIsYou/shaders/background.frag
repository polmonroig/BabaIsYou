#version 330

uniform vec3 color;

out vec4 FragColor;


void main(){
	// FragColor = vec4(0.031, 0.031, 0.031, 1);
	FragColor = vec4(color, 1);

}

