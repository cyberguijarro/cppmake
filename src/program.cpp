#include "program.hpp"

#include <vector>
#include <string>
#include <iterator>

namespace cppmake
{

using namespace std;

Node::BuildResult Program::build(const Node& node, Environment& environment)
{
    vector<string> command{
        environment.toolchain["CXX"],
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
