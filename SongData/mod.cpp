#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <thread>
#include <filesystem>
#include <Windows.h>
#include <toml.hpp>
#include "exports.hpp"
#include "pipe.hpp"


static int* song_id = nullptr;


static void pipe_loop(void* pipe) {
    using namespace songdata;
    std::string input;

    do {
        const bool success = read_pipe(pipe, input);
        if (!success) { continue; }

        if (input == "song-id") {
            int id = *song_id;
            write_pipe(pipe, id);
        }
    } while (input != "exit");
}


static void start_process(const std::filesystem::path& path) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));

    si.cb = sizeof(si);

    const bool success = CreateProcess(path.c_str(),
      nullptr,
      nullptr,
      nullptr,
      false,
      0,
      nullptr,
      nullptr,
      &si,
      &pi
    );

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}


SONGDATA_API(void) init() {
    // Called before any of the game's global variables are initialized.
    using namespace songdata;

    const auto settings = toml::parse_file("settings.toml");
    const char* pipe_name = settings["pipe"].value_or("\\\\.\\pipe\\marcgii");

    song_id = reinterpret_cast<int*>(0x1416E2BEC);

    std::thread([pipe_name]() {
        auto* const pipe = create_pipe(pipe_name);
        const bool result = connect_pipe(pipe);

        if (result) {
            pipe_loop(pipe);
        }

        close_pipe(pipe);
    }).detach();

    try {
        const auto path_value = settings["start"].value_or("");
        const auto startup_path = std::filesystem::path(path_value);

        if (std::filesystem::exists(startup_path) &&
            std::filesystem::is_regular_file(startup_path)) {
            start_process(startup_path);
        }
    } catch (const toml::parse_error&) {
        // Do nothing.
    }
}
