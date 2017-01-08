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

#include <stdlib.h>
#include <stdio.h>
#include <3ds.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include "http.h"
#include "util.h"
#include "editor.h"
#include "graphic.h"
#include "fx.h"

#define GAMES 6
#define ASSETS 8

char* path[] =    { "/3ds/data/PKSM/additionalassets/3dsicons.png",
					"/3ds/data/PKSM/additionalassets/alternative_icons_spritesheet.png",
					"/3ds/data/PKSM/additionalassets/back_button.png",
					"/3ds/data/PKSM/additionalassets/balls_spritesheet.png",
					"/3ds/data/PKSM/additionalassets/editor_bar.png",
					"/3ds/data/PKSM/additionalassets/editor_bottom.png",
					"/3ds/data/PKSM/additionalassets/pokemon_icons_spritesheet.png",
					"/3ds/data/PKSM/additionalassets/species_en.txt",
};
char* url[] = { "https://raw.githubusercontent.com/dsoldier/PKResources/master/additionalassets/3dsicons.png", 
				"https://raw.githubusercontent.com/dsoldier/PKResources/master/additionalassets/alternative_icons_spritesheet.png",
				"https://raw.githubusercontent.com/dsoldier/PKResources/master/additionalassets/back_button.png",
				"https://raw.githubusercontent.com/dsoldier/PKResources/master/additionalassets/balls_spritesheet.png",
				"https://raw.githubusercontent.com/dsoldier/PKResources/master/additionalassets/editor_bar.png",
				"https://raw.githubusercontent.com/dsoldier/PKResources/master/additionalassets/editor_bottom.png",
				"https://raw.githubusercontent.com/dsoldier/PKResources/master/additionalassets/pokemon_icons_spritesheet.png",
				"https://raw.githubusercontent.com/dsoldier/PKResources/master/additionalassets/species_en.txt",
};

void exitServices() {
	FXElementsExit();
	GUIElementsExit();
	hidExit();
	srvExit();
	fsEnd();
	sdmcExit();
	aptExit();
	romfsExit();
	sftd_fini();
	sf2d_fini();
}

bool initServices() {
	bool isDownloaded = false;
	sf2d_init();
	sftd_init();
	sf2d_set_clear_color(BLACK);
	sf2d_set_vblank_wait(1);
	aptInit();
	sdmcInit();
	romfsInit();
	fsStart();
	srvInit();
	hidInit();
	GUIElementsInit();
	FXElementsInit();
	GUIGameElementsInit();

	mkdir("sdmc:/3ds", 0777);
	mkdir("sdmc:/3ds/data", 0777);
	mkdir("sdmc:/3ds/data/PKSM", 0777);
	mkdir("sdmc:/3ds/data/PKSM/additionalassets", 0777);
	
	char* str = (char*)malloc(30);
	for (int i = 0; i < ASSETS; i++) {
		FILE *temp1 = fopen(path[i], "rt");
		if (temp1 == NULL) {
			fclose(temp1);
			snprintf(str, 30, "Downloading assets #%d...", i + 1);
			freezeMsg(str);
			downloadFile(url[i], path[i]);
			isDownloaded = true;
		} else
			fclose(temp1);
	}
	free(str);
	
	loadPersonal();
	
    u8 tmp[12000];
	FILE *fptr = fopen(path[7], "rt");
	if (fptr == NULL) {
		fclose(fptr);
		return true;
	}
	fseek(fptr, 0, SEEK_END);
	u32 size = ftell(fptr);
	memset(tmp, 0, size);
	rewind(fptr);
	fread(tmp, size, 1, fptr);
	fclose(fptr);
	loadLines(tmp, personal.species[0], 12, size);

	return isDownloaded;
}

int main() {
	if (initServices()) {
		infoDisp("Restart the application!");
		exitServices();
		return 0;
	}
	
	for (int i = 0; i < ASSETS; i++) {
		if(!checkFile(path[i])) {
			infoDisp("You're missing a few assets!");
			exitServices();
			return -1;
		}
	}

	u8* mainbuf;
	u64 mainSize = 0;
	int game = 0;
	
	Handle mainHandle;
	FS_Archive saveArch;
	
	//X, Y, OR, AS, SUN, MOON
	const u64 ids[] = {0x0004000000055D00, 0x0004000000055E00, 0x000400000011C400, 0x000400000011C500, 0x0004000000164800, 0x0004000000175E00};

	while (aptMainLoop() && !(hidKeysDown() & KEY_A)) {
		hidScanInput();
		
		if (hidKeysDown() & KEY_B) {
			exitServices();
			return 0;
		}
		
		if (hidKeysDown() & KEY_DLEFT) {
			if (game == 0) game = GAMES - 1;
			else if (game > 0) game--;	
		}
		
		if (hidKeysDown() & KEY_DRIGHT) {
			if (game == GAMES - 1) game = 0;
			else if (game < GAMES - 1) game++;
		}
		
		gameSelectorMenu(game);
	}
	
	GUIGameElementsExit();
	freezeMsg("Loading save...");
	

	if (!(openSaveArch(&saveArch, ids[game]))) {
		infoDisp("Game not found!");
		exitServices();
		return -1;
	}
	FSUSER_OpenFile(&mainHandle, saveArch, fsMakePath(PATH_ASCII, "/main"), FS_OPEN_READ | FS_OPEN_WRITE, 0);		
	FSFILE_GetSize(mainHandle, &mainSize);
	switch (game) {
		case GAME_X : { if (mainSize != 415232) infoDisp("Incorrect size for this game!"); break; }
		case GAME_Y : { if (mainSize != 415232) infoDisp("Incorrect size for this game!"); break; }
		case GAME_OR : { if (mainSize != 483328) infoDisp("Incorrect size for this game!"); break; }
		case GAME_AS : { if (mainSize != 483328) infoDisp("Incorrect size for this game!"); break; }
		case GAME_SUN : { if (mainSize != 441856) infoDisp("Incorrect size for this game!"); break; }
		case GAME_MOON : { if (mainSize != 441856) infoDisp("Incorrect size for this game!"); break; }
		exitServices();
		return -1;
	}	
	mainbuf = malloc(mainSize);
	FSFILE_Read(mainHandle, NULL, 0, mainbuf, mainSize);

	GUIElementsSpecify();
	pokemonEditor(mainbuf, game);
	
	free(mainbuf);
	exitServices();
	return 0;
}