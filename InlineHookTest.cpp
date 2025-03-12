#include <windows.h>
#include <stdio.h>
#include <memoryapi.h>

int main() {
    LPVOID funcAddress = reinterpret_cast<LPVOID>(CreateProcessA);
    printf("Function Address: %p\n", funcAddress);
    DWORD oldProtect;

    if (VirtualProtect(funcAddress, 94, PAGE_EXECUTE_READWRITE, &oldProtect)) {
        printf("Memory protection changed successfully.\n");
        printf("Old protection: 0x%X\n", oldProtect);
    }
    else {
        printf("VirtualProtect failed. Error: %d\n", GetLastError());
    }

    return 0;
}
