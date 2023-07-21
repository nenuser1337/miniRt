#include "vectors.h"


// float vec2_length(Vec2 v) {
//     return sqrt(v.x * v.x + v.y * v.y);
// }

// float vec3_length(Vec3 v) {
//     return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
// }

float clamp(float x, float min, float max) {
    if (x < min) {
        return min;
    }
    if (x > max) {
        return max;
    }
    return x;
}

float smoothstep(float edge0, float edge1, float x) {
    // Scale, bias and saturate x to 0..1 range
    x = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0); 
    // Evaluate polynomial
    return x * x * (3 - 2 * x);
}


float Circle(Vec2 uv, Vec2 p, float r, float blur) {
    float d = vec2_length(vec2_subtract(uv, p));
    float c =  smoothstep(r, r - blur, d);
    return c;
}


float min(float a, float b) {
    return (a < b) ? a : b;
}

float max(float a, float b) {
    return (a > b) ? a : b;
}

float Band(float t, float start, float end, float blur) {
    float step1 = smoothstep(start - blur, start + blur, t);
    float step2 = smoothstep(end + blur, end - blur, t);
    return step1 * step2;
}

float Rect(Vec2 uv, float left, float right, float bottom, float top, float blur) {
    float band1 = Band(uv.x, left, right, blur);
    float band2 = Band(uv.y, bottom, top, blur);
    return band1 * band2;
}


float remap01(float a, float b, float t) {
    return (t-a) / (b-a);
}

float remap(float a, float b, float c, float d, float t) {
    return remap01(a, b, t) * (d-c) + c;
}

Vec2 vec2_floor_multiply(Vec2 v, float scalar) {
    Vec2 result;
    result.x = floorf(v.x * scalar);
    result.y = floorf(v.y * scalar);
    return result;
}

float mix(float x, float y, float a) {
    return x * (1 - a) + y * a;
}

Vec3 mix_vec3(Vec3 x, Vec3 y, float a) {
    Vec3 result;
    result.r = mix(x.r, y.r, a);
    result.g = mix(x.g, y.g, a);
    result.b = mix(x.b, y.b, a);
    return result;
}

Vec2 fract_vec2(Vec2 v) {
    Vec2 result;
    result.x = v.x - floorf(v.x);
    result.y = v.y - floorf(v.y);
    return result;
}

float dot_vec2(Vec2 v1, Vec2 v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

float step(float edge, float x) {
    return x < edge ? 0.0f : 1.0f;
}
float inversesqrt(float x) {
    return 1.0f / sqrtf(x);
}
