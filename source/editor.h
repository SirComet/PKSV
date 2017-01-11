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

#include <3ds.h>
#include <stdio.h>

#define PKMNLENGTH 232
#define BOXMAX 31
#define MOVELENGTH 2
#define EGGMOVELENGTH 2
#define EVLENGTH 1
#define PIDLENGTH 4
#define IVLENGTH 4
#define OTIDLENGTH 2
#define SOTIDLENGTH 2
#define NICKNAMELENGTH 26
#define POKEDEXNUMBERLENGTH 2
#define ABILITYLENGTH 1
#define ABILITYNUMLENGTH 1
#define NATURELENGTH 1
#define GENDERLENGTH 1
#define ITEMLENGTH 2
#define EXPPOINTLENGTH 4

#define ED_STANDARD 0
#define ED_SEED 1

struct {
	u8 species[803][12];
	u8 pkmData[961][42];
} personal;

u32 seedStep(const u32 seed);
void shuffleArray(u8* pkmn, const u32 encryptionkey);
void decryptPkmn(u8* pkmn);
int getPkmnAddress(const int boxnumber, const int indexnumber, int game);
void getPkmn(u8* mainbuf, const int boxnumber, const int indexnumber, u8* pkmn, int game);
bool isShiny(u8* pkmn);
bool isEgg(u8* pkmn);

u8 getGender(u8* pkmn);
u8 getLanguage(u8* pkmn);
u16 getPokedexNumber(u8* pkmn);
u8 getNature(u8* pkmn);
u8 getEV(u8* pkmn, const int stat);
u8 getFriendship(u8* pkmn);
u8 getOTFriendship(u8* pkmn);
u8 getIV(u8* pkmn, const int stat);
u16 getOTID(u8* pkmn);
u16 getSOTID(u8* pkmn);
u32 getPID(u8* pkmn);
u16 getTSV(u8* pkmn);
u16 getMove(u8* pkmn, int nmove);
u16 getItem(u8* pkmn);
u8 getHPType(u8* pkmn);
u8 getLevel(u8* pkmn);
bool isInfected (u8* pkmn);
u8 getForm(u8* pkmn);
u16 getStat(u8* pkmn, const int stat);
bool getPokerus(u8* pkmn);
u8 getAbility(u8* pkmn);
char *getOT(u8* pkmn, char* dst);
char *getNickname(u8* pkmn, char* dst);
u8 getBall(u8* pkmn);
u16 getPSV(u8* pkmn);
u16 getSaveTID(u8* mainbuf, int game);
u16 getSaveSID(u8* mainbuf, int game);
u16 getSaveTSV(u8* mainbuf, int game);
u32 getSaveSeed(u8* mainbuf, int game, int index);

void pokemonEditor(u8* mainbuf, int game);