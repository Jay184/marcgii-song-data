#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <Windows.h>


int __stdcall DllMain(HMODULE module, unsigned long reason, void* reserved) {
    switch (reason) {
        case DLL_PROCESS_ATTACH:
        case DLL_PROCESS_DETACH:
            break;
    }

    return 1;
}
