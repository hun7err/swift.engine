#include "../include/Renderer.h"
#include "../include/Sphere.h"
#include "../include/MaterialManager.h"
//#include <glm/gtc/type_ptr.hpp>

/*
	to-do:
		ogarn¹æ ten burdel.
*/

#include <sstream>
#include <string>
#include <cassert>
#include <cstdio>

namespace Swift {
	void Renderer::render() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		std::vector<Light*> lights = *(ObjectManager->getLights());

		/*
			to-read:
				RPG -> wyk³ad o w³asnym mened¿erze pamiêci
		*/
		std::vector<Group*>::iterator it = ObjectManager->getGroups()->begin(), end = ObjectManager->getGroups()->end();
		for(; it != end; ++it) { // dla ka¿dej grupy z ObjectManager
			std::vector<Object*>::iterator j = (*it)->getObjects()->begin(), end = (*it)->getObjects()->end();

			for(; j != end; ++j) { // dla ka¿dego obiektu

				Object* object = *j; // dla u³atwienia
				for(int i = 0; i < object->getPartCount(); i++) { // dla ka¿dej czêœci obiektu
					printf("part count: %d\n", object->getPartCount());
					if(object->getPartAt(i).isVisible()) { // renderujê tylko widoczne czêœci
						//printf("key: %d\n", object->getPartAt(i).getMaterial().key);
						Material mtl = MaterialManager->getMaterial(object->getPartAt(i).getMaterial().key); // z MaterialManager pobieramy materia³ o kluczu
						
						//printf("i = %d, Diffuse: %f %f %f, program ID: %d\n", i, mtl.DiffuseColor.r, mtl.DiffuseColor.g, mtl.DiffuseColor.b, mtl.getProgramID());
						GLuint programID = mtl.getProgramID(); // pobieram ID programu (z³o¿onego z shaderów) dla renderowanej czêœci
						
						glUseProgram(programID);

						// tu pobieram sloty pod którymi po³o¿one s¹ konkretne zmienne jednorodne:
						// macierze: odpowiednio modelu, widoku i rzutu perspektywicznego
						GLuint ModelSlot = glGetUniformLocation(programID, "Model");
						GLuint ViewSlot = glGetUniformLocation(programID, "View");
						GLuint PerspSlot = glGetUniformLocation(programID, "Perspective");
						// kolory: dla œwiat³a rozproszonego, otoczenia, odbiæ/po³yskiwania oraz wyk³adnik Phonga i iloœæ œwiate³
						GLuint DiffuseColor = glGetUniformLocation(programID, "DiffuseColor");
						GLuint AmbientColor = glGetUniformLocation(programID, "AmbientColor");
						GLuint SpecularColor = glGetUniformLocation(programID, "SpecularColor");
						GLuint PhongExponent = glGetUniformLocation(programID, "PhongExponent");
						GLuint LightCount = glGetUniformLocation(programID, "LightCount");
				
						glUniformMatrix4fv(ModelSlot, 1, GL_FALSE, &(object->getPartAt(i).getModelMatrix())[0][0]);
						glUniformMatrix4fv(ViewSlot, 1, GL_FALSE, &(cam->getView())[0][0]);
						glUniformMatrix4fv(PerspSlot, 1, GL_FALSE, &(cam->getProjection())[0][0]);
				
						GLuint cameraSlot = glGetUniformLocation(programID, "cameraPos");
						glUniform3f(cameraSlot, cam->getPosition().x, cam->getPosition().y, cam->getPosition().z);

						// przekazujê wartoœci pod odpowiednie sloty
						glUniform3fv(DiffuseColor, 1, &mtl.DiffuseColor.r);
						glUniform3fv(AmbientColor, 1, &mtl.AmbientColor.r);
						glUniform3fv(SpecularColor, 1, &mtl.SpecularColor.r);
						glUniform1i(PhongExponent, mtl.PhongExponent);
						glUniform1i(LightCount, lights.size());

						// dla ka¿dego œwiat³a...
						for(int l = 0; l < lights.size(); l++) {
							std::string t = "Lights[";
							std::stringstream ss;
							ss << t;
							ss << l;
							ss << "]";
							t = ss.str();
							std::string temp = t+".pos";
							GLuint loc = glGetUniformLocation(programID, temp.c_str());
							// ...przekazujê pozycjê, ...
							glUniform3fv(loc, 1, &(lights[l]->getStructPtr()->pos.x));
							temp = t+".color";
							loc = glGetUniformLocation(programID, temp.c_str());
							// ...kolor, ...
							glUniform3fv(loc, 1, &(lights[l]->getStructPtr()->color.r));
							temp = t+".intensity";
							// ..."moc" œwiat³a...
							loc = glGetUniformLocation(programID, temp.c_str());
							glUniform1f(loc, lights[l]->getStructPtr()->intensity);
							temp = t+".model";
							loc = glGetUniformLocation(programID, temp.c_str());
							// ...i macierz modelu
							glUniformMatrix4fv(loc, 1, GL_FALSE, &(lights[l]->getStructPtr()->model[0][0]));
							ss.clear();
							t.clear();
						}
				
						// u¿ywam programu dla aktualnie renderowanej czêœci

						glEnableVertexAttribArray(0);

						glBindBuffer(GL_ARRAY_BUFFER, object->getPartAt(i).getVBO());
						glVertexAttribPointer(
							0,
							3,
							GL_FLOAT,
							GL_FALSE,
							0,
							(void*)0
						);

						glEnableVertexAttribArray(1);

						glBindBuffer(GL_ARRAY_BUFFER, object->getPartAt(i).getNormalBuffer());
						glVertexAttribPointer(
							1,
							3,
							GL_FLOAT,
							GL_FALSE,
							0,
							(void*)0
						);

						glDrawArrays(GL_TRIANGLES, 0, object->getPartAt(i).getVertexCount());

						glDisableVertexAttribArray(0);
						glDisableVertexAttribArray(1);
					}
				}
			}
		}
		
	}

	void Renderer::setRenderMode(unsigned int mode) {
		// to-add: edged polygons (solid+wireframe)
		switch(mode) {
			case SW_WIREFRAME:
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
			case SW_SOLID:
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		}
		renderMode = mode;
	}

	int Renderer::getRenderMode() {
		return renderMode;
	}

	void Renderer::setCamera(Camera* c) {
		cam = c;
	}

	void Renderer::clearColor(double r, double g, double b, double a) {
		glClearColor(r, g, b, a);
	}

	/*Renderer::Renderer(ObjectManager* obj) {
		objManager = obj;
	}*/
	Renderer::Renderer() {
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
	}
	Renderer::~Renderer() {}
}