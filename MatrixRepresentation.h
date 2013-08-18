#ifndef MATRIX_REPRESENTATION_H
#define MATRIX_REPRESENTATION_H
#include "Representation.h"

template <typename Vertex_t, typename Edge_t>
class Graph;

template <typename Vertex_t, typename Edge_t>
class MatrixRepresentation: public Representation<Vertex_t, Edge_t>
{
private:
	friend class Graph<Vertex_t, Edge_t>;
	QList<QList<Edge_t*> > matrix;

public:
	MatrixRepresentation (bool isdirected = false) : Representation<Vertex_t, Edge_t>::directed(isdirected) {}

	MatrixRepresentation (int numberOfVertex, bool isdirected) : Representation<Vertex_t, Edge_t>::directed(isdirected)
	{
		for(int i = 0; i < numberOfVertex; i++)
			insertVertex();
	}

	MatrixRepresentation (int numberOfVertex, int numberOfEdge, bool isdirected)
		: Representation<Vertex_t, Edge_t>::directed(isdirected)
	{
		// Create graph with given number of vertexes and given number of random
		// edges
		for(int i = 0; i < numberOfVertex; i++)
			insertVertex();

		int maxEdgesCount = this->maxEdgesCount();
		if(numberOfEdge > maxEdgesCount)
			numberOfEdge = maxEdgesCount;

		QTime t = QTime::currentTime();
		qsrand((uint) t.msec());

		int edgesCreated = 0;
		while(edgesCreated < numberOfEdge)
		{
			int from = qrand() % numberOfVertex;
			int to   = qrand() % numberOfVertex;

			if(insertEdge(this->vertexes[from], this->vertexes[to]))
				edgesCreated++;
		}
	}

	MatrixRepresentation (MatrixRepresentation &one)
	{
		// Copy all vertexes
		// Copy matrix: if null, copy null
		// else create new edge, fill with appropriate data
		this->directed = one.directed;

		foreach(Vertex_t *v, one.vertexes)
			this->vertexes.append(new Vertex_t(*v));

		for(int i = 0; i < one.matrix.count(); i++)
		{
			matrix.append(QList<Edge_t *>());
			for(int j = 0; j < one.matrix.count(); j++)
			{
				if(one.matrix[i][j] == NULL)
					matrix[i].append(NULL);
				else
				{
					Edge_t *e = new Edge_t(this->vertexes[one.matrix[i][j]->getBegin()->getIndex()],
							this->vertexes[one.matrix[i][j]->getEnd()->getIndex()],
							one.matrix[i][j]->getWeight(),
							one.matrix[i][j]->getData());
					matrix[i].append(e);
				}
			}
		}
	}

	~MatrixRepresentation ()
	{
		// Delete all, what new'ed: vertexes and edges
		foreach(Vertex_t *v, this->vertexes)
			delete v;

		foreach(const QList<Edge_t *> row, matrix)
			foreach(Edge_t *e, row)
				if(e)
					delete e;
	}

	int edgeCount ()
	{
		// As there is always only one descriptor for loop edge,
		// not dividing loops count by 2
		int count = 0;
		int loops = 0;
		int vtx_cnt = matrix.count();

		for(int i = 0; i < vtx_cnt; i++)
		{
			for(int j = 0; j < vtx_cnt; j++)
			{
				if(i == j && matrix[i][j])
					loops++;
				else if(matrix[i][j])
					count++;
			}
		}
		if(this->directed)
			return count/2 + loops;
		else
			return count + loops;
	}

	Vertex_t* insertVertex ()
	{
		// Insert vertex into vertexes[]
		// Insert row and col into repr matrix
		// Initialize new row and col with NULL
		Vertex_t *vtx = new Vertex_t();
		this->vertexes.append(vtx);
		int index = this->vertexes.count() - 1;

		matrix.append(QList<Edge_t *>());
		for(int i = 0; i < index; i++)
		{
			matrix[i].append(NULL);
			if(i != index)
				matrix[index].append(NULL);
		}

		vtx->setIndex(index);
		return vtx;
	}

	bool deleteVertex (Vertex_t* v)
	{
		// Remove vertex from vertexes
		// Regen indexes of remaining vertexes
		// Remove all edges related to vertex
		// Remove row and col from matrix
		if(!belongs(v))
			return false;
		int index = v->getIndex();

		delete this->vertexes[index];
		this->vertexes.removeAt(index);
		for(int i = index; i < this->vertexes.count(); i++)
			this->vertexes[i]->setIndex(i);

		for(int i = 0; i < matrix.count(); i++)
		{
			if(matrix[i][index])
				delete matrix[i][index];
			if(i != index)
			{
				matrix[i].removeAt(index);
				if(matrix[index][i])
					delete matrix[index][i];
			}
		}
		matrix.removeAt(index);
		return true;
	}

	Edge_t* insertEdge (Vertex_t* v1, Vertex_t* v2)
	{
		// Check if vertexes belongs to graph
		// And there is no such edge
		int idx1 = v1->getIndex();
		int idx2 = v2->getIndex();
		if(!belongs(v1) || !belongs(v2) || matrix[idx1][idx2] != NULL)
			return NULL;

		Edge_t *e = new Edge_t;
		e->setBegin(v1);
		e->setEnd(v2);
		matrix[idx1][idx2] = e;
		if(this->directed)
		{
			Edge_t *e_reversed = new Edge_t;
			e_reversed->setBegin(v2);
			e_reversed->setEnd(v1);
			matrix[idx2][idx1] = e_reversed;
		}
		return e;
	}

	bool deleteEdge (Vertex_t* v1, Vertex_t* v2)
	{
		// Check if vertexes belongs to graph and there is an edge
		// Remove direct edge
		// If graph is directed, remove reverse edge
		int idx1 = v1->getIndex();
		int idx2 = v2->getIndex();
		if(!belongs(v1) || !belongs(v2) || matrix[idx1][idx2] == NULL)
			return false;

		delete matrix[idx1][idx2];
		matrix[idx1][idx2] = NULL;
		if(this->directed)
		{
			delete matrix[idx2][idx1];
			matrix[idx2][idx1] = NULL;
		}
	}
};

#endif // MATRIX_REPRESENTATION_H
