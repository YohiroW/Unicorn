#ifndef REF_H
#define REF_H
//
#include "UcMacros.h"
namespace Unicorn
{

	class Reference
	{
	public:
		virtual ~Reference();
		//increase reference count ,pair with decRef()
		void incRef();
		//decrease ref count
		void decRef();
		//add object to memory pool 
		void autoCollect();
		//
		void dispose();
		//
		UCInline unsigned int getRefCount() const;
		//
		Reference* operator ->();
	
		bool operator ==(Reference& refObj);
	
		bool operator !=(Reference& refObj);
	
		Reference& operator =(Reference& refObj);

	protected:
		Reference();

		Reference(Reference& refObj);

	private:
		//The count being referenced
		int _count;

		Reference* _refObject;

	};

}
#endif // !REF_H
