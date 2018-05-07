#ifndef __Window_hpp_2018_05_06_20_07
#define __Window_hpp_2018_05_06_20_07

#include <GL/gl.h>
#include <GL/glxext.h>
#include <GL/glext.h>

class WindowHandle{
	int x;
	int y;
	int w;
	int h;
	bool visible;
	bool decorated;
	bool focused;
	GLXContext ctx;
	Display* currDisplay;
};

#endif
