/**
 *
 * Copyright(c) 2011-2016 Intel Corporation All Rights Reserved.
 *
 * The source code contained or described herein and all documents related to
 * the source code ("Material") are owned by Intel Corporation or its suppliers
 * or licensors. Title to the Material remains with Intel Corporation or its
 * suppliers and licensors. The Material contains trade secrets and proprietary
 * and confidential information of Intel or its suppliers and licensors. The
 * Material is protected by worldwide copyright and trade secret laws and treaty
 * provisions. No part of the Material may be used, copied, reproduced, modified,
 * published, uploaded, posted, transmitted, distributed, or disclosed in any
 * way without Intel's prior express written permission.
 *
 * No license under any patent, copyright, trade secret or other intellectual
 * property right is granted to or conferred upon you by disclosure or delivery
 * of the Materials, either expressly, by implication, inducement, estoppel or
 * otherwise. Any license under such intellectual property rights must be
 * express and approved by Intel(R) in writing.
 *
 */

/* Test Array Attributes */

#include "sgx_trts.h"
#include "../Enclave.h"
#include "Enclave_t.h"

/* ecall_array_user_check:
 *   [user_check] parameter does not perfrom copy operations.
 */
void ecall_array_user_check(int arr[4])
{
    if (sgx_is_outside_enclave(arr, 4 * sizeof(int)) != 1)
        abort();
    
    for (int i = 0; i < 4; i++) {
        assert(arr[i] == i);
        arr[i] = 3 - i;
    }
}

/* ecall_array_in:
 *   arr[] is copied to trusted domain, but modified 
 *   results will not be reflected to the untrusted side.
 */
void ecall_array_in(int arr[4])
{
    for (int i = 0; i < 4; i++) {
        assert(arr[i] == i);
        arr[i] = (3 - i);
    }
}

/* ecall_array_out:
 *   arr[] is allocated inside the enclave, and it will be copied
 *   to the untrusted side
 */
void ecall_array_out(int arr[4])
{
    for (int i = 0; i < 4; i++) {
        /* arr is not copied from App */
        assert(arr[i] == 0);
        arr[i] = (3 - i);
    }
}

/* ecall_array_in_out:
 *   arr[] will be allocated inside the enclave, content of arr[] will be copied either.
 *   After ECALL returns, the results will be copied to the outside.
 */
void ecall_array_in_out(int arr[4])
{
    for (int i = 0; i < 4; i++) {
        assert(arr[i] == i);
        arr[i] = (3 - i);
    }
}

/* ecall_array_isary:
 *   [isary] tells Edger8r that user defined 'array_t' is an array type.
 */
void ecall_array_isary(array_t arr)
{
    if (sgx_is_outside_enclave(arr, sizeof(array_t)) != 1)
        abort();

    int n = sizeof(array_t)/sizeof(arr[0]);
    for (int i = 0; i < n; i++) {
        assert(arr[i] == i);
        arr[i] = (n - 1 - i);
    }
}
