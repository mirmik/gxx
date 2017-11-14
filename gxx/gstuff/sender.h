#ifndef GXX_GSTUFF_SENDER_H
#define GXX_GSTUFF_SENDER_H

#include <gxx/io/ostream_messenger.h>
#include <gxx/util/crc.h>
#include <gxx/util/gstuff.h>

namespace gxx {
	namespace gstuff {
		class sender : public gxx::io::ostream_messenger {
			gxx::io::ostream& out;
			uint8_t crc;
	
		public:
			sender(gxx::io::ostream& out) : out(out) {}
	
			void start_message() override {
				out.putchar(gxx::gmsg::strt);
				crc = 0xFF;
			}
	
			void end_message() override {
				out.putchar(crc);
				out.putchar(gxx::gmsg::strt);
			}
	
		protected:
			int writeData(const char* str, size_t sz) override {
				while(sz--) {
					char c = *str++;
					strmcrc8(&crc, c);
					switch(c) {
						case gxx::gmsg::strt:
							out.putchar(gxx::gmsg::stub);
							out.putchar(gxx::gmsg::stub_strt);
							break;
	
						case gxx::gmsg::stub:
							out.putchar(gxx::gmsg::stub);
							out.putchar(gxx::gmsg::stub_stub);
							break;

						default:
							out.putchar(c);
					}
				}
			}
		};
	}
}

#endif