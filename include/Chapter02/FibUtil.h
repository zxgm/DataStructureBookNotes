
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

// 斐波那契数列生成类
class FibUtil
{
public:
	FibUtil(uint32_t numOfItems);
	~FibUtil();

	// 获取斐波那契数列中第itemIndex项
	int64_t get(uint32_t itemIndex);
	int64_t get();

	template<typename VST>
	void traverse(VST &t);

private:
	uint32_t m_numOfItems;

	// 存储小于项数的斐波那契数值
	int64_t *m_pItems;
	uint32_t m_numOfReal;// 实际存储的项数量

	void initialize();
};

template<typename VST>
void FibUtil::traverse(VST &t)
{
	for (int32_t i = 0; i < m_numOfItems; i++)
		t(m_pItems[i]);
}
