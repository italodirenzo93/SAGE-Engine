#ifndef __SCENENODE_H__
#define __SCENENODE_H__

#include <map>
#include <string>
#include <memory>

namespace SAGE
{
	class cSceneNode
	{
	public:
		cSceneNode();
		virtual ~cSceneNode();

	protected:
		virtual void OnRender() {}

	public:
		void AttachNode(std::string const&, std::shared_ptr<cSceneNode>);
		std::shared_ptr<cSceneNode> DetachNode(std::string const&);
		void RenderNodes();

	private:
		cSceneNode*	m_parent;
		std::map<std::string, std::shared_ptr<cSceneNode>>	m_children;
	};
}

#endif