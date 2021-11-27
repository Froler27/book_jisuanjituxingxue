#pragma once

#include "Shader.hpp"
#include <string>
#include <memory>

#include "F7/Vec/Vec.h"

/**
* @brief: 着色器程序
*/
class ShaderProgram
{
public:
	/** @brief: 创建着色器程序 */
	static std::unique_ptr<ShaderProgram> CreateShaderProgram(const char* vertexPath, const char* fragmentPath);
	static bool checkOpenGLError();
public:
	ShaderProgram();
	ShaderProgram(const char* vertexPath, const char* fragmentPath);
	~ShaderProgram() {}

	void use() { glUseProgram(_id); }

	GLuint getId() const { return _id; }

	//void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec2f(const std::string& name, const F7::Vec2f& value) const;
	void setVec3f(const std::string& name, const F7::Vec3f& value) const;
	void setVec4f(const std::string& name, const F7::Vec4f& value) const;
	void setMatrix4fv(const std::string& name, float* value) const;

private:
	void printProgramLog();
	void attachShader(GLuint shaderID) { glAttachShader(_id, shaderID); }
	void linkProgram();

private:
	GLuint _id{ 0 };
};

