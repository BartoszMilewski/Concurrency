#include "Ctrl.h"

TopController::TopController()
    :_msgNotify(L"Notify")
{}

bool TopController::OnDestroy()
{
    ::PostQuitMessage(0);
    return true;
}

bool TopController::OnCreate(Win::CreateData const * create)
{
    _view = std::unique_ptr<View>(new View(_win));
    _model = std::unique_ptr<Model>(new Model(_win, _msgNotify, L"c:\\Dropbox\\Video\\Search"));
    return true;
}

bool TopController::OnFocus(Win::Dow winPrev)
{
    _view->SetFocus();
    return true;
}

bool TopController::OnSize(int width, int height, int flags)
{
    if (flags != SIZE_MINIMIZED)
    {
        _view->Size(width, height);
    }
    return true;
}

bool TopController::OnRegisteredMessage(Win::Message & msg)
{
    if (msg == _msgNotify)
    {
        for (;;)
        {
            std::wstring file = _model->GetFileSnc();
            if (file.empty())
                break;
            _view->AddItem(file);
        }
        return true;
    }
    return false;
}

#if ASYNC_IMPL == 0

// Asynchronous implementation

bool TopController::OnControl(Win::Dow control, int controlId, int notifyCode)
{
    if (controlId == IDOK)
    {
        std::wstring str = _view->GetInput();
        _view->Clear();
        Cursor::Holder hourglass(_waitCursor);
        _model->SearchFilesAsync(str);
        return true;
    }
    return false;
}

#else

// Synchronous implementation

bool TopController::OnControl(Win::Dow control, int controlId, int notifyCode)
{
    if (controlId == IDOK)
    {
        std::wstring str = _view->GetInput();
        _view->Clear();
        _model->Clear();
        Cursor::Holder hourglass(_waitCursor);
        _model->SearchFiles(str);
        for (auto str : _model->GetFiles())
            _view->AddItem(str);
        return true;
    }
    return false;
}

#endif

