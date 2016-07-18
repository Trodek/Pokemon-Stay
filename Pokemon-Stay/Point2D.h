#ifndef __Point2D_H__
#define __Point2D_H__

#include <math.h>

template<class TYPE>
class Point2D
{
public:

	TYPE x, y;

	Point2D()
	{}

	Point2D(const Point2D& v)
	{
		this->x = v.x;
		this->y = v.y;
	}

	Point2D(const TYPE& x, const TYPE& y)
	{
		this->x = x;
		this->y = y;
	}

	Point2D& create(const TYPE& x, const TYPE& y)
	{
		this->x = x;
		this->y = y;

		return(*this);
	}

	// Math ------------------------------------------------
	Point2D operator -(const Point2D &v) const
	{
		Point2D r;

		r.x = x - v.x;
		r.y = y - v.y;

		return(r);
	}

	Point2D operator + (const Point2D &v) const
	{
		Point2D r;

		r.x = x + v.x;
		r.y = y + v.y;

		return(r);
	}

	const Point2D& operator -=(const Point2D &v)
	{
		x -= v.x;
		y -= v.y;

		return(*this);
	}

	const Point2D& operator +=(const Point2D &v)
	{
		x += v.x;
		y += v.y;

		return(*this);
	}

	bool operator ==(const Point2D& v) const
	{
		return (x == v.x && y == v.y);
	}

	bool operator !=(const Point2D& v) const
	{
		return (x != v.x || y != v.y);
	}

	// Utils ------------------------------------------------
	bool IsZero() const
	{
		return (x == 0 && y == 0);
	}

	Point2D& SetToZero()
	{
		x = y = 0;
		return(*this);
	}

	Point2D& Negate()
	{
		x = -x;
		y = -y;

		return(*this);
	}

	// Distances ---------------------------------------------
	TYPE DistanceTo(const Point2D& v) const
	{
		TYPE fx = x - v.x;
		TYPE fy = y - v.y;

		return (TYPE)sqrtf(float(fx*fx) + float(fy*fy));
	}

	TYPE DistanceNoSqrt(const Point2D& v) const
	{
		TYPE fx = x - v.x;
		TYPE fy = y - v.y;

		return (fx*fx) + (fy*fy);
	}

	TYPE DistanceManhattan(const Point2D& v) const
	{
		return abs(v.x - x) + abs(v.y - y);
	}
};

typedef Point2D<int> iPoint;
typedef Point2D<float> fPoint;

#endif // __Point2D_H__