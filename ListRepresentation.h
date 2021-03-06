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
		for (int i = 0; i < numberOfVertex; i++)
			this->insertVertex();

		if (numberOfEdge > this->maxEdgesCount())
			numberOfEdge = this->maxEdgesCount();

		qsrand(time_t(NULL));
		for (int edgesInserted = 0; edgesInserted < numberOfEdge;)
		{
			int posBegin = qrand() % numberOfVertex;
			int posEnd = qrand() % numberOfVertex;

			if (insertEdge(this->vertexes[posBegin], this->vertexes[posEnd]) != NULL)
				edgesInserted++;
		}
	}

	ListRepresentation (ListRepresentation &other)
		: Representation<Vertex_t, Edge_t>(other)
	{
		this->directed = other.directed;

		for (int i = 0; i < other.vertexCount(); i++)
		{
			this->vertexes.append(new Vertex_t(*(other.vertexes[i])));
		}

		for (int i = 0; i < other.vertexCount(); i++)
		{
			for (int j = 0; j < other.list[i].size(); j++)
			{
				this->list[i].append(new Edge_t(
										this->vertexes[other.list[i][j]->getBegin()->getIndex()],
										this->vertexes[other.list[i][j]->getEnd()->getIndex()],
										other.list[i][j]->getWeight(),
										other.list[i][j]->getData()));
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
		int uidx = 0;
		if(this->vertexes.count())
			uidx = this->vertexes.last()->getUserIndex() + 1;
		this->vertexes.append(new Vertex_t());
		this->vertexes.last()->setIndex(this->vertexes.size() - 1);
		this->vertexes.last()->setUserIndex(uidx);
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
			if (_pvertex1 != _pvertex2)
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

	Edge_t* getEdge (Vertex_t* _pvertex1, Vertex_t* _pvertex2)
	{
		if (!(this->belongs(_pvertex1) && this->belongs(_pvertex2)))
			return NULL;

		Edge_t* tmp = NULL;
		for (int i = 0; i < this->list[_pvertex1->getIndex()].size(); i++)
		{
			if ((this->list[_pvertex1->getIndex()][i])->getEnd() == _pvertex2)
			{
				tmp = this->list[_pvertex1->getIndex()][i];
				break;
			}
		}

		return tmp;
	}
};

#endif // LIST_REPRESENTATION_H
