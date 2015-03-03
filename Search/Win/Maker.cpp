#include "Maker.h"

Win::Maker::Maker(std::wstring const & className, HINSTANCE hInst)
: _style(WS_OVERLAPPEDWINDOW),
_exStyle(0),
_className(className),
_x(CW_USEDEFAULT), // horizontal position of window
_y(0),             // vertical position of window
_width(CW_USEDEFAULT), // window width  
_wineight(0),        // window height
_winParent(0),    // handle to parent or owner window
_menu(0),         // handle to menu, or child-window identifier
_data(0),          // pointer to window-creation data
_winInst(hInst)
{
}

HWND Win::Maker::Create(Controller & controller, std::wstring const & title)
{
    HWND win = ::CreateWindowEx(
        _exStyle,
        _className.c_str(),
        title.c_str(),
        _style,
        _x,
        _y,
        _width,
        _wineight,
        _winParent,
        _menu,
        _winInst,
        &controller);

    if (win == 0)
        throw "Internal error: Window Creation Failed.";
    return win;
}


Win::ChildMaker::ChildMaker(std::wstring const & className, Win::Dow winParent, int childId)
: Maker(className, winParent.GetInstance())
{
    _style = WS_CHILD;
    _winParent = winParent.handle();
    _menu = reinterpret_cast<HMENU> (childId);
}

HWND Win::ChildMaker::Create(std::wstring const & text)
{
    HWND win = ::CreateWindowEx(
        _exStyle,
        _className.c_str(),
        text.c_str(),
        _style,
        _x,
        _y,
        _width,
        _wineight,
        _winParent,
        _menu,
        _winInst,
        0);

    if (win == 0)
        throw "Internal error: Child Window Creation Failed.";
    return win;
}

