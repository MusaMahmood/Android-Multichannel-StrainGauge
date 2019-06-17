//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: prep_eog.h
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 30-Jan-2019 20:49:44
//
#ifndef PREP_EOG_H
#define PREP_EOG_H

// Include Files
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "prep_eog_types.h"

// Function Declarations
extern void prep_eog(const double data_in[768], float Y_o[768]);
extern void prep_eog_initialize();
extern void prep_eog_terminate();

#endif

//
// File trailer for prep_eog.h
//
// [EOF]
//
