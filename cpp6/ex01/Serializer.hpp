#ifndef SR_H
#define SR_H

#include <stdint.h>
#include <iostream>
#include "Data.hpp"

class Serializer
{
    private:
        Serializer();
        Serializer(const Serializer& rhs);
        Serializer&  operator=(const Serializer& rhs);
        ~Serializer();
    public:
        static uintptr_t serialize(Data* ptr);
        static Data* deserialize(uintptr_t raw);
};


#endif