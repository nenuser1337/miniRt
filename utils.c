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
