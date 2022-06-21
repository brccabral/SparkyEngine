#pragma once

#include "layer.h"
#include "../batchrenderer2d.h"

namespace sparky::graphics
{
	class TileLayer : public Layer
	{
	public:
		TileLayer(Shader *shader);
		~TileLayer();
	};
}