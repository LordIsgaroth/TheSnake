#pragma once

template<typename T>
class IObserver
{
public:
    virtual void Update(T message) = 0;
};