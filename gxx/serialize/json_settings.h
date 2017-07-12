#ifndef GXX_JSON_SETTINGS_H
#define GXX_JSON_SETTINGS_H

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>

#include <gxx/serialize/json_parser.h>
#include <gxx/iteratible.h>

namespace gxx {

	class json_settings {
	public:
		json m_settings;

		std::string pathstr;

		json_settings(const char* path) : pathstr(path) {};

		void load() {
			std::fstream file(pathstr);
			std::stringstream file_contents;
			file_contents << file.rdbuf();
			m_settings = json_parser::parse(file_contents).unwrap();
			file.close();
		}

		void save() {
			std::fstream file(pathstr, std::ios_base::trunc);
			m_settings.prettyPrintTo(file);	
			file.close();
		}

		json& settings() {
			return m_settings;
		}
	};
	
}

#endif