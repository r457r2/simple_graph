#include "graphtest.h"

#include <iostream>
#include <assert.h>

#include "Graph.h"
#include "VertexDescriptor.h"
#include "EdgeDescriptor.h"

const ReprType GRAPH_REPR = LIST_REPR;

typedef VertexDescriptor<int, int> Vertex_t;
typedef EdgeDescriptor<Vertex_t, int, int> Edge_t;
typedef Graph<Vertex_t, Edge_t> TestGraph;


void GraphTest::correctnessTest()
{
	// Check that interface behaves as expected
	TestGraph g;
	// empty graph
	assert(g.vertexCount() == 0);
	assert(g.edgeCount() == 0);

	// delete out of range foreign vertex
	Vertex_t v_dummy(0, 0, 150);
	assert(g.deleteVertex(&v_dummy) == false);

	// insert edge and do as before
	v_dummy.setIndex(0);
	Vertex_t *v1 = g.insertVertex();
	Vertex_t *v2 = g.insertVertex();
	assert(g.deleteVertex(&v_dummy) == false);

	// delete wrong edge
	Edge_t *e1 = g.insertEdge(v1, v2);
	Vertex_t v_dummy2(1, 1, 1);
	assert(g.deleteEdge(&v_dummy, &v_dummy2) == false);

}

void GraphTest::loadTest()
{

}
