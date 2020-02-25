#version 330

uniform sampler2D  sampler;
out vec4 FragColor;

in vec2 vtexCoord;

void main(){
	vec4 color = texture(sampler, vtexCoord);
	FragColor = color;
}
