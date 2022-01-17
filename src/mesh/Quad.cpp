#include "Quad.h"

Quad::Quad()
{
	Positions = {
		{ -1.0f,  1.0f, 0.0f },
		{ -1.0f, -1.0f, 0.0f },
		{  1.0f,  1.0f, 0.0f },
		{  1.0f, -1.0f, 0.0f }
	};

	TexCoords = {
		{ 0.0f, 1.0f },
		{ 0.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ 1.0f, 0.0f },
	};

	Topology = TOPOLOGY::TRIANGLE_STRIP;

	init();
}
