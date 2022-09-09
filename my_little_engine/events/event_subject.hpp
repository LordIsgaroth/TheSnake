#pragma once

#include <memory>
#include <unordered_set>

#include "my_little_engine/common/ISubject.hpp"
#include "my_little_engine/common/IObserver.hpp"

template<typename T>
class EventSubject : public ISubject<T>
{
public:
    
    typedef std::shared_ptr<IObserver<T>> observer;

    void Attach(observer obs) override
    {
        auto obsInSet = observers.find(obs);

        if (obsInSet == observers.end())
        {
            observers.insert(obs);
        }
    }

    void Detach(observer obs) override
    {
        auto obsInSet = observers.find(obs);

        if (obsInSet != observers.end())
        {
            observers.erase(*obsInSet);
        }
    }
    
    void Notify(T message) override
    {
        for(observer obs : observers)
        {
            obs->OnNotify(message);
        }
    }

private:
    std::unordered_set<observer> observers;
};