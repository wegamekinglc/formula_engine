#pragma once

#include <iostream>
#include <fel/time/timeunit.hpp>
#include <fel/time/period.hpp>
#include <fel/time/weekday.hpp>

namespace FEngine {

    using Day = int;

    enum Month { January   = 1,
                 February  = 2,
                 March     = 3,
                 April     = 4,
                 May       = 5,
                 June      = 6,
                 July      = 7,
                 August    = 8,
                 September = 9,
                 October   = 10,
                 November  = 11,
                 December  = 12,
                 Jan = 1,
                 Feb = 2,
                 Mar = 3,
                 Apr = 4,
                 Jun = 6,
                 Jul = 7,
                 Aug = 8,
                 Sep = 9,
                 Oct = 10,
                 Nov = 11,
                 Dec = 12
    };

    using Year = int;

    class Date {
        public:
            using serial_type = unsigned int;
            Date();
            explicit Date(serial_type serial);
            Date(const std::string& str);
            Date(Year y, Month m, Day d);
            
            Weekday weekday() const;
            Day dayOfMonth() const;
            Day dayOfYear() const;
            Month month() const;
            Year year() const;
            serial_type serial() const { return serial_;}
            
            static std::string to_string(const Date&);
            static serial_type minimumSerial();
            static serial_type maximumSerial();
            static Date minDate();
            static Date maxDate();
            static bool isLeap(Year y);
            static int monthLength(Month m, bool leapYear);
            static int monthOffset(Month m, bool leapYear);
            static Date::serial_type yearOffset(Year y);
            static Date endOfMonth(const Date& d);

            Date& operator+=(Date::serial_type days);
            //! increments date by the given period
            Date& operator+=(const Period&);
            //! decrement date by the given number of days
            Date& operator-=(Date::serial_type days);
            //! decrements date by the given period
            Date& operator-=(const Period&);

            Date& operator++();
            //! 1-day post-increment
            Date operator++(int );
            //! 1-day pre-decrement
            Date& operator--();
            //! 1-day post-decrement
            Date operator--(int );
            //! returns a new date incremented by the given number of days
            Date operator+(Date::serial_type days) const;
            //! returns a new date incremented by the given period
            Date operator+(const Period&) const;
            //! returns a new date decremented by the given number of days
            Date operator-(Date::serial_type days) const;
            //! returns a new date decremented by the given period
            Date operator-(const Period&) const;

        private:
            static Date advance(const Date& d, int units, TimeUnit);
            serial_type serial_;
    };

    inline bool operator==(const Date& d1, const Date& d2) {
        return (d1.serial() == d2.serial());
    }

    inline bool operator!=(const Date& d1, const Date& d2) {
        return (d1.serial() != d2.serial());
    }

    inline bool operator<(const Date& d1, const Date& d2) {
        return (d1.serial() < d2.serial());
    }

    inline bool operator<=(const Date& d1, const Date& d2) {
        return (d1.serial() <= d2.serial());
    }

    inline bool operator>(const Date& d1, const Date& d2) {
        return (d1.serial() > d2.serial());
    }

    inline bool operator>=(const Date& d1, const Date& d2) {
        return (d1.serial() >= d2.serial());
    }

    std::ostream& operator<<(std::ostream&, const Date&);

}