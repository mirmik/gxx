#ifndef GXX_SERIALIZE_GBSON_H
#define GXX_SERIALIZE_GBSON_H

#include <gxx/io/iostream.h>
#include <gxx/trent/trent.h>
//#include <gxx/util/gbson.h>
#include <gxx/result.h>

namespace gxx {
	constexpr int8_t GBSON_INTERNAL_ERROR = -10;

	namespace gbson {
		enum class type : uint8_t {
			integer = 0,
			numer = 1,
			string = 2,
			list = 3,
			dict = 4,
		};

		int dump(const gxx::trent& tr, char* buffer, size_t maxlen);
		int load(	   gxx::trent& tr, char* buffer, size_t maxlen);
	}
}

#endif // GBSON_H
