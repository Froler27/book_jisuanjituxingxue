#pragma once

#include "Camera.hpp"
#include "Model.hpp"
#include <vector>

class Scene
{  
public:
	Scene() { init(); }
	~Scene() {}

	void init();
	void display();
	void addModel(Model* pModel) { _models.push_back(pModel); }
	void useRenderingProgram(GLuint id);
	void endRenderingProgram();

	void setCamera(Camera* camera) { _camera = camera; }

	//Camera& camera() { return _camera; }

private:
	Camera* _camera;
	std::vector<Model*> _models;
	GLuint _curRenderingProgramID{ 0 };
	
	float deltaTime{ 0 };	// time between current frame and last frame
	float lastFrame{ 0 };
	bool firstMouse{ true };

	GLuint _projViewWorldMatLoc;	// 最终矩阵地址
	F7::Mat4 _projViewWorldMat;	// 最终矩阵
	F7::Mat4 _projMat;			// 投影矩阵
	F7::Mat4 _viewMat;			// 视角矩阵
	F7::Mat4 _worldMat;			// 世界矩阵
};

