#include "sidebar.h"
#include "button.h"
#include "fonts.h"
#include "raylib.h"
#include <memory>
#include <string>
#include "level.h"

SideBar::SideBar(Vector2 pos, Vector2 size, Color bgColor, Level& refLevel):
   pos(pos), size(size), bgColor(bgColor), level(refLevel){}

void SideBar::initButtons(){
   // show sidebar button
   addButton(std::make_unique<ToggleButton>(Vector2 {pos.x, pos.y} , Vector2 {size.x, 40},
                                            "   ^", "   v", GFManager.getFont("sidebar-icon", 42), bgColor,BLACK,
                                            false,[this] () {isShow = !isShow;}));
   // grid buttons
   addButton(std::make_unique<ToggleButton>(Vector2 {pos.x+60, pos.y+90},Vector2 {50, 35},"󰋁 ","󰋂 ",GFManager.getFont("sidebar-icon",42),bgColor,BLACK,
                                            false,[this] () {level.switchGrid();}));
   addButton(std::make_unique<TextButton>(Vector2 {pos.x+8, pos.y+130} , Vector2 {30, 35}, "-", GFManager.getFont("sidebar-text", 42), bgColor,BLACK,
                                          [this] () {--level.gridSize;}));
   addButton(std::make_unique<TextButton>(Vector2 {pos.x+118, pos.y+130} , Vector2 {30, 35}, "+", GFManager.getFont("sidebar-text", 42), bgColor,BLACK,
                                          [this] () {++level.gridSize;}));
}

void SideBar::addButton(std::unique_ptr<Button> button){
   buttons.push_back(std::move(button));
}

void SideBar::draw(){
   if (isShow) {
      DrawRectangleRounded({pos.x, pos.y, size.x, size.y}, 0.5f, 8, bgColor);
      // grid
      DrawTextEx(GFManager.getFont("sidebar-text",42), "GRID", Vector2 {pos.x+40, pos.y+45}, GFManager.getFont("sidebar-text", 36).baseSize, 0, BLACK);
      DrawTextEx(GFManager.getFont("sidebar-text",42), (std::to_string(level.gridSize)).c_str(), Vector2 {pos.x+55, pos.y+130}, GFManager.getFont("sidebar-text", 36).baseSize, 0, BLACK);
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

void SideBar::updatePos(Vector2 newPos) {pos = newPos;}
void SideBar::updateSize(Vector2 newSize) {size = newSize;}
