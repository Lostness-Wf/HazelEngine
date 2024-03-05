#pragma once

#include <vector>

#undef INFINITE
#include "msdf-atlas-gen.h"

namespace Hazel {

	struct MSDFData
	{
		//表示字形的几何信息，通常用于描述单个字符或字形的特征和属性。
		//包括字形的位置、尺寸、纹理坐标等相关信息，用于在字形图集中定位和渲染单个字符或字形。
		std::vector<msdf_atlas::GlyphGeometry> Glyphs;

		//表示字体的几何信息，用于描述整个字体的特征和属性。
		//包括字体的大小、行高、基准线位置等整体信息，用于在生成字形图集时提供字体的整体信息，以便在渲染时正确地处理字体的各种属性和特征。
		msdf_atlas::FontGeometry FontGeometry;
	};

}