#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <vector>

//#include <glad/glad.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderProgram.hpp"
#include "Log.hpp"

using namespace std;

const GLuint numVAOs = 1;
const GLuint numVBOs = 2;

float cameraX, cameraY, cameraZ;
float cubeLocX, cubeLocY, cubeLocZ;

GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

GLuint mvLoc, projLoc;
int width, height;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat;
glm::mat4 tMat, rMat;


float x = 0.f;
float inc = 0.01f;

void readVertexes(vector<float>& verts)
{
	const char* filePath = "Models/cubo.txt";
	try
	{
		verts.clear();
		ifstream vertsFile;
		vertsFile.open(filePath);

		std::stringstream vertsStream;
		vertsStream << vertsFile.rdbuf();
		vertsFile.close();
		float tem;
		while (vertsStream >> tem) {
			verts.push_back(tem);
		}
	}
	catch (std::ifstream::failure)
	{
		Log() << "Error: can't open file " << filePath << Log::ENDL;
	}
	
}

void setupVertices()
{
	vector<float> verts;
	readVertexes(verts);
	float vv[108];
	for (int i = 0; i < 108; i++) {
		vv[i] = verts[i];
	}
	
	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(numVBOs, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), vv, GL_STATIC_DRAW);
}

void init(GLFWwindow* window) 
{
	renderingProgram = ShaderProgram::CreateShaderProgram(
		"Shaders/vertShader.glsl",
		"Shaders/fragShader.glsl").getId();
	cameraX = 0;
	cameraY = 0;
	cameraZ = 30;
	cubeLocX = 0;
	cubeLocY = -2;
	cubeLocZ = 0;
	setupVertices();
}

void display(GLFWwindow* window, double currentTime)
{
	glClearColor(0.96f, 0.64f, 0.78f, 1.f);// ���ñ�����ɫ��׼ȷ˵����ʲô��ɫ�������ɫ������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// �����ǰ��������Ȼ���
	glUseProgram(renderingProgram);// ����ɫ����������OpenGL���ߣ����ŵ�GPU�У�����û������
	//glPointSize(30.f);// ���õ��СΪ30
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);// �����߿�ģʽ��GL_FILL Ϊ���ģʽ��Ĭ�ϣ�

	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	aspect = (float)width / (float)height;
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.f);//1.0472 radians = 60 degrees
	vMat = glm::translate(glm::mat4(1.f), glm::vec3(-cameraX, -cameraY, -cameraZ));
	//mMat = glm::translate(glm::mat4(1.f), glm::vec3(cubeLocX, cubeLocY, cubeLocZ));

	float tf;
	for (int i = 0; i < 24; i++)
	{
		tf = currentTime + i;
		tMat = glm::translate(glm::mat4(1.f), glm::vec3(sin(0.35f * tf) * 8.0f, cos(0.52f * tf) * 8.f, sin(0.7f * tf) * 8.f));
		rMat = glm::rotate(glm::mat4(1.f), 1.75f * (float)currentTime, glm::vec3(0.f, 1.f, 0.f));
		rMat = glm::rotate(rMat, 1.75f * (float)currentTime, glm::vec3(1, 0, 0));
		rMat = glm::rotate(rMat, 1.75f * (float)currentTime, glm::vec3(0, 0, 1));

		mMat = tMat * rMat;
		mvMat = vMat * mMat;

		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

int main()
{
	glewExperimental = GL_TRUE;// Ϊ�˽�������������⣬����ɾ������������
	if (!glfwInit()) { exit(EXIT_FAILURE); }// ��ʼ�� glfw

	// ָ������������OpenGL�汾4.3����
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);// ���汾�� 4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);// �ΰ汾�� 3

	// �������ڣ�����Ϊ ���ߡ����⡢����ȫ����ʾ����Դ����
	GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter2 - program1", nullptr, nullptr);
	glfwMakeContextCurrent(window);// �������뵱ǰ OpenGL �����Ĺ�������

	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }// ��ʼ��glew��ʹ�ÿ��Ե��� opengl ����
	//if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { exit(EXIT_FAILURE); } // ��ʼ��glad��ʹ�ÿ��Ե��� opengl ����
	
	glfwSwapInterval(1);// ���ý���ˢ�µ���С���

	init(window);

	// ��ʼ��ʾ����
	while (!glfwWindowShouldClose(window)) { // ������ڲ��رգ������ѭ��
		display(window, glfwGetTime()); // ���ƽ���
		glfwSwapBuffers(window); // ˢ�½���
		glfwPollEvents();// ����������¼�
	}

	glfwDestroyWindow(window);// ���ٴ���
	glfwTerminate();// ��ֹ����

	return 0;
}
