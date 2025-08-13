#ifndef _Utils_h_
#define _Utils_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <raylib.h>
#include <direct.h>
#include <time.h>

#ifdef _WIN32
__declspec(dllimport) void __stdcall Sleep(unsigned long ms);
#endif

#include "Delimiters.h"

#define vector2Equals(a, b) (fabsf((a).x - (b).x) < (0.00001f) && fabsf((a).y - (b).y) < (0.00001f))

#define Vector2EqualZERO(vector) ((vector).x == 0 && (vector).y == 0)

bool Wait(double intervalo);

bool Wait2(double intervalo);

int getSign(float value);

float Slerp(float a, float b, float t);

Color darkenColor(Color color, float rate);

float linearFunction(float t);

float easedFunction(float t);

float quadraticFunction(float t);

float rootFunction(float t);

#endif