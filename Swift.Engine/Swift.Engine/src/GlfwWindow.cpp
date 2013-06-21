#include "../include/GlfwWindow.h"

namespace Swift {
	GlfwWindow::GlfwWindow() : width(800), height(600), mode(SW_WINDOW), samples(4) {
		initWindow();
	}

	GlfwWindow::GlfwWindow(int w, int h, int m, std::string t):
		width(w),
		height(h),
		mode(m),
		title(t),
		samples(4)
	{
		initWindow();
	}

	GlfwWindow::~GlfwWindow() {
		destroy();
	}

	int GlfwWindow::initWindow() {
		if(!glfwInit()) {
			fprintf(stderr, "Failed to initialize GLFW!\n");
			return -1;
		}
		glfwOpenWindowHint(GLFW_FSAA_SAMPLES, samples);
		glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 4);
		glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 0);
		glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		if(!glfwOpenWindow( width, height, 0,0,0,0, 32, 0, mode)) {
			fprintf(stderr, "Failed to open GLFW window\n");
			glfwTerminate();
			return -1;
		}
		glfwSetWindowTitle(title.c_str());
		glfwEnable(GLFW_STICKY_KEYS);
		return 0;
	}

	int GlfwWindow::destroy() {
		glfwTerminate();
		return 0;
	}

	void GlfwWindow::swapBuffers() {
		glfwSwapBuffers();
	}

	bool GlfwWindow::isOpen() {
		return glfwGetWindowParam(GLFW_OPENED);
	}

	int GlfwWindow::getWidth() {
		return width;
	}

	int GlfwWindow::getHeight() {
		return height;
	}

	int GlfwWindow::getMode() {
		return mode;
	}

	int GlfwWindow::getFSAAsamples() {
		return samples;
	}

	std::string GlfwWindow::getTitle() {
		return title;
	}

	void GlfwWindow::setMode(int m) {
		mode = m;
	}

	void GlfwWindow::setFSAAsamples(int count) {
		samples = count;
	}
	
	void GlfwWindow::setTitle(std::string t) {
		title = t;
	}
	
	void GlfwWindow::setWidth(int w) {
		width = w;
	}
	
	void GlfwWindow::setHeight(int h) {
		height = h;
	}
}