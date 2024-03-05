#pragma once

#include <vector>

#undef INFINITE
#include "msdf-atlas-gen.h"

namespace Hazel {

	struct MSDFData
	{
		//��ʾ���εļ�����Ϣ��ͨ���������������ַ������ε����������ԡ�
		//�������ε�λ�á��ߴ硢��������������Ϣ������������ͼ���ж�λ����Ⱦ�����ַ������Ρ�
		std::vector<msdf_atlas::GlyphGeometry> Glyphs;

		//��ʾ����ļ�����Ϣ����������������������������ԡ�
		//��������Ĵ�С���иߡ���׼��λ�õ�������Ϣ����������������ͼ��ʱ�ṩ�����������Ϣ���Ա�����Ⱦʱ��ȷ�ش�������ĸ������Ժ�������
		msdf_atlas::FontGeometry FontGeometry;
	};

}