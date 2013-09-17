#ifndef TASK_ONE_H
#define TASK_ONE_H
#include <Graph.h>
#include <QVector>
#include <QDebug>
#include <iostream>

using namespace std;
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

		//cout << currInd << " current Vertex" << endl;

		typename Graph<Vertex_t,Edge_t>::OutgoingEdgeIterator eiter = pgraph->outgoingEdgeBegin(currvrtx);

		for (; eiter != pgraph->outgoingEdgeEnd(currvrtx); ++eiter)
		{
			int iterInd = (*eiter)->getEnd()->getIndex();
			//cout << (*eiter)->getBegin()->getIndex() << "..." << iterInd << endl;

			if (ord[iterInd] == -1)
			{
				laborEdge++;
				this->edgesArray.append(*eiter);
				cout << "from " << currInd << " to " << iterInd << endl;
				solveC(Edge_t(currvrtx, (*eiter)->getEnd()));
			}
			else if (iterInd == currInd)
				{
					laborEdge++;
					this->edgesArray.append(*eiter);
					cout << "from " << currInd << " to " << iterInd << endl;

					this->edgesArray.append(*eiter);
					cout << "from " << iterInd << " to " << currInd << endl;
				}
				else if (ord[iterInd] < ord[fromInd])
					{
						laborEdge++;
						this->edgesArray.append(*eiter);
						cout << "from " << currInd << " to " << iterInd << endl;

						this->edgesArray.append(pgraph->getEdge((*eiter)->getEnd(), currvrtx));

					cout << "from " << iterInd << " to " << currInd << endl;
					}
		}

		if (fromInd != currInd)
		{
			this->edgesArray.append(pgraph->getEdge(currvrtx, other.getBegin()));
			cout << "from " << currInd << " to " << fromInd << endl;
		}
		else
		{
			cout << "." << endl;
		}
//		cout << "up from " << currInd << endl;
	}

	void solve()
	{
		laborVertex = 0;
		laborEdge = 0;
		cnt = 0;

		ord.resize(pgraph->vertexCount());
		for (int i = 0; i < pgraph->vertexCount(); i++)
			ord[i] = -1;
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
			cout << (*one) << endl;
	}

	int operator[] (int v) { return ord[v]; }

public:
	TaskOne () {}
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

		if (_pgraph->vertexCount() == 0)
			return;
		this->solve();
	}

	void restart()
	{
		if (pgraph->vertexCount() == 0)
			return;
		this->solve();
	}

	QVector<Edge_t*> result()
	{
		cout << "edge from...to" << endl;
		typename QVector<Edge_t*>::iterator i = edgesArray.begin();
		for (; i != edgesArray.end(); i++)
		{
			cout << *i << "   " << (*i)->getBegin()->getIndex() << "..." << (*i)->getEnd()->getIndex() << endl;
		}

		cout << "edges labortness: " << laborEdge  << endl;
		cout << "vertex labortness: " << laborVertex << endl;
		cout << "full labortness: " << laborEdge + laborVertex << endl;
		cout << "edges + vertexes: " << pgraph->edgeCount() + pgraph->vertexCount() << endl << endl;
		return edgesArray;
	}
};

#endif // TASK_ONE_H
