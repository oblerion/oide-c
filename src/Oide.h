#pragma once
#include "raylib.h"
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include "Cmd.h"
#include "kbd_layout.h"
#include "dstring.h"

#define OIDE_VERSION "a0.1"

void Oide(int psize);
void Oide_Free();
void Oide_Load(const char* ptext);
void Oide_Draw();
