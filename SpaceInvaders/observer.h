#pragma once
#include <vector>
#include <iostream>
#include <memory>

namespace si {
    // M is the type of the message payload.
    template <typename M>
    class Observer {
    public:
        virtual ~Observer() {}
        virtual void onEvent(const M&) = 0;
    };

    template <typename M>
    class Observable {
    public:
        void publish(const M &m) {
            for (auto &observer : observers) {
				auto o = observer;
                observer->onEvent(m);
			}
        }

        void addObserver(Observer<M> *observer) {
            observers.push_back(observer);
        }

    private:
        std::vector<Observer<M> *> observers;
    };
}