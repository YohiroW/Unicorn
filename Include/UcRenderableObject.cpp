#include "UcRenderableObject.h"
#include "UcTextureMgr.h"
#include "UcCamera.h"
#include "UcLogger.h" 
NS_UNICORN;

RenderableObject::RenderableObject(ShaderProgram* shader /*= ShaderMgr::DEFAULT*/,
	Transform transf /*= Transform()*/) :
	_transform(Transform()),
	_shader(ShaderMgr::DEFAULT),
	_isPolygon(false),
	_isLightEnable(false)
{

}

RenderableObject::~RenderableObject()
{
}

bool RenderableObject::initialize()
{

	return true;
}

void RenderableObject::draw(float dt)
{

}

void RenderableObject::onPreRender(Camera* cam)
{
	////shader settings
	//if (!_shader)
	//	ShaderMgr::DEFAULT->apply();
	//else
	//	_shader->apply();

}

void RenderableObject::onPostRender()
{
	
}

void RenderableObject::destroy()
{
	//some shader would be used, so wait for user to delete from shader manager
	//_shader->destroy();
	delete this;
}

void RenderableObject::setTransform(const Transform& transf)
{
	_transform = transf;
}

void RenderableObject::attachTexture(Texture* texture)
{

}

bool RenderableObject::initializeWithTex(const std::string& texPath)
{


	return true;
}

void RenderableObject::setShader(ShaderProgram* shader)
{
	if (!shader)
	{
		Log("ShaderProgram* is nil.");
		return;
	}
	_shader = shader;
}

ShaderProgram* RenderableObject::getShader()
{
	return _shader;
}

Transform RenderableObject::getTransform()
{
	return _transform;
}

void RenderableObject::translate(const Vector3& vec)
{
	_transform.translate(vec);
}

void RenderableObject::rotate(const float& degree, const Vector3& axis)
{
	_transform.rotate(degree, axis);
}

void RenderableObject::rotateWithEuler(const Vector3& euler)
{
	_transform.rotateWithEuler(euler);
}

void RenderableObject::scale(const Vector3& scaleFactor)
{
	_transform.scale(scaleFactor);
}

void RenderableObject::setLightPosition(const Vector3& lightPos)
{
	_lightPos = lightPos;
}

void RenderableObject::castShadow()
{

}

bool RenderableObject::polygonEnable(bool enable)
{
	_isPolygon = enable;

	return _isPolygon;
}

void RenderableObject::enableLight(bool enable)
{
	_isLightEnable = enable;
}

bool RenderableObject::isLightEnable() const
{
	return _isLightEnable;
}
