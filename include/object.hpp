#pragma once

#include "node.hpp"
#include "file.hpp"

namespace cppmake
{

struct Object : public Node
{
    static BuildResult build(const Node& node, Environment& environment);

    inline Object(Node::List dependencies)
        : Node(
            dependencies.begin()->path + std::string(".o"),
            &Object::build,
            &File::timestamp,
            dependencies
        )
    {
    }

    inline Object(const Node& node) : Object(Node::List{node}) { }

    inline Object(const std::string& path) : Object(Node::List{File(path)}) { }
};

}
