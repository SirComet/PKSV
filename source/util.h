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

#include <stdlib.h>
#include <3ds.h>

#define POKEBANK 0x00040000000C9B00

#define GAME_X 0
#define GAME_Y 1
#define GAME_OR 2
#define GAME_AS 3
#define GAME_SUN 4
#define GAME_MOON 5

void loadLines(u8 *src, u8 *dst, u8 strlen,  u32 size);
bool checkFile(char* path);
void loadPersonal();
bool isHBL();
void fsStart();
void fsEnd();
bool openSaveArch(FS_Archive *out, u64 id);