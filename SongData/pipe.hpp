#ifndef SONGDATA_PIPE_HPP_INCLUDED
#define SONGDATA_PIPE_HPP_INCLUDED
#pragma once

#include <string>

namespace songdata {
    void* create_pipe(const char* name);
    void close_pipe(void* pipe);
    bool connect_pipe(void* pipe);

    bool read_pipe(void* pipe, std::string& s);
    bool write_pipe(void* pipe, const int& num);
}

#endif // SONGDATA_PIPE_HPP_INCLUDED
