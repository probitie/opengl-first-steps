#ifndef LOGGER_H
#define LOGGER_H

#include <string.h>

// to make shorter names in debug log, (for Windows - \\, for linux/mac - /)
#ifdef __APPLE__
#define SLASH '/'
#endif
#ifdef __linux__
#define SLASH '/'
#endif
#ifdef _WIN32
#define SLASH '\\'
#endif
#ifdef __MINGW64__
#define SLASH '\\'
#endif
#ifdef __MSC_VER__
#define SLASH '\\'
#endif


#define __FILENAME__ (strrchr(__FILE__, SLASH) ? strrchr(__FILE__, SLASH) + 1 : __FILE__)

#define log(level, message) std::cout << level << "::" << __FILENAME__ << "::" << __LINE__ \
    << "::" << __FUNCTION__ << ":: " << message << std::endl

// dont forget to include <iostream>
// you can use it like this "debuglog("Hello " << user->name)"
#define debuglog(message) log("DEBUG", message)
#define errorlog(message) log("ERROR", message)
#define warnlog(message)  log("WARNING", message)


#endif // LOGGER_H
