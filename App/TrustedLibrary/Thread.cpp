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


#include <thread>
#include <stdio.h>
using namespace std;

#include "../App.h"
#include "Enclave_u.h"

static size_t counter = 0;

void increase_counter(void)
{
    size_t cnr = 0;
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    ret = ecall_increase_counter(global_eid, &cnr);
    if (cnr != 0) counter = cnr; 
    if (ret != SGX_SUCCESS)
        abort();
}

void data_producer(void)
{
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    ret = ecall_producer(global_eid);
    if (ret != SGX_SUCCESS)
        abort();
}

void data_consumer(void)
{
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    ret = ecall_consumer(global_eid);
    if (ret != SGX_SUCCESS)
        abort();
}

/* ecall_thread_functions:
 *   Invokes thread functions including mutex, condition variable, etc.
 */
void ecall_thread_functions(void)
{
    thread adder1(increase_counter);
    thread adder2(increase_counter);
    thread adder3(increase_counter);
    thread adder4(increase_counter);

    adder1.join();
    adder2.join();
    adder3.join();
    adder4.join();

    assert(counter == 4*LOOPS_PER_THREAD);

    printf("Info: executing thread synchronization, please wait...  \n");
    /* condition variable */
    thread consumer1(data_consumer);
    thread producer0(data_producer);
    thread consumer2(data_consumer);
    thread consumer3(data_consumer);
    thread consumer4(data_consumer);
    
    consumer1.join();
    consumer2.join();
    consumer3.join();
    consumer4.join();
    producer0.join();
}
