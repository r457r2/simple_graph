#include <QCoreApplication>
#include <QString>
#include <iostream>

#include "VertexDescriptor.h"
#include "EdgeDescriptor.h"
#include "Graph.h"
#include "repeater.h"

// tests
#include "graphtest.h"

//tasks
#include "TaskOne.h"
#include "TaskTwo.h"

using namespace std;

const ReprType GRAPH_REPR = LIST_REPR;
typedef VertexDescriptor<string, int> Vertex_t;
typedef EdgeDescriptor<VertexDescriptor<string,int>,int,int> Edge_t;
typedef Graph<VertexDescriptor<string,int>, EdgeDescriptor<VertexDescriptor<string,int>,int,int> > TestGraph;

typedef Graph<VertexDescriptor<string,int>, EdgeDescriptor<VertexDescriptor<string,int>,int,int> > MyGraph;

//to do
//get vertex by it's index
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	MyGraph one(3,10,true);

	repeater<Vertex_t, Edge_t> rep(one);
	rep.repeat();
	TaskOne<VertexDescriptor<string,int>, EdgeDescriptor<VertexDescriptor<string,int>,int,int> > three;
return 0;
//	three.set(&one);
//	three.result();

//	VertexDescriptor<string,int>* other = *(one.vertexBegin());

//	TaskTwo<VertexDescriptor<string,int>, EdgeDescriptor<VertexDescriptor<string,int>,int,int> > two(&one, other);

//	two.result();

//	TestGraph g_small(3, 6, false, GRAPH_REPR);

//	TestGraph::VertexIterator vii = g_small.vertexBegin();
//	TestGraph::OutgoingEdgeIterator oii;
//	for(oii = g_small.outgoingEdgeBegin(*vii); oii != g_small.outgoingEdgeEnd(*vii); ++oii)
//		qDebug() << (*oii);

	return a.exec();
}
