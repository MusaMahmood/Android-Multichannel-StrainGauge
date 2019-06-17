package com.yeolabgt.mahmoodms.multistraingauge

/**
 * Created by Musa Mahmood on 1/14/2018.
 *
 */

class NativeInterfaceClass {


    @Throws(IllegalArgumentException::class)
    external fun jmainInitialization(b: Boolean): Int
    @Throws(IllegalArgumentException::class)
    external fun jfiltRescale(data: DoubleArray): FloatArray
    @Throws(IllegalArgumentException::class)
    external fun janalyzeOutputs(data: FloatArray): Double

    companion object {
        init {
            System.loadLibrary("ssvep-lib")
        }
    }
}