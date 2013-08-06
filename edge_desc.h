#ifndef DESCRIPTOR_OF_THE_EDGE_H
#define DESCRIPTOR_OF_THE_EDGE_H

template <typename Vertix, typename Weight, typename Data>
class edge_desc
{
    private:
        Vertix in_vertix;
        Vertix out_vertix;
        Weight weight;
        Data data;

    public:
        edge_desc () {};
        edge_desc (Vertix _in_vertix, Vertix _out_vertix) : in_vertix(_in_vertix), out_vertix(_out_vertix) {};
        edge_desc (Vertix _in_vertix, Vertix _out_vertix, Weight _weight) : in_vertix(_in_vertix), out_vertix(_out_vertix), weight(_weight) {};
        edge_desc (Vertix _in_vertix, Vertix _out_vertix, Weight _weight, Data _data) : in_vertix(_in_vertix), out_vertix(_out_vertix), weight(_weight), data(_data) {};
        ~edge_desc ();

        Vertix Get_in_vertix () { return in_vertix; }
        void Set_in_vertix (Vertix val) { in_vertix = val; }

        Vertix Get_out_vertix () { return out_vertix; }
        void Set_out_vertix (Vertix val) { out_vertix = val; }

        Weight Get_weight () { return weight; }
        void Set_weight (Weight val) { weight = val; }

        Data Get_data () { return data; }
        void Set_data (Data val) { data = val; }

        int From (Vertix val) {if (val == out_vertix) return 1; return 0;}
        int To (Vertix val) {if (val == in_vertix) return 1; return 0;}
};

#endif // DESCRIPTOR_OF_THE_EDGE_H
