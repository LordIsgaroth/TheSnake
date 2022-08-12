#pragma once

#include <memory>
#include "IObserver.hpp"

template<typename T>
class ISubject
{
public:
    virtual ~ISubject(){};

    virtual void Attach(std::shared_ptr<IObserver<T>> observer) = 0;
    virtual void Detach(std::shared_ptr<IObserver<T>> observer) = 0;
    virtual void Notify() = 0;
};
