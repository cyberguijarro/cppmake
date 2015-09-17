#pragma once

#include <functional>
#include <chrono>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iterator>

#include "environment.hpp"

namespace cppmake
{

typedef std::chrono::system_clock Clock;

class Node
{
public:
    enum class BuildResult { NotBuilt = 0, Built, Error };
    typedef std::function<BuildResult(const Node&, Environment&)> Builder;
    typedef std::function<Clock::time_point(const Node&)> Timestamp;
    typedef std::vector<Node> List;

    std::string path;
    List dependencies;
    Builder builder;
    Timestamp timestamp;
    bool temporal;
   
    BuildResult make(Environment& environment) const;
    void clean() const;
   
    inline Node(
        const std::string path,
        Builder builder,
        Timestamp timestamp,
        List dependencies,
        bool temporal = true
    ) : path(path),
        builder(builder),
        timestamp(timestamp),
        dependencies(dependencies),
        temporal(temporal)
    {
    }
   
protected:
    template<typename C>
    static bool run(const C& iterable)
    {
        std::ostringstream command;

        std::copy(
           iterable.begin(), iterable.end(),
           std::ostream_iterator<std::string>(command, " ")
        );
        std::cout << command.str() << std::endl;
        system(command.str().c_str());

        return true;
   }
};

}
