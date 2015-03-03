#include "Icon.h"

Icon::~Icon()
{
    ::DestroyIcon(_win);
}

void Icon::Load(HINSTANCE res, int id, int dx, int dy, unsigned flag)
{
    _win = reinterpret_cast<HICON> (
        ::LoadImage(res,
        MAKEINTRESOURCE(id),
        IMAGE_ICON,
        dx, dy,
        flag));
    if (_win == 0)
        throw "Icon load image failed";
}

void SmallIcon::Load(HINSTANCE res, int id)
{
    Icon::Load(res, id,
        ::GetSystemMetrics(SM_CXSMICON),
        ::GetSystemMetrics(SM_CYSMICON));
}

void StdIcon::Load(HINSTANCE res, int id)
{
    Icon::Load(res, id,
        ::GetSystemMetrics(SM_CXICON),
        ::GetSystemMetrics(SM_CYICON));
}
