#version 330

uniform sampler2D  sampler;
uniform vec3 color;

out vec4 FragColor;

in vec2 vtexCoord;

void main(){
	FragColor = vec4(color, 1) * texture(sampler, vtexCoord);

}
