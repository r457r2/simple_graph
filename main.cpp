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

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	MyGraph one(3,10,false,LIST_REPR);
	repeater<Vertex_t, Edge_t> rep(one);
	rep.repeat();

	return a.exec();
}
