#ifndef JSON_UTIL_
#define JSON_UTIL_

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

namespace bridges {


	namespace JSONUtil {
	  ///encodes whatever C++ primary type: int, float, double, bool, unsigned long int into its basic proper JSON format.
	  ///
	  ///This also works for std::string and char*: that is to say, for a string, it is escaped properly and surrounded by quotes
		
		template <typename T>
		inline string JSONencode(const T& d) {
			rapidjson::Value s;
			s.Set(d);

			rapidjson::StringBuffer buffer;
			rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
			s.Accept(writer);

			const char* output = buffer.GetString();

			string ss = output;
			return ss;
		}

		template <>
		  inline string JSONencode<std::string> (const std::string& str) {

			rapidjson::Value s;
			s.SetString(rapidjson::StringRef(str.c_str()));


			rapidjson::StringBuffer buffer;
			rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
			s.Accept(writer);

			const char* output = buffer.GetString();

			string ss = output;
			return ss;
		}
		
		inline string JSONencode (const char* str) {
		  rapidjson::Value s;
		  s.SetString(rapidjson::StringRef(str));
		  
		  
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
