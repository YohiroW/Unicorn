#include "UcPlane.h"
#include "UcCamera.h"
NS_UNICORN;
//
GLuint Plane::_vao = -1;
GLuint Plane::_vbo = -1;

Plane::Plane() :
RenderableObject(ShaderMgr::DEFAULT, Transform()),
_texture(NULL)
{
}

Plane::~Plane()
{

}

bool Plane::initialize(Texture* tex /* = NULL */)
{
	if (!_shader)
		_shader = ShaderMgr::DEFAULT;
	
	if (tex)
		_texture = tex;

	_shaderLoc[0] = _shader->getLocation("model");
	_shaderLoc[1] = _shader->getLocation("view");
	_shaderLoc[2] = _shader->getLocation("projection");
	_shaderLoc[4] = _shader->getLocation("diffTex");

	if (_isLightEnable){
		_shaderLoc[3] = _shader->getLocation("viewPosition");
	}

	this->_setup();

	return true;
}

void Plane::_setup()
{
	//gen -> (bind) bufferData -> bind vao -> unbind -> set data offset in array
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	//
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(RenderData::plane), RenderData::plane, GL_STATIC_DRAW);
	//
	glBindVertexArray(_vao);
	//important, set offset, bind attribute location
	//location = 0 -> position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	//location = 1 -> normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	//location = 2 -> texcoordation
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	//
	glBindVertexArray(0);

}

void Plane::draw(float dt)
{
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Plane::onPreRender(Camera* cam)
{
	_shader->apply();

	_shader->setMatrix4(_shaderLoc[0], _transform.getModel(), true);
	_shader->setMatrix4(_shaderLoc[1], cam->getViewMatrix(), true);
	_shader->setMatrix4(_shaderLoc[2], cam->getProjectionMatrix(), true);
	
	if (_isLightEnable){
		_shader->setVector3(_shaderLoc[3], _lightPos, true);
	}

	if (_texture)
	{
		_texture->bind();
		_shader->setInterger(_shaderLoc[4], _texture->getTextureHandler(), true);
	}
}

void Plane::onPostRender()
{
	//
	glBindVertexArray(0);
	_texture->unbind();
}

void Plane::destroy()
{
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
}

void Plane::attachTexture(const char* path)
{
	this->_texture = TextureMgr::getInstance()->createTexture(path);
	if (!_texture->load())
		Log("Texture load failed.\n");

}

void Plane::attachTexture(Texture* texture)
{
	this->_texture = texture;
}