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

	QList<QList<int> > two;
	two.append(QList<int>());
	two.append(QList<int>());
	int* c = new int(1);
	two[0].append((*c)++);
	two[0].append((*c)++);
	two[0].append((*c)++);
	two[1].append((*c)++);
	two[1].append((*c)++);
	delete c;

	qDebug() << two;
	qDebug() << two[1][1];
	return 0;
	return app.exec();
}
