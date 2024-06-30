#pragma once

#include "IScene.h"

class SceneTitle :
	public IScene
{
public:
	void Update() override;
	void Draw() override;
};

