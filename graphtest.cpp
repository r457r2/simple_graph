#include "graphtest.h"

#include <QTime>
#include <iostream>
#include <assert.h>

#include "Graph.h"
#include "VertexDescriptor.h"
#include "EdgeDescriptor.h"

const ReprType GRAPH_REPR = MATRIX_REPR;
const bool DIRECTED = true;

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
	g.insertEdge(v1, v2);
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

	// TODO: transformation
}

void GraphTest::iterTest()
{
	{
		TestGraph g_big(1200, 9540, true, GRAPH_REPR);

		TestGraph::VertexIterator vi;
		int i = 0;
		for(vi = g_big.vertexBegin(); vi != g_big.vertexEnd(); ++vi, ++i)
			(*vi)->setData(65536);
		assert(i == 1200);

		TestGraph::EdgeIterator ei;
		i = 0;
		for(ei = g_big.edgeBegin();	ei != g_big.edgeEnd(); ++ei, ++i)
			(*ei)->setData(131052);
		assert(i == 9540);
	}

	TestGraph in_out(0, true, GRAPH_REPR);
	Vertex_t *v1 = in_out.insertVertex();
	Vertex_t *v2 = in_out.insertVertex();
	Vertex_t *v3 = in_out.insertVertex();
	Vertex_t *v4 = in_out.insertVertex();
	Vertex_t *v5 = in_out.insertVertex();
	Vertex_t *v6 = in_out.insertVertex();
	Vertex_t *v7 = in_out.insertVertex();
	Vertex_t *v8 = in_out.insertVertex();
	Vertex_t *v9 = in_out.insertVertex();

	// for outgoing e-iter
	in_out.insertEdge(v1, v2)->setData(12);
	in_out.insertEdge(v1, v7)->setData(17);
	in_out.insertEdge(v1, v5)->setData(15);
	in_out.insertEdge(v1, v9)->setData(19);
	in_out.insertEdge(v1, v4)->setData(14);
	in_out.insertEdge(v1, v6)->setData(16);
	in_out.insertEdge(v1, v1)->setData(11);

	// dummy
	in_out.insertEdge(v2, v3)->setData(23);
	in_out.insertEdge(v7, v6)->setData(76);
	in_out.insertEdge(v8, v6)->setData(86);
	in_out.insertEdge(v5, v3)->setData(53);
	in_out.insertEdge(v6, v2)->setData(62);
	in_out.insertEdge(v4, v4)->setData(44);
	in_out.insertEdge(v5, v4)->setData(54);
	in_out.insertEdge(v7, v7)->setData(77);
	in_out.insertEdge(v7, v7);
	in_out.insertEdge(v7, v2)->setData(72);
	in_out.insertEdge(v4, v6)->setData(46);
	in_out.insertEdge(v7, v4)->setData(74);
	in_out.insertEdge(v3, v8)->setData(38);

	// for incoming e-iter
	in_out.insertEdge(v2, v9)->setData(28);
	in_out.insertEdge(v5, v9)->setData(59);
	in_out.insertEdge(v8, v9)->setData(89);
	in_out.insertEdge(v3, v9)->setData(39);
	in_out.insertEdge(v4, v9)->setData(49);
	in_out.insertEdge(v9, v9)->setData(99);

	assert(in_out.vertexCount() == 9);
	assert(in_out.edgeCount() == 25);

	int i = 0;
	TestGraph::EdgeIterator ei2;
	for(ei2 = in_out.edgeBegin(); ei2 != in_out.edgeEnd(); ++ei2, ++i)
		(*ei2)->getData();
	assert(i == 25);

	i = 0;
	TestGraph::OutgoingEdgeIterator oi;
	for(oi = in_out.outgoingEdgeBegin(v1); oi != in_out.outgoingEdgeEnd(v1); ++oi, ++i)
		(*oi)->setWeight(3948212);
	assert(i == 7);

	i = 0;
	TestGraph::IncomingEdgeIterator ii;
	for(ii = in_out.incomingEdgeBegin(v9); ii != in_out.incomingEdgeEnd(v9); ++ii, ++i)
		(*ii)->setData(4987935);
	assert(i == 7);
}

void GraphTest::loadTest(int nvtxs, int nedges, int niters)
{
	std::cout << "Load test\n";
	std::cout << "Creating graph with " << nvtxs << " vertexes and "
			  << nedges << " edges... " << std::flush;
	QTime t;
	t.start();
	TestGraph g(nvtxs, nedges, DIRECTED, GRAPH_REPR);
	std::cout << "took " << t.elapsed() << " ms" << std::endl;
	assert(g.vertexCount() == nvtxs);
	assert(g.edgeCount() == nedges);

	t.start();
	std::cout << "Iterating over vertexes... " << std::flush;
	QList<Vertex_t *> vtxs;
	TestGraph::VertexIterator vi;
	for(vi = g.vertexBegin(); vi != g.vertexEnd(); ++vi)
		vtxs.push_back(*vi);
	std::cout << "took " << t.elapsed() << " ms" << std::endl;
	assert(vtxs.size() == nvtxs);

	t.currentTime();
	qsrand((uint) t.msec());

	std::cout << "Main loop start" << std::endl;

	t.start();
	for(int i = 0, prog = 0; i < niters; ++i)
	{
		Vertex_t *v1 = g.insertVertex();
		Vertex_t *v2 = g.insertVertex();
		int from, to;

		do
		{
			from = qrand() % nvtxs;
			to = qrand() % nvtxs;
		} while(!g.insertEdge(vtxs[from], vtxs[to]));

		g.deleteEdge(v1, v2);
		g.deleteEdge(vtxs[from], vtxs[to]);
		g.deleteVertex(v1);
		g.deleteVertex(v2);

		if(100*i/niters != prog)
		{
			prog = 100*i/niters;
			std::cout << prog << "%" << std::endl;
		}
	}
	std::cout << "took " << t.elapsed() << " ms" << std::endl;
}
