#pragma once

#include "raylib.h"
#include <map>
#include <string>
class FontManager{
public:
   ~FontManager();
   void loadFont(const std::string& name, const std::string& filePath, int size);
   Font& getFont(const std::string& name, int size);
   void unloadAll();
private:
   std::map<std::string, std::map<int, Font>> fonts;
};
extern FontManager GFM;
