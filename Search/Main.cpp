#include "Win/Win.h"
#include "Win/Class.h"
#include "Win/Maker.h"
#include "Win/MsgLoop.h"
#include "Ctrl.h"

int WINAPI WinMain
   (HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdParam, int cmdShow)
{
    std::wstring className = L"Search";
    Win::ClassMaker winClass (Win::Procedure, className, hInst);
    winClass.Register ();
    Win::Maker maker (className, hInst);
    maker.SetRect(300, 800);
    TopController ctrl;
    Win::Dow win = maker.Create(ctrl, L"Search");
    win.Display (cmdShow);

    Win::MsgPrepro loop;
    return loop.Pump();
}
