#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <vector>

//#include <glad/glad.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "F7/Graphic/Shader/ShaderProgram.hpp"
#include "F7/Common/Log.hpp"
#include "F7/Vec/Vec.h"
#include "F7/Matrix/Mat.h"
#include "F7/Graphic/Camera/Camera.hpp"
#include "F7/Graphic/Scene.hpp"
#include "F7/Graphic/Material.hpp"

using namespace std;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void processInput(GLFWwindow* window);
void windowReshapeCallback(GLFWwindow* window, int newWidth, int newHeight);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const string PATH = "C:/Users/16634/source/book_jisuanjituxingxue/";

// camera
Camera camera{ F7::Vec3(0.0f, 0.0f, 3.0f) };
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool grapMouse = true;
bool mouseLeftBtnPressed = false;
bool mouseRightBtnPressed = false;

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
	camera._width = SCR_WIDTH;
	camera._height = SCR_HEIGHT;

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glewExperimental = GL_TRUE;// Ϊ�˽�������������⣬����ɾ������������
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }// ��ʼ��glew��ʹ�ÿ��Ե��� opengl ����
	//if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { exit(EXIT_FAILURE); } // ��ʼ��glad��ʹ�ÿ��Ե��� opengl ����
	ShaderProgram::checkOpenGLError();
	glfwSwapInterval(1);// ���ý���ˢ�µ���С���
	glfwSetWindowSizeCallback(window, windowReshapeCallback);// ��Ӵ��ڴ�С�ı�ص�����

	Scene scene;
	scene.setCamera(&camera);
	std::shared_ptr<ShaderProgram> spShader = ShaderProgram::CreateShaderProgram(
		PATH + "Shaders/vertShader.glsl",
		PATH + "Shaders/fragShader.glsl");

	std::shared_ptr<ShaderProgram> spShader_Blinn_Phong = ShaderProgram::CreateShaderProgram(
		PATH + "Shaders/vert_Blinn_Phong.glsl",
		PATH + "Shaders/frag_Blinn_Phong.glsl");

	PointLight pointLight;
	ParallelLight parallelLight;

	Cube cube/*, pyr*/;
	cube.genData();
	cube.configData_v_n_tc();
	cube.setShaderProgram(spShader_Blinn_Phong);
	cube.loadTexture(PATH + "Images/container.jpg", "texture0", 0);
	cube.loadTexture(PATH + "Images/awesomeface.png", "texture1", 1);

	Sphere sphere;
	//sphere.setRaius(1000);
	sphere.genData();
	sphere.configData_v_n_tc();
	std::shared_ptr<ShaderProgram> spShaderVNTC = ShaderProgram::CreateShaderProgram(
		PATH + "Shaders/vertShader_v_n_tc.glsl",
		PATH + "Shaders/fragShader_1tex.glsl");
	sphere.setShaderProgram(spShaderVNTC);
	sphere.loadTexture(PATH + "Images/texture/star/io.jpg", "texture0", 0);

	std::shared_ptr<ShaderProgram> spShader_v_n_u1c = ShaderProgram::CreateShaderProgram(
		//"Shaders/vert_Gouraud.glsl",
		//"Shaders/frag.glsl");
		PATH + "Shaders/vert_Phong.glsl",
		PATH + "Shaders/frag_Phong.glsl");
		//"Shaders/vert_Blinn_Phong.glsl",
		//"Shaders/frag_Blinn_Phong.glsl");
	std::shared_ptr<ShaderProgram> spShader_Gouraud = ShaderProgram::CreateShaderProgram(
		PATH + "Shaders/vert_Gouraud.glsl",
		PATH + "Shaders/frag.glsl");

	Torus torus;
	//torus.setRaius(1000);
	torus.genData();
	torus.configData_v_n();
	torus.setShaderProgram(spShader_v_n_u1c);
	torus.getShaderProgram()->use();
	//F7::Vec4f color_u{ 1,1,0,1 };
	//torus.getShaderProgram()->setVec4f("color_u", color_u);
	torus.setMaterial(MaterialGold);
	torus.setGlobalAmbient({ 0.7f, 0.7f ,0.7f ,1.0f });
	
	torus.setLight(pointLight);

	
	Torus torus1;
	//torus.setRaius(1000);
	torus1.genData();
	torus1.configData_v_n();
	torus1.setShaderProgram(spShader_Blinn_Phong);
	torus1.getShaderProgram()->use();
	//F7::Vec4f color_u{ 1,1,0,1 };
	//torus1.getShaderProgram()->setVec4f("color_u", color_u);
	torus1.setMaterial(MaterialGold);
	torus1.setGlobalAmbient({ 0.7f, 0.7f ,0.7f ,1.0f });
	
	torus.setLight(pointLight);


	
	Torus torus2;
	//torus.setRaius(1000);
	torus2.genData();
	torus2.configData_v_n();
	torus2.setShaderProgram(spShader_Gouraud);
	torus2.getShaderProgram()->use();
	//torus2.getShaderProgram()->setVec4f("color_u", color_u);
	torus2.setMaterial(MaterialGold);
	torus2.setGlobalAmbient({ 0.7f, 0.7f ,0.7f ,1.0f });
	
	torus.setLight(pointLight);

	cube.position().set(0, -2, 0);
	sphere.position().set(0, 2, 0);
	torus.position().set(0, 0, -2);
	torus1.position().set(3, 0, -2);
	torus2.position().set(-3, 0, -2);

	
	//pyr.renderingProgramID() = renderingProgram;
	scene.addModel(&cube);
	//scene.addModel(&sphere);
	scene.addModel(&torus);
	scene.addModel(&torus1);
	scene.addModel(&torus2);
	//scene.addModel(&pyr);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	camera._pos.set(0, -10, 0);
	camera._aspect = (float)width / (float)height;

	float currentFrame;
	// ��ʼ��ʾ����
	while (!glfwWindowShouldClose(window)) { // ������ڲ��رգ������ѭ��
		currentFrame = (float)glfwGetTime();
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
	if (!grapMouse)
		return;
	if (firstMouse)
	{
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
		//return;
	}

	float xoffset = float(xpos - lastX);
	float yoffset = float(lastY - ypos); // reversed since y-coordinates go from bottom to top

	lastX = (float)xpos;
	lastY = (float)ypos;

	camera.processMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.processMouseScroll((float)yoffset);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	static double xpos, ypos;
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT: {
		if (action == GLFW_PRESS) {
			mouseLeftBtnPressed = true;
			glfwGetCursorPos(window, &xpos, &ypos);
			F7::Vec3 v3Coord(xpos, ypos, 0.5);
			cout << "Cursor Pressed Position at " << v3Coord << endl;

			camera.getNDCCoord(v3Coord);
			cout << "NDC  Coordinate: " << v3Coord << endl;

			
			F7::Vec4 v4TestPoint(0, -8, 0, 1);
			cout << camera.getViewMatrix() * v4TestPoint << endl;
			cout << camera.getProjMatrix() * camera.getViewMatrix() * v4TestPoint << endl;
			v4TestPoint = camera.getProjMatrix() * camera.getViewMatrix() * v4TestPoint;
			F7::Vec3 v3TestCoord = v4TestPoint.xyz()/ v4TestPoint.w();
			camera.getScreenCoordFromNDC(v3TestCoord);
			cout << v3TestCoord << endl;

			F7::Vec4 v4TemCoord(v3Coord, 1);
			F7::Mat4 matInvProj = camera.getProjInverseMatrix();
			v4TemCoord = (matInvProj * v4TemCoord);
			v4TemCoord /= v4TemCoord.w();
			cout << "View Coordinate: " << v4TemCoord << endl;

			F7::Mat4 matInvView = camera.getViewInverseMatrix();
			//v3Coord = (matInvView * F7::Vec4(v3Coord, 1)).xyz();
			//cout << "View Coordinate: " << v3Coord << endl;
			cout << endl;
		}
		else if (action == GLFW_RELEASE) {
			mouseLeftBtnPressed = false;
			glfwGetCursorPos(window, &xpos, &ypos);
			cout << "Cursor Released Position at (" << xpos << " : " << ypos << endl;

		}
		else {
			cout << "-" << endl;
		}	
	}
		break;
	case GLFW_MOUSE_BUTTON_RIGHT: {
		if (action == GLFW_PRESS) {
			mouseRightBtnPressed = true;
		}
		else if (action == GLFW_RELEASE) {
			mouseRightBtnPressed = false;
		}
		else {
			cout << "-" << endl;
		}
	}
		break;
	default:
		break;
	}
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
		
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		if (mouseRightBtnPressed)
			camera.processKeyboard(Camera_Movement::FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		if (mouseRightBtnPressed)
			camera.processKeyboard(Camera_Movement::BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		if (mouseRightBtnPressed)
			camera.processKeyboard(Camera_Movement::LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		if (mouseRightBtnPressed)
			camera.processKeyboard(Camera_Movement::RIGHT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		if (mouseRightBtnPressed)
			camera.processKeyboard(Camera_Movement::UP, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		if (mouseRightBtnPressed)
			camera.processKeyboard(Camera_Movement::DOWN, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		camera.addMouseMoveSpeed(0.1);
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		camera.addMouseMoveSpeed(-0.1);

	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		static int x = -1;
		x++;
		x %= 3;
		switch (x)
		{
		case 0:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case 1:
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			break;
		case 2:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		default:
			break;
		}
	}

	static bool tag = true;
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS) {
		if (tag) {
			firstMouse = true;
			tag = false;
			grapMouse = false;
		}
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		tag = true;
		grapMouse = true;
	}
		
}

void windowReshapeCallback(GLFWwindow* window, int newWidth, int newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	camera._aspect = (float)newWidth / (float)newHeight;
	camera._width = newWidth;
	camera._height = newHeight;
}