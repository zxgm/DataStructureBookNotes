
typedef enum{UNDISCOVERED,DISCOVERED,VISITED} VStatus;
typedef enum{UNDETERMINED,TREE,CROSS,FORWARD,BACKWARD} EType;

template<typename Tv,typename Te>
class Graph
{
private:
	void reset()
	{
		for (int i = 0; i < n; i++)
		{
			status(i) = UNDISCOVERED;
			dTime(i) = fTime(i) = -1;
			parent(i) = -1;
			priority(i) = INT_MAX;
			for (int j = 0; i < n; j++)
			{
				if (exists(i, j))
					type(i, j) = UNDETERMINED;
			}
		}
	}

public:
	int n;
	virtual int insert(const Tv &) = 0;
	virtual Tv remove(int) = 0;
	virtual Tv& vertex(int) = 0;
	virtual int inDegree(int) = 0;
	virtual int outDegree(int) = 0;
	virtual int firstNbr(int) = 0;
	virtual int nextNbr(int, int) = 0;
	virtual VStatus& status(int) = 0;
	virtual int& dTime(int) = 0;
	virtual int& fTime(int) = 0;
	virtual int& parent(int) = 0;
	virtual int& priority(int) = 0;

	int e;
	virtual bool exists(int, int) = 0;
	virtual void insert(const Te&, int, int, int) = 0;
	virtual Te remove(int, int) = 0;
	virtual EType& type(int, int) = 0;
	virtual Te& edge(int, int) = 0;
	virtual int& weight(int, int) = 0;

	void bfs(int);
	void dfs(int);
	void bcc(int);
	//Stack<Tv>* tSort(int);
	void prim(int);
	void dijkstra(int);
	template<typename PU> void pfs(int, PU);
};