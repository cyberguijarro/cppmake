#include "file.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

namespace cppmake
{

using namespace std;

Node::BuildResult File::build(const Node& node, Environment&)
{
    struct stat _stat;

    return (
        (stat(node.path.c_str(), &_stat) == 0)
        ? BuildResult::NotBuilt
        : BuildResult::Error
    );
}

Clock::time_point File::timestamp(const Node& node)
{
    struct stat _stat;

    stat(node.path.c_str(), &_stat);

    return Clock::from_time_t(_stat.st_mtime);
}

Node::List File::glob(const string& path, const regex& pattern)
{
    DIR* directory;
    struct dirent* entry;
    Node::List result;

    if (directory = opendir(path.c_str())) {
        while ((entry = readdir(directory)) != NULL) {
            if (
                (entry->d_type == DT_REG) 
                && (regex_match(entry->d_name, pattern))
            )
            {
                result.emplace_back(
                    path + '/' + entry->d_name,
                    &File::build,
                    &File::timestamp,
                    Node::List(),
                    false
                );
            }
        }

        closedir(directory);
    }

    return result;
}

}
