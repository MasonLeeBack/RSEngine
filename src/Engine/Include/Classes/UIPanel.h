/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: UIPanel.h

*/

#ifndef _UIPANEL_H_
#define _UIPANEL_H_

#include "Instance.h"

namespace rs {

    class UIPanel : public Instance {
    public:
        INITIALIZE_INSTANCE_HEADER(UIPanel);

        UIScale Size;
        UIScale Position;

        float Transparency = 0.0f;

        float Rotation = 0.0f;

        virtual void render() override;
    };

} // namespace rs

#endif // _UIPANEL_H_
