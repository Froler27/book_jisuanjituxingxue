#include "Scene.hpp"
#include "F7/F7.hpp"
#include <GL/glew.h>

void Scene::init()
{
	//_camera.setPos(0, 0, 10);

}

void Scene::display()
{
	glClearColor(0.96f, 0.64f, 0.78f, 1.f);// 设置背景颜色，准确说是用什么颜色来填充颜色缓冲区
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// 清除当前画面与深度缓存

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//glPointSize(30.f);// 设置点大小为30
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);// 设置线框模式，GL_FILL 为填充模式（默认）
	
	static GLuint mvLoc, projLoc;
	static F7::Mat4 mvMat;
	static F7::Mat4 pMat;//1.0472 radians = 60 degrees
	static F7::Mat4 vMat;
	static F7::Mat4 mMat;
	for (auto model : _models) {
		useRenderingProgram(model->renderingProgramID());
		mvLoc = glGetUniformLocation(_curRenderingProgramID, "mv_matrix");
		projLoc = glGetUniformLocation(_curRenderingProgramID, "proj_matrix");
		//mvMat = F7::Mat4::Translate(0, -3, -10);
		vMat = _camera->getViewMatrix();
		mMat = model->getWorldMatrix();
		mvMat = vMat * mMat;
		pMat = _camera->getProjMatrix();
		glBindVertexArray(model->getVAO());
		glUniformMatrix4fv(mvLoc, 1, GL_TRUE, mvMat.ptr());
		glUniformMatrix4fv(projLoc, 1, GL_TRUE, pMat.ptr());
		//glBindVertexArray(model->getVAO());
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLES, 0, model->getVertsNum());
		//glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 100000);
	}
}

void Scene::useRenderingProgram(GLuint id)
{
	glUseProgram(id);// 将着色器程序载入OpenGL管线，即放到GPU中，但并没有运行
	_curRenderingProgramID = id;
}

void Scene::endRenderingProgram()
{
}
