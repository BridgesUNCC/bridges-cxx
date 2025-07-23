#ifndef BRIDGESEXP_H
#define BRIDGESEXP_H

namespace bridges {

	struct RuntimeException : public std::exception {
	
		std::string what_str;

		RuntimeException() = default;		
		virtual ~RuntimeException() = default;
		
		virtual const char* what() const noexcept {
			return what_str.c_str();
		}
	};

        struct HTTPException : public bridges::RuntimeException {
		std::string url; //URL hit that generated the exception
		long httpcode; // The returned HTTP code
		std::string headers; //The headers returned by the HTTP server
		std::string data; //The data returned by the HTTP server

		HTTPException (std::string url,
			long httpcode,
			std::string headers,
			std::string data)
			:url(url), httpcode(httpcode), headers(headers), data(data) {
			what_str = std::string("HTTPException raised when hitting ") + url + "\n" +
				"HTTP code: " + to_string(httpcode) + "\n" +
				headers + "\n" +
				data;
		}
		virtual ~HTTPException() = default;
	};

}

#endif
