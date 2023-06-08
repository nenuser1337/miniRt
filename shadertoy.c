#include "vectors.h"



void   vec3(t_data *data, Vec3 fragColor, Vec2 fragCoord,Vec2 iResolution) {
    
   
     int color = vec3_to_color(fragColor);
    int i ;
    int j;
    Vec2 center = vec2_create(0.5f, 0.5f);
    float maxDist = sqrt(1.0 * 1.0 + 1.0 * 1.0);  // Calculate max distance


   for(int i = 0; i < WIDTH; i++) {
        for(int j = 0; j < HEIGHT; j++) {
                Vec2 fragCoord = vec2_create((float)i, (float)j);
                Vec2 iResolution = vec2_create((float)WIDTH, (float)HEIGHT);
                
                // Normalized pixel coordinates (from 0 to 1)
                Vec2 uv = vec2_divide_vec(fragCoord, iResolution);

                // Flip the y-coordinate
                uv.y = 1.0 - uv.y;
             uv = vec2_subtract_scalar(uv, 0.5f);
            uv.x *= iResolution.x / iResolution.y;


                Vec2 smtg = vec2_subtract(uv , vec2_create(0.5f, 0.5f));
                // Compute length of uv and normalize it
                float d = vec2_length(uv) / maxDist;
                float r = 0.3;
                float c = smoothstep(r, r-0.01, d );
                    // if (d < 0.3)
                    //      c = 1.0;
                    // else
                    //      c = 0.0;

                Vec3 fragColor = vec3_create(c, c, c);
               
                color = vec3_to_color(fragColor);
                // Convert uv to color
                //int color = uv_to_color(uv);
                
                // Set pixel color
                my_mlx_pixel_put(data, i, j, color);
            }
}

}