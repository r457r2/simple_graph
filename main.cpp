#include <QString>
#include <QtGui>
#include <QApplication>
#include "VertexDescriptor.h"
#include "EdgeDescriptor.h"
#include "Graph.h"
// tests
#include "graphtest.h"
//tasks
#include "TaskTwo.h"

using namespace std;

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	Graph<VertexDescriptor<string,int>, EdgeDescriptor<VertexDescriptor<string,int>,int,int> > one(6,14);

	VertexDescriptor<string,int>* other = *(one.vertexBegin());

	TaskTwo<VertexDescriptor<string,int>, EdgeDescriptor<VertexDescriptor<string,int>,int,int> > two(&one, other);

	return 0;
	return app.exec();
}
