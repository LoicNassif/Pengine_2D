#include <iostream>
#include <catch2/catch.hpp>

template<typename Number>
class Vec2 {
    public:
        Vec2(Number _x, Number _y): x(_x), y(_y) {}
        ~Vec2() {}

        Number x;
        Number y;
};

/* Dot product */
template <typename Number>
int operator*(const Vec2<Number> &a, const Vec2<Number> &b)
{
    return a.x*b.x + a.y*b.y;
}

/* scalar multiplication */
template <typename Number, typename Const>
Vec2<Number> operator*(const Vec2<Number> &a, Const c)
{
    return Vec2<Number>((Number)(c * a.x), (Number)(c * a.y));
}

template <typename Number, typename Const>
Vec2<Number> operator*(Const c, const Vec2<Number> &a)
{
    return Vec2<Number>((Number)(c * a.x), (Number)(c * a.y));
}

/* Element wise addition */
template <typename Number, typename Number2>
Vec2<Number> operator+(const Vec2<Number> &a, const Vec2<Number2> &b)
{
    return Vec2<Number>(a.x + b.x, a.y + b.y);
}

/* Element wise substraction */
template <typename Number>
Vec2<Number> operator-(const Vec2<Number> &a, const Vec2<Number> &b)
{
    return Vec2<Number>(a.x - b.x, a.y - b.y);
}

/* Printing */
template<typename Number>
std::ostream& operator<<(std::ostream &out, const Vec2<Number> &a) {
    out << '(' << a.x << ',' << a.y << ')';
    return out;
}