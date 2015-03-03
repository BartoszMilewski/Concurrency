#if !defined (MSGLOOP_H)
#define MSGLOOP_H
#include <windows.h>
#include <list>

namespace Win
{
	class MsgPrepro
	{
		typedef std::list<HWND>::iterator DlgIter;
	public:
		MsgPrepro ()
			: _winTop (0)
		{}
		int Pump ();
	private:
		HWND	_winTop;
	};
}

#endif
