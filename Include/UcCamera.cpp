#include "UcCamera.h"
#include "UcGame.h"
#include "UcEventDispatcher.h"
#include "UcRenderMgr.h"
NS_UNICORN;

const float Camera::YAW = -90.0f;
const float Camera::PITCH = 0.0f;
const float Camera::SPEED = 2.0f;
const float Camera::SENSITIVITY = 0.2f;
const float Camera::ZOOM = 45.0f;

bool Camera::CAM_DIR[4] = { false, false, false, false };

Camera::Camera(
const Vector3& position /*= Vector3(0.0f,0.0f,5.0f)*/, 
const Vector3& upward /*= Vector3(0.0f, 1.0f, 0.0f)*/, 
const float& yaw /*= YAW*/, 
const float& pitch /*= PITCH*/):
_front(Vector3(0.0f, 0.0f, -1.0f)),
_moveSpeed(SPEED),
_sensitivity(SENSITIVITY),
_zoomFactor(ZOOM),
_deltaTime(0),
_nearPlane(1.0f),
_farPlane(7.5f),
_isLock(false)
{
	this->_position = position;
	this->_worldUpward = upward;
	this->_yaw = yaw;
	this->_pitch = pitch;

	this->_isMoved = false;
	this->_isInteractable = true;

	this->_lastX = Game::getInstance()->getWidth()/2;
	this->_lastY = Game::getInstance()->getHeight()/2;

	this->_update();
}

Camera::~Camera()
{
}

bool Camera::initialize(const Vector3& pos, const CameraType& type)
{
	//add listener
	EventDispatcher::getInstance()->addListener(this);
	//
	this->_position = pos;
	this->_camType = type;
	//
	//this->initialzeWithType(type);


	return true;
}

void Camera::destroy()
{
	EventDispatcher::getInstance()->removeListener(this);

	delete this;
}


void Camera::_update()
{
	// Calculate the new Front vector
	Vector3 front;
	front.x = cos(RADIANS(this->_yaw)) * cos(RADIANS(this->_pitch));
	front.y = sin(RADIANS(this->_pitch));
	front.z = sin(RADIANS(this->_yaw)) * cos(RADIANS(this->_pitch));
	this->_front = front.normalize();
	
	this->_right = Vector3::cross(this->_front, this->_worldUpward).normalize();
	this->_upward = Vector3::cross(this->_right, this->_front).normalize();
}

Matrix4x4 Camera::getViewMatrix()
{
	return _lookAt(this->_position, this->_position + this->_front, this->_upward);
}

Matrix4x4 Camera::getProjectionMatrix()
{
	float ratio = Game::getInstance()->getWidthHeightRatio();
	return perspective(this->_zoomFactor,ratio, 0.1f, 100.0f);
}

Matrix4x4 Camera::getOrthoMatrix(float bottomSrc, float bottomDst, float heightSrc, float heightDst)
{
	return ortho(bottomSrc, bottomDst, heightSrc, heightDst, _nearPlane, _farPlane);
}

void Camera::_keyboardCallback(const Camera_Forward& dir, const float& dt)
{
	GLfloat velocity = this->_moveSpeed * dt;
	if (dir == FORWARD)
		this->_position = this->_position + this->_front * velocity;
	if (dir == BACKWARD)
		this->_position = this->_position - this->_front * velocity;
	if (dir == LEFT)
		this->_position = this->_position - this->_right * velocity;
	if (dir == RIGHT)
		this->_position = this->_position + this->_right * velocity;
}

void Camera::_mouseCallback(float offX, float offY, const bool lockPitch /*= true*/)
{
	offX *= this->_sensitivity;
	offY *= this->_sensitivity;

	this->_yaw += offX;
	this->_pitch += offY;

	if (lockPitch)
	{
		if (this->_pitch > 89.0f)
			this->_pitch = 89.0f;
		if (this->_pitch < -89.0f)
			this->_pitch = -89.0f;
	}
	this->_update();
}

void Camera::_scrollCallback(const double& offY)
{
	float minus = glm::radians(1.0f);
	float maxium = glm::radians(45.0f);
	if (this->_zoomFactor >= minus && this->_zoomFactor <= maxium)
		this->_zoomFactor -= glm::radians(offY);
	if (this->_zoomFactor <= minus)
		this->_zoomFactor = minus;
	if (this->_zoomFactor >= maxium)
		this->_zoomFactor = maxium;
}

Matrix4x4 Camera::_lookAt(Vector3 eye, Vector3 center, Vector3 up)
{
	return glm::lookAt(vec3(eye.x, eye.y, eye.z),
				       vec3(center.x, center.y, center.z),
					   vec3(up.x, up.y, up.z));
}

void Camera::onKeyPress(int keyCode, int scanCode, int mode)
{
	if (_isLock)
		return;

	switch (keyCode)
	{
	case KEY_W:
		CAM_DIR[FORWARD] = true;
		break;
	case KEY_S:
		CAM_DIR[BACKWARD] = true;
		break;
	case KEY_A:
		CAM_DIR[LEFT] = true;
		break;
	case KEY_D:
		CAM_DIR[RIGHT] = true;
		break;
	default:
		break;
	}
}

void Camera::onKeyRelease(int keyCode, int scanCode, int mode)
{
	if (_isLock)
		return;

	switch (keyCode)
	{
	case KEY_W:
		CAM_DIR[FORWARD] = false;
		break;
	case KEY_S:
		CAM_DIR[BACKWARD] = false;
		break;
	case KEY_A:
		CAM_DIR[LEFT] = false;
		break;
	case KEY_D:
		CAM_DIR[RIGHT] = false;
		break;
	default:
		break;
	}
}

void Camera::onMouseMove(double x, double y)
{
	if (_isLock)
		return;

	if (!_isMoved)
	{
		_lastX = x;
		_lastY = y;
		_isMoved = true;
	}

	float xoffset = x - _lastX;
	float yoffset = _lastY - y;

	_lastX = x;
	_lastY = y;

	this->_mouseCallback(xoffset, yoffset);
}

void Camera::onScroll(double offX, double offY)
{
	if (_isLock)
		return;

	this->_scrollCallback(offY); 
}

void Camera::setPosition(const Vector3& pos)
{
	//when update vector it will change view matrix itself
	this->_position = pos;	
}

Vector3 Camera::getPosition()
{
	return 	this->_position;
}

void Camera::setSensitivity(const float& sens)
{
	this->_sensitivity = sens;
}

void Camera::update(float dt)
{
	if (_isLock)
		return;

	_deltaTime = dt;
	if (CAM_DIR[FORWARD])
		this->_keyboardCallback(FORWARD, dt);
	if (CAM_DIR[BACKWARD])
		this->_keyboardCallback(BACKWARD, dt);
	if (CAM_DIR[LEFT])
		this->_keyboardCallback(LEFT, dt);
	if (CAM_DIR[RIGHT])
		this->_keyboardCallback(RIGHT, dt);
}

Vector3 Camera::getRightVector() const
{
	return _right;
}

Vector3 Camera::getFrontVector() const
{
	return _front;
}

Vector3 Camera::getUpVector() const
{
	return _upward;
}



