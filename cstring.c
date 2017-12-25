#include "cstring.h"
#include <assert.h>
#include <string.h>

char* cstralloc(size_t len)
{
    char *s = malloc(len + 1);
    if (s) {
        s[len] = '\0';
    }
    return s;
}

size_t cstrapp(char *dest, const char *src, size_t count, size_t dest_hint)
{
   assert(dest); assert(src);
   
   size_t dest_len = dest_hint == 0 ? strlen(dest) : dest_hint;
 
   // if the count is zero, we want to append the entire string
   // this has the effect of practically making count infinite
   // or the max bit representation of size_t (1111...111)
   if (count == 0) {
       count = (size_t)(~0);
   } 

   // could be strncpy 
   size_t amnt = 0;
   dest += dest_len;
   while (amnt < count && *src) {
       *dest++ = *src++;
       ++amnt; 
   }
   *dest = '\0';
   return amnt; 
}

bool cstr_is_prefix(const char *base, const char *pre)
{
    assert(base); assert(pre);
    while (*base && *pre) {
        if (*base++ != *pre++) {
             return false;
        }
    }
    return true;
}

char* cstr_find(const char *base, const char *str)
{
    return strstr(base, str);
}

bool cstr_contains(const char *base, const char *str)
{
    return cstr_find(base, str) != NULL;
}

char* cstr_copy(const char *str, size_t count)
{
    if (count == 0) {
        count = strlen(str);
    }

    char *copy = cstralloc(count);
    if (copy) {
        strncpy(copy, str, count); 
    }
    return copy;
}
