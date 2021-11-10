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
	_id = glCreateProgram();// ������ɫ���������
}


ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::attachShader(GLuint shaderID)
{
	glAttachShader(_id, shaderID);// ����ɫ������������
}

void ShaderProgram::linkProgram()
{
	glLinkProgram(_id);// ������ĸ�����ɫ�������������
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
