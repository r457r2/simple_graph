#include "graphtest.h"

#include <iostream>
#include <assert.h>

#include "Graph.h"
#include "VertexDescriptor.h"
#include "EdgeDescriptor.h"

#include <QDebug>

const ReprType GRAPH_REPR = LIST_REPR;

typedef VertexDescriptor<int, int> Vertex_t;
typedef EdgeDescriptor<Vertex_t, int, int> Edge_t;
typedef Graph<Vertex_t, Edge_t> TestGraph;


void GraphTest::correctnessTest()
{
	// Check that interface behaves as expected
	//TestGraph g;
	TestGraph g(0, false, GRAPH_REPR);

	// empty graph
	assert(g.vertexCount() == 0);
	assert(g.edgeCount() == 0);

	// delete out of range foreign vertex
	Vertex_t v_dummy(0, 0, 150);
	assert(g.deleteVertex(&v_dummy) == false);
	assert(g.vertexCount() == 0);
	assert(g.edgeCount() == 0);

	// insert vertexes
	v_dummy.setIndex(0);
	Vertex_t *v1 = g.insertVertex();
	Vertex_t *v2 = g.insertVertex();
	assert(g.vertexCount() == 2);
	assert(g.edgeCount() == 0);

	// insert edge
	Edge_t *e1 = g.insertEdge(v1, v2);
	assert(g.vertexCount() == 2);
	assert(g.edgeCount() == 1);

	// override edge
	assert(g.insertEdge(v1, v2) == NULL);
	assert(g.vertexCount() == 2);
	assert(g.edgeCount() == 1);

	// delete dummy vertex
	assert(g.deleteVertex(&v_dummy) == false);
	assert(g.vertexCount() == 2);
	assert(g.edgeCount() == 1);

	// delete edge (foreign vertexes)
	Vertex_t v_dummy2(1, 1, 1);
	assert(g.deleteEdge(&v_dummy, &v_dummy2) == false);
	assert(g.vertexCount() == 2);
	assert(g.edgeCount() == 1);

	//delete edge (not exists, but v-s are owned by g)
	Vertex_t *v3 = g.insertVertex();
	assert(g.deleteEdge(v2, v3) == false);
	assert(g.vertexCount() == 3);
	assert(g.edgeCount() == 1);

	// new edge
	Vertex_t *v4 = g.insertVertex();
	assert(g.insertEdge(v4, v3) != NULL);
	assert(g.vertexCount() == 4);
	assert(g.edgeCount() == 2);

	// delete vertex with correspondent edge
	assert(g.deleteVertex(v3) == true);
	assert(g.vertexCount() == 3);
	assert(g.edgeCount() == 1);

	// delete edge
	assert(g.deleteEdge(v1, v2) == true);
	assert(g.vertexCount() == 3);
	assert(g.edgeCount() == 0);

	// delete rest
	assert(g.deleteVertex(v1) == true);
	assert(g.deleteVertex(v2) == true);
	assert(g.deleteVertex(v4) == true);
	assert(g.vertexCount() == 0);
	assert(g.edgeCount() == 0);

	//other ctors
	TestGraph g_vertexes(50, true, GRAPH_REPR);
	assert(g_vertexes.vertexCount() == 50);
	assert(g_vertexes.edgeCount() == 0);

	TestGraph g_edges(400, 800, true, GRAPH_REPR);
	assert(g_edges.vertexCount() == 400);
	assert(g_edges.edgeCount() == 800);

}

void GraphTest::loadTest()
{

}
