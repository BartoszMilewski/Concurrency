#if !defined (FONT_H)
#define FONT_H
#include <windows.h>

namespace Win
{
    class StockObject
    {
    public:
        StockObject(int type)
            : _obj(::GetStockObject(type))
        {}
        operator HGDIOBJ () const { return _obj; }
    protected:
        HGDIOBJ _obj;
    };
}

namespace Font
{
    class Stock : public Win::StockObject
    {
    public:
        Stock(int type) : Win::StockObject(type) {}
        operator HFONT () const { return reinterpret_cast<HFONT> (_obj); }
        void GetTextSize(int &width, int &height);
    };

    class SysFixed : public Stock
    {
    public:
        SysFixed() : Stock(SYSTEM_FIXED_FONT) {}
    };

    class OemFixed : public Stock
    {
    public:
        OemFixed() : Stock(OEM_FIXED_FONT) {}
    };

    class Holder
    {
    public:
        Holder(HDC hdc, HFONT font)
            : _windc(hdc)
        {
            _fontOld = reinterpret_cast<HFONT> (::SelectObject(_windc, font));
        }
        ~Holder()
        {
            ::SelectObject(_windc, _fontOld);
        }
    private:
        HDC     _windc;
        HFONT   _fontOld;
    };
}

#endif
