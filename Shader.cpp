#include "Shader.hpp"
#include "Log.hpp"
#include <fstream>
#include <sstream>


void Shader::loadSource(const char* source)
{
	glShaderSource(_id, 1, &source, nullptr);
}

void Shader::loadSource(const std::string& source)
{
	loadSource(source.c_str());
}

void Shader::loadSource(GLsizei numSource, const GLchar* const* sources, const GLint* lenPerSource /*= nullptr*/)
{
	glShaderSource(_id, numSource, sources, lenPerSource);
}

void Shader::loadSourceFromFile(const char* filePath)
{
	try
	{
		std::string content;
		std::ifstream fileStream;
		fileStream.open(filePath);

		std::stringstream shaderStream;
		shaderStream << fileStream.rdbuf();
		fileStream.close();
		content = shaderStream.str();

		loadSource(content.c_str());
	}
	catch (std::ifstream::failure)
	{
		Log() << "Error: can't open file " << filePath << Log::ENDL;
	}
}

void Shader::compileShader()
{
	glCompileShader(_id);
	printShaderLog();
}

void Shader::printShaderLog()
{
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char *)malloc(len);
		glGetShaderInfoLog(_id, len, &chWrittn, log);
		Log() << getTypeStr() << "compilation failed!\n"
			<< "Shader Info Log: " << log << Log::ENDL;
		free(log);
	}
}

bool Shader::checkOpenGLError()
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

std::string Shader::getTypeStr()
{
	switch (_type)
	{
	case Shader::EType::VERTEX:
		return "Vertex ";
		break;
	case Shader::EType::FRAGMENT:
		return "Fragment ";
		break;
	default:
		break;
	}
	return "";
}

ShaderVert::ShaderVert()
	:Shader(EType::VERTEX)
{
	createShader();
}

void ShaderVert::createShader()
{
	_id = glCreateShader(GL_VERTEX_SHADER);// 创建类型为GL_VERTEX_SHADER的着色器，即顶点着色器
}

ShaderFrag::ShaderFrag()
	:Shader(EType::FRAGMENT)
{
	createShader();
}

void ShaderFrag::createShader()
{
	_id = glCreateShader(GL_FRAGMENT_SHADER);// 创建类型为GL_FRAGMENT_SHADER的着色器，即片元着色器
}
