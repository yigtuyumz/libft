#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <strings.h>
#include <time.h>
#include <fcntl.h>
#include <ctype.h>
#include <limits.h>
#include <stdarg.h>

// dprintf writes to a file descriptor, not FILE stream.
#define _log(fildes, fmt, ...) (void) dprintf(fildes, "[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define _u __attribute__((unused))
#define SIGN_BIT(val, dtype) (((dtype) (val)) >> ((sizeof(dtype) * 8) - 1))

#include "../libft.h"

// NOLINTBEGIN clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling

int errfile;

// fill n bytes of s with random values
void random_bufferfill(void *s, size_t n)
{
	int fd = open("/dev/random", O_RDONLY);

	if (fd < 0) {
		fprintf(stderr, "random_bufferfill\t[FAIL] Opening device /dev/random\n");
		exit(EXIT_FAILURE);
	}

	ssize_t readval = read(fd, s, n);
	if (readval != (ssize_t) n) {
		fprintf(stderr, "random_bufferfill\t[FAIL] Failed to read %lu byted from /dev/random\n", n);
		close(fd);
		exit(EXIT_FAILURE);
	}

	close(fd);
}


void open_errlog(const char *file_path)
{
	errfile = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (errfile < 0) {
		fprintf(stderr, "[FAIL] trying to open %s for logging.", file_path);
		exit(EXIT_FAILURE);
	}

}

void close_errlog(void)
{
	if (close(errfile) < 0) {
		fprintf(stderr, "[FAIL] trying to close log file! fildes: %d.\n", errfile);
		exit(EXIT_FAILURE);
	}
}

void append_errlog(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vdprintf(errfile, fmt, args);
    va_end(args);
}


void assert_memcmp(const void *s1, const void *s2, size_t n, const char *desc)
{
	int std_result = memcmp(s1, s2, n);
	int ft_result = ft_memcmp(s1, s2, n);

	if (SIGN_BIT(std_result, int) == SIGN_BIT(ft_result, int))
		printf("ft_memcmp\t[PASS] %s\n", desc);
	else
		append_errlog("ft_memcmp\t[FAIL] %s\n  memcmp: %d, ft_memcmp: %d\n", desc, std_result, ft_result);
}

void assert_memchr(const void *s, int c, size_t n, const char *desc)
{
	void *std_result = memchr(s, c, n);
	void *ft_result = ft_memchr(s, c, n);
	if (std_result == ft_result)
		printf("ft_memchr\t[PASS] %s\n", desc);
	else
		append_errlog("ft_memchr\t[FAIL] %s\n  memchr: %p, ft_memchr: %p\n", desc, std_result, ft_result);
}

void assert_strncmp(const char *s1, const char *s2, size_t n, const char *desc)
{
	int std_result = strncmp(s1, s2, n);
	int ft_result = ft_strncmp(s1, s2, n);
	if (std_result == ft_result)
		printf("ft_strncmp\t[PASS] %s\n", desc);
	else
		append_errlog("ft_strncmp\t[FAIL] %s\n  strncmp: %d, ft_strncmp: %d\n", desc, std_result, ft_result);
}

void assert_strrchr(const char *s, int c, const char *desc) {
	char *std_result = strrchr(s, c);
	char *ft_result = ft_strrchr(s, c);
	if (std_result == ft_result)
		printf("ft_strrchr\t[PASS] %s\n", desc);
	else
		append_errlog("ft_strrchr\t[FAIL] %s\n  strrchr: %p, ft_strrchr: %p\n", desc, std_result, ft_result);
}

void assert_atoi(const char *s, const char *desc)
{
	int std_result = atoi(s);
	int ft_result = ft_atoi(s);
	if (std_result == ft_result)
		printf("ft_atoi\t\t[PASS] %s\n", desc);
	else
		append_errlog("ft_atoi\t\t[FAIL] %s\n  atoi: %d, ft_atoi: %d\n", desc, std_result, ft_result);
}

// NOLINTBEGIN clang-analyzer-security.insecureAPI.bzero
void assert_bzero(void *s1, void *s2, size_t n, const char *desc)
{
	random_bufferfill(s1, n);
	random_bufferfill(s2, n);
	bzero(s1, n);
	ft_bzero(s2, n);
	int result = memcmp(s1, s2, n);
	if (result == 0)
		printf("ft_bzero\t[PASS] %s\n", desc);
	else
		append_errlog("ft_bzero\t[FAIL] %s\n  result: %d differs at: %lu\n", desc, result, n);
}
// NOLINTEND clang-analyzer-security.insecureAPI.bzero

void assert_tolower(int c, const char *desc)
{
	int c1 = c;
	int c2 = c;
	int std_result = tolower(c);
	int ft_result = ft_tolower(c1);

	if (std_result == ft_result)
		printf("ft_tolower\t[PASS] %s\n", desc);
	else
		append_errlog("ft_tolower\t[FAIL] %s\n  given: %d result: %d expected: %d\n", desc, c2, ft_result, std_result);
}

void assert_toupper(int c, const char *desc)
{
	int c1 = c;
	int c2 = c;
	int std_result = toupper(c);
	int ft_result = ft_toupper(c1);

	if (std_result == ft_result)
		printf("ft_toupper\t[PASS] %s\n", desc);
	else
		append_errlog("ft_toupper\t[FAIL] %s\n  given: %d result: %d expected: %d\n", desc, c2, ft_result, std_result);
}

void assert_memcpy(void *buff1, void *buff2, size_t n, const char *desc)
{
	char buff[n];
	random_bufferfill(buff, n);
	void *std_result = memcpy(buff1, buff, n);
	void *ft_result = ft_memcpy(buff2, buff, n);

	int result = memcmp(std_result, ft_result, n);
	if (result == 0 && ft_result == buff2)
		printf("ft_memcpy\t[PASS] returns: %p %s\n", ft_result, desc);
	else
		append_errlog("ft_memcpy\t[FAIL] %s\n  returns: %p result: %d\n", desc, ft_result, result);

}

void assert_memset(void *buff, int val, size_t n, const char *desc)
{
	char buff1[n];
	void *std_result = memset(buff1, val, n);
	void *ft_result = ft_memset(buff, val, n);

	int result = memcmp(std_result, ft_result, n);
	if (result == 0 && ft_result == buff)
		printf("ft_memset\t[PASS] returns: %p %s\n", ft_result, desc);
	else
		append_errlog("ft_memset\t[FAIL] %s\n  returns: %p result: %d\n", desc, ft_result, result);

}

void assert_strchr(const char *str, int val, const char *desc)
{
	char *std_result = strchr(str, val);
	char *ft_result = ft_strchr(str, val);

	if (std_result == NULL && ft_result == NULL)
		printf("ft_strchr\t[PASS] returns: NULL %s\n", desc);
	else if (std_result == NULL || ft_result == NULL)
		append_errlog("ft_strchr\t[FAIL] %s\n  One is NULL: ft=%p, std=%p\n", desc, ft_result, std_result);
	else if (ft_result == std_result)
		printf("ft_strchr\t[PASS] returns: %p index: %ld %s\n", ft_result, (long)(ft_result - str), desc);
	else
		append_errlog("ft_strchr\t[FAIL] %s\n  returns: %p expected: %p\n", desc, ft_result, std_result);
}

void assert_isprint(int val, const char *desc)
{
	int std_val = isprint(val);
	int ft_val = ft_isprint(val);

	if (std_val == ft_val)
		printf("ft_isprint\t[PASS] %s value: %d\n", desc, val);
	else
		append_errlog("ft_isprint\t[FAIL] %s\n  value: %d returns: %d expected: %d\n", desc, val, ft_val, std_val);
}

void assert_isalnum(int val, const char *desc)
{
	int std_val = isalnum(val);
	int ft_val = ft_isalnum(val);

	if (std_val == ft_val)
		printf("ft_isalnum\t[PASS] %s value: %d\n", desc, val);
	else
		append_errlog("ft_isalnum\t[FAIL] %s\n  value: %d returns: %d expected: %d\n", desc, val, ft_val, std_val);
}

void assert_isdigit(int val, const char *desc)
{
	int std_val = isdigit(val);
	int ft_val = ft_isdigit(val);

	if (std_val == ft_val)
		printf("ft_isdigit\t[PASS] %s value: %d\n", desc, val);
	else
		append_errlog("ft_isdigit\t[FAIL] %s\n  value: %d returns: %d expected: %d\n", desc, val, ft_val, std_val);
}

void assert_isalpha(int val, const char *desc)
{
	int std_result = isupper(val) || islower(val);
	int ft_result = ft_isalpha(val);

	if (ft_result == std_result)
		printf("ft_isalpha\t[PASS] %s value: %d\n", desc, val);
	else
		append_errlog("ft_isalpha[FAIL] %s\n  value: %016lX returns: %d expected: %d\n", desc, (unsigned long) val, ft_result, std_result);
}

void assert_strdup(const char *val, const char *desc)
{
	char *std_result = strdup(val);
	char *ft_result = ft_strdup(val);

	int result = strcmp((const char *) ft_result, (const char *) std_result);

	if (result == 0)
		printf("ft_strdup\t[PASS] %s\n", desc);
	else
		append_errlog("ft_strdup\t[FAIL] %s\n  strdup: \"%s\", ft_strdup: \"%s\"\n", desc, std_result, ft_result);

	free(std_result);
	free(ft_result);
}

