#include "FileUtil.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

#include<stdio.h>

std::string getFileContents(const std::string &filePath)
{
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        throw std::runtime_error("Unable to open file: " + filePath);
    }

    std::stringstream stream;

    stream << inFile.rdbuf();
    return stream.str();
}

//const char* get_file_content(const char* path) 
//{
//    FILE* pFile;
//    long lSize;
//    char* buffer;
//    size_t result;
//    
//    pFile = fopen(path, "rb");
//    if (pFile == NULL) { fputs("File error", stderr); exit(1); }
//
//    // obtain file size:
//    fseek(pFile, 0, SEEK_END);
//    lSize = ftell(pFile);
//    rewind(pFile);
//
//    // allocate memory to contain the whole file:
//    buffer = (char*)malloc(sizeof(char) * lSize);
//    if (buffer == NULL) { fputs("Memory error", stderr); exit(2); }
//    
//    // copy the file into the buffer:
//    result = fread(buffer, 1, lSize, pFile);
//    if (result != lSize) { fputs("Reading error", stderr); exit(3); }
//
//    // terminate
//    fclose(pFile);
//    return buffer;
//}
