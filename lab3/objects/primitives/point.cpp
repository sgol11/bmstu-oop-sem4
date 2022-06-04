#include "point.h"
#include <cmath>


double to_radians(const double &angle)
{
    return angle * (M_PI / 180);
}


Point::Point(const double src_x, const double src_y, const double src_z)
{
    x = src_x;
    y = src_y;
    z = src_z;
}

Point::Point(const Point &&src_point) noexcept
{
    x = src_point.get_x();
    y = src_point.get_y();
    z = src_point.get_z();

    src_point.~Point();
}


Point &Point::operator = (Point &&src_point) noexcept
{
    x = src_point.get_x();
    y = src_point.get_y();
    z = src_point.get_z();

    src_point.~Point();

    return *this;
}


void Point::move(const double &dx, const double &dy, const double &dz)
{
    x += dx;
    y += dy;
    z += dz;
}

void Point::scale(const double &kx, const double &ky, const double &kz)
{
    x *= kx;
    y *= ky;
    z *= kz;
}

void Point::rotate(const double &ox, const double &oy, const double &oz)
{
    rotate_x(ox);
    rotate_y(oy);
    rotate_z(oz);
}

void Point::rotate_x(const double &ox)
{
    const double cos_rotate = cos(to_radians(ox));
    const double sin_rotate = sin(to_radians(ox));

    const double init_y = y;

    y = y * cos_rotate - z * sin_rotate;
    z = z * cos_rotate + init_y * sin_rotate;
}

void Point::rotate_y(const double &oy)
{
    const double cos_rotate = cos(to_radians(oy));
    const double sin_rotate = sin(to_radians(oy));

    const double init_x = x;

    x = x * cos_rotate - z * sin_rotate;
    z = z * cos_rotate + init_x * sin_rotate;
}

void Point::rotate_z(const double &oz)
{
    const double cos_rotate = cos(to_radians(oz));
    const double sin_rotate = sin(to_radians(oz));

    const double init_x = x;

    x = x * cos_rotate - y * sin_rotate;
    y = y * cos_rotate + init_x * sin_rotate;
}


double Point::get_x() const
{
    return x;
}

double Point::get_y() const
{
    return y;
}

double Point::get_z() const
{
    return z;
}


void Point::set_x(double const &_x)
{
    x = _x;
}

void Point::set_y(double const &_y)
{
    y = _y;
}

void Point::set_z(double const &_z)
{
    z = _z;
}


bool Point::operator == (const Point &second_point) const noexcept
{
    return (x == second_point.get_x()) &&
           (y == second_point.get_y()) &&
           (z == second_point.get_z());
}

bool Point::operator != (const Point &second_point) const noexcept
{
    return !(*this == second_point);
}

Point Point::operator + (const Point &second_point)
{
    Point result{};

    result.x = this->x + second_point.get_x();
    result.y = this->y + second_point.get_y();
    result.z = this->z + second_point.get_z();

    return result;
}

Point Point::operator - (const Point &second_point)
{
    Point result{};

    result.x = this->x - second_point.get_x();
    result.y = this->y - second_point.get_y();
    result.z = this->z - second_point.get_z();

    return result;
}


Point Point::operator-() const
{
    Point result{};

    result.x = -x;
    result.y = -y;
    result.z = -z;

    return result;
}
