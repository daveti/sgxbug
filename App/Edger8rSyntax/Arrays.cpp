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


#include "../App.h"
#include "Enclave_u.h"

/* edger8r_array_attributes:
 *   Invokes ECALLs declared with array attributes.
 */
void edger8r_array_attributes(void)
{
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;

    /* user_check */
    int arr1[4] = {0, 1, 2, 3};
    ret = ecall_array_user_check(global_eid, arr1);
    if (ret != SGX_SUCCESS)
        abort();

    /* make sure arr1 is changed */
    for (int i = 0; i < 4; i++)
        assert(arr1[i] == (3 - i));

    /* in */
    int arr2[4] = {0, 1, 2, 3};
    ret = ecall_array_in(global_eid, arr2);
    if (ret != SGX_SUCCESS)
        abort();
    
    /* arr2 is not changed */
    for (int i = 0; i < 4; i++)
        assert(arr2[i] == i);
    
    /* out */
    int arr3[4] = {0, 1, 2, 3};
    ret = ecall_array_out(global_eid, arr3);
    if (ret != SGX_SUCCESS)
        abort();
    
    /* arr3 is changed */
    for (int i = 0; i < 4; i++)
        assert(arr3[i] == (3 - i));
    
    /* in, out */
    int arr4[4] = {0, 1, 2, 3};
    ret = ecall_array_in_out(global_eid, arr4);
    if (ret != SGX_SUCCESS)
        abort();
    
    /* arr4 is changed */
    for (int i = 0; i < 4; i++)
        assert(arr4[i] == (3 - i));
    
    /* isary */
    array_t arr5 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    ret = ecall_array_isary(global_eid, arr5);
    if (ret != SGX_SUCCESS)
        abort();
    
    /* arr5 is changed */
    for (int i = 0; i < 10; i++)
        assert(arr5[i] == (9 - i));
}
