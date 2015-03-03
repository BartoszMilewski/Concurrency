#include "View.h"
#include "Win/Font.h"

View::View(Win::Dow win)
{
    // Create child windows
    Win::ListBoxMaker listBox(win.handle(), 100);
    _list.Init(listBox.Create(L"List"));
    Win::EditMaker edit(win.handle(), 101);
    _edit.Init(edit.Create(L""));

    _edit.SubClass(&_editCtrl);

    Font::OemFixed fixed;
    fixed.GetTextSize(_charWidth, _charHeight);

    _list.SetFont(fixed);
    _edit.SetFont(fixed);
}

void View::Size(int width, int height)
{
    int wEdit = width;
    int hEdit = _charHeight + 6;

    _edit.Move(0, 0, wEdit, hEdit);

    _list.Move(0, hEdit, wEdit, height - hEdit);
}

void View::AddItem(std::wstring const & str)
{
    _list.AddString(str);
}

void View::Clear()
{
    _edit.Clear();
    _list.Clear();
}

// Turn the return key into IDOK and send to parent
bool EditController::OnKeyDown(int vKey, int flags)
{
    if (vKey == VK_RETURN)
    {
        _win.GetParent().SendMessage(WM_COMMAND,
            MAKEWPARAM(IDOK, 0),
            reinterpret_cast<LPARAM> (_win.handle()));
        return true;
    }
    return false;
};

// Override to suppress the beep
bool EditController::OnChar(int vKey, int flags)
{
    if (vKey == VK_RETURN)
        return true;
    return false;
};

