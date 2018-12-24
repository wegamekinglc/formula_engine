#pragma once

#include <fel/types.hpp>

namespace FEngine {
    template <class T>
    class Singleton {
        public:
            static T& instance();
            Singleton(const Singleton&) = delete;
            T& operator=(const Singleton&) = delete;
        protected:
            Singleton() = default;
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
            const Vector_<String_>& symbols() const;
            void setSymbols(const Vector_<String_>&);

        private:
            DateTime referenceDate_;
            Vector_<String_> symbols_;
    };


    class GlobalSymbols {
        public:
            explicit GlobalSymbols(const Vector_<String_>& symbols);
            ~GlobalSymbols();

        private:
            Vector_<String_> preSymbols_;
    };
}