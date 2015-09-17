#include "object.hpp"

#include <vector>
#include <string>
#include <iterator>

namespace cppmake
{

using namespace std;

Node::BuildResult Object::build(const Node& node, Environment& environment)
{
    vector<string> command{
        environment.toolchain["CXX"],
        environment.toolchain["CXX_SOURCE_PREFIX"],
        environment.toolchain["CXX_FLAGS"],
    };
   
    transform(
        node.dependencies.begin(), node.dependencies.end(),
        back_inserter(command),
        [] (const Node& node) { return node.path; }
    );

    command.push_back(environment.toolchain["CXX_TARGET_PREFIX"]);
    command.push_back(node.path);
   
    return run(command) ? BuildResult::Built : BuildResult::Error;
}

}
