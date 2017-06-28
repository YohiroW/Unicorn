#ifndef _UC_TEXMAP_H_
#define _UC_TEXMAP_H_
//
#include "UcObject.h"

namespace Unicorn
{
	enum TextureMapType
	{
		NORMAL,
		PARALLEL,
		SHADOW,
		LIGHT,
		SPECULAR,
		O_O		 //wait for updating
	};

	//
	class TextureMap
	{
	public:
		//realized by the class driven
		virtual ~TextureMap();

		//interfaces
		virtual void bind() = 0;
		virtual void unbind() = 0;
	
	protected:
		TextureID _textureId;
		unsigned int _textureUnit;
	};
}

#endif