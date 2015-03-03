#if !defined (LISTBOX_H)
#define LISTBOX_H
#include "Controls.h"

namespace Win
{
    class ListBox : public SimpleCtrl
    {
    public:
        ListBox(HWND winParent, int id)
            : SimpleCtrl(winParent, id)
        {}
        ListBox(HWND win = 0) : SimpleCtrl(win) {}
        void Init(HWND winParent, int id)
        {
            SimpleCtrl::Init(winParent, id);
        }
        ~ListBox()
        {
            Clear();
        }
        void Init(HWND win)
        {
            SimpleCtrl::Init(win);
        }
        bool IsSelection()
        {
            return SendMessage(LB_GETCURSEL) != LB_ERR;
        }
        int GetCount()
        {
            return SendMessage(LB_GETCOUNT);
        }
        void Clear()
        {
            SendMessage(LB_RESETCONTENT);
        }
        void InsertString(int idx, std::wstring const & str)
        {
            SendMessage(LB_INSERTSTRING, idx, reinterpret_cast<LPARAM> (str.c_str()));
        }
        int AddString(std::wstring const & str)
        {
            return SendMessage(LB_ADDSTRING, 0, reinterpret_cast<LPARAM> (str.c_str()));
        }
        void DeleteString(int idx)
        {
            SendMessage(LB_DELETESTRING, idx);
        }
        void ReplaceString(int idx, std::wstring const & str)
        {
            DeleteString(idx);
            InsertString(idx, str);
        }
        int GetData(int idx)
        {
            return SendMessage(LB_GETITEMDATA, idx);
        }
        void SetData(int idx, int value)
        {
            SendMessage(LB_SETITEMDATA, idx, value);
        }
        int GetTextLen(int idx)
        {
            return SendMessage(LB_GETTEXTLEN, idx);
        }
        std::wstring GetText(int idx)
        {
            int len = GetTextLen(idx);
            std::wstring str;
            str.reserve(len + 1);
            str.resize(len);
            SendMessage(LB_GETTEXT, idx, reinterpret_cast<LPARAM> (&str[0]));
            return str;
        }
        void ListDirectory(Win::Dow dlg,
            wchar_t * pathBuf,
            int idStatic = 0, // to display drive and directory
            unsigned fileTypes = DDL_DIRECTORY | DDL_DRIVES)
        {
            if (::DlgDirList(dlg.handle(), pathBuf, GetId(), idStatic, fileTypes) == 0)
                throw "Error Listing Directory.";
        }
        // true, if directory
        bool GetSelectedPath(Win::Dow dlg,
            wchar_t * pathBuf,
            int bufLen)
        {
            return DlgDirSelectEx(dlg.handle(), pathBuf, bufLen, GetId()) != 0;
        }
    };

    class ListBoxMaker : public ControlMaker
    {
    public:
        ListBoxMaker(HWND winParent, int id)
            : ControlMaker(L"LISTBOX", winParent, id)
        {
            _style |= LBS_NOINTEGRALHEIGHT;
        }
    };
}

#endif
