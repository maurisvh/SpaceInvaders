#pragma once
#include <vector>
#include <iostream>
#include <memory>

namespace si {
    // E is the type of the event payload.
    template <typename E>
    class Observer {
    public:
        virtual ~Observer() {}
        virtual void onEvent(const E&) = 0;
    };

    template <typename E>
    class Observable {
    public:
        void publish(const E &e) {
            for (auto &observer : observers)
                observer->onEvent(e);
        }

        void addObserver(std::shared_ptr<Observer<E>> observer) {
            observers.push_back(observer);
        }

    private:
        std::vector<std::shared_ptr<Observer<E>>> observers;
    };

    template <typename E>
    struct Propagate : Observer<E>, Observable<E> {
        void onEvent(const E &e) override { publish(e); }
    };
}