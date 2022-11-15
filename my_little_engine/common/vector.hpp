#pragma once

class Vector2D
{    
public:
    Vector2D();
    Vector2D(double x, double y);
    const double X() const { return x; }
    const double Y() const { return y; }

    static Vector2D Up();
    static Vector2D Down();
    static Vector2D Left();
    static Vector2D Right();

    friend bool operator == (const Vector2D& first, const Vector2D& second) { return (first.X() == second.X() && first.Y() == second.Y()); }
    friend bool operator != (const Vector2D& first, const Vector2D& second) { return (first.X() != second.X() || first.Y() != second.Y()); }

private:
    double x, y;
};

