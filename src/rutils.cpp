#include "rutils.h"
#include <sstream>

Texture2D ResizeTexture(Texture2D texture, int newWidth, int newHeight) {
   // Create a render texture to draw into
   RenderTexture2D render = LoadRenderTexture(newWidth, newHeight);

   // Draw the original texture to the new size into the render texture
   BeginTextureMode(render);
   ClearBackground(BLANK); // Optional
   DrawTexturePro(
      texture,
      (Rectangle){ 0, 0, (float)texture.width, (float)-texture.height }, // Flip vertically
      (Rectangle){ 0, 0, (float)newWidth, (float)newHeight },
      (Vector2){ 0, 0 },
      0.0f,
      WHITE
   );
   EndTextureMode();

   // Extract the texture from the render texture
   Image image = LoadImageFromTexture(render.texture); // Copy it as an image
   Texture2D resized = LoadTextureFromImage(image);    // Convert back to texture

   // Clean up
   UnloadImage(image);
   UnloadRenderTexture(render);

   return resized;
}
int GetAccurateCurrentMonitor() {
   Vector2 windowPos = GetWindowPosition();

   int monitorCount = GetMonitorCount();
   for (int i = 0; i < monitorCount; i++) {
      int x = GetMonitorPosition(i).x;
      int y = GetMonitorPosition(i).y;
      int w = GetMonitorWidth(i);
      int h = GetMonitorHeight(i);

      if (windowPos.x >= x && windowPos.x < (x + w) &&
         windowPos.y >= y && windowPos.y < (y + h)) {
         return i;
      }
   }

   return 0; // fallback to primary monitor
}

Color HexToColor(const std::string& hex) {
    std::string hexCode = hex;

    // Remove '#' if it exists
    if (hexCode[0] == '#') hexCode = hexCode.substr(1);

    // Default alpha
    unsigned char r = 0, g = 0, b = 0, a = 255;

    if (hexCode.length() == 6 || hexCode.length() == 8) {
        std::stringstream ss;
        unsigned int hexValue;
        ss << std::hex << hexCode.substr(0, 6);
        ss >> hexValue;

        r = (hexValue >> 16) & 0xFF;
        g = (hexValue >> 8) & 0xFF;
        b = hexValue & 0xFF;

        if (hexCode.length() == 8) {
            std::stringstream ssAlpha;
            ssAlpha << std::hex << hexCode.substr(6, 2);
            unsigned int alphaValue;
            ssAlpha >> alphaValue;
            a = static_cast<unsigned char>(alphaValue);
        }
    }

    return Color{r, g, b, a};
}
