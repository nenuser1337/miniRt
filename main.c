#include "vectors.h"



void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}



int rendering(t_vars *vars)
{
    // Initialize the scene
    setupScene();
    
    // For every pixel on the screen
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            // Compute the pixel coordinates
            Vec2 fragCoord = vec2_create((float)i, (float)j);
            Vec2 iResolution = vec2_create((float)WIDTH, (float)HEIGHT);

            // Normalize the pixel coordinates
            Vec2 uv = vec2_divide_vec(fragCoord, iResolution);
            uv = vec2_subtract_scalar(uv, 0.5f);
            uv.x *= iResolution.x / iResolution.y;

            // Adjust uv coordinates based on the FOV
            uv.x *= camera.fov;
            uv.y *= camera.fov;

            // Compute the direction from the camera to the pixel
            Vec3 direction = normalize_vec3(vec3_subtract(vec3_create(uv.x, uv.y, 1.0), camera.position));
            // Trace the ray and compute the pixel color
            Vec3 col = rayTrace(direction);

            // Clamp the color components to the range [0, 1]
            col.r = fmax(0.0, fmin(col.r, 1.0));
            col.g = fmax(0.0, fmin(col.g, 1.0));
            col.b = fmax(0.0, fmin(col.b, 1.0));

            // Convert the color to RGBA format
            Vec4 fragColor = vec4_create(col.r, col.g, col.b, 0.0f);
            int color = vec4_to_color(fragColor);

            // Set the pixel color
            my_mlx_pixel_put(&vars->img, i, j, color);
        }
    }

    // Render the image to the window
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
    return 0;
}

int mouse_move(int x, int y, t_vars *vars)
{
    vars->mouse_x = x;
    vars->mouse_y = y;
    return (0);
}
int main(void)
{
    t_vars  vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "miniRt");
    vars.img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
    vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length,
                                 &vars.img.endian);
  

    mlx_loop_hook(vars.mlx,rendering , &vars);
    
     mlx_loop(vars.mlx);
}