
#include "Chapter02\FibUtil.h"

FibUtil::FibUtil(uint32_t numOfItems)
	:m_numOfItems(numOfItems)
{
	initialize();
}

FibUtil::~FibUtil()
{
	if (m_pItems)
	{
		delete[] m_pItems;
		m_pItems = NULL;
	}
}

// 0 1 1 2 3 5 8 13 21 ...
void FibUtil::initialize()
{
	m_pItems = new int64_t[m_numOfItems];
	uint32_t index = 0;
	int64_t f = 0, g = 1;
	while (index < m_numOfItems)
	{
		g += f;
		f = g - f;
		if (g <= m_numOfItems)
		{

		}
	}
}
