#ifndef UC_OBJECT_H
#define UC_OBJECT_H
//
#include <string>
#include <map>
#include <hash_map>
#include "UcConfig.h"
#include "UcMacros.h"
#include "UcLogger.h"

namespace Unicorn
{
	class Object
	{
	public:
		typedef std::map<std::string, Object*> ObjectMap;
	public:
		//
		virtual ~Object();
		//
		GEN_FUNC(std::string, _name, Name);
		void setEnabled(bool isEnable);
		bool isEnabled() const;
		//
		virtual void onEnable();
		virtual void onDisable();
		virtual void onDestroy();
		//
		virtual bool equal(const Object* obj) const;
		//This method should be override by the class drived
		virtual void destroy();

		int getHashCode() const;

		static Object* findObjectByName(const std::string& name);		
		
	protected:
		Object();
		Object(const Object& obj);
		//
		int _hash(const char* key);
	
	protected:
		//
		bool _isEnable;
		//
		std::string _name;
		//
		int _hashCode;


	private:
		//global object sets
		static ObjectMap _objSets;
	};

}

#endif