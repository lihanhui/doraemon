#include <filesystem>

#include "doraemon/sys/system.h"

namespace doraemon{

char System::PathSeperator = std::filesystem::path::preferred_separator;

};
