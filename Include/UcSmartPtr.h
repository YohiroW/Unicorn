#ifndef UC_SMART_PTR
#define UC_SMART_PTR

#include "UcMacros.h"
#include "UcObject.h"

namespace Unicorn
{
	template<class T>
	class SmartPtr
	{
	public:
		SmartPtr();
		SmartPtr(T* ptr);
		~SmartPtr();
		SmartPtr(const SmartPtr<T>& ptr);

		T* operator->();
		bool operator==(const SmartPtr<T>& ptr);
		bool operator!=(const SmartPtr<T>& ptr);
		SmartPtr<T>& operator=(const SmartPtr<T>& ptr);

		inline int SmartPtr::getRefCount() const;
		//
		inline T* getReference() const{
			return _refPtr;
		}
		//
		inline bool isNull() const{
			return _refPtr == NULL;
		}

	private:
		int* _refCount;	
		T* _refPtr;
	};
}


#endif