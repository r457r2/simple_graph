#ifndef LIST_REPRESENTATION_H
#define LIST_REPRESENTATION_H
#include "Representation.h"

template <typename Vertex_t, typename Edge_t>
class ListRepresentation: public Representation<Vertex_t, Edge_t>
{
private:
	QList<QList<Edge_t*> > repr;

public:
	ListRepresentation (bool _directed = false)
	{
		this->directed = _directed;
	}

	ListRepresentation (int numberOfVertex, bool _directed  = false)
	{
		this->directed = _directed;

		for (int i = 0; i < numberOfVertex; i++)
		{
			this->vertexes.append(new Vertex_t());
			this->vertexes.last()->setIndex(i);
			repr.append(QList<Edge_t*>());
		}
	}

	ListRepresentation (int numberOfVertex, int numberOfEdge, bool _directed = false)
	{
		this->directed = _directed;

		if ((_directed == true) && (numberOfEdge > (numberOfVertex * numberOfVertex)))
				numberOfEdge = numberOfVertex * numberOfVertex;

		int maxEdgeCounter = 0;
		for (int i = 1; i <= this->vertexes.size(); i++)
		{
			maxEdgeCounter += i;
		}
		if (numberOfEdge > maxEdgeCounter)
			numberOfEdge = maxEdgeCounter;

		for (int i = 0; i < numberOfVertex; i++)
		{
			this->vertexes.append(new Vertex_t());
			this->vertexes.last()->setIndex(i);
			repr.append(QList<Edge_t*>());
		}

		qsrand(time_t(NULL));
		for (int i = 0; i < numberOfEdge;)
		{
			int posBegin = qrand()%numberOfVertex;
			int posEnd = qrand()%numberOfVertex;
			if (insertEdge(this->vertexes[posBegin], this->vertexes[posEnd]) != NULL)
			{
				if (this->directed == false)
					insertEdge(this->vertexes[posEnd], this->vertexes[posBegin]);
				i++;
			}
		}

	}

	ListRepresentation (ListRepresentation &one)
	{
		this->directed = one.directed;

		for (int i = 0; i < one.vertexCount(); i++)
		{
			this->vertexes.append(new Vertex_t(*(one.vertexes[i])));
		}

		for (int i = 0; i < one.vertexCount(); i++)
		{
			for (int j = 0; j < one.repr[i].size(); j++)
			{
				this->repr[i].append(new Edge_t(
										this->vertexes[one.repr[i][j]->From()->getIndex()],
										this->vertexes[one.repr[i][j]->To()->getIndex()],
										one.repr[i][j]->getWeight(),
										one.repr[i][j]->getData()));
			}
		}
	}

	~ListRepresentation ()
	{
		for (int i = 0; i < this->vertexes.size(); i++)
		{
			delete this->vertexes[i];
		}

		for (int i = 0; i < this->vertexes.size(); i++)
		{
			for (int j = 0; j < repr[i].size(); j++)
			{
				delete repr[i][j];
			}
		}
	}\

	int edgeCount ()
	{

		int edgeCount = 0;
		if (this->directed == true)
		{
			for (int i = 0; i < this->vertexes.size(); i++)
			{
				edgeCount += repr[i].size();
			}
			return edgeCount;
		}

		int loopEdgeCount = 0;
		for (int i = 0; i < this->vertexes.size(); i++)
		{
			edgeCount += repr[i].size();
			for (int j = 0; j < repr[i].size(); j++)
			{
				if (repr[i][j]->getBegin() == repr[i][j]->getEnd())
				{
					edgeCount--;
					loopEdgeCount++;
					break;
				}
			}
		}
		return ((edgeCount / 2) + loopEdgeCount);
	}

	Vertex_t* insertVertex ()
	{
		this->vertexes.append(new Vertex_t());
		this->vertexes.last()->setIndex(this->vertexes.size() - 1);
		repr.append(QList<Edge_t*>());
		return this->vertexes.last();
	}

	bool deleteVertex (Vertex_t* _pvertex1)
	{
		int pos = this->vertexes.indexOf(_pvertex1);

		if (pos == -1)
			return false;

		for (int i = 0; i < this->vertexes.size(); i++)
		{
			for (int j = 0; j < repr[i].size(); j++)
			{
				if (repr[i][j]->isComingTo(_pvertex1) == true)
				{
					delete repr[i][j];
					repr[i].removeAt(j);
					break;
				}
			}
		}

		delete this->vertexes[pos];
		this->vertexes.removeOne(_pvertex1);
		repr.removeAt(pos);

		for (; pos < this->vertexes.size(); pos++)
		{
			this->vertexes[pos]->setIndex(pos);
		}

		return true;
	}

	Edge_t* insertEdge (Vertex_t* _pvertex1, Vertex_t* _pvertex2)
	{
		if (((this->belongs(_pvertex1)) && (this->belongs(_pvertex2))) == false)
			return NULL;

		int pos1 = _pvertex1->getIndex();
		for (int i = 0; i < repr[pos1].size(); i++)
		{
			if (repr[pos1][i]->isComingTo(_pvertex2) == true)
				return NULL;
		}

		repr[pos1].append(new Edge_t(_pvertex1, _pvertex2));
		if (this->directed == false)
			repr[_pvertex2->getIndex()].append(new Edge_t(_pvertex2, _pvertex1));
		return repr[pos1].last();
	}

	bool deleteEdge (Vertex_t* _vertex1, Vertex_t* _vertex2)
	{
		if (this->belongs(_vertex1) == false)
			return false;

		int pos1 = _vertex1->getIndex();
		for (int i = 0; i < repr[pos1].size(); i++)
		{
			if (repr[pos1][i]->isComingTo(_vertex2) == true)
			{
				delete repr[pos1][i];
				repr[pos1].removeAt(i);

				if (this->directed == false)
				{
					int pos2 = _vertex2->getIndex();
					for (int j = 0; j < repr[pos2].size(); j++)
					{
						if (repr[pos2][j]->isComingTo(_vertex1) == true)
						{
							delete repr[pos2][j];
							repr[pos2].removeAt(j);
							break;
						}
					}
				}
				return true;
			}
		}
		return false;
	}
};

#endif // LIST_REPRESENTATION_H
