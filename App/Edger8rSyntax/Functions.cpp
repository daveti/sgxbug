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

/* No need to implement memccpy here! */

/* edger8r_function_attributes:
 *   Invokes ECALL declared with calling convention attributes.
 *   Invokes ECALL declared with [public].
 */
void edger8r_function_attributes(void)
{
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;

    ret = ecall_function_calling_convs(global_eid);
    if (ret != SGX_SUCCESS)
        abort();
    
    ret = ecall_function_public(global_eid);
    if (ret != SGX_SUCCESS)
        abort();
    
    /* user shall not invoke private function here */
    int runned = 0;
    ret = ecall_function_private(global_eid, &runned);
    if (ret != SGX_ERROR_ECALL_NOT_ALLOWED || runned != 0)
        abort();
}

/* ocall_function_allow:
 *   The OCALL invokes the [allow]ed ECALL 'edger8r_private'.
 */
void ocall_function_allow(void)
{
    int runned = 0;
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    
    ret = ecall_function_private(global_eid, &runned);
    if (ret != SGX_SUCCESS || runned != 1)
        abort();
}
