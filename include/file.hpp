#pragma once

#include <string>
#include <regex>

#include "node.hpp"

namespace cppmake
{

struct File : public Node
{
    static BuildResult build(const Node& node, Environment&);
    static Clock::time_point timestamp(const Node& node);
    static Node::List glob(
        const std::string& path,
        const std::regex& pattern = std::regex(".*")
    );

    inline File(const std::string& path) : Node(
        path,
        &File::build,
        &File::timestamp,
        Node::List(),
        false
    )
    {
    }
};

}
