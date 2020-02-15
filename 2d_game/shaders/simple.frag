#version 330

uniform sampler2D  sampler;
out vec4 FragColor;

in vec2 vtexCoord;

void main(){
	FragColor = texture(sampler, vtexCoord);
}
