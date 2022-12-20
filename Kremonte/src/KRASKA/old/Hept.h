#pragma once

#include "Kremonte/krpch.h"

//#include <stdlib.h>
#include <iostream>

namespace Kremonte {

    static const std::string HEPT_CHARS = "0123456789ABCDEFGHKMNPRTVXZ";

    class Hept {
    public:

        inline int modulo(int a, int b)
        {
            const int result = a % b;
            return result >= 0 ? result : result + b;
        }

        Hept(int val) {
            std::string hept = "";

            do {
                int pos = val % 27;
                hept = std::string(HEPT_CHARS[modulo(pos + 13, 27)] + hept);
                val = (val + pos) / 27;
            } while (val != 0);

            //KR_INFO("constructed: {0]", )
            _val = hept;
        }

        std::string str() const {
            return _val;
        }

        Hept operator!() const {
            //return static_cast<CMYKvalue>(-value);
        }
    
        Hept operator&&(const Hept& h) const {

            //return (value < t.value) ? static_cast<CMYKvalue>(value) : t.value;
        }

        Hept operator||(const Hept& h) const {
            //return (-value > t.value) ? static_cast<CMYKvalue>(-value) : t.value;
        }

        Hept operator>>(const Hept& h) const {
            //return (-value > t.value) ? static_cast<CMYKvalue>(-value) : t.value;
        }

        Hept operator==(const Hept& h) const {
            //return static_cast<CMYKvalue>((value * t.value));
        }

    protected:
        std::string _val;
    };

    std::ostream& operator<<(std::ostream& ostr, const Hept& h) {
        ostr << h.str();
        return ostr;
    }

}