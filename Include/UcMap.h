#ifndef _UC_MAP_H_
#define _UC_MAP_H_
//

namespace Unicorn
{
	enum MapType
	{
		DIFFUSE_MAP,
		EMISSION_MAP,
		NORMAL_MAP,
	};


	//base class 
	class Map
	{
	public:

	protected:
		MapType _type;
	};
}

#endif