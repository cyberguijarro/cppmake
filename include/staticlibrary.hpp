#pragma once

#include "node.hpp"
#include "file.hpp"

namespace cppmake
{

struct StaticLibrary : public Node
{
    static BuildResult build(const Node& node, Environment& environment);

    inline StaticLibrary(
        const std::string& path,
        Node::List dependencies 
    ) : Node(
        path,
        &StaticLibrary::build,
        &File::timestamp,
        dependencies
    )
    {
    }
};

}
