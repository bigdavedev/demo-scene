#include <dave_stdlib.h>

char* read_from_file(char const* filename)
{
    char* content = (char*)0;
    //DWORD dummy;

    //HANDLE file = CreateFile(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    //DWORD count = SetFilePointer(file, 0, NULL, FILE_END);
    //content = (char*)HeapAlloc(GetProcessHeap(), 0, (size_t)(count+1));
    //ReadFile(file, content, count, &dummy, NULL);
    //content[count] = '\0';
    //CloseHandle(file);
    return content;
}

void* malloc(size_t size)
{
    return GlobalAlloc(0, size);
}

void free(void* ptr)
{
    GlobalFree((HGLOBAL)ptr);
}

void* memset(void* dst, int val, size_t count)
{
    unsigned char* byte = dst;
    while(count--)
    {
        *byte++ = (unsigned char)val;
    }
    return dst;
}
