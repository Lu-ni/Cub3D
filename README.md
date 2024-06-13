# Cub3D
## Design
 - Parser
   - The map is not always square, we still need to check if the map is close (maybe using -1 for the outside and then check that each -1 touch a 1)
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
