#include "cstring.h"
#include "CuTest.h"
#include <string.h>

void TestAppendEntireStringNoHint(CuTest *c)
{
    const char *str = "testing";
    size_t len1 = strlen(str);
    const char *other = "tamer";
    size_t len2 = strlen(other);

    char *buf = cstralloc(len1 + len2);
    size_t appended = cstrapp(buf, other, 0, 0);

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

    char *buf = cstralloc(len1 + len2);
    size_t appended = cstrapp(buf, other, 2, 0);

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

    char *buf = cstralloc(len1 + len2);
    strcpy(buf, str);
    size_t appended = cstrapp(buf, other, 0, len1);

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

    char *buf = cstralloc(len1 + len2);
    strcpy(buf, str);
    size_t appended = cstrapp(buf, other, 3, len1);

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

    char *buf = cstralloc(len1 + len2);
    strcpy(buf, str);
    size_t appended = cstrapp(buf, other, 10, len1);

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
