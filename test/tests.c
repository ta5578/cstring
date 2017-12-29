#include "cstring.h"
#include "CuTest.h"
#include <string.h>
#include <stdlib.h>

void TestAppendEntireStringNoHint(CuTest *c)
{
    const char *str = "testing";
    size_t len1 = strlen(str);
    const char *other = "tamer";
    size_t len2 = strlen(other);

    char *buf = cstr_alloc(len1 + len2);
    size_t appended = cstr_app(buf, other, 0, 0);

    CuAssertStrEquals(c, "tamer", buf);
    CuAssertTrue(c, strlen(buf) == len2);
    CuAssertTrue(c, appended == len2);
}

void TestAppendSubStringNoHint(CuTest *c)
{
    const char *str = "testing";
    size_t len1 = strlen(str);
    const char *other = "tamer";
    size_t len2 = strlen(other);

    char *buf = cstr_alloc(len1 + len2);
    size_t appended = cstr_app(buf, other, 2, 0);

    CuAssertStrEquals(c, "ta", buf);
    CuAssertTrue(c, strlen(buf) == 2);
    CuAssertTrue(c, appended == 2);
}

void TestAppendEntireStringWithHint(CuTest *c)
{
    const char *str = "testing";
    size_t len1 = strlen(str);
    const char *other = "tamer";
    size_t len2 = strlen(other);

    char *buf = cstr_alloc(len1 + len2);
    strcpy(buf, str);
    size_t appended = cstr_app(buf, other, 0, len1);

    CuAssertStrEquals(c, "testingtamer", buf);
    CuAssertTrue(c, strlen(buf) == len1 + len2);
    CuAssertTrue(c, appended == len2);
}

void TestAppendSubStringWithHint(CuTest *c)
{
    const char *str = "testing";
    size_t len1 = strlen(str);
    const char *other = "tamer";
    size_t len2 = strlen(other);

    char *buf = cstr_alloc(len1 + len2);
    strcpy(buf, str);
    size_t appended = cstr_app(buf, other, 3, len1);

    CuAssertStrEquals(c, "testingtam", buf);
    CuAssertTrue(c, strlen(buf) == len1 + 3);
    CuAssertTrue(c, appended == 3);
}

void TestAppendSubStringWithCountGreaterThanStringLength(CuTest *c)
{
    const char *str = "testing";
    size_t len1 = strlen(str);
    const char *other = "tamer";
    size_t len2 = strlen(other);

    char *buf = cstr_alloc(len1 + len2);
    strcpy(buf, str);
    size_t appended = cstr_app(buf, other, 10, len1);

    CuAssertStrEquals(c, "testingtamer", buf);
    CuAssertTrue(c, strlen(buf) == len1 + len2);
    CuAssertTrue(c, appended == len2);
}

void TestIsPrefixShouldBeTrue(CuTest *c)
{
    const char *base = "thisisastring";
    CuAssertTrue(c, cstr_is_prefix(base, "this"));
}

void TestIsPrefixShouldBeFalse(CuTest *c)
{
    const char *base = "thisisastring";
    CuAssertTrue(c, !cstr_is_prefix(base, "abc"));
}

void TestFindStringShouldBeTrue(CuTest *c)
{
    CuAssertTrue(c, cstr_find("thisisa  string", "isa") != NULL);
}

void TestFindStringShouldBeFalse(CuTest *c)
{
    CuAssertTrue(c, cstr_find("thisisa  string", "xxx") == NULL);
}

void TestContainsStringShouldBeTrue(CuTest *c)
{
    CuAssertTrue(c, cstr_contains("thisisa  string", "isa"));
}

void TestContainsStringShouldBeFalse(CuTest *c)
{
    CuAssertTrue(c, !cstr_contains("thisisa  string", "xxx"));
}

void TestCopyFullString(CuTest *c)
{
    char *copy = cstr_copy("tamer", 0);
    CuAssertIntEquals(c, 5, strlen(copy));
}

void TestCopySubString(CuTest *c)
{
    char *copy = cstr_copy("tamer", 3);
    CuAssertIntEquals(c, 3, strlen(copy));
}

void TestSplitStringBySpaces(CuTest *c)
{
    size_t count = 0;
    char **tokens = NULL;
    CuAssertTrue(c, cstr_split("this is a sentence", " ", &tokens, &count));

    CuAssertIntEquals(c, 4, count); 
    CuAssertStrEquals(c, "this", tokens[0]);
    CuAssertStrEquals(c, "is", tokens[1]);
    CuAssertStrEquals(c, "a", tokens[2]);
    CuAssertStrEquals(c, "sentence", tokens[3]);

    for (size_t i = 0; i < count; ++i) {
        free(tokens[i]);
    }
    free(tokens);
}

void TestSplitStringUsingStringNotExisting(CuTest *c)
{
    size_t count = 0;
    char **tokens = NULL;
    CuAssertTrue(c, cstr_split("this is a sentence", "xyz", &tokens, &count));

    CuAssertIntEquals(c, 0, count); 
    CuAssertPtrEquals(c, NULL, tokens);
}

