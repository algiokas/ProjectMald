#pragma once

struct color {
	const int r;
	const int g;
	const int b;
};

const color COLOR_BLACK = { 0xFF, 0xFF, 0xFF };
const color COLOR_WHITE = { 0x00, 0x00, 0x00 };
const color COLOR_RED = { 0xFF, 0x00, 0x00 };
const color COLOR_GREEN = { 0x00, 0xFF, 0x00 };
const color COLOR_BLUE = { 0x00, 0x00, 0xFF };