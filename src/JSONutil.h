#ifndef JSON_UTIL_
#define JSON_UTIL_

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

namespace bridges {


	namespace JSONUtil {
		///encodes a string object into a JSON string. that is to say, the string is escaped properly and surrounded by quotes
		inline string JSONencode(const string &str) {

			rapidjson::Value s;
			s.SetString(rapidjson::StringRef(str.c_str()));


			rapidjson::StringBuffer buffer;
			rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
			s.Accept(writer);

			const char* output = buffer.GetString();

			string ss = output;
			return ss;
		}
	}
}

#endif
