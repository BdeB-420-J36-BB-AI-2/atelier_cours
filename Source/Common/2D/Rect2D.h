#ifndef S2DRECT2D_H
#define S2DRECT2D_H
//------------------------------------------------------------------------
//
//  Name:   Rect2D.h
//
//  Desc:   Plain 2D rectangle (position + size), used at the GraphicsContext
//          boundary so callers never need raylib's own Rectangle type.
//
//------------------------------------------------------------------------

struct Rect2D
{
  double x, y, w, h;

  Rect2D() : x(0.0), y(0.0), w(0.0), h(0.0) {}
  Rect2D(double x, double y, double w, double h) : x(x), y(y), w(w), h(h) {}
};

#endif
