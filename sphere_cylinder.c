#include "vectors.h"
// Function to initialize our scene's parameters
void setupScene()
{
    // Set the camera's position and direction, and its zoom level
    camera.position = vec3_create(0., 0., 3.5);
    camera.direction = vec3_create(0., 0., -1.);
    camera.zoom = 1.0;
    
    // Set the sphere's position, radius, and color
    sphere.position = vec3_create(0., 0., 0.);
    sphere.radius = 0.3;
    sphere.color = vec3_create(0.6, 0.9, 0.3);


    cylinder.position = vec3_create(0., -0.5, 0.);
    cylinder.radius = 0.3;
    cylinder.height = 1.0;
    cylinder.color = vec3_create(0.2, 0.3, 0.9);
    
    // Set the light's direction and normalize it
    light.direction = normalize_vec3(vec3_create(0., 1., -0.78));
    
    // Set the material's ambience, diffuse, specular, and shininess properties
    material.ambience = 0.2;
    material.diffuse = 0.7;
    material.specular = 1.4;
    material.shininess = 12.0; 
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
Vec3 rayTrace(Vec3 direction)
{
    Vec3 surfaceNormal;
    
    // If the ray intersects the sphere
    if (intersect(direction, &surfaceNormal))
    {
        // Compute the reflection coefficient
        float coeff = -1 * dot_vec3(light.direction, surfaceNormal);                          
        // Clamp coeff to the range [0, 1]
        coeff = coeff < 0 ? 0 : coeff;  
        // Compute the ambient color
        Vec3 ambient = vec3_multiply_float(sphere.color, material.ambience);
        // Compute the diffuse color
        Vec3 diffuse = vec3_multiply_float(sphere.color, coeff * material.diffuse);

        // Compute the reflected light direction
        Vec3 reflectedLightDirection = reflect(light.direction, surfaceNormal);
        // Compute the shininess factor
        float shininess = pow(max(-dot_vec3(direction, reflectedLightDirection), 0.0), material.shininess);
        shininess = shininess < 0 ? 0 : shininess; 
        // Compute the specular color
        Vec3 specular = vec3_multiply_float(sphere.color, shininess * material.specular);
        // Return the sum of the ambient, diffuse, and specular colors
        return  vec3_add(vec3_add(ambient, diffuse), specular);
    }
    
    // If the ray does not intersect the sphere, return black
    return vec3_create(0., 0., 0.);
}