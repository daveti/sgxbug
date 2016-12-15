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


#include <stdarg.h>
#include <stdio.h>      /* vsnprintf */
#include <string.h>	/* memcpy */

#include "sgx_status.h"
#include "Enclave.h"
#include "Enclave_t.h"  /* print_string */

/*
 * Sensitive Ins covered by UMIP
 * SGDT - Store Global Descriptor Table
 * SIDT - Store Interrupt Descriptor Table
 * SLDT - Store Local Descriptor Table
 * SMSW - Store Machine Status Word
 * STR - Store Task Register
*/
#define SEN_INS_SGDT	0
#define SEN_INS_SIDT	1
#define SEN_INS_SLDT	2
#define SEN_INS_SMSW	3
#define SEN_INS_STR	4

/* Def for x86_64 descriptor */
typedef struct {
	unsigned long	limit : 16;
	unsigned long	base  : 64;
} __attribute__((packed)) dt_x86_64;

/* Global vars in the enclave */
static dt_x86_64 gdt = {0, 0};
static dt_x86_64 idt = {0, 0};
static unsigned long ldt = -1;
static unsigned long tr = -1;
static unsigned long msw = -1;

/*
 * Wrappers for all inlines asms
 */
static void get_gdt(void)
{
	asm volatile( "sgdt %0" : "=m"(gdt) );
}

static void get_idt(void)
{
	asm volatile( "sidt %0" : "=m"(idt) );
}

static void get_ldt(void)
{
	asm volatile( "sldt %0" : "=m"(ldt) );
}

static void get_msw(void)
{
	asm volatile( "smsw %0" : "=m"(msw) );
}

static void get_tr(void)
{
	asm volatile( "str %0" : "=m"(tr) );
}


/*
 * do_sensitive_ins:
 *   Invokes ECALL to do inline asm using sensitive instructions.
 * NOTE: since we could not call set_cpu_affinity inside the enclave,
 * there is no way to guarantee that the GDT/IDT/LDT/MSW/STR are from
 * the same CPU core.
 */
sgx_status_t do_sensitive_ins(int idx, int len, char *buf)
{
	sgx_status_t rtn;

	rtn = SGX_SUCCESS;

	switch (idx) {
	case SEN_INS_SGDT:
		if (len != sizeof(dt_x86_64)) {
			rtn = SGX_ERROR_INVALID_PARAMETER;
			break;
		}
		get_gdt();
		memcpy(buf, &gdt, len);
		break;
	case SEN_INS_SIDT:
		if (len != sizeof(dt_x86_64)) {
			rtn = SGX_ERROR_INVALID_PARAMETER;
			break;
		}
		get_idt();
		memcpy(buf, &idt, len);
		break;
	case SEN_INS_SLDT:
		if (len != sizeof(unsigned long)) {
			rtn = SGX_ERROR_INVALID_PARAMETER;
			break;
		}
		get_ldt();
		memcpy(buf, &ldt, len);
		break;
	case SEN_INS_SMSW:
		if (len != sizeof(unsigned long)) {
			rtn = SGX_ERROR_INVALID_PARAMETER;
			break;
		}
		get_msw();
		memcpy(buf, &msw, len);
		break;
	case SEN_INS_STR:
		if (len != sizeof(unsigned long)) {
			rtn = SGX_ERROR_INVALID_PARAMETER;
			break;
		}
		get_tr();
		memcpy(buf, &tr, len);
		break;
	default:
		rtn = SGX_ERROR_UNEXPECTED;
		break;
	}

	return rtn;
}

/* 
 * printf: 
 *   Invokes OCALL to display the enclave buffer to the terminal.
 */
void printf(const char *fmt, ...)
{
    char buf[BUFSIZ] = {'\0'};
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, BUFSIZ, fmt, ap);
    va_end(ap);
    ocall_print_string(buf);
}
