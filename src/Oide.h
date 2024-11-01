#pragma once
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "Cmd.h"
#include "kbd_layout.h"
#include "dstring.h"
#define OIDE_VERSION "a0.1"

enum OideScene
{
   oi_dt=0,
   oi_config,
   oi_help
};

struct OideConfig
{
    Color cbg;
    Color ctext;
    Color ccursor;
    int layout;
};

void Oide(int psize);
void Oide_Free();
void Oide_Load(const char* ptext);
void Oide_Draw();
