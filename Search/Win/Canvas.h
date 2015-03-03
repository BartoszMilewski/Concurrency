#if !defined (CANVAS_H)
#define CANVAS_H
#include <windows.h>
#include <string>

namespace Win
{
    class Canvas
    {
    public:
        operator HDC ()
        {
            return _windc;
        }

        // Point
        void SetPixel(int x, int y, int r = 0, int g = 0, int b = 0)
        {
            ::SetPixel(_windc, x, y, RGB(r, g, b));
        }

        // Line
        void LineTo(int x, int y)
        {
            ::LineTo(_windc, x, y);
        }

        void MoveTo(int x, int y)
        {
            ::MoveToEx(_windc, x, y, 0);
        }

        void Line(int x1, int y1, int x2, int y2)
        {
            ::MoveToEx(_windc, x1, y1, 0);
            ::LineTo(_windc, x2, y2);
        }

        // Text
        void Text(int x, int y, std::wstring str)
        {
            ::TextOut(_windc, x, y, str.c_str(), str.length());
        }

    protected:
        // only derived classes are usable
        Canvas(HDC hdc) :_windc(hdc) {}

        HDC  _windc;
    };

    // Use for painting after WM_PAINT

    class PaintCanvas : public Canvas
    {
    public:
        PaintCanvas(HWND win)
            : Canvas(::BeginPaint(win, &_paint)),
            _win(win)
        {}

        ~PaintCanvas()
        {
            ::EndPaint(_win, &_paint);
        }

        int Top() const    { return _paint.rcPaint.top; }
        int Bottom() const { return _paint.rcPaint.bottom; }
        int Left() const   { return _paint.rcPaint.left; }
        int Right() const  { return _paint.rcPaint.right; }

    protected:

        PAINTSTRUCT _paint;
        HWND        _win;
    };

    // Device Context
    // Use for painting other than WM_PAINT

    class UpdateCanvas : public Canvas
    {
    public:
        UpdateCanvas(HWND win)
            : Canvas(::GetDC(win)),
            _win(win)
        {}

        ~UpdateCanvas()
        {
            ::ReleaseDC(_win, _windc);
        }

    protected:

        HWND _win;
    };

    // use when no window available, or to draw on the display
    class DisplayCanvas : public Canvas
    {
    public:
        DisplayCanvas()
            : Canvas(::CreateDC(L"DISPLAY", 0, 0, 0))
        {}
    };
}

#endif
