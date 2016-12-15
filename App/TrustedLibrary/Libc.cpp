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

/* ecall_libc_functions:
 *   Invokes standard C functions.
 */
void ecall_libc_functions(void)
{
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;

    ret = ecall_malloc_free(global_eid);
    if (ret != SGX_SUCCESS)
        abort();
    
    int cpuid[4] = {0x1, 0x0, 0x0, 0x0};
    ret = ecall_sgx_cpuid(global_eid, cpuid, 0x0);
    if (ret != SGX_SUCCESS)
        abort();
}
