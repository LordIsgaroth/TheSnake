#pragma once

enum SnakeEventType
{
    PositionChanged,
    AppleEaten
};

class SnakeEvent
{
public:
    SnakeEvent(SnakeEventType type);
    const SnakeEventType Type() const;

private:    
    SnakeEventType type;
};