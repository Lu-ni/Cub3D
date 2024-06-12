# Cub3D
## Design
 - Parser
 - Texture Loader
   - Texture atlas
 - Screen Drawer (I'm wondering if we can use the multi-threading of minilibx to chunk the screen)
   - Double Buffering: Use double buffering to prevent flickering and tearing.
   - Occlusion Culling: Skip rendering objects that are occluded by other objects.
   - Backface Culling: Skip rendering the back faces of walls and objects.
 - Ray-casting module
   - fast sqrt / hashmap
   - compilator optimisation
   - keeping the memory close (maybe ChunkyChunk will be used here !!!!)
 - Key event handler
 - GUI module (HUD and menu)
