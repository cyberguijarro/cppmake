#include <iostream>
#include "cppmake.hpp"

int main()
{
    using namespace std;
    using namespace cppmake;

    Environment environment{
        Toolchain(
            {gnuToolchain, gccToolchain},
            {make_pair("CXX_FLAGS", "-std=c++11 -Iinclude")}
         ),
        false
    };
    Node::List objects{
        convert<Object>(File::glob("src", std::regex(".*.cpp")))
    };

    StaticLibrary("cppmake.a", objects).make(environment);

    return 0;
}
