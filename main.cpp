#include <QString>
#include <QtGui>
#include <QApplication>
#include "vertix_desc.h"
#include "edge_desc.h"
#include "simple_graph.h"

using namespace std;

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

    simple_graph<vertix_desc<string,int>, edge_desc<vertix_desc<string,int>,int,int> > one;
	qDebug() << "Hello world!";

	return app.exec();
}
