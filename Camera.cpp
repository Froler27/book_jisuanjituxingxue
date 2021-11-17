#include "Camera.hpp"

Camera::Camera(F7::Vec3 pos /*= F7::Vec3()*/, F7::Vec3 up /*= F7::Vec3(0.f, 1.f, 0.f)*/, float yaw /*= YAW*/, float pitch /*= PITCH*/)
	: _pos(pos), _front(0, 0, -1), _wordUp(up), _yaw(yaw), _pitch(pitch),
	_moveSpeed(SPEED), _mouseSensitivity(SENSITIVITY), _zoom(ZOOM)
{
	updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
	: _front(0.0f, 0.0f, -1.0f), _moveSpeed(SPEED), _mouseSensitivity(SENSITIVITY), _zoom(ZOOM)
{
	_pos.set(posX, posY, posZ);
	_wordUp.set(upX, upY, upZ);

	updateCameraVectors();
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = _moveSpeed * deltaTime;
	if (direction == Camera_Movement::FORWARD)
		_pos += _front * velocity;
	if (direction == Camera_Movement::BACKWARD)
		_pos -= _front * velocity;
	if (direction == Camera_Movement::LEFT)
		_pos -= _right * velocity;
	if (direction == Camera_Movement::RIGHT)
		_pos += _right * velocity;
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch /*= true*/)
{
	xoffset *= _mouseSensitivity;
	yoffset *= _mouseSensitivity;

	_yaw += xoffset;
	_pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (_pitch > 89.0f)
			_pitch = 89.0f;
		if (_pitch < -89.0f)
			_pitch = -89.0f;
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}

void Camera::updateCameraVectors()
{
	// calculate the new Front vector
	F7::Vec3 front;
	front.x() = cos(F7::Math::Degree2Radian(_yaw)) * cos(F7::Math::Degree2Radian(_pitch));
	front.y() = sin(F7::Math::Degree2Radian(_pitch));
	front.z() = sin(F7::Math::Degree2Radian(_yaw)) * cos(F7::Math::Degree2Radian(_pitch));

	_front = front.normalize();
	// also re-calculate the Right and Up vector

	_right = (_front ^ _wordUp).normalize();  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	_up = (_right ^ _front).normalize();
}
