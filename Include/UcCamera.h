#ifndef _UC_CAMERA_H_
#define _UC_CAMERA_H_
//
#include <gl/glew.h>
#include "UcVector3.h"
#include "UcMatrix.h"
#include "UcTransform.h"
#include "UcEventNode.h"
#include "UcEvent.h"

namespace Unicorn
{
	class RenderMgr;
	class EventDispatcher;

	enum CameraType
	{

		FREELOOK,		    //normal camera
		ORTHOGONAL,			//45¡ãview point, like most MOBA
		HUD					//better to use when with GUI
	};

	class Camera : public Listener
	{
	public:
		//enumrator
		enum Camera_Forward {
			FORWARD,
			BACKWARD,
			LEFT,
			RIGHT
		};

		//default parameters
		static const float YAW;
		static const float PITCH; 
		static const float SPEED;
		static const float SENSITIVITY;
		static const float ZOOM;
		//
		static bool CAM_DIR[4];

	public:
		Camera(const Vector3& position = Vector3(0.0f, 0.0f ,5.0f),
			   const Vector3& upward = Vector3(0.0f, 1.0f, 0.0f), 
			   const float& yaw = YAW,
			   const float& pitch = PITCH); 

		virtual ~Camera();
		//
		bool initialize(const Vector3& pos, const CameraType& type);
		//
		void setPosition(const Vector3& pos);
		Vector3 getPosition();
		//
		Matrix4x4 getViewMatrix();
		Matrix4x4 getProjectionMatrix();
		Matrix4x4 getOrthoMatrix(float bottomSrc, float bottomDst, float heightSrc, float heightDst);

		void setSensitivity(const float& sens);
		GEN_FUNC(float, _nearPlane, NearPlane);
		GEN_FUNC(float, _farPlane, FarPlane);
		GEN_FUNC(bool, _isLock, Locker);


		//Methods of listener
		virtual void onKeyPress(int keyCode, int scanCode, int mode);
		virtual void onKeyRelease(int keyCode, int scanCode, int mode);
		virtual void onMouseMove(double x, double y);
		virtual void onScroll(double offX, double offY);
		virtual void update(float dt);
		virtual void destroy();

		Vector3 getRightVector() const;
		Vector3 getFrontVector() const;
		Vector3 getUpVector() const;

		inline float getDeltaTime() const{
			return _deltaTime;
		}


	protected:
		//
		void _update();
		//
		Matrix4x4 _lookAt(Vector3 eye, Vector3 center, Vector3 up);
		//
		void _keyboardCallback(const Camera_Forward& forward,const float& dt);
		void _mouseCallback(float offX, float offY, bool lockPitch = true);
		void _scrollCallback(const double& offY);

	protected:
		//type
		CameraType _camType;
		//
		bool _isLock;
		//
		float _deltaTime;
		//attr
		Vector3 _position;
		Vector3 _front;
		Vector3 _upward;
		Vector3 _right;
		Vector3 _worldUpward;
		//
		float _nearPlane;
		float _farPlane;
		//
		float _lastX, _lastY;
		//
		float _yaw;
		float _pitch;
		//
		float _moveSpeed;
		float _sensitivity;
		float _zoomFactor;
		//
		bool _isMoved;
		bool _isInteractable;
	};
}

#endif