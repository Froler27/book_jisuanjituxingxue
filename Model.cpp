#include "Model.hpp"
#include <string>
#include <sstream>
#include <fstream>

#include "Dependencies/stb_image.h"
#include "Log.hpp"

bool Model::loadModelFile(const char* modelPath)
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
    return true;
}

bool Model::loadTexture(const char* texturePath, const char* uniformName, GLint level)
{
	GLuint textureID;
	glBindVertexArray(_vao);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	_textureMap.insert(std::make_pair(level, textureID));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
	if (data)
	{
		if (nrChannels<4)
			glTexImage2D(GL_TEXTURE_2D, level, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else
			glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		Log() << "Failed to load texture" << Log::ENDL;
		return false;
	}
	stbi_image_free(data);
	_spShader->use();
	_spShader->setInt(uniformName, level);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}

bool Model::configData()
{
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	glBufferData(GL_ARRAY_BUFFER, _verts.size() * sizeof(float), &_verts[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return true;
}

void Model::useTexture()
{
	for (auto e : _textureMap) {
		glActiveTexture(GL_TEXTURE0 + e.first);
		glBindTexture(GL_TEXTURE_2D, e.second);
	}
}

F7::Mat4 Model::getWorldMatrix()
{
	F7::Mat4 res{ 1 };
	res *= F7::Mat4::Translate(_pos);
	res *= F7::Mat4::Rotate(_rot);
	res *= F7::Mat4::Scale(_sca);
	return res;
}