/*
 * ******************* *
 */

void strdup_tester(void)
{
	assert_strdup("", "Empty string");
	assert_strdup("Hello, world!", "Normal string");
	assert_strdup("1234567890", "Numeric string");
	assert_strdup("Line1\nLine2", "String with newline");
	assert_strdup("  leading and trailing  ", "String with spaces");
	assert_strdup("!@#$\\%^&*()", "String with symbols");
	assert_strdup("", "Empty string");
	assert_strdup("a", "Single char");
	assert_strdup("abc", "Short string");
	assert_strdup("Hello, world!", "Normal string");
	assert_strdup("1234567890", "Numeric string");
	assert_strdup("Line1\nLine2", "String with newline");
	assert_strdup("  leading and trailing  ", "String with spaces");
	assert_strdup("!@#$%^&*()", "String with symbols");
	assert_strdup("😊", "Unicode emoji");
	assert_strdup("日本語の文字列", "Unicode Japanese");
	assert_strdup("This is a very very very long string to test strdup functionality over long inputs", "Long string");
	assert_strdup("Tab\tseparated\twords", "String with tabs");
	assert_strdup("Null\0char", "String with embedded null");
	assert_strdup("Mixed1234string5678with90numbers", "Mixed alphanumeric");
	assert_strdup("UPPERCASE", "Uppercase string");
	assert_strdup("lowercase", "Lowercase string");
	assert_strdup("MiXeD CaSe", "Mixed case string");
	assert_strdup("     ", "Only spaces");
	assert_strdup("\n\r\t", "Only control characters");
	assert_strdup("C-style\\nnewline", "String with escape sequences");
	assert_strdup("End with null\0", "Ends with null char");
	assert_strdup("Special chars: ~`<>?", "Special characters");
	assert_strdup("RepeatRepeatRepeatRepeatRepeat", "Repeated substring");
	assert_strdup("A", "Single uppercase");
	assert_strdup("z", "Single lowercase");
	assert_strdup("0", "Single digit");
	assert_strdup(" ", "Single space");
	assert_strdup("!@#$%^&*()_+", "Symbols");
	assert_strdup("😊😊😊😊😊", "Repeated emoji");
	assert_strdup("a\0b\0c", "Multiple null bytes");
	assert_strdup("Normal sentence with punctuation.", "Sentence with punctuation");
	assert_strdup("123 456 789", "Numbers with spaces");
	assert_strdup("Tab\tand\nNewline", "Tabs and newlines");
	assert_strdup("中文字符", "Chinese characters");
	assert_strdup("Русские буквы", "Cyrillic letters");
	assert_strdup("한국어 문자열", "Korean characters");
	assert_strdup("🌍🚀✨", "Multiple emojis");
	assert_strdup("Line1\nLine2\nLine3", "Multiple lines");
	assert_strdup("Ends with space ", "Ends with space");
	assert_strdup("  Starts with space", "Starts with space");
	assert_strdup("Middle   spaces", "Multiple spaces in middle");
	assert_strdup("Tabs\tin\tmiddle", "Tabs in middle");
	assert_strdup("1234567890abcdef", "Hex digits");
	assert_strdup("Special \x7F char", "DEL char");
	assert_strdup("Embedded\0null", "Embedded null char");
	assert_strdup("Empty\0\0\0", "Multiple embedded nulls");
	assert_strdup("😊Mixed ASCII and emoji😊", "Mixed ASCII and emoji");
	assert_strdup("New\nline and tab\t", "New line and tab");
}

void isalpha_tester(void)
{
	for (int i = 'a'; i <= 'z'; i++)
		assert_isalpha(i, "Lowercase letters");
	for (int i = 'A'; i <= 'Z'; i++)
		assert_isalpha(i, "Uppercase letters");
	for (int i = -128; i <= 127; i++) {
		if (isprint(i))
			assert_isalpha(i, "Printable ASCII characters.");
		else
			assert_isalpha(i, "non-printable ASCII characters.");
	}

}

void isdigit_tester(void)
{
	for (int i = -128; i <= 127; i++) {
		if (isprint(i)) {
			assert_isdigit(i, "Printable ASCII characters.");
		} else {
			assert_isdigit(i, "Non-printable ASCII characters.");
		}
	}
}

void isalnum_tester(void)
{
	for (int i = -128; i <= 127; i++) {
		if (isprint(i)) {
			assert_isdigit(i, "Printable ASCII characters.");
		} else {
			assert_isdigit(i, "Non-printable ASCII characters.");
		}
	}
}

void isprint_tester(void)
{
	for (int i = -128; i <= 127; i++)
		assert_isprint(i, "ASCII Character set.");
}

