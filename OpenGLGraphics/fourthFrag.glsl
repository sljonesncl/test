#version 150 core

uniform sampler2D normalTex;
uniform sampler2D noiseT;
uniform float time;


in Vertex	{
	vec2 texCoord;
	vec4 colour;
} IN;

out vec4 gl_FragColor;

void main(void)	{	
vec4 smileyColour = texture(normalTex, IN.texCoord);

vec2 tempTex = IN.texCoord;

gl_FragColor = smileyColour / (texture(noiseT , tempTex ) * time );

gl_FragColor.a = 255;

}
