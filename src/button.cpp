#include "button.h"
#include "raylib.h"
#include <functional>

// general button
Button::Button(Vector2 startPos, Vector2 startSize, std::function<void()> buttonFunction){
   updatePos(startPos);
   updateSize(startSize);
   bounds = {pos.x, pos.y, size.x, size.y};
   func = buttonFunction;
}
void Button::update(Vector2 mousePos, bool mousePressed){
   hovered = CheckCollisionPointRec(mousePos, bounds);
   pressed = hovered && mousePressed;
   if (pressed) {
      onClick();
   }
}
void Button::draw() const {
   if (pressed) DrawRectangleRounded(bounds, 0.5f,8, PINK);
   else DrawRectangleRounded(bounds, 0.5f,8, WHITE) ;
}
void Button::onClick(){
   if (func) func();
}
Vector2 Button::getPos(){
   return pos;
}
Vector2 Button::getSize(){
   return size;
}
void Button::updatePos(Vector2 newPos){
   pos = newPos;
   bounds.x = newPos.x;
   bounds.y = newPos.y;
}
void Button::updateSize(Vector2 newSize){
   size = newSize;
   bounds.width=newSize.x;
   bounds.height=newSize.y;
}
// text button 
TextButton::TextButton(Vector2 pos,
                       Vector2 size,
                       const std::string& startLabel,
                       Font& font,
                       Color startBgColor,
                       Color startFgColor,
                       std::function<void()> buttonFunction):
   Button(pos, size, buttonFunction) , label(startLabel), font(font), bgColor(startBgColor), fgColor(startFgColor){}
void TextButton::draw() const{
   DrawRectangleRounded(bounds, 0.5f,8, bgColor);
   DrawTextEx(font,label.c_str(), pos, font.baseSize, 1, fgColor);
}
void TextButton::updateLabel(const std::string& newLabel){
   label = newLabel;
}
// toggle button
ToggleButton::ToggleButton(Vector2 pos,
                           Vector2 size,
                           const std::string& startOnLable,
                           const std::string& startOffLabel,
                           Font& font,
                           Color startBgColor,
                           Color startFgColor,
                           bool startState,
                           std::function<void()> buttonFunction):
   TextButton(pos, size, "", font, startBgColor, startFgColor, buttonFunction),onLabel(startOnLable), offLabel(startOffLabel),  isOn(startState){};
void ToggleButton::draw() const{
   DrawRectangleRounded(bounds, 0.5f,8, bgColor);
   DrawTextEx(font,(isOn?onLabel:offLabel).c_str(), pos, font.baseSize, 1, fgColor);
}
void ToggleButton::onClick(){
   isOn = !isOn;
   if (func) func();
}
