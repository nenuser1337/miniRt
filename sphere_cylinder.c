#include "vectors.h"


const int numCylinders = 3; // Or however many cylinders you need
struct Cylinder cylinders[numCylinders];

const int numSpheres = 2;  // or any number you'd like
struct Sphere spheres[numSpheres];


// Function to initialize our scene's parameters
void setupScene()
{
    camera.position = (Vec3){0., 0., 3.5};
    camera.direction = normalize_vec3((Vec3){0., 0., 3.5});
    camera.zoom = 2.0;

    
     cylinders[0].position = vec3_create(0.1, -0.06, 2.2);
    cylinders[0].axis = normalize_vec3(vec3_create(1.7, 0.8, -2.));
    cylinders[0].diameter = 0.2;
    cylinders[0].height = 1.;
    cylinders[0].color = vec3_create(0.1, 0.0, 1.0);

    // Initialize the second cylinder
    cylinders[1].position = vec3_create(-0.3, -0.2, 2.1);
    cylinders[1].axis = normalize_vec3(vec3_create(-0.5, 0.5, 1.0));
    cylinders[1].diameter = 0.1;
    cylinders[1].height = 0.5;
    cylinders[1].color = vec3_create(1.0, 0.0, 0.0);
     cylinders[2].position = vec3_create(0.0, 0.5, 0.0);
    cylinders[2].axis = normalize_vec3(vec3_create(1.0, 1.0, 1.0));
    cylinders[2].diameter = 0.15;
    cylinders[2].height = 0.7;
    cylinders[2].color = vec3_create(0.0, 1.0, 0.0);
    
    plane.point = vec3_create(0., 0.5, 0.);
    plane.normal = vec3_create(0., 1., 0.);
    plane.color = vec3_create(0.5, 0.5, 0.5);  // Plane color is grey
    
    
    spheres[1].position = vec3_create(0.5, -0.5, 1.);
    spheres[1].radius = 0.3;
    spheres[1].color = vec3_create(0.2, 0.9, 0.3);
    
    spheres[0].position = vec3_create(-0.5, -1., -1.);
    spheres[0].radius = 0.3;
    spheres[0].color = vec3_create(0.9, 0.9, 0.3);

     light.direction = normalize_vec3(vec3_create(0., -1., -0.78));
}

float vec3_length(Vec3 v) {
    return sqrt(v.r * v.r + v.g * v.g + v.b * v.b);
}


// Function to solve a quadratic equation given a, b, and c coefficients
bool solveQuadratic(float a, float b, float c,  float *t0,  float *t1)
{
    // Compute the discriminant
    float disc = b * b - 4. * a * c;

    // If the discriminant is less than zero, there are no real solutions
    if (disc < 0.)
    {
        return false;
    } 

    // If the discriminant is zero, there is exactly one real solution
    if (disc == 0.)
    {
        *t0 = *t1 = -b / (2. * a);
        return true;
    }

    // Otherwise, there are two real solutions
    *t0 = (-b + sqrt(disc)) / (2. * a);
    *t1 = (-b - sqrt(disc)) / (2. * a);
    return true;    
}

bool intersect_plane(Vec3 direction, Vec3* Phit)
{
    float denom = dot_vec3(plane.normal, direction);
    if (fabs(denom) < 0.0001) return false;  // parallel to the plane

    float tTemp = dot_vec3(vec3_subtract(plane.point, camera.position), plane.normal) / denom;
    if (tTemp >= 0.) {
        *Phit = vec3_add(camera.position, vec3_multiply_float(direction, tTemp));
        return true;
    }

    return false;
}


bool intersect_sphere(struct Sphere sphere, Vec3 rayOrigin, Vec3 rayDirection, Vec3 *surfaceNormal, float *tHit)
{
    Vec3 L = vec3_subtract(rayOrigin, sphere.position);  // Assuming vec3_subtract() is defined in your math utilities
    
    float a = dot_vec3(rayDirection, rayDirection);
    float b = 2.0 * dot_vec3(rayDirection, L);
    float c = dot_vec3(L, L) - pow(sphere.radius, 2.0);
    
    float t0, t1;
    
    if (solveQuadratic(a, b, c, &t0, &t1))  // Assuming solveQuadratic() fills t0 and t1
    {
        *tHit = t0;
        if (t1 < t0)
        {
            *tHit = t1;
        }
        
        Vec3 Phit = vec3_add(rayOrigin, vec3_multiply_scalar(rayDirection, *tHit));  // Assuming vec3_add() and vec3_multiply_scalar() are defined
        *surfaceNormal = normalize_vec3(vec3_subtract(Phit, sphere.position));
        
        return true;
    }
    
    return false;
}

bool intersectCaps(struct Cylinder cylinder, Vec3 rayOriginLocal, Vec3 rayDirLocal, Vec3* surfaceNormal, float* tHit)
{
    float tBottom = -rayOriginLocal.g / rayDirLocal.g;
    Vec3 pBottom = vec3_add(rayOriginLocal, vec3_multiply_float(rayDirLocal, tBottom));
    if (tBottom > 0.0 && pBottom.r * pBottom.r + pBottom.b * pBottom.b <= (cylinder.diameter * 0.5) * (cylinder.diameter * 0.5))
    {
        *tHit = tBottom;
        *surfaceNormal = vec3_create(0.0, -1.0, 0.0);
        return true;
    }
    
    float tTop = (cylinder.height - rayOriginLocal.g) / rayDirLocal.g;
    Vec3 pTop = vec3_add(rayOriginLocal, vec3_multiply_float(rayDirLocal, tTop));
    if (tTop > 0.0 && pTop.r * pTop.r + pTop.b * pTop.b <= (cylinder.diameter * 0.5) * (cylinder.diameter * 0.5))
    {
        *tHit = tTop;
        *surfaceNormal = vec3_create(0.0, 1.0, 0.0);
        return true;
    }
    
    return false;
}

