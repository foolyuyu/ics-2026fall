/*
 * Cache Lab Part A: simulate a data cache with LRU replacement.
 * Read a Valgrind trace and report hits, misses, and evictions.
 */
#include <errno.h>
#include <inttypes.h>
#include <getopt.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "cachelab.h"

typedef struct {
    uint64_t tag;
    uint64_t last_used;
    bool valid;
} cachestatus;

/* Print the supported command-line options. */
static void print_usage(const char *program)
{
    printf("Usage: %s [-hv] -s <s> -E <E> -b <b> -t <tracefile>\n",
           program);
}

/* Parse a nonnegative decimal integer, rejecting invalid or oversized values. */
static bool parse_number(const char *text, int *value)
{
    char *end;
    long number;

    errno = 0;
    number = strtol(text, &end, 10);
    if (errno == ERANGE || end == text || *end != '\0' ||
        number < 0 || number > INT_MAX) {
        return false;
    }
    *value = (int)number;
    return true;
}

/* Parse the cache parameters and simulate each access in the trace. */
int main(int argc, char *argv[])
{
    int hit_count = 0, miss_count = 0, eviction_count = 0;
    int S = -1, E = -1, B = -1;
    const char *trace_path = NULL;
    bool verbose = false;
    FILE *fp;
    cachestatus *cache;
    size_t sets, lines;
    uint64_t access_time = 0, dst;
    int size, fields;
    char type;

    if (argc == 1) {
        print_usage(argv[0]);
        return 0;
    }
    int option;
    while ((option = getopt(argc, argv, ":hvs:E:b:t:")) != -1) {
        switch (option) {
        case 'h':
            print_usage(argv[0]);
            return 0;
        case 'v':
            verbose = true;
            break;
        case 's':
        case 'E':
        case 'b': {
            int *value = option == 's' ? &S : option == 'E' ? &E : &B;
            if (!parse_number(optarg, value)) {
                fprintf(stderr, "Invalid value for -%c: %s\n",
                        option, optarg);
                return 1;
            }
            break;
        }
        case 't':
            trace_path = optarg;
            break;
        case ':':
            fprintf(stderr, "Missing argument for -%c\n", optopt);
            return 1;
        default:
            fprintf(stderr, "Unknown option: -%c\n", optopt);
            print_usage(argv[0]);
            return 1;
        }
    }
    if (optind != argc) {
        fprintf(stderr, "Unexpected argument: %s\n", argv[optind]);
        return 1;
    }
    if (S < 0 || E <= 0 || B < 0 || trace_path == NULL ||
        S >= 64 || B >= 64 || S + B >= 64 ||
        S >= (int)(sizeof(size_t) * CHAR_BIT)) {
        fprintf(stderr, "Missing or invalid cache parameters\n");
        print_usage(argv[0]);
        return 1;
    }

    sets = (size_t)1 << S;
    if (sets > SIZE_MAX / (size_t)E ||
        sets * (size_t)E > SIZE_MAX / sizeof(*cache)) {
        fprintf(stderr, "Cache size is too large\n");
        return 1;
    }
    lines = sets * (size_t)E;
    fp = fopen(trace_path, "r");
    if (fp == NULL) {
        perror("Opening trace file");
        return 1;
    }
    cache = malloc(lines * sizeof(*cache));
    if (cache == NULL) {
        perror("Allocating cache");
        fclose(fp);
        return 1;
    }

    for (size_t i = 0; i < lines; ++i) {
        cache[i].valid = false;
    }

    while ((fields = fscanf(fp, " %c %" SCNx64 ",%d", &type, &dst,
                            &size)) == 3) {
        if (type == 'I') {
            continue;
        }
        if (type != 'L' && type != 'S' && type != 'M') {
            fprintf(stderr, "Unknown trace operation: %c\n", type);
            free(cache);
            fclose(fp);
            return 1;
        }
        if (verbose) {
            printf("%c %" PRIx64 ",%d", type, dst, size);
        }

        size_t set = (size_t)((dst >> B) & ((uint64_t)sets - 1));
        uint64_t tag = dst >> (S + B);
        cachestatus *p = cache + set * (size_t)E;
        ++access_time;

        for (cachestatus *i = p; i < p + E; ++i) {
            if (i->valid) {
                if (i->tag == tag) {
                    ++hit_count;
                    i->last_used = access_time;
                    if (verbose) {
                        printf(" hit");
                    }
                    break;
                } else if (i == p + E - 1) {
                    ++miss_count;
                    ++eviction_count;
                    cachestatus *oldest = p;
                    for (cachestatus *j = p + 1; j < p + E; ++j) {
                        if (j->last_used < oldest->last_used) {
                            oldest = j;
                        }
                    }
                    oldest->tag = tag;
                    oldest->last_used = access_time;
                    if (verbose) {
                        printf(" miss eviction");
                    }
                    break;
                }
            } else {
                i->valid = true;
                i->tag = tag;
                i->last_used = access_time;
                ++miss_count;
                if (verbose) {
                    printf(" miss");
                }
                break;
            }
        }
        /* A modify performs a second access to the same cached block. */
        if (type == 'M') {
            ++hit_count;
            if (verbose) {
                printf(" hit");
            }
        }
        if (verbose) {
            printf(" \n");
        }
    }
    if (fields != EOF || ferror(fp)) {
        fprintf(stderr, "Error reading trace file\n");
        free(cache);
        fclose(fp);
        return 1;
    }
    free(cache);
    if (fclose(fp) != 0) {
        perror("Closing trace file");
        return 1;
    }
    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}
