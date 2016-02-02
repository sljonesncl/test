#version 330 core

uniform sampler2D smileyT;// Bind smiley face tex to a TU and set
uniform sampler2D crackT;// Bind static face tex to a TU and set

uniform float time; // This should be some sort of incrementing value

in Vertex {
	smooth vec4 colour;
	smooth vec2 texCoord;
} IN;

out vec4 gl_FragColor;

void main ( void ) {
	vec4 smileyColour = texture(smileyT,IN.texCoord);
	vec4 crackColour = texture(crackT,IN.texCoord);

	gl_FragColor = (smileyColour * (time * 0.1)) + (crackColour * (1.0 - (time * 0.1)));
}
