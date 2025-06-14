#pragma once
#include <raylib.h>
#include <iostream>

Texture2D ResizeTexture(Texture2D texture, int newWidth, int newHeight);
int GetAccurateCurrentMonitor();
Color HexToColor(const std::string& hex);
