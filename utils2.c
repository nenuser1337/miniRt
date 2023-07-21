#include "vectors.h"

float fract_float(float x) {
    return x - floor(x);
}

Vec2 fract_2(Vec2 v) {
    return vec2_subtract (v , floor_2(v));
}




float floor_float(float x) {
    return (x >= 0.0) ? (float)((int)x) : (float)((int)x - 1);
}

Vec2 floor_2(Vec2 v) {
    return vec2_create(floor(v.x), floor(v.y));
}


Vec2 vec2_multiply_double(Vec2 v, double scalar) {
    return vec2_create(v.x * scalar, v.y * scalar);
}

Vec3 vec3_multiply_float(Vec3 v, float scalar) {
    return vec3_create(v.r * scalar, v.g * scalar, v.b * scalar);
}

// Mat3 mat3_create(float m11, float m12, float m13,
//                  float m21, float m22, float m23,
//                  float m31, float m32, float m33) {
//     Mat3 mat;
//     mat.m11 = m11; mat.m12 = m12; mat.m13 = m13;
//     mat.m21 = m21; mat.m22 = m22; mat.m23 = m23;
//     mat.m31 = m31; mat.m32 = m32; mat.m33 = m33;
//     return mat;
// }

// Vec3 vec3_multiply_mat3(Vec3 vec, Mat3 mat) {
//     Vec3 result;
//     result.r = mat.m11 * vec.r + mat.m12 * vec.g + mat.m13 * vec.b;
//     result.g = mat.m21 * vec.r + mat.m22 * vec.g + mat.m23 * vec.b;
//     result.b = mat.m31 * vec.r + mat.m32 * vec.g + mat.m33 * vec.b;
//     return result;
// }


// Function to create a mat3 from three vec3
mat3 mat3_create(Vec3 t, Vec3 b, Vec3 n) {
    mat3 matrix;
    for (int i = 0; i < 3; i++) {
        matrix.m[0][i] = (&t.r)[i];  // Here, t.x, t.y, and t.z correspond to indices 0, 1, and 2 respectively
        matrix.m[1][i] = (&b.r)[i];
        matrix.m[2][i] = (&n.r)[i];
    }
    return matrix;
}

// Function to transpose a mat3
mat3 mat3_transpose(mat3 m) {
    mat3 transposed;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            transposed.m[j][i] = m.m[i][j];
    return transposed;
}

float dot_vec3(Vec3 v1, Vec3 v2) {
    return v1.r * v2.r + v1.g * v2.g + v1.b * v2.b;
}
