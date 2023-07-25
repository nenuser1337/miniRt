#ifndef VEC_H
#define VEC_H

#define WIDTH 750
#define HEIGHT 500
#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include <stdbool.h>

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
    int     mouse_x;
    int     mouse_y;
}               t_vars;


typedef struct {
    float r, g, b;
} Vec3;

typedef struct Ray
{
    Vec3 o;
    Vec3 d;
}  Ray;

typedef struct {
    float x, y;
} Vec2;

typedef struct {
    float x, y, z, w;
} Vec4;
/*
// typedef struct {
//     float m11, m12, m13;
//     float m21, m22, m23;
//     float m31, m32, m33;
// } Mat3;
*/

typedef struct {
    float m[3][3];
} mat3;



struct Sphere
{
    Vec3 color;
    Vec3 position;
    float radius;     
} sphere;

struct Light
{
	Vec3 position;
    Vec3 color;
    float brightness;  
} light;


struct AmbientLight
{
    float ratio;
    Vec3 color;
} ambientLight;


struct Camera {
    Vec3 position;
    Vec3 direction;
    float fov;
}   camera;

struct Material {
    float ambience;  // The ambient reflection coefficient
    float diffuse;   // The diffuse reflection coefficient
    float specular;  // The specular reflection coefficient
    float shininess; // The shininess coefficient
} material;

 struct Plane{
    Vec3 normal;
    float distance;
    Vec3 color;
} plane;

 struct Cylinder
{
    Vec3 color;
    Vec3 position;
    float radius;
    float height;     
} cylinder;


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
// void mainImage(t_data *data ,Vec3 fragColor, Vec2 fragCoord , Vec2 iResolution);
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
int animation(t_vars *vars);
Vec3 vec3_add_scalar(Vec3 v, float scalar);
int render_next_frame(t_vars *vars);
void waving_rec(t_vars *vars);
int waves(t_vars *vars);
float remap(float a, float b, float c, float d, float t);
float remap01(float a, float b, float t);
Vec3 ToGamma(Vec3 col);
Vec3 vec3_mix(Vec3 x, Vec3 y, float a);
Vec3 vec3_max(Vec3 x, Vec3 y);
Vec2 vec2_max(Vec2 x, Vec2 y);
Vec3 vec3_min(Vec3 x, Vec3 y);
Vec2 vec2_min(Vec2 x, Vec2 y);
float dot_float(float x, float y);
// float dot_vec2(Vec2 x, Vec2 y);
// float dot_vec3(Vec3 x, Vec3 y);
float dot_vec4(Vec4 x, Vec4 y);
float mix_float(float x, float y, float a);
float normalize_float(float x);
Vec2 normalize_vec2(Vec2 x);
Vec3 normalize_vec3(Vec3 x);
Vec3 vec3_pow(Vec3 v, Vec3 p);
float length_float(float v);
float length_vec2(Vec2 v);
float length_vec3(Vec3 v);
Vec2 vec2_divide_scalar(Vec2 v, float scalar);
Vec3 vec3_divide_scalar(Vec3 v, float scalar) ;
//Vec3 sphere(Vec2 pos, Vec2 frag, Vec3 lightPos, float r);
Vec3 vec3_subtract(Vec3 a, Vec3 b);
Vec3 vec3_add(Vec3 vec1, Vec3 vec2);
int draw_sphere( t_vars *vars );
float mod(float a, float b);
float fract_float(float x);
float floor_float(float x);
Vec2 floor_2(Vec2 v);
Vec3 Checker(Vec3 p);
Vec2 vec2_multiply_double(Vec2 v, double scalar);
float sdPlane(Vec3 p);
float GetDist(Vec3 p);
float RayMarching(Ray r);
Vec3 vec3_multiply_float(Vec3 v, float scalar) ;
float GetLight(Vec3 p);
Ray InitOrbCam(Vec3 pos, Vec3 dir, float speed);
// Mat3 mat3_create(float m11, float m12, float m13,
//                  float m21, float m22, float m23,
//                  float m31, float m32, float m33);


// int plane(t_vars *vars );
// Vec3 vec3_multiply_mat3(Vec3 vec, Mat3 mat);
Vec3 cross_vec3(Vec3 x, Vec3 y);
float DistLine(Vec3 ro, Vec3 rd, Vec3 p);
void setupScene();
bool solveQuadratic(float a, float b, float c,  float *t0,  float *t1);
bool intersect(Vec3 direction, Vec3 *surfaceNormal);
Vec3 rayTrace(Vec3 direction);
int sphere_shader(t_vars *vars);
int mouse_move(int x, int y, t_vars *vars);
Vec3 reflect(Vec3 I, Vec3 N) ;
float sdSphere(Vec3 p, float r);
int texture(t_vars *vars);
mat3 mat3_transpose(mat3 m);
mat3 mat3_create(Vec3 t, Vec3 b, Vec3 n);
Vec3 mat3_mul_vec3(mat3 m, Vec3 v);
Vec2 vec2_floor_multiply(Vec2 v, float scalar) ;
float mix(float x, float y, float a);
Vec3 mix_vec3(Vec3 x, Vec3 y, float a);
Vec2 fract_vec2(Vec2 v);
float dot_vec2(Vec2 v1, Vec2 v2);
float dot_vec3(Vec3 v1, Vec3 v2);
float step(float edge, float x);
float inversesqrt(float x);
int cylinder_raytracing(t_vars *vars);
float sign(float x);
bool intersect_sphere(Vec3 direction, Vec3 *surfaceNormal);
int rendering(t_vars *vars);
float vec3_length_squared(Vec3 v);
Vec3 vec3_multiply_vec(Vec3 a, Vec3 b);
bool vec3_equals(Vec3 a, Vec3 b);
Vec3 vec3_negate(Vec3 v);
#endif