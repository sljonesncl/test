#include "Renderer.h"

Renderer::Renderer(Window &parent) : OGLRenderer(parent)	{

	//glEnable(GL_DEPTH_TEST);
	smileyTexture = loadTexture("smiley.png");
	noiseTexture = loadTexture("noise.png");
	perlinTexture = loadTexture("perlin.png");
	crackTexture = loadTexture("cracks.png");
	time = 0.0f;
	scale = 1.0f;

}

Renderer::~Renderer(void)	{
	glDeleteTextures(1, &smileyTexture);
	glDeleteTextures(1, &noiseTexture);
}

void	Renderer::RenderScene() {
	for(vector<RenderObject*>::iterator i = renderObjects.begin(); i != renderObjects.end(); ++i ) {
		Render(*(*i));
	}
}

GLuint Renderer::loadTexture(const char* textIn)
{
GLuint texture;
texture = SOIL_load_OGL_texture(textIn, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);


glBindTexture(GL_TEXTURE_2D, texture);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

return texture;
}

void	Renderer::Render(const RenderObject &o) {
	modelMatrix = o.GetWorldTransform();

	if(o.GetShader() && o.GetMesh()) {
		GLuint program = o.GetShader()->GetShaderProgram();
		
		glUseProgram(program);

		UpdateShaderMatrices(program);
		glUniform1i(glGetUniformLocation(program, "smileyT"), 0);
		glUniform1i(glGetUniformLocation(program, "noiseT"), 1);
		glUniform1i(glGetUniformLocation(program, "perlinT"), 2);
		glUniform1i(glGetUniformLocation(program, "crackT"), 3);
		glUniform1f(glGetUniformLocation(program, "time"), time);
		glUniform1f(glGetUniformLocation(program, "scale"), scale);

		scale += 0.1;
		if (scale > 110)
		{
			scale = 0.5;
		}
		time += 0.1;

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, smileyTexture);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, noiseTexture);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, perlinTexture);

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, crackTexture);

		o.Draw();
	}

	for(vector<RenderObject*>::const_iterator i = o.GetChildren().begin(); i != o.GetChildren().end(); ++i ) {
		Render(*(*i));
	}
}

void	Renderer::UpdateScene(float msec) {
	time += msec;

	for(vector<RenderObject*>::iterator i = renderObjects.begin(); i != renderObjects.end(); ++i ) {
		(*i)->Update(msec);
	}
}