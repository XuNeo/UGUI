/* -------------------------------------------------------------------------------- */
/* -- µGUI - Generic GUI module (C)Achim Döbler, 2015                            -- */
/* -------------------------------------------------------------------------------- */
// µGUI is a generic GUI module for embedded systems.
// This is a free software that is open for education, research and commercial
// developments under license policy of following terms.
//
//  Copyright (C) 2015, Achim Döbler, all rights reserved.
//  URL: http://www.embeddedlightning.com/
//
// * The µGUI module is a free software and there is NO WARRANTY.
// * No restriction on use. You can use, modify and redistribute it for
//   personal, non-profit or commercial products UNDER YOUR RESPONSIBILITY.
// * Redistributions of source code must retain the above copyright notice.
//
/* -------------------------------------------------------------------------------- */
#ifndef __UGUI_H
#define __UGUI_H

#include <stdlib.h>
#include "ugui_config.h"
#if !defined(UGUI_USE_CUSTOM_THEME)
#include "ugui_theme.h"
#else
#include "ugui_theme_custom.h"
#endif

/* -------------------------------------------------------------------------------- */
/* -- TYPEDEFS                                                                   -- */
/* -------------------------------------------------------------------------------- */
typedef struct S_OBJECT                               UG_OBJECT;
typedef struct S_WINDOW                               UG_WINDOW;
typedef UG_S8                                         UG_RESULT;
#if defined(UGUI_USE_COLOR_RGB888)
typedef UG_U32                       UG_COLOR;
#elif defined(UGUI_USE_COLOR_RGB565)
typedef UG_U16                       UG_COLOR;
#elif defined(UGUI_USE_COLOR_BW)
typedef UG_U8                        UG_COLOR;
#endif
#if !defined(UGUI_USE_COLOR_RGB888) && !defined(UGUI_USE_COLOR_RGB565) && !defined(UGUI_USE_COLOR_BW)
#error "You must define a color space!"
#endif
#if !defined(C_PAL_WINDOW)
#error "You must define a theme!"
#endif

/* -------------------------------------------------------------------------------- */
/* -- DEFINES                                                                    -- */
/* -------------------------------------------------------------------------------- */

/* Alignments */
#define ALIGN_H_LEFT                                  (1<<0)
#define ALIGN_H_CENTER                                (1<<1)
#define ALIGN_H_RIGHT                                 (1<<2)
#define ALIGN_V_TOP                                   (1<<3)
#define ALIGN_V_CENTER                                (1<<4)
#define ALIGN_V_BOTTOM                                (1<<5)
#define ALIGN_BOTTOM_RIGHT                            (ALIGN_V_BOTTOM|ALIGN_H_RIGHT)
#define ALIGN_BOTTOM_CENTER                           (ALIGN_V_BOTTOM|ALIGN_H_CENTER)
#define ALIGN_BOTTOM_LEFT                             (ALIGN_V_BOTTOM|ALIGN_H_LEFT)
#define ALIGN_CENTER_RIGHT                            (ALIGN_V_CENTER|ALIGN_H_RIGHT)
#define ALIGN_CENTER                                  (ALIGN_V_CENTER|ALIGN_H_CENTER)
#define ALIGN_CENTER_LEFT                             (ALIGN_V_CENTER|ALIGN_H_LEFT)
#define ALIGN_TOP_RIGHT                               (ALIGN_V_TOP|ALIGN_H_RIGHT)
#define ALIGN_TOP_CENTER                              (ALIGN_V_TOP|ALIGN_H_CENTER)
#define ALIGN_TOP_LEFT                                (ALIGN_V_TOP|ALIGN_H_LEFT)

