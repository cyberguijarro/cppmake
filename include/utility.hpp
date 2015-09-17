#pragma once

namespace cppmake
{

template<typename T>
Node::List convert(Node::List list)
{
    Node::List result;

    std::transform(
       list.begin(), list.end(),
       std::back_inserter(result),
       [] (const Node& node) { return T(node); }
    );

    return result;
}

}
