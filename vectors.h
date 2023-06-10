#ifndef VEC_H
#define VEC_H

#define WIDTH 750
#define HEIGHT 500
#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


#include <time.h>


typedef struct	s_data {
	void	*mlx;
    void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_data;

typedef struct  s_vars {
    void        *mlx;
    void        *win;
    t_data      img;
}               t_vars;

typedef struct {
    float r, g, b;
} Vec3;

typedef struct {
    float x, y;
} Vec2;

typedef struct {
    float x, y, z, w;
} Vec4;

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
int	close(int keycode, t_vars  *img);
int	closing2(int keycode, t_vars  *data);
int	closing(int keycode, t_vars  *data);
int	closingesc(t_vars  *data);
float vec2_length(Vec2 v);
float vec3_length(Vec3 v);
Vec2 vec2_subtract_scalar(Vec2 a, float scalar);
float clamp(float x, float min, float max);
float smoothstep(float edge0, float edge1, float x);
float Circle (Vec2 uv, Vec2 p, float r, float blur);	
Vec4 vec4_create(float x, float y, float z, float w);
int vec4_to_color(Vec4 color);
float min(float a, float b);
float max(float a, float b);
Vec3 vec3_multiply_scalar(Vec3 v, float scalar);
float Band(float t, float start, float end, float blur);
float Rect(Vec2 uv, float left, float right, float bottom, float top, float blur);
void drawRectangle(t_data *data);
int animation(t_data *data);
Vec3 vec3_add_scalar(Vec3 v, float scalar);
int render_next_frame(t_vars *vars);
void waving_rec(t_vars *vars);
int waves(t_vars *vars);
float remap(float a, float b, float c, float d, float t);
float remap01(float a, float b, float t);
#endif