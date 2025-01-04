#ifndef ENV_H
#define ENV_H

#include <stdlib.h>
#include <string.h>

void load_env();
const char* get_env(const char* key, const char* default_value);

#endif
