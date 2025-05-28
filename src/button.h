#pragma once
#include "raylib.h"
#include <string>

class Button{
protected:
   Rectangle bounds;
   Vector2 pos;
   Vector2 size;
   bool hovered = false;
   bool pressed = false;
public:
   Button(Vector2 pos, Vector2 size);
   Vector2 getPos();
   Vector2 getSize();
   void updatePos(Vector2 newPos);
   void updateSize(Vector2 newSize);
   virtual ~Button() = default;
   virtual void update(Vector2 mousePos, bool mousePressed);
   virtual void draw() const;
   virtual void onClick();
};

class TextButton : public Button {
protected:
   std::string label;
public:
   TextButton(Vector2 pos, Vector2 size, const std::string& startLabel);
   void draw() const override;
   void onClick() override;
};


