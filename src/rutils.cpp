#include "rutils.h"

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

