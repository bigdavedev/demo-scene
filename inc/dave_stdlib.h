#pragma once

/*
 * A peril of demo-scening is that we cannot use the std run-time since it is
 * essentially a waste of space.  Here we define a few helpful functions that
 * that are good to have.
 */

#include <windows.h>

char* read_from_file(char const* filename);

extern void* memset(void* dst, int val, size_t count);
