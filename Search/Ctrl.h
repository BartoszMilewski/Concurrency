#include "Win/Controller.h"
#include "Win/Cursor.h"
#include "Win/Message.h"
#include "View.h"
#include "Model.h"
#include <memory>

class TopController : public Win::Controller
{
public:
    TopController();
    bool OnCreate(Win::CreateData const * create);
    bool OnDestroy();
    bool OnFocus(Win::Dow winPrev);
    bool OnSize(int width, int height, int flags);
    bool OnControl(Win::Dow control, int controlId, int notifyCode);
    bool OnRegisteredMessage(Win::Message & msg);
private:
    std::unique_ptr<View> _view;
    std::unique_ptr<Model> _model;
    Cursor::Hourglass _waitCursor;
    Win::RegisteredMessage _msgNotify;
};
