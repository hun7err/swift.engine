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
	/*
		najwa�niejsze to-do:
		1. naprawi� shader phongblinn i nazwa� go phong
		2. doda� shader Phonga-Blinna
		3. doda� wy�wietlanie �wiate�
		4. doda� teksturowanie 2D, 3D i pobawi� si� renderowaniem obiektu do tekstury 3D
		5. przepisa� pod Qt -> edytor
	*/
	int width = 800, height = 600, mode = SW_WINDOW;
	ilInit();
	GlfwWindow *window = new GlfwWindow(width, height, mode, "Swift::Engine test");

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
			glm::vec3(-2,2,-12),	// location
			glm::vec3(0,0,0),	// target
			glm::vec3(0,1,0),	// up vector
			45.0f,				// field of view
			(float)width/(float)height,			// aspect
			0.1f,				// near clipping
			100.0f				// far clipping
		);
	printf("new Renderer()\n");
	Renderer *renderer = new Renderer();

	//renderer->clearColor(0.0f, 0.0f, 0.4f, 0.0f);
	renderer->clearColor(0.3f, 0.3f, 0.3f, 1.0f);
	//renderer->clearColor(1.0f, 1.0f, 1.0f, 1.0f);
	renderer->setCamera(cam);
	
	MaterialManager->loadShaders("phongblinn");
	Mesh *monkey = new Mesh("monkey.obj"),
		 *teapot = new Mesh("teapot.obj"),
		 *lara = new Mesh("Lara_Croft.obj"),
		 *tank = new Mesh("Abrams_BF3.obj"),
		 *heli = new Mesh("uh60.obj"); // m1abrams/Abrams_BF3.obj

	/*if(ret == SW_FAILURE) {
		printf("Failed to load T-90 model\n");
		return -1;
	}*/

	monkey->move(glm::vec3(-3,0,0));
	monkey->rotate(glm::vec3(0,1,0), 180);
	teapot->move(glm::vec3(-2,1,2.0f));
	teapot->scale(glm::vec3(0.2f)); // 0.2
	//tank->move(glm::vec3(0.0f));
	//tank->scale(glm::vec3(2.0f));

	Sphere *s = new Sphere(3.0f, 70, 50, glm::vec3(2,0,0)),
			*kula = new Sphere(1.0f, 30, 20, glm::vec3(-1,-2,-2));

	Light *light = new Light(glm::vec3(1.0f), glm::vec3(-3.0f,1.0f,-2.5f), 1.5f),
			*light2 = new Light(glm::vec3(0,0,1.0f), glm::vec3(2.5f,3.0f,-3.9f), 3.0f),
			*light3 = new Light(glm::vec3(0,1.0f,0), glm::vec3(-2,5,0),5.0f),
			*light4 = new Light(glm::vec3(1.0f), glm::vec3(-2,6,1.0f), 3.0f);

	MaterialManager->loadShaders("lambert");

	//printf("Tworzenie materialow\n");

	Material mmat("phongblinn", glm::vec3(0.0f,1.0f,0.0f), glm::vec3(1.0f), glm::vec3(0.1f)),
			tmat("phongblinn", glm::vec3(1.0f,0.0f,0.0f), glm::vec3(1.0f), glm::vec3(0.1f), 5),
			smat("lambert", glm::vec3(0.0f,0.0f,1.0f), glm::vec3(1.0f), glm::vec3(0.1f), 20),
			cmat("lambert", glm::vec3(0.3f), glm::vec3(1.0f), glm::vec3(0.3f));

	// to-do: tekstury 2D, 3D

	// pytanie: czy dla tekstur 3D te� s� UV czy UVW?
	// odpowied�: 
	// ---||--- gdyby podzieli� model na kilka cz�ci, to b�dzie mia� jedno VAO czy kilka?
	// odpowied�: mo�e by� jedno VAO, ale �onglowa� startow� warto�ci� w glDrawArrays() przy kilku VBO
	// (czyli w sumie jedna tablica z wierzcho�kami ale dla cz�ci musimy trzyma� gdzie si� zaczyna i ile wierzcho�k�w)

	MaterialPtr monkeymtl = MaterialManager->addMaterial(mmat),
				teapotmtl = MaterialManager->addMaterial(tmat),
				spheremtl = MaterialManager->addMaterial(smat),
				clay = MaterialManager->addMaterial(cmat);

	//printf("Ustawianie materialow\n");
	s->setMaterial(spheremtl);
	//printf("Malpa\n");
	monkey->setMaterial(monkeymtl);
	//printf("Czajnik\n");
	teapot->setMaterial(teapotmtl);
	kula->setMaterial(clay);
	//tank->setMaterial(clay);

	//lara->setMaterial(clay);
	//tank->setMaterial(clay);


	//tank->rotate(glm::vec3(1,0,0), 180);
	//tank->rotate(glm::vec3(1,0,0), 90);

	//printf("czesci w czolgu: %d\n", tank->getPartCount());
	
	//printf("Wszystko ok\n");
	//light1->setMaterial(def);
	
	//teapot->setMaterial(phong);

	//printf("Tworzenie grupy\n");
	Group* g = new Group();
	s->hide();
	monkey->hide();
	teapot->hide();
	kula->hide();
	lara->hide();
	//tank->hide();

	g->add(s);
	g->add(monkey);
	g->add(teapot);
	g->add(kula);
	g->add(lara);
	g->add(tank);
	//g->add(heli);

	/*
		z�e przypisania tekstur: jedn� pomija ca�kiem a reszt� przesuwa
	*/

	printf("przed wypisywaniem czesci\n");
	//printf("Material part0: %s\n", lara->getPartAt(1).getMaterial()->DiffuseMap->getName());
	printf("Dostepne materialy:\n");
	for(int i = 0; i < /*MaterialManager->getMaterialCount()*/25; i++) {
		Material mtl = MaterialManager->getMaterial(i);
		printf("%d\t", i);
		printf("%s\t", mtl.name.c_str());
		if(mtl.DiffuseMap != SW_TEXTURE_EMPTY) {
			printf("%s\t", mtl.DiffuseMap->getName().c_str());
			printf("%d\n", mtl.DiffuseMap->getImageID());
		}
		else
			printf("[None]\n");
		//printf("%d\t%s\t%s\n", i, mtl.name, mtl.DiffuseMap->getName().c_str());
	}
	printf("\nCzesci i przypisania materialow:\n");
	for(int i = 0; i < lara->getPartCount(); i++) {
		printf("%d\t", i);
		Material mtl = *(lara->getPartAt(i).getMaterial());
		printf("%s\t", mtl.name.c_str());
		if(mtl.DiffuseMap != SW_TEXTURE_EMPTY)
			printf("%s\t", mtl.DiffuseMap->getName().c_str());
		else
			printf("[None]\t");
		printf("%d\n", lara->getPartAt(i).getMaterial().key);
	}

	printf("-----------------\n");
	printf("UVs of tank:\n");
	for (int i = 0; i < 9; i += 3) {
		printf("tri %d start\n", i/3);
		printf("uv 1: %f %f\n", tank->getPartAt(0).uvs[i].x, tank->getPartAt(0).uvs[i].y);
		printf("uv 2: %f %f\n", tank->getPartAt(0).uvs[i+1].x, tank->getPartAt(0).uvs[i+1].y);
		printf("uv 3: %f %f\n", tank->getPartAt(0).uvs[i+2].x, tank->getPartAt(0).uvs[i+2].y);
		printf("tri %d end\n", i/3);
	}
	printf("-----------------\n");
	/*MaterialPtr m = MaterialManager->getMaterialByName("glass_png");
	printf("name: %s\n", (*m).name.c_str());
	printf("diffuse: %f %f %f\n", (*m).DiffuseColor.r, (*m).DiffuseColor.g, (*m).DiffuseColor.b);
	printf("ambient: %f %f %f\n", (*m).AmbientColor.r, (*m).AmbientColor.g, (*m).AmbientColor.b);
	printf("specular: %f %f %f\n", (*m).SpecularColor.r, (*m).SpecularColor.g, (*m).SpecularColor.b);
	printf("phong exp: %f\n", (*m).PhongExponent);*/

	/*for(int i = 0; i < tank->getPartCount(); i++) { // na part0 nie znalaz�o nazwy
		Material mtl = *(tank->getPartAt(i).getMaterial());
		printf("Part %d\n-------\n\n", i);
		printf("Mat name: %s\n", mtl.name.c_str());
		printf("Phong exponent: %d\n", mtl.PhongExponent);
		printf("Diffuse color: (%d, %d, %d)\n", mtl.DiffuseColor.r, mtl.DiffuseColor.g, mtl.DiffuseColor.b);
		if(mtl.DiffuseMap != SW_TEXTURE_EMPTY) printf("Diffuse tex: %s\n\n", mtl.DiffuseMap->getName().c_str());
	}*/

	/*printf("po wypisywaniu czesci\n");
	printf("atof(%s) = %f\n", "1.36848e-005", atof("1.36848e-005"));
	printf("part0:\n");
	printf("vertex size: %d\n", tank->getPartAt(0).vertices.size());
	printf("normal size: %d\n", tank->getPartAt(0).normals.size());
	printf("uv size: %d\n", tank->getPartAt(0).uvs.size());
	glm::vec2 uv = tank->getPartAt(0).uvs[tank->getPartAt(0).uvs.size()-1];
	printf("vt: %f %f\n", uv.x, uv.y);*/


	//for(int i = 0; i < 3; i++) printf("mtl key: %d\n", g->getObjectAt(i)->getPartAt(0).getMaterial().key);
	
	/*
	  to-do:
	  -------
		-!!!! sto�ek (cone)
		-!!!! prostopad�o�cian (box)
		-!!!! predefiniowane: czajnik, ma�pa
		-!!!! 'p�czek' (torus)
		-!!! sfera o r�wnym roz�o�eniu wierzcho�k�w (ikosfera)
		-!!!!! model o�wietlenia phonga
			- �wiat�a -> punktowe i "obiektowe"
		- "mi�kkie" �wiat�a (soft shadows)
		-!!! przemy�le� co zrobi�, �eby obiekt po prze�adowaniu pozostawa� w swoim miejscu w kt�rym by� po przesuni�ciu

		-! przelicza� �rodek grupy po dodaniu ka�dego obiektu
		  (wsp�rz�dne w przestrzeni �wiata! a �rodek w przestrzeni "grupy" tj. grupie modeli)
		-!! doda� transformacje grup (translacja, obr�t itp.)
		-!!!! naprawi� kumulowane transformacje �eby jedna z kul mog�a si� obraca� i wok� w�asnej osi i wok� drugiej kuli
		- poprawi� distance shading -> maksymalna odleg�o�� od obiektu
		- poprawi� material manager -> definiowanie zmiennych kt�re b�dzie mo�na przekaza� do shadera ju� w aplikacji
		  "roboczej" (tu example.cpp)
		-!!!!! tekstury!
		-!!!!! texture manager na uchwytach (materia�y te�)

		
		-!!!! sze�cian (cube)			(done)
		-!!!! �adowanie modelu z pliku	(done, pozostaje .3ds, .blend i w�asny format)
	*/

	ObjectManager->add(g);
	ObjectManager->addLight(light);
	ObjectManager->addLight(light2);
	ObjectManager->addLight(light3);
	ObjectManager->addLight(light4);

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
	
	renderer->setRenderMode(SW_SOLID);
	double lastTime = glfwGetTime();
	bool clicked = false, enter = false;

	glm::vec3 light_pos = glm::vec3(-3.0f,1.0f,-2.5f);

	//light2->move(glm::vec3(1.0f,1.5f,-1.9f));

	double angle2 = 0;
	do {
		//light->_move(glm::vec3(4.5f*cos(angle),1.5f,4.5f*sin(angle)));

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
		if(glfwGetKey(GLFW_KEY_SPACE) == GLFW_PRESS && !clicked) {
			renderer->setRenderMode(1 - renderer->getRenderMode());
			clicked = true;
		} else if (glfwGetKey(GLFW_KEY_SPACE) == GLFW_RELEASE) 
			clicked = false;
		if(glfwGetKey(GLFW_KEY_ENTER) == GLFW_PRESS && !enter) {
			if(tank->isVisible()) tank->hide();
			else tank->show();
			if(lara->isVisible()) lara->hide();
			else lara->show();
			enter = true;
		} else if (glfwGetKey(GLFW_KEY_ENTER) == GLFW_RELEASE)
			enter = false;

		cam->move(position, direction, up);
		// obr�t pierwszej kuli
		//glm::vec3 pos = s1->getPosition();
		//s1->move(pos);
		//s1->rotate(glm::vec3(1,0,0), angle);
		//s1->move(-pos);
		//p1->rotate(glm::vec3(0,1,0), 0.5*angle);

		// s2->rotate(glm::vec3(0,1,0), 2*angle);
		//light1->rotate(glm::vec3(0,1,0), angle);
		
		//glm::vec3(-3.0f,1.0f,-2.5f)
		angle2 += 0.01f;
		light->move(light_pos + glm::vec3(0,0,2*sin(angle2)));
		light2->rotate(glm::vec3(0,1,0), angle);
		light3->rotate(glm::vec3(0,1,0), -2 * angle);
		light4->rotate(glm::vec3(0,1,0), -angle);
		renderer->render();
		window->swapBuffers();
	} while (glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS && window->isOpen());

	delete g;
	//delete s1;
	//delete s2;
	delete renderer;
	delete cam;

	delete window;
	// automatycznie zwalnia� wszystkie wska�niki przez delete
	return 0;
}