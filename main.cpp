#include <QString>
#include <QtGui>
#include <QApplication>
#include "VertexDescriptor.h"
#include "EdgeDescriptor.h"
#include "Graph.h"

// tests
#include "graphtest.h"

using namespace std;

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	//Graph<VertexDescriptor<string,int>, EdgeDescriptor<VertexDescriptor<string,int>,int,int> > one;
	qDebug() << "Hello world!";

	QList<int> list;
	QList<int>::Iterator one = list.begin();
	QList<int>::Iterator two = list.end();
	two++;
	if (one == two) qDebug() << "ok";
	return 0;
	GraphTest::correctnessTest();
	GraphTest::loadTest();

	return app.exec();
}
