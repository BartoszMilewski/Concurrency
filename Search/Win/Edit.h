#if !defined (EDIT_H)
#define EDIT_H
#include "Controls.h"
#include <string>

namespace Win
{
    class StaticText : public SimpleCtrl
    {
    public:
        StaticText(HWND winParent, int id)
            : SimpleCtrl(winParent, id)
        {}
    };

    class EditReadOnly : public SimpleCtrl
    {
    public:
        EditReadOnly(HWND winParent, int id)
            : SimpleCtrl(winParent, id)
        {}

        void Select(int offStart, int offEnd)
        {
            SendMessage(EM_SETSEL, (WPARAM)offStart, (LPARAM)offEnd);
        }
    };

    class Edit : public SimpleCtrl
    {
    public:
        Edit(HWND winParent, int id)
            : SimpleCtrl(winParent, id)
        {}

        Edit(HWND win = 0) : SimpleCtrl(win) {}

        void Append(std::wstring const & buf);

        void Select(int offStart, int offEnd)
        {
            SendMessage(EM_SETSEL, (WPARAM)offStart, (LPARAM)offEnd);
        }

        void SetReadonly(bool flag)
        {
            SendMessage(EM_SETREADONLY, (WPARAM)(flag ? TRUE : FALSE), 0);
        }

        // code is the HIWORD (wParam)
        static bool IsChanged(int code)
        {
            return code == EN_CHANGE;
        }

        int GetLen() const
        {
            return SendMessage(WM_GETTEXTLENGTH);
        }

        int GetLineCount()
        {
            return SendMessage(EM_GETLINECOUNT);
        }

        void GetText(wchar_t * buf, int len) const
        {
            SendMessage(WM_GETTEXT, (WPARAM)len, (LPARAM)buf);
        }

        std::wstring GetText() const;

        void Select()
        {
            SendMessage(EM_SETSEL, 0, -1);
        }

        void SelectLine(int lineIdx);
        void ReplaceSelection(wchar_t * info)
        {
            SendMessage(EM_REPLACESEL, 0, reinterpret_cast<LPARAM>(info));
        }
        void Clear();
    };

    class EditMaker : public ControlMaker
    {
    public:
        EditMaker(HWND winParent, int id) : ControlMaker(L"EDIT", winParent, id)
        {}
        void MakeReadOnly() { _style |= ES_READONLY; }
        void WantReturn() { _style |= ES_WANTRETURN; }
    };
}
#endif
