#include <iostream>
#include <vector>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "color.h"
#include "ray.h"
#include "vec3.h"

using namespace std;

color ray_color(const ray& r) {
    // return color(0, 0, 0);

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main()
{
    // Image config
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    
    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width) / image_height);
    auto camera_center = point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center
        - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render

    // Create a buffer to hold the image data
    vector<unsigned char> image_data(image_width * image_height * 3);

    // Generate image data
    for (int j = 0; j < image_height; j++) {
        clog << "\rScanlines Remaining: " << (image_height - j) << ' ' << flush;
        for (int i = 0; i < image_width; i++) {
            // Calculate the color for this pixel
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);
            color pixel_color = ray_color(r);

            // Calculate the index in the buffer for this pixel
            int index = 3 * (j * image_width + i);

            // Write the color to the buffer
            write_color(image_data.data(), index, pixel_color);
        }
    }

    // Write the buffer to a PNG file
    if (stbi_write_png("image.png", image_width, image_height, 3, image_data.data(), image_width * 3)) {
        clog << "\nImage written to image.png\n";
    }
    else {
        cerr << "\nFailed to write image to file.\n";
    }

    return 0;
}
