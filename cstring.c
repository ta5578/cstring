#include "cstring.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

// Internal dynamic array data structure.
typedef struct {
    char **arr;
    size_t size, cap;
} _cstr_arr;

// Append the provided string to the array of strings and report success status 
static bool _cstr_arr_append(_cstr_arr *arr, char *elem)
{
    if (arr->size >= arr->cap) {
        size_t n_cap = arr->cap == 0 ? 5 : arr->cap * 2;
        char **buf = realloc(arr->arr, n_cap * sizeof(*buf));
        if (buf) {
            arr->arr = buf;
            arr->cap = n_cap;
        } else {
            return false;
        }
    }
    arr->arr[arr->size++] = elem;
    return true;
}

char* cstr_alloc(size_t len)
{
    char *s = malloc(len + 1);
    if (s) {
        s[len] = '\0';
    }
    return s;
}

bool cstr_equals(const char *s1, const char *s2)
{
    assert(s1); assert(s2);
    return strcmp(s1, s2) == 0;
}

size_t cstr_app(char *dest, const char *src, size_t count, size_t dest_hint)
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

    char *copy = cstr_alloc(count);
    if (copy) {
        strncpy(copy, str, count); 
    }
    return copy;
}

bool cstr_split(const char *str, const char *token, char ***toks, size_t *count)
{
    assert(str); assert(token); assert(count);
   
    _cstr_arr tokens = { .arr = NULL, .size = 0, .cap = 0 };
    const size_t tok_size = strlen(token);
    
    char *tok = NULL;
    bool isSuccess = true;
    while ((tok = cstr_find(str, token))) {
        // copy the string from where we started to where we found the split string 
        char *n_tok = cstr_copy(str, tok - str);
        if (!n_tok || !_cstr_arr_append(&tokens, n_tok)) {
            isSuccess = false;
            goto done;
        }
        // start looking after where we found the split string
        str = tok + tok_size;
    }

    // Copy the rest of the string if we've found any tokens
    // We need to check if we found any tokens to avoid a full string duplication
    // Example: cstr_split("a sentence", " ") should return ["a", "sentence"]
    // Since we found a space, the position of str will be:
    // "a sentence"
    //    |-> str
    // If there were no tokens found, then we'd have the following:
    // "a sentence"
    //  |-> str
    if (*str && tokens.size > 0) {
        isSuccess = _cstr_arr_append(&tokens, cstr_copy(str, 0));
    }

done:
    *count = tokens.size;
    *toks = tokens.arr;
    return isSuccess;
}

size_t cstr_remove_char(char *str, char c)
{
    assert(str);

    char *pw = str;
    size_t count = 0;
    while (*str) {
        *pw = *str++;
        if (*pw != c) {
            ++pw;
        } else {
            ++count;
        }
    }
    *pw = '\0';
    return count;
}

size_t cstr_replace_char(char *str, char before, char after)
{
    assert(str);
    if (before == after) {
        return 0;
    }

    size_t count = 0;
    while (*str) {
        if (*str == before) {
            *str = after;
            ++count;
        }
        ++str;
    }
    return count;
}

size_t cstr_remove_str(char *base, const char *pattern)
{
    assert(base); assert(pattern);
    
    if (base == pattern) {
        *base = '\0';
        return 0;
    }

    const size_t pat_len = strlen(pattern);
    if (pat_len == 0) {
        return 0;
    }
    if (pat_len == 1) {
        return cstr_remove_char(base, *pattern);
    }
    
    // TODO: possible performance enhancement:
    // consider checking if len(base) < len(pattern) and exit early

    size_t count = 0;
    char *tok = NULL;
    while ((tok = cstr_find(base, pattern))) {
        memmove(tok, tok + pat_len, pat_len * sizeof(*tok));
        base = tok;
        ++count;
    }
    return count;
}
