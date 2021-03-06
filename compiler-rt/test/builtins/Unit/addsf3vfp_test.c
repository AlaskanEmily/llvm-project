// RUN: %clang_builtins %s %librt -o %t && %run %t
//===-- addsf3vfp_test.c - Test __addsf3vfp -------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file tests __addsf3vfp for the compiler_rt library.
//
//===----------------------------------------------------------------------===//

#include "int_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


extern COMPILER_RT_ABI float __addsf3vfp(float a, float b);

#if __arm__ && __VFP_FP__
int test__addsf3vfp(float a, float b)
{
    float actual = __addsf3vfp(a, b);
    float expected = a + b;
    if (actual != expected)
        printf("error in test__addsf3vfp(%f, %f) = %f, expected %f\n",
               a, b, actual, expected);
    return actual != expected;
}
#endif

int main()
{
#if __arm__ && __VFP_FP__
    if (test__addsf3vfp(1.0, 1.0))
        return 1;
    if (test__addsf3vfp(HUGE_VALF, HUGE_VALF))
        return 1;
    if (test__addsf3vfp(0.0, HUGE_VALF))
        return 1;
    if (test__addsf3vfp(0.0, -0.0))
        return 1;
#else
    printf("skipped\n");
#endif
    return 0;
}
