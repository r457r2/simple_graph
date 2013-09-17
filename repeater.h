#ifndef REPEATER_H
#define REPEATER_H

#include "VertexDescriptor.h"
#include "EdgeDescriptor.h"
#include "Graph.h"
#include "iostream"

#include "TaskOne.h"
#include "TaskTwo.h"

using namespace std;

template <typename Vertex_t, typename Edge_t>
class repeater
{
private:
	TaskOne<Vertex_t, Edge_t> one;
	TaskTwo<Vertex_t, Edge_t> two;
	Graph<Vertex_t, Edge_t>& graph;

	void showVertexes ()
	{
		cout << "Vertexes:" << endl;
		typename Graph<Vertex_t,Edge_t>::VertexIterator viter = graph.vertexBegin();
		while (viter != graph.vertexEnd())
		{
			cout << (*viter)->getIndex() << "   " << (*viter) << "   " << (*viter)->getName()<< endl;
			++viter;
		}
		cout << endl << endl;
	}

	Vertex_t* getVertex (int index)
	{
		if (index >= graph.vertexCount())
			return NULL;

		typename Graph<Vertex_t,Edge_t>::VertexIterator viter = graph.vertexBegin();
		while (viter != graph.vertexEnd())
		{
			if ((*viter)->getIndex() == index)
				return (*viter);

			++viter;
		}
	}

	void showEdges ()
	{
		int index = 0;
		cout << "Edges:" << endl;
		typename Graph<Vertex_t,Edge_t>::EdgeIterator viter = graph.edgeBegin();
		while (viter != graph.edgeEnd())
		{
			cout << index << ":   " << (*viter) << "   " << (*viter)->getWeight() << "   ";
			if (graph.isDirected() == true)
			{
				cout << (*viter)->getBegin()->getIndex() << "--->" << (*viter)->getEnd()->getIndex() << endl;
				index++;
			}
			else if ((*viter)->getBegin() <= (*viter)->getEnd())
				 {
					 cout << (*viter)->getBegin()->getIndex() << "----" << (*viter)->getEnd()->getIndex() << endl;
					 index++;
				 }

			++viter;
		}
		cout << endl << endl;
	}

	void showMenu ()
	{
		cout << "0 - Printed whole struct          " << endl
			 << "1 - Add vertex                    " << endl
			 << "2 - Delete vertex                 " << endl
			 << "3 - Add edge                      " << endl
			 << "4 - Delete edge                   " << endl
			 << "5 - Get edge                      " << endl
			 << "6 - Get density                   " << endl
			 << "7 - Transform to list-graph       " << endl
			 << "8 - Transform to matrix-graph     " << endl
			 << "9 - Get type                      " << endl
			 << "10 - Is directed?                 " << endl
			 << "11 - Get edge count               " << endl
			 << "12 - Get vertex count             " << endl
			 << "13 - Get vertex iterator          " << endl
			 << "14 - Get edge iterator            " << endl
			 << "15 - Get outgoing edge iterator   " << endl
			 << "16 - Get incoming edge iterator   " << endl
			 << "17 - Solve first task             " << endl
			 << "18 - Show first task result       " << endl
			 << "19 - Solve second task            " << endl
			 << "20 - Show second task result      " << endl
			 << "21 - Repeat this menu             " << endl
			 << "22 - Finish work                  " << endl << endl;
	}

public:
	repeater (Graph<Vertex_t, Edge_t>& grph) : graph(grph)
	{
		qsrand(time_t(NULL));
		if (graph.vertexCount() != 0)
		{
			for (typename Graph<Vertex_t, Edge_t>::EdgeIterator eiter = graph.edgeBegin(); eiter != graph.edgeEnd(); ++eiter)
			{
				int weight = qrand() % graph.edgeCount();
				if ((qrand() % 5) == 0)
						weight = (-1) * weight;

				(*eiter)->setWeight(weight);
			}
		}
	}

