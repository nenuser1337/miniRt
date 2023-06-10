#include "vectors.h"





int uv_to_color(Vec2 uv) {
    // Convert the normalized uv.x value to an integer in the range 0 - 255
    int color_intensity = (int)(uv.x * 255.0);
    
    // The color will be in 0xRRGGBB format
    int color = (color_intensity << 16) | (color_intensity << 8) | color_intensity;

    return color;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


// draw a square
void   draw(t_data *data) {
    
        Vec2 fragCoord ;
       
        Vec3 fragColor = vec3_create(1.0, 1.0, 0.0);
        Vec2 iResolution = vec2_create((float)WIDTH, (float)HEIGHT);		

        mainImage(data, fragColor, fragCoord, iResolution);
           
}

void mainImage(t_data *data ,Vec3 fragColor, Vec2 fragCoord , Vec2 iResolution)
{
     // Normalized pixel coordinates (from 0 to 1)
        Vec2 uv = vec2_divide_vec(fragCoord, iResolution);

    
    // Output to screen , we have black screen here
    //vec3(data,fragColor, fragCoord,iResolution);
    //drawRectangle(data);
    animation(data);
}
    

int render_next_frame(t_vars *vars)
{
    static clock_t start_time = 0;
    double scaling_factor = 1; // speed up the animation
  
    if (start_time == 0) start_time = clock();

    double time_in_seconds = ((double)(clock() - start_time) / CLOCKS_PER_SEC) * scaling_factor;

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
            my_mlx_pixel_put(&vars->img, i, j, color);
        }
    }
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
    return (0);
}

int	closing(int keycode, t_vars  *data)
{
	if (keycode == 53)
	{
		mlx_destroy_image(data->mlx, data->img.img);
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	return (0);
}

// int	closingesc(t_vars  *data)
// {
// 	if (data->img != NULL)
// 		mlx_destroy_image(data->mlx, data->img);
// 	if (data->win != NULL)
// 		mlx_destroy_window(data->mlx, data->win);
// 	exit(0);
// 	return (0);
// }
int waves(t_vars *vars)
{
     static clock_t start_time = 0;
    double scaling_factor =2; // speed up the animation
  
    if (start_time == 0) start_time = clock();

    double time_in_seconds = ((double)(clock() - start_time) / CLOCKS_PER_SEC) * scaling_factor;

    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            Vec2 fragCoord = vec2_create((float)i, (float)j);
            Vec2 iResolution = vec2_create((float)WIDTH, (float)HEIGHT);

            // Normalized pixel coordinates (from 0 to 1)
            Vec2 uv = vec2_divide_vec(fragCoord, iResolution);
            uv = vec2_subtract_scalar(uv, 0.5f);
            uv.x *= iResolution.x / iResolution.y;

            float x = uv.x;
            float m = sinf(time_in_seconds + x * 8.0f) * 0.1f;
            float y = uv.y - m;
            float blur = remap(-.5, .5, .01, .25, uv.x);
            blur = pow(blur * 4., 3);
            float mask = Rect(vec2_create(x, y), -0.5f, 0.5f, -0.1f, 0.1f, blur);
            Vec3 col = vec3_multiply_scalar(vec3_create(1.0f, 1.0f, 1.0f), mask);

            // Set pixel color
            my_mlx_pixel_put(&vars->img, i, j, vec3_to_color(col));
        }
    }

    mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
    return 0;

}

int main(void)
{
    t_vars  vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Hello world!");
    vars.img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
    vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length,
                                 &vars.img.endian);

    mlx_loop_hook(vars.mlx, waves, &vars);
      
    mlx_hook(vars.win, 2, 1L << 0, closing, &vars);
	//mlx_hook(vars.win, 17, 0, closingesc, &vars);
    mlx_loop(vars.mlx);
}