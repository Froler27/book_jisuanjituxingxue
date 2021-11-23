#include "ShaderProgram.hpp"
#include "Log.hpp"


std::unique_ptr<ShaderProgram> ShaderProgram::CreateShaderProgram(const char* vertexPath, const char* fragmentPath)
{
	return std::unique_ptr<ShaderProgram>(new ShaderProgram(vertexPath, fragmentPath));
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
