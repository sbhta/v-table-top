#pragma once

#include "raylib.h"
#include <map>
#include <string>
class FontManager{
public:
   ~FontManager();
   void loadFont(const std::string& name, const std::string& filePath, int size);
   Font& getFont(const std::string& name);
   void unloadAll();
private:
   std::map<std::string, Font> fonts;
};

extern FontManager GFManager;
