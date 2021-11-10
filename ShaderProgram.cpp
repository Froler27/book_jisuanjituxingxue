#include "ShaderProgram.hpp"
#include "Log.hpp"


ShaderProgram ShaderProgram::CreateShaderProgram(const char* vertSource, const char* fragSource)
{
	ShaderVert vertShader;
	ShaderFrag fragShader;

	vertShader.loadSourceFromFile(vertSource);
	vertShader.compileShader();
	fragShader.loadSourceFromFile(fragSource);
	fragShader.compileShader();

	ShaderProgram vfProgram;
	vfProgram.attachShader(vertShader.getId());
	vfProgram.attachShader(fragShader.getId());
	vfProgram.linkProgram();

	return vfProgram;
}

ShaderProgram::ShaderProgram()
{
	_id = glCreateProgram();// 创建着色器程序对象
}


ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::attachShader(GLuint shaderID)
{
	glAttachShader(_id, shaderID);// 将着色器加入程序对象
}

void ShaderProgram::linkProgram()
{
	glLinkProgram(_id);// 将加入的各个着色器程序进行链接
	if (_showLog) printProgramLog();
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
