#ifndef CAMERA_H
#define CAMERA_H

/**
 * @file Camera.h
 * Basic camera class: enough for simple usage
 * @author Krzysztof 'hun7er' Marciniak
 */

#include <glm/glm.hpp>

namespace Swift {
	class Camera {
		private:
			float fov;	/** Field Of View - the angle between left side and riht side */
			float aspect;	/** Aspect Ratio - window width/height */
			float nearClipping;	/**	Distance after which (going to 0) the object should be marked as being too close to be rendered */
			float farClipping;	/** Distance after which (going to infinity) the object should be treated as being too far to be rendered */
			glm::vec3 pos;	/** Camera position */
			glm::vec3 target;	/** The place (point) we are looking at */
			glm::vec3 up;	/** The "up" (or "nose") vector - defines rotation of the camera on all axes */

			glm::mat4 View;	/** View matrix - determined by Camera options (fov, aspect, nearClipping, farClipping) transforms World coordinates to the Eye space */
			glm::mat4 Projection;	/** Projection matrix - deforms the object to create perspective  */
		public:
			void refresh();	/** Refresh matrices after parameter change */
			/*
				to-add:
					- pitch/yaw/roll
					- move
			*/

			void setFoV(const float &_fov);	/** Set FOV value */
			void setAspect(const float &_aspect);	/** Set the screen aspect ratio */
			void setNearClip(const float &_nearClip);	/** Set Near Clipping value */
			void setFarClip(const float &_farClip);	/** Set Far Clipping value */
			void setViewParams(glm::vec3 _pos, glm::vec3 _target, glm::vec3 _up);
			void setProjectionParams(const float &_fov, const float &_aspect, const float &_nearClip, const float &_farClip);
			void setViewMatrix(const glm::mat4 &_View);
			void setProjectionMatrix(const glm::mat4 &_Projection);

			glm::mat4 getVP();	/** Get View*Projection matrix */
			glm::mat4 getView();	/** Get View matrix */
			glm::mat4 getProjection();	/** Get Projection Matrix */
			float getFoV();	/** Get Field of View value */
			float getAspect();
			float getNearClip();
			float getFarClip();
			glm::vec3 getPosition();
			glm::vec3 getTarget();
			glm::vec3 getUpVector();
		Camera();	/** Basic constructor - sets View and Perspective to identity matrices; use ONLY when you intend to change the paramters later and refresh matrices manually by using Camera::refresh() */
		Camera(glm::vec3 _pos,
			glm::vec3 _target,
			glm::vec3 _up,
			const float &_fov,
			const float &_aspect,
			const float &_nearClip,
			const float &_farClip
		);	/**  */
		virtual ~Camera();
	};
};

#endif // CAMERA_H