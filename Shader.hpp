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
	enum EType {
		UNDEFINED,
		VERTEX,
		FRAGMENT
	};
	static bool checkOpenGLError();

public:
	Shader() {}
	Shader(EType eType) :_type(eType) {}
	virtual ~Shader() {}
private:
	virtual void createShader() = 0;

public:
	void loadSource(const char* source);
	void loadSource(const std::string& source);
	void loadSource(GLsizei numSource, const GLchar* const* sources, const GLint* lenPerSource = nullptr);
	void loadSourceFromFile(const char* fileName);
	virtual void compileShader();

	GLuint getId() { return _id; }
	void noLog(bool bShow = false) { _showLog = bShow; }

protected:
	std::string getTypeStr();
	void printShaderLog();


protected:
	char* _source{ nullptr };
	GLuint _id{ 0 };
	EType _type{ UNDEFINED };
	bool _showLog{ true };
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
