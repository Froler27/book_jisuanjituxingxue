#pragma once

#include "Shader.hpp"

/**
* @brief: 着色器程序
*/
class ShaderProgram
{
public:
	/** @brief: 创建着色器程序 */
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
	bool _showLog{ true };// 是否打印着色器编译的信息
};