/* Default IDs */
#define OBJ_ID_0                                      0
#define OBJ_ID_1                                      1
#define OBJ_ID_2                                      2
#define OBJ_ID_3                                      3
#define OBJ_ID_4                                      4
#define OBJ_ID_5                                      5
#define OBJ_ID_6                                      6
#define OBJ_ID_7                                      7
#define OBJ_ID_8                                      8
#define OBJ_ID_9                                      9
#define OBJ_ID_10                                     10
#define OBJ_ID_11                                     11
#define OBJ_ID_12                                     12
#define OBJ_ID_13                                     13
#define OBJ_ID_14                                     14
#define OBJ_ID_15                                     15
#define OBJ_ID_16                                     16
#define OBJ_ID_17                                     17
#define OBJ_ID_18                                     18
#define OBJ_ID_19                                     19

/* -------------------------------------------------------------------------------- */
/* -- FUNCTION RESULTS                                                           -- */
/* -------------------------------------------------------------------------------- */
#define UG_RESULT_FAIL                                -1
#define UG_RESULT_OK                                  0

/* -------------------------------------------------------------------------------- */
/* -- µGUI FONTS                                                                 -- */
/* -- Source: http://www.mikrocontroller.net/user/show/benedikt                  -- */
/* -------------------------------------------------------------------------------- */

/* Font structures */
typedef enum
{
	FONT_TYPE_1BPP,
	FONT_TYPE_8BPP
} FONT_TYPE;

typedef struct
{
   UG_U8* p;
   FONT_TYPE font_type;
   UG_S16 char_width;
   UG_S16 char_height;
   UG_U16 start_char;
   UG_U16 end_char;
   UG_U8  *widths;
} UG_FONT;

#define UGUI_DECLARE_FONT(name, varPointer, bpp, width, height)   const UG_FONT name = { (UG_U8*) varPointer, bpp, width, height, 0, 255, NULL };

#include "fonts/font_4x6.h"
#include "fonts/font_5x8.h"
#include "fonts/font_5x12.h"
#include "fonts/font_6x8.h"
#include "fonts/font_6x10.h"
#include "fonts/font_7x12.h"
#include "fonts/font_8x8.h"
#include "fonts/font_8x12.h"
#include "fonts/font_8x12_cyrillic.h"
#include "fonts/font_8x14.h"
#include "fonts/font_10x16.h"
#include "fonts/font_12x16.h"
#include "fonts/font_12x20.h"
#include "fonts/font_16x26.h"
#include "fonts/font_22x36.h"
#include "fonts/font_24x40.h"
#include "fonts/font_32x53.h"

/* -------------------------------------------------------------------------------- */
/* -- UNIVERSAL STRUCTURES                                                       -- */
/* -------------------------------------------------------------------------------- */
/* Area structure */
typedef struct
{
   UG_S16 xs;
   UG_S16 ys;
   UG_S16 xe;
   UG_S16 ye;
} UG_AREA;

/* Text structure */
typedef struct
{
   char* str;
   const UG_FONT* font;
   UG_AREA a;
   UG_COLOR fc;
   UG_COLOR bc;
   UG_U8 align;
   UG_S16 h_space;
   UG_S16 v_space;
} UG_TEXT;

/* -------------------------------------------------------------------------------- */
/* -- BITMAP                                                                     -- */
/* -------------------------------------------------------------------------------- */
typedef struct
{
   void* p;
   UG_U16 width;
   UG_U16 height;
   UG_U8 bpp;
   UG_U8 colors;
} UG_BMP;

#define BMP_BPP_1                                     (1<<0)
#define BMP_BPP_2                                     (1<<1)
#define BMP_BPP_4                                     (1<<2)
#define BMP_BPP_8                                     (1<<3)
#define BMP_BPP_16                                    (1<<4)
#define BMP_BPP_32                                    (1<<5)
#define BMP_RGB888                                    (1<<0)
#define BMP_RGB565                                    (1<<1)
#define BMP_RGB555                                    (1<<2)

