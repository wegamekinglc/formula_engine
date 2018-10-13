#pragma once

#include <fel/types.hpp>

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
            const vector<string>& symbols() const;
            void setSymbols(const vector<string>&);

        private:
            DateTime referenceDate_;
            vector<string> symbols_;
    };
}