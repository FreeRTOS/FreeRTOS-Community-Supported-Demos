 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


/******************************************************************************
 * @file     csi_core.h
 * @brief    CSI Core Layer Header File
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/

#ifndef _CORE_H_
#define _CORE_H_

#include <stdint.h>
#include <core/csi_rv_encoding.h>

#include <core/core_rv64.h>
#include <core/csi_rv64_gcc.h>

#ifdef __cplusplus
extern "C" {
#endif

__STATIC_INLINE const char* csi_get_cpu_name()
{
#if CONFIG_CPU_XUANTIE_C906
	return "c906";
#elif CONFIG_CPU_XUANTIE_C906FD
	return "c906fd";
#elif CONFIG_CPU_XUANTIE_C906FDV
	return "c906fdv";
#elif CONFIG_CPU_XUANTIE_C907
	return "c907";
#elif CONFIG_CPU_XUANTIE_C907FD
	return "c907fd";
#elif CONFIG_CPU_XUANTIE_C907FDV
	return "c907fdv";
#elif CONFIG_CPU_XUANTIE_C907FDVM
	return "c907fdvm";
#elif CONFIG_CPU_XUANTIE_C907_RV32
	return "c907-rv32";
#elif CONFIG_CPU_XUANTIE_C907FD_RV32
	return "c907fd-rv32";
#elif CONFIG_CPU_XUANTIE_C907FDV_RV32
	return "c907fdv-rv32";
#elif CONFIG_CPU_XUANTIE_C907FDVM_RV32
	return "c907fdvm-rv32";
#elif CONFIG_CPU_XUANTIE_C908
	return "c908";
#elif CONFIG_CPU_XUANTIE_C908V
	return "c908v";
#elif CONFIG_CPU_XUANTIE_C908I
	return "c908i";
#elif CONFIG_CPU_XUANTIE_C908X
	return "c908x";
#elif CONFIG_CPU_XUANTIE_C908X_CP
	return "c908x-cp";
#elif CONFIG_CPU_XUANTIE_C908X_CP_XT
	return "c908x-cp-xt";
#elif CONFIG_CPU_XUANTIE_C910
	return "c910";
#elif CONFIG_CPU_XUANTIE_C920
	return "c920";
#elif CONFIG_CPU_XUANTIE_C910V2
	return "c910v2";
#elif CONFIG_CPU_XUANTIE_C910V3
	return "c910v3";
#elif CONFIG_CPU_XUANTIE_C910V3_CP
	return "c910v3-cp";
#elif CONFIG_CPU_XUANTIE_C910V3_CP_XT
	return "c910v3-cp-xt";
#elif CONFIG_CPU_XUANTIE_C920V2
	return "c920v2";
#elif CONFIG_CPU_XUANTIE_C920V3
	return "c920v3";
#elif CONFIG_CPU_XUANTIE_C920V3_CP
	return "c920v3-cp";
#elif CONFIG_CPU_XUANTIE_C920V3_CP_XT
	return "c920v3-cp-xt";
#elif CONFIG_CPU_XUANTIE_R910
	return "r910";
#elif CONFIG_CPU_XUANTIE_R920
	return "r920";
#elif CONFIG_CPU_XUANTIE_R908
	return "r908";
#elif CONFIG_CPU_XUANTIE_R908FD
	return "r908fd";
#elif CONFIG_CPU_XUANTIE_R908FDV
	return "r908fdv";
#elif CONFIG_CPU_XUANTIE_R908_CP
	return "r908-cp";
#elif CONFIG_CPU_XUANTIE_R908FD_CP
	return "r908fd-cp";
#elif CONFIG_CPU_XUANTIE_R908FDV_CP
	return "r908fdv-cp";
#elif CONFIG_CPU_XUANTIE_R908_CP_XT
	return "r908-cp-xt";
#elif CONFIG_CPU_XUANTIE_R908FD_CP_XT
	return "r908fd-cp-xt";
#elif CONFIG_CPU_XUANTIE_R908FDV_CP_XT
	return "r908fdv-cp-xt";
#elif CONFIG_CPU_XUANTIE_E901PLUS_CP
	return "e901plus-cp";
#elif CONFIG_CPU_XUANTIE_E901PLUS_B_CP
	return "e901plusb-cp";
#elif CONFIG_CPU_XUANTIE_E901PLUS_M_CP
	return "e901plusm-cp";
#elif CONFIG_CPU_XUANTIE_E901PLUS_BM_CP
	return "e901plusbm-cp";
#elif CONFIG_CPU_XUANTIE_E901_CP
	return "e901-cp";
#elif CONFIG_CPU_XUANTIE_E901_B_CP
	return "e901b-cp";
#elif CONFIG_CPU_XUANTIE_E901_ZM_CP
	return "e901zm-cp";
#elif CONFIG_CPU_XUANTIE_E901_BZM_CP
	return "e901bzm-cp";
#elif CONFIG_CPU_XUANTIE_E902
	return "e902";
#elif CONFIG_CPU_XUANTIE_E902M
	return "e902m";
#elif CONFIG_CPU_XUANTIE_E902T
	return "e902t";
#elif CONFIG_CPU_XUANTIE_E902MT
	return "e902mt";
#elif CONFIG_CPU_XUANTIE_E906
	return "e906";
#elif CONFIG_CPU_XUANTIE_E906F
	return "e906f";
#elif CONFIG_CPU_XUANTIE_E906FD
	return "e906fd";
#elif CONFIG_CPU_XUANTIE_E906P
	return "e906p";
#elif CONFIG_CPU_XUANTIE_E906FP
	return "e906fp";
#elif CONFIG_CPU_XUANTIE_E906FDP
	return "e906fdp";
#elif CONFIG_CPU_XUANTIE_E907
	return "e907";
#elif CONFIG_CPU_XUANTIE_E907F
	return "e907f";
#elif CONFIG_CPU_XUANTIE_E907FD
	return "e907fd";
#elif CONFIG_CPU_XUANTIE_E907P
	return "e907p";
#elif CONFIG_CPU_XUANTIE_E907FP
	return "e907fp";
#elif CONFIG_CPU_XUANTIE_E907FDP
	return "e907fdp";
#else
	return "unknown";
#endif
}


#ifdef __cplusplus
}
#endif

#endif /* _CORE_H_ */
