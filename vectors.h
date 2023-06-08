#ifndef VEC_H
#define VEC_H

#define WIDTH 750
#define HEIGHT 500
#include <mlx.h>
#include <math.h>
#include <stdlib.h>

typedef struct	s_data {
	void	*mlx;
    void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_data;

typedef struct {
    float r, g, b;
} Vec3;

typedef struct {
    float x, y;
} Vec2;

Vec2 vec2_create(float x, float y);
 Vec2 vec2_add(Vec2 a, Vec2 b);
Vec2 vec2_subtract(Vec2 a, Vec2 b);
Vec2 vec2_multiply(Vec2 a, float scalar);
Vec2 vec2_divide(Vec2 a, float scalar);
float vec2_length(Vec2 a);
Vec2 vec2_normalize(Vec2 a);
float vec2_dot(Vec2 a, Vec2 b);
float vec2_distance(Vec2 a, Vec2 b);
float vec2_cross(Vec2 a, Vec2 b);
int uv_to_color(Vec2 uv);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void   draw(t_data *data);
Vec2 vec2_divide_vec(Vec2 a, Vec2 b);
Vec3 vec3_create(float r, float g, float b);
int vec3_to_color(Vec3 color);
void   vec3(t_data *data, Vec3 fragColor, Vec2 fragCoord,Vec2 iResolution);
void mainImage(t_data *data ,Vec3 fragColor, Vec2 fragCoord , Vec2 iResolution);
int	close(int keycode, t_data *img);
int	closing2(int keycode, t_data *data);
int	closing(int keycode, t_data *data);
int	closingesc(t_data *data);
float vec2_length(Vec2 v);
float vec3_length(Vec3 v);
Vec2 vec2_subtract_scalar(Vec2 a, float scalar);
#endif