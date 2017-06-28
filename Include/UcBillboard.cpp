#include "UcBillboard.h"
#include "UcTextureMgr.h"
#include "UcCamera.h"
NS_UNICORN;

const int Billboard::DEFAULT_ROW = 10;
const int Billboard::DEFAULT_COLLUM = 10;

Billboard::Billboard() :
RenderableObject(),
_texture(NULL),
_vbo(INVALID_OGL_VALUE),
_isFixed(true),
_size(Vector2(1.0f, 1.0f)),
_scale(Vector2(1.0f, 1.0f))
{

}

Billboard::~Billboard()
{
	glDeleteBuffers(1, &_vbo);
}

bool Billboard::initialize(const char* tex, const Vector3& pos)
{
	//initialize the shader will be used
	if (!ShaderMgr::DEFAULT_BILLBOARD)
	{
		ShaderMgr::DEFAULT_BILLBOARD = 
			ShaderMgr::getInstance()->createShaderProgram(ShaderMgr::DEFAULT_BILLBOARD_VS,
														  ShaderMgr::DEFAULT_BILLBOARD_FS);
	}
	_shader = ShaderMgr::DEFAULT_BILLBOARD;
	

	_texture = TextureMgr::getInstance()->createTexture(tex);
	if (!_texture->load() || !_texture)
	{
		//log error
		return false;
	}
	else
		_textureUnit = TextureMgr::getNextTextureTarget();

	//
	_transform.setPosition(pos);
	//else setup buffers
	this->_setup();

	return true;
}

void Billboard::onPreRender(Camera* cam)
{
	//glDisable(GL_BLEND);
	//use billboard shader (vs fs gs)
	_shader->apply();
	//set attributes of shader
	_shader->setVector3("billboardPosition_WS", _transform.Position(), true);
	_shader->setVector2("scaleFactor", _scale, true);
	_shader->setMatrix4("VP", cam->getProjectionMatrix()* cam->getViewMatrix()* _transform.getModel(), true);	
	_shader->setInterger("isFixed", _isFixed? 1: 0 , true);
	//
	_texture->bind();
	_shader->setInterger("colorMap", _texture->getTextureHandler(), true);

}

void Billboard::draw(float dt)
{
	//enable the attribute which loc == 0
	//glEnableVertexAttribArray(0);
	
	//glBindBuffer(GL_ARRAY_BUFFER, _vbo); //bind

	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


}

void Billboard::onPostRender()
{
	//unbind
	glBindVertexArray(0); 
	_texture->unbind();

	//glDisableVertexAttribArray(0);
	
	//glEnable(GL_BLEND);
	//ordinary linear blend
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Billboard::destroy()
{
	if (_texture)
	{
		_texture->destroy();
		UCSafeDelete(_texture);
	}
	delete this;
}

void Billboard::_setup()
{
	//
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);

	//setup billboard vbo
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(RenderData::billboard),RenderData::billboard, GL_STATIC_DRAW);

	glBindVertexArray(_vao);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0); // position 
	glEnableVertexAttribArray(0);
	

	glBindVertexArray(0);
}

void Billboard::setRelativePosition(const Vector3& pos)
{
	_transform.setPosition(pos); 
}

void Billboard::setFixed(const bool& fixed)
{
	_isFixed = fixed;
}

void Billboard::setBillboardScale(const Vector2& scale)
{
	_scale = scale;
	_transform.scale(Vector3(_scale.x, _scale.y , 1.0f));
}

void Billboard::setBillboardSize(const Vector2& size)
{
	_size = size;
}

Vector2 Billboard::getBillboardScale() const
{
	return _scale;
}

bool Billboard::isFixed() const
{
	return _isFixed;
}

Vector2 Billboard::getBillboardSize() const
{
	return _size;
}

Vector3 Billboard::getRelativePosition() const
{
	return _transform.Position();
}

void Billboard::setTexture(const char* path)
{
	TextureMgr::getInstance()->loadTexture(path, false);
}