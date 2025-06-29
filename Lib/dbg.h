#ifndef __dbg_h__
#define __dbg_h__

/***
 * dbg.h - Debugging macros
 * 单文件建议调试宏
 * 可以分级别展示调试信息，并且可以显示调试信息的文件和行号
 * 来源是hardway C ，笨办法学C语言
 * 编译是增加NDEBUG
 * 编译时，在Makefile中增加CFLAGS += -DNDEBUG
 * 可以取消debug的开关
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", \
							  __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...) fprintf(stderr,                                                \
								"[ERROR] (%s:%d:errno:%s)" M "\n", __FILE__, __LINE__, \
								clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr,                          \
								 "[WARN](%s:%d:errno:%s)" M "\n", \
								 __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, "[INFO](%s:%d)" M "\n", \
								 __FILE__, __LINE__, ##__VA_ARGS__)

#define check(A, M, ...)           \
	if (!(A))                      \
	{                              \
		log_err(M, ##__VA_ARGS__); \
		errno = 0;                 \
		goto error;                \
	}

#define sentinel(M, ...)           \
	{                              \
		log_err(M, ##__VA_ARGS__); \
		errno = 0;                 \
		goto error;                \
	}

#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...)   \
	if (!(A))                    \
	{                            \
		debug(M, ##__VA_ARGS__); \
		errno = 0;               \
		goto error;              \
	}

#endif
