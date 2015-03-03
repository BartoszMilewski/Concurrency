#include "Win.h"
#include "Controller.h"
#include "Procedure.h"
#include "Message.h"

bool Win::Dow::PostMsg(Message const & msg) const
{
    return ::PostMessage(handle(), msg.GetMsg(), msg.GetWParam(), msg.GetLParam()) != FALSE;
}

void Win::Dow::SubClass(SubController * subCtrl)
{
    // get previous window procedure and controller (if any)
    ProcPtr prevProc = GetLong<ProcPtr>(GWL_WNDPROC);
    Controller * prevCtrl = GetLong<Controller *>();
    // remember them in the new controller
    subCtrl->Init(_win, prevProc, prevCtrl);
    // attach new controller to window
    SetLong<Controller *>(subCtrl);
    // attach new window procedure to window
    SetLong<ProcPtr>(SubProcedure, GWL_WNDPROC);
}

void Win::Dow::UnSubClass()
{
    // Get the current subclass controller
    SubController * pCtrl = GetLong<SubController *>();
    // restore previous window procedure and controller (if any)
    SetLong<ProcPtr>(pCtrl->GetPrevProc(), GWL_WNDPROC);
    SetLong<Controller *>(pCtrl->GetPrevController());
}
