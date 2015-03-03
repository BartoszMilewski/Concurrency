#if !defined (CONTROLS_H)
#define CONTROLS_H
#include "Win.h"
#include "Maker.h"
#include <windows.h>
#include <commctrl.h>
#include <string>

namespace Win
{
    class SimpleCtrl : public Win::Dow
    {
    public:
        SimpleCtrl(HWND winParent, int id)
            : Win::Dow(::GetDlgItem(winParent, id)), _id(id)
        {}

        SimpleCtrl(HWND win = 0)
            : Win::Dow(win), _id(0)
        {}

        void Init(HWND winParent, int id)
        {
            Init(::GetDlgItem(winParent, id));
            _id = id;
        }
        void Init(HWND win)
        {
            Dow::Init(win);
            _id = 0;
        }
        // code is the HIWORD (wParam)
        static bool IsClicked(int code)
        {
            return code == BN_CLICKED;
        }
        int GetId() const { return _id; }
    private:
        int _id;
    };

    class ControlMaker : public ChildMaker
    {
    public:
        ControlMaker(std::wstring const & className, HWND winParent, int id)
            : ChildMaker(className, winParent, id)
        {
            _exStyle = WS_EX_CLIENTEDGE;
            _style = WS_CHILD | WS_VISIBLE;
        }
    };
}
#endif
