#include <string.h>
int startsWith(const char* str, const char* start){
      size_t str_len = strlen(str), start_len = strlen(start);
      return str_len < start_len ? 0 : strncmp(str, start, start_len) == 0;
    }

