/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: SceneLighting.h

*/

#ifndef _SceneLighting_h_
#define _SceneLighting_h_

#include "Instance.h"

namespace rs {
	class SceneLighting : public Instance {
	public:
		INITIALIZE_INSTANCE_HEADER(SceneLighting);

		void render() override;
	};

} // namespace rs

#endif // _SceneLighting_h_
