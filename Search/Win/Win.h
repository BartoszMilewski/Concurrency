#if !defined (WIN_H)
#define WIN_H
#include <windows.h>
#include <string>
#include <vector>

namespace Win
{
    class SubController;
    class Message;

    class Dow
    {
    public:
        Dow(HWND win = 0) : _win(win) {}
        void Init(HWND win) { _win = win; }
        HWND handle() const { return _win; }
        Win::Dow GetParent() { return ::GetParent(_win); }
        HINSTANCE GetInstance() const
        {
            return reinterpret_cast<HINSTANCE> (
                ::GetWindowLong(_win, GWL_HINSTANCE));
        }
        template <class T>
        inline T GetLong(int which = GWL_USERDATA)
        {
            return reinterpret_cast<T> (::GetWindowLong(_win, which));
        }

        template <class T>
        inline void SetLong(T value, int which = GWL_USERDATA)
        {
            ::SetWindowLong(_win, which, reinterpret_cast<long> (value));
        }
        LRESULT SendMessage(UINT msg, WPARAM wparam = 0, LPARAM lparam = 0) const
        {
            return ::SendMessage(_win, msg, wparam, lparam);
        }
        bool PostMessage(UINT msg, WPARAM wparam = 0, LPARAM lparam = 0) const
        {
            return ::PostMessage(_win, msg, wparam, lparam) != FALSE;
        }
        bool PostMsg(Message const & msg) const;
        void Destroy()
        {
            ::DestroyWindow(_win);
        }
        // Focus
        void SetFocus()
        {
            ::SetFocus(_win);
        }
        bool HasFocus() const
        {
            return ::GetFocus() == _win;
        }
        // Capture
        void CaptureMouse()
        {
            ::SetCapture(_win);
        }
        void ReleaseMouse()
        {
            if (HasCapture())
                ::ReleaseCapture();
        }
        bool HasCapture() const
        {
            return ::GetCapture() == _win;
        }
        // Text/Caption
        void SetText(std::wstring const & text)
        {
            ::SetWindowText(_win, text.c_str());
        }
        std::wstring GetText() const
        {
            int len = ::GetWindowTextLength(_win);
            std::wstring buf;
            if (len > 0)
            {
                buf.reserve(len + 1);
                buf.resize(len);
                ::GetWindowText(_win, &buf[0], len + 1);
            }
            return buf;
        }
        // Font
        void SetFont(HFONT hFont)
        {
            BOOL fRedraw = TRUE;
            SendMessage(WM_SETFONT,
                reinterpret_cast<WPARAM> (hFont),
                MAKELPARAM(fRedraw, 0));
        }
        // Window visibility
        void Show(int cmdShow = SW_SHOW)
        {
            ::ShowWindow(_win, cmdShow);
        }
        void Hide()
        {
            ::ShowWindow(_win, SW_HIDE);
        }
        void Update()
        {
            ::UpdateWindow(_win);
        }
        void Display(int cmdShow = SW_SHOW)
        {
            Show(cmdShow);
            Update();
        }
        void Enable()
        {
            ::EnableWindow(_win, TRUE);
        }
        void Disable()
        {
            ::EnableWindow(_win, FALSE);
        }
        // Moving
        void Move(int x, int y, int width, int height)
        {
            ::MoveWindow(_win, x, y, width, height, TRUE);
        }
        // Subclassing
        void SubClass(SubController * ctrl);
        void UnSubClass();
    protected:
        HWND _win;
    };
}
#endif
