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
//	qDebug() << "Hello world!";

	QList<int> list;
	QList<int>::Iterator one = list.begin();
	QList<int>::Iterator two = list.end();
	two++;
	if (one == two) qDebug() << "ok";

//	for(int i = 0; i < 4; i++)
//	{
//		qDebug() << i;
//		if(i != 4)
//			qDebug() << i;
//	}

	GraphTest::correctnessTest();
	GraphTest::iterTest();
	GraphTest::loadTest(10000, 90000, 10000);
	return 0;
	return app.exec();
}
