#pragma once

#include "Shader.hpp"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
* @brief: ��ɫ������
*/
class ShaderProgram
{
public:
	/** @brief: ������ɫ������ */
	static ShaderProgram CreateShaderProgram(const char* vertexPath, const char* fragmentPath);

public:
	ShaderProgram();
	ShaderProgram(const char* vertexPath, const char* fragmentPath);
	~ShaderProgram() {}

	void use() { glUseProgram(_id); }

	GLuint getId() const { return _id; }
	void noLog(bool bShow = false) { _showLog = bShow; }

	//void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMatrix4fv(const std::string& name, glm::mat4 value) const;

private:
	void printProgramLog();
	void attachShader(GLuint shaderID) { glAttachShader(_id, shaderID); }
	void linkProgram();

private:
	GLuint _id{ 0 };
	bool _showLog{ true };// �Ƿ��ӡ��ɫ���������Ϣ
};

