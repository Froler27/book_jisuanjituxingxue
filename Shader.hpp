#pragma once

//#include <glad/glad.h>
#include <GL/glew.h>
#include <string>

/**
* @brief: 着色器基类，虚基类
*/
class Shader
{
public:
	enum class EType {
		UNDEFINED,
		VERTEX,
		FRAGMENT
	};
	static bool checkOpenGLError();

public:
	Shader() {}
	Shader(EType eType) :_type(eType) {}
	virtual ~Shader() { glDeleteShader(_id); }
private:
	virtual void createShader() = 0;

public:
	/** @brief: 加载着色器代码 */
	void loadSource(const char* source);
	void loadSource(const std::string& source);
	void loadSource(GLsizei numSource, const GLchar* const* sources, const GLint* lenPerSource = nullptr);
	/** @brief: 从文件中加载着色器代码 */
	void loadSourceFromFile(const char* fileName);
	/** @brief: 编译着色器 */
	virtual void compileShader();

	/** @brief: 获取着色器ID */
	GLuint getId() { return _id; }

protected:
	std::string getTypeStr();// 获取着色器类型的字符串
	void printShaderLog();// 打印着色器编译信息


protected:
	GLuint _id{ 0 };
	EType _type{ EType::UNDEFINED };
};


/**
 * @brief: 顶点着色器
*/
class ShaderVert: public Shader
{
public:
	ShaderVert();
	virtual ~ShaderVert() {}
private:
	virtual void createShader() override;
};


/**
* @brief: 片段着色器
*/
class ShaderFrag : public Shader
{
public:
	ShaderFrag();
	virtual ~ShaderFrag() {}

private:
	virtual void createShader() override;
};