/* -------------------------------------------------------------------------------- */
/* -- MESSAGE                                                                    -- */
/* -------------------------------------------------------------------------------- */
/* Message structure */
typedef struct
{
   UG_U8 type;
   UG_U8 id;
   UG_U8 sub_id;
   UG_U8 event;
   void* src;
} UG_MESSAGE;

/* Message types */
#define MSG_TYPE_NONE                                 0
#define MSG_TYPE_WINDOW                               1
#define MSG_TYPE_OBJECT                               2

/* -------------------------------------------------------------------------------- */
/* -- TOUCH                                                                      -- */
/* -------------------------------------------------------------------------------- */
#ifdef UGUI_USE_TOUCH
/* Touch structure */
typedef struct
{
   UG_U8 state;
   UG_S16 xp;
   UG_S16 yp;
} UG_TOUCH;

#define TOUCH_STATE_PRESSED                           1
#define TOUCH_STATE_RELEASED                          0
#endif

/* -------------------------------------------------------------------------------- */
/* -- OBJECTS                                                                    -- */
/* -------------------------------------------------------------------------------- */
/* Object structure */
struct S_OBJECT
{
   UG_U8 state;                              /* object state                               */
   #ifdef UGUI_USE_TOUCH
   UG_U8 touch_state;                        /* object touch state                         */
   #endif
   void (*update) (UG_WINDOW*,UG_OBJECT*);   /* pointer to object-specific update function */
   UG_AREA a_abs;                            /* absolute area of the object                */
   UG_AREA a_rel;                            /* relative area of the object                */
   UG_U8 type;                               /* object type                                */
   UG_U8 id;                                 /* object ID                                  */
   UG_U8 event;                              /* object-specific events                     */
   void* data;                               /* pointer to object-specific data            */
};

/* Currently supported objects */
#define OBJ_TYPE_NONE                                 0

/* Standard object events */
#define OBJ_EVENT_NONE                                0
#define OBJ_EVENT_CLICKED                             1
#ifdef UGUI_USE_PRERENDER_EVENT
#define OBJ_EVENT_PRERENDER                           2
#endif
#ifdef UGUI_UGUI_USE_POSTRENDER_EVENT
#define OBJ_EVENT_POSTRENDER                          3
#endif
#define OBJ_EVENT_PRESSED                             4
#define OBJ_EVENT_RELEASED                            5

/* Object states */
#define OBJ_STATE_FREE                                (1<<0)
#define OBJ_STATE_VALID                               (1<<1)
#define OBJ_STATE_BUSY                                (1<<2)
#define OBJ_STATE_VISIBLE                             (1<<3)
#define OBJ_STATE_ENABLE                              (1<<4)
#define OBJ_STATE_UPDATE                              (1<<5)
#define OBJ_STATE_REDRAW                              (1<<6)
#ifdef UGUI_USE_TOUCH
   #define OBJ_STATE_TOUCH_ENABLE                     (1<<7)
#endif
#define OBJ_STATE_INIT                                (OBJ_STATE_FREE | OBJ_STATE_VALID)

#ifdef UGUI_USE_TOUCH
/* Object touch states */
#define OBJ_TOUCH_STATE_CHANGED                       (1<<0)
#define OBJ_TOUCH_STATE_PRESSED_ON_OBJECT             (1<<1)
#define OBJ_TOUCH_STATE_PRESSED_OUTSIDE_OBJECT        (1<<2)
#define OBJ_TOUCH_STATE_RELEASED_ON_OBJECT            (1<<3)
#define OBJ_TOUCH_STATE_RELEASED_OUTSIDE_OBJECT       (1<<4)
#define OBJ_TOUCH_STATE_IS_PRESSED_ON_OBJECT          (1<<5)
#define OBJ_TOUCH_STATE_IS_PRESSED                    (1<<6)
#define OBJ_TOUCH_STATE_CLICK_ON_OBJECT               (1<<7)
#define OBJ_TOUCH_STATE_INIT                          0
#endif

