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


#include <cstdlib>
#include <string>

#include "../Enclave.h"
#include "Enclave_t.h"

/*
 * ecall_exception:
 *   throw/catch C++ exception inside the enclave.
 */

void ecall_exception(void)
{
    std::string foo = "foo";
    try {
        throw std::runtime_error(foo);
    }
    catch (std::runtime_error const& e) {
        assert( foo == e.what() );
        std::runtime_error clone("");
        clone = e;
        assert(foo == clone.what() );
    }
    catch (...) {
        assert( false );
    }
}

#include <map>
#include <algorithm>

using namespace std;

/*
 * ecall_map:
 *   Utilize STL <map> in the enclave.
 */
void ecall_map(void)
{
    typedef map<char, int, less<char> > map_t;
    typedef map_t::value_type map_value;
    map_t m;

    m.insert(map_value('a', 1));
    m.insert(map_value('b', 2));
    m.insert(map_value('c', 3));
    m.insert(map_value('d', 4));

    assert(m['a'] == 1);
    assert(m['b'] == 2);
    assert(m['c'] == 3);
    assert(m['d'] == 4);

    assert(m.find('e') == m.end());
    
    return;
}
