#include "Model.hpp"
#include <string>
#include <sstream>
#include <fstream>

#include "Dependencies/stb_image.h"
#include "Log.hpp"

using namespace F7;

bool Model::loadModelFile(const char* modelPath)
{
	try
	{
		_verts.clear();
		std::ifstream vertsFile;
		vertsFile.open(modelPath);

		std::stringstream vertsStream;
		vertsStream << vertsFile.rdbuf();
		vertsFile.close();
		float tem;
		while (vertsStream >> tem) {
			_verts.push_back(tem);
		}
	}
	catch (std::ifstream::failure)
	{
		Log() << "Error: can't open file " << modelPath << Log::ENDL;
		return false;
	}
    return true;
}

bool Model::loadTexture(const char* texturePath, const char* uniformName, int texUnit)
{
	GLuint textureID;
	glBindVertexArray(_vao);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	_textureMap.insert(std::make_pair(texUnit, textureID));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
	if (data)
	{
		if (nrChannels<4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		Log() << "Failed to load texture" << Log::ENDL;
		return false;
	}
	stbi_image_free(data);
	_spShader->use();
	_spShader->setInt(uniformName, texUnit);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}

void Model::configData_v_n()
{
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	glBufferData(GL_ARRAY_BUFFER, _verts.size() * sizeof(value_type), &_verts[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(value_type), (void*)0);
	glEnableVertexAttribArray(0);//顶点
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(value_type), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);//法线
	if (_bUseEBO) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(_indices[0]), &_indices[0], GL_STATIC_DRAW);
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Model::configData_v_n_tc()
{
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	glBufferData(GL_ARRAY_BUFFER, _verts.size() * sizeof(value_type), &_verts[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(value_type), (void*)0);
	glEnableVertexAttribArray(0);//顶点
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(value_type), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);//法线
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(value_type), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);//纹理坐标
	if (_bUseEBO) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(_indices[0]), &_indices[0], GL_STATIC_DRAW);
	}
	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Model::useTexture()
{
	for (auto e : _textureMap) {
		if (e.first==0)
			glActiveTexture(GL_TEXTURE0);
		else if (e.first==1)
			glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, e.second);
	}
}

void Model::genEBO()
{
	glGenBuffers(1, &_ebo);
	_bUseEBO = true;
}

void Model::draw()
{
	useTexture();
	glBindVertexArray(_vao);
	if (_bUseEBO)
		glDrawElements(GL_TRIANGLE_STRIP, (GLsizei)_indices.size(), GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, _vertsNum);
	//glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 100000);
	glBindVertexArray(0);
}

F7::Mat4 Model::getWorldMatrix()
{
	F7::Mat4 res{ 1 };
	res *= F7::Mat4::Translate(_pos);
	res *= F7::Mat4::Rotate(_rot);
	res *= F7::Mat4::Scale(_sca);
	return res;
}

void Model::setMaterial(const Material& material)
{
	//_pMaterial = pMaterial;
	_spShader->setVec4f("material.ambient", material.ambient);
	_spShader->setVec4f("material.diffuse", material.diffuse);
	_spShader->setVec4f("material.specular", material.specular);
	_spShader->setFloat("material.shininess", material.shininess);
}

void Model::setGlobalAmbient(const Vec4f& globalAmbient)
{
	_spShader->setVec4f("globalAmbient", globalAmbient);
}

void Model::setLight(const LightSource& pLightSource)
{
	_spShader->setVec4f("light.ambient", pLightSource.ambient);
	_spShader->setVec4f("light.diffuse", pLightSource.diffuse);
	_spShader->setVec4f("light.specular", pLightSource.specular);
	_spShader->setVec3f("light.position", pLightSource.position);
}

void Sphere::genData()
{
	genEBO();
	setNormalBinding(EBindingType::Per_Vertex);

	int vertsNum = (_prec + 1) * (_prec * 2 + 1);// 顶点数量
	int len = 3 + 3 + 2; // 顶点大小 + 法线大小 + 纹理坐标大小

	_verts.reserve((long long)vertsNum * len);
	for (int i = 0; i <= _prec; i++)//从下到上添加点，有等于号是为了之后贴纹理时可以和图片的点一一对应
	{
		for (int j = 0; j <= _prec * 2; j++)//逆时针添加点
		{
			Vec3_T<value_type> vec3VertexT(
				sin(value_type(F7::PI * i / (value_type)_prec)) * cos(value_type(F7::PI * j / (value_type)_prec)),
				sin(value_type(F7::PI * i / (value_type)_prec)) * sin(value_type(F7::PI * j / (value_type)_prec)),
				-cos(value_type(F7::PI * i / (value_type)_prec)));//添加负号是为了从下到上添加点，与纹理坐标一致
			push_back_vec3(vec3VertexT* _radius);//添加顶点
			push_back_vec3(vec3VertexT);
			_verts.push_back(value_type(j) / 2.0f / _prec);//添加纹理坐标x
			_verts.push_back(value_type(i) / _prec);//添加纹理坐标y
/*			std::cout << vec3VertexT << std::endl;*/
		}
	}

	_indices.reserve((long long)_prec * ((long long)_prec * 2 + 1)*2);
	for (int i = 0; i < _prec; i++) {
		for (int j = 0; j <= _prec * 2; j++) {
			_indices.push_back(i * (_prec * 2 + 1) + j);
			_indices.push_back((i + 1) * (_prec * 2 + 1) + j);
// 			std::cout << _indices[_indices.size() - 2] << " "
// 				<< _indices[_indices.size() - 1] << std::endl;
		}
	}
}

