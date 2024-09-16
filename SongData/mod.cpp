#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <thread>
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


SONGDATA_API(void) init() {
    // Called before any of the game's global variables are initialized.
    using namespace songdata;

    song_id = reinterpret_cast<int*>(0x1416E2BEC);

	std::thread([]() {
		auto* const pipe = create_pipe("\\\\.\\pipe\\marcgii");
		const bool result = connect_pipe(pipe);

		if (result) {
			pipe_loop(pipe);
		}

		close_pipe(pipe);
	}).detach();
}
