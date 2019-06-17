//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: analyze_outputs_eog.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 30-Jan-2019 20:18:38
//

// Include Files
#include "rt_nonfinite.h"
#include "analyze_outputs_eog.h"

// Function Definitions

//
// Arguments    : const double input_array[6]
// Return Type  : double
//
double analyze_outputs_eog(const float input_array[6])
{
  double output;
  int ixstart;
  double mtmp;
  int itmp;
  int ix;
  boolean_T exitg1;
  ixstart = 1;
  mtmp = input_array[0];
  itmp = 1;
  if (rtIsNaN(input_array[0])) {
    ix = 2;
    exitg1 = false;
    while ((!exitg1) && (ix < 7)) {
      ixstart = ix;
      if (!rtIsNaN(input_array[ix - 1])) {
        mtmp = input_array[ix - 1];
        itmp = ix;
        exitg1 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 6) {
    while (ixstart + 1 < 7) {
      if (input_array[ixstart] > mtmp) {
        mtmp = input_array[ixstart];
        itmp = ixstart + 1;
      }

      ixstart++;
    }
  }

  output = itmp;

  //  output = 1; % 1=null
  //  CLASSES = 6;
  //  rearranged = single(zeros(2000, CLASSES));
  //  for i = 1:2000
  //      for j = 1:CLASSES
  //          rearranged(i, j) = input_array((i-1)*CLASSES + j);
  //      end
  //  end
  //  % analyze last second
  //  [~, inds] = max(rearranged(:, :), [], 2);
  //  cnt = 0;
  //  for i = 1500:2000
  //      if inds(i) > 1
  //          cnt = cnt + 1;
  //          if cnt > 67
  //              output = inds(i);
  //              break;
  //          end
  //      else
  //          cnt = 0;
  //      end
  //  end
  return output;
}

//
// Arguments    : void
// Return Type  : void
//
void analyze_outputs_eog_initialize()
{
  rt_InitInfAndNaN(8U);
}

//
// Arguments    : void
// Return Type  : void
//
void analyze_outputs_eog_terminate()
{
  // (no terminate code required)
}

//
// File trailer for analyze_outputs_eog.cpp
//
// [EOF]
//
