#ifndef DIYVECTOR_H
#define DIYVECTOR_H

template <typename obj>
class Vector{
public:
	explicit Vector(int initSize = 0)
		: theSize(initSize), theCapacity(initSize + SPARE_CAPACITY)
	{
		objects = new obj[theCapacity];
	}
	Vector(const Vector& rhs) : objects(nullptr)
	{
		operator=(rhs);
	}
	const Vector& operator= (const Vector& rhs)
	{
		if (this != &rhs)
		{
			delete[] objects;
			theSize = rhs.theSize;
			theCapacity = rhs.theCapacity;

			objects = new obj[theCapacity];
			for (int k = 0; k < rhs.size(); k++)
				objects[k] = rhs.objects[k];
		}

		return *this;
	}
	~Vector() { delete[] objects; }

	void resize(int newSize)
	{
		if (newSize > theCapacity)
			reserve(newSize * 2 + 1);
		theSize = newSize;
	}
	void reserve(int newCapacity)
	{
		if (newCapacity < theSize)
			return;

		obj *oldObj = objects;
		objects = new objects[newCapacity];
		for (int k = 0; k < theSize; k++)
			objects[k] = oldObj[k];
		theCapacity = newCapacity;

		delete[] oldObj;
	}

	obj& operator[] (int index)
	{ return objects[index]; }
	const obj& operator[] (int index) const 
	{ return objects[index]; }

	void push_back(const obj & x)
	{
		if (theSize == theCapacity)
			reserve(2 * theSize + 1);
		objects[theSize++] = x;
	}
	void pop_back() { theSize--; }
	const obj& back() const 
	{ return objects[theSize - 1]; }

	bool isEmpty() const { return theSize == 0; }
	int size() const { return theSize; }
	int capacity() const { return theCapacity; }

	typedef obj* iterator;
	typedef obj* const_iterator;
	iterator begin() { return &objects[0]; }
	iterator end() { return &objects[size()]; }
	const_iterator begin() const{ return &objects[0]; }
	const_iterator end() const{ return &objects[size()]; }

	enum { SPARE_CAPACITY = 16 };
	
private:
	int theSize;
	int theCapacity;
	obj *objects;
};

#endif