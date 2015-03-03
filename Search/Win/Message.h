#if !defined (WINMESSAGE_H)
#define WINMESSAGE_H
#include "Win.h"

namespace Win
{
	class Message
	{
	public:
		Message (unsigned int msg, unsigned int wParam = 0, long lParam = 0)
			: _msg (msg),
			  _wParam (wParam),
			  _lParam (lParam),
			  _result (0)
		{}
		void SetLParam (long lParam) { _lParam = lParam; }
		void SetLParam (void const * ptr) { _lParam = reinterpret_cast<LPARAM> (ptr); }
		void SetLParam (Win::Dow win) 
			{ _lParam = reinterpret_cast<LPARAM> (win.handle ()); }
		void SetWParam (unsigned int wParam) { _wParam = wParam; }
		void SetWParam (Win::Dow win) 
			{ _wParam = reinterpret_cast<WPARAM> (win.handle()); }
		void SetResult (long result) { _result = result; }
		void MakeWParam (unsigned int lo, unsigned int hi) { _wParam = MAKEWPARAM (lo, hi); }

		unsigned int GetMsg () const { return _msg; }
		// Revisit: this is not portable
		unsigned int GetWParam () const { return _wParam; }
		void UnpackWParam (unsigned int & lo, unsigned int & hi)
		{
			lo = LOWORD (_wParam);
			hi = HIWORD (_wParam);
		}
		// Revisit: this is not portable
		long GetLParam () const { return _lParam; }
		// Revisit: this is not portable
		long GetResult () const { return _result; }
		bool operator == (Win::Message const & msg) const
		{
			return msg.GetMsg () == GetMsg ();
		}

	protected:
		UINT	_msg;
		WPARAM	_wParam;
		LPARAM	_lParam;
		LRESULT	_result;
	};

	// Create this message up front and send/post it repeatedly
	// possibly resetting its parameters
	class RegisteredMessage: public Message
	{
	public:
		RegisteredMessage (std::wstring const & msgName)
			: Message (::RegisterWindowMessage (msgName.c_str ()))
		{
			if (_msg == 0)
				throw "Cannot register Window message";
		}
		RegisteredMessage (wchar_t * msgName)
			: Message (::RegisterWindowMessage (msgName))
		{
			if (_msg == 0)
				throw "Cannot register Window message";
		}
		void SetWParam (unsigned int wParam)
		{
			_wParam = wParam;
		}
	};
}

#endif
