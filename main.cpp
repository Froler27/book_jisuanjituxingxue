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
	glClearColor(0.96f, 0.64f, 0.78f, 1.f);// 设置背景颜色，准确说是用什么颜色来填充颜色缓冲区
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// 清除当前画面与深度缓存
	glUseProgram(renderingProgram);// 将着色器程序载入OpenGL管线，即放到GPU中，但并没有运行
	//glPointSize(30.f);// 设置点大小为30
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);// 设置线框模式，GL_FILL 为填充模式（默认）

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
	glewExperimental = GL_TRUE;// 为了解决电脑适配问题，可以删除如果不会出错
	if (!glfwInit()) { exit(EXIT_FAILURE); }// 初始化 glfw

	// 指定机器必须与OpenGL版本4.3兼容
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);// 主版本号 4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);// 次版本号 3

	// 创建窗口，参数为 宽、高、标题、允许全屏显示、资源共享
	GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter2 - program1", nullptr, nullptr);
	glfwMakeContextCurrent(window);// 将窗口与当前 OpenGL 上下文关联起来

	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }// 初始化glew，使得可以调用 opengl 函数
	//if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { exit(EXIT_FAILURE); } // 初始化glad，使得可以调用 opengl 函数
	
	glfwSwapInterval(1);// 设置界面刷新的最小间隔

	init(window);

	// 开始显示画面
	while (!glfwWindowShouldClose(window)) { // 如果窗口不关闭，则继续循环
		display(window, glfwGetTime()); // 绘制界面
		glfwSwapBuffers(window); // 刷新界面
		glfwPollEvents();// 处理窗口相关事件
	}

	glfwDestroyWindow(window);// 销毁窗口
	glfwTerminate();// 终止运行

	return 0;
}
