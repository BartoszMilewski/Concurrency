#if !defined CURSOR_H
#define CURSOR_H
#include <Windows.h>
#include <string>

namespace Cursor
{
    class Handle
    {
    public:
        Handle(HCURSOR h = 0)
            : _win(h)
        {}
        HCURSOR handle()
        {
            return _win;
        }
    private:
        HCURSOR _win;
    };
    
    class System : public Handle
	{
	public:
		System (LPCWSTR cursorId)
			: Handle(::LoadCursor (0, cursorId))
		{}
	};

	class Hourglass : public System
	{
	public:
		Hourglass () : System (IDC_WAIT) {}
	};

	class Arrow : public System
	{
	public:
		Arrow () : System (IDC_ARROW) {}
	};

	class SizeWE : public System
	{
	public:
		SizeWE () : System (IDC_SIZEWE) {}
	};

	class SizeNS : public System
	{
	public:
		SizeNS () : System (IDC_SIZENS) {}
	};

	class Holder
	{
	public:
		Holder () : _oldCursor (0) {}
		Holder (Handle newCursor)
		{
			Set (newCursor);
		};
		~Holder ()
		{
			Restore ();
		}
		void Set (Handle cursor)
		{
			_oldCursor = ::SetCursor (cursor.handle());
		}
		void Restore ()
		{
			::SetCursor (_oldCursor.handle());
		}

	private:
		Handle _oldCursor;
	};
}

#endif
