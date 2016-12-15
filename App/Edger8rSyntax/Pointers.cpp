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

/* edger8r_pointer_attributes:
 *   Invokes the ECALLs declared with pointer attributes.
 */
void edger8r_pointer_attributes(void)
{
    int val = 0;
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;

    char c[128] = {0};
    size_t len = 0;
    memset(c, 0xe, 128);
    ret = ecall_pointer_user_check(global_eid, &len, &c, 128);
    if (ret != SGX_SUCCESS)
        abort();
    assert(strcmp(c, "SGX_SUCCESS") == 0);


    val = 0;
    ret = ecall_pointer_in(global_eid, &val);
    if (ret != SGX_SUCCESS)
        abort();
    assert(val == 0);
    
    val = 0;
    ret = ecall_pointer_out(global_eid, &val);
    if (ret != SGX_SUCCESS)
        abort();
    assert(val == 1234);
    
    val = 0;
    ret = ecall_pointer_in_out(global_eid, &val);
    if (ret != SGX_SUCCESS)
        abort();
    assert(val == 1234);
    
    ret = ocall_pointer_attr(global_eid);
    if (ret != SGX_SUCCESS)
        abort();

    char str1[] = "1234567890";
    ret = ecall_pointer_string(global_eid, str1);
    if (ret != SGX_SUCCESS)
        abort();
    assert(memcmp(str1, "0987654321", strlen(str1)) == 0);

    const char str2[] = "1234567890";
    ret = ecall_pointer_string_const(global_eid, str2);
    if (ret != SGX_SUCCESS)
        abort();
    assert(memcmp(str2, "1234567890", strlen(str2)) == 0);

    char str3[] = "1234567890";
    ret = ecall_pointer_size(global_eid, (void*)str3, strlen(str3));
    if (ret != SGX_SUCCESS)
        abort();
    assert(memcmp(str3, "0987654321", strlen(str3)) == 0);

    char str4[] = "1234567890";
    ret = ecall_pointer_isptr_readonly(global_eid, (buffer_t)str4, strlen(str4));
    if (ret != SGX_SUCCESS)
        abort();
    assert(memcmp(str4, "1234567890", strlen(str4)) == 0);

    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    ret = ecall_pointer_count(global_eid, arr, 10);
    if (ret != SGX_SUCCESS)
        abort();

    for (int i = 0; i < 10; i++)
        assert(arr[i] == (9 - i));
    
    memset(arr, 0x0, sizeof(arr));
    ret = ecall_pointer_sizefunc(global_eid, (char *)arr);
    if (ret != SGX_SUCCESS)
        abort();

    for (int i = 0; i < 10; i++)
        assert(arr[i] == i);
    
    return;
}

/* ocall_pointer_user_check:
 *   The OCALL declared with [user_check].
 */
void ocall_pointer_user_check(int* val)
{
    (void)val;
    assert(val != NULL);
}

/* ocall_pointer_in:
 *   The OCALL declared with [in].
 */
void ocall_pointer_in(int* val)
{
    *val = 1234;
}

/* ocall_pointer_out:
 *   The OCALL declared with [out].
 */
void ocall_pointer_out(int* val)
{
    *val = 1234;
}

/* ocall_pointer_in_out:
 *   The OCALL declared with [in, out].
 */
void ocall_pointer_in_out(int* val)
{
    *val = 1234;
}
