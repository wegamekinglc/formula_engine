#pragma once

#include <iostream>

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

            Day dayOfMonth() const;
            Day dayOfYear() const;
            Month month() const;
            Year year() const;
            serial_type serial() const { return serial_;}

            static serial_type minimumSerial();
            static serial_type maximumSerial();
            static Date minDate();
            static Date maxDate();
            static bool isLeap(Year y);
            static int monthLength(Month m, bool leapYear);
            static int monthOffset(Month m, bool leapYear);
            static Date::serial_type yearOffset(Year y);

        private:
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