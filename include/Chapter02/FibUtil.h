
#include <stdint.h>
#include <stdio.h>

// 쳲���������������
class FibUtil
{
public:
	FibUtil(uint32_t numOfItems);
	~FibUtil();

private:
	uint32_t m_numOfItems;
	int64_t *m_pItems;

	void initialize();
};