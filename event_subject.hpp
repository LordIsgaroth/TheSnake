#pragma once

#include <unordered_set>

#include "ISubject.hpp"
#include "IObserver.hpp"

template<typename T>
class EventSubject : public ISubject<T>
{
public:

    typedef IObserver<T> observer;

    void Attach(observer *obs) override
    {
        auto obsInSet = observers.find(obs);

        if (obsInSet == observers.end())
        {
            observers.insert(obs);
        }
    }

    void Detach(observer *obs) override
    {
        auto obsInSet = observers.find(obs);

        if (obsInSet != observers.end())
        {
            observers.erase(*obsInSet);
        }       
    }
    
    void Notify() override
    {
        for(observer *obs : observers)
        {
            obs->Update(message);
        }
    }

    void SetMessage(T message)
    {
        this->message = message;
    }

private:
    std::unordered_set<observer*> observers;
    T message;
};