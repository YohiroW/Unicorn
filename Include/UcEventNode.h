#ifndef _UC_LISTENER_H_
#define _UC_LISTENER_H_
//
#include "UcObject.h"

namespace Unicorn
{
	class Listener: public Object
	{
	public:
		Listener();
		virtual ~Listener();
		//key code can be get by enumator KeyCode,see details in GLEvent
		virtual void onKeyPress(int keyCode, int scanCode, int mode);
		virtual void onKeyRelease(int keyCode, int scanCode, int mode);
		virtual void onMouseMove(double x, double y);
		virtual void onMouseClick(int btn, int action, int modify);
		virtual void onScroll(double offX, double offY);
		//

	};


}


#endif