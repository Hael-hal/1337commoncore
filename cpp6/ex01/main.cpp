#include "Serializer.hpp"


int main()
{
    Data data;

    data.age = 21;
    data.tag = " savage hamza!";
    
    std::cout << "kuro : " << data.age << data.tag << std::endl;

    Data *kuro = &data;

    std::cout << "Deserialized address:   " << kuro << std::endl;

    uintptr_t seri = Serializer::serialize(kuro);

    std::cout << "Serialized address:   " << seri << std::endl;

    Data *restored = Serializer::deserialize(seri);

    std::cout << "Deserialized address:   " << restored << std::endl;

    return 0;
}