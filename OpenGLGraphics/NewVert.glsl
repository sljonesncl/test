#version 330 core

uniform float scale;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

in  vec3 position;
in  vec2 texCoord;
in  vec4 colour;

out Vertex	{
	vec2 texCoord;
	vec4 colour;
} OUT;

void main(void)	{
	gl_Position		= (projMatrix * viewMatrix * modelMatrix) * vec4(position, scale);
	
	OUT.texCoord	= texCoord;
	OUT.colour		= colour;
}