#include "Scene.hpp"
#include "F7/F7.hpp"
#include <GL/glew.h>

void Scene::init()
{
	//_camera.setPos(0, 0, 10);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	//glClearColor(0.96f, 0.64f, 0.78f, 1.f);// ���ñ�����ɫ��׼ȷ˵����ʲô��ɫ�������ɫ������
	glClearColor(0.5, 0.5, 0.5, 1.f);
}

void Scene::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// �����ǰ��������Ȼ���

	//glPointSize(30.f);// ���õ��СΪ30
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);// �����߿�ģʽ��GL_FILL Ϊ���ģʽ��Ĭ�ϣ�
	
	
	for (auto model : _models) {
		useRenderingProgram(model->getShaderProgram()->getId());
			
		_worldMatLoc = glGetUniformLocation(model->getShaderProgram()->getId(), "world_matrix");
		_viewMatLoc = glGetUniformLocation(model->getShaderProgram()->getId(), "view_matrix");
		_projMatLoc = glGetUniformLocation(model->getShaderProgram()->getId(), "proj_matrix");
		_viewMat = _camera->getViewMatrix();
		_worldMat = model->getWorldMatrix();
		_projMat = _camera->getProjMatrix();
		glUniformMatrix4fv(_worldMatLoc, 1, GL_TRUE, _worldMat.ptr());
		glUniformMatrix4fv(_viewMatLoc, 1, GL_TRUE, _viewMat.ptr());
		glUniformMatrix4fv(_projMatLoc, 1, GL_TRUE, _projMat.ptr());

		model->draw();
	}
	//ShaderProgram::checkOpenGLError();
}

void Scene::useRenderingProgram(GLuint id)
{
	if (_curRenderingProgramID != id) {
		glUseProgram(id);// ����ɫ����������OpenGL���ߣ����ŵ�GPU�У�����û������
		_curRenderingProgramID = id;
	}
}

void Scene::endRenderingProgram()
{
}