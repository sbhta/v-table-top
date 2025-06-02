#include "sidebar.h"
#include "button.h"
#include "raylib.h"
#include <memory>

SideBar::SideBar(Vector2 pos, Vector2 size, Color bgColor):
   pos(pos), size(size), bgColor(bgColor){
   addButton(std::make_unique<ToggleButton>(pos , Vector2 {50, 35}, " <", " >", "sidebar-icon", bgColor,BLACK,false,[this] () {isShow = !isShow;}));
   //addButton(std::make_unique<ToggleButton>(Vector2 {pos.x, pos.y+40} , Vector2 {50, 35}, " 󰋁 ", " 󰋂 ", "sidebar-icon", bgColor,BLACK,false,[] () {}));
}
void SideBar::addButton(std::unique_ptr<Button> button){
   buttons.push_back(std::move(button));
}

void SideBar::draw(){
   if (isShow) {
      DrawRectangleRounded({pos.x, pos.y, size.x, size.y}, 0.5f, 8, bgColor);
      for (auto& button : buttons){
         button->draw();
      }
   }
   else {
      buttons[0]->draw();
   }
}
void SideBar::update(Vector2 mousePos, bool mousePressed){
   if (isShow){
      for (auto& button : buttons){
         button->update(mousePos, mousePressed);
      }
   }
   else {
      buttons[0]->update(mousePos, mousePressed);
   }
}
