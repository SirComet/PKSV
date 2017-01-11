/* This file is part of PKSV
> MIT License
> Copyright (c) 2016/17 Bernardo Giordano
>
> Permission is hereby granted, free of charge, to any person obtaining a copy
> of this software and associated documentation files (the "Software"), to deal
> in the Software without restriction, including without limitation the rights
> to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
> copies of the Software, and to permit persons to whom the Software is
> furnished to do so, subject to the following conditions:
>
> The above copyright notice and this permission notice shall be included in all
> copies or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
> IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
> FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
> AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
> LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
> OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
> SOFTWARE. */

#pragma once

#include <sf2d.h>
#include <sftd.h>
#include <sfil.h>
#include "util.h"

#define BLUE      RGBA8(104, 137, 205, 255)
#define YELLOW    RGBA8(237, 247, 157, 255)
#define LIGHTBLUE RGBA8(187, 208, 254, 255)
#define DARKBLUE  RGBA8( 35,  69, 167, 255)
#define HIGHBLUE  RGBA8( 28,  45,  86, 255) 

#define BLACK RGBA8(0, 0, 0, 255)
#define SHINYRED RGBA8(255, 17, 17, 255)
#define WHITE RGBA8(255, 255, 255, 255)

#define EGGSPRITEPOS 803

#define MOVEMENTSPEED 4

void GUIElementsInit();
void GUIElementsSpecify();
void GUIGameElementsInit();
void GUIGameElementsExit();
void gameSelectorMenu(int n);
void GUIElementsExit();
void init_font_cache();
void infoDisp(char* message);
void freezeMsg(char* message);
void printPKViewer(u8* mainbuf, bool isTeam, int game, int currentEntry, int box, int modeFlag);
void printElement(u8* pkmn, u16 n, int x, int y);
void infoViewer(u8* pkmn, int game);