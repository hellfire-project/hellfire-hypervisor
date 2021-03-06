/*
Copyright (c) 2016, prpl Foundation

Permission to use, copy, modify, and/or distribute this software for any purpose with or without 
fee is hereby granted, provided that the above copyright notice and this permission notice appear 
in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE 
FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM 
LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, 
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

This code was written by Carlos Moratelli at Embedded System Group (GSE) at PUCRS/Brazil.

*/

#ifndef _TYPES_H_
#define _TYPES_H_

typedef   __INT8_TYPE__ int8_t;
typedef  __INT16_TYPE__ int16_t;
typedef  __INT32_TYPE__ int32_t;
typedef  __INT64_TYPE__ int64_t;
typedef  __UINT8_TYPE__ uint8_t;
typedef __UINT16_TYPE__ uint16_t;
typedef __UINT32_TYPE__ uint32_t;
typedef __UINT64_TYPE__ uint64_t;

#if defined(RISCV64)
typedef __UINT64_TYPE__ uint32_64_t;
typedef __INT64_TYPE__ int32_64_t;
#else
typedef __UINT32_TYPE__ uint32_64_t;
typedef __INT32_TYPE__ int32_64_t;
#endif


typedef uint32_t size_t;

#endif /*_TYPES_H_*/  

