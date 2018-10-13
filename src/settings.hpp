#pragma once

#include "types.hpp"

namespace FEngine {
    template <class T>
    class Singleton {
        public:
            static T& instance();
        protected:
            Singleton() {}
        private:
            Singleton(const Singleton&);
            T& operator=(const Singleton&);
    };

    template <class T>
    T& Singleton<T>::instance() {
        static T instance;
        return instance;
    }

    class Settings: public Singleton<Settings> {
        public:
            DateTime referenceDate() const;
            void setReferenceDate(const DateTime&);

        private:
            DateTime referenceDate_;
    };
}