#ifndef _UC_CAMERA_MAIN_H_
#define _UC_CAMERA_MAIN_H_
//
#include "UcCamera.h"
#include "UcMatrix.h"

namespace Unicorn
{
	class MainCamera: public Camera
	{
	public:
		//
		~MainCamera();
		//
		static MainCamera* getInstance();
		//



	private:
		//
		MainCamera();
		bool initialize();

	private:
		//
		static MainCamera* _instance;


	};
}


#endif