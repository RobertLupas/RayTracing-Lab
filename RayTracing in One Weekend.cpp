#include <iostream>
#include <vector>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

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
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0.7;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            // Store the pixel data in the buffer
            image_data[3 * (j * image_width + i) + 0] = ir;
            image_data[3 * (j * image_width + i) + 1] = ig;
            image_data[3 * (j * image_width + i) + 2] = ib;
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
