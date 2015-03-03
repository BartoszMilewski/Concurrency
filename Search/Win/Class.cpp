#include "Class.h"
#include "Procedure.h"

Win::ClassMaker::ClassMaker
(WNDPROC winProcedure, std::wstring const & className, HINSTANCE hInst)
{
    _class.lpfnWndProc = winProcedure;// window procedure: mandatory
    _class.hInstance = hInst;         // owner of the class: mandatory
    _class.lpszClassName = className.c_str(); // mandatory
    _class.cbSize = sizeof (WNDCLASSEX);
    _class.hCursor = ::LoadCursor(0, IDC_ARROW);
    _class.hbrBackground = 0;
    _class.style = 0;
    _class.cbClsExtra = 0;
    _class.cbWndExtra = 0;
    _class.hIcon = 0;
    _class.hIconSm = 0;
    _class.lpszMenuName = 0;
}

void Win::ClassMaker::SetIcons(int id)
{
    _stdIcon.Load(_class.hInstance, id);
    _smallIcon.Load(_class.hInstance, id);
    _class.hIcon = _stdIcon;
    _class.hIconSm = _smallIcon;
}
