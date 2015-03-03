#if !defined (MOUSE_H)
#define MOUSE_H
#include <windows.h>

namespace Win
{
    class KeyState
    {
    public:
        KeyState(WPARAM wParam) : _data(wParam)
        {}
        bool IsCtrl() const    { return (_data & MK_CONTROL) != 0; }
        bool IsShift() const   { return (_data & MK_SHIFT) != 0; }
        bool IsLButton() const { return (_data & MK_LBUTTON) != 0; }
        bool IsMButton() const { return (_data & MK_MBUTTON) != 0; }
        bool IsRButton() const { return (_data & MK_RBUTTON) != 0; }
    private:
        WPARAM	_data;
    };
}

#endif
