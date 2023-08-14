#include "vectors.h"
// Function to initialize our scene's parameters
void setupScene()
{
    // Set the camera's position and direction, and its zoom level
    camera.position = vec3_create(0., 0., 3.5);
    camera.direction = vec3_create(0., 0., -1.);
    camera.fov = 1.0;

    // Set the sphere's position, radius, and color
    sphere.position = vec3_create(0., 0., 0.);
    sphere.radius = 0.3;
    sphere.color = vec3_create(0.6, 0.9, 0.3);

    plane.point = vec3_create(0., 0.5, 0.);
    plane.normal = vec3_create(0., 1., 0.);
    plane.color = vec3_create(0.5, 0.5, 0.5);  // Plane color is grey

    cylinder.position = vec3_create(0., -0.5, 0.);
    cylinder.axis = normalize_vec3(vec3_create(1.7, 1.8, 2.));
    cylinder.radius = 0.1;
    cylinder.height = 1.0;
    cylinder.color = vec3_create(0.2, 0.3, 0.9);

    // Set the light's direction and normalize it
    light.position = normalize_vec3(vec3_create(0., -1., -0.78));

    // Set the material's ambience, diffuse, specular, and shininess properties
    material.ambience = 0.2;
    material.diffuse = 0.7;
    material.specular = 1.4;
    material.shininess = 12.0; 
   
    ambientLight.ratio = 0.01;
    ambientLight.color = vec3_multiply_float(vec3_create(255./255., 255./255., 255./255.), ambientLight.ratio); // Normalize color from [0-255] to [0.0-1.0]
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


bool intersect_sphere(Vec3 direction, Vec3 *surfaceNormal)
{
    // Compute the vector from the camera to the sphere
    Vec3 L = vec3_subtract (camera.position ,sphere.position);

    // Compute the coefficients a, b, and c for the quadratic equation
    float a = dot_vec3(direction, direction);
    float b = 2. * dot_vec3(direction, L);
    float c = dot_vec3(L, L) - pow(sphere.radius, 2.);

    // Initialize the solutions to the quadratic equation
    float t0 = 0;
    float t1 = 0;

    // If the quadratic equation has solutions
    if (solveQuadratic(a, b, c, &t0, &t1))
    {
        // Select the smaller of the two solutions
        float t = t0;
        if (t1 < t0)
        {
            t = t1;
        }

        // Compute the point of intersection
        Vec3 Phit = vec3_add(camera.position,vec3_multiply_float(direction, t));
        // Compute the surface normal at the point of intersection
        *surfaceNormal = normalize_vec3( vec3_subtract(Phit , sphere.position));

        return true;
    }  

    return false;
}

bool intersect_cylinder(Vec3 direction, Vec3* surfaceNormal) {
    // Calculate the rotation matrix and its inverse
    mat3 rotationMatrix = rotationToY(cylinder.axis);
    mat3 inverseRotation = mat3_transpose(rotationMatrix); // Since it's a rotation matrix, transpose is its inverse
    
    Vec3 rayOriginLocal = mat3_multiply_vec3(inverseRotation, vec3_subtract(camera.position, cylinder.position)); // Assuming you have a function mat3_multiply_vec3
    Vec3 rayDirLocal = mat3_multiply_vec3(inverseRotation, direction);

    float r = cylinder.radius ;

    float a = rayDirLocal.r * rayDirLocal.r + rayDirLocal.b * rayDirLocal.b;
    float b = 2.0 * (rayOriginLocal.r * rayDirLocal.r + rayOriginLocal.b * rayDirLocal.b);
    float c = rayOriginLocal.r * rayOriginLocal.r + rayOriginLocal.b * rayOriginLocal.b - r * r;

    float t0, t1;
    if (solveQuadratic(a, b, c, &t0, &t1)) {
        float t = fmin(t0, t1); // Use fmin from math.h
        Vec3 PhitLocal = vec3_add(rayOriginLocal, vec3_multiply_float(rayDirLocal, t));

        float yDiff = PhitLocal.g;
        if(yDiff < 0.0 || yDiff > cylinder.height) {
            return false;
        }

        Vec3 Phit = vec3_add(mat3_multiply_vec3(rotationMatrix, PhitLocal), cylinder.position);
        *surfaceNormal = normalize_vec3(mat3_multiply_vec3(rotationMatrix, vec3_create(PhitLocal.r, 0.0, PhitLocal.b)));
        return true;
    }
    return false;
}



bool intersect(Vec3 direction, Vec3 *surfaceNormal)
{
   // Compute the vector from the camera to the cylinder
    Vec3 L = vec3_subtract(camera.position, cylinder.position);

    // Compute the coefficients a, b, and c for the quadratic equation
    float a = direction.r * direction.r + direction.b * direction.b;
    float b = 2.0 * (L.r * direction.r + L.b * direction.b);
    float c = L.r * L.r + L.b * L.b - cylinder.radius * cylinder.radius;

    // Initialize the solutions to the quadratic equation
    float t0, t1;

    // If the quadratic equation has solutions
    if (solveQuadratic(a, b, c, &t0, &t1))
    {
        // Select the smaller of the two solutions
        float t = fmin(t0, t1);

        // Compute the point of intersection
        Vec3 Phit = vec3_add(camera.position, vec3_multiply_float(direction, t));

        // Compute the y coordinate relative to the cylinder's position
        float y = Phit.g - cylinder.position.g;

        // If the y coordinate is not within the cylinder's height, return false
        if(y < 0.0 || y > cylinder.height)
        {
            return false;
        }

        // Compute the surface normal at the point of intersection
        *surfaceNormal = vec3_create(Phit.r - cylinder.position.r, 0, Phit.b - cylinder.position.b);
        surfaceNormal->g = (y < 0.0 || y > cylinder.height - 0.001) ? -sign(y) : 0.0;
        *surfaceNormal = normalize_vec3(*surfaceNormal);

        return true;
    }  

    return false;
}





// Function to trace a ray from the camera in the given direction
Vec3 rayTrace(Vec3 direction) {
    Vec3 surfaceNormal;
    Vec3 Phit;

    // If the ray intersects the sphere
     if (intersect_cylinder(direction, &surfaceNormal))
    {
        // Compute the reflection coefficient
        float coeff = -1 * dot_vec3(light.position, surfaceNormal);                          
        // Clamp coeff to the range [0, 1]
        coeff = coeff < 0 ? 0 : coeff;  
        Vec3 directLightColor = vec3_multiply_float(sphere.color, coeff);

        Vec3 ambientlight =vec3_multiply_vec(sphere.color, ambientLight.color);
        return  vec3_add(directLightColor,ambientlight );
    
    }
        // Checking if the ray intersects the plane
    // if (intersect_plane(direction, &Phit))
    // {
    //     // Calculate the shadow position. 
    //     // We now project along the light direction.
    //     Vec3 shadowPos = vec3_add(sphere.position, vec3_multiply_float(light.position, fabs(dot_vec3(vec3_subtract(sphere.position, plane.point), plane.normal))));

    //     // Calculate the distance between the hit point and the shadow position.
    //     float dist = vec3_length(vec3_subtract(shadowPos, Phit));

    //     // If the distance is less than the radius, the hit point is in the shadow.
    //     if (dist < sphere.radius) {
    //         return vec3_create(0., 0., 0.);  // Shadow color
    //     } else {
    //         return plane.color;
    //     }
    //  }
    

    // If the ray does not intersect the sphere, return black
    return vec3_create(0., 0., 0.);
}


