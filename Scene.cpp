#include "Scene.hpp"
#include "F7/F7.hpp"
#include <GL/glew.h>

void Scene::init()
{
	//_camera.setPos(0, 0, 10);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	//glClearColor(0.96f, 0.64f, 0.78f, 1.f);// 设置背景颜色，准确说是用什么颜色来填充颜色缓冲区
	glClearColor(0.5, 0.5, 0.5, 1.f);
}

void Scene::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// 清除当前画面与深度缓存

	//glPointSize(30.f);// 设置点大小为30
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);// 设置线框模式，GL_FILL 为填充模式（默认）
	
	
	for (auto model : _models) {
		useRenderingProgram(model->getShaderProgram()->getId());
			
		_projViewWorldMatLoc = glGetUniformLocation(model->getShaderProgram()->getId(), "proj_view_world_matrix");
		_viewMat = _camera->getViewMatrix();
		_worldMat = model->getWorldMatrix();
		_projMat = _camera->getProjMatrix();
		_projViewWorldMat = _projMat* _viewMat * _worldMat;
		glUniformMatrix4fv(_projViewWorldMatLoc, 1, GL_TRUE, _projViewWorldMat.ptr());

		model->draw();
	}
	//ShaderProgram::checkOpenGLError();
}

void Scene::useRenderingProgram(GLuint id)
{
	if (_curRenderingProgramID != id) {
		glUseProgram(id);// 将着色器程序载入OpenGL管线，即放到GPU中，但并没有运行
		_curRenderingProgramID = id;
	}
}

void Scene::endRenderingProgram()
{
}
