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
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "editor.h"
#include "http.h"
#include "util.h"
#include "graphic.h"

void loadLines(u8 *src, u8 *dst, u8 strlen,  u32 size) {
	u16 readnum = 3;
	u16 line = 0, chr; 

	while (readnum < size) {
		chr = 0;
		while (readnum < size && src[readnum] != '\n') {
		  dst[line * strlen + chr] = src[readnum];
		  readnum++;
		  chr++;
		}
		dst[line * strlen + chr] = 0;
		readnum++;
		line++;
	}
}

bool checkFile(char* path) {
	FILE *temp = fopen(path, "rt");
	if (temp == NULL) {
		fclose(temp);
		return false;
	}
	fclose(temp);
	return true;
}

void loadPersonal() {
	FILE *fptr = fopen("romfs:/personal/personal.bin", "rt");
	if (fptr == NULL) {
		fclose(fptr);
		return;
	}
	fseek(fptr, 0, SEEK_END);
	u32 size = ftell(fptr);
	u8 *buf = (u8*)malloc(size);
	if (buf == NULL) {
		fclose(fptr);
		free(buf);
		return;
	}
	rewind(fptr);
	fread(buf, size, 1, fptr);
	fclose(fptr);
	memcpy(personal.pkmData, buf, size);
	free(buf);
}

bool isHBL() {
    u64 id;
    APT_GetProgramID(&id);

    return id != 0x000400000EC20000;
}

void fsStart() {
    if(isHBL()) {
        Handle fsHandle;
        srvGetServiceHandleDirect(&fsHandle, "fs:USER");
        FSUSER_Initialize(fsHandle);
        fsUseSession(fsHandle);
    }
}

void fsEnd() {
    if(isHBL())
        fsEndUseSession();
}

bool openSaveArch(FS_Archive *out, u64 id) {
	if (id == POKEBANK || !isHBL()) { //If we're using Pokebank or CIA
		u32 cardPath[3] = {MEDIATYPE_GAME_CARD, id, id >> 32}; //Card
		if (R_FAILED(FSUSER_OpenArchive(out, ARCHIVE_USER_SAVEDATA, (FS_Path){PATH_BINARY, 0xC, cardPath}))) { //If that fails, try digital
			u32 sdPath[3] = {MEDIATYPE_SD, id, id >> 32};
			if (R_FAILED(FSUSER_OpenArchive(out, ARCHIVE_USER_SAVEDATA, (FS_Path){PATH_BINARY, 0xC, sdPath})))
				return false;
			else
				return true;
		}
		else
			return true;
	}
	else {
		if (R_SUCCEEDED(FSUSER_OpenArchive(out, ARCHIVE_SAVEDATA, fsMakePath(PATH_EMPTY, ""))))
			return true;
		else
			return false;
	}

	return false;
}