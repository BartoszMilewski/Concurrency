#include "Font.h"
#include "Canvas.h"

void Font::Stock::GetTextSize(int &width, int &height)
{
    Win::DisplayCanvas canvas;
    Font::Holder font(canvas, *this);
    TEXTMETRIC metric;
    ::GetTextMetrics(canvas, &metric);
    width = metric.tmAveCharWidth;
    height = metric.tmHeight + metric.tmExternalLeading;
}
