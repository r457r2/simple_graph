#ifndef GRAPH_H
#define GRAPH_H

template <typename Top, typename Edge>
class graph
{
    private:
        Top* vector;
        int lenth;
        bool orient;

    public:
        graph() : lenth(0)  {};
        graph(int num_of_top, bool _orient) {};
        ~graph() {};
};

#endif // GRAPH_H