void Sphere::init()
{
	
}

void Torus::genData()
{
	genEBO();
	setNormalBinding(EBindingType::Per_Vertex);

	Vec3_T<value_type> center;
	Vec3_T<value_type> aPoint;

	value_type hint1 = value_type(PI*2 / _prec1);
	value_type hint2 = value_type(PI*2 / _prec2);

	int vertsNum = (_prec1 + 1) * (_prec2 + 1);
	int len = 3 + 3 + 2;

	_verts.reserve((long long)vertsNum * len);
	for (int i = 0; i <= _prec1; ++i) {
		center.set(_radius1 * Math::cos(hint1 * i),
			_radius1 * Math::sin(hint1 * i), 0);
		for (int j = 0; j <= _prec2; ++j) {
			value_type r = _radius1 + _radius2 * Math::cos(value_type(hint2 * j+PI));// +PI 是为了从内圈中间开始添加点
			aPoint.set(r * Math::cos(hint1 * i),
				r * Math::sin(hint1 * i),
				_radius2 * Math::sin(value_type(hint2 * j+ PI)));
			push_back_vec3(aPoint);
			push_back_vec3((aPoint - center).getNormalize());// 法向量
			_verts.push_back(1.f * i / _prec1);//纹理X坐标
			_verts.push_back(1.f * j / _prec2);//纹理Y坐标
		}
	}

	_indices.reserve((long long)_prec1 * ((long long)_prec2 + 1) * 2);
	for (int i = 0; i < _prec1; i++) {
		for (int j = 0; j <= _prec2; j++) {
			_indices.push_back(i * (_prec2 + 1) + j);
			_indices.push_back((i + 1) * (_prec2 + 1) + j);
		}
	}
}

void Torus::draw()
{
	Model::draw();
}


void Torus::init()
{

}

void Cube::genData()
{
	genEBO();
	setNormalBinding(EBindingType::Per_Vertex);
	value_type halfLen = _sideLength / 2.f;
	
	_vertsNum = 4 * 6;
	_vertSize = 3 + 3 + 2;
	int n = _vertsNum * _vertSize;

	std::unique_ptr<float> verts = (std::unique_ptr<float>) new float[n]{
		 -halfLen , halfLen ,-halfLen ,0,0,-1 ,0,0
		, halfLen , halfLen ,-halfLen ,0,0,-1 ,1,0
		,-halfLen ,-halfLen ,-halfLen ,0,0,-1 ,0,1
		, halfLen ,-halfLen ,-halfLen ,0,0,-1 ,1,1

		,-halfLen ,-halfLen ,-halfLen ,0,-1,0 ,0,0
		, halfLen ,-halfLen ,-halfLen ,0,-1,0 ,1,0
		,-halfLen ,-halfLen , halfLen ,0,-1,0 ,0,1
		, halfLen ,-halfLen , halfLen ,0,-1,0 ,1,1

		, halfLen ,-halfLen ,-halfLen ,1,0,0 ,0,0
		, halfLen , halfLen ,-halfLen ,1,0,0 ,1,0
		, halfLen ,-halfLen , halfLen ,1,0,0 ,0,1
		, halfLen , halfLen , halfLen ,1,0,0 ,1,1

		, halfLen , halfLen ,-halfLen ,0,1,0 ,0,0
		,-halfLen , halfLen ,-halfLen ,0,1,0 ,1,0
		, halfLen , halfLen , halfLen ,0,1,0 ,0,1
		,-halfLen , halfLen , halfLen ,0,1,0 ,1,1

		,-halfLen , halfLen ,-halfLen ,-1,0,0 ,0,0
		,-halfLen ,-halfLen ,-halfLen ,-1,0,0 ,1,0
		,-halfLen , halfLen , halfLen ,-1,0,0 ,0,1
		,-halfLen ,-halfLen , halfLen ,-1,0,0 ,1,1

		,-halfLen ,-halfLen , halfLen ,0,0,1 ,0,0
		, halfLen ,-halfLen , halfLen ,0,0,1 ,1,0
		,-halfLen , halfLen , halfLen ,0,0,1 ,0,1
		, halfLen , halfLen , halfLen ,0,0,1 ,1,1
	};

	_verts.reserve(n);
	for (int i = 0; i < n; ++i)
		_verts.push_back(verts.get()[i]);

	_indices.reserve(36);
	for (int i = 0; i < 6; ++i) {
		_indices.push_back(4 * i); _indices.push_back(4 * i + 1); _indices.push_back(4 * i + 2);
		_indices.push_back(4 * i + 2); _indices.push_back(4 * i + 1); _indices.push_back(4 * i + 3);
	}
}