bool intersect(Vec3 rayOrigin, Vec3 rayDirection, Vec3* surfaceNormal, struct Cylinder cylinder)
{
    mat3 rotationMatrix = rotationToY(cylinder.axis);  // Assuming you have this function implemented
    mat3 inverseRotation = mat3_transpose(rotationMatrix);
    
    Vec3 rayOriginLocal = mat3_multiply_vec3(inverseRotation, vec3_subtract(rayOrigin, cylinder.position));
    Vec3 rayDirLocal = mat3_multiply_vec3(inverseRotation, rayDirection);

    float r = cylinder.diameter * 0.5;

    float a = rayDirLocal.r * rayDirLocal.r + rayDirLocal.b * rayDirLocal.b;
    float b = 2.0 * (rayOriginLocal.r * rayDirLocal.r + rayOriginLocal.b * rayDirLocal.b);
    float c = rayOriginLocal.r * rayOriginLocal.r + rayOriginLocal.b * rayOriginLocal.b - r * r;

    float t0, t1;
    if (solveQuadratic(a, b, c, &t0, &t1))  // Assuming you have this function implemented
    {
        float t = fmin(t0, t1);  // Using fmin from math.h
        Vec3 PhitLocal = vec3_add(rayOriginLocal, vec3_multiply_float(rayDirLocal, t));

        float yDiff = PhitLocal.g;
        if(yDiff < 0.0 || yDiff > cylinder.height)
        {
            if(intersectCaps(cylinder, rayOriginLocal, rayDirLocal, surfaceNormal, &t))
            {
                return true;
            }
            return false;
        }

        Vec3 Phit = vec3_add(mat3_multiply_vec3(rotationMatrix, PhitLocal), cylinder.position);
        *surfaceNormal = normalize_vec3(mat3_multiply_vec3(rotationMatrix, vec3_create(PhitLocal.r, 0.0, PhitLocal.b)));

        return true;
    }
    return false;
}




bool isInShadow(Vec3 point, Vec3 toLight)
{
    Vec3 surfaceNormal;
    float tHit;

    // Assuming cylinders and spheres are arrays of Cylinder and Sphere types
    // Assuming numCylinders and numSpheres are the number of cylinders and spheres
    for (int i = 0; i < numCylinders; ++i)
    {
        // Assuming intersect() takes the cylinder as a parameter
        if (intersect(vec3_add(point, vec3_multiply_float(toLight, 1e-4)), toLight, &surfaceNormal, cylinders[i]))
        {
            return true;
        }
    }

    for (int i = 0; i < numSpheres; ++i)
    {
        // Assuming intersect_sphere() takes the sphere as a parameter
        if (intersect_sphere(spheres[i], vec3_add(point, vec3_multiply_float(toLight, 1e-4)), toLight, &surfaceNormal, &tHit))
        {
            if (tHit > 1e-4)  // To avoid self-shadowing
            {
                return true;
            }
        }
    }

    return false;
}




Vec3 rayTrace(Vec3 direction) {
    Vec3 surfaceNormal;
    Vec3 Phit;
    float tHit;  // To store the t value for the closest hit

    // Check for intersections with cylinders
    for (int i = 0; i < numCylinders; ++i) {
        if (intersect(camera.position, direction, &surfaceNormal, cylinders[i])) {
            float coeff = -dot_vec3(light.direction, surfaceNormal);
            coeff = coeff < 0 ? 0 : coeff;
            Vec3 potentialColor = vec3_multiply_float(cylinders[i].color, coeff);

            // Compute the new ray starting point based on the intersection point
            Vec3 newStart = vec3_add(camera.position, vec3_multiply_float(direction, tHit));

           
                return vec3_multiply_float(potentialColor, 0.5);  // Shadowed color
            
        }
    }
     for (int i = 0; i < numSpheres; ++i)
    {
        if (intersect_sphere(spheres[i], camera.position, direction, &surfaceNormal, &tHit)) // Assuming this function is implemented
        {
            Vec3 Phit = vec3_add(camera.position, vec3_multiply_float(direction, tHit));
            float coeff = -dot_vec3(light.direction, surfaceNormal);  // Assuming dot_vec3 is implemented
            coeff = coeff < 0 ? 0 : coeff;
            Vec3 potentialColor = vec3_multiply_float(spheres[i].color, coeff);  // Assuming spheres[i].color is Vec3

          
                return vec3_multiply_float(potentialColor, 0.5);  // Shadowed color
            
        }
    }
    // Check for intersections with the plane
    if (intersect_plane(direction, &Phit)) {  // Assuming Phit gets modified by intersectPlane
        Vec3 col = plane.color;  // Assuming plane.color is a Vec3
        
        if (isInShadow(Phit, vec3_negate(light.direction))) {
            col = vec3_multiply_float(col, 0.5);  // Darken the color if in shadow
        }
        
        return col;
    }

    // If the ray does not intersect any object, return black
    return vec3_create(0., 0., 0.);
}



