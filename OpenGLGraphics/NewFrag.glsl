#version 330 core

uniform sampler2D smileyT;
uniform sampler2D noiseT;
uniform float time;


in Vertex	{
	vec2 texCoord;
	vec4 colour;
} IN;

out vec4 gl_FragColor;

void main(void)	{	
vec4 smileyColour = texture(smileyT, IN.texCoord);

if(smileyColour.b > 0.1) {
vec2 tempTex = IN.texCoord ;
tempTex.y += time ;

gl_FragColor = texture(noiseT, tempTex );
gl_FragColor.a = 0.6;
}else{
gl_FragColor = smileyColour;
gl_FragColor.a = 0.3;

}


}