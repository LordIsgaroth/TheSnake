#include "vector.hpp"

Vector2D::Vector2D()
{
    x = 0;
    y = 0;
}

Vector2D::Vector2D(double x, double y)
{
    this->x = x;
    this->y = y;
}

Vector2D Vector2D::Up() { return Vector2D(0, -1); }
Vector2D Vector2D::Down() { return Vector2D(0, 1); }
Vector2D Vector2D::Left() { return Vector2D(-1, 0); }
Vector2D Vector2D::Right() { return Vector2D(1, 0); }

bool operator == (Vector2D first, Vector2D second)
{
    return (first.X() == second.X() && first.Y() == second.Y());
}

bool operator != (Vector2D first, Vector2D second)
{
    return (first.X() != second.X() || first.Y() != second.Y());
}