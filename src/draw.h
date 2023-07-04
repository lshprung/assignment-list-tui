#ifndef DRAW_H
#define DRAW_H

#include "entry.h"
#include "group.h"

// initialize the tui
void tui_init(Group **groups, Entry **entries);

// destroy the tui
void tui_end();

#endif
