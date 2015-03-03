#if !defined (VIEW_H)
#define VIEW_H
#include "Win/ListBox.h"
#include "Win/Edit.h"
#include "Win/Win.h"
class Calculator;

class EditController : public Win::SubController
{
public:
    bool OnKeyDown(int vKey, int flags);
    bool OnChar(int vKey, int flags);
};

class View
{
public:
    View(Win::Dow winTop);
    void Size(int width, int height);
    std::wstring GetInput()
    {
        return _edit.GetText();
    }
    void SetFocus()
    {
        _edit.SetFocus();
    }
    void Clear();
    void AddItem(std::wstring const & str);
private:
    int _charWidth;
    int _charHeight;

    Win::ListBox	_list;
    Win::Edit		_edit;

    EditController	_editCtrl;
};
#endif
