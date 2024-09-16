#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <Windows.h>
#include "pipe.hpp"


void* songdata::create_pipe(const char* name) {
    constexpr const int buffer_size = sizeof(int);
    constexpr const unsigned long mode = PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT;

    return CreateNamedPipeA(name, PIPE_ACCESS_DUPLEX, mode, 1, buffer_size, buffer_size, 0, nullptr);
}


void songdata::close_pipe(void* pipe) {
    CloseHandle(pipe);
}


bool songdata::connect_pipe(void* pipe) {
    return ConnectNamedPipe(pipe, nullptr);
}


bool songdata::read_pipe(void* pipe, std::string& s) {
    constexpr const size_t max_size = 128;

    char buffer[max_size]{};
    unsigned long read = 0;

    const bool success = ReadFile(pipe, buffer, max_size - 1, &read, nullptr);

    if (!success || read == 0) { return false; }

    buffer[read] = '\0';
    s.assign(buffer, read);

    return success;
}


bool songdata::write_pipe(void* pipe, const int& num) {
    unsigned long written = 0;
    const bool success = WriteFile(pipe, &num, sizeof(num), &written, nullptr);
    return success;
}
