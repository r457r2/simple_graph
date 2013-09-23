#ifndef VERTEX_DESCRIPTOR_H
#define VERTEX_DESCRIPTOR_H

template <typename Name_t, typename Data_t>
class VertexDescriptor
{
private:
	Name_t name;
	Data_t data;
	int index;
	int user_index;

public:
	VertexDescriptor () : index(-1), user_index(-1){}

	VertexDescriptor (Name_t _name, Data_t _data, int _index, int uidx) :
		name(_name), data(_data), index(_index), user_index(uidx){}

	VertexDescriptor (VertexDescriptor& one)
	{
		name = one.getName();
		data = one.getData();
		index = one.getIndex();
		user_index = one.getUserIndex();
	}

	~VertexDescriptor (){}

	Name_t getName (){return name;}
	void setName (Name_t _name){name = _name;}
	Name_t& getSName (){return name;}

	Data_t getData () {return data;}
	void setData (Data_t _data){data = _data;}
	Data_t& getSData () {return data;}

	int getIndex (){return index;}
	int getUserIndex() {return user_index;}
	void setIndex (int _index){index = _index;}
	void setUserIndex(int uidx) { user_index = uidx; }

	VertexDescriptor& operator= (VertexDescriptor& other)
	{
		name = other.getName();
		data = other.getData();
		index = other.getIndex();
		user_index = other.getUserIndex();
		return *this;
	}
};

#endif // VERTEX_DESCRIPTOR_H
