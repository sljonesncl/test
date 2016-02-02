#pragma once
#include "../nclgl/OGLRenderer.h"

#include "RenderObject.h"

#include <vector>

using std::vector;

class Renderer : public OGLRenderer	{
public:
	Renderer(Window &parent);
	~Renderer(void);

	virtual void	RenderScene();

	virtual void	Render(const RenderObject &o);

	virtual void	UpdateScene(float msec);

	void	AddRenderObject(RenderObject &r) {
		renderObjects.push_back(&r);
	}

	void resetScale()
	{
		scale = 1;
	}

	void resetTime()
	{
		time = 0;
	}

protected:
	GLuint loadTexture(const char* textIn);
	GLuint smileyTexture;
	GLuint noiseTexture;
	GLuint perlinTexture;
	GLuint crackTexture;
	float roc;
	float time;
	float scale;
	vector<RenderObject*> renderObjects;
};

