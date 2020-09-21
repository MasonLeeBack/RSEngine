/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: RSErrorHandling.h

*/

#ifndef _RSERRORHANDLING_H_
#define _RSERRORHANDLING_H_

#include <stdexcept>

namespace rs {

	class errorHandling {
	public:
		static void handleError(const char* argument, const char* file, int lineNum);
		static void crashEngine();
	};

#define RSHandleError(str) errorHandling::handleError(str, __FILE__, __LINE__)

}


#endif // _RSERRORHANDLING_H_
