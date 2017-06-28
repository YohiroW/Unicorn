#ifndef _UC_RANDDOM_TEX_H_
#define _UC_RANDDOM_TEX_H_
//
#include "UcTexture.h"
#include "UcObject.h"
#include "UcVector3.h"


namespace Unicorn
{
	class RandomTexture: public Object
	{
	public:
		RandomTexture();
		~RandomTexture();
		//
		bool initialize(const int& size);
		virtual void destroy();

		void bind(const TextureUnit& unit);
		TextureID getTextureHandler() const;

	private:
		float _getRandomFloat() const;


	private:
		GLuint _texHandler;
		
	};
}


#endif