#pragma once

#include <GL/glew.h>
#include <vector>
#include <map>
#include <memory>
#include "F7/F7.hpp"
#include "ShaderProgram.hpp"


class Model
{
public:
	enum class EDataType
	{
		Vertex = 1,
		Color = 2,
		Normal = 4,
		TexCoord = 8
	};
	enum class EBindingType
	{
		Off = 0,
		Overall,
		Per_Vertex
	};
public:
	Model() {
		glGenVertexArrays(1, &_vao);
		glGenBuffers(1, &_vbo);
		//glGenBuffers(1, &_ebo);
	}
	~Model() {}

	bool loadModelFile(const char* modelPath);
	bool loadTexture(const char* texturePath, const char* uniformName, GLint level = 0);
	bool configData();

	void useTexture();

	void setShaderProgram(ShaderProgram* pShader) { _spShader = std::shared_ptr<ShaderProgram>(pShader); }
	void setShaderProgram(std::shared_ptr<ShaderProgram>& spShader) { _spShader = spShader; }
	std::shared_ptr<ShaderProgram>& getShaderProgram() { return _spShader; }

	F7::Mat4 getWorldMatrix();
	GLuint getVAO() { return _vao; }
	int getVertsNum() { return _verts.size(); }

	std::vector<float>& getData() { return _verts; }
	const std::vector<float>& getData() const { return _verts; }

	F7::Vec3& position() { return _pos; }
	F7::Vec3& rotate() { return _rot; }
	F7::Vec3& scale() { return _sca; }

protected:
	GLuint _vao{ 0 };
	GLuint _vbo{ 0 };
	GLuint _ebo{ 0 };
	std::shared_ptr<ShaderProgram> _spShader;

	bool _bUseEBO{ false };
	std::map<GLint, GLuint> _textureMap;

	EBindingType _colorBinding{ EBindingType::Off };
	EBindingType _normalBinding{ EBindingType::Off };

	F7::Vec3 _pos{ 0 };
	F7::Vec3 _rot{ 0 };
	F7::Vec3 _sca{ 1 };

	std::vector<float> _verts;
	
};

class Sphere: public Model
{

};