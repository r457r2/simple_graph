#ifndef TASKTWO_H
#define TASKTWO_H
#include <Graph.h>

//Интерфейс АТД «Задача 2» включает операции:
//Конструктор (g) - создает объект задачи 2, ассоциированный с графом  g, и выполняет решение задачи для графа g,
//Конструктор (T) - конструктор копирования создает копию объекта – задачи T,
//Деструктор () - уничтожает внутренние структуры объекта задачи,
//Set (g) – связывает объект задачи с графом g и выполняет решение задачи 2 для графа g,
//Restart ( ) – повторно выполняет решение задачи 2 для графа g,
//Result( ) –  возвращает результат решения задачи 2

//Варианты алгоритмов:
//1)	определение списка вершин, которые лежат в пределах заданного расстояния d от заданной вершины
//взвешенного орграфа с отрицательной весовой функции на основе алгоритма Беллмана-Форда,

template <typename Vertex_t, typename Edge_t>
class TaskTwo
{
private:
	Graph<Vertex_t,Edge_t>* pgraph;	
	Vertex_t* pvertex;
	int vrtxCount;
	int* pathSize;//lenth and parent

	void prepTask (Vertex_t* pvrtx)
	{
		pvertex = pvrtx;
		vrtxCount = pgraph->vertexCount();

		delete []pathSize;
		pathSize = new int[vrtxCount * 2];

		for (int i = 0; i < vrtxCount; i++)
		{
			this->pathSize[0 + i] = INT_MAX;
			this->pathSize[vrtxCount + i] = -1;
		}
		pathSize[pvrtx->getIndex()] = 0;
	}

	bool solve()
	{
		for (int i = 1; i <= vrtxCount - 1; i++)
		{
			typename Graph<Vertex_t,Edge_t>::EdgeIterator eiter = pgraph->edgeBegin();
			while (eiter != pgraph->edgeEnd())
			{
				Vertex_t* from = (*eiter)->getBegin();
				Vertex_t* to = (*eiter)->getEnd();

				if (pathSize[from->getIndex()] != INT_MAX)
				{
					if (pathSize[to->getIndex()] > (pathSize[from->getIndex()] + (*eiter)->getWeight()))
					{
						pathSize[to->getIndex()] = (pathSize[from->getIndex()] + (*eiter)->getWeight());
						pathSize[vrtxCount + to->getIndex()] = from->getIndex();
					}
				}
				eiter++;
			}

			eiter = pgraph->edgeBegin();
			while (eiter != pgraph->edgeEnd())
			{
				Vertex_t* from = (*eiter)->getBegin();
				Vertex_t* to = (*eiter)->getEnd();

				if (pathSize[to->getIndex()] > (pathSize[from->getIndex()] + (*eiter)->getWeight()))
					return false;
				eiter++;
			}

			return true;
		}
//		for i ←1 to | V[G] | - 1
//		5.      do for для каждого ребра (u, v)E[G]
//		6.               do Relax (u, v, w)
//		7.  for для каждого ребра (u, v)E[G]
//		8.           do if d[v]>d[u] + w(u, v)
//		9.                    then return FALSE
//		10. return TRUE.
	}

public:
	TaskTwo(Graph<Vertex_t,Edge_t>* _pgraph, Vertex_t* pvrtx) : pgraph(_pgraph)
	{
		pvertex = pvrtx;
		vrtxCount = pgraph->vertexCount();
		pathSize = new int[vrtxCount * 2];

		for (int i = 0; i < vrtxCount; i++)
		{
			this->pathSize[0 + i] = INT_MAX;
			this->pathSize[vrtxCount + i] = -1;;
		}
		pathSize[pvrtx->getIndex()] = 0;

		this->solve();
	}

	TaskTwo(TaskTwo& other)
	{
		this->pgraph = other.pgraph;
		this->pvertex = other.pvertex;
		this->vrtxCount = other.vrtxCount;
		pathSize = new int[vrtxCount * 2];

		for (int i = 0; i < vrtxCount; i++)
		{
			this->pathSize[0 + i] = other.pathSize[0 + i];
			this->pathSize[vrtxCount + i] = other.pathSize[vrtxCount + i];
		}
	}

	~TaskTwo(){delete []pathSize;}

	bool set(Graph<Vertex_t,Edge_t>* pgrph, Vertex_t* pvrtx)
	{
		this->pgraph = pgrph;
		this->prepTask(pvrtx);
		return (this->solve());
	}

	bool restart(Vertex_t* pvrtx)
	{
		this->prepTask(pvrtx);
		return (this->solve());
	}

	bool restart()
	{
		this->prepTask(pvertex);
		return (this->solve());
	}
	
	void result()
	{
		for (int i = 0; i < vrtxCount; i++)
		{
			qDebug() << pathSize[i] << " : " << pathSize[vrtxCount + i];
		}
	}
};

#endif // TASKTWO_H
