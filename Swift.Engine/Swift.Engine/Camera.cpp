#include "Camera.h"
#include <glm/ext.hpp>

namespace Swift {
	////// STANDARD METHODS
	void Camera::refresh() {
		Projection = glm::perspective(fov, aspect, nearClipping, farClipping);
		View = glm::lookAt(
			pos,
			target,
			up
		);
	}

	////// SETTERS
	void Camera::setFoV(const float &_fov) {
		fov = _fov;
	}
	void Camera::setAspect(const float &_aspect) {
		aspect = _aspect;
	}
	void Camera::setNearClip(const float &_nearClip) {
		nearClipping = _nearClip;
	}
	void Camera::setFarClip(const float &_farClip) {
		farClipping = _farClip;
	}
	void Camera::setViewParams(glm::vec3 _pos, glm::vec3 _target, glm::vec3 _up){
		pos = _pos;
		target = _target;
		up = _up;

		View = glm::lookAt(pos, target, up);
	}
	void Camera::setProjectionParams(const float &_fov, const float &_aspect, const float &_nearClip, const float &_farClip){
		fov = _fov;
		aspect = _aspect;
		nearClipping = _nearClip;
		farClipping = _farClip;

		Projection = glm::perspective(fov, aspect, nearClipping, farClipping);
	}
	void Camera::setViewMatrix(const glm::mat4 &_View){
		View = _View;
	}
	void Camera::setProjectionMatrix(const glm::mat4 &_Projection){
		Projection = _Projection;
	}

	////// GETTERS
	glm::mat4 Camera::getVP() {
		return Projection * View;
	}
	
	glm::mat4 Camera::getView(){
		return View;
	}
	
	glm::mat4 Camera::getProjection(){
		return Projection;
	}

	float Camera::getFoV(){
		return fov;
	}

	float Camera::getAspect(){
		return aspect;
	}
	
	float Camera::getNearClip(){
		return nearClipping;
	}
	
	float Camera::getFarClip(){
		return farClipping;
	}
	
	glm::vec3 Camera::getPosition(){
		return pos;
	}
	
	glm::vec3 Camera::getTarget(){
		return target;
	}
	
	glm::vec3 Camera::getUpVector(){
		return up;
	}

	////// CONSTRUCTORS AND DESTRUCTORS
	Camera::Camera() {
		View = glm::mat4(1.0);
		Projection = glm::mat4(1.0);
	}

	Camera::Camera(	glm::vec3 _pos, glm::vec3 _target, glm::vec3 _up,
					const float &_fov, const float &_aspect, const float &_nearClip, const float &_farClip)
	{
		pos = _pos;
		target = _target;
		up = _up;
		fov = _fov;
		aspect = _aspect;
		nearClipping = _nearClip;
		farClipping = _farClip;

		Projection = glm::perspective(fov, aspect, nearClipping, farClipping);
		View = glm::lookAt(
			pos,
			target,
			up
		);
	}
	Camera::~Camera() {}
}