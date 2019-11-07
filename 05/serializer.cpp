#include "serializer.h"

Error Serializer::process(bool arg)
{
    if (arg) {
        out_ << "true";
    } else {
        out_ << "false";
    }
    return Error::NoError;
}
Error Serializer::process(uint64_t arg)
{
    out_ << arg;
    return Error::NoError;
}