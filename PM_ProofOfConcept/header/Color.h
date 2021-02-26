#pragma once

#include <map>
#include <string>

struct color {
	int r;
	int g;
	int b;

	color() : r(0), g(0), b(0) {}
	color(int r, int g, int b) : r(r), g(g), b(b) {}
};

const std::map<std::string, color> COLORS = {
	{ "BLACK", color(0xFF, 0xFF, 0xFF) },
	{ "WHITE", { 0x00, 0x00, 0x00 } },
	{ "RED", { 0xFF, 0x00, 0x00 } },
	{ "GREEN", { 0x00, 0xFF, 0x00 } },
	{ "BLUE", { 0x00, 0x00, 0xFF } }
};