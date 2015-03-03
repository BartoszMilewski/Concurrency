#include <thread>
#include <future>
#include <filesystem>
#include <vector>
#include <string>
#include <iostream>

// filesystem
using namespace std::tr2::sys;
using namespace std;

vector<string> listDir(path const & dir)
{
    vector<string> files;
    for (directory_iterator it(dir); it != directory_iterator(); ++it)
    {
        if (is_regular_file(it->status()))
        {
            files.push_back(it->path().leaf());
        }
    }
    return files;
}

vector<string> listDirs(vector<path> const & paths)
{
    vector<future<vector<string>>> futures;
    for (auto const & pth: paths)
    {
        cout << pth << endl;
        futures.emplace_back(async(listDir, ref(pth)));
    }
    vector<string> allFiles;
    for (auto & fut : futures)
    {
        auto files = fut.get();
        move(files.begin(), files.end(), back_inserter(allFiles));
    }
    return allFiles;
}

void main()
{
    vector<path> paths;
    for (directory_iterator it("c:\\"); it != directory_iterator(); ++it)
    {
        if (is_directory(it->status()))
            paths.push_back(it->path());
    }

    for (auto name : listDirs(paths))
        cout << name << endl;
}

