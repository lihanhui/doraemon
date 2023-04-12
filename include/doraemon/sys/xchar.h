#ifndef DORAEMON_SYS_XCHAR_H
#define DORAEMON_SYS_XCHAR_H

#ifdef __WINDOWS__
    using nchar = wchar_t;
    using nstring = std::wstring;
#else
    using nchar = char;
    using nstring = std::string;
#endif    

#endif
