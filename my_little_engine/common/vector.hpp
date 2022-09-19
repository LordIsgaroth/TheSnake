#pragma once

class Vector2D
{    
public:
    Vector2D();
    Vector2D(double x, double y);
    double x, y;

    static Vector2D Up();
    static Vector2D Down();
    static Vector2D Left();
    static Vector2D Right();
};

bool operator == (Vector2D first, Vector2D second);