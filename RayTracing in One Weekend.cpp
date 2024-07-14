#include <iostream>
#include <vector>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "color.h"
#include "vec3.h"

using namespace std;

int main()
{
    // Image config
    int image_width = 256;
    int image_height = 256;

    // Create a buffer to hold the image data
    vector<unsigned char> image_data(image_width * image_height * 3);

    // Generate image data
    for (int j = 0; j < image_height; j++) {
        clog << "\rScanlines Remaining: " << (image_height - j) << ' ' << flush;
        for (int i = 0; i < image_width; i++) {
            // Calculate the color for this pixel
            auto pixel_color = color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.7);

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
