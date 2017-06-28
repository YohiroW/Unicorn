#include "UcSkybox.h"
#include "UcCamera.h"
NS_UNICORN;

//define static variables
//--------------------------------------------------------------
const int Skybox::MAX_QUAD_COUNT = 6;
//
const char* Skybox::DEFAULT_SKYBOX_RIGHT = "res/texture/right.png";
const char*	Skybox::DEFAULT_SKYBOX_LEFT = "res/texture/left.png";
const char*	Skybox::DEFAULT_SKYBOX_TOP = "res/texture/top.png";
const char*	Skybox::DEFAULT_SKYBOX_BOTTOM = "res/texture/bottom.png";
const char*	Skybox::DEFAULT_SKYBOX_BACK = "res/texture/back.png";
const char*	Skybox::DEFAULT_SKYBOX_FRONT = "res/texture/front.png";

Skybox::Skybox() :RenderableObject(ShaderMgr::DEFAULT_SKYBOX)
{
}

Skybox::~Skybox()
{
	_skyboxFaces.clear();
}

bool Skybox::initialize(const char* right, const char* left, const char* top, const char* bottom, const char* back, const char* front)
{
	_shader = ShaderMgr::DEFAULT_SKYBOX;

	_skyboxFaces.push_back(right);
	_skyboxFaces.push_back(left);
	_skyboxFaces.push_back(top);
	_skyboxFaces.push_back(bottom);
	_skyboxFaces.push_back(back);
	_skyboxFaces.push_back(front);

	this->_setup();
	_cubeMapTexHadl = this->_loadeCubeMap(_skyboxFaces);


	_shader->apply();
	_shaderLoc[0] = _shader->getLocation("view");
	_shaderLoc[1] = _shader->getLocation("projection");

	return true;
}

void Skybox::_setup()
{
	// Setup skybox VAO
	glGenVertexArrays(1, &_skyboxVAO);
	glGenBuffers(1, &_skyboxVBO);
	glBindVertexArray(_skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(RenderData::skyboxVertices), &RenderData::skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);
}


TextureID Skybox::_loadeCubeMap(std::vector<const GLchar*> faces)
{
	GLuint textureID;
	glGenTextures(1, &textureID);

	int width, height;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	for (GLuint i = 0; i < MAX_QUAD_COUNT; i++)
	{
		image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);


	return textureID;
}

void Skybox::onPreRender(Camera* cam)
{
	glDepthFunc(GL_LEQUAL);
	_shader->apply();

	Matrix4x4 view = Matrix4x4(Matrix3x3(cam->getViewMatrix()));
	_shader->setMatrix4(_shaderLoc[0], view, true);
	_shader->setMatrix4(_shaderLoc[1], cam->getProjectionMatrix(),true);
	//_shader->setInterger("")
}

void Skybox::onPostRender()
{
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_CUBE_MAP,0);

	glDepthFunc(GL_LESS);
}

void Skybox::draw(float dt)
{
	//
	glBindVertexArray(_skyboxVAO);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _cubeMapTexHadl);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

TextureID Skybox::getSkyboxMapHandler() const
{
	return _cubeMapTexHadl;
}

void Skybox::destroy()
{
	glDeleteVertexArrays(1, &_skyboxVAO);
	glDeleteBuffers(1, &_skyboxVBO);
}