	void repeat()
	{
		if ((graph.isDirected() == false) && (graph.vertexCount() != 0))
			one.set(&graph);
		if ((graph.isDirected() == true) && (graph.vertexCount() != 0))
			two.set(&graph, *(graph.vertexBegin()));

		bool cont = true;

		showMenu();

		while(cont)
		{
			int choise;
			cout << "Your choise: ";
			cin >> choise;
			cout << endl;

			switch(choise)
			{
			case 0:
			{
				if (graph.vertexCount() == 0)
				{
					cout << "Graph is empty!" << endl << endl;
					break;
				}
				showVertexes();
				showEdges();
				break;
			}

			case 1:
			{graph.insertVertex(); break;}

			case 2:
			{
				cout << "Insert vertex index: ";
				int index;
				cin >> index;
				Vertex_t* vrt = getVertex(index);
				if (vrt != NULL)
				{
					graph.deleteVertex(vrt);
					cout << "Success." << endl << endl;
					break;
				}
				cout << "Couldn't delete." << endl << endl;
				break;
			}

			case 3:
			{
				cout << "Insert from and to vertexes indexes: ";
				int index1,	index2;
				cin >> index1 >> index2;
				Vertex_t* fromvrt = getVertex(index1);
				Vertex_t* tovrt = getVertex(index2);
				if ((fromvrt != NULL) && (tovrt != NULL))
				{
					int weight = qrand() % graph.edgeCount();
					if ((qrand() % 5) == 0)
							weight = (-1) * weight;
					(graph.insertEdge(fromvrt, tovrt))->setWeight(weight);
					cout << "Success."<< endl << endl;
					break;
				}
				cout << "Couldn't add." << endl << endl;
				break;
			}

			case 4:
			{
				cout << "Insert from and to vertexes indexes: ";
				int index1,	index2;
				cin >> index1 >> index2;
				Vertex_t* fromvrt = getVertex(index1);
				Vertex_t* tovrt = getVertex(index2);
				if ((fromvrt != NULL) && (tovrt != NULL))
				{
					graph.deleteEdge(fromvrt, tovrt);
					cout << "Success." << endl << endl;
					break;
				}
				cout << "Couldn't delete." << endl << endl;
				break;
			}

			case 5:
			{
				cout << "Insert from and to vertexes indexes: ";
				int index1,	index2;
				cin >> index1 >> index2;
				Vertex_t* fromvrt = getVertex(index1);
				Vertex_t* tovrt = getVertex(index2);
				if ((fromvrt == NULL) || (tovrt == NULL))
				{
					cout << "Wrong vertexes." << endl << endl;
					break;
				}

				Edge_t* edge = graph.getEdge(fromvrt, tovrt);
				if (edge == NULL)
				{
					cout << "No edge." << endl << endl;
					break;
				}

				if (graph.isDirected() == true)
					cout << edge << "   " << edge->getWeight()  << "   " << index1 << "--->" << index2 << endl << endl;
				else
					cout << edge << "   " << edge->getWeight()  << "   " << index1 << "----" << index2 << endl << endl;

				break;
			}

			case 6:
			{cout << "Density coefficent: " << graph.getDensity() << endl << endl; break;}

			case 7:
			{
				graph.toListGraph();
				cout << "Transformation to List compleate." << endl << endl;
				break;
			}

			case 8:
			{
				graph.toMatrixGraph();
				cout << "Transformation to Matrix compleate." << endl << endl;
				break;
			}

			case 9:
			{
				if (graph.getType() == LIST_REPR)
					cout << "List representation" << endl << endl;
				else
					cout << "Matrix representation" << endl << endl;
				break;
			}

			case 10:
			{
				if (graph.isDirected() == true)
					cout << "Graph is directed." << endl << endl;
				else
					cout << "Graph is not directed." << endl << endl;
				break;
			}

			case 11:
			{cout << "Edge count: " << graph.edgeCount() << endl << endl; break;}

			case 12:
			{cout << "Vertex count: " << graph.vertexCount() << endl << endl; break;}

			case 13:
			{
				if (graph.vertexCount() == 0)
				{
					cout << "Could'n set iterator." << endl;
					break;
				}

				typename Graph<Vertex_t,Edge_t>::VertexIterator viter = graph.vertexBegin();
				bool contv = true;
				while(contv)
				{
					cout << endl
						 << "0 - Increment vertex iterator" << endl
						 << "1 - Take iterator" << endl
						 << "2 - Set vertex name" << endl
						 << "3 - Set vertex data" << endl
						 << "4 - Finish work" << endl  << endl;

					int vchoise;
					cout << "Your choise: ";
					cin >> vchoise;
					cout << endl;

					switch(vchoise)
					{
					case 0:
					{
						if (viter == graph.vertexEnd())
							break;

						++viter;
						break;
					}

					case 1:
					{
						if (viter == graph.vertexEnd())
						{
							cout << "Couldn't get data." << endl;
							break;
						}
						cout << (*viter) << "   "
							 << (*viter)->getIndex() << "   "
							 << (*viter)->getName() << "   "
							 << (*viter)->getData() << endl << endl;

						break;
					}

					case 2:
					{
						if (viter == graph.vertexEnd())
						{
							cout << "Couldn't set vertex name." << endl << endl;
							break;
						}
						cout << "Insert vertex name: ";
						cin >> (*viter)->getSName();
						cout << endl;
						break;
					}

					case 3:
					{
						if (viter == graph.vertexEnd())
						{
							cout << "Couldn't set vertex data." << endl << endl;
							break;
						}

						cout << "Insert vertex data: ";
						cin >> (*viter)->getSData();
						cout << endl;
						break;
					}

					case 4:
					{
						cout  << endl << endl;
						contv = false;
						showMenu();
						break;
					}

					default: {}
					}
				}
				break;
			}

			case 14:
			{
				if (graph.edgeCount() == 0)
				{
					cout << "Could'n set iterator." << endl << endl;
					break;
				}

				typename Graph<Vertex_t,Edge_t>::EdgeIterator eiter = graph.edgeBegin();
				bool conte = true;
				while(conte)
				{
					cout << endl
						 << "0 - Increment edge iterator" << endl
						 << "1 - Take iterator" << endl
						 << "2 - Set edge weight" << endl
						 << "3 - Set edge data" << endl
						 << "4 - Finish work" << endl << endl;

					int echoise;
					cout << "Your choise: ";
					cin >> echoise;
					cout << endl;

					switch(echoise)
					{
					case 0:
					{
						if (eiter == graph.edgeEnd())
							break;

						++eiter;
						break;
					}

					case 1:
					{
						if (eiter == graph.edgeEnd())
						{
							cout << "Couldn't get data." << endl << endl;
							break;
						}

						if (graph.isDirected() == true)
							cout << (*eiter) << "   "
								 << (*eiter)->getWeight() << "   "
								 << (*eiter)->getBegin()->getIndex() << "--->" << (*eiter)->getEnd()->getIndex() << "   "
								 << (*eiter)->getData() << endl << endl;
						else
							cout << (*eiter) << "   "
								 << (*eiter)->getWeight() << "   "
								 << (*eiter)->getBegin()->getIndex() << "----" << (*eiter)->getEnd()->getIndex() << "   "
								 << (*eiter)->getData() << endl << endl;
						break;
					}

					case 2:
					{
						if (eiter == graph.edgeEnd())
						{
							cout << "Couldn't set edge weight." << endl << endl;
							break;
						}
						cout << "Insert edge weight: ";
						cin >> (*eiter)->getSWeight();
						cout  << endl;
						break;
					}

					case 3:
					{
						if (eiter == graph.edgeEnd())
						{
							cout << "Couldn't set edge data." << endl << endl;
							break;
						}

						cout << "Insert edge data: ";
						cin >> (*eiter)->getSData();
						cout  << endl;
						break;
					}

					case 4:
					{
						cout  << endl << endl;
						conte = false;
						showMenu();
						break;
					}

					default: {}
					}
				}
				break;
			}

			case 15:
			{
				if (graph.edgeCount() == 0)
				{
					cout << "Could'n set iterator." << endl << endl;
					break;
				}

				showVertexes();
				cout << "Select vertex: ";
				int vindex;
				cin >> vindex;
				if (vindex >= graph.vertexCount())
				{
					cout << "Vrong vertex." << endl << endl;
					break;
				}

				typename Graph<Vertex_t,Edge_t>::OutgoingEdgeIterator oeiter = graph.outgoingEdgeBegin(getVertex(vindex));
				bool contoe = true;
				while(contoe)
				{
					cout << endl
						 << "0 - Increment outgoing edge iterator" << endl
						 << "1 - Take iterator" << endl
						 << "2 - Set edge weight" << endl
						 << "3 - Set edge data" << endl
						 << "4 - Finish work" << endl << endl;

					int echoise;
					cout << "Your choise: ";
					cin >> echoise;
					cout << endl << endl;

					switch(echoise)
					{
					case 0:
					{
						if (oeiter == graph.outgoingEdgeEnd(getVertex(vindex)))
							break;

						++oeiter;
						break;
					}

					case 1:
					{
						if (oeiter == graph.outgoingEdgeEnd(getVertex(vindex)))
						{
							cout << "Couldn't get data." << endl << endl;
							break;
						}

						if (graph.isDirected() == true)
							cout << (*oeiter) << "   "
								 << (*oeiter)->getWeight() << "   "
								 << (*oeiter)->getBegin()->getIndex() << "--->" << (*oeiter)->getEnd()->getIndex() << "   "
								 << (*oeiter)->getData() << endl << endl;
						else
							cout << (*oeiter) << "   "
								 << (*oeiter)->getWeight() << "   "
								 << (*oeiter)->getBegin()->getIndex() << "----" << (*oeiter)->getEnd()->getIndex() << "   "
								 << (*oeiter)->getData() << endl << endl;
						break;
					}

					case 2:
					{
						if (oeiter == graph.outgoingEdgeEnd(getVertex(vindex)))
						{
							cout << "Couldn't set edge weight." << endl << endl;
							break;
						}
						cout << "Insert edge weight: ";
						cin >> (*oeiter)->getSWeight();
						cout << endl;
						break;
					}

					case 3:
					{
						if (oeiter == graph.outgoingEdgeEnd(getVertex(vindex)))
						{
							cout << "Couldn't set edge data." << endl << endl;
						}

						cout << "Insert edge data: ";
						cin >> (*oeiter)->getSData();
						cout  << endl;
						break;
					}

					case 4:
					{
						cout  << endl << endl;
						contoe = false;
						showMenu();
						break;
					}

					default: {}
					}
				}
				break;
			}

			case 16:
			{
				if (graph.edgeCount() == 0)
				{
					cout << "Could'n set iterator." << endl;
					break;
				}

				showVertexes();
				cout << "Select vertex: ";
				int vindex;
				cin >> vindex;
				if (vindex >= graph.vertexCount())
				{
					cout << "Vrong vertex." << endl;
					break;
				}

				typename Graph<Vertex_t,Edge_t>::IncomingEdgeIterator ieiter = graph.incomingEdgeBegin(getVertex(vindex));
				bool contie = true;
				while(contie)
				{
					cout << endl
						 << "0 - Increment incoming edge iterator" << endl
						 << "1 - Take iterator" << endl
						 << "2 - Set edge weight" << endl
						 << "3 - Set edge data" << endl
						 << "4 - Finish work" << endl;

					int echoise;
					cout << "Your choise: ";
					cin >> echoise;
					cout << endl << endl;

					switch(echoise)
					{
					case 0:
					{
						if (ieiter == graph.incomingEdgeEnd(getVertex(vindex)))
							break;

						++ieiter;
						break;
					}

					case 1:
					{
						if (ieiter == graph.incomingEdgeEnd(getVertex(vindex)))
						{
							cout << "Couldn't get data." << endl;
							break;
						}

						if (graph.isDirected() == true)
							cout << (*ieiter) << "   "
								 << (*ieiter)->getWeight() << "   "
								 << (*ieiter)->getBegin()->getIndex() << "--->" << (*ieiter)->getEnd()->getIndex() << "   "
								 << (*ieiter)->getData() << endl;
						else
							cout << (*ieiter) << "   "
								 << (*ieiter)->getWeight() << "   "
								 << (*ieiter)->getBegin()->getIndex() << "----" << (*ieiter)->getEnd()->getIndex() << "   "
								 << (*ieiter)->getData() << endl;
						break;
					}

					case 2:
					{
						if (ieiter == graph.incomingEdgeEnd(getVertex(vindex)))
						{
							cout << "Couldn't set edge weight." << endl;
							break;
						}
						cout << "Insert edge weight: ";
						cin >> (*ieiter)->getSWeight();
						break;
					}

					case 3:
					{
						if (ieiter == graph.incomingEdgeEnd(getVertex(vindex)))
						{
							cout << "Couldn't set edge data." << endl;
							break;
						}

						cout << "Insert edge data: ";
						cin >> (*ieiter)->getSData();
						break;
					}

					case 4:
					{
						cout  << endl << endl;
						contie = false;
						showMenu();
						break;
					}

					default: {}
					}
				}
				break;
			}

			case 17:
			{
				if ((graph.isDirected() == true) || (graph.vertexCount() == 0))
				{
					cout << "Wrong graph." << endl << endl;
					break;
				}
				one.restart();
				cout << endl;
				break;
			}

			case 18:
			{
				if ((graph.isDirected() == true) || (graph.vertexCount() == 0))
				{
					cout << "Wrong graph." << endl << endl;
					break;
				}
				one.result();
				cout << endl;
				break;
			}

			case 19:
			{
				if ((graph.isDirected() == false) || (graph.vertexCount() == 0))
				{
					cout << "Wrong graph." << endl << endl;
					break;
				}

				showVertexes();
				cout << "Select vertex: ";
				int index;
				cin >> index;
				cout << endl;
				if (index >= graph.vertexCount())
				{
					cout << "Wrong index." << endl << endl;
					break;
				}

				two.restart(getVertex(index));
				break;
			}

			case 20:
			{
				if ((graph.isDirected() == false) || (graph.vertexCount() == 0))
				{
					cout << "Wrong graph." << endl << endl;
					break;
				}
				two.result();
				cout << endl;
				break;
			}

			case 21:
			{showMenu(); break;}

			case 22:
			{cont = false; break;}

			default: {}
			}
		}
	}
};

#endif // REPEATER_H
