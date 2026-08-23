#include "misc/GraphicsContext.h"
#include "raygui.h"

static GraphicsContext g_instance;

GraphicsContext& GraphicsContext::Instance()
{
    return g_instance;
}

GraphicsContext::GraphicsContext():m_PenColor(colors[black]),
             m_PenThickness(1.0f),
             m_BrushColor(colors[black]),
             m_bBrushHollow(false),
             m_TextColor(colors[black]),
             m_bDrawing(false)
{
}

static Rectangle ToRaylibRect(const Rect2D& r)
{
    return Rectangle{(float)r.x, (float)r.y, (float)r.w, (float)r.h};
}

void GraphicsContext::GuiPanel(Rect2D bounds, const char* text)
{
    ::GuiPanel(ToRaylibRect(bounds), text);
}

void GraphicsContext::GuiLabel(Rect2D bounds, const char* text)
{
    ::GuiLabel(ToRaylibRect(bounds), text);
}

bool GraphicsContext::GuiButton(Rect2D bounds, const char* text)
{
    return ::GuiButton(ToRaylibRect(bounds), text) != 0;
}

void GraphicsContext::GuiCheckBox(Rect2D bounds, const char* text, bool* checked)
{
    ::GuiCheckBox(ToRaylibRect(bounds), text, checked);
}

void GraphicsContext::GuiListView(Rect2D bounds, const char* text, int* scrollIndex, int* active)
{
    ::GuiListView(ToRaylibRect(bounds), text, scrollIndex, active);
}