void strchr_tester(void)
{
	char buff[2048];

	memcpy(buff, "this is a buffer!\n", 19);
	assert_strchr(buff, 'f', "Find first 'f' in string.");

	ft_memset(buff, 0, 2048);
	random_bufferfill(buff, 2047);
	buff[2047] = 0;
	assert_strchr(buff, 0, "Find first 0.");

	buff[0] = '\0';
	assert_strchr(buff, 'a', "Empty string, search for 'a'.");
	assert_strchr(buff, '\0', "Empty string, search for null terminator");

	buff[0] = 'x';
	buff[1] = '\0';
	assert_strchr(buff, 'x', "Single character string, match");
	assert_strchr(buff, 'y', "Single character string, no match");
	assert_strchr(buff, '\0', "Single character string, match null terminator");
 
	strcpy(buff, "abacacv djrel gcdh s  djdgvbns    \n\n\n\n\n\n\\\\\\\\\\\\jd");
	assert_strchr(buff, 'a', "Multiple 'a' characters, should find first");
	assert_strchr(buff, 'd', "Last character match");
	assert_strchr(buff, 'z', "Character not in string");

	memset(buff, 'A', 1024);
	buff[1024] = 0;
	assert_strchr(buff, 'A', "All same character, should return index 0");

	memset(buff, '\0', 2048);
	assert_strchr(buff, '\0', "Null-byte filled buffer");

	memset(buff, '.', 2047);
	buff[2047] = '\0';
	buff[2046] = 'Z';
	assert_strchr(buff, 'Z', "Match at very end of large buffer");

	strcpy(buff, "xyz");
	assert_strchr(buff, 'x', "Match at first index");

	strcpy(buff, "abcde");
	assert_strchr(buff, 'c', "Match in middle");

	buff[0] = -1; buff[1] = '\0';
	assert_strchr(buff, 255, "Signed char -1 (interpreted as 255)");

	buff[0] = 200; buff[1] = 201; buff[2] = 0;
	assert_strchr(buff, 200, "High ASCII match (extended char)");

	random_bufferfill(buff, 2048);
	buff[0] = '!';
	buff[2047] = 0;
	assert_strchr(buff, '!', "First character match in random buffer");

	strcpy(buff, "abgggasc\0defashewr");
	assert_strchr(buff, 'c', "Match before null terminator");
	assert_strchr(buff, 'd', "No match after null terminator (should fail)");

	strcpy(buff, "awewetwetwetetgbcdef");
	assert_strchr(buff, 128, "Out of ASCII range, no match");

	buff[0] = '\0'; buff[1] = '\0'; buff[2] = '\0';
	assert_strchr(buff, '\0', "Multiple nulls, should return first one");
}

void memset_tester(void)
{
	char buff[2048];

	assert_memset((void *) buff, 'a', 2048, "Fill buffer with an ASCII character");

	assert_memset((void *) buff + 1000, 0, 1000, "Write 0 with offset");

	assert_memset((void *) buff, 12312, 2048, "Write bigger than 1 byte value");
}

void memcpy_tester(void)
{
	char buff1[4096];
	char buff2[4096];

	assert_memcpy(buff1, buff2, 0, "Zero-length copy");
	assert_memcpy(buff1, buff2, 1, "Single byte copy");
	assert_memcpy(buff1 + 1, buff2 + 1, 1, "Single byte copy at offset");
	assert_memcpy(buff1, buff2, 16, "Small aligned copy");
	assert_memcpy(buff1 + 3, buff2 + 3, 16, "Small unaligned copy");

	assert_memcpy(buff1, buff2, 255, "255 byte copy");
	assert_memcpy(buff1 + 5, buff2 + 5, 256, "Unaligned 256 byte copy");
	assert_memcpy(buff1, buff2, 512, "512 byte aligned copy");
	assert_memcpy(buff1 + 7, buff2 + 7, 512, "512 byte unaligned copy");

	assert_memcpy(buff1 + 2047, buff2 + 2047, 1, "Last byte of buffer");
	assert_memcpy(buff1 + 1023, buff2 + 1023, 1, "Middle of buffer");
	assert_memcpy(buff1, buff2, 1024, "1024 byte copy");

	assert_memcpy(buff1 + 123, buff2 + 123, 789, "Random offset and size");
	assert_memcpy(buff1 + 4095, buff2 + 4095, 1, "Final byte only");

	for (size_t i = 1; i <= 128; i *= 2)
		assert_memcpy(buff1 + 100, buff2 + 100, i, "Exponential size test");

	for (size_t i = 0; i < 32; ++i)
		assert_memcpy(buff1 + i, buff2 + i, 64, "Unaligned start 0-31");

	for (size_t i = 1; i <= 64; i++)
		assert_memcpy(buff1 + 500, buff2 + 500, i, "Length sweep 1-64");

	assert_memcpy(buff1 + 256, buff2 + 256, 768, "Large middle copy");
	assert_memcpy(buff1, buff2, 2048, "Full 2048 byte copy");
	assert_memcpy(buff1 + 2047, buff2 + 2047, 1, "Last byte (edge)");

	for (int i = 0; i < 10; ++i) {
		size_t offset = rand() % 2000;
		size_t len = rand() % (2048 - offset);
		assert_memcpy(buff1 + offset, buff2 + offset, len, "Random offset/length");
	}

	assert_memcpy(buff1, buff1, 100, "Same source and destination");

	for (size_t i = 0; i < 4096; i++)
		buff1[i] = (unsigned char)(i % 256);
	assert_memcpy(buff1, buff2, 4096, "Full buffer known pattern copy");

	for (size_t i = 0; i < 4096; i++)
		buff1[i] = 0xFF;
	assert_memcpy(buff1, buff2, 4096, "All 0xFF bytes");

	for (size_t i = 0; i < 4096; i++)
		buff1[i] = 0x00;
	assert_memcpy(buff1, buff2, 4096, "All 0x00 bytes");

	for (size_t i = 0; i < 4096; i++)
		buff1[i] = (i % 2) ? 0xAA : 0x55;
	assert_memcpy(buff1, buff2, 4096, "Repetitive bit pattern");

}

void toupper_tester(void)
{
	for (char c = 'A'; c <= 'Z'; c++)
		assert_toupper(c, "Uppercase letter");
	for (char c = '0'; c <= '9'; c++)
		assert_toupper(c, "Digit");
	for (char c = -128; c < 127; c++) {
		if (isprint(c)) {
			assert_toupper(c, "Printable ASCII characters only");
		}
	}
	for (char c = -128; c < 127; c++) {
		if (!isprint(c)) {
			assert_toupper(c, "Non-Printable ASCII characters only");
		}
	}

	for (int c = -1000; c <= 1000; c++)
		assert_toupper(c, "Integer values between -1000 and 1000");

	for (int c = 100000; c >= 101000; c--)
		assert_toupper(c, "Integer values between 100000 and 101000");
}

void tolower_tester(void)
{
	for (char c = 'A'; c <= 'Z'; c++)
		assert_tolower(c, "Uppercase letter");
	for (char c = '0'; c <= '9'; c++)
		assert_tolower(c, "Digit");
	for (char c = -128; c < 127; c++) {
		if (isprint(c)) {
			assert_tolower(c, "Printable ASCII characters only");
		}
	}
	for (char c = -128; c < 127; c++) {
		if (!isprint(c)) {
			assert_tolower(c, "Non-Printable ASCII characters only");
		}
	}

	for (int c = -1000; c <= 1000; c++)
		assert_tolower(c, "Integer values between -1000 and 1000");

	for (int c = 5000000; c >= 5001000; c--)
		assert_tolower(c, "Integer values between 5000000 and 5001000");
}

void atoi_tester(void)
{
	assert_atoi("-2147483648", "Minimum integer value");

	assert_atoi("2147483647", "Maximum integer value");

	assert_atoi("\n\v\t\r\r\f\f  \f   1231251", "Starts with isppace characters");

	assert_atoi("-2643768   \f  \r\t\v\n", "Ends with isppace characters");

	assert_atoi("+", "Just one plus sign");

	assert_atoi("-", "Just one minus sign");

	assert_atoi("--124152", "Multiple minus sign");

	assert_atoi("++++52", "Multiple plus sign");

	assert_atoi("2147483649", "Too big (Integer overflow)");

	assert_atoi("", "Empty string");
}

void bzero_tester(void)
{
	char buff1[1024];
	char buff2[1024];
	void *b1 = buff1;
	void *b2 = buff2;

	assert_bzero(b1, b2, sizeof(buff1), "Entire buffer (1000 bytes)");

	assert_bzero(b1, b2, sizeof(buff1) / 2, "First Half");
	assert_bzero(b1 + sizeof(buff1) / 2, b2 + sizeof(buff1) / 2, sizeof(buff1) / 2, "Second Half");

	assert_bzero(b1, b2, 0, "Zero-length");

	assert_bzero(b1 + 123, b2 + 123, 1, "Single byte");

	for (size_t offset = 0; offset < 16; ++offset)
		assert_bzero((b1 + offset), (b2 + offset), 32, "Unaligned 32 bytes");

	for (size_t len = 1; len <= 128; len *= 2)
		assert_bzero((b1 + (500 - len / 2)), (b2 + (500 - len / 2)), len, "Exponential size test");

	for (size_t len = 0; len <= 100; ++len)
		assert_bzero((b1 + 450), (b2 + 450), len, "Length sweep 0-100");

	for (int i = 0; i < 10; ++i) {
		size_t offset = rand() % 900;
		size_t length = rand() % (1000 - offset);
		assert_bzero(b1 + offset, b2 + offset, length, "Random offset and length");
	}
}

void memcmp_tester(void)
{
	char diff_then_same1[] = {'a', 'b', 'c', 'd'};
	char diff_then_same2[] = {'x', 'b', 'c', 'd'};
	assert_memcmp(diff_then_same1, diff_then_same2, 4, "First byte differs, rest same");

	assert_memcmp("abcdef", "abcxyz", 3, "First 3 bytes same, rest differs, n=3");

	assert_memcmp("A", "B", 1, "One character difference");

	assert_memcmp("abcdefghijklmnopqrstuvwxyz", "abcxefghijklmnopqrstuvwxyz", 3, "First 3 same, long strings");

	assert_memcmp("", "", 0, "Both empty, n=0");

	assert_memcmp("", "nonempty", 0, "Empty vs non-empty, n=0");

	assert_memcmp("abc", "xbc", 1, "Only first byte compared");

	unsigned char neg1[] = {(char)-1};
	unsigned char pos255[] = {255};
	assert_memcmp(neg1, pos255, 1, "-1 vs 255 as unsigned char");

	char utf1[] = "çalış";
	char utf2[] = "çalışma";
	assert_memcmp(utf1, utf2, 6, "UTF-8 multibyte prefix match");

	assert_memcmp(NULL, NULL, 0, "NULL pointers, n=0");

	char shorty[] = "abc";
	char longy[] = "abcXYZ";
	assert_memcmp(shorty, longy, 3, "Same first 3 bytes, rest ignored");

	unsigned char zeros1[] = {0x00, 0x00, 0x00};
	unsigned char zeros2[] = {0x00, 0x00, 0x01};
	assert_memcmp(zeros1, zeros2, 3, "Embedded null bytes, last differs");

	unsigned char rand1[] = {17, 34, 51, 68, 85};
	unsigned char rand2[] = {17, 34, 51, 68, 86};
	assert_memcmp(rand1, rand2, 5, "Random data, last byte off");

	unsigned char one1[] = {42};
	unsigned char one2[] = {42};
	assert_memcmp(one1, one2, 1, "1-byte data, equal");

	assert_memcmp("same", "same", 0, "Equal strings, n=0");

	assert_memcmp("abc", "abc", 3, "Same strings");

	assert_memcmp("abc", "xbc", 3, "First byte differs");
	assert_memcmp("bbc", "xbc", 3, "First byte differs");
	assert_memcmp("cbc", "xbc", 3, "First byte differs");
	assert_memcmp("dbc", "xbc", 3, "First byte differs");
	assert_memcmp("ebc", "xbc", 3, "First byte differs");

	assert_memcmp("abc", "abd", 3, "Last byte differs");

	assert_memcmp("abc", "adc", 3, "Middle byte differs");

	assert_memcmp("abc", "xyz", 0, "Zero length comparison");

	unsigned char bin1[] = {0x00, 0x01, 0x02, 0xFF};
	unsigned char bin2[] = {0x00, 0x01, 0x02, 0xFE};
	assert_memcmp(bin1, bin2, 4, "Binary data with FF vs FE");

	unsigned char bin3[] = {0x80};
	unsigned char bin4[] = {0x7F};
	assert_memcmp(bin3, bin4, 1, "128 vs 127 (unsigned)");

	char same[] = "same";
	assert_memcmp(same, same, 4, "Same memory location");

	char *big1 = calloc(10000, 1);
	char *big2 = calloc(10000, 1);
	assert_memcmp(big1, big2, 10000, "Large block equal data");

	big2[9999] = 1;
	assert_memcmp(big1, big2, 10000, "Large block last byte differs");

	free(big1);
	free(big2);

	unsigned char full1[256];
	unsigned char full2[256];
	for (int i = 0; i < 256; i++)
	{
		full1[i] = (unsigned char)i;
		full2[i] = (unsigned char)i;
	}
	assert_memcmp(full1, full2, 256, "All 0-255 bytes equal");

	full2[128] = 129;
	assert_memcmp(full1, full2, 256, "Byte 128 differs: 128 vs 129");
}

void memchr_tester(void)
{
	assert_memchr("hello", 'e', 5, "Basic match: 'e' in 'hello'");

	assert_memchr("hello", 'z', 5, "No match: 'z' not in 'hello'");

	assert_memchr("hello", 'h', 5, "First character match");

	assert_memchr("hello", 'o', 5, "Last character match");

	assert_memchr("hello", 'l', 5, "Middle character match (first of duplicates)");

	assert_memchr("hello", 'h', 0, "Zero length, should return NULL");

	assert_memchr("", 'a', 1, "Empty string, non-zero n");

	assert_memchr(NULL, 'a', 0, "NULL pointer, zero length");

	char str1[] = "abcabc";
	assert_memchr(str1, 'a', 6, "Match on first and again later, should return first");

	char str2[] = "xxxxxZ";
	assert_memchr(str2, 'Z', 6, "Only last byte matches");

	unsigned char bin1[] = {1, 2, 3, 255, 5};
	assert_memchr(bin1, 255, 5, "Match with byte 255");

	assert_memchr(bin1, -1, 5, "Match with byte -1 interpreted as 255");

	unsigned char bin2[] = {1, 0, 2, 3};
	assert_memchr(bin2, 0, 4, "Null byte in middle");

	unsigned char bin3[] = {0, 0, 0, 0};
	assert_memchr(bin3, 'x', 4, "Only null bytes, char not present");

	char str3[] = "abc";
	assert_memchr(str3, 'a', 1, "First byte match, limited n");

	char str4[] = "banana";
	assert_memchr(str4, 'a', 6, "Multiple matches, return first");

	unsigned char rand1[] = {42, 77, 123, 200, 88};
	assert_memchr(rand1, 123, 5, "Random data, match in middle");

	assert_memchr(rand1, 1, 5, "Random data, no match");

	unsigned char full[256];
	for (int i = 0; i < 256; i++)
		full[i] = (unsigned char)i;
	for (int i = 0; i < 256; i++)
	{
		char desc[64];
		snprintf(desc, sizeof(desc), "Full byte test: find %d", i);
		assert_memchr(full, i, 256, desc);
	}

	assert_memchr(full, 255, 100, "Char 255 not in first 100 bytes");
}

void strncmp_tester(void)
{
	assert_strncmp("abc", "abc", 3, "Same strings, same length");

	assert_strncmp("xbc", "abc", 3, "First character differs");

	assert_strncmp("axc", "abc", 3, "Middle character differs");

	assert_strncmp("aba", "abc", 3, "Last character differs");

	assert_strncmp("abcdef", "abc", 3, "Same first 3, s1 longer");

	assert_strncmp("abc", "abcdef", 3, "Same first 3, s2 longer");

	assert_strncmp("abcdef", "abcxyz", 6, "Match first 3, compare till 6");

	assert_strncmp("abc", "def", 0, "n = 0, should return 0");

	assert_strncmp("", "", 1, "Empty strings");

	assert_strncmp("", "abc", 1, "Empty vs non-empty");

	assert_strncmp("abc", "", 1, "Non-empty vs empty");

	assert_strncmp("çalış", "çalıs", 5, "UTF-8, i vs ı");

	assert_strncmp("ı", "ı", 5, "Only ı");

	assert_strncmp("abcdef", "abcxyz", 3, "Same prefix, n = 3");

	assert_strncmp("abc", "abc\0xyz", 6, "Null terminator should stop comparison");

	assert_strncmp("a", "a", 1, "One char equal");

	assert_strncmp("a", "b", 1, "One char different");

	assert_strncmp("\0abc", "\0abc", 4, "First char is null");

	assert_strncmp("\0abc", "\0xyz", 4, "Both start with null, ignore rest");

	char s1[] = {(char)200, 0};
	char s2[] = {(char)150, 0};
	assert_strncmp(s1, s2, 1, "Signed char comparison");

	assert_strncmp("xyz", "abc", 3, "Completely different strings");

	assert_strncmp("zbcdefgh", "abcdefgh", 100, "First character differs, large n");

	assert_strncmp("abc", "abcdef", 6, "Short string vs long string");

	char long1[] = "this is a very long test string with lots of characters";
	char long2[] = "this is a very long test string with lots of characters";
	assert_strncmp(long1, long2, 100, "Very long same strings");

	char long3[] = "this is a very long test string with lots of characterx";
	assert_strncmp(long1, long3, 100, "Very long strings, last character differs");

	assert_strncmp("abc", "abcdef", 10, "s1 shorter than s2, n large");

	assert_strncmp("abcdef", "abc", 10, "s2 shorter than s1, n large");

	char nul1[] = {'a', 'b', '\0', 'x', 'y'};
	char nul2[] = {'a', 'b', '\0', 'z', 'w'};
	assert_strncmp(nul1, nul2, 5, "Same with embedded nulls");

	assert_strncmp("a\0x", "a\0y", 1, "Only compare first byte with null present");
}

void strrchr_tester(void)
{
	assert_strrchr("hello", 'e', "Single occurrence of 'e'");

	assert_strrchr("hello", 'z', "Character not present");

	assert_strrchr("banana", 'a', "Multiple 'a', should return last");

	assert_strrchr("abcabcabc", 'a', "Multiple 'a', including first");

	assert_strrchr("helloo", 'o', "Match at end");

	assert_strrchr("hello", '\0', "Searching for null terminator");

	assert_strrchr("", '\0', "Empty string, searching null terminator");

	assert_strrchr("", 'x', "Empty string, character not present");

	assert_strrchr("xabcx", 'x', "Match at start and end, return end");

	assert_strrchr("a", 'a', "Single character, matches");

	assert_strrchr("a", 'b', "Single character, no match");

	assert_strrchr("çalış", "ş"[0], "UTF-8 character match");

	assert_strrchr("aaaaa", 'a', "All same characters");

	assert_strrchr("hellox", 'x', "Match at last index");

	char test15[] = {'a', 'b', '\0', 'c', 'b', '\0'};
	assert_strrchr(test15, 'b', "Embedded null: should return index 1");

	assert_strrchr("abcdef", 'c', "Match in middle, normal termination");

	assert_strrchr("abc\0def", '\0', "Embedded null terminator match");

	assert_strrchr("abc", -1, "Negative int as char");

	char test19[] = {1, 2, 3, 255, 4, 255, 0};
	assert_strrchr(test19, 255, "Char 255, multiple times");

	char longstr[] = "x........................................................................................................";
	assert_strrchr(longstr, 'x', "Long string, only start match");

	longstr[0] = '.'; longstr[99] = 'z'; longstr[100] = '\0';
	assert_strrchr(longstr, 'z', "Long string, match at end");

	assert_strrchr("abcabcabcabcabc", 'b', "Last 'b' in repeating pattern");

	char nulls[] = {'\0', '\0', '\0', '\0', '\0'};
	assert_strrchr(nulls, '\0', "All null characters");

	assert_strrchr("xyz", '\0', "String ends, no match but null terminator");

	assert_strrchr("apple", 'a', "First character only match");

	char negchars[] = { -128, -127, -1, 0 };
	assert_strrchr(negchars, -1, "Negative character value (-1)");
	assert_strrchr(negchars, 127, "127 not found in negative array");

	char full_ascii[257];
	for (int i = 0; i < 256; ++i)
		full_ascii[i] = (char)i;
	full_ascii[256] = '\0';
	assert_strrchr(full_ascii, 255, "Char 255 in full byte range");
	assert_strrchr(full_ascii, 0, "Null terminator at end");

	char huge[10001];
	memset(huge, 'a', 10000);
	huge[10000] = '\0';
	assert_strrchr(huge, 'a', "Very long string of 'a's");

	huge[9999] = 'b';
	assert_strrchr(huge, 'b', "Very long string ending with unique match");

	const char *utf8_misalign = "eğğğ";
	assert_strrchr(utf8_misalign, (unsigned char)"ğ"[1], "UTF-8 trailing byte");

	char partial_nulls[] = {'x', 'y', 'z', 'x', 'y', 'z'};
	assert_strrchr(partial_nulls, 'z', "No null terminator in segment (undefined behavior)");

	assert_strrchr("", 300, "Empty string with high out-of-range int");

	char post_null[] = {'a', 'b', '\0', 'c', 'd', '\0'};
	assert_strrchr(post_null, 'd', "Invisible character after null (undefined)");

	char mega_same[1001];
	memset(mega_same, 'x', 1000);
	mega_same[1000] = '\0';
	assert_strrchr(mega_same, 'x', "All same 1000 characters");

	char unique_start[] = "x........................................................................................................";
	assert_strrchr(unique_start, 'x', "Only start character is match");

	unique_start[0] = '.'; unique_start[99] = 'z'; unique_start[100] = '\0';
	assert_strrchr(unique_start, 'z', "Match at last position");

	assert_strrchr("abc", 1000, "Very high int (outside unsigned char)");

	char null_in_middle[] = { 'a', '\0', 'b', '\0', 0 };
	assert_strrchr(null_in_middle, '\0', "Multiple embedded nulls");

	char multi_nulls[] = {'\0', '\0', '\0', '\0', 0};
	assert_strrchr(multi_nulls, '\0', "Multiple null bytes, return last");

	char hidden[] = {'h', 'i', '\0', 'x', 'y', 'z', 0};
	assert_strrchr(hidden, 'z', "Character after null (should not match)");

}

int main(int argc, char *argv[])
{
	open_errlog("err.log");


	memcmp_tester();
	// memchr_tester();
	// strncmp_tester();
	// strrchr_tester();
	// atoi_tester();
	// bzero_tester();
	// toupper_tester();
	// tolower_tester();
	// memcpy_tester();
	// memset_tester();
	// strchr_tester();
	// isprint_tester();
	// isdigit_tester();
	// isalpha_tester();
	// isalnum_tester();
	strdup_tester();
	close_errlog();
	return (0);
}

// NOLINTEND clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling
