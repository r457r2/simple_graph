#include <QString>
#include <QtGui>
#include <QApplication>
#include "VertexDescriptor.h"
#include "EdgeDescriptor.h"
#include "Graph.h"

// tests
#include "graphtest.h"

//tasks
#include "TaskOne.h"
#include "TaskTwo.h"

using namespace std;

typedef Graph<VertexDescriptor<string,int>, EdgeDescriptor<VertexDescriptor<string,int>,int,int> > MyGraph;


const ReprType GRAPH_REPR = LIST_REPR;
typedef VertexDescriptor<string, int> Vertex_t;
typedef EdgeDescriptor<VertexDescriptor<string,int>,int,int> Edge_t;
typedef Graph<VertexDescriptor<string,int>, EdgeDescriptor<VertexDescriptor<string,int>,int,int> > TestGraph;

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	MyGraph one(3,6);

	TaskOne<VertexDescriptor<string,int>, EdgeDescriptor<VertexDescriptor<string,int>,int,int> > three(&one);

	three.result();

	//VertexDescriptor<string,int>* other = *(one.vertexBegin());

	//TaskTwo<VertexDescriptor<string,int>, EdgeDescriptor<VertexDescriptor<string,int>,int,int> > two(&one, other);

	//two.result();

//	TestGraph g_small(3, 6, false, GRAPH_REPR);

//	TestGraph::VertexIterator vii = g_small.vertexBegin();
//	TestGraph::OutgoingEdgeIterator oii;
//	for(oii = g_small.outgoingEdgeBegin(*vii); oii != g_small.outgoingEdgeEnd(*vii); ++oii)
//		qDebug() << (*oii);






	return 0;
	return app.exec();
}
