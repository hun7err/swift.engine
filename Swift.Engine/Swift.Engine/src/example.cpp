#include "../include/Supervisor.h"
#include "../include/Sphere.h"
#include "../include/Plane.h"
#include "../include/Cube.h"
#include "../include/Mesh.h"
#include "../include/GlfwWindow.h"
#include <iostream>
using namespace std;
using namespace Swift;

#define GLFW_STATIC

int main() {
	GlfwWindow *window = new GlfwWindow(800, 600, SW_WINDOW, "Swift::Engine test");
	int width = window->getWidth(),
		height = window->getHeight(),
		mode = window->getMode();

	glewExperimental = true;
	if(glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		glfwSleep(1.0);
		return -1;
	}

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
			(float)width/(float)height,			// aspect
			0.1f,				// near clipping
			100.0f				// far clipping
		);
	
	Renderer *renderer = new Renderer();
	//renderer->clearColor(0.0f, 0.0f, 0.4f, 0.0f);
	renderer->clearColor(1.0f, 1.0f, 1.0f, 1.0f);
	renderer->setCamera(cam);

	Sphere	*s1 = new Sphere(3, 55, 29, glm::vec3(0,0,0));//,
		//	*s2 = new Sphere(1, 25, 19, glm::vec3(5,0,0));

	Plane *p0 = new Plane(1000.0f, 1000.0f, glm::vec3(0,-10,0)),
			*p1 = new Plane(10.0f, 10.0f, glm::vec3(-5,0,0), 3, 3);

	Cube *c = new Cube(4.0f, glm::vec3(4,0,0));
	
	Mesh	*m = new Mesh("tree.obj"),
			*m2 = new Mesh("Lara_Croft.obj"),
			*m3 = new Mesh("teapot.obj"),
			*m4 = new Mesh("monkey.obj");

	//m->scale(glm::vec3(2.5f, 2.5f, 2.5f));
	m2->move(glm::vec3(-5,0,0));
	m2->scale(glm::vec3(2,2,2));
	m2->rotate(glm::vec3(0,1,0), 180);
	
	m3->move(glm::vec3(-12,0,0));

	m4->move(glm::vec3(-19,0,0));
	m4->scale(glm::vec3(2,2,2));
	m4->rotate(glm::vec3(0,1,0), 180);
	//m->move(glm::vec3(-20, -2, 0));
	//m->scale(glm::vec3(3.5f, 3.5f, 3.5f));
	//m->rotate(glm::vec3(0,1,0), 180);

	//MaterialManager->loadShader("default", "default.vxshader", "default.pxshader");
	MaterialManager->loadShader("distance", "distance.vxshader", "distance.pxshader");
	MaterialManager->loadShader("default", "default.vxshader", "default.pxshader");
	Material	*dist = new Material("distance"),
				*def = new Material("default");

	s1->setMaterial(dist);
	s1->setName("Sfera 1");
	//s2->setMaterial(def);
	//s2->setName("Sfera 2");
	p0->setMaterial(dist);
	p1->setMaterial(dist);
	c->setMaterial(dist);
	m->setMaterial(dist);
	m2->setMaterial(dist);
	m3->setMaterial(def);
	m4->setMaterial(dist);
	//m2->setMaterial(def);
	//m3->setMaterial(def);
	//m->hide();

	Group* g = new Group(s1);
	g->setName("Okon"); // Podajê has³o: okoñ.
	//g->add(s2);
	//g->add(p0);
	g->add(p1);
	g->add(c);
	g->add(m);
	g->add(m2);
	g->add(m3);
	g->add(m4);
	//g->add(m2);
	//g->add(m3);

	/*
	  to-do:
	  -------
		-!!!! sto¿ek (cone)
		-!!!! prostopad³oœcian (box)
		-!!!! predefiniowane: czajnik, ma³pa
		-!!!! 'p¹czek' (torus)
		-!!! sfera o równym roz³o¿eniu wierzcho³ków (ikosfera)
		-!!!!! model oœwietlenia phonga
			- œwiat³a -> punktowe i "obiektowe"
		- "miêkkie" œwiat³a (soft shadows)
		-!!! przemyœleæ co zrobiæ, ¿eby obiekt po prze³adowaniu pozostawa³ w swoim miejscu w którym by³ po przesuniêciu

		-! przeliczaæ œrodek grupy po dodaniu ka¿dego obiektu
		  (wspó³rzêdne w przestrzeni œwiata! a œrodek w przestrzeni "grupy" tj. grupie modeli)
		-!! dodaæ transformacje grup (translacja, obrót itp.)
		-!!!! naprawiæ kumulowane transformacje ¿eby jedna z kul mog³a siê obracaæ i wokó³ w³asnej osi i wokó³ drugiej kuli
		- poprawiæ distance shading -> maksymalna odleg³oœæ od obiektu
		- poprawiæ material manager -> definiowanie zmiennych które bêdzie mo¿na przekazaæ do shadera ju¿ w aplikacji
		  "roboczej" (tu example.cpp)
		-!!!!! tekstury!
		-!!!!! texture manager na uchwytach (materia³y te¿)

		
		-!!!! szeœcian (cube)			(done)
		-!!!! ³adowanie modelu z pliku	(done, pozostaje .3ds, .blend i w³asny format)
	*/

	ObjectManager->add(g);

	// render loop
	float angle = 0.5f;
	//double i = 0;
	glm::vec3 target = cam->getTarget();
	glm::vec3 camPos = cam->getPosition();
	double	x = target.x - camPos.x,
			y = target.y - camPos.y,
			z = target.z - camPos.z;
	double xz = sqrt(x*x + z*z);

	float horizontalAngle = atan(x/z);
	float verticalAngle = atan(y/xz);
	float speed = 15.0f;
	float mouseSpeed = 0.05f;
	
	renderer->setRenderMode(SW_WIREFRAME);
	double lastTime = glfwGetTime();

	do {
		double currentTime = glfwGetTime();
		float deltaTime = float(currentTime - lastTime);
		lastTime = currentTime;
		int xpos, ypos;
		glfwGetMousePos(&xpos, &ypos);
		glfwSetMousePos(width/2, height/2);
		horizontalAngle += mouseSpeed * deltaTime * float(width/2 - xpos);
		verticalAngle += mouseSpeed * deltaTime * float(height/2 - ypos);

		glm::vec3 direction(
			cos(verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle),
			cos(verticalAngle) * cos(horizontalAngle)
		);

		glm::vec3 right = glm::vec3(
			sin(horizontalAngle - 3.14f/2.0f),
			0,
			cos(horizontalAngle - 3.14f/2.0f)
		);
		glm::vec3 up = glm::cross(right, direction);
		glm::vec3 position = cam->getPosition();
		if (glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS)
			position += direction * deltaTime * speed;
		if(glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS)
			position -= direction * deltaTime * speed;
		if(glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
			position += right * deltaTime * speed;
		if(glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS)
			position -= right * deltaTime * speed;
		if(glfwGetKey(GLFW_KEY_SPACE) == GLFW_PRESS)
			renderer->setRenderMode(SW_SOLID);
		if(glfwGetKey(GLFW_KEY_KP_ADD) == GLFW_PRESS) {
			int hs = p1->getHeightSegCount(),
				ws = p1->getWidthSegCount();
			p1->setHeightSegCount(++hs);
			p1->setWidthSegCount(++ws);
		}
		if(glfwGetKey(GLFW_KEY_F3) == GLFW_PRESS) {
			int s = c->getSegCount();
			c->setSegCount(++s);
		}
		if(glfwGetKey(GLFW_KEY_F1) == GLFW_PRESS) {
			int s = s1->getSegmentCount(),
				r = s1->getRingCount();
			s1->setSegmentCount(++s);
			s1->setRingCount(++r);
		}
		if(glfwGetKey(GLFW_KEY_F2) == GLFW_PRESS) {
			int s = s1->getSegmentCount(),
				r = s1->getRingCount();
			s1->setSegmentCount(--s);
			s1->setRingCount(--r);
		}
		if(glfwGetKey(GLFW_KEY_BACKSPACE) == GLFW_PRESS)
			m->loadObj("teapot.obj");

		cam->move(position, direction, up);
		// obrót pierwszej kuli
		//glm::vec3 pos = s1->getPosition();
		//s1->move(pos);
		//s1->rotate(glm::vec3(1,0,0), angle);
		//s1->move(-pos);
		//p1->rotate(glm::vec3(0,1,0), 0.5*angle);

		// s2->rotate(glm::vec3(0,1,0), 2*angle);

		renderer->render();
		window->swapBuffers();
	} while (glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS && window->isOpen());

	delete g;
	//delete s1;
	//delete s2;
	delete def;
	delete renderer;
	delete cam;

	delete window;
	// automatycznie zwalniaæ wszystkie wskaŸniki przez delete
	return 0;
}