#pragma once

#include <GL/glew.h>
#include <vector>
#include "F7/F7.hpp"

class Model
{
public:
	Model() {
		glGenVertexArrays(1, &_vao);
		glGenBuffers(1, &_vbo);
	}
	~Model() {}

	bool load(const char* modelPath);

	F7::Mat4 getWorldMatrix();
	GLuint getVAO() { return _vao; }
	int getVertsNum() { return _verts.size(); }

	F7::Vec3& position() { return _pos; }
	F7::Vec3& rotate() { return _rot; }
	F7::Vec3& scale() { return _sca; }
	GLuint& renderingProgramID() { return _renderingProgramID; }

private:
	std::vector<float> _verts;
	F7::Vec3 _pos{ 0 };
	F7::Vec3 _rot{ 0 };
	F7::Vec3 _sca{ 1 };
	GLuint _renderingProgramID{ 0 };
	GLuint _vao{ 0 };
	GLuint _vbo{ 0 };
};

