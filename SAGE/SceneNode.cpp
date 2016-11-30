#include "SceneNode.h"
#include <iostream>

namespace SAGE
{
	cSceneNode::cSceneNode() {}
	cSceneNode::~cSceneNode() {}

	void cSceneNode::AttachNode(std::string const& name, std::shared_ptr<cSceneNode> node) {
		node->m_parent = this;
		m_children.insert(std::pair<std::string, std::shared_ptr<cSceneNode>>(name, node));
	}

	std::shared_ptr<cSceneNode> cSceneNode::DetachNode(std::string const& name) {
		if (m_children.find(name) == m_children.end()) {
			return nullptr;
		}

		auto ptrToNode = std::make_shared<cSceneNode>(*m_children[name].get());
		ptrToNode->m_parent = nullptr;
		m_children.erase(name);
		return ptrToNode;
	}

	void cSceneNode::RenderNodes() {
		this->OnRender();
		for (auto& child : m_children) {
			child.second->RenderNodes();
		}
	}
}