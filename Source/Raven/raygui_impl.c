/* raygui's implementation uses C99 compound literals (e.g. (Vector2){0,0}),
   which MSVC's C++ front-end rejects as a hard error. Compiling this single
   translation unit as C avoids that; the C++ callers only ever include
   raygui.h for the declarations. */
#define RAYGUI_IMPLEMENTATION
//#include "raygui.h"
