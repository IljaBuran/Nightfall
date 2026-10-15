#pragma once

#if defined(_WIN32)

#define NF_WINDOWS 1

#elif defined(__linux__)

#define NF_LINUX 1

#elif defined(__APPLE__)

#define NF_MAC 1

#endif