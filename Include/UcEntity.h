/********************************************************************
	created:	2017/03/06
	filename: 	UcEntity.h
	file ext:	h
	author:		Yohiro
	
	purpose:	
*********************************************************************/
#ifndef _UC_ENTITY_H_
#define _UC_ENTITY_H_
//
#include <gl/glew.h>
#include <vector>
#include "UcObject.h"
#include "UcVector3.h"
#include "UcTransform.h"
//
namespace Unicorn
{
	class Scene;
	class RenderableObject;

	class Entity: public Object 
	{
	public:
		typedef std::vector<Object*> ObjectList;
	
	public:
		//
		Entity();
		//
		virtual ~Entity();
		//
		bool initialize(const std::string& name);
		//
		virtual void destroy();
		//
		void attachRenderable(RenderableObject* renderable);
		//
		void setScene(const Scene* scene);
		Scene* getScene() const;
		//
		void setParent(Entity*	parent);
		UCInline Entity* getParent() const; 
		//
		void setPosition(const Vector3& pos);
		Vector3 getPosition() const;
		//
		void setScale(const Vector3& scale);
		Vector3 getScale() const;
		//
		void setEuler(const Vector3& euler);
		Vector3 getEuler() const;
		//
		void rotate(const float& degree, const Vector3& axis);
		//
		Transform getTransform() const;
		//
		RenderableObject* getRenderable() const;
		//
		virtual void update(float dt);
		
	
	protected:
		void _transformToParent(Entity* parent);
		//

	private:
		//everytime you created a new entity ,this func shall be invoked automatically
		static void _addEntity(const Entity* entity);
		//when scene was destroy invoke this, while push scene wont be called
		static void _removeAllEntity();

	private:
		Entity* _parent;
		//
		RenderableObject* _renderable;
		//
		Transform _transform;

	};
}

#endif