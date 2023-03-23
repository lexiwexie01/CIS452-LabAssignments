#include <stdio.h>
#include <Windows.h>


 char* getStateType(MEMORY_BASIC_INFORMATION* mbi) {
    switch (mbi->State) {
        case MEM_COMMIT:
            return "Committed";
            break;
        case MEM_RESERVE:
            return "Reserved";
            break;
        case MEM_FREE:
            return "Free";
            break;
        default:
            return "N\\A";
            break;
    }
}


int main() {
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);
    printf("Page Size: %u bytes\n", systemInfo.dwPageSize);

    void* memory = VirtualAlloc(NULL, (1024*1024), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    if (memory == NULL) {
        printf("Error: Failed to allocate memory\n");
        return 1;
    }

    MEMORY_BASIC_INFORMATION memoryBasicInformation;
    VirtualQuery(memory, &memoryBasicInformation, sizeof(memoryBasicInformation));
    printf("Allocated memory state: %s\n", getStateType(&memoryBasicInformation));
    VirtualFree(memory, 0, MEM_RELEASE);
    // memory = VirtualAlloc(NULL, (1024*1024), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    VirtualQuery(memory, &memoryBasicInformation, sizeof(memoryBasicInformation));
    printf("Allocated memory state after de-allocating memory: %s\n", getStateType(&memoryBasicInformation));
    VirtualFree(memory, 0, MEM_RELEASE);
    return 0;

}