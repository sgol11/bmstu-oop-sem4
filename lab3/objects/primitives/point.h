#ifndef POINT_H
#define POINT_H

#include <cmath>
#include <memory>


class Point
{
public:
    Point() = default;
    Point(const double src_x, const double src_y, const double src_z);

    Point(const Point &src_point) = default;
    Point(const Point &&src_point) noexcept;

    ~Point() = default;

    Point &operator = (const Point &src_point) = default;
    Point &operator = (Point &&src_point) noexcept;

    void move  (const double &dx, const double &dy, const double &dz);
    void scale (const double &kx, const double &ky, const double &kz);
    void rotate(const double &ox, const double &oy, const double &oz);

    void rotate_x(const double &ox);
    void rotate_y(const double &oy);
    void rotate_z(const double &oz);

    double get_x() const;
    double get_y() const;
    double get_z() const;

    void set_x(double const &src_x);
    void set_y(double const &src_y);
    void set_z(double const &src_z);

    bool operator == (const Point &second_point) const noexcept;
    bool operator != (const Point &second_point) const noexcept;

    Point operator + (const Point &second_point);
    Point operator - (const Point &second_point);

    Point operator-() const;

private:
    double x, y, z;
};

#endif // POINT_H
