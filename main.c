#include <cbm.h>
#include <conio.h>
#include <joystick.h>
#include <string.h>
#include <stdbool.h>

#include "data/shiggy.h"

#define SPRITE_LOCATION 0x3EC0

int x = 172, y = 125;
bool alreadyFired = false;
char frame = 0;

void handle_input(void) {
	if (JOY_LEFT(joy_read(JOY_1))) {
		if (x > 24) {
			x -= 1;
		} else x = 24;
	} else if (JOY_RIGHT(joy_read(JOY_1))) {
		if (x < 320) {
			x += 1;
		} else x = 320;
	}

	if (JOY_UP(joy_read(JOY_1))) {
		if (y > 50) {
			y -= 1;
		} else y = 50;
	} else if (JOY_DOWN(joy_read(JOY_1))) {
		if (y < 208) {
			y += 1;
		} else y = 208;
	}

	if (JOY_BTN_1(joy_read(JOY_1)) && (alreadyFired == false)) {
		frame = (frame + 1) % 5;
		alreadyFired = true;
	} else if ((JOY_BTN_1(joy_read(JOY_1)) == false) & alreadyFired) {
		alreadyFired = false;
	}

	VIC.spr_pos[0].x = (short int)x;
	VIC.spr_pos[0].y = y;

	VIC.spr_hi_x = (x > 255);

}

void main() {
	unsigned char *sprites = (unsigned char*)SPRITE_LOCATION;

	joy_install(joy_static_stddrv);

	clrscr();
	VIC.spr_exp_y  = 0b00000001;
	VIC.spr_mcolor = 0b00000001;
	VIC.spr_mcolors[0] = COLOR_LIGHTGREEN;
	VIC.spr_mcolors[1] = COLOR_YELLOW;
	VIC.spr_color[0] = COLOR_BROWN;
	VIC.bgcolor[0] = COLOR_WHITE;
	VIC.spr_ena = 0b00000001;
	*(unsigned char*)0x7F8 = SPRITE_LOCATION / 64;
	for (;;) {
		handle_input();
		memcpy((unsigned*)0x3EC0, shiggy+(63*frame), shiggy_size);
	}
}
