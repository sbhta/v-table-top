#pragma once

#include "button.h"
#include "level.h"
#include "raylib.h"
#include <memory>
#include <vector>
class SideBar{
public:
   SideBar(Vector2 pos, Vector2 size, Color bgColor, Level& level);
   void draw();
   void update(Vector2 mousePos, bool mousePressed);
   Vector2 getPos();
   Vector2 getSize();
   void updatePos(Vector2 newPos);
   void updateSize(Vector2 newSize);

   void initButtons();
   void addButton(std::unique_ptr<Button> button);
   std::vector<std::unique_ptr<Button>> buttons;
private:
   Vector2 pos;
   Vector2 size;
   Color bgColor;
   bool isShow = true;
   Level& level;
};
