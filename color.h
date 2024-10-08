#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"

using color = vec3;

inline double linear_to_gamma(const double linear_component)
{
	if (linear_component > 0)
		return sqrt(linear_component);

	return 0;
}

void write_color(unsigned char* buffer, const int index, const color& pixel_color)
{
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	// Apply a linear to gamma transform for gamma 2
	r = linear_to_gamma(r);
	g = linear_to_gamma(g);
	b = linear_to_gamma(b);

	// Translate the [0,1] component values to the byte range [0,255].
	static const interval intensity(0.000, 0.999);
	const int rbyte = static_cast<int>(256 * intensity.clamp(r));
	const int gbyte = static_cast<int>(256 * intensity.clamp(g));
	const int bbyte = static_cast<int>(256 * intensity.clamp(b));

	// Write the color to the buffer at the specified index.
	buffer[index] = rbyte;
	buffer[index + 1] = gbyte;
	buffer[index + 2] = bbyte;
}

#endif
