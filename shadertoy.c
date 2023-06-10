#include "vectors.h"



void   vec3(t_data *data, Vec3 fragColor, Vec2 fragCoord,Vec2 iResolution) {
    
   
    int i ;
    int j;
    float maxDist = sqrt(1.0 * 1.0 + 1.0 * 1.0);  // Calculate max distance


   for(int i = 0; i < WIDTH; i++) {
        for(int j = 0; j < HEIGHT; j++) {
                Vec2 fragCoord = vec2_create((float)i, (float)j);
                Vec2 iResolution = vec2_create((float)WIDTH, (float)HEIGHT);
                
        // Normalized pixel coordinates (from 0 to 1)
        Vec2 uv = vec2_divide_vec(fragCoord, iResolution);

        // Flip the y-coordinate and shift origin to center
        uv.y = 1.0f - uv.y;
        uv = vec2_subtract_scalar(uv, 0.5f);
        uv.x *= iResolution.x / iResolution.y;

        Vec3 col = vec3_multiply_scalar(vec3_create(1.0f, 0.0f, 1.0f), 1.0f);
        float c = Circle(uv, vec2_create(0.f, 0.f), .4f, .05f);
        c -= Circle(uv, vec2_create(.13f, .2f), .07f, .01f);
         c -= Circle(uv, vec2_create(-.13f, .2f), .07f, .01f);
        //c = max(0.0, min(c, 1.0));
         float mouth = Circle(uv, vec2_create(0.f, 0.f), .3f, .02f);
        mouth -= Circle(uv, vec2_create(0.f, 0.1f), .3f, .02f);
        c -= mouth;
         c = max(0.0, min(c, 1.0));
        col = vec3_multiply_scalar(vec3_create(1.0f, 1.0f, 0.0f), c);
        // Output to screen
        Vec4 fragColor = vec4_create(col.r, col.g, col.b, 0.0f);
        int color = vec4_to_color(fragColor);

        // Set pixel color
        my_mlx_pixel_put(data, i, j, color);
    
            }
    }

}
void drawRectangle(t_data *data) {
    for(int i = 0; i < WIDTH; i++) {
        for(int j = 0; j < HEIGHT; j++) {
            Vec2 fragCoord = vec2_create((float)i, (float)j);
            Vec2 iResolution = vec2_create((float)WIDTH, (float)HEIGHT);

            // Normalized pixel coordinates (from 0 to 1)
            Vec2 uv = vec2_divide_vec(fragCoord, iResolution);

            // Flip the y-coordinate and shift origin to center
            uv.y = 1.0f - uv.y;
            uv = vec2_subtract_scalar(uv, 0.5f);
            uv.x *= iResolution.x / iResolution.y;

            Vec3 col = vec3_create(0.0f, 0.0f, 0.0f);
            float mask = Rect(uv, -0.2f, 0.2f, -0.3f, 0.3f, 0.01f);

            col = vec3_multiply_scalar(vec3_create(1.0f, 1.0f, 1.0f), mask);

            // Output to screen
            Vec4 fragColor = vec4_create(col.r, col.g, col.b, 0.0f);
            int color = vec4_to_color(fragColor);

            // Set pixel color
            my_mlx_pixel_put(data, i, j, color);
        }
    }
}


int animation(t_data *data) {
    clock_t start_time = clock();
    double time_in_seconds = (double)start_time / CLOCKS_PER_SEC;

    for(int i = 0; i < WIDTH; i++) {
        for(int j = 0; j < HEIGHT; j++) {
            Vec2 fragCoord = vec2_create((float)i, (float)j);
            Vec2 iResolution = vec2_create((float)WIDTH, (float)HEIGHT);

            // Normalized pixel coordinates (from 0 to 1)
            Vec2 uv = vec2_divide_vec(fragCoord, iResolution);

            // Time varying pixel color
            Vec3 col = vec3_create(
                0.5f + 0.5f * cosf(time_in_seconds + uv.x + 0),
                0.5f + 0.5f * cosf(time_in_seconds + uv.x + 2),
                0.5f + 0.5f * cosf(time_in_seconds + uv.x + 4)
            );

            // Output to screen
            Vec4 fragColor = vec4_create(col.r, col.g, col.b, 0.0f);
            int color = vec4_to_color(fragColor);

            // Set pixel color
            my_mlx_pixel_put(data, i, j, color);
        }
    }

    return 0;
}