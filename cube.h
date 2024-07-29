#ifndef CUBE_H
#define CUBE_H

#include "hittable.h"

class cube : public hittable
{
public:
	cube(const vec3& min, const vec3& max, shared_ptr<material> mat)
		: min(min), max(max), mat(mat)
	{
	}

	bool hit(const ray& r, interval ray_t, hit_record& rec) const override
	{
		for (int a = 0; a < 3; a++)
		{
			auto invD = 1.0f / r.direction()[a];
			auto t0 = (min[a] - r.origin()[a]) * invD;
			auto t1 = (max[a] - r.origin()[a]) * invD;
			if (invD < 0.0f) std::swap(t0, t1);
			ray_t.min = t0 > ray_t.min ? t0 : ray_t.min;
			ray_t.max = t1 < ray_t.max ? t1 : ray_t.max;
			if (ray_t.max <= ray_t.min) return false;
		}
		rec.t = ray_t.min;
		rec.p = r.at(rec.t);

		// Compute normal
		for (int a = 0; a < 3; a++)
		{
			if (rec.p[a] == min[a])
			{
				auto normal = vec3(0, 0, 0);
				normal[a] = -1;
				rec.set_face_normal(r, normal);
				break;
			}
			if (rec.p[a] == max[a])
			{
				auto normal = vec3(0, 0, 0);
				normal[a] = 1;
				rec.set_face_normal(r, normal);
				break;
			}
		}

		rec.mat = mat;
		return true;
	}

private:
	vec3 min;
	vec3 max;
	shared_ptr<material> mat;
};

#endif
