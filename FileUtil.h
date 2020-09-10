#ifndef FILEUTIL_H_INCLUDED
#define FILEUTIL_H_INCLUDED

#include <string>

std::string getFileContents(const std::string &filePath);

const char* get_file_content(const char* path);
#endif // FILEUTIL_H_INCLUDED
