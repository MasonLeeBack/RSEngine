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

File name: Instance.h
Notes: This class should not (and can not) be initialized from itself

*/

#pragma once
#ifndef _Instance_h_
#define _Instance_h_

#include <string>
#include <memory>
#include <vector>

#include <Utils/RSEngine_RenderPipeline.h>

#define INITIALIZE_INSTANCE_SOURCE(CName) \
    CName::CName() { \
        CName::ClassName = #CName; \
        CName::Name = #CName; \
    } \
    std::shared_ptr<CName> CName::newInstance(std::shared_ptr<Instance> inParent) { \
        std::shared_ptr<CName> Ins; \
        Ins = std::make_shared<CName>(); \
        Ins->SetParent(inParent); \
        return Ins; \
    } \
    std::string CName::getClassName() \
    { \
        return #CName; \
    } 

#define INITIALIZE_INSTANCE_HEADER(ClassName) \
    ClassName(); \
    static std::shared_ptr<ClassName> newInstance(std::shared_ptr<Instance> inParent); \
    virtual std::string getClassName() override;

#define public_entity std::shared_ptr

namespace rs {
    class Instance : public std::enable_shared_from_this<Instance> {
    public:
        Instance();
        ~Instance();

        std::string Name;
        virtual void SetName(std::string name);
        virtual std::string GetName();

        virtual void Remove(); /* Recursively removes all children, then itself */
        virtual std::shared_ptr<Instance> CopyInstance(std::shared_ptr<Instance> Parent = NULL); /* Copies instance to memory, until parent is specified */

        virtual std::string GetPath();
        virtual std::string GetClassHierarchy();

        std::shared_ptr<Instance> Parent;
        virtual std::shared_ptr<Instance> GetParent();
        virtual void SetParent(std::shared_ptr<Instance> parent);

        std::vector<std::shared_ptr<Instance>> children;
        virtual std::vector<std::shared_ptr<Instance>> GetChildren();
        virtual void ClearAllChildren(); /* Recursively removes all children */

        Utils::RenderPipeline *pipeline = nullptr;
        virtual void render();
        virtual void renderClean();
        virtual void renderChildren();

        virtual void tick(); /* called every frame */
        virtual void tickChildren();

        virtual std::shared_ptr<Instance> newInstance() {
            return std::make_shared<Instance>();
        }

        std::string ClassName;
        virtual std::string getClassName();
    };

} // namespace rs

#include "EngineClass.h"

#endif // _Instance_h_
