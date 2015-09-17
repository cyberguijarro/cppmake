#pragma once

#include "toolchain.hpp"

namespace cppmake
{

struct Environment
{
    Toolchain toolchain;
    bool verbose;
};

}
