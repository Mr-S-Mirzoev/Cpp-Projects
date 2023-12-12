#pragma once

#ifdef _WIN32
#include <io.h>
#define access _access_s
#else
#include <unistd.h>
#endif
#include <string>

static bool FileExists(const std::string& Filename) { return access(Filename.c_str(), 0) == 0; }
