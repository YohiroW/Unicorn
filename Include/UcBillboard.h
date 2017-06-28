#ifndef _UC_BILLBOARD_H_
#define _UC_BILLBOARD_H_
//
#include "UcRenderableObject.h"
#include "UcTexture.h"
#include "UcRenderData.h"

namespace Unicorn
{
	//which also can be attached to entity
	class Billboard: public RenderableObject
	{
	public:
		//
		static const int DEFAULT_ROW;
		static const int DEFAULT_COLLUM;


	public:
		Billboard();
		~Billboard();
		//
		bool initialize(const char* tex, const Vector3& pos);
		
		virtual void onPreRender(Camera* cam);
		virtual void draw(float dt);
		virtual void onPostRender();
		virtual void destroy();

		void setFixed(const bool& fixed);
		bool isFixed() const;

		void setBillboardScale(const Vector2& scale);
		Vector2 getBillboardScale() const;

		void setBillboardSize(const Vector2& size);
		Vector2 getBillboardSize() const;

		void setRelativePosition(const Vector3& pos);
		Vector3 getRelativePosition() const;

		void setTexture(const char* path);

	protected:
		//to setup position buffers
		void _setup();

	private:
		//biilboard vbo
		GLuint _vbo;
		GLuint _vao;
		Texture* _texture;
		bool _isFixed;
		Vector2 _size;
		Vector2 _scale;


		//
		GLuint _textureUnit;
	};
}
#endif