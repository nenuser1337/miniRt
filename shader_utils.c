#include "vectors.h"

Vec3 vec3_mix(Vec3 x, Vec3 y, float a)
{
    float invA = 1.0f - a;
    return vec3_create(
        x.r * invA + y.r * a,
        x.g * invA + y.g * a,
        x.b * invA + y.b * a
    );
}

Vec2 vec2_max(Vec2 x, Vec2 y)
{
    return vec2_create(
        fmaxf(x.x, y.x),
        fmaxf(x.y, y.y)
    );
}

Vec3 vec3_max(Vec3 x, Vec3 y)
{
    return vec3_create(
        fmaxf(x.r, y.r),
        fmaxf(x.g, y.g),
        fmaxf(x.b, y.b)
    );
}

Vec2 vec2_min(Vec2 x, Vec2 y)
{
    return vec2_create(
        fminf(x.x, y.x),
        fminf(x.y, y.y)
    );
}

Vec3 vec3_min(Vec3 x, Vec3 y)
{
    return vec3_create(
        fminf(x.r, y.r),
        fminf(x.g, y.g),
        fminf(x.b, y.b)
    );
}

float dot_float(float x, float y)
{
    return x * y;
}

// float dot_vec2(Vec2 x, Vec2 y)
// {
//     return x.x * y.x + x.y * y.y;
// }

// float dot_vec3(Vec3 x, Vec3 y)
// {
//     return x.r * y.r + x.g * y.g + x.b * y.b;
// }

// float dot_vec4(Vec4 x, Vec4 y)
// {
//     return x.r * y.r + x.g * y.g + x.b * y.b + x.a * y.a;
// }

float mix_float(float x, float y, float a)
{
    return x * (1.0 - a) + y * a;
}

float normalize_float(float x)
{
    return x / length_float(x);
}

Vec2 normalize_vec2(Vec2 x)
{
    float len = length_vec2(x);
    return vec2_divide_scalar(x, len);
}

Vec3 normalize_vec3(Vec3 x)
{
    float len = length_vec3(x);
    return vec3_divide_scalar(x, len);
}
Vec3 vec3_pow(Vec3 v, Vec3 p) {
    Vec3 result;
    result.r = powf(v.r, p.r);
    result.g = powf(v.g, p.g);
    result.b = powf(v.b, p.b);
    return result;
}

float length_float(float v) {
    return fabsf(v);
}

float length_vec3(Vec3 v) {
    return sqrtf(v.r * v.r + v.g * v.g + v.b * v.b);
}

float length_vec2(Vec2 v) {
    return sqrtf(v.x * v.x + v.y * v.y);
}

Vec2 vec2_divide_scalar(Vec2 v, float scalar) {
    Vec2 result;
    result.x = v.x / scalar;
    result.y = v.y / scalar;
    return result;
}

Vec3 vec3_divide_scalar(Vec3 v, float scalar) {
    Vec3 result;
    result.r = v.r / scalar;
    result.g = v.g / scalar;
    result.b = v.b / scalar;
    return result;
}

Vec3 vec3_subtract(Vec3 a, Vec3 b)
{
    Vec3 result;
    result.r = a.r - b.r;
    result.g = a.g - b.g;
    result.b = a.b - b.b;
    return result;
}

Vec3 vec3_add(Vec3 vec1, Vec3 vec2)
{
    Vec3 result;
    result.r = vec1.r + vec2.r;
    result.g = vec1.g + vec2.g;
    result.b = vec1.b + vec2.b;
    return result;
}

float mod(float a, float b) {
    float result = fmodf(a, b);
    return result >= 0.0f ? result : result + b;
}


