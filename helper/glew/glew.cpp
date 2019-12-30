#include "glew.h"
#include <GL/glew.h>

void GlHelper::GLEW::init()
{
	if (glewInit() != GLEW_OK)
	{
		throw GLEWError("Cannot init glew.");
	}
}
