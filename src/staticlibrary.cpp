#include "staticlibrary.hpp"

#include <vector>
#include <string>
#include <iterator>

namespace cppmake
{

using namespace std;

Node::BuildResult StaticLibrary::build(
    const Node& node,
    Environment& environment
)
{
    vector<string> command{
        environment.toolchain["AR"],
        environment.toolchain["ARFLAGS"],
    };

    command.push_back(node.path);

    transform(
        node.dependencies.begin(), node.dependencies.end(),
        back_inserter(command),
        [] (const Node& node) { return node.path; }
    );

    return run(command) ? BuildResult::Built : BuildResult::Error;
}

}
