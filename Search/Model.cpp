#include "Model.h"
#include <fstream>
#include <string>

// Thread function
void worker(std::wstring root, std::wstring str, FileSink * sink)
{
#if PAR_IMPL == 1
    SearchFilesRecPar(root, str, *sink);
#else
    SearchFilesRec(root, str, *sink);
#endif
}

Model::Model(Win::Dow winTop, Win::Message const & msgNotify, std::wstring const & root)
: _win(winTop), _root(root), _msgNotify(msgNotify)
{
#if ASYNC_IMPL == 1
    _sink.reset(new FileSinkAsync(this));
#else
    _sink.reset(new FileSinkSync(this));
#endif
}

Model::~Model()
{
    if (_worker.joinable())
        _worker.join();
}

void Model::SearchFiles(std::wstring const & str)
{
    SearchFilesRec(_root, str, *_sink);
}

void Model::SearchFilesAsync(std::wstring const & str)
{
    if (_worker.joinable())
        _worker.join();
    _worker = std::thread(worker, _root, str, _sink.get());
}

void Model::AddFile(std::wstring const & name, int n)
{
    if (n > 0)
        _files.push_back(name);
}

void Model::AddFileAsync(std::wstring const & name, int n)
{
    if (n > 0)
    {
        std::lock_guard<std::mutex> lck(_mutex);
        AddFile(name, n);
        _win.PostMsg(_msgNotify);
    }
}

std::wstring Model::GetFileSnc()
{
    std::lock_guard<std::mutex> lck(_mutex);
    if (_files.empty())
        return std::wstring();

    std::wstring str = std::move(_files.front());
    _files.pop_back();
    return str;
}

// Free functions

int findInFile(wpath const & path, std::wstring const & str)
{
    std::wifstream in(path);
    int n = 0;
    while (in)
    {
        std::wstring word;
        in >> word;
        if (word == str)
            ++n;
    }
    return n;
}

void SearchFilesRec(wpath const & path, std::wstring const & str, FileSink & sink)
{
    for (wdirectory_iterator it(path); it != wdirectory_iterator(); ++it)
    {
        if (is_regular_file(it->status()))
        {
            std::wstring name = it->path().leaf();
            int n = findInFile(it->path(), str);
            sink.AddFile(name, n);
        }
        else if (is_directory(it->status()))
        {
            SearchFilesRec(it->path(), str, sink);
        }
    }
}

void SearchFilesRecPar(wpath const & path, std::wstring const & str, FileSink & sink)
{
    std::vector<std::thread> threads;
    for (wdirectory_iterator it(path); it != wdirectory_iterator(); ++it)
    {
        if (is_regular_file(it->status()))
        {
            std::wstring name = it->path().leaf();
            int n = findInFile(it->path(), str);
            sink.AddFile(name, n);
        }
        else if (is_directory(it->status()))
        {
            threads.emplace_back(worker, it->path(), str, &sink);
        }
    }
    for (std::thread & th : threads)
        th.join();
}


