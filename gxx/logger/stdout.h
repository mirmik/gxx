#ifndef GXX_LOGGER_CONSOLE_H
#define GXX_LOGGER_CONSOLE_H

#include <gxx/logger/target.h>
#include <gxx/io/stdstream.h>

namespace gxx {
	namespace log {
		class stdout_target : public target {
			std_stream io;

			void log(const char* str) override;
		};
	}
}

#endif