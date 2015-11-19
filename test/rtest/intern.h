/*
 *  intern.h
 *
 *  Copyright (C) 1999-2015, ARM Limited, All Rights Reserved
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  This file is part of the Optimized Routines project
 */

#ifndef mathtest_intern_h
#define mathtest_intern_h

#include <mpfr.h>
#include <mpc.h>

#include "types.h"
#include "wrappers.h"

/* Generic function pointer. */
typedef void (*funcptr)(void);

/* Pointers to test function types. */
typedef int    (*testfunc1)(mpfr_t, mpfr_t, mpfr_rnd_t);
typedef int    (*testfunc2)(mpfr_t, mpfr_t, mpfr_t, mpfr_rnd_t);
typedef int    (*testrred)(mpfr_t, mpfr_t, int *);
typedef char * (*testsemi1)(uint32 *, uint32 *);
typedef char * (*testsemi2)(uint32 *, uint32 *, uint32 *);
typedef char * (*testsemi2f)(uint32 *, uint32 *, uint32 *);
typedef char * (*testldexp)(uint32 *, uint32 *, uint32 *);
typedef char * (*testfrexp)(uint32 *, uint32 *, uint32 *);
typedef char * (*testmodf)(uint32 *, uint32 *, uint32 *);
typedef char * (*testclassify)(uint32 *, uint32 *);
typedef char * (*testclassifyf)(uint32 *, uint32 *);

typedef int    (*testfunc1c)(mpc_t, mpc_t, mpc_rnd_t);
typedef int    (*testfunc2c)(mpc_t, mpc_t, mpc_t, mpc_rnd_t);

typedef int    (*testfunc1cr)(mpfr_t, mpc_t, mpfr_rnd_t);

/* Pointer to a function that generates random test cases. */
typedef void (*casegen)(uint32 *, uint32, uint32);

/*
 * List of testable functions, their types, and their testable range.
 */
enum {
    args1,                             /* afloat-based, one argument */
    args1f,                            /* same as args1 but in single prec */
    args2,                             /* afloat-based, two arguments */
    args2f,                            /* same as args2 but in single prec */
    rred,                              /* afloat-based, one arg, aux return */
    rredf,                             /* same as rred but in single prec */
    semi1,                             /* seminumerical, one argument */
    semi1f,                            /* seminumerical, 1 arg, float */
    semi2,                             /* seminumerical, two arguments */
    semi2f,                            /* seminumerical, 2 args, floats */
    t_ldexp,                           /* dbl * int -> dbl */
    t_ldexpf,                          /* sgl * int -> sgl */
    t_frexp,                           /* dbl -> dbl * int */
    t_frexpf,                          /* sgl -> sgl * int */
    t_modf,                            /* dbl -> dbl * dbl */
    t_modff,                           /* sgl -> sgl * sgl */
    classify,                          /* classify double: dbl -> int */
    classifyf,                         /* classify float: flt -> int */
    compare,                           /* compare doubles, returns int */
    comparef,                          /* compare floats, returns int */

    args1c,                            /* acomplex-base, one argument */
    args2c,
    args1fc,
    args2fc,
    args1cr,                           /* dbl-complex -> complex */
    args1fcr                           /* sgl-complex -> complex */
};

typedef struct __testable Testable;
struct __testable {
    char *name;
    funcptr func;
    int type;
    wrapperfunc wrappers[MAXWRAPPERS];
    casegen cases; /* complex functions use the same casegen for both real and complex args */
    uint32 caseparam1, caseparam2;
};

extern Testable functions[];
extern const int nfunctions;

extern void init_pi(void);

int nargs_(Testable* f);

#endif
