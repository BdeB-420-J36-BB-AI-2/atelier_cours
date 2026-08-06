#ifndef GRAPHICS_CONTEXT_H
#define GRAPHICS_CONTEXT_H
//------------------------------------------------------------------------
//
//  Name:   GraphicsContext.h
//
//  Desc:   A singleton class that mimics the old GDI-based drawing helper
//          but is backed entirely by raylib. Call each method using the
//          #define for gfx. eg gfx.Line(10, 20, 300, 300)
//          gfx.StartDrawing()/StopDrawing() wrap raylib's own
//          BeginDrawing()/EndDrawing() for the whole frame - call them
//          once per frame, before/after everything else is drawn.
//
//------------------------------------------------------------------------
#include "raylib.h"
#include <string>
#include <vector>
#include <cassert>

#include "2D/Vector2D.h"
#include "2D/Rect2D.h"


//------------------------------- define some colors
const int NumColors = 15;

const Color colors[NumColors] =
{
  Color{255,0,0,255},      //red
  Color{0,0,255,255},      //blue
  Color{0,255,0,255},      //green
  Color{0,0,0,255},        //black
  Color{255,200,200,255},  //pink
  Color{200,200,200,255},  //grey
  Color{255,255,0,255},    //yellow
  Color{255,170,0,255},    //orange
  Color{255,0,170,255},    //purple
  Color{133,90,0,255},     //brown
  Color{255,255,255,255},  //white
  Color{0,100,0,255},      //dark green
  Color{0,255,255,255},    //light blue
  Color{200,200,200,255},  //light grey
  Color{255,230,230,255}   //light pink
};


//make life easier on the fingers
#define gfx GraphicsContext::Instance()

class GraphicsContext
{
  GraphicsContext(const GraphicsContext&) = delete;
  GraphicsContext& operator=(const GraphicsContext&) = delete;

public:

  int NumPenColors()const{return NumColors;}

  //enumerate some colors
  enum
  {
    red,
    blue,
    green,
    black,
    pink,
    grey,
    yellow,
    orange,
    purple,
    brown,
    white,
    dark_green,
    light_blue,
    light_grey,
    light_pink,
    hollow
  };



private:

  //current pen (outline) state
  Color  m_PenColor;
  float  m_PenThickness;

  //current brush (fill) state
  Color  m_BrushColor;
  bool   m_bBrushHollow;

  //current text color
  Color  m_TextColor;

  bool   m_bDrawing;

public:

  static GraphicsContext& Instance();
  GraphicsContext();
  ~GraphicsContext(){}

  void BlackPen(){m_PenColor = colors[black]; m_PenThickness = 1.0f;}
  void WhitePen(){m_PenColor = colors[white]; m_PenThickness = 1.0f;}
  void RedPen()  {m_PenColor = colors[red]; m_PenThickness = 1.0f;}
  void GreenPen(){m_PenColor = colors[green]; m_PenThickness = 1.0f;}
  void BluePen() {m_PenColor = colors[blue]; m_PenThickness = 1.0f;}
  void GreyPen() {m_PenColor = colors[grey]; m_PenThickness = 1.0f;}
  void PinkPen() {m_PenColor = colors[pink]; m_PenThickness = 1.0f;}
  void YellowPen() {m_PenColor = colors[yellow]; m_PenThickness = 1.0f;}
  void OrangePen() {m_PenColor = colors[orange]; m_PenThickness = 1.0f;}
  void PurplePen() {m_PenColor = colors[purple]; m_PenThickness = 1.0f;}
  void BrownPen() {m_PenColor = colors[brown]; m_PenThickness = 1.0f;}

  void DarkGreenPen() {m_PenColor = colors[dark_green]; m_PenThickness = 1.0f;}
  void LightBluePen() {m_PenColor = colors[light_blue]; m_PenThickness = 1.0f;}
  void LightGreyPen() {m_PenColor = colors[light_grey]; m_PenThickness = 1.0f;}
  void LightPinkPen() {m_PenColor = colors[light_pink]; m_PenThickness = 1.0f;}

