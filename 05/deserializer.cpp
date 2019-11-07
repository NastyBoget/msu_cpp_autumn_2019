#include "deserializer.h"

Error Deserializer::process(bool &arg)
{
    std::string text;
    in_ >> text;
    if (text == "true")
        arg = true;
    else if (text == "false")
        arg = false;
    else
        return Error::CorruptedArchive;
    return Error::NoError;
}

Error Deserializer::process(uint64_t &arg)
{
    std::string text;
    in_ >> text;
    try {
        arg = std::stoull(text);
    } catch (std::exception& e){
        return Error::CorruptedArchive;
    }
    return Error::NoError;
}

