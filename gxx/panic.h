#ifndef GXX_PANIC_H
#define GXX_PANIC_H

#include <gxx/util/location.h>
#include <cstring>
#include <cstdio>


__BEGIN_DECLS

void panic(const char* str);

__END_DECLS

/*static inline void panic_not_supported(location loc) {
	char buf [128];
	sprintf(buf, "FunctionNotSupported: \r\nfile: %s\r\nline: %d\r\nfunc: %s", loc.file, loc.line, loc.func);
	panic(buf);
}*/

#define PANIC_TRACED(...)					\
{debug_print_location(current_location());	\
gxx::panic(__VA_ARGS__);}

//#define GXX_PANIC_TRACED(...) PANIC_TRACED(__VA_ARGS__)

#ifdef __cplusplus
namespace gxx {
	using ::panic;
}
#endif

#endif
