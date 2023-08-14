#include "vectors.h"


#define EPSILON 1e-6

bool vec3_equals(Vec3 a, Vec3 b) {
    return fabs(a.r - b.r) < EPSILON && fabs(a.g - b.g) < EPSILON && fabs(a.b - b.b) < EPSILON;
}

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

Vec4 vec4_create(float x, float y, float z, float w) {
    Vec4 v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return v;
}

int vec4_to_color(Vec4 color) {
    int r = (int)(color.x * 255);
    int g = (int)(color.y * 255);
    int b = (int)(color.z * 255);
    int a = (int)(color.w * 255);

    // Assuming you're using a 32-bit color depth (ARGB), and color components are in the range [0, 255]
    return (a << 24) + (r << 16) + (g << 8) + b;
}
Vec3 vec3_multiply_scalar(Vec3 v, float scalar) {
    v.r *= scalar;
    v.g *= scalar;
    v.b *= scalar;
    return v;
}

Vec3 vec3_add_scalar(Vec3 v, float scalar) {
    v.r += scalar;
    v.g += scalar;
    v.b += scalar;
    return v;
}

Vec3 cross_vec3(Vec3 x, Vec3 y) {
    Vec3 result;
    result.r = x.g * y.b - x.b * y.g;
    result.g = x.b * y.r - x.r * y.b;
    result.b = x.r * y.g - x.g * y.r;
    return result;
}

Vec3 reflect(Vec3 I, Vec3 N) {
    float NdotI = dot_vec3(N, I);
    Vec3 term1 = vec3_multiply_float(N, 2.0f * NdotI);
    return vec3_subtract(I, term1);
}

Vec3 mat3_mul_vec3(mat3 m, Vec3 v) {
    Vec3 result;
    result.r = m.m[0][0] * v.r + m.m[0][1] * v.g + m.m[0][2] * v.b;
    result.g = m.m[1][0] * v.r + m.m[1][1] * v.g + m.m[1][2] * v.b;
    result.b = m.m[2][0] * v.r + m.m[2][1] * v.g + m.m[2][2] * v.b;
    return result;
}

float sign(float x) {
    return (x > 0) - (x < 0);
}

float vec3_length_squared(Vec3 v) {
    return v.r * v.r + v.g * v.g + v.b * v.b;
}

Vec3 vec3_multiply_vec(Vec3 a, Vec3 b) {
    Vec3 result;

    result.r = a.r * b.r;
    result.g = a.g * b.g;
    result.b = a.b * b.b;

    return result;
}

Vec3 vec3_negate(Vec3 v) {
    Vec3 result;
    result.r = -v.r;
    result.g = -v.g;
    result.b = -v.b;
    return result;
}
mat3 mat3_add(mat3 m1, mat3 m2) {
    mat3 result;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.m[i][j] = m1.m[i][j] + m2.m[i][j];
        }
    }

    return result;
}
mat3 mat3_multiply_scalar(mat3 m, float scalar) {
    mat3 result;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.m[i][j] = m.m[i][j] * scalar;
        }
    }

    return result;
}
mat3 mat3_multiply(mat3 m1, mat3 m2) {
    mat3 result;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.m[i][j] = 0.0;  // Initialize the result element to 0
            for (int k = 0; k < 3; k++) {
                result.m[i][j] += m1.m[i][k] * m2.m[k][j];
            }
        }
    }

    return result;
}

mat3 rotationToY(Vec3 dir) {
    Vec3 yAxis = vec3_create(0.0, 1.0, 0.0);
    
    // Cross product
    Vec3 v = cross_vec3(dir, yAxis); // Assuming you have a function named cross_vec3 for cross product
    
    // Length of the vector
    float s = vec3_length(v); // Using your vec3_length function
    
    // Dot product
    float c = dot_vec3(dir, yAxis); // Assuming you have a function named dot_vec3 for dot product
    
    // Create the skew-symmetric matrix for v
    mat3 vMat = mat3_create(
        vec3_create(0, -v.b, v.g),
        vec3_create(v.b, 0, -v.r),
        vec3_create(-v.g, v.r, 0)
    );

    // Identity matrix
    mat3 identity = mat3_create(
        vec3_create(1.0, 0.0, 0.0),
        vec3_create(0.0, 1.0, 0.0),
        vec3_create(0.0, 0.0, 1.0)
    );

    // Assuming you have matrix addition and multiplication functions:
    // mat3_add for matrix addition
    // mat3_multiply for matrix multiplication
    // mat3_multiply_scalar for matrix-scalar multiplication
    return mat3_add(
        identity,
        mat3_add(
            vMat,
            mat3_multiply_scalar(
                mat3_multiply(vMat, vMat),
                (1.0 - c) / (s * s)
            )
        )
    );
}


Vec3 mat3_multiply_vec3(mat3 m, Vec3 v) {
    Vec3 result;

    result.r = m.m[0][0] * v.r + m.m[0][1] * v.g + m.m[0][2] * v.b;
    result.g = m.m[1][0] * v.r + m.m[1][1] * v.g + m.m[1][2] * v.b;
    result.b = m.m[2][0] * v.r + m.m[2][1] * v.g + m.m[2][2] * v.b;

    return result;
}
