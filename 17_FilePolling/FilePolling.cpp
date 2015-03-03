#include <thread>
#include <future>
#include <filesystem>
#include <vector>
#include <string>
#include <iostream>
#include <mutex>

// filesystem
using namespace std::tr2::sys;
using namespace std;

class FileMonitor
{
public:
    void push_back(string file)
    {
        lock_guard<mutex> lck(_mtx);
        _allFiles.push_back(move(file));
    }
    bool hasData() const
    {
        lock_guard<mutex> lck(_mtx);
        return !_allFiles.empty();
    }
    string pop_back()
    {
        lock_guard<mutex> lck(_mtx);
        string name = move(_allFiles.back());
        _allFiles.pop_back();
        return name;
    }
private:
    mutable mutex _mtx;
    vector<string> _allFiles;
};

void listDir(string path, FileMonitor & fileSink)
{
    for (directory_iterator it(path); it != directory_iterator(); ++it)
    {
        if (is_regular_file(it->status()))
        {
            fileSink.push_back(it->path().leaf());
        }
    }
}

void listDirs(vector<path> paths, FileMonitor & fileSink)
{
    vector<future<void>> futures;
    for (auto & pth : paths)
    {
        cout << pth << endl;
        futures.emplace_back(async(listDir, pth, ref(fileSink)));
    }
    for (;;)
    {
        if (fileSink.hasData())
        {
            string name = fileSink.pop_back();
            cout << name << endl;
        }
    }
    for (auto &fut : futures)
    {
        fut.wait();
    }
}

void main()
{
    vector<path> paths;
    for (directory_iterator it("c:\\"); it != directory_iterator(); ++it)
    {
        if (is_directory(it->status()))
            paths.push_back(it->path());
    }

    FileMonitor fileSink;
    listDirs(paths, fileSink);
}

