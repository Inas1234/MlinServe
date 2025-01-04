#include "../include/Env.h"
#include <stdio.h>

void load_env() {
    const char* filename = ".env";
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Warning: Could not open .env file: %s\n", filename);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '\n' || line[0] == '#' || line[0] == '\r') {
            continue;
        }

        char* delimiter = strchr(line, '=');
        if (delimiter == NULL) {
            continue; 
        }

        *delimiter = '\0';
        char* key = line;
        char* value = delimiter + 1;

        size_t value_len = strlen(value);
        if (value[value_len - 1] == '\n') {
            value[value_len - 1] = '\0';
        }

        setenv(key, value, 1); 
    }

    fclose(file);
}


const char* get_env(const char* key, const char* default_value) {
    const char* value = getenv(key);
    return value ? value : default_value;
}
