#ifndef GXX_STRMOUT_H
#define GXX_STRMOUT_H

#include <gxx/debug/dprint.h>

#include <string.h>
#include <gxx/string.h>
//#include <gxx/format.h>
#include <gxx/events/signal.h>

namespace gxx {
	namespace io {
		class strmout {
		public:
			virtual int write(const char* str, size_t sz) = 0;
			virtual int putchar(char c) {
				return write(&c,1);
			}

			/*template<typename ... Args> 
			int print(const char* str, Args ... args) {
				gxx::string gen = gxx::format(str, args...);
				int ret = print(gen.c_str());
				return ret;
			}*/

			int print(const char* str) {
				return write(str, strlen(str));
			}

			template<typename ... Args>
			int println(Args ... args) {
				int ret = print(args ...);
				return ret + write("\r\n", 2);
			}			
		};

		class strmin {
			virtual int read(char* str, size_t sz) = 0;
			virtual int getchar() {
				char c;
				read(&c,1);
				return c;
			}
		};

		class lstrmout : virtual public strmout {
		public:
			sigflag haveData;
			virtual size_t room() = 0;
			virtual void clean();
		};

		class lstrmin : virtual public strmin {
			virtual size_t avail() = 0;
		};


		class strmio : virtual public strmout, virtual public strmin {};
		class lstrmio : virtual public strmio, virtual public lstrmout, virtual public lstrmin {};		
	
		class debug_strmout : public strmout {
			bool m_dumpmode = false;

			void dump_putchar(char c) {
				if(isprint(c)) {
					debug_putchar(c);
				} else {
					debug_write("\\x", 2);
					debug_printhex_uint8(c);
				}
			}

			void dump_write(const char* str, size_t sz) {
				const char* end = str + sz;
				for(;str!=end;str++) {
					dump_putchar(*str);
				}
			}
		public:
			int write(const char* str, size_t sz) override {
				m_dumpmode ? dump_write(str, sz) : debug_write(str, sz);
				return sz;
			}
			
			int putchar(const char c) override {
				m_dumpmode ? dump_putchar(c) : debug_putchar(c);
				return 1;
			}

			void dumpmode(bool en) {
				m_dumpmode = en;
			}
		};
	}
}

#endif