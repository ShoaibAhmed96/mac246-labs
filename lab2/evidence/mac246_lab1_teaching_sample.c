/* MAC 246 Graded Lab 1, session 3: the benign teaching binary.
 *
 * This is the whole program. It is compiled by
 * mac246_lab1_make_teaching_binary.py into evidence/sample_teaching.bin, which
 * is the file students run file, strings, sha256sum and readelf against.
 *
 * Read it before you run it. That is the point of the exercise, and it is why
 * the source is committed next to the binary.
 *
 * What this program does, completely:
 *   - writes nine lines to standard output with puts,
 *   - adds up the bytes of one constant array that lives inside itself,
 *   - returns 0.
 *
 * What this program does not do, at all:
 *   - it opens no socket and resolves no name, so it touches no network,
 *   - it opens, creates, writes and deletes no file, anywhere, including /tmp,
 *   - it calls no exec, fork, system or popen, so it starts no other process,
 *   - it reads no environment variable and no command-line argument,
 *   - it loads no library of its own and maps no memory it did not declare,
 *   - it needs no privilege, and nothing it does changes the machine.
 *
 * Two of the strings below are planted so that students find something worth
 * arguing about in the strings output. Neither one is used:
 *
 *   BEACON_URL is a string constant that is printed and never opened. Its host
 *   is under the .invalid top level domain, which RFC 2606 reserves precisely
 *   so that it can never resolve. The program contains no networking code, so
 *   there is nothing that could open it even if it did resolve.
 *
 *   LOCK_PATH is a string constant that is printed and never created. The
 *   program contains no file code.
 *
 *   The lesson is the one that matters most in static triage: a string is
 *   evidence of what a program contains, not evidence of what it does. The
 *   imports tell you what it can do. This binary imports puts and nothing
 *   else, so it can print and it can do nothing else.
 */
#include <stdio.h>
#include <stddef.h>

#ifndef MAC246_BUILD_TAG
#define MAC246_BUILD_TAG "MAC246-BUILD-0000000000000000"
#endif

static const char BANNER[]     = "MAC246-TEACHING-SAMPLE v1.0 benign static-analysis target";
static const char BUILD_TAG[]  = MAC246_BUILD_TAG;
static const char BEACON_URL[] = "http://update-check.invalid/report";
static const char LOCK_PATH[]  = "/tmp/mac246-teaching.lock";
static const char B64_BLOB[]   = "TUFDMjQ2LXRlYWNoaW5nLXNhbXBsZQ==";
static const char NOTE_1[]     = "INERT-STRING: the URL above is never opened, this program has no network code";
static const char NOTE_2[]     = "INERT-STRING: the path above is never created, this program writes no files";
static const char NOTE_3[]     = "SAFE-TO-RUN: prints these lines, sums one internal array, exits 0";

/* One small constant array, so that .text has some arithmetic in it and
 * .rodata is not the only thing in the file worth looking at. */
static const unsigned char SAMPLE_TABLE[32] = {
    0x4d, 0x41, 0x43, 0x32, 0x34, 0x36, 0x20, 0x74,
    0x65, 0x61, 0x63, 0x68, 0x69, 0x6e, 0x67, 0x20,
    0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x20, 0x74,
    0x61, 0x62, 0x6c, 0x65, 0x20, 0x76, 0x31, 0x0a
};

int main(void)
{
    unsigned int sum = 0;
    size_t i;
    char line[64];

    puts(BANNER);
    puts(BUILD_TAG);
    puts(BEACON_URL);
    puts(NOTE_1);
    puts(LOCK_PATH);
    puts(NOTE_2);
    puts(B64_BLOB);
    puts(NOTE_3);

    for (i = 0; i < sizeof SAMPLE_TABLE; i++) {
        sum += SAMPLE_TABLE[i];
    }
    snprintf(line, sizeof line, "CHECKSUM: %u over %zu bytes", sum, sizeof SAMPLE_TABLE);
    puts(line);

    return 0;
}
