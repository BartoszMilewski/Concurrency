#include "Edit.h"


std::wstring Win::Edit::GetText() const
{
    int len = GetLen();
    std::wstring val;
    if (len > 0)
    {
        val.reserve(len + 1);
        val.resize(len);
        GetText(&val[0], len + 1);
    }
    return val;
}

void Win::Edit::Append(std::wstring const & buf)
{
    int len = GetLen();
    Select(len, -1);
    SendMessage(EM_REPLACESEL, 0, reinterpret_cast<LPARAM> (&buf[0]));
}

void Win::Edit::SelectLine(int lineNo)
{
    int lineStart = SendMessage(EM_LINEINDEX, lineNo);
    int lineLen = SendMessage(EM_LINELENGTH, lineNo);
    Select(lineStart, lineStart + lineLen);
}

void Win::Edit::Clear()
{
    Select();
    SendMessage(WM_CLEAR, 0, 0);
}
