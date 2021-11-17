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
#include "F7/Vec/Vec.h"
#include "F7/Matrix/Mat.h"
#include "Camera.hpp"
#include "Scene.hpp"

using namespace std;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void windowReshapeCallback(GLFWwindow* window, int newWidth, int newHeight);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera{ F7::Vec3(0.0f, 0.0f, 3.0f) };
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
	if (!glfwInit()) { exit(EXIT_FAILURE); }// 初始化 glfw

	// 指定机器必须与OpenGL版本4.3兼容
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);// 主版本号 4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);// 次版本号 3

	// 创建窗口，参数为 宽、高、标题、允许全屏显示、资源共享
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Chapter2 - program1", nullptr, nullptr);
	glfwMakeContextCurrent(window);// 将窗口与当前 OpenGL 上下文关联起来

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;// 为了解决电脑适配问题，可以删除如果不会出错
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }// 初始化glew，使得可以调用 opengl 函数
	//if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { exit(EXIT_FAILURE); } // 初始化glad，使得可以调用 opengl 函数
	
	glfwSwapInterval(1);// 设置界面刷新的最小间隔
	glfwSetWindowSizeCallback(window, windowReshapeCallback);// 添加窗口大小改变回调函数

	Scene scene;
	scene.setCamera(&camera);

	GLuint renderingProgram = ShaderProgram::CreateShaderProgram(
		"Shaders/vertShader.glsl",
		"Shaders/fragShader.glsl").getId();
	Model cube, pyr;
	cube.load("Models/cubo.txt");
	pyr.load("Models/pyramid.txt");

	cube.position().set(0, -2, 0);
	pyr.position().set(5, 1, -2);

	cube.renderingProgramID() = renderingProgram;
	pyr.renderingProgramID() = renderingProgram;
	scene.addModel(&cube);
	scene.addModel(&pyr);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	camera._pos.set(0, 0, 10);
	camera._aspect = (float)width / (float)height;

	float currentFrame;
	// 开始显示画面
	while (!glfwWindowShouldClose(window)) { // 如果窗口不关闭，则继续循环
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);// 处理输入，鼠标移动，按键
		scene.display(); // 绘制界面
		glfwSwapBuffers(window); // 刷新界面
		glfwPollEvents();// 处理窗口相关事件
	}

	glfwDestroyWindow(window);// 销毁窗口
	glfwTerminate();// 终止运行

	return 0;
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
		//return;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.processMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.processMouseScroll(yoffset);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.processKeyboard(Camera_Movement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.processKeyboard(Camera_Movement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.processKeyboard(Camera_Movement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.processKeyboard(Camera_Movement::RIGHT, deltaTime);
	static bool tag = true;
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS) {
		if (tag) {
			firstMouse = true;
			tag = false;
		}
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		tag = true;
	}
		
}

void windowReshapeCallback(GLFWwindow* window, int newWidth, int newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	camera._aspect = (float)newWidth / (float)newHeight;
}