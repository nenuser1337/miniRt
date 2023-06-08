#include "vectors.h"



Vec2 vec2_create(float x, float y) {
    Vec2 v;
    v.x = x;
    v.y = y;
    return v;
}

Vec2 vec2_add(Vec2 a, Vec2 b) {
    return vec2_create(a.x + b.x, a.y + b.y);
}

Vec2 vec2_subtract(Vec2 a, Vec2 b) {
    return vec2_create(a.x - b.x, a.y - b.y);
}

Vec2 vec2_multiply(Vec2 a, float scalar) {
    return vec2_create(a.x * scalar, a.y * scalar);
}

Vec2 vec2_divide(Vec2 a, float scalar) {
    if (scalar != 0.0) {
        return vec2_create(a.x / scalar, a.y / scalar);
    } else {
        // Handle division by zero error
        // You can return a zero vector, print an error message, or handle it how you prefer
        return vec2_create(0, 0);
    }
}

float vec2_length(Vec2 a) {
    return sqrtf(a.x * a.x + a.y * a.y);
}

Vec2 vec2_normalize(Vec2 a) {
    float len = vec2_length(a);
    if (len != 0.0) {
        return vec2_divide(a, len);
    } else {
        // Handle division by zero error
        // You can return a zero vector, print an error message, or handle it how you prefer
        return vec2_create(0, 0);
    }
}

float vec2_dot(Vec2 a, Vec2 b) {
    return a.x * b.x + a.y * b.y;
}

float vec2_distance(Vec2 a, Vec2 b) {
    Vec2 diff = vec2_subtract(a, b);
    return vec2_length(diff);
}

// Pseudo cross product. In 2D returns a scalar.
float vec2_cross(Vec2 a, Vec2 b) {
    return a.x * b.y - a.y * b.x;
}

Vec2 vec2_divide_vec(Vec2 a, Vec2 b) {
    // Again, handle division by zero as per your needs
    if (b.x != 0.0 && b.y != 0.0) {
        return vec2_create(a.x / b.x, a.y / b.y);
    } else {
        // Handle division by zero error
        // You can return a zero vector, print an error message, or handle it how you prefer
        return vec2_create(0, 0);
    }
}

Vec3 vec3_create(float r, float g, float b) {
    Vec3 color;
    color.r = r;
    color.g = g;
    color.b = b;
    return color;
}

int vec3_to_color(Vec3 color) {
    int r = (int)(color.r * 255.0);
    int g = (int)(color.g * 255.0);
    int b = (int)(color.b * 255.0);

    // The color is in 0xRRGGBB format
    int color_int = (r << 16) | (g << 8) | b;

    return color_int;
}

Vec2 vec2_subtract_scalar(Vec2 a, float scalar) {
    Vec2 result;
    result.x = a.x - scalar;
    result.y = a.y - scalar;
    return result;
}

