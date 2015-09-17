#pragma once

#include <map>
#include <string>
#include <algorithm>
#include <initializer_list>

namespace cppmake
{

class Toolchain : public std::map<std::string, std::string>
{
private:
    typedef std::map<std::string, std::string> Base;

public:
    inline Toolchain(std::initializer_list<Base::value_type> list)
        : Base(list)
    {
    }
   
    inline Toolchain(std::initializer_list<Toolchain> toolchains)
    {
        for_each(
            toolchains.begin(), toolchains.end(),
            [this] (const Toolchain& toolchain) {
                insert(toolchain.begin(), toolchain.end());
            }
        );
    }
   
    inline Toolchain(
        std::initializer_list<Toolchain> toolchains,
        std::initializer_list<Base::value_type> extra
    ) : Toolchain(toolchains)
    {
        insert(extra.begin(), extra.end());
    }
};

extern const Toolchain gnuToolchain;
extern const Toolchain gccToolchain;

}
