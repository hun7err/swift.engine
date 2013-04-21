#include "../include/Renderer.h"
//#include <glm/gtc/type_ptr.hpp>

/*
	to-do:
		naprawiæ to randomowe access violation przy rysowaniu :f
*/

#include <cassert>
#include <cstdio>

namespace Swift {
	void Renderer::render() {
		//glm::mat4 MVP = glm::mat4(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*
			to-read:
				RPG -> wyk³ad o w³asnym mened¿erze pamiêci
		*/
		std::vector<Group*>::iterator it = ObjectManager->getGroups()->begin(), end = ObjectManager->getGroups()->end();
		for(; it != end; ++it) {
			//printf("Group name: %s\n", (*it)->getName().c_str());
			std::vector<Object*>::iterator j = (*it)->getObjects()->begin(), end = (*it)->getObjects()->end();

			for(; j != end; ++j) {
				Object* object = *j;
				if(object->isVisible()) {
				//printf("Vertices[n-1] = vertices[%d] = %f\n", object->getVertexCount()-1, object->getVertices()[object->getVertexCount()-1]);
				//printf("Object name: %s\n", object->getName().c_str());

				//printf("MVP slot, shader ID: %d\n", object->getMaterial()->getShaderID());
				
				//GLuint MVPslot = glGetUniformLocation(object->getMaterial()->getShaderID(), "MVP"); // <- tu siê coœ sypie (wtf)
				GLuint ModelSlot = glGetUniformLocation(object->getMaterial()->getShaderID(), "Model");
				GLuint ViewSlot = glGetUniformLocation(object->getMaterial()->getShaderID(), "View");
				GLuint PerspSlot = glGetUniformLocation(object->getMaterial()->getShaderID(), "Perspective");
				
				//printf("using shader...\n");
				glUseProgram(object->getMaterial()->getShaderID());
				//printf("MVP\n");
				//glm::mat4 MVP = (cam->getVP()) * (object->getModelMatrix());
				
				//printf("MVP address: %x\n", &MVP[0][0]);
				//GLuint MVPslot = 0;
				//printf("MVP slot: %d\n", MVPslot);
				
				//glUniformMatrix4fv(MVPslot, 1, GL_FALSE, &MVP[0][0]);
				glUniformMatrix4fv(ModelSlot, 1, GL_FALSE, &(object->getModelMatrix())[0][0]);
				glUniformMatrix4fv(ViewSlot, 1, GL_FALSE, &(cam->getView())[0][0]);
				glUniformMatrix4fv(PerspSlot, 1, GL_FALSE, &(cam->getProjection())[0][0]);
				
				GLuint cameraSlot = glGetUniformLocation(object->getMaterial()->getShaderID(), "cameraPos");
				glUniform3f(cameraSlot, cam->getPosition().x, cam->getPosition().y, cam->getPosition().z);
				//printf("Vertex Array Object\n");
				glEnableVertexAttribArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, object->getVBO());
				glVertexAttribPointer(
					0,
					3,
					GL_FLOAT,
					GL_FALSE,
					0,
					(void*)0
				);
				//printf("Vertices: \n");
				//for(int i = 0; i < object->getVertexCount()-3; i++)
				//	printf("%f %f %f\n", object->getVertices()[i], object->getVertices()[i+1], object->getVertices()[i+2]);
				glDrawArrays(GL_TRIANGLES, 0, object->getVertexCount());
				glDisableVertexAttribArray(0);
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