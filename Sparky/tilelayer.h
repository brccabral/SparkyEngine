#pragma once

#include "src/graphics/layers/layer.h"
#include "src/graphics/batchrenderer2d.h"
#include <sparky_types.h>
#include "src/maths/maths.h"

class TileLayer : public sparky::graphics::Layer
{
public:
	TileLayer(sparky::graphics::Shader *shader);
	~TileLayer();
};
