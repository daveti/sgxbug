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


/* Test Calling Conventions */

#include <string.h>
#include <stdio.h>

#include "../Enclave.h"
#include "Enclave_t.h"

/* ecall_function_calling_convs:
 *   memccpy is defined in system C library.
 */
void ecall_function_calling_convs(void)
{
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;

    char s1[] = "1234567890";
    char s2[] = "0987654321";

    char buf[BUFSIZ] = {'\0'};
    memcpy(buf, s1, strlen(s1));

    ret = memccpy(NULL, s1, s2, '\0', strlen(s1));
    
    if (ret != SGX_SUCCESS)
        abort();
    assert(memcmp(s1, s2, strlen(s1)) == 0);

    return;
}

/* ecall_function_public:
 *   The public ECALL that invokes the OCALL 'ocall_function_allow'.
 */
void ecall_function_public(void)
{
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;

    ret = ocall_function_allow();
    if (ret != SGX_SUCCESS)
        abort();
    
    return;
}

/* ecall_function_private:
 *   The private ECALL that only can be invoked in the OCALL 'ocall_function_allow'.
 */
int ecall_function_private(void)
{
    return 1;
}

