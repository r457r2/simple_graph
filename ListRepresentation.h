#ifndef LIST_REPRESENTATION_H
#define LIST_REPRESENTATION_H
#include "Representation.h"

template <typename Vertex_t, typename Edge_t>
class Graph;

template <typename Vertex_t, typename Edge_t>
class ListRepresentation: public Representation<Vertex_t, Edge_t>
{
private:
	friend class Graph<Vertex_t, Edge_t>;
	QList<QList<Edge_t*> > list;

public:
	ListRepresentation (bool _directed = false) : Representation<Vertex_t, Edge_t>(_directed) {}

	ListRepresentation (int numberOfVertex, bool _directed  = false) : Representation<Vertex_t, Edge_t>(_directed)
	{
		for (int i = 0; i < numberOfVertex; i++)
			this->insertVertex();
	}

	ListRepresentation (int numberOfVertex, int numberOfEdge, bool _directed = false)
		: Representation<Vertex_t, Edge_t>(_directed)
	{
		if (numberOfEdge > this->maxEdgesCount())
			numberOfEdge = this->maxEdgesCount();

		for (int i = 0; i < numberOfVertex; i++)
			this->insertVertex();

		qsrand(time_t(NULL));
		for (int edgesInserted = 0; edgesInserted < numberOfEdge;)
		{
			int posBegin = qrand() % numberOfVertex;
			int posEnd = qrand() % numberOfVertex;

			if (insertEdge(this->vertexes[posBegin], this->vertexes[posEnd]) != NULL)
				edgesInserted++;
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
			for (int j = 0; j < one.list[i].size(); j++)
			{
				this->list[i].append(new Edge_t(
										this->vertexes[one.list[i][j]->From()->getIndex()],
										this->vertexes[one.list[i][j]->To()->getIndex()],
										one.list[i][j]->getWeight(),
										one.list[i][j]->getData()));
			}
		}
	}

	~ListRepresentation ()
	{
		for (int i = 0; i < this->vertexes.size(); i++)
			delete this->vertexes[i];

		for (int i = 0; i < this->vertexes.size(); i++)
			for (int j = 0; j < list[i].size(); j++)
				delete list[i][j];
	}

	int edgeCount ()
	{
		int edgeCount = 0;
		if (this->directed == true)
		{
			for (int i = 0; i < this->vertexes.size(); i++)
				edgeCount += list[i].size();

			return edgeCount;
		}

		int loopEdgeCount = 0;
		for (int i = 0; i < this->vertexes.size(); i++)
		{
			edgeCount += list[i].size();
			for (int j = 0; j < list[i].size(); j++)
			{
				if (list[i][j]->getBegin() == list[i][j]->getEnd())
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
		list.append(QList<Edge_t*>());
		return this->vertexes.last();
	}

	bool deleteVertex (Vertex_t* _pvertex1)
	{
		if(!this->belongs(_pvertex1))
			return false;

		int pos = _pvertex1->getIndex();

		for (int i = 0; i < this->vertexes.size(); i++)
			for (int j = 0; j < list[i].size(); j++)
				if (list[i][j]->isComingTo(_pvertex1) == true)
				{
					delete list[i][j];
					list[i].removeAt(j);
					break;
				}

		delete this->vertexes[pos];
		this->vertexes.removeOne(_pvertex1);
		list.removeAt(pos);

		for (; pos < this->vertexes.size(); pos++)
		{
			this->vertexes[pos]->setIndex(pos);
		}

		return true;
	}

	Edge_t* insertEdge (Vertex_t* _pvertex1, Vertex_t* _pvertex2)
	{
		if (!this->belongs(_pvertex1) || !this->belongs(_pvertex2))
			return NULL;

		int pos1 = _pvertex1->getIndex();
		for (int i = 0; i < list[pos1].size(); i++)
		{
			if (list[pos1][i]->isComingTo(_pvertex2) == true)
				return NULL;
		}

		list[pos1].append(new Edge_t(_pvertex1, _pvertex2));

		if (this->directed == false)
			list[_pvertex2->getIndex()].append(new Edge_t(_pvertex2, _pvertex1));
		return list[pos1].last();
	}

	bool deleteEdge (Vertex_t* _vertex1, Vertex_t* _vertex2)
	{
		if (!this->belongs(_vertex1) || !this->belongs(_vertex2))
			return false;

		int pos1 = _vertex1->getIndex();
		for (int i = 0; i < list[pos1].size(); i++)
		{
			if (list[pos1][i]->isComingTo(_vertex2) == true)
			{
				delete list[pos1][i];
				list[pos1].removeAt(i);

				if (this->directed == false)
				{
					int pos2 = _vertex2->getIndex();
					for (int j = 0; j < list[pos2].size(); j++)
					{
						if (list[pos2][j]->isComingTo(_vertex1) == true)
						{
							delete list[pos2][j];
							list[pos2].removeAt(j);
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
