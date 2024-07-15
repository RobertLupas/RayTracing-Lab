#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "utilities.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

// Function to configure and add a sphere to the world based on user input
void configureScene(hittable_list& world) {
    // User input for sphere properties
    std::cout << "Enter sphere properties:\n";

    // Sphere position
    point3 center;
    std::cout << "Center (x y z): ";
    double x, y, z;
    std::cin >> x >> y >> z;
    center[0] = x;
    center[1] = y;
    center[2] = z;

    // Sphere radius
    double radius;
    std::cout << "Radius: ";
    std::cin >> radius;

    // Sphere color
    color sphereColor;
    std::cout << "Color (r g b): ";
    std::cin >> x >> y >> z;
    sphereColor[0] = x;
    sphereColor[1] = y;
    sphereColor[2] = z;

    // Sphere material type
    std::cout << "Material type (lambertian, dielectric, metal): ";
    std::string materialType;
    std::cin >> materialType;

    std::shared_ptr<material> sphereMaterial;

    if (materialType == "lambertian") {
        sphereMaterial = std::make_shared<lambertian>(sphereColor);
    }
    else if (materialType == "dielectric") {
        sphereMaterial = std::make_shared<dielectric>(1.50); // Refractive index for dielectric
    }
    else if (materialType == "metal") {
        sphereMaterial = std::make_shared<metal>(sphereColor, 1.0); // Metal with fuzziness
    }
    else {
        std::cerr << "Unknown material type. Using Lambertian by default.\n";
        sphereMaterial = std::make_shared<lambertian>(sphereColor);
    }

    // Add the sphere to the world
    world.add(std::make_shared<sphere>(center, radius, sphereMaterial));
}

int main() {
    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.4, 0.2, 0.6));
    world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));

    // Configure the scene based on user input
    configureScene(world);

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 200;
    cam.max_depth = 50;

    cam.vfov = 20;
    cam.lookfrom = point3(-2, 2, 1);
    cam.lookat = point3(0, 0, -1);
    cam.vup = vec3(0, 1, 0);

    cam.defocus_angle = 10.0;
    cam.focus_dist = 3.4;

    // Render the scene
    cam.render(world);

    return 0;
}
