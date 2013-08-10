#ifndef VERTEX_DESCRIPTOR_H
#define VERTEX_DESCRIPTOR_H

template <typename Name_t, typename Data_t>
class VertexDescriptor
{
private:
	Name_t name;
	Data_t data;
	int index;

public:
	VertexDescriptor () : index(-1){}
	VertexDescriptor (Name_t _name, Data_t _data, int _index) :
		name(_name), data(_data), index(_index){}
	~VertexDescriptor (){}

	Name_t getName (){return name;}
	void setName (Name_t _name){name = _name;}

	Data_t getData () {return data;}
	void setData (Data_t _data){data = _data;}

	int getIndex (){return index;}
	void setIndex (int _index){index = _index;}

	VertexDescriptor<Name_t, Data_t>& operator= (VertexDescriptor <Name_t, Data_t>& val)
	{
		name = val.getName();
		data = val.getData();
		index = val.getIndex();
	}
};

#endif // VERTEX_DESCRIPTOR_H
