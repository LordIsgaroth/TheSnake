#pragma once

template<typename T>
class IObserver
{
public:
    virtual void OnNotify(T message) = 0;
};