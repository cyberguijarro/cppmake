#pragma once

#include "node.hpp"
#include "file.hpp"

namespace cppmake
{

struct Program : public Node
{
    static BuildResult build(const Node& node, Environment& environment);

    inline Program(
        const std::string& path,
        Node::List dependencies 
    ) : Node(
        path,
        &Program::build,
        &File::timestamp,
        dependencies
    )
    {
    }
};

}
