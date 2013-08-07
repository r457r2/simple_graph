#include <QString>
#include <QtGui>
#include <QApplication>
#include "VertexDescriptor.h"
#include "EdgeDescriptor.h"
#include "Graph.h"

using namespace std;

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	Graph<VertexDescriptor<string,int>, EdgeDescriptor<VertexDescriptor<string,int>,int,int> > one;
	qDebug() << "Hello world!";

	return app.exec();
}
