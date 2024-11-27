// Copyright (c) 2019 Hanhui LI
#include "doraemon/sys/system.h"

#include <filesystem>

namespace doraemon
{

    char System::PathSeperator = std::filesystem::path::preferred_separator;

};  // namespace doraemon
