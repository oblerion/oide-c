/*******************************************************************************************
*
*   LayoutConfig v1.0.0 - Tool Description
*
*   MODULE USAGE:
*       #define GUI_LAYOUT_CONFIG_IMPLEMENTATION
*       #include "gui_layout_config.h"
*
*       INIT: GuiLayoutConfigState state = InitGuiLayoutConfig();
*       DRAW: GuiLayoutConfig(&state);
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 raylib technologies. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/
#pragma once
#include "raylib.h"
// WARNING: raygui implementation is expected to be defined before including this header
#include <string.h>     // Required for: strcpy()



typedef struct {
    bool WindowBox000Active;
    Color ColorPicker001Value;
    Color ColorPicker002Value;
    Color ColorPicker003Value;
    int ToggleGroup007Active;

    Rectangle layoutRecs[10];

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiLayoutConfigState;

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

GuiLayoutConfigState InitGuiLayoutConfig(void);
void GuiLayoutConfig(GuiLayoutConfigState *state);

#ifdef __cplusplus
}
#endif


