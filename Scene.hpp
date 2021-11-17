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
};

