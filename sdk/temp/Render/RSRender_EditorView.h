/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSRender_EditorView.h

*/

#ifndef _RSRender_EditorView_h_
#define _RSRender_EditorView_h_

namespace rs::Render {
    class RSRender_EditorView {
        RSRender_EditorView();
        ~RSRender_EditorView();

        void startReroute();
        void endReroute();

        RSShaderResourceView* getShaderResource();
    private:
        RSRender_Texture* texture;
    };

} // namespace rs::Render

#endif // _RSRender_EditorView_h_
