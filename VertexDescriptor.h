#ifndef VERTEX_DESCRIPTOR_H
#define VERTEX_DESCRIPTOR_H

template <typename N, typename D> //name,data
class VertexDescriptor
{
    private:
		N name;
		D data;
        int index;

    public:
		VertexDescriptor () : index(-1){}
		VertexDescriptor (N _name, D _data, int _index) : name(_name), data(_data), index(_index){}
		~VertexDescriptor (){}

		N getName (){return name;}
		void setName (N _name){name = _name;}

		D getData () {return data;}
		void setData (D _data){data = _data;}

		int getIndex (){return index;}
		void setIndex (int _index){index = _index;}

		VertexDescriptor<N, D>& operator= (VertexDescriptor <N, D>& val)
        {
			name = val.getName();
			data = val.getData();
			index = val.getIndex();
        }
};

#endif // VERTEX_DESCRIPTOR_H
