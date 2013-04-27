#ifndef GLFWWINDOW_H
#define GLFWWINDOW_H

#include <GL/glfw.h>
#include <string>

#define GLFW_STATIC
#define SW_WINDOW GLFW_WINDOW
#define SW_FULLSCREEN GLFW_FULLSCREEN

namespace Swift {
	class GlfwWindow {
		private:
			int width;
			int height;
			int mode;
			std::string title;
			int samples;

			int initWindow();
			int destroy();
		public:
			void swapBuffers();

			bool isOpen();
			int getWidth();
			int getHeight();
			std::string getTitle();
			int getFSAAsamples();
			int getMode();

			void setMode(int m);
			void setFSAAsamples(int count);
			void setTitle(std::string t);
			void setWidth(int w);
			void setHeight(int h);
		GlfwWindow();
		GlfwWindow(int w, int h, int m, std::string t = "Swift::Engine example application");
		~GlfwWindow();
	};
}

#endif // GLFWWINDOW_H