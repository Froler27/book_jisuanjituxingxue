#pragma once

#include "F7/Vec/Vec.h"
#include "F7/Matrix/Mat.h"
#include "F7/Common/Log.hpp"

//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>

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
		
	void getNDCCoord(F7::Vec2& sceenCoord) {
		sceenCoord.x() = (sceenCoord.x() / _width - 0.5);
		sceenCoord.y() = (0.5 - sceenCoord.y() / _height);
	}
	void getNDCCoord(F7::Vec3& sceenCoord) {
		sceenCoord.x() = (sceenCoord.x() / _width - 0.5);
		sceenCoord.y() = (0.5 - sceenCoord.y() / _height);
		sceenCoord.z() = F7::Math::clamp(sceenCoord.z() * 2 - 1, F7::Vec3::value_type(-1), F7::Vec3::value_type(1));
	}
	void getScreenCoordFromNDC(F7::Vec3& NDCCoord) { 
		NDCCoord.x() = (NDCCoord.x() + 1) * 0.5 * _width;
		NDCCoord.y() = (1 - NDCCoord.y()) * 0.5 * _height;
		NDCCoord.z() = (NDCCoord.z() + 1) * 0.5;
	}
	void setPos(F7::Vec3 pos) { _pos = pos; }
	void setPos(float x, float y, float z) { _pos.x() = x; _pos.y() = y; _pos.z() = z; }
	void addMouseMoveSpeed(float x) { _moveSpeed += x; }

	inline F7::Mat4 getViewMatrix() { return F7::Mat4::LookAt(_pos, _pos + _front, _up); }
	inline F7::Mat4 getProjMatrix() { return F7::Mat4::Perspective(F7::Math::Degree2Radian(_zoom), _aspect, 1.0f, 100.f); }
	inline F7::Mat4 getViewInverseMatrix() { F7::Mat4 res = getViewMatrix(); res.invert(); return res; }
	inline F7::Mat4 getProjInverseMatrix() { F7::Mat4 res = getProjMatrix(); res.invert(); return res; }

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
	int _width;
	int _height;

	float _aspect{ 1 };

	float _yaw;
	float _pitch;

	float _moveSpeed;
	float _mouseSensitivity;
	float _zoom;
};