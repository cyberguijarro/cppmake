#include "node.hpp"

#include <unistd.h>

namespace cppmake
{

using namespace std;

Node::BuildResult Node::make(Environment& environment) const
{
    BuildResult result = BuildResult::NotBuilt;
    bool outdated = false;

    if (environment.verbose)
        cout << "Processing '" << path << "'... " << endl;

    for_each(
        dependencies.begin(), dependencies.end(),
        [this, &result, &environment, &outdated] (const Node& node) {
            result = max(node.make(environment), result);
            outdated = (node.timestamp(node) > timestamp(*this));
        }
    );

    if (outdated || (result == BuildResult::Built))
        result = builder(*this, environment);

    if (environment.verbose) {
        cout << "'" << path << "' ";

        switch (result) {
        case BuildResult::NotBuilt:
            cout << "skipped" << endl;
            break;
        case BuildResult::Built:
            cout << "built" << endl;
            break;
        case BuildResult::Error:
            cout << "error" << endl;
            break;
        }
    }

    return result;
}

void Node::clean() const
{
    for_each(
        dependencies.begin(), dependencies.end(),
        bind(&Node::clean, placeholders::_1)
    );

    if (temporal) {
        cout << "Removing '" << path << "'..." << endl;
        unlink(path.c_str());
    }
}

}
