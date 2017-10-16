#ifndef GXX_DATATREE_H
#define GXX_DATATREE_H

#include <cstdint>
#include <cassert>
#include <utility>

#include <string>
#include <vector>
#include <map>

#include <gxx/result.h>
#include <gxx/string.h>
#include <gxx/util/ctrdtr.h>
#include <gxx/buffer.h>

using namespace gxx::result_type;

namespace gxx {
	class trent {
	public:
		enum class type {
			string,
			array,
			dictionary,
                        integer,
                        floating,
			noinit,
		};

		using check_type = uint8_t;

		static constexpr check_type check_subset = 0;
		static constexpr check_type check_superset = 1;
		static constexpr check_type check_equal = 2;

                using float_type = double;
                using numer_type = double;
                using integer_type = int64_t;
                using array_type = std::vector<trent>;
                using dictionary_type = std::map<std::string, trent>;
                //using _type = double;

	protected:
		trent::type m_type = trent::type::noinit;

		union {
                        int64_t m_i64;
			double m_num;
			std::string m_str;
			std::vector<trent> m_arr;
			std::map<std::string, trent> m_dict;
		};

	public:
		~trent();
		trent();
		trent(const trent& other);
		trent(const std::string& str);
		trent(const trent::type& t);
                trent(double num);
                trent(int i);
                trent(long i);
                trent(long long i);
                trent(short i);

	private:
		template <typename T>	
		void reset(T obj) {
			invalidate();
			init(obj);
		}

		void init(trent::type t);
		void init(const std::string& str);
                void init(double i);
                void init(short i);
                void init(int i);
                void init(long i);
                void init(long long i);

                void init_array(size_t reserve);
		void invalidate();

	public:
                trent& operator[](int i);
		trent& operator[](const char* key);
		trent& operator[](const std::string& key);
		trent& operator[](const gxx::buffer& key);

		std::map<std::string, trent>& as_dictionary();
                result<std::map<std::string, trent>&> as_dictionary_critical();

                std::vector<trent>& as_array();
                result<std::vector<trent>&> as_array_critical();
                std::vector<trent>& as_vector();
                result<std::vector<trent>&> as_vector_critical();
		
                numer_type as_numer();
                float_type as_floating();
                integer_type as_integer();

		const double as_numer_default(const double i);
		result<const double&> as_numer_critical();

		const std::string& as_string();
                const gxx::buffer as_buffer() const;
		const std::string& as_string_default(const std::string& str);
		result<const std::string&> as_string_critical();
		
		
                //double get_numer(const char*, double def);
                //double get_numer(const std::string&, double def);

                //result<double> get_numer_critical(const std::string&);

                REFERENCE_GETTER(unsafe_integer, m_i64);
                REFERENCE_GETTER(unsafe_float, m_num);
		REFERENCE_GETTER(unsafe_string, m_str);
		REFERENCE_GETTER(unsafe_array, m_arr);
		REFERENCE_GETTER(unsafe_dictionary, m_dict);

                CONSTREF_GETTER(unsafe_integer_const, m_i64);
                CONSTREF_GETTER(unsafe_float_const, m_num);
                CONSTREF_GETTER(unsafe_string_const, m_str);
                CONSTREF_GETTER(unsafe_array_const, m_arr);
                CONSTREF_GETTER(unsafe_dictionary_const, m_dict);


		trent::type get_type() const;
		const char * type_to_str();

		bool is_nil() 			{ return m_type == type::noinit; }
                bool is_numer() 		{ return m_type == type::floating || m_type == type::integer; }
                bool is_float() 		{ return m_type == type::floating; }
		bool is_array() 		{ return m_type == type::array; }
		bool is_dictionary()	{ return m_type == type::dictionary; }
		bool is_string() 		{ return m_type == type::string; }
		
                strlst check_dict(strlst lst, check_type ct);
		std::pair<strlst,strlst> check_dict_symmetric(strlst lst);

	public:
		trent& operator= (const trent& other);
                trent& operator= (const std::string& str);
                trent& operator= (double num);
                trent& operator= (short i);
                trent& operator= (int i);
                trent& operator= (long i);
                trent& operator= (long long i);
		int size();

		bool contains(gxx::buffer buf);
	};
}

#endif
