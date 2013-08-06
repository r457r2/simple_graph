#ifndef SIMPLE_GRAPH_H
#define SIMPLE_GRAPH_H
#include "graph.h"



template <typename Top, typename Edge>
class simple_graph
{
    private:

    public:
        simple_graph(){};//empty l-graph
        simple_graph(int V, bool Or, bool F){};//vithout edge
        simple_graph(int V, int E, bool Or, bool F){};//full
        simple_graph(simple_graph &one){};//copy
        ~simple_graph(){};
        int V(){};
        int E(){};
        bool Directed(){};
        bool Dense(){};
        float K(){};
        bool To_List_Graph(){};
        bool To_Matrix_Graph(){};
        bool Insert_V(){};
        bool Delete_V(){};
        bool Insert_E(){};
        bool Delete_E(){};

};

#endif // SIMPLE_GRAPH_H
