/*

RSEngine
Copyright (c) 2019 Mason Lee Back

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

File name: Texture.cpp

*/

#include <RSEngine.h>

using namespace rs::Render;
using namespace rs::Utils;

namespace rs {
    INITIALIZE_INSTANCE_SOURCE(Texture);

    void Texture::render() {
        /* Get the parent instance pipeline. */
        RenderPipeline* parentPipeline = Parent->pipeline;

        /* Another texture isn't already applied. Apply one. */
        if (parentPipeline->textureObject == nullptr) {
            // load the texture data and assign the texture file
            int tex_width, tex_height, tex_bpp;
            unsigned char *data = stbi_load(File.c_str(), &tex_width, &tex_height, &tex_bpp, STBI_rgb_alpha);
            if (data == NULL)
                return;

            RSTextureDesc desc;
            desc.imageType = RS_IMAGE_R8G8B8A8_UNORM;
            desc.data = data;
            desc.iPitch = tex_width * tex_bpp;
            desc.iSlicePitch = 0;

            parentPipeline->textureObject = g_Renderer->CreateTexture(desc);
        }

        renderChildren();
    }

    void Texture::renderClean() {
        /* Get the parent instance pipeline. */
        RenderPipeline* parentPipeline = Parent->pipeline;

        if (parentPipeline->textureObject != nullptr) {
            g_Renderer->DestroyTexture(parentPipeline->textureObject);
            pipeline->textureObject = nullptr;
        }
    }

} // namespace rs

