#ifndef _UC_RENDERABLE_H_
#define _UC_RENDERABLE_H_
//
#include <gl/glew.h>
#include "UcObject.h"
#include "UcMesh.h"
#include "UcTransform.h"
#include "UcShaderMgr.h"
//assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


namespace Unicorn
{
	class Camera;
	class Texture;

	class RenderableObject :public Object
	{
	public:
		
		virtual ~RenderableObject();
		
		//
		bool initialize();
		bool initializeWithTex(const std::string& texPath);
		//overridable method
		virtual void onPreRender(Camera* cam);
		virtual void onPostRender();
		virtual void draw(float dt);
		//
		virtual void destroy();
		//
		virtual void setLightPosition(const Vector3& lightPos);	
		//
		virtual void attachTexture(Texture* texture);
		//
		virtual void setShader(ShaderProgram* shaderPragma);
		virtual ShaderProgram* getShader();
		virtual void setTransform(const Transform& transf);
		Transform getTransform();
		//
		virtual void translate(const Vector3& vec);
		//rotate with clockwise
		//the former two func use quaternion to rotate, late use euler
		virtual void rotate(const float& degree, const Vector3& axis);
		virtual void rotateWithEuler(const Vector3& euler);
		virtual void scale(const Vector3& scaleFactor);
		
		//when invoked, create shadow map for it
		void castShadow();

		//
		bool polygonEnable(bool enable);
		void enableLight(bool enable);
		bool isLightEnable() const;
		
	protected:
		//
		RenderableObject(ShaderProgram* shader = ShaderMgr::DEFAULT,
			             Transform transf = Transform());

	protected:
		//
		Transform _transform;
		ShaderProgram* _shader;
		Vector3 _lightPos;
		bool _isPolygon;
		bool _isLightEnable;
	};
}

#endif