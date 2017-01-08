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

#include "graphic.h" 
#include "fx.h"

sf2d_texture *cubesSheet, *boxesSheet;

int movementSlow = 0;
bool up = true;

int x[11] = {0, 50, 186, 244, 484, 660, 10, 572, 128, 272, 300};
float rad = 0.0f;

void FXElementsInit() {
	cubesSheet = sfil_load_PNG_file("romfs:/res/fx/Cubes.png", SF2D_PLACE_RAM);
	boxesSheet = sfil_load_PNG_file("romfs:/res/fx/Boxes.png", SF2D_PLACE_RAM);
}

void FXElementsExit() {
	sf2d_free_texture(boxesSheet);
	sf2d_free_texture(cubesSheet);
}

int movementOffsetSlow(int maxrange) {
	if (up && movementSlow > - maxrange * MOVEMENTSPEED) movementSlow -= 1;
	if (movementSlow == - maxrange * MOVEMENTSPEED) up = false;
	if (!up && movementSlow < maxrange * MOVEMENTSPEED) movementSlow += 1;
	if (movementSlow == maxrange * MOVEMENTSPEED) up = true;
	
	return movementSlow / MOVEMENTSPEED;
}

void animateBG(bool isUp) {
	int maxrange = (isUp) ? 400 : 320;
	sf2d_draw_texture_part(boxesSheet, 0, 0, maxrange - x[0] / 2, 0, maxrange, 240);
	
	sf2d_draw_texture_part(cubesSheet, x[1] / 2, 50, 0, 6, 66, 56); //cube1
	sf2d_draw_texture_part_rotate_scale(cubesSheet, x[2] / 2, 180, rad, 67, 11, 56, 51, 1, 1); //cube2rotate
	sf2d_draw_texture_part(cubesSheet, x[3] / 2, 82, 124, 0, 57, 62); //cube3
	sf2d_draw_texture_part_rotate_scale(cubesSheet, x[4] / 2, 60, rad, 182, 6, 58, 56, 1, 1); //cube4rotate
	sf2d_draw_texture_part(cubesSheet, x[5] / 2, 85, 241, 24, 41, 38); //cube5
	sf2d_draw_texture_part(cubesSheet, x[6] / 2, 126, 283, 36, 27, 26); //cube6
	
	//rep
	sf2d_draw_texture_part_rotate_scale(cubesSheet, x[7] / 2, 140, rad, 67, 11, 56, 51, 1, 1); //cube2rotate
	sf2d_draw_texture_part(cubesSheet, x[8] / 2, 66, 283, 36, 27, 26); //cube6
	sf2d_draw_texture_part(cubesSheet, x[9] / 2, 78, 311, 47, 14, 15); //cube7
	sf2d_draw_texture_part(cubesSheet, x[10] / 2, 48, 311, 47, 14, 15); //cube7
	
	x[0] = (x[0] > maxrange * 2) ? 0 : (x[0] + 1);
	
	for (int i = 1; i < 11; i++)
		x[i] = (x[i] >= maxrange * 2 + 45) ? (x[i] - (181 + maxrange * 2)) : (x[i] + 1);
	
	rad = (rad >= 360) ? 0.0f : (rad + 0.005f);
}