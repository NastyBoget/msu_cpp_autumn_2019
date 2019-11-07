#ifndef DESERIALIZER_H
#define DESERIALIZER_H

#include <istream>
#include "error.h"

class Deserializer {
public:
    explicit Deserializer(std::istream& in): in_(in)
    {}
    template <class T>
    Error load(T& object)
    {
        return object.serialize(*this);
    }
    template <class... ArgsT>
    Error operator()(ArgsT&... args)
    {
        return process(args...);
    }
private:
    std::istream& in_;
    // process использует variadic templates
    template <class T, class... ArgsT>
    Error process(T& arg, ArgsT&... args)
    {
        const Error err = process(arg);
        if (err == Error::NoError) {
            return process(args...);
        } else {
            return err;
        }
    }
    Error process(bool& arg);
    Error process(uint64_t& arg);
    template<class T>
    Error process(T& arg)
    {
        return Error::CorruptedArchive;
    }

};

#endif
