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

void TestRemoveExistingStringInTheMiddle(CuTest *c)
{
    char test[] = "this is a big test.";
    CuAssertIntEquals(c, 1, cstr_remove_str(test, "big"));
    CuAssertStrEquals(c, "this is a  test.", test);
}

void TestRemoveExistingStringInTheBeginning(CuTest *c)
{
    char test[] = "this is a big test.";
    CuAssertIntEquals(c, 1, cstr_remove_str(test, "this"));
    CuAssertStrEquals(c, " is a big test.", test);
}

void TestRemoveMultipleStrings(CuTest *c)
{
    char test[] = "this is a big big test.";
    CuAssertIntEquals(c, 2, cstr_remove_str(test, "big"));
    CuAssertStrEquals(c, "this is a   test.", test);
}

void TestReplaceExistingStringWithEqualStringLengths(CuTest *c)
{
    char test[] = "this is a test";
    CuAssertIntEquals(c, 1, cstr_replace_str(test, "test", "mess"));
    CuAssertStrEquals(c, "this is a mess", test);
}

void TestReplaceExistingStringWithPatternShorterThanReplacement(CuTest *c)
{
    char test[] = "this is a test";
    CuAssertIntEquals(c, 1, cstr_replace_str(test, "this", "cat"));
    CuAssertStrEquals(c, "cat is a test", test);
}

void TestReplaceExistingStringWithPatternShorterThanReplacement2(CuTest *c)
{
    char test[] = "this is a test";
    CuAssertIntEquals(c, 1, cstr_replace_str(test, "test", "cat"));
    CuAssertStrEquals(c, "this is a cat", test);
}

void TestReplaceExistingStringWithPatternShorterThanReplacement3(CuTest *c)
{
    char test[] = "this is a gigantic test";
    CuAssertIntEquals(c, 1, cstr_replace_str(test, "gigantic", "huge"));
    CuAssertStrEquals(c, "this is a huge test", test);
}

void TestReplaceExistingStringWithPatternLongerThanReplacementInMiddle(CuTest *c)
{
    char test[] = "this is a big test.";
    CuAssertIntEquals(c, 1, cstr_replace_str(test, "big", "huge"));
    CuAssertStrEquals(c, "this is a huge test.", test);
}

void TestReplaceExistingStringWithPatternLongerThanReplacementAtEnd(CuTest *c)
{
    char test[] = "this is a big test..";
    CuAssertIntEquals(c, 1, cstr_replace_str(test, "test", "abcde"));
    CuAssertStrEquals(c, "this is a big abcde..", test);
}

void TestReplaceExistingStringWithPatternLongerThanReplacementAtBeginning(CuTest *c)
{
    char test[] = "this is a big test..";
    CuAssertIntEquals(c, 1, cstr_replace_str(test, "this", "thank"));
    CuAssertStrEquals(c, "thank is a big test..", test);
}

void TestReplaceExistingStringWithEmptyString_ShouldRemoveString(CuTest *c)
{
    char test[] = "this is a big test.";
    CuAssertIntEquals(c, 1, cstr_replace_str(test, "big", ""));
    CuAssertStrEquals(c, "this is a  test.", test);
}

void TestReplaceUsingEmptyString_ShouldNotModifyString(CuTest *c)
{
    char test[] = "this is a test.";
    CuAssertIntEquals(c, 0, cstr_replace_str(test, "", "def"));
    CuAssertStrEquals(c, "this is a test.", test);
}

void TestReplaceUsingEmptyBaseString_ShouldNotHaveReplacements(CuTest *c)
{
    char test[] = "";
    CuAssertIntEquals(c, 0, cstr_replace_str(test, "abc", "def"));
    CuAssertStrEquals(c, "", test);
}

void TestMultipleReplacements(CuTest *c)
{
    char test[] = "this is a big big change....";
    CuAssertIntEquals(c, 2, cstr_replace_str(test, "big", "great"));
    CuAssertStrEquals(c, "this is a great great change....", test);
}

void TestTrimLeadingSpacesFromString(CuTest *c)
{
    char test[] = "    this is a test.";
    cstr_trim(test);
    CuAssertStrEquals(c, "this is a test.", test);
}

void TestTrimTrailingSpacesFromString(CuTest *c)
{
    char test[] = "this is a test.      ";
    cstr_trim(test);
    CuAssertStrEquals(c, "this is a test.", test);
} 

void TestTrimLeadingAndTrailingSpacesFromString(CuTest *c)
{
    char test[] = "    this is a test.      ";
    cstr_trim(test);
    CuAssertStrEquals(c, "this is a test.", test);
} 

void TestTrimSpacesFromEmptyString(CuTest *c)
{
    char test[] = "";
    cstr_trim(test);
    CuAssertStrEquals(c, "", test);
}

void TestTrimSpacesFromStringThatDoesntNeedTrimming(CuTest *c)
{
    char test[] = "no trimming necessary.";
    cstr_trim(test);
    CuAssertStrEquals(c, "no trimming necessary.", test);
}

void TestSortStringAscendingNoDuplicates(CuTest *c)
{
    char test[] = "cstring";
    cstr_sort(test, 0);
    CuAssertStrEquals(c, "cginrst", test);
}

void TestSortStringDescendingNoDuplicates(CuTest *c)
{
    char test[] = "cstring";
    cstr_sort(test, 1);
    CuAssertStrEquals(c, "tsrnigc", test);
}

void TestSortStringAscendingWithDuplicates(CuTest *c)
{
    char test[] = "dddcccbbbaaa";
    cstr_sort(test, 0);
    CuAssertStrEquals(c, "aaabbbcccddd", test);
}

void TestSortStringDescendingWithDuplicates(CuTest *c)
{
    char test[] = "aaabbbcccddd";
    cstr_sort(test, 1);
    CuAssertStrEquals(c, "dddcccbbbaaa", test);
}

void TestSortEmptyStringAscending(CuTest *c)
{
    char test[] = "";
    cstr_sort(test, 0);
    CuAssertStrEquals(c, "", test);
}

void TestSortEmptyStringDescending(CuTest *c)
{
    char test[] = "";
    cstr_sort(test, 1);
    CuAssertStrEquals(c, "", test);
}
