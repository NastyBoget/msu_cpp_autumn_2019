#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <ostream>
#include "error.h"

class Serializer
{
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out): out_(out)
    {}
    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }
    template <class... ArgsT>
    Error operator()(ArgsT... args)
    {
        return process(args...);
    }
private:
    std::ostream& out_;
    // process использует variadic templates
    template <class T, class... ArgsT>
    Error process(T arg, ArgsT... args)
    {
        const Error err = process(arg);
        if (err == Error::NoError) {
            out_ << Separator;
            return process(args...);
        } else {
            return err;
        }
    }
    Error process(bool arg);
    Error process(uint64_t arg);
    template<class T>
    Error process(T arg)
    {
        return Error::CorruptedArchive;
    }
};

#endif
