#ifndef TASKTWO_H
#define TASKTWO_H
#include <Graph.h>
#include <QVector>
#include <QDebug>

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
	int labor;
	Vertex_t* pvertex;
	int vrtxCount;

	struct VertexLenth
	{
		Vertex_t* vertex;
		int parent;
		int lenth;
	};

	QVector<VertexLenth*> pathSize;//lenth and parent

	void prepTask (Vertex_t* pvrtx)
	{
		pvertex = pvrtx;

		labor = 0;

		pathSize.clear();

		for (typename Graph<Vertex_t,Edge_t>::VertexIterator i = pgraph->vertexBegin(); i != pgraph->vertexEnd(); i++)
		{
			pathSize.append(new VertexLenth);
			(this->pathSize[(*i)->getIndex()])->vertex = *i;
			(this->pathSize[(*i)->getIndex()])->parent = -1;
			(this->pathSize[(*i)->getIndex()])->lenth = INT_MAX;
		}
		pathSize[pvrtx->getIndex()]->lenth = 0;
	}

	bool solve()
	{	
		typename Graph<Vertex_t,Edge_t>::EdgeIterator eiter;

		for (int i = 1; i <= vrtxCount - 1; i++)
		{		
			eiter = pgraph->edgeBegin();
			while (eiter != pgraph->edgeEnd())
			{
				labor++;
				Vertex_t* from = (*eiter)->getBegin();
				Vertex_t* to = (*eiter)->getEnd();
				int toind = to->getIndex();
				int fromind = from->getIndex();

				if (pathSize[fromind]->lenth != INT_MAX)
				{
					if (pathSize[toind]->lenth > (pathSize[fromind]->lenth + (*eiter)->getWeight()))
					{
						pathSize[toind]->lenth = (pathSize[fromind]->lenth + (*eiter)->getWeight());
						pathSize[toind]->parent = from->getIndex();
					}
				}
				++eiter;
			}
		}

		eiter = pgraph->edgeBegin();
		while (eiter != pgraph->edgeEnd())
		{
			labor++;
			Vertex_t* from = (*eiter)->getBegin();
			Vertex_t* to = (*eiter)->getEnd();
			if (pathSize[to->getIndex()]->lenth > (pathSize[from->getIndex()]->lenth + (*eiter)->getWeight()))
				return false;
			++eiter;
		}

		return true;
	}

public:
	TaskTwo(Graph<Vertex_t,Edge_t>* _pgraph, Vertex_t* pvrtx) : pgraph(_pgraph), pvertex(pvrtx)
	{
		vrtxCount = pgraph->vertexCount();
		labor = 0;

		for (typename Graph<Vertex_t,Edge_t>::VertexIterator i = pgraph->vertexBegin(); i != pgraph->vertexEnd(); ++i)
		{
			pathSize.append(new VertexLenth);
			(this->pathSize[(*i)->getIndex()])->vertex = *i;
			(this->pathSize[(*i)->getIndex()])->parent = -1;
			(this->pathSize[(*i)->getIndex()])->lenth = INT_MAX;
		}
		pathSize[pvrtx->getIndex()]->lenth = 0;
		this->solve();
	}

	TaskTwo(TaskTwo& other)
	{
		this->pgraph = other.pgraph;
		this->labor = other.labor;
		this->pvertex = other.pvertex;
		this->vrtxCount = other.vrtxCount;
		this->pathSize = other.pathSize;
	}

	~TaskTwo(){}

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

	QVector<Vertex_t*> result(int maxLenth = INT_MAX)
	{
		QVector<Vertex_t*> tmp;

		for (int i = 0; i < vrtxCount; i++)
			if (pathSize[i]->lenth < maxLenth)
			{
				tmp.append(pathSize[i]->vertex);
				//qDebug() << pathSize[i]->lenth << " : " << pathSize[i]->parent;
			}

		qDebug() << "labortness" << labor;
		qDebug() << "edges * vertexes" << pgraph->edgeCount() * pgraph->vertexCount();
		return tmp;
	}
};

#endif // TASKTWO_H