void TestSplitStringByContainingCharacter(CuTest *c)
{
    size_t count = 0;
    char **tokens = NULL;
    CuAssertTrue(c, cstr_split("cstring", "t", &tokens, &count));

    CuAssertIntEquals(c, 2, count); 
    CuAssertStrEquals(c, "cs", tokens[0]);
    CuAssertStrEquals(c, "ring", tokens[1]);

    for (size_t i = 0; i < count; ++i) {
        free(tokens[i]);
    }
    free(tokens);
}

void TestSplitStringByNonContainingCharacter(CuTest *c)
{
    size_t count = 0;
    char **tokens = NULL;
    CuAssertTrue(c, cstr_split("cstring", "x", &tokens, &count));

    CuAssertIntEquals(c, 0, count); 
    CuAssertPtrEquals(c, NULL, tokens);
}

void TestSplitStringByItself_ShouldReturnArrayOf1String(CuTest *c)
{
    size_t count = 0;
    char **tokens = NULL;
    CuAssertTrue(c, cstr_split("cstring", "cstring", &tokens, &count));

    CuAssertIntEquals(c, 1, count); 
    CuAssertStrEquals(c, "cstring", tokens[0]);
    
    for (size_t i = 0; i < count; ++i) {
        free(tokens[i]);
    }
    free(tokens);
}

void TestRemoveCharExistingInString(CuTest *c)
{
    char test[] = "test";
    CuAssertIntEquals(c, 2, cstr_remove_char(test, 't'));
    CuAssertStrEquals(c, "es", test);
}

void TestRemoveCharNotExistingInString(CuTest *c)
{
    char test[] = "cheese";
    CuAssertIntEquals(c, 0, cstr_remove_char(test, 't'));
    CuAssertStrEquals(c, "cheese", test);
}

void TestRemoveCharFromEmptyString(CuTest *c)
{
    char test[] = "";
    CuAssertIntEquals(c, 0, cstr_remove_char(test, 't'));
    CuAssertStrEquals(c, "", test);
}

void TestRemoveCharFromSingleCharString_ShouldBeEmpty(CuTest *c)
{
    char test[] = "t";
    CuAssertIntEquals(c, 1, cstr_remove_char(test, 't'));
    CuAssertStrEquals(c, "", test);
}

void TestReplaceCharacterExistingInString(CuTest *c)
{
    char test[] = "abc";
    CuAssertIntEquals(c, 1, cstr_replace_char(test, 'a', 'x'));
    
    CuAssertStrEquals(c, "xbc", test);
}

void TestReplaceCharacterNotExistingInString(CuTest *c)
{
    char test[] = "abc";
    CuAssertIntEquals(c, 0, cstr_replace_char(test, 'u', 'r'));
    
    CuAssertStrEquals(c, "abc", test);
}

void TestReplaceExistingCharacterWithItself(CuTest *c)
{
    char test[] = "abc";
    CuAssertIntEquals(c, 0, cstr_replace_char(test, 'a', 'a'));
    
    CuAssertStrEquals(c, "abc", test);
}

void TestReplaceNonExistingCharacterWithItself(CuTest *c)
{
    char test[] = "abc";
    CuAssertIntEquals(c, 0, cstr_replace_char(test, 'x', 'x'));
    
    CuAssertStrEquals(c, "abc", test);
}

void TestRemoveExistingString(CuTest *c)
{
    char test[] = "this is a test";
    CuAssertIntEquals(c, 1, cstr_remove_str(test, "test"));
    CuAssertStrEquals(c, "this is a ", test);
}

void TestRemoveNonExistingString(CuTest *c)
{
    char test[] = "this is a test";
    CuAssertIntEquals(c, 0, cstr_remove_str(test, "xyz"));
    CuAssertStrEquals(c, "this is a test", test);
}

void TestRemoveEmptyString_ShouldReturnUnmodifiedString(CuTest *c)
{
    char test[] = "this is a test";
    CuAssertIntEquals(c, 0, cstr_remove_str(test, ""));
    CuAssertStrEquals(c, "this is a test", test);
}

void TestRemoveSameString_ShouldReturnEmptyString(CuTest *c)
{
    char test[] = "this is a test";
    CuAssertIntEquals(c, 1, cstr_remove_str(test, "this is a test"));
    CuAssertStrEquals(c, "", test);
}

void TestRemoveStringLongerThanBase_ShouldReturnUnmodifiedString(CuTest *c)
{
    char test[] = "this is a test";
    CuAssertIntEquals(c, 0, cstr_remove_str(test, "this is a test 2"));
    CuAssertStrEquals(c, "this is a test", test);
}

void TestRemoveSameInMemoryString_ShouldReturnEmptyString(CuTest *c)
{
    char test[] = "this is a test";
    CuAssertIntEquals(c, 0, cstr_remove_str(test, test));
    CuAssertStrEquals(c, "", test);
}
