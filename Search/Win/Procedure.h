#if !defined (PROCEDURE_H)
#define PROCEDURE_H
#include <windows.h>
#include <string>

namespace Win
{
    class CreateData : public CREATESTRUCT
    {
    public:
        void * GetCreationData() const { return lpCreateParams; }
        int GetHeight() const { return cy; }
        int GetWidth() const { return cx; }
        int GetX() const { return x; }
        int GetY() const { return y; }
        std::wstring GetWndName() const 
        { 
            return std::wstring(lpszName);
        }
    };

    // Window procedures

    typedef LRESULT(CALLBACK * ProcPtr)
        (HWND win, UINT message, WPARAM wParam, LPARAM lParam);


    LRESULT CALLBACK Procedure
        (HWND win, UINT message, WPARAM wParam, LPARAM lParam);

    LRESULT CALLBACK SubProcedure
        (HWND win, UINT message, WPARAM wParam, LPARAM lParam);
}

#endif
