#pragma once

#include "Shader.hpp"

/**
* @brief: ×ÅÉ«Æ÷³ÌÐò
*/
class ShaderProgram
{
public:
	static ShaderProgram CreateShaderProgram(const char* vertSource, const char* fragSource);

public:
	ShaderProgram();
	~ShaderProgram();

	void attachShader(GLuint shaderID);
	void linkProgram();

	GLuint getId() { return _id; }
	void noLog(bool bShow = false) { _showLog = bShow; }

	//operator GLuint() { return _id; }

private:
	void printProgramLog();

private:
	GLuint _id{ 0 };
	bool _showLog{ true };
};

