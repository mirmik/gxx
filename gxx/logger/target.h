#ifndef GXX_LOGGER_TARGET_H
#define GXX_LOGGER_TARGET_H

#include <gxx/debug/dprint.h>

namespace gxx {
	namespace log {
		class target {
		public:
			void log(const char* str) {
				dprln(str);
			}
		};
	}
}

#endif