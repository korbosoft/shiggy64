#include <cbm.h>
#include <conio.h>
#include <string.h>

#include "data/shiggy.h"

#define SPRITE_LOCATION 0x3EC0

int x = 0, y = 0;

void main() {
	char frame;
	unsigned char *sprites = (unsigned char*)SPRITE_LOCATION;
	clrscr();
	VIC.spr_pos[0].x = 24;
	VIC.spr_pos[0].y = 50;
	VIC.spr_exp_y  = 0b00000001;
	VIC.spr_mcolor = 0b00000001;
	VIC.spr_mcolors[0] = COLOR_LIGHTGREEN;
	VIC.spr_mcolors[1] = COLOR_YELLOW;
	VIC.spr_color[0] = COLOR_BROWN;
	VIC.bgcolor[0] = COLOR_WHITE;
	VIC.spr_ena = 0b00000001;
	*(unsigned char*)0x7F8 = SPRITE_LOCATION / 64;
	for (;;) {
		memcpy((unsigned*)0x3EC0, shiggy+(63*frame), shiggy_size);
		frame++;
		frame = frame % 5;
	}
}
