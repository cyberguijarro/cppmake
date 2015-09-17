#include "toolchain.hpp"

namespace cppmake
{

using namespace std;

const Toolchain gnuToolchain {
     make_pair("RM", "rm"),
     make_pair("AR", "ar")
};

const Toolchain gccToolchain {
     make_pair("CXX", "g++"),
     make_pair("CXX_SOURCE_PREFIX", "-c"),
     make_pair("CXX_TARGET_PREFIX", "-o"),
     make_pair("ARFLAGS", "rcs")
};

}