  void ThickBlackPen(){m_PenColor = colors[black]; m_PenThickness = 2.0f;}
  void ThickWhitePen(){m_PenColor = colors[white]; m_PenThickness = 2.0f;}
  void ThickRedPen()  {m_PenColor = colors[red]; m_PenThickness = 2.0f;}
  void ThickGreenPen(){m_PenColor = colors[green]; m_PenThickness = 2.0f;}
  void ThickBluePen() {m_PenColor = colors[blue]; m_PenThickness = 2.0f;}

  void BlackBrush(){m_BrushColor = colors[black]; m_bBrushHollow = false;}
  void WhiteBrush(){m_BrushColor = colors[white]; m_bBrushHollow = false;}
  void HollowBrush(){m_bBrushHollow = true;}
  void GreenBrush(){m_BrushColor = colors[green]; m_bBrushHollow = false;}
  void RedBrush()  {m_BrushColor = colors[red]; m_bBrushHollow = false;}
  void BlueBrush()  {m_BrushColor = colors[blue]; m_bBrushHollow = false;}
  void GreyBrush()  {m_BrushColor = colors[grey]; m_bBrushHollow = false;}
  void BrownBrush() {m_BrushColor = colors[brown]; m_bBrushHollow = false;}
  void YellowBrush() {m_BrushColor = colors[yellow]; m_bBrushHollow = false;}
  void LightBlueBrush() {m_BrushColor = colors[light_blue]; m_bBrushHollow = false;}
  void DarkGreenBrush() {m_BrushColor = colors[dark_green]; m_bBrushHollow = false;}
  void OrangeBrush() {m_BrushColor = colors[orange]; m_bBrushHollow = false;}



  //--------------------------- Window lifecycle

  //wraps raylib's InitWindow()
  void InitWindow(int width, int height, const char* title)
  {
    ::InitWindow(width, height, title);
  }

  //wraps raylib's CloseWindow()
  void CloseWindow()
  {
    ::CloseWindow();
  }

  //wraps raylib's SetTargetFPS()
  void SetTargetFPS(int fps)
  {
    ::SetTargetFPS(fps);
  }

  //wraps raylib's WindowShouldClose()
  bool WindowShouldClose()
  {
    return ::WindowShouldClose();
  }

  //wraps raylib's GetScreenHeight()
  int GetScreenHeight()
  {
    return ::GetScreenHeight();
  }

  //ALWAYS call this once, before drawing anything else in the frame.
  //Wraps raylib's BeginDrawing().
  void StartDrawing()
  {
    assert(!m_bDrawing);

    m_bDrawing = true;

    BeginDrawing();

    BlackPen();
    BlackBrush();
    m_TextColor = colors[black];
  }

  //clears the frame to the given color. Wraps raylib's ClearBackground().
  void ClearBackground(Color color)
  {
    ::ClearBackground(color);
  }

  //ALWAYS call this once, after everything else in the frame has been
  //drawn. Wraps raylib's EndDrawing().
  void StopDrawing()
  {
    assert(m_bDrawing);

    m_bDrawing = false;

    EndDrawing();
  }


  //---------------------------Text

  void TextAtPos(int x, int y, const std::string &s)
  {
    DrawText(s.c_str(), x, y, 10, m_TextColor);
  }

  void TextAtPos(double x, double y, const std::string &s)
  {
    DrawText(s.c_str(), (int)x, (int)y, 10, m_TextColor);
  }

  void TextAtPos(Vector2D pos, const std::string &s)
  {
    DrawText(s.c_str(), (int)pos.x, (int)pos.y, 10, m_TextColor);
  }

  //raylib always draws text with a transparent background, so these are no-ops
  //kept for API compatibility with the old GDI-backed version
  void TransparentText(){}

  void OpaqueText(){}

  void TextColor(int color){assert(color < NumColors); m_TextColor = colors[color];}
  void TextColor(int r, int g, int b){m_TextColor = Color{(unsigned char)r,(unsigned char)g,(unsigned char)b,255};}


  //----------------------------pixels
  void DrawDot(Vector2D pos, Color color)
  {
    DrawPixel((int)pos.x, (int)pos.y, color);
  }

  void DrawDot(int x, int y, Color color)
  {
    DrawPixel(x, y, color);
  }

  //-------------------------Line Drawing

  void Line(Vector2D from, Vector2D to)
  {
    DrawLineEx(Vector2{(float)from.x, (float)from.y}, Vector2{(float)to.x, (float)to.y}, m_PenThickness, m_PenColor);
  }

