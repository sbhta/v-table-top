#pragma once

#include "raylib.h"
#include <map>
#include <string>
class ColorManager{
public:
   ColorManager();
   ~ColorManager();
   void addColor(const std::string& name, const std::string& hex);
   bool getTheme(const std::string& themePath);
   Color& getColor(const std::string& name);
private:
   std::map<std::string, Color> colors;
};
extern ColorManager GCM;

