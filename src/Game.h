#ifndef _Game_h_
#define _Game_h_

#include "TextObject.h"
#include "Player.h"

void LoadingDraw(TextObject* loading);

void LoadingScreen();

void BlackIn(int *opacity);

void Blackout();

void changeScreen(int (*screen)());

void changeScreenItem(int (*screen)(Player*), Player* item);

#endif