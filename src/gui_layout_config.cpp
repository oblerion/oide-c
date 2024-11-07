#include "gui_layout_config.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

GuiLayoutConfigState InitGuiLayoutConfig(void)
{
    GuiLayoutConfigState state = { 0 };

    state.WindowBox000Active = true;
    state.ColorPicker001Value = (Color){ 0, 0, 0, 0 };
    state.ColorPicker002Value = (Color){ 0, 0, 0, 0 };
    state.ColorPicker003Value = (Color){ 0, 0, 0, 0 };
    state.ToggleGroup007Active = 0;

    state.layoutRecs[0] = (Rectangle){ 0, 0, 1000, 576 };
    state.layoutRecs[1] = (Rectangle){ 24, 72, 96, 96 };
    state.layoutRecs[2] = (Rectangle){ 168, 72, 96, 96 };
    state.layoutRecs[3] = (Rectangle){ 312, 72, 96, 96 };
    state.layoutRecs[4] = (Rectangle){ 24, 48, 120, 24 };
    state.layoutRecs[5] = (Rectangle){ 168, 48, 120, 24 };
    state.layoutRecs[6] = (Rectangle){ 312, 48, 120, 24 };
    state.layoutRecs[7] = (Rectangle){ 24, 224, 40, 24 };
    state.layoutRecs[8] = (Rectangle){ 8, 40, 976, 144 };
    state.layoutRecs[9] = (Rectangle){ 8, 208, 976, 128 };

    // Custom variables initialization

    return state;
}

void GuiLayoutConfig(GuiLayoutConfigState *state)
{
    if (state->WindowBox000Active)
    {
        state->WindowBox000Active = !GuiWindowBox(state->layoutRecs[0], "config");
        GuiColorPicker(state->layoutRecs[1], NULL, &state->ColorPicker001Value);
        GuiColorPicker(state->layoutRecs[2], NULL, &state->ColorPicker002Value);
        GuiColorPicker(state->layoutRecs[3], NULL, &state->ColorPicker003Value);
        GuiLabel(state->layoutRecs[4], "bg color");
        GuiLabel(state->layoutRecs[5], "text color");
        GuiLabel(state->layoutRecs[6], "gui color");
        GuiToggleGroup(state->layoutRecs[7], "EN_US;EN_UK;FR;FR_BEL", &state->ToggleGroup007Active);
        GuiGroupBox(state->layoutRecs[8], "theme color");
        GuiGroupBox(state->layoutRecs[9], "keyboard layout");
    }
}

