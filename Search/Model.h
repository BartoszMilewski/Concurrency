#include "Win/Win.h"
#include "Win/Message.h"
#include <vector>
#include <string>
#include <filesystem>
#include <mutex>
#include <thread>

#define ASYNC_IMPL 1
#define PAR_IMPL 1

using namespace std::tr2::sys;

class Model;

class FileSink
{
public:
    FileSink(Model * model) : _model(model) {}
    virtual ~FileSink() {}
    virtual void AddFile(std::wstring const & file, int n) = 0;
protected:
    Model * _model;
};

class Model
{
public:
    Model(Win::Dow winTop, Win::Message const & msgNotify, std::wstring const & root);
    ~Model();
    void Clear()
    {
        _files.clear();
    }
    void SearchFiles(std::wstring const & str);
    void SearchFilesAsync(std::wstring const & str);
    std::vector<std::wstring> const & GetFiles()
    {
        return _files;
    }
    void AddFile(std::wstring const & name, int n);
    void AddFileAsync(std::wstring const & name, int n);
    std::wstring GetFileSnc();

private:
    std::wstring _root;
    std::vector<std::wstring> _files;
    // Asynchronous
    Win::Dow _win;
    Win::Message _msgNotify;
    std::mutex _mutex;
    std::thread _worker;
    std::unique_ptr<FileSink> _sink;
};


void SearchFilesRec(wpath const & path, std::wstring const & str, FileSink & sink);

void SearchFilesRecPar(wpath const & path, std::wstring const & str, FileSink & sink);

class FileSinkSync : public FileSink
{
public:
    FileSinkSync(Model * model) : FileSink(model) {}
    virtual ~FileSinkSync() {}
    virtual void AddFile(std::wstring const & file, int n)
    {
        _model->AddFile(file, n);
    }
};

class FileSinkAsync : public FileSink
{
public:
    FileSinkAsync(Model * model) : FileSink(model) {}
    void AddFile(std::wstring const & file, int n)
    {
        _model->AddFileAsync(file, n);
    }
};


