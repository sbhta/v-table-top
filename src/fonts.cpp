#include "fonts.h"
#include "raylib.h"
#include <string>
#include <vector>

void FontManager::loadFont(const std::string& name, const std::string& filePath, int size){
   std::vector<int> codepoints = {0xf02c2}; // SPECIAL ICONS FROM NERDFONT
   for (int i = 0x20; i <= 0x7E; i++) codepoints.push_back(i);
   for (int i = 0xA0; i <= 0xFF; i++) codepoints.push_back(i);
   fonts[name] = LoadFontEx(filePath.c_str(), size, codepoints.data(), codepoints.size());
}

Font& FontManager::getFont(const std::string& name){
   return fonts.at(name);
}

void FontManager::unloadAll(){
   for (auto& [name, font] : fonts){
      UnloadFont(font);
   }
   fonts.clear();
}

FontManager::~FontManager(){
   unloadAll();
}

FontManager GFManager;
