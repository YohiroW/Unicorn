#ifndef _UC_MATERIAL_H_
#define _UC_MATERIAL_H_
//
#include "UcObject.h"

namespace Unicorn
{
	class Material: public Object
	{
	public:
		virtual ~Material();
		//
		void setEmission(const float& factor);
		float getEmission() const;
		void setAmbient(const float& factor);
		float getAmbient() const;
		void setDiffuse(const float& factor);
		float getDiffuse() const;
		void setSpecular(const float& factor);
		float getSpecular() const;
		void setShine(const float& factor);
		float getShine() const;
		void setAlpha(const float& factor);
		float getAlpha() const;
	
	protected:
		Material();


	private:
		float _emis, _ambi, _diff, _spec, _shine, _alpha;
	};
}


#endif
