#include <windows.h>
#include <stdio.h>
#include <iostream>
//TODO, check function contents against loadLibraryA first load kernel32.dll from disk

size_t GetFunctionSize(void* func) {
    unsigned char* p = static_cast<unsigned char*>(func);
    size_t size = 0;
    while (true) {
        // Common x86/x64 RET instructions: 0xC3 (RET), 0xC2 (RET imm16)
        if (p[size] == 0xC3 || p[size] == 0xC2) {
            return size + 1; 
        }
        size++;
        if (size > 1000) break; 
    }
    return 0;
}

void PrintFunctionBytes(void* func, size_t length) {
    unsigned char* p = static_cast<unsigned char*>(func);
    printf("Function bytes: ");
    for (size_t i = 0; i < length; i++) {
        printf("0x%02X ", p[i]);
    }
}

int main() {
    void* funcAddress = reinterpret_cast<void*>(&CreateProcessA);
    size_t funcSize = GetFunctionSize(funcAddress);
    if (funcSize > 0) {
        PrintFunctionBytes(funcAddress, funcSize);
    }
    else {
        printf("Could not determine func size");
    }
    HMODULE hModule = LoadLibraryA("C:\\Windows\\System32\\kernel32.dll");

    if (hModule) {
        printf("Loaded copy of kernel32.dll at : %p\n", hModule);
        void* funcAddress = reinterpret_cast<void*>(GetProcAddress(hModule, "CreateProcessA"));
        printf("CreateProcessA address %p\n", funcAddress);
        size_t funcSize = GetFunctionSize(funcAddress);
        PrintFunctionBytes(funcAddress, funcSize);
        printf("\nEstimated Function Size %zu\n", funcSize);
        FreeLibrary(hModule); 
    }
    else {
        printf("Failed to load kernel32.dll. Error: %d\n", GetLastError());
    }

    return 0;
}
