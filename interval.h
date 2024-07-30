#ifndef INTERVAL_H
#define INTERVAL_H

class interval
{
public:
	double min, max;

	interval() : min(+infinity), max(-infinity)
	{
	} // Default interval is empty

	interval(const double min, const double max) : min(min), max(max)
	{
	}

	double size() const
	{
		return max - min;
	}

	bool contains(const double x) const
	{
		return min <= x && x <= max;
	}

	bool surrounds(const double x) const
	{
		return min < x && x < max;
	}

	double clamp(const double x) const
	{
		if (x < min) return min;
		if (x > max) return max;
		return x;
	}

	static const interval empty, universe;
};

const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);

#endif