  void Line(int a, int b, int x, int y)
  {
    DrawLineEx(Vector2{(float)a, (float)b}, Vector2{(float)x, (float)y}, m_PenThickness, m_PenColor);
  }

  void Line(double a, double b, double x, double y)
  {
    DrawLineEx(Vector2{(float)a, (float)b}, Vector2{(float)x, (float)y}, m_PenThickness, m_PenColor);
  }

  void PolyLine(const std::vector<Vector2D>& points)
  {
    //make sure we have at least 2 points
    if (points.size() < 2) return;

    for (unsigned int p=1; p<points.size(); ++p)
    {
      Line(points[p-1], points[p]);
    }
  }

  void LineWithArrow(Vector2D from, Vector2D to, double size)
  {
    Vector2D norm = Vec2DNormalize(to-from);

    //calculate where the arrow is attached
    Vector2D CrossingPoint = to - (norm * size);

    //calculate the two extra points required to make the arrowhead
    Vector2D ArrowPoint1 = CrossingPoint + (norm.Perp() * 0.4f * size);
    Vector2D ArrowPoint2 = CrossingPoint - (norm.Perp() * 0.4f * size);

    //draw the line
    Line(from, CrossingPoint);

    //draw the arrowhead (filled with the currently selected brush)
    DrawTriangle(Vector2{(float)ArrowPoint1.x, (float)ArrowPoint1.y},
                 Vector2{(float)to.x, (float)to.y},
                 Vector2{(float)ArrowPoint2.x, (float)ArrowPoint2.y},
                 m_bBrushHollow ? m_PenColor : m_BrushColor);
  }

  void Cross(Vector2D pos, int diameter)
  {
    Line((int)pos.x-diameter, (int)pos.y-diameter, (int)pos.x+diameter, (int)pos.y+diameter);
    Line((int)pos.x-diameter,(int)pos.y+diameter, (int)pos.x+diameter, (int)pos.y-diameter);
  }

  //---------------------Geometry drawing methods

  void Rect(int left, int top, int right, int bot)
  {
    if (!m_bBrushHollow)
    {
      DrawRectangle(left, top, right-left, bot-top, m_BrushColor);
    }
    DrawRectangleLinesEx(Rectangle{(float)left, (float)top, (float)(right-left), (float)(bot-top)}, m_PenThickness, m_PenColor);
  }

  void Rect(double left, double top, double right, double bot)
  {
    Rect((int)left, (int)top, (int)right, (int)bot);
  }

  void ClosedShape(const std::vector<Vector2D> &points)
  {
    if (points.empty()) return;

    if (!m_bBrushHollow && points.size() >= 3)
    {
      std::vector<Vector2> fan(points.size());
      for (size_t p=0; p<points.size(); ++p)
      {
        fan[p] = Vector2{(float)points[p].x, (float)points[p].y};
      }
      DrawTriangleFan(fan.data(), (int)fan.size(), m_BrushColor);
    }

    for (unsigned int p=1; p<points.size(); ++p)
    {
      Line(points[p-1], points[p]);
    }

    Line(points[points.size()-1], points[0]);
  }


  void Circle(Vector2D pos, double radius)
  {
    Circle((int)pos.x, (int)pos.y, radius);
  }

  void Circle(double x, double y, double radius)
  {
    Circle((int)x, (int)y, radius);
  }

  void Circle(int x, int y, double radius)
  {
    if (!m_bBrushHollow)
    {
      DrawCircle(x, y, (float)radius, m_BrushColor);
    }
    DrawCircleLines(x, y, (float)radius, m_PenColor);
  }

  void SetPenColor(int color)
  {
    assert (color < NumColors);

   switch (color)
   {
    case black:BlackPen(); return;

    case white:WhitePen(); return;
    case red: RedPen(); return;
    case green: GreenPen(); return;
    case blue: BluePen(); return;
    case pink: PinkPen(); return;
    case grey: GreyPen(); return;
    case yellow: YellowPen(); return;
    case orange: OrangePen(); return;
    case purple: PurplePen(); return;
    case brown: BrownPen(); return;
    case light_blue: LightBluePen(); return;
    case light_grey: LightGreyPen(); return;
    case light_pink: LightPinkPen(); return;
    }//end switch
  }
};

#endif
