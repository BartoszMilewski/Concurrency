#if !defined (ICON_H)
#define ICON_H
#include <Windows.h>

class Icon
{
public:
    Icon(HINSTANCE res,
        int id,
        int dx = 0,
        int dy = 0,
        unsigned flag = LR_DEFAULTCOLOR)
    {
        Load(res, id, dx, dy, flag);
    }
    ~Icon();
    operator HICON () const { return _win; }
protected:
    Icon() : _win(0) {}
    void Load(HINSTANCE res,
        int id,
        int dx = 0,
        int dy = 0,
        unsigned flag = LR_DEFAULTCOLOR);
protected:
    HICON _win;
};

class SmallIcon : public Icon
{
public:
    SmallIcon() {}
    SmallIcon(HINSTANCE res, int id);
    void Load(HINSTANCE res, int id);
};

class StdIcon : public Icon
{
public:
    StdIcon() {}
    StdIcon(HINSTANCE res, int id);
    void Load(HINSTANCE res, int id);
};

#endif