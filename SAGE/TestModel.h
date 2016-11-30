#pragma once

#include "SceneNode.h"
#include "MeshManager.h"

namespace SAGE
{
	class cTestModel : public cSceneNode
	{
		std::shared_ptr<cMeshInfo> m_pMeshInfo;
	public:
		cTestModel();
		void OnRender() override;
	};
}