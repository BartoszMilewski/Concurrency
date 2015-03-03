#if !defined (CLASS_H)
#define CLASS_H
#include <Windows.h>
#include <string>
#include "Icon.h"

namespace Win
{
    class ClassMaker
    {
    public:
        ClassMaker(WNDPROC WinProcedure,
            std::wstring const & className,
            HINSTANCE hInst);
        void Register()
        {
            if (::RegisterClassEx(&_class) == 0)
                throw "RegisterClass failed";
        }
        void SetIcons(int id);
    private:
        WNDCLASSEX _class;
        StdIcon       _stdIcon;
        SmallIcon     _smallIcon;
    };
}

#endif
