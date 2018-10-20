#include <fel/time/date.hpp>
#include <fel/utilities/errors.hpp>
#include <iomanip>

namespace FEngine {
    Date::serial_type Date::minimumSerial() {
        return 367;       // Jan 1st, 1901
    }

    Date::serial_type Date::maximumSerial() {
        return 109574;    // Dec 31st, 2199
    }

    Date Date::minDate() {
        static const Date minimumDate(minimumSerial());
        return minimumDate;
    }

    Date Date::maxDate() {
        static const Date maximumDate(maximumSerial());
        return maximumDate;
    }

    namespace {

        void checkSerial(Date::serial_type serial) {
            FEL_REQUIRE(serial >= Date::minimumSerial() &&
                        serial <= Date::maximumSerial(),
                        "Date's serial number (" << serial << ") outside "
                        "allowed range [" << Date::minimumSerial() <<
                        "-" << Date::maximumSerial() << "], i.e. [" <<
                        Date::minDate() << "-" << Date::maxDate() << "]");
        }

        struct iso_date_holder {
            explicit iso_date_holder(const Date& d) : d(d) {}
            Date d;
        };

        iso_date_holder iso_date(const Date& d) {
            return iso_date_holder(d);
        }

        struct FormatResetter {
            struct nopunct : std::numpunct<char> {
                std::string do_grouping() const {return "";}
            };
            explicit FormatResetter(std::ostream &out)
                : out_(&out), flags_(out.flags()), filler_(out.fill()),
                  loc_(out.getloc()) {
                std::locale loc (out.getloc(),new nopunct);
                out.imbue(loc);
                out << std::resetiosflags(
                    std::ios_base::adjustfield | std::ios_base::basefield |
                    std::ios_base::floatfield | std::ios_base::showbase |
                    std::ios_base::showpos | std::ios_base::uppercase);
                out << std::right;
            }
            ~FormatResetter() {
                out_->flags(flags_);
                out_->fill(filler_);
                out_->imbue(loc_);
            }
            std::ostream *out_;
            std::ios_base::fmtflags flags_;
            char filler_;
            std::locale loc_;
        };

        std::ostream& operator<<(std::ostream& out,
                                 const iso_date_holder& holder) {
            const Date& d = holder.d;
            if (d == Date()) {
                out << "null date";
            } else {
                FormatResetter resetter(out);
                unsigned int dd = d.dayOfMonth();
                unsigned int mm = d.month();
                unsigned yyyy = d.year();
                out << yyyy << "-";
                out << std::setw(2) << std::setfill('0') << mm << "-";
                out << std::setw(2) << std::setfill('0') << dd;
            }
            return out;
        }
    }

    std::ostream& operator<<(std::ostream& out, const Date& d) {
        return out << iso_date(d);
    }
}