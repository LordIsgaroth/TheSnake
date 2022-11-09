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
private:
    double x, y;
};

bool operator == (Vector2D first, Vector2D second);
bool operator != (Vector2D first, Vector2D second);