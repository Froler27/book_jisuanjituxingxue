#include "ShaderProgram.hpp"
#include "F7/Common/Log.hpp"


std::unique_ptr<ShaderProgram> ShaderProgram::CreateShaderProgram(const char* vertexPath, const char* fragmentPath)
{
	return std::unique_ptr<ShaderProgram>(new ShaderProgram(vertexPath, fragmentPath));
}

std::unique_ptr<ShaderProgram> ShaderProgram::CreateShaderProgram(const std::string& vertexPath, const std::string& fragmentPath)
{
	return CreateShaderProgram(vertexPath.c_str(), fragmentPath.c_str());
}

bool ShaderProgram::checkOpenGLError()
{
	bool foundError = false;
	int glErr = glGetError();
	while (glErr != GL_NO_ERROR) {
		Log() << "glError: " << glErr << Log::ENDL;
		foundError = true;
		glErr = glGetError();
	}
	return foundError;
}

ShaderProgram::ShaderProgram()
{
	_id = glCreateProgram();// 创建着色器程序对象
}


ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath)
{
	_id = glCreateProgram();// 创建着色器程序对象

	ShaderVert vertShader;
	ShaderFrag fragShader;

	vertShader.loadSourceFromFile(vertexPath);
	vertShader.compileShader();
	fragShader.loadSourceFromFile(fragmentPath);
	fragShader.compileShader();

	this->attachShader(vertShader.getId());
	this->attachShader(fragShader.getId());
	this->linkProgram();
}

void ShaderProgram::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
}

void ShaderProgram::setVec2f(const std::string& name, const F7::Vec2f& value) const
{
	glUniform2fv(glGetUniformLocation(_id, name.c_str()), 1, value.ptr());
}

void ShaderProgram::setVec3f(const std::string& name, const F7::Vec3f& value) const
{
	glUniform3fv(glGetUniformLocation(_id, name.c_str()), 1, value.ptr());
}

void ShaderProgram::setVec4f(const std::string& name, const F7::Vec4f& value) const
{
	//glUniform4fv(glGetUniformLocation(_id, name.c_str()), 1, value.ptr());
	glUniform4f(glGetUniformLocation(_id, name.c_str()), value.x(), value.y(), value.z(), value.w());
}

void ShaderProgram::setMatrix4fv(const std::string& name, float* value) const
{
	glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()),
		1, GL_FALSE, value);
}

//void ShaderProgram::setBool(const std::string& name, bool value) const
//{
//	glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value);
//}

void ShaderProgram::linkProgram()
{
	glLinkProgram(_id);// 将加入的各个着色器程序进行链接
	printProgramLog();
}

void ShaderProgram::printProgramLog()
{
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char *)malloc(len);
		glGetProgramInfoLog(_id, len, &chWrittn, log);
		Log() << "Linking failed!\n"
			<< "Program Info Log: " << log << Log::ENDL;
		free(log);
	}
}
