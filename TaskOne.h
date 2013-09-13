#ifndef TASK_ONE_H
#define TASK_ONE_H
#include <Graph.h>
#include <QVector>
#include <QDebug>

//Интерфейс АТД «Задача 1» включает операции:
//Конструктор (g) - создает объект задачи 1, ассоциированный с графом  g, и выполняет решение задачи для графа g,
//Конструктор (T) - конструктор копирования создает копию объекта – задачи T,
//Деструктор () - уничтожает внутренние структуры объекта задачи,
//Set (g) – связывает объект задачи с графом g и выполняет решение задачи 1 для графа g,
//Restart ( ) – повторно выполняет решение задачи 1 для графа g,
//Result( ) –  возвращает результат решения задачи 1

//Варианты задачи 1:
//1)	формирование списка ребер неориентированного графа в порядке двухпроходного эйлерова цикла,

template <typename Vertex_t, typename Edge_t>
class TaskOne
{
private:
	Graph<Vertex_t,Edge_t>* pgraph;
	int cnt;
	QVector<int> ord;	
	QVector<Edge_t*> edgesArray;
	int laborVertex;
	int laborEdge;


	void solveC(Edge_t other)
	{
		laborVertex++;
		int fromInd = other.getBegin()->getIndex();
		int currInd = other.getEnd()->getIndex();
		Vertex_t* currvrtx = other.getEnd();
		ord[currInd] = cnt++;

//qDebug() << currInd << "current Vertex";

		typename Graph<Vertex_t,Edge_t>::OutgoingEdgeIterator eiter = pgraph->outgoingEdgeBegin(currvrtx);

		for (; eiter != pgraph->outgoingEdgeEnd(currvrtx); ++eiter)
		{
			int iterInd = (*eiter)->getEnd()->getIndex();
//qDebug() << (*eiter)->getBegin()->getIndex() << "..." << iterInd;

			if (ord[iterInd] == -1)
			{
				laborEdge++;
				this->edgesArray.append(*eiter);
//qDebug() << "from" << currInd << "to" << iterInd;
				solveC(Edge_t(currvrtx, (*eiter)->getEnd()));
			}
			else if (iterInd == currInd)
				{
					laborEdge++;
					this->edgesArray.append(*eiter);
//qDebug() << "from__" << currInd << "to" << iterInd;

					this->edgesArray.append(*eiter);
//qDebug() << "from__" << iterInd << "to" << currInd;
				}
				else if (ord[iterInd] < ord[fromInd])
					{
						laborEdge++;
						this->edgesArray.append(*eiter);
//qDebug() << "from" << currInd << "to" << iterInd;

						this->edgesArray.append(pgraph->getEdge((*eiter)->getEnd(), currvrtx));

//qDebug() << "from" << iterInd << "to" << currInd;
					}
		}

		if (fromInd != currInd)
		{
			this->edgesArray.append(pgraph->getEdge(currvrtx, other.getBegin()));
//qDebug() << "from" << currInd << "to" << fromInd;
		}
		else
		{
			//qDebug() << ".";
		}
		//qDebug() << "up from" << currInd;
	}
//	{
//		int fromInd = other.getBegin()->getIndex();
//		int toInd = other.getEnd()->getIndex();
//		ord[toInd] = cnt++;
//		qDebug() << "-" << toInd << "adressat";

//		typename Graph<Vertex_t,Edge_t>::OutgoingEdgeIterator eiter = pgraph->outgoingEdgeBegin(other.getEnd());
//		for (; eiter != pgraph->outgoingEdgeEnd(other.getEnd()); ++eiter)
//			if (ord[(*eiter)->getEnd()->getIndex()] == -1)
//				solveC(Edge_t(other.getEnd(), (*eiter)->getEnd()));
//			else if (ord[(*eiter)->getEnd()->getIndex()] == ord[fromInd])
//				qDebug() << "-" << (*eiter)->getEnd()->getIndex() << "-" << toInd << "";

//		if (fromInd != toInd)
//			qDebug() << "-" << fromInd;
//		else
//			qDebug() << "";
//	}

	void solve()
	{
		laborVertex = 0;
		laborEdge = 0;
		this->edgesArray.clear();
		typename Graph<Vertex_t,Edge_t>::VertexIterator viter = pgraph->vertexBegin();
		for (int v = 0; v < pgraph->vertexCount(); v++)
		{
			if (ord[v] == -1)
				solveC(Edge_t(*viter,*viter));
			 ++viter;
		}

//		QVector<int>::iterator one = ord.begin();
//		for (;one != ord.end(); one++)
//			qDebug() << *one;
	}

	int operator[] (int v) { return ord[v]; }

public:
	TaskOne(Graph<Vertex_t,Edge_t>* _pgraph) : pgraph(_pgraph),
		cnt(0), ord(pgraph->vertexCount(), -1), edgesArray(0) { this->solve(); }

	TaskOne(TaskOne& other)
	{
		this->pgraph = other.pgraph;
		this->laborEdge = other.laborEdge;
		this->laborVertex = other.laborVertex;
		this->ord = other.ord;
		this->cnt = other.cnt;
		this->edgesArray = other.edgesArray;
	}

	~TaskOne(){}

	void set(Graph<Vertex_t,Edge_t>* _pgraph)
	{
		this->pgraph = _pgraph;
		return (this->solve());
	}

	void restart()
	{
		return (this->solve());
	}

	QVector<Edge_t*> result()
	{
//		typename QVector<Edge_t*>::iterator i = edgesArray.begin();
//		for (; i != edgesArray.end(); i++)
//		{
//			qDebug() << *i;
//			qDebug() << (*i)->getBegin()->getIndex() << "..." << (*i)->getEnd()->getIndex();
//		}

		qDebug() << "edges labortness" << laborEdge;
		qDebug() << "vertex labortness" << laborVertex;
		qDebug() << "full labortness" << laborEdge + laborVertex;
		qDebug() << "edges + vertexes" << pgraph->edgeCount() + pgraph->vertexCount();
		return edgesArray;
	}
};

#endif // TASK_ONE_H
