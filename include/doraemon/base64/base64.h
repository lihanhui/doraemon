/*Stolen from https://renenyffenegger.ch/notes/development/Base64/Encoding-and-decoding-base-64-with-cpp*/
#ifndef DORAEMON_BASE64_BASE64_H
#define DORAEMON_BASE64_BASE64_H

#include <string>
namespace doraemon{

struct base64 {
    static std::string encode(unsigned char const *, unsigned int len);
    static std::string decode(std::string const &s);
};
};
#endif /* BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A */