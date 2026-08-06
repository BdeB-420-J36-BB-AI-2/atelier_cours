#include "misc/GraphicsContext.h"

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