/* -------------------------------------------------------------------------------- */
/* -- WINDOW                                                                     -- */
/* -------------------------------------------------------------------------------- */
/* Title structure */
typedef struct
{
   char* str;
   const UG_FONT* font;
   UG_S8 h_space;
   UG_S8 v_space;
   UG_U8 align;
   UG_COLOR fc;
   UG_COLOR bc;
   UG_COLOR ifc;
   UG_COLOR ibc;
   UG_U8 height;
} UG_TITLE;

/* Window structure */
struct S_WINDOW
{
   UG_U8 objcnt;
   UG_OBJECT* objlst;
   UG_U8 state;
   UG_COLOR fc;
   UG_COLOR bc;
   UG_S16 xs;
   UG_S16 ys;
   UG_S16 xe;
   UG_S16 ye;
   UG_U8 style;
   UG_TITLE title;
   void (*cb)( UG_MESSAGE* );
};

/* Window states */
#define WND_STATE_FREE                                (1<<0)
#define WND_STATE_VALID                               (1<<1)
#define WND_STATE_BUSY                                (1<<2)
#define WND_STATE_VISIBLE                             (1<<3)
#define WND_STATE_ENABLE                              (1<<4)
#define WND_STATE_UPDATE                              (1<<5)
#define WND_STATE_REDRAW_TITLE                        (1<<6)

/* Window styles */
#define WND_STYLE_2D                                  (0<<0)
#define WND_STYLE_3D                                  (1<<0)
#define WND_STYLE_HIDE_TITLE                          (0<<1)
#define WND_STYLE_SHOW_TITLE                          (1<<1)

/* -------------------------------------------------------------------------------- */
/* -- µGUI DRIVER                                                                -- */
/* -------------------------------------------------------------------------------- */
typedef struct
{
  void* driver;
  UG_U8 state;
} UG_DRIVER;

#define DRIVER_REGISTERED                             (1<<0)
#define DRIVER_ENABLED                                (1<<1)

/* Supported drivers */
#define NUMBER_OF_DRIVERS                             3
#define DRIVER_DRAW_LINE                              0
#define DRIVER_FILL_FRAME                             1
#define DRIVER_FILL_AREA                              2

/* -------------------------------------------------------------------------------- */
/* -- µGUI CORE STRUCTURE                                                        -- */
/* -------------------------------------------------------------------------------- */
typedef struct
{
   void (*pset)(UG_S16,UG_S16,UG_COLOR);
   void (*flush)(void);
   UG_S16 x_dim;
   UG_S16 y_dim;
   #ifdef UGUI_USE_TOUCH
   UG_TOUCH touch;
   #endif
   UG_WINDOW* next_window;
   UG_WINDOW* active_window;
   UG_WINDOW* last_window;
   struct
   {
      UG_S16 x_pos;
      UG_S16 y_pos;
      UG_S16 x_start;
      UG_S16 y_start;
      UG_S16 x_end;
      UG_S16 y_end;
      UG_COLOR fore_color;
      UG_COLOR back_color;
   } console;
   UG_FONT font;
   UG_S8 char_h_space;
   UG_S8 char_v_space;
   UG_COLOR fore_color;
   UG_COLOR back_color;
   UG_COLOR desktop_color;
   UG_U8 state;
   UG_DRIVER driver[NUMBER_OF_DRIVERS];
} UG_GUI;

#define UG_STATUS_WAIT_FOR_UPDATE                     (1<<0)

/* -------------------------------------------------------------------------------- */
/* -- PROTOTYPES                                                                 -- */
/* -------------------------------------------------------------------------------- */
/* Classic functions */
UG_S16 UG_Init( UG_GUI* g, void (*p)(UG_S16,UG_S16,UG_COLOR), void (*flush)(void), UG_S16 x, UG_S16 y );
UG_S16 UG_SelectGUI( UG_GUI* g );
void UG_FontSelect( const UG_FONT* font );
void UG_FillScreen( UG_COLOR c );
void UG_FillFrame( UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2, UG_COLOR c );
void UG_FillRoundFrame( UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2, UG_S16 r, UG_COLOR c );
void UG_DrawMesh( UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2, UG_COLOR c );
void UG_DrawFrame( UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2, UG_COLOR c );
void UG_DrawRoundFrame( UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2, UG_S16 r, UG_COLOR c );
void UG_DrawPixel( UG_S16 x0, UG_S16 y0, UG_COLOR c );
void UG_DrawCircle( UG_S16 x0, UG_S16 y0, UG_S16 r, UG_COLOR c );
void UG_FillCircle( UG_S16 x0, UG_S16 y0, UG_S16 r, UG_COLOR c );
void UG_DrawArc( UG_S16 x0, UG_S16 y0, UG_S16 r, UG_U8 s, UG_COLOR c );
void UG_DrawLine( UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2, UG_COLOR c );
void UG_PutString( UG_S16 x, UG_S16 y, const char* str );
void UG_PutChar( const char chr, UG_S16 x, UG_S16 y, UG_COLOR fc, UG_COLOR bc );
void UG_ConsolePutString( const char* str );
void UG_ConsoleSetArea( UG_S16 xs, UG_S16 ys, UG_S16 xe, UG_S16 ye );
void UG_ConsoleSetForecolor( UG_COLOR c );
void UG_ConsoleSetBackcolor( UG_COLOR c );
void UG_SetForecolor( UG_COLOR c );
void UG_SetBackcolor( UG_COLOR c );
UG_S16 UG_GetXDim( void );
UG_S16 UG_GetYDim( void );
void UG_FontSetHSpace( UG_U16 s );
void UG_FontSetVSpace( UG_U16 s );

/* Miscellaneous functions */
void UG_WaitForUpdate( void );
void UG_Update( void );
void UG_DrawBMP( UG_S16 xp, UG_S16 yp, UG_BMP* bmp );
#ifdef UGUI_USE_TOUCH
void UG_TouchUpdate( UG_S16 xp, UG_S16 yp, UG_U8 state );
#endif

/* Driver functions */
void UG_DriverRegister( UG_U8 type, void* driver );
void UG_DriverEnable( UG_U8 type );
void UG_DriverDisable( UG_U8 type );

/* Internal API functions */
void _UG_PutText(UG_TEXT* txt);
UG_OBJECT* _UG_SearchObject( UG_WINDOW* wnd, UG_U8 type, UG_U8 id );
void _UG_DrawObjectFrame( UG_S16 xs, UG_S16 ys, UG_S16 xe, UG_S16 ye, UG_COLOR* p );
UG_OBJECT* _UG_GetFreeObject( UG_WINDOW* wnd );
UG_RESULT _UG_DeleteObject( UG_WINDOW* wnd, UG_U8 type, UG_U8 id );
#ifdef UGUI_USE_PRERENDER_EVENT
void _UG_SendObjectPrerenderEvent(UG_WINDOW *wnd,UG_OBJECT *obj);
#endif
#ifdef UGUI_USE_POSTRENDER_EVENT
void _UG_SendObjectPostrenderEvent(UG_WINDOW *wnd,UG_OBJECT *obj);
#endif

/* Window functions */
UG_RESULT UG_WindowCreate( UG_WINDOW* wnd, UG_OBJECT* objlst, UG_U8 objcnt, void (*cb)( UG_MESSAGE* ) );
UG_RESULT UG_WindowDelete( UG_WINDOW* wnd );
UG_RESULT UG_WindowShow( UG_WINDOW* wnd );
UG_RESULT UG_WindowHide( UG_WINDOW* wnd );
UG_RESULT UG_WindowResize( UG_WINDOW* wnd, UG_S16 xs, UG_S16 ys, UG_S16 xe, UG_S16 ye );
UG_RESULT UG_WindowAlert( UG_WINDOW* wnd );
UG_RESULT UG_WindowSetForeColor( UG_WINDOW* wnd, UG_COLOR fc );
UG_RESULT UG_WindowSetBackColor( UG_WINDOW* wnd, UG_COLOR bc );
UG_RESULT UG_WindowSetTitleTextColor( UG_WINDOW* wnd, UG_COLOR c );
UG_RESULT UG_WindowSetTitleColor( UG_WINDOW* wnd, UG_COLOR c );
UG_RESULT UG_WindowSetTitleInactiveTextColor( UG_WINDOW* wnd, UG_COLOR c );
UG_RESULT UG_WindowSetTitleInactiveColor( UG_WINDOW* wnd, UG_COLOR c );
UG_RESULT UG_WindowSetTitleText( UG_WINDOW* wnd, char* str );
UG_RESULT UG_WindowSetTitleTextFont( UG_WINDOW* wnd, const UG_FONT* font );
UG_RESULT UG_WindowSetTitleTextHSpace( UG_WINDOW* wnd, UG_S8 hs );
UG_RESULT UG_WindowSetTitleTextVSpace( UG_WINDOW* wnd, UG_S8 vs );
UG_RESULT UG_WindowSetTitleTextAlignment( UG_WINDOW* wnd, UG_U8 align );
UG_RESULT UG_WindowSetTitleHeight( UG_WINDOW* wnd, UG_U8 height );
UG_RESULT UG_WindowSetXStart( UG_WINDOW* wnd, UG_S16 xs );
UG_RESULT UG_WindowSetYStart( UG_WINDOW* wnd, UG_S16 ys );
UG_RESULT UG_WindowSetXEnd( UG_WINDOW* wnd, UG_S16 xe );
UG_RESULT UG_WindowSetYEnd( UG_WINDOW* wnd, UG_S16 ye );
UG_RESULT UG_WindowSetStyle( UG_WINDOW* wnd, UG_U8 style );
UG_COLOR UG_WindowGetForeColor( UG_WINDOW* wnd );
UG_COLOR UG_WindowGetBackColor( UG_WINDOW* wnd );
UG_COLOR UG_WindowGetTitleTextColor( UG_WINDOW* wnd );
UG_COLOR UG_WindowGetTitleColor( UG_WINDOW* wnd );
UG_COLOR UG_WindowGetTitleInactiveTextColor( UG_WINDOW* wnd );
UG_COLOR UG_WindowGetTitleInactiveColor( UG_WINDOW* wnd );
char* UG_WindowGetTitleText( UG_WINDOW* wnd );
UG_FONT* UG_WindowGetTitleTextFont( UG_WINDOW* wnd );
UG_S8 UG_WindowGetTitleTextHSpace( UG_WINDOW* wnd );
UG_S8 UG_WindowGetTitleTextVSpace( UG_WINDOW* wnd );
UG_U8 UG_WindowGetTitleTextAlignment( UG_WINDOW* wnd );
UG_U8 UG_WindowGetTitleHeight( UG_WINDOW* wnd );
UG_S16 UG_WindowGetXStart( UG_WINDOW* wnd );
UG_S16 UG_WindowGetYStart( UG_WINDOW* wnd );
UG_S16 UG_WindowGetXEnd( UG_WINDOW* wnd );
UG_S16 UG_WindowGetYEnd( UG_WINDOW* wnd );
UG_U8 UG_WindowGetStyle( UG_WINDOW* wnd );
UG_RESULT UG_WindowGetArea( UG_WINDOW* wnd, UG_AREA* a );
UG_S16 UG_WindowGetInnerWidth( UG_WINDOW* wnd );
UG_S16 UG_WindowGetOuterWidth( UG_WINDOW* wnd );
UG_S16 UG_WindowGetInnerHeight( UG_WINDOW* wnd );
UG_S16 UG_WindowGetOuterHeight( UG_WINDOW* wnd );

/* Pointer to the gui */
extern UG_GUI* gui;

#endif
