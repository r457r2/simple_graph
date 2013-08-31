#ifndef TASK_ONE_H
#define TASK_ONE_H
#include <Graph.h>

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

	void solveC(Edge_t other)
	{
		int fromInd = other.getBegin()->getIndex();
		int currInd = other.getEnd()->getIndex();
		ord[currInd] = cnt++;

		qDebug() << currInd << "current Vertex";

		typename Graph<Vertex_t,Edge_t>::OutgoingEdgeIterator eiter = pgraph->outgoingEdgeBegin(other.getEnd());

		Edge_t* tmp;

		for (; eiter != pgraph->outgoingEdgeEnd(other.getEnd()); ++eiter)
		{
			qDebug() << (*eiter)->getBegin()->getIndex() << "..." << (*eiter)->getEnd()->getIndex();

			if (((*eiter)->getEnd()->getIndex()) == fromInd)
				tmp = *eiter;

			if (ord[(*eiter)->getEnd()->getIndex()] == -1)
			{
				this->edgesArray.append(*eiter);
				qDebug() << "from" << currInd << "to" << (*eiter)->getEnd()->getIndex();
				solveC(Edge_t(other.getEnd(), (*eiter)->getEnd()));
			}
			else if ((*eiter)->getEnd()->getIndex() == currInd)
				{
					this->edgesArray.append(*eiter);
					qDebug() << "from__" << currInd << "to" << (*eiter)->getEnd()->getIndex();

					this->edgesArray.append(*eiter);
					qDebug() << "from__" << (*eiter)->getEnd()->getIndex() << "to" << currInd;
				}
				else if (ord[(*eiter)->getEnd()->getIndex()] < ord[fromInd])
					{
						this->edgesArray.append(*eiter);
						qDebug() << "from" << currInd << "to" << (*eiter)->getEnd()->getIndex();

						typename Graph<Vertex_t,Edge_t>::VertexIterator viter = pgraph->vertexBegin();
						for (int index = 0; index < (*eiter)->getEnd()->getIndex(); index++)
							++viter;
						typename Graph<Vertex_t,Edge_t>::OutgoingEdgeIterator eit = pgraph->outgoingEdgeBegin(*viter);

						while ((*eit)->getEnd()->getIndex() != currInd)
							++eit;
						this->edgesArray.append(*eit);
						qDebug() << "from" << (*eiter)->getEnd()->getIndex() << "to" << currInd;
					}
		}

		if (fromInd != currInd)
		{
			this->edgesArray.append(tmp);
			qDebug() << currInd << "current Vertex";
			qDebug() << "from" << currInd << "to" << fromInd;
		}
		else
		{
			qDebug() << ".";
		}
		qDebug() << "up from" << currInd;
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
		this->edgesArray.clear();
		typename Graph<Vertex_t,Edge_t>::VertexIterator viter = pgraph->vertexBegin();
		for (int v = 0; v < pgraph->vertexCount(); v++)
		{
			if (ord[v] == -1)
				solveC(Edge_t(*viter,*viter));
			 ++viter;
		}

		QVector<int>::iterator one = ord.begin();
		for (;one != ord.end(); one++)
			qDebug() << *one;
	}

public:
	TaskOne(Graph<Vertex_t,Edge_t>* _pgraph) : pgraph(_pgraph),
		cnt(0), ord(pgraph->vertexCount(), -1), edgesArray(0) { this->solve(); }

	TaskOne(TaskOne& other)
	{
		this->pgraph = other.pgraph;
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

	void result()
	{
		typename QVector<Edge_t*>::iterator i = edgesArray.begin();
		for (; i != edgesArray.end(); i++)
		{
			qDebug() << *i;
			qDebug() << (*i)->getBegin()->getIndex() << "..." << (*i)->getEnd()->getIndex();
		}
	}

	int operator[] (int v) { return ord[v]; }
};

#endif // TASK_ONE_H
