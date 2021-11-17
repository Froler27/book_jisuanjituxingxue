#include "Model.hpp"
#include <string>
#include <sstream>
#include <fstream>

#include "Log.hpp"

bool Model::load(const char* modelPath)
{
	try
	{
		_verts.clear();
		std::ifstream vertsFile;
		vertsFile.open(modelPath);

		std::stringstream vertsStream;
		vertsStream << vertsFile.rdbuf();
		vertsFile.close();
		float tem;
		while (vertsStream >> tem) {
			_verts.push_back(tem);
		}
	}
	catch (std::ifstream::failure)
	{
		Log() << "Error: can't open file " << modelPath << Log::ENDL;
		return false;
	}
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	glBufferData(GL_ARRAY_BUFFER, _verts.size() * sizeof(float), &_verts[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    return true;
}

F7::Mat4 Model::getWorldMatrix()
{
	F7::Mat4 res{ 1 };
	res *= F7::Mat4::Translate(_pos);
	res *= F7::Mat4::Rotate(_rot);
	res *= F7::Mat4::Scale(_sca);
	return res;
}
