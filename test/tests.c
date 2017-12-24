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
