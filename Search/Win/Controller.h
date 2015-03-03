#if !defined (CONTROLLER_H)
#define CONTROLLER_H
#include "Win.h"
#include "Mouse.h"
#include "Procedure.h"

namespace Win
{
    class Message;

    class Controller
    {
        friend LRESULT CALLBACK Procedure(HWND win,
            UINT message, WPARAM wParam, LPARAM lParam);
    protected:
        void SetWindowHandle(HWND win) { _win.Init(win); }
    public:
        virtual ~Controller() {}
        virtual bool OnCreate(CreateData const * create)
        {
            return false;
        }
        virtual bool OnDestroy()
        {
            return false;
        }
        virtual bool OnSize(int width, int height, int flag)
        {
            return false;
        }
        virtual bool OnFocus(Win::Dow winPrev)
        {
            return false;
        }
        virtual bool OnPaint()
        {
            return false;
        }
        virtual bool OnCommand(int cmdId, bool isAccel)
        {
            return false;
        }
        virtual bool OnControl(Win::Dow control, int controlId, int notifyCode)
        {
            return false;
        }
        // Keyboard
        virtual bool OnKeyDown(int vKey, int flags)
        {
            return false;
        }
        virtual bool OnChar(int vKey, int flags)
        {
            return false;
        }
        virtual bool OnRegisteredMessage(Message & msg)
        {
            return false;
        }
    protected:
        Win::Dow  _win;
    };

    class SubController : public Controller
    {
    public:
        SubController() : _prevProc(0), _prevController(0) {}
        void Init(HWND win, ProcPtr prevProc, Controller * prevCtrl)
        {
            SetWindowHandle(win);
            _prevProc = prevProc;
            _prevController = prevCtrl;
        }
        LRESULT CallPrevProc(UINT message, WPARAM wParam, LPARAM lParam)
        {
            return ::CallWindowProc(_prevProc, _win.handle(), message, wParam, lParam);
        }
        ProcPtr GetPrevProc()
        {
            return _prevProc;
        }
        Controller * GetPrevController()
        {
            return _prevController;
        }
    protected:
        ProcPtr _prevProc;
        Controller * _prevController;
    };
}
#endif
