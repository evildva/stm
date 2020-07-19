#ifndef _PRINT_H
#define _PRINT_H


#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>

#pragma import(__use_no_semihosting)

#ifdef __cplusplus
 extern "C" {
#endif

int print(void* out, const char*fmt, ...);

#ifdef __cplusplus
}
#endif

#endif
