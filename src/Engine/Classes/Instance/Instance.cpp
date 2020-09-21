/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: Instance.cpp

*/

#include <Classes/Instance.h>

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

		//delete this;
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

    void Instance::render() {
        renderChildren();
    }

    void Instance::renderChildren() {
        for (auto kid : children) {
            if (kid) {
                kid->render();
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
