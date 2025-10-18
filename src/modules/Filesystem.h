#ifndef FILESYSTEM_H
#define FILESYSTEM_H


#include <FS.h>

void setupFileSystem();
bool fileExists(const char* path);
File openFile(const char* path, const char* mode);

#endif // FILESYSTEM_H
