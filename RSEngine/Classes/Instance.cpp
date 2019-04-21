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

File name: Instance.cpp

*/

#include "RSEngine.h"

namespace rs {
	Instance::Instance() {
		ClassName = "Instance";
		Name = getClassName();
	}

	Instance::~Instance() {
		/* should we do something here? */
	}

	std::string Instance::GetName() {
		return Name;
	}

	void Instance::SetName(std::string name) {
		Name = name;
	}

	void Instance::Remove() {
		SetParent(NULL);

		for (auto kid : children) {
			if (kid) {
				kid->Remove();
			}
		}
	}

	std::shared_ptr<Instance> Instance::CopyInstance(std::shared_ptr<Instance> Parent) {
		return std::shared_ptr<Instance>();
	}

	std::string Instance::GetPath() {
		std::string temp = Name;
		if (Parent != NULL) {
			temp = Parent->GetPath() + "/" + temp; /* keep adding the directories until we reach the end */
		}

		return temp;
	}

	std::string Instance::GetClassHierarchy() {
		std::string temp = getClassName();
		if (Parent != NULL) {
			temp = Parent->GetClassHierarchy() + "/" + temp;
		}
		return temp;
	}

	std::shared_ptr<Instance> Instance::GetParent() {
		return Parent;
	}

	void Instance::SetParent(std::shared_ptr<Instance> parent) {
		/* No need to try setting the parent */
		if (Parent == parent)
			return;

		if (parent == shared_from_this())
			return;

		/* clear the previous child, and add the new one */
		if (Parent) {
			for (auto i = Parent->children.begin(); i != Parent->children.end(); ) {
				if (*i == shared_from_this()) i = Parent->children.erase(i); else ++i;
			}
		}
		Parent = parent;
		if (Parent)
			Parent->children.push_back(shared_from_this());
	}

	std::vector<std::shared_ptr<Instance>> Instance::GetChildren() {
		return children;
	}

	void Instance::ClearAllChildren() {
		for (auto kid : children) {
			if (kid) {
				kid->Remove();
			}
		}
	}

	void Instance::tick() {
		tickChildren();
	}

	void Instance::tickChildren() {
		for (auto kid : children) {
			if (kid) {
				kid->tick();
			}
		}
	}

	std::string Instance::getClassName() {
		return ClassName;
	}

} // namespace rs
