#include "sidebar.h"
#include "button.h"
#include "fonts.h"
#include "raylib.h"
#include <memory>
#include <string>
#include "level.h"
#include "raymath.h"

SideBar::SideBar(Vector2 pos, Vector2 size, Color bgColor,Color fgColor, Level& refLevel):
   pos(pos), size(size), bgColor(bgColor),fgColor(fgColor), level(refLevel){}

// Load levelButtons thar are always supposed to be in the sidebar
void SideBar::initButtons(){
   // show sidebar button
   addButton(levelButtons, std::make_unique<ToggleButton>(Vector2 {pos.x, pos.y} , Vector2 {size.x, 40},
                                            "   ^", "   v", GFM.getFont("sidebar-icon", 42),
                                            bgColor,fgColor,
                                            false,[this] () {isShow = !isShow;}));
   // grid levelButtons
   addButton(levelButtons, std::make_unique<ToggleButton>(Vector2 {pos.x+60, pos.y+90},Vector2 {50, 35},"󰋁 ","󰋂 ",GFM.getFont("sidebar-icon",42),
                                            bgColor,fgColor,
                                            false,[this] () {level.switchGrid();}));
   addButton(levelButtons, std::make_unique<TextButton>(Vector2 {pos.x+8, pos.y+130} , Vector2 {30, 35}, "-", GFM.getFont("sidebar-text", 42),
                                          bgColor,fgColor,
                                          [this] () {--level.gridSize;}));
   addButton(levelButtons, std::make_unique<TextButton>(Vector2 {pos.x+118, pos.y+130} , Vector2 {30, 35}, "+", GFM.getFont("sidebar-text", 42),
                                          bgColor,fgColor,
                                          [this] () {++level.gridSize;}));
   // Token visual buttons
   addButton(tokenButtons, std::make_unique<TextButton>(Vector2 {pos.x+118, pos.y+280} , Vector2 {30, 35}, "+", GFM.getFont("sidebar-text", 42),
                                          bgColor,fgColor,
                                          [this] () {level.selectedToken->updateSize(Vector2Add(level.selectedToken->getSize(), Vector2 {10, 10}));}));
   addButton(tokenButtons, std::make_unique<TextButton>(Vector2 {pos.x+8, pos.y+280} , Vector2 {30, 35}, "-", GFM.getFont("sidebar-text", 42),
                                          bgColor,fgColor,
                                          [this] () {level.selectedToken->updateSize(Vector2Add(level.selectedToken->getSize(), Vector2 {-10, -10}));}));
}
void SideBar::addButton(std::vector<std::unique_ptr<Button>>& group, std::unique_ptr<Button> button){
   group.push_back(std::move(button));
}
void SideBar::draw(){
   if (isShow) {
      DrawRectangleRounded({pos.x, pos.y, size.x, size.y}, 0.5f, 8, bgColor);
      // grid
      DrawTextEx(GFM.getFont("sidebar-text",36), "GRID", Vector2 {pos.x+40, pos.y+45},
                 GFM.getFont("sidebar-text", 36).baseSize, 0, fgColor);
      DrawTextEx(GFM.getFont("sidebar-text",36), (std::to_string(level.gridSize)).c_str(), Vector2 {pos.x+55, pos.y+130},
                 GFM.getFont("sidebar-text", 36).baseSize, 0, fgColor);
      for (auto& btn : levelButtons){
         btn->draw();
      }
      if (level.selectedToken) {
         for (auto& btn : tokenButtons){
            btn->draw();
         }
      }
   }
   else {
      levelButtons[0]->draw();
   }
}
void SideBar::update(Vector2 mousePos, bool mousePressed){
   if (isShow){
      for (auto& button : levelButtons){
         button->update(mousePos, mousePressed);
      }
      if (level.selectedToken) {
         for (auto& btn : tokenButtons){
            btn->update(mousePos, mousePressed);
         }
      }
   }
   else {
      levelButtons[0]->update(mousePos, mousePressed);
   }
}
void SideBar::updatePos(Vector2 newPos) {pos = newPos;}
void SideBar::updateSize(Vector2 newSize) {size = newSize;}
