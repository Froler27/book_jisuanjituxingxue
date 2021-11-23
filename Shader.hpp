#pragma once

//#include <glad/glad.h>
#include <GL/glew.h>
#include <string>

/**
* @brief: ��ɫ�����࣬�����
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
	/** @brief: ������ɫ������ */
	void loadSource(const char* source);
	void loadSource(const std::string& source);
	void loadSource(GLsizei numSource, const GLchar* const* sources, const GLint* lenPerSource = nullptr);
	/** @brief: ���ļ��м�����ɫ������ */
	void loadSourceFromFile(const char* fileName);
	/** @brief: ������ɫ�� */
	virtual void compileShader();

	/** @brief: ��ȡ��ɫ��ID */
	GLuint getId() { return _id; }

protected:
	std::string getTypeStr();// ��ȡ��ɫ�����͵��ַ���
	void printShaderLog();// ��ӡ��ɫ��������Ϣ


protected:
	GLuint _id{ 0 };
	EType _type{ EType::UNDEFINED };
};


/**
 * @brief: ������ɫ��
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
* @brief: Ƭ����ɫ��
*/
class ShaderFrag : public Shader
{
public:
	ShaderFrag();
	virtual ~ShaderFrag() {}

private:
	virtual void createShader() override;
};
