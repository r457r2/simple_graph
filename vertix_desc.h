#ifndef VERTIX_DESC_H
#define VERTIX_DESC_H

template <typename Name, typename Data>
class vertix_desc
{
    private:
        Name name;
        Data data;
        int index;

    public:
        vertix_desc() : index(-1) {};
        vertix_desc(Name _name, Data _data, int _index):name(_name), data(_data), index(_index){};
        ~vertix_desc(){};

        Name Get_name() { return name; }
        void Set_name(Name val) { name = val; }

        Data Get_data() { return data; }
        void Set_data(Data val) { data = val; }

        int Get_index() { return index; }
        void Set_index(int val) { index = val; }

        vertix_desc<Name, Data>& operator= (vertix_desc<Name, Data>& val)
        {
            name = val.Get_name();
            data = val.Get_data();
            index = val.Get_index();
        }

        int operator== (vertix_desc<Name, Data>& val)
        {
            if(name = val.Get_name() && data = val.Get_data() && index = val.Get_index())
                return 1;
            return 0;
        }
};

#endif // VERTIX_DESC_H
