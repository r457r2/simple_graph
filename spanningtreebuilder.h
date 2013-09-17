#ifndef SPANNINGTREEBUILDER_H
#define SPANNINGTREEBUILDER_H

#include "Graph.h"
#include <QVector>
#include <iostream>

template <typename Vertex_t, typename Edge_t>
class SpanningTreeBuilder
{
private:
	struct Vertex
	{
		Vertex_t *vertex;
		Vertex_t *parent;
		int outdegree;
		enum Color
		{
			WHITE = 0,
			GRAY,
			BLACK
		} color;
	};

	typedef Graph<Vertex_t, Edge_t> SpanningTree;

	SpanningTree *graph;
	QVector<Edge_t *> res;
	QVector<Vertex *> vertexes;

	int getOutdegree(Vertex_t *v)
	{
		typename SpanningTree::OutgoingEdgeIterator iter;
		int outdegree = 0;
		for(iter = graph->outgoingEdgeBegin(v); iter != graph->outgoingEdgeEnd(v); ++iter)
			++outdegree;
		return outdegree;
	}

	Vertex* maxOutdegree()
	{
		typename QVector<Vertex *>::ConstIterator iter;
		static Vertex dummy = {NULL, NULL, 0, Vertex::BLACK};
		Vertex *max = &dummy;
		for(iter = vertexes.constBegin(); iter != vertexes.constEnd(); ++iter)
			if((*iter)->outdegree > max->outdegree && (*iter)->color == Vertex::WHITE)
				max = *iter;
		return max;
	}

	void bfs_visit(Vertex *vtx)
	{
		std::cout << "in " << vtx->vertex->getIndex()+1 << std::endl;
		vtx->color = Vertex::GRAY;
		QVector<Vertex *> queue;
		queue.push_back(vtx);

		while(queue.size())
		{
			Vertex *v = queue.front();
			std::cout << "	deq " << v->vertex->getIndex()+1 << std::endl;
			queue.pop_front();
			typename SpanningTree::OutgoingEdgeIterator iter;
			for(iter = graph->outgoingEdgeBegin(v->vertex); iter != graph->outgoingEdgeEnd(v->vertex); ++iter)
			{
				int idx = (*iter)->getEnd()->getIndex();
				std::cout << "		chk: " << idx+1;
				if(vertexes[idx]->color == Vertex::WHITE)
				{
					res.push_back(*iter);
					std::cout << "/enq " << std::endl;
					vertexes[idx]->color = Vertex::GRAY;
					queue.push_back(vertexes[idx]);
				}
				else
					std::cout << "/nope" << std::endl;
			}
			v->color = Vertex::BLACK;
		}
		std::cout << "out " << vtx->vertex->getIndex()+1 << std::endl << std::endl;
	}

	void solve()
	{
		typename SpanningTree::VertexIterator iter;
		for(iter = graph->vertexBegin(); iter != graph->vertexEnd(); ++iter)
		{
			Vertex *v = new Vertex;
			v->color = Vertex::WHITE;
			v->vertex = *iter;
			v->parent = NULL;
			v->outdegree = getOutdegree(*iter);
			vertexes.push_back(v);
		}

		Vertex *v;
		while((v = maxOutdegree())->color == Vertex::WHITE)
			bfs_visit(v);
	}

public:
	SpanningTreeBuilder()
	{
		graph = NULL;
	}

	SpanningTreeBuilder(SpanningTree *g)
	{
		graph = g;
		solve();
	}

	SpanningTreeBuilder(SpanningTreeBuilder &other)
	{
		// ???
	}

	~SpanningTreeBuilder()
	{
		typename QVector<Vertex *>::ConstIterator iter;
		for(iter = vertexes.constBegin(); iter != vertexes.constEnd(); ++iter)
			delete *iter;
	}

	void set(SpanningTree *g)
	{
		graph = g;
		solve();
	}

	void restart()
	{
		solve();
	}

	void result()
	{
		typename QVector<Edge_t *>::ConstIterator ri;
		for(ri = res.constBegin(); ri != res.constEnd(); ++ri)
		{
			std::cout << (*ri)->getBegin()->getIndex()+1
					  << "->" << (*ri)->getEnd()->getIndex()+1
						 << std::endl;
		}
	}
};

#endif // SPANNINGTREEBUILDER_H
