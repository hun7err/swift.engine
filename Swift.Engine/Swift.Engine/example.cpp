#include "Supervisor.h"
#include "Sphere.h"
#include <iostream>
#include <GL/glfw.h>
using namespace std;
using namespace Swift;

#define GLFW_STATIC

int main() {
	if(!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW!\n");
		return -1;
	}
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 4);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 0);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if(!glfwOpenWindow( 800, 600, 0,0,0,0, 32, 0, GLFW_WINDOW)) {
		fprintf(stderr, "Failed to open GLFW window\n");
		glfwTerminate();
		return -1;
	}
	glewExperimental = true;
	if(glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		glfwSleep(1.0);
		return -1;
	}
	glfwSetWindowTitle("Swift::Engine test");
	glfwEnable(GLFW_STICKY_KEYS);

	cout << "=========================" << endl;
	cout << "OpenGL version: " << Supervisor->getOpenGLversion() << endl;
	cout << "GPU info: " << Supervisor->getVendor() << " " << Supervisor->getRenderer() << endl;
	cout << "Shader language version: " << Supervisor->getShaderLanguageVersion() << endl;
	cout << "=========================" << endl;
	
	Camera *cam = new Camera(
			glm::vec3(7,5,-12),	// location
			glm::vec3(0,0,0),	// target
			glm::vec3(0,1,0),	// up vector
			45.0f,				// field of view
			4.0f/3.0f,			// aspect
			0.1f,				// near clipping
			100.0f				// far clipping
		);
	
	Renderer *renderer = new Renderer();
	renderer->clearColor(0.0f, 0.0f, 0.4f, 0.0f); // czasem tu si� pojawia segfault :x
	renderer->setCamera(cam);

	Sphere	*s1 = new Sphere(3, 55, 29, glm::vec3(0,0,0)),
			*s2 = new Sphere(1, 25, 19, glm::vec3(5,0,0));
	//MaterialManager->loadShader("default", "default.vxshader", "default.pxshader");
	MaterialManager->loadShader("distance", "distance.vxshader", "distance.pxshader");
	Material* def = new Material("distance");

	s1->setMaterial(def);
	s1->setName("Sfera 1");
	s2->setMaterial(def);
	s2->setName("Sfera 2");

	Group* g = new Group(s1);
	g->setName("Okon"); // Podaj� has�o: oko�.
	g->add(s2);

	/*
	  to-do:
	  -------
		-! przelicza� �rodek grupy po dodaniu ka�dego obiektu
		  (wsp�rz�dne w przestrzeni �wiata! a �rodek w przestrzeni "grupy" tj. grupie modeli)
		-!! doda� transformacje grup (translacja, obr�t itp.)
		-!!! doda� kumulowane transformacje �eby jedna z kul mog�a si� obraca� i wok� w�asnej osi i wok� drugiej kuli
		- poprawi� distance shading -> maksymalna odleg�o�� od obiektu
		- poprawi� material manager -> definiowanie zmiennych kt�re b�dzie mo�na przekaza� do shadera ju� w aplikacji
		  "roboczej" (tu example.cpp)
		- tekstury!
		- texture manager na uchwytach (materia�y te�)
	*/

	ObjectManager->add(g);

	// render loop
	float angle = 0.5f;
	//double i = 0;
	renderer->setRenderMode(SW_WIREFRAME);
	do {
		// obr�t pierwszej kuli
		s1->rotate(glm::vec3(0,1,0), angle);
		
		// obr�t wok� pierwszej kuli
		s2->rotate(glm::vec3(0,1,0), 2*angle);
		glm::vec3 pos = s2->getPosition();
		// obr�t wok� w�asnej osi
		s2->move(pos);
		s2->rotate(glm::vec3(0,1,0), angle);
		s2->move(-pos);

		renderer->render();
		glfwSwapBuffers();
	} while (glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS && glfwGetWindowParam(GLFW_OPENED));

	delete g;
	//delete s1;
	//delete s2;
	delete def;
	delete renderer;
	delete cam;

	glfwTerminate();
	// automatycznie zwalnia� wszystkie wska�niki przez delete
	return 0;
}