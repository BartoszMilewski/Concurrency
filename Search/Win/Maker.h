#if !defined (MAKER_H)
#define MAKER_H

#include <string>
#include "Win.h"
#include "Controller.h"

namespace Win
{
    class Maker
    {
    public:
        Maker(std::wstring const & className, HINSTANCE hInst);
        HWND Create(Controller & controller, std::wstring const & title);
        void SetRect(int w, int h) { _width = w; _wineight = h; }
    protected:
        HINSTANCE    _winInst;        // program instance
        std::wstring _className;    // name of Window class
        DWORD        _style;        // window style
        DWORD        _exStyle;      // window extended style
        int          _x;            // horizontal position of window
        int          _y;            // vertical position of window
        int          _width;        // window width  
        int          _wineight;       // window height
        HWND         _winParent;    // handle to parent or owner window
        HMENU        _menu;         // handle to menu, or child-window id
        void *       _data;         // pointer to window-creation data
    };

    class ChildMaker : public Maker
    {
    public:
        ChildMaker(std::wstring const & className, Win::Dow winParent, int childId);
        HWND Create(std::wstring const & text);
    };
}

#endif