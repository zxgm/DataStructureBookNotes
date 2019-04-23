
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

// 쳲���������������
class FibUtil
{
public:
	FibUtil(uint32_t numOfItems);
	~FibUtil();

	// ���С��value��ֵ�����쳲���������ֵ
	int64_t getlt(uint32_t value);

	template<typename VST>
	void traverse(VST &t);

private:
	uint32_t m_numOfItems;

	// �洢С��������쳲�������ֵ
	int64_t *m_pItems;
	uint32_t m_numOfReal;// ʵ�ʴ洢��������
	void initialize();
};

template<typename VST>
void FibUtil::traverse(VST &t)
{
	for (int32_t i = 0; i < m_numOfItems; i++)
		t(m_pItems[i]);
}
