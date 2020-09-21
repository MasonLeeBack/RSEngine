/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: RSEngine_Versioning.h

*/

#ifndef _RSENGINE_VERSIONING_H_
#define _RSENGINE_VERSIONING_H_

namespace rs {
	typedef struct engine_versioning_t {
		int engineMajor;
		int engineMinor;
		int engineIncrement;
		const char* engineBranch;
	};

	static engine_versioning_t engineVersion = { 2, 0, 000001, "main" };
}

#endif // _RSENGINE_VERSIONING_H_
