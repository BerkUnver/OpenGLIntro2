#ifndef SRC_DRAW_H
#define SRC_DRAW_H

#include "math.h"

void draw_init(void);
void draw_free(void);

void draw_immediate_rect(Rect rect, Color color);

#endif
