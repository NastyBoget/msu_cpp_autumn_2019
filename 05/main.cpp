#include <iostream>
#include <sstream>
#include <cassert>
#include "serializer.h"
#include "deserializer.h"
#include "error.h"

struct Data1
{
    uint64_t a;
    bool b;
    uint64_t c;
    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
};
struct Data2
{
    bool a;
    bool b;
    uint64_t c;
    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
};
struct Data3
{
    float a;
    bool b;
    uint64_t c;
    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
};
int main()
{
    // test 1
    {
        Data1 x{1, true, 2};
        std::stringstream stream;
        Serializer serializer(stream);
        serializer.save(x);
        Data1 y{0, false, 0};
        Deserializer deserializer(stream);
        const Error err = deserializer.load(y);
        assert(x.a == y.a);
        assert(x.b == y.b);
        assert(x.c == y.c);
    }
    // test 2
    {
        Data1 x{1, true, 2};
        std::stringstream stream;
        Serializer serializer(stream);
        serializer.save(x);
        Data2 y{false, false, 0};
        Deserializer deserializer(stream);
        const Error err = deserializer.load(y);
        assert(err == Error::CorruptedArchive);
    }
    // test 3
    {
        Data3 x{1.15f, true, 2};
        std::stringstream stream;
        Serializer serializer(stream);
        const Error err = serializer.save(x);
        assert(err == Error::CorruptedArchive);
    }
    std::cout << "done" << std::endl;
    return 0;
}