#include "Procedure.h"
#include "Controller.h"
#include "Win.h"
#include "Mouse.h"
#include "Message.h"

// generic window procedure

LRESULT CALLBACK Win::Procedure(HWND win,
    UINT message,
    WPARAM wParam,
    LPARAM lParam)
{
    Win::Dow h(win);
    Controller * pCtrl = h.GetLong<Controller *>();
    switch (message)
    {
    case WM_NCCREATE:
    {
        CreateData const * create =
            reinterpret_cast<CreateData const *> (lParam);
        pCtrl = static_cast<Controller *> (create->GetCreationData());
        pCtrl->SetWindowHandle(win);
        h.SetLong<Controller *>(pCtrl);
    }
        break;
    case WM_CREATE:
        if (pCtrl->OnCreate(reinterpret_cast<CreateData const *> (lParam)))
            return 0;
        break;
    case WM_DESTROY:
        // We're no longer on screen
        pCtrl->OnDestroy();
        return 0;
    case WM_SETFOCUS:
    {
        HWND wndPrev = reinterpret_cast<HWND> (wParam);
        if (pCtrl->OnFocus(wndPrev))
            return 0;
    }
        break;
    case WM_SIZE:
        if (pCtrl->OnSize(LOWORD(lParam), HIWORD(lParam), wParam))
            return 0;
        break;
    case WM_PAINT:
        if (pCtrl->OnPaint())
            return 0;
        break;
    case WM_COMMAND:
        if (lParam == 0)
        {
            if (pCtrl->OnCommand(LOWORD(wParam), HIWORD(wParam) == 1))
                return 0;
        }
        else
        {
            HWND hCtrl = reinterpret_cast<HWND>(lParam);
            if (pCtrl->OnControl(hCtrl, LOWORD(wParam), HIWORD(wParam)))
                return 0;
        }
        break;
    case WM_KEYDOWN:
        if (pCtrl->OnKeyDown(wParam, lParam))
            return 0;
        break;
    case WM_CHAR:
        if (pCtrl->OnChar(wParam, lParam))
            return 0;
        break;
    default:
        if (0xc000 <= message && message <= 0xffff)
        {
            Message msg(message, wParam, lParam);
            if (pCtrl->OnRegisteredMessage(msg))
            {
                return msg.GetResult();
            }
        }
        break;
    }
    return ::DefWindowProc(win, message, wParam, lParam);
}

// window subclassing procedure

LRESULT CALLBACK Win::SubProcedure(HWND win,
    UINT message,
    WPARAM wParam,
    LPARAM lParam)
{
    Win::Dow h(win);
    SubController * pCtrl = h.GetLong<SubController *>();
    switch (message)
    {
    case WM_KEYDOWN:
        if (pCtrl->OnKeyDown(wParam, lParam))
            return 0;
        break;
    case WM_CHAR:
        if (pCtrl->OnChar(wParam, lParam))
            return 0;
        break;
    }
    return pCtrl->CallPrevProc(message, wParam, lParam);
}
