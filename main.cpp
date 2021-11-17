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
	if (!glfwInit()) { exit(EXIT_FAILURE); }// ��ʼ�� glfw

	// ָ������������OpenGL�汾4.3����
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);// ���汾�� 4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);// �ΰ汾�� 3

	// �������ڣ�����Ϊ ���ߡ����⡢����ȫ����ʾ����Դ����
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Chapter2 - program1", nullptr, nullptr);
	glfwMakeContextCurrent(window);// �������뵱ǰ OpenGL �����Ĺ�������

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;// Ϊ�˽�������������⣬����ɾ������������
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }// ��ʼ��glew��ʹ�ÿ��Ե��� opengl ����
	//if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { exit(EXIT_FAILURE); } // ��ʼ��glad��ʹ�ÿ��Ե��� opengl ����
	
	glfwSwapInterval(1);// ���ý���ˢ�µ���С���
	glfwSetWindowSizeCallback(window, windowReshapeCallback);// ��Ӵ��ڴ�С�ı�ص�����

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
	// ��ʼ��ʾ����
	while (!glfwWindowShouldClose(window)) { // ������ڲ��رգ������ѭ��
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);// �������룬����ƶ�������
		scene.display(); // ���ƽ���
		glfwSwapBuffers(window); // ˢ�½���
		glfwPollEvents();// ����������¼�
	}

	glfwDestroyWindow(window);// ���ٴ���
	glfwTerminate();// ��ֹ����

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