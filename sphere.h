#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable
{
public:
	sphere(const vec3& center, const double radius, shared_ptr<material> mat)
		: center(center), radius(fmax(0, radius)), mat(mat)
	{
	}

	bool hit(const ray& r, const interval ray_t, hit_record& rec) const override
	{
		const vec3 oc = center - r.origin();
		const auto a = r.direction().length_squared();
		const auto h = dot(r.direction(), oc);
		const auto c = oc.length_squared() - radius * radius;

		const auto discriminant = h * h - a * c;
		if (discriminant < 0)
			return false;

		const auto sqrtd = sqrt(discriminant);

		// Find the nearest root that lies in the acceptable range.
		auto root = (h - sqrtd) / a;
		if (!ray_t.surrounds(root))
		{
			root = (h + sqrtd) / a;
			if (!ray_t.surrounds(root))
				return false;
		}

		rec.t = root;
		rec.p = r.at(rec.t);
		const vec3 outward_normal = (rec.p - center) / radius;
		rec.set_face_normal(r, outward_normal);
		rec.mat = mat;

		return true;
	}

private:
	vec3 center;
	double radius;
	shared_ptr<material> mat;
};

#endif
