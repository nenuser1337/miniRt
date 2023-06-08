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
    vec3(data,fragColor, fragCoord,iResolution);
}
    
int	closing(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(0);
	}
	return (0);
}

int	closingesc(t_data *data)
{
	if (data->img != NULL)
		mlx_destroy_image(data->mlx, data->img);
	if (data->mlx_win != NULL)
		mlx_destroy_window(data->mlx, data->mlx_win);
	exit(0);
	return (0);
}

int	main(void)
{
    
    t_data	img;

    img.mlx = mlx_init();
    img.mlx_win = mlx_new_window(img.mlx, WIDTH, HEIGHT, "Hello world!");
    img.img = mlx_new_image(img.mlx, WIDTH, HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
    draw(&img);
    mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
    
    mlx_hook(img.mlx_win, 2, 1L << 0, closing, &img);
	mlx_hook(img.mlx_win, 17, 0, closingesc, &img);
    mlx_loop(img.mlx);

    return (0);
}

