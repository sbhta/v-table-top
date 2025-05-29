#pragma once
#include "raylib.h"
#include <functional>
#include <string>

class Button{
protected:
   Rectangle bounds;
   Vector2 pos;
   Vector2 size;
   bool hovered = false;
   bool pressed = false;
public:
   Button(Vector2 pos, Vector2 size, std::function<void()> buttonFunction);
   Vector2 getPos();
   Vector2 getSize();
   void updatePos(Vector2 newPos);
   void updateSize(Vector2 newSize);
   virtual ~Button() = default;
   virtual void update(Vector2 mousePos, bool mousePressed);
   virtual void draw() const;
   virtual void onClick();
   std::function<void()> func;
};

class TextButton : public Button {
protected:
   std::string label;
   int fontSize;
   Color bgColor;
   Color fgColor;
public:
   TextButton(Vector2 pos, Vector2 size, const std::string& startLabel, int startFontSize, Color startBgColor, Color startFgColor, std::function<void()> buttonFunction);
   void draw() const override;
   void updateLabel(const std::string& newLabel);
};


