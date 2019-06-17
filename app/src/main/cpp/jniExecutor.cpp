//
// Created by mahmoodms on 4/3/2017.
//

#include "rt_nonfinite.h"
#include "prep_eog.h"
#include "analyze_outputs_eog.h"

/*Additional Includes*/
#include <jni.h>
#include <android/log.h>

#define  LOG_TAG "jniExecutor-cpp"
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static void rescale_minmax_floats(const float X[], float Y[], const int size)
{
    int ixstart;
    float mtmp;
    int ix;
    boolean_T exitg1;
    float b_mtmp;
    ixstart = 1;
    mtmp = X[0];
    if (rtIsNaN(X[0])) {
        ix = 2;
        exitg1 = false;
        while ((!exitg1) && (ix < size + 1)) {
            ixstart = ix;
            if (!rtIsNaN(X[ix - 1])) {
                mtmp = X[ix - 1];
                exitg1 = true;
            } else {
                ix++;
            }
        }
    }

    if (ixstart < size) {
        while (ixstart + 1 < size + 1) {
            if (X[ixstart] < mtmp) {
                mtmp = X[ixstart];
            }
            ixstart++;
        }
    }

    ixstart = 1;
    b_mtmp = X[0];
    if (rtIsNaN(X[0])) {
        ix = 2;
        exitg1 = false;
        while ((!exitg1) && (ix < size + 1)) {
            ixstart = ix;
            if (!rtIsNaN(X[ix - 1])) {
                b_mtmp = X[ix - 1];
                exitg1 = true;
            } else {
                ix++;
            }
        }
    }

    if (ixstart < size) {
        while (ixstart + 1 < size+1) {
            if (X[ixstart] > b_mtmp) {
                b_mtmp = X[ixstart];
            }

            ixstart++;
        }
    }

    b_mtmp -= mtmp;
    for (ixstart = 0; ixstart < size; ixstart++) {
        Y[ixstart] = (X[ixstart] - mtmp) / b_mtmp;
    }
}

extern "C" {
JNIEXPORT jfloatArray JNICALL
Java_com_yeolabgt_mahmoodms_multistraingauge_NativeInterfaceClass_jfiltRescale(
        JNIEnv *env, jobject jobject1, jdoubleArray data) {
    jdouble *X = env->GetDoubleArrayElements(data, nullptr);
    if (X == nullptr) LOGE("ERROR - C_ARRAY IS nullptr");
    float Y[384*2];
    jfloatArray m_result = env->NewFloatArray(384*2);
    prep_eog(X, Y);
    env->SetFloatArrayRegion(m_result, 0, 384*2, Y);
    return m_result;
}
}

extern "C" {
JNIEXPORT jdouble JNICALL
/**
 *
 * @param env
 * @param jobject1
 * @return array of frequencies (Hz) corresponding to a raw input signal.
 */
Java_com_yeolabgt_mahmoodms_multistraingauge_NativeInterfaceClass_janalyzeOutputs(
        JNIEnv *env, jobject jobject1, jfloatArray x) {
    jfloat *X = env->GetFloatArrayElements(x, nullptr);
    return analyze_outputs_eog(X);
}
}

extern "C" {
JNIEXPORT jfloatArray JNICALL
Java_com_yeolabgt_mahmoodms_multistraingauge_NativeInterfaceClass_jrescaleMinmax(
        JNIEnv *env, jobject jobject1, jfloatArray data, jint size) {
    jfloat *X = env->GetFloatArrayElements(data, nullptr);
    if (X == nullptr) LOGE("ERROR - C_ARRAY IS nullptr");
    float Y[size];
    jfloatArray m_result = env->NewFloatArray(size);
    rescale_minmax_floats(X, Y, size);
    env->SetFloatArrayRegion(m_result, 0, size, Y);
    return m_result;
}
}

extern "C" {
JNIEXPORT jint JNICALL
Java_com_yeolabgt_mahmoodms_multistraingauge_NativeInterfaceClass_jmainInitialization(
        JNIEnv *env, jobject obj, jboolean terminate) {
    if (!(bool) terminate) {
        prep_eog_initialize();
        return 0;
    } else {
        return -1;
    }
}
}
