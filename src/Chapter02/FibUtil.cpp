
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
// 2,3,4,5,3,4,3 // 7项
void FibUtil::initialize()
{
	// 存在问题，当数据项很多，多余空间
	m_pItems = new int64_t[m_numOfItems];
	memset(m_pItems, 0, m_numOfItems*sizeof(int64_t));

	uint32_t index = 0;
	int64_t f = 0, g = 1;
	m_pItems[index] = g;
	while (++index < m_numOfItems)
	{
		g += f;
		f = g - f;
		if (g >= m_numOfItems)
		{
			m_numOfReal = index;
			break;
		}
		else
			m_pItems[index] = g;
	}
}

int64_t FibUtil::get(uint32_t itemIndex)
{
	assert(0 <= itemIndex < m_numOfReal);
	return m_pItems[itemIndex];
}

int64_t FibUtil::get()
{
	return m_pItems[m_numOfReal-1];
}