#include "MsgLoop.h"

using namespace Win;

int MsgPrepro::Pump ()
{
    MSG  msg;
	int status;
    while ((status = ::GetMessage (&msg, 0, 0, 0 )) != 0)
    {
		if (status == -1)
			throw "Error in the Windows message loop";
		if (!::TranslateAccelerator (_winTop, 0, &msg))
		{
			::TranslateMessage (&msg);
			::DispatchMessage (&msg);
		}
    }
    return msg.wParam;
}