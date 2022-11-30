// SPDX-License-Identifier: GPL-3.0-only
/**
 * Copyright (c) 2022 - CCOS ICMC-USP
 */

#ifndef UTILS_H
#define UTILS_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

/* Report a system error and exit. */

#define sysfatal(expression)                                                  \
    do {                                                                      \
        if ((expression)) {                                                   \
            fprintf(stderr, "%s: %d: %s: %s\n", __FILE__, __LINE__, __func__, \
                    strerror(errno));                                         \
            exit(EXIT_FAILURE);                                               \
        }                                                                     \
    } while (0)

/* Subtract the ‘struct timeval’ values X and Y, storing the result in RESULT.
   Return 1 if the difference is negative, otherwise 0. */

int timeval_subtract(struct timeval *result, struct timeval *x,
                     struct timeval *y);

#endif /* UTILS_H */
