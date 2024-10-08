#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material_base.h"

class dielectric : public material
{
public:
	dielectric(const double refraction_index) : refraction_index(refraction_index)
	{
	}

	bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
	const override
	{
		attenuation = color(1.0, 1.0, 1.0);
		const double ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;

		const vec3 unit_direction = unit_vector(r_in.direction());
		const double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
		const double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

		const bool cannot_refract = ri * sin_theta > 1.0;
		vec3 direction;

		if (cannot_refract || reflectance(cos_theta, ri) > random_double())
			direction = reflect(unit_direction, rec.normal);
		else
			direction = refract(unit_direction, rec.normal, ri);

		scattered = ray(rec.p, direction);
		return true;
	}

private:
	double refraction_index;

	static double reflectance(const double cosine, const double refraction_index)
	{
		auto r0 = (1 - refraction_index) / (1 + refraction_index);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}
};

#endif
