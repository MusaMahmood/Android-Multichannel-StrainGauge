//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: prep_eog.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 30-Jan-2019 20:49:44
//

// Include Files
#include "rt_nonfinite.h"
#include "prep_eog.h"

// Function Declarations
static void filter(double b[4], double a[4], const double x[402], const double
                   zi[3], double y[402]);
static void filtfilt(const double x_in[384], double y_out[384]);

// Function Definitions

//
// Arguments    : double b[4]
//                double a[4]
//                const double x[402]
//                const double zi[3]
//                double y[402]
// Return Type  : void
//
static void filter(double b[4], double a[4], const double x[402], const double
                   zi[3], double y[402])
{
  double a1;
  int k;
  int naxpy;
  int j;
  a1 = a[0];
  if ((!rtIsInf(a[0])) && (!rtIsNaN(a[0])) && (!(a[0] == 0.0)) && (a[0] != 1.0))
  {
    for (k = 0; k < 4; k++) {
      b[k] /= a1;
    }

    for (k = 0; k < 3; k++) {
      a[k + 1] /= a1;
    }

    a[0] = 1.0;
  }

  for (k = 0; k < 3; k++) {
    y[k] = zi[k];
  }

  memset(&y[3], 0, 399U * sizeof(double));
  for (k = 0; k < 402; k++) {
    naxpy = 402 - k;
    if (!(naxpy < 4)) {
      naxpy = 4;
    }

    for (j = 0; j + 1 <= naxpy; j++) {
      y[k + j] += x[k] * b[j];
    }

    naxpy = 401 - k;
    if (!(naxpy < 3)) {
      naxpy = 3;
    }

    a1 = -y[k];
    for (j = 1; j <= naxpy; j++) {
      y[k + j] += a1 * a[j];
    }
  }
}

//
// Arguments    : const double x_in[384]
//                double y_out[384]
// Return Type  : void
//
static void filtfilt(const double x_in[384], double y_out[384])
{
  double xtmp;
  double d0;
  int i;
  double y[402];
  double dv0[4];
  static const double dv1[4] = { 0.997489880846521, -2.992469642539564,
    2.992469642539564, -0.997489880846521 };

  double dv2[4];
  static const double dv3[4] = { 1.0, -2.9949734530771832, 2.9899595313037808,
    -0.994986062391208 };

  double b_y[402];
  double a[3];
  static const double b_a[3] = { -0.99748988926171522, 1.9949797784811321,
    -0.997489889219522 };

  xtmp = 2.0 * x_in[0];
  d0 = 2.0 * x_in[383];
  for (i = 0; i < 9; i++) {
    y[i] = xtmp - x_in[9 - i];
  }

  memcpy(&y[9], &x_in[0], 384U * sizeof(double));
  for (i = 0; i < 9; i++) {
    y[i + 393] = d0 - x_in[382 - i];
  }

  for (i = 0; i < 4; i++) {
    dv0[i] = dv1[i];
    dv2[i] = dv3[i];
  }

  for (i = 0; i < 3; i++) {
    a[i] = b_a[i] * y[0];
  }

  memcpy(&b_y[0], &y[0], 402U * sizeof(double));
  filter(dv0, dv2, b_y, a, y);
  for (i = 0; i < 201; i++) {
    xtmp = y[i];
    y[i] = y[401 - i];
    y[401 - i] = xtmp;
  }

  for (i = 0; i < 4; i++) {
    dv0[i] = dv1[i];
    dv2[i] = dv3[i];
  }

  for (i = 0; i < 3; i++) {
    a[i] = b_a[i] * y[0];
  }

  memcpy(&b_y[0], &y[0], 402U * sizeof(double));
  filter(dv0, dv2, b_y, a, y);
  for (i = 0; i < 201; i++) {
    xtmp = y[i];
    y[i] = y[401 - i];
    y[401 - i] = xtmp;
  }

  memcpy(&y_out[0], &y[9], 384U * sizeof(double));
}

//
// PREP_EOG Preprocesses ECG Signal:
//  High pass filter @ 0.1 Hz & Upscale (*200) ~Nothing else
// Arguments    : const double data_in[768]
//                float Y_o[768]
// Return Type  : void
//
void prep_eog(const double data_in[768], float Y_o[768])
{
  int i;
  double b[384];
  int i0;
  float Y[768];
  float b_Y[768];
  for (i = 0; i < 2; i++) {
    //  chs:
    filtfilt(*(double (*)[384])&data_in[384 * i], b);
    for (i0 = 0; i0 < 384; i0++) {
      b_Y[i0 + 384 * i] = (float)(200.0 * b[i0]);
    }
  }

  //  CRITICAL STEP: INTERLACES DATA FOR TENSORFLOW FORMAT!
  //  This is due to the way the tf.reshape() works.
  for (i0 = 0; i0 < 384; i0++) {
    for (i = 0; i < 2; i++) {
      Y[i + (i0 << 1)] = b_Y[i0 + 384 * i];
    }
  }

  memcpy(&Y_o[0], &Y[0], 768U * sizeof(float));
}

//
// Arguments    : void
// Return Type  : void
//
void prep_eog_initialize()
{
  rt_InitInfAndNaN(8U);
}

//
// Arguments    : void
// Return Type  : void
//
void prep_eog_terminate()
{
  // (no terminate code required)
}

//
// File trailer for prep_eog.cpp
//
// [EOF]
//
