#pragma once

#include "F7/Vec/Vec.h"
#include "F7/Matrix/Mat.h"
#include "Log.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

const float YAW = 0.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
	Camera(F7::Vec3 pos = F7::Vec3(), F7::Vec3 up = F7::Vec3(0.f, 0.f, 1.f), float yaw = YAW, float pitch = PITCH);
		
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
		

	void setPos(F7::Vec3 pos) { _pos = pos; }
	void setPos(float x, float y, float z) { _pos.x() = x; _pos.y() = y; _pos.z() = z; }
	void addMouseMoveSpeed(float x) { _moveSpeed += x; }

	inline F7::Mat4 getViewMatrix() { return F7::Mat4::LookAt(_pos, _pos + _front, _up); }
	inline F7::Mat4 getProjMatrix() { return F7::Mat4::Perspective(F7::Math::Degree2Radian(_zoom), _aspect, 0.1f, 1000.f); }

	void processKeyboard(Camera_Movement direction, float deltaTime);

	void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
	void processMouseScroll(float yoffset)
	{
		_zoom -= (float)yoffset;
		if (_zoom < 1.0f)
			_zoom = 1.0f;
		if (_zoom > 80.0f)
			_zoom = 80.0f;
	}
private:
	void updateCameraVectors();

public:
	F7::Vec3 _pos;
	F7::Vec3 _front{ 0,1,0 };
	F7::Vec3 _up;
	F7::Vec3 _right;
	F7::Vec3 _wordUp;

	float _aspect{ 1 };

	float _yaw;
	float _pitch;

	float _moveSpeed;
	float _mouseSensitivity;
	float _zoom;
};