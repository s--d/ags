//=============================================================================
//
// Adventure Game Studio (AGS)
//
// Copyright (C) 1999-2011 Chris Jones and 2011-20xx others
// The full list of copyright holders can be found in the Copyright.txt
// file, which is part of this source code distribution.
//
// The AGS source code is provided under the Artistic License 2.0.
// A copy of this license can be found in the file License.txt and at
// http://www.opensource.org/licenses/artistic-license-2.0.php
//
//=============================================================================

#include <string.h>
#include "util/wgt2allg.h"
#include "gfx/ali3d.h"
#include "ac/mouse.h"
#include "ac/record.h"
#include "gui/mypushbutton.h"
#include "gui/guidialog.h"
#include "gui/guidialoginternaldefs.h"
#include "main/game_run.h"
#include "media/audio/audio.h"
#include "gfx/bitmap.h"

using AGS::Common::Bitmap;

extern volatile int timerloop;

extern int windowbackgroundcolor, pushbuttondarkcolor;
extern int pushbuttonlightcolor;
extern int cbuttfont;

MyPushButton::MyPushButton(int xx, int yy, int wi, int hi, char *tex)
{                             //wlevel=2;
    x = xx;
    y = yy;
    wid = wi;
    hit = hi + 1;               //hit=hi;
    state = 0;
    strncpy(text, tex, 50);
    text[49] = 0;
};

void MyPushButton::draw()
{
    wtextcolor(0);
    wsetcolor(COL254);
    abuf->FillRect(Rect(x, y, x + wid, y + hit), currentcolor);
    if (state == 0)
        wsetcolor(pushbuttondarkcolor);
    else
        wsetcolor(pushbuttonlightcolor);

    abuf->DrawRect(Rect(x, y, x + wid, y + hit), currentcolor);
    if (state == 0)
        wsetcolor(pushbuttonlightcolor);
    else
        wsetcolor(pushbuttondarkcolor);

    abuf->DrawLine(Line(x, y, x + wid - 1, y), currentcolor);
    abuf->DrawLine(Line(x, y, x, y + hit - 1), currentcolor);
    wouttextxy(x + (wid / 2 - wgettextwidth(text, cbuttfont) / 2), y + 2, cbuttfont, text);
    if (typeandflags & CNF_DEFAULT)
        wsetcolor(0);
    else
        wsetcolor(windowbackgroundcolor);

    abuf->DrawRect(Rect(x - 1, y - 1, x + wid + 1, y + hit + 1), currentcolor);
}

//extern const int LEFT;  // in mousew32

int MyPushButton::pressedon()
{
    int wasstat;
    while (mbutrelease(LEFT) == 0) {
        timerloop = 0;
        wasstat = state;
        next_iteration();
        state = mouseisinarea();
        // stop mp3 skipping if button held down
        update_polled_stuff_if_runtime();
        if (wasstat != state) {
            //        domouse(2);
            draw();
            //domouse(1);
        }

        //      domouse(0);

        refresh_screen();

        while (timerloop == 0) ;
    }
    wasstat = state;
    state = 0;
    //    domouse(2);
    draw();
    //  domouse(1);
    return wasstat;
}

int MyPushButton::processmessage(int mcode, int wParam, long lParam)
{
    return -1;                  // doesn't support messages
}