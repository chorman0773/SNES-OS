#ifndef __Window_hpp_2018_05_06_20_07
#define __Window_hpp_2018_05_06_20_07

#include <GL/gl.h>
#include <GL/glxext.h>
#include <GL/glext.h>

#include <string>

using std::string;

class GLGraphicsContext;

class WindowHandle{
	int x;
	int y;
	int w;
	int h;
	bool visible;
	bool decorated;
	bool focused;
	GLGraphicsContext* ctx;
	Display* currDisplay;
public:
	WindowHandle(int,int,int,int,Display*);
	WindowHandle(const WindowHandle&);
	WindowHandle(WindowHandle&&);
	WindowHandle& operator=(const WindowHandle&);
	WindowHandle& operator=(WindowHandle&&);
	~WindowHandle();
	void createContext();
	void setVisible(bool);
	void setDecorated(bool);
	void setFocused(bool);
	void setSize(int,int);
	void moveTo(int,int);
	void setDisplay(Display*);
	GLGraphicsContext& getContext();
};

class Window{
	WindowHandle* handle;
	bool resizeable;
	string title;
public:
	Window(WindowHandle&);
	Window(Window&&);
	Window(const Window&);
	Window& operator=(Window&&);
	Window& operator=(const Window&);
	void dispose();
	void setVisible(bool);
	void setResizeable(bool);
	void setDecorated(bool);
	void focus();
	void unfocus();
	void redraw();
	bool isVisible()const;
	void setTitle(string);
	const string& getTitle()const;
	GLXContext getGLXCtx();
	Graphics& getGraphics();
};

Window openWindow();


#endif
