#include <iostream>
#include <functional>

template <typename T>
class Shared_ptr
{
private:
	struct ControlBlock
	{
		int RC;
		std::function<void(T *)> deleter;
	};
	T *ptr;
	ControlBlock *controlBlock;

public:
	int get()
	{
		return this->controlBlock->RC;
	}
	Shared_ptr();
	Shared_ptr(T *);
	Shared_ptr(T* ,std::function<void(T *)> deleter );
	Shared_ptr(const Shared_ptr &ctor); //copy constructor
	Shared_ptr(Shared_ptr &&tmp);	    // muve constructor
	Shared_ptr &operator=(const Shared_ptr &obj);
	Shared_ptr &operator=(Shared_ptr &&tmp); //muve assignment
	T *operator*() const
	{
		return this->ptr;
	}
	T *operator->() const
	{
		return this->ptr;
	}
	~Shared_ptr();
};
template <typename T>
Shared_ptr<T>::Shared_ptr()
{
	this->controlBlock = new ControlBlock();
	this->controlBlock->RC = 0;
	this->ptr = nullptr;
}

template <typename T>
Shared_ptr<T>::Shared_ptr(T *ptr)
{
	this->controlBlock = new ControlBlock();
	this->controlBlock->RC = 1;
	this->ptr = ptr;
}
template <typename T>
Shared_ptr<T>::~Shared_ptr()
{
	if (ptr)
	{
		this->controlBlock->RC--;
		if (this->controlBlock->RC == 0)
		{
			delete this->ptr;
			delete this->controlBlock;
		}
	}
}

/**************copy constructor**********/
template <typename T>
Shared_ptr<T>::Shared_ptr(const Shared_ptr<T> &other)
{
	this->controlBlock = new ControlBlock();
	this->controlBlock = other.controlBlock;
	this->ptr = other.ptr;
	this->controlBlock->RC++;
}

/**************muve constructor**********/
template <typename T>
Shared_ptr<T>::Shared_ptr(Shared_ptr<T> &&tmp)
{
	this->controlBlock = new ControlBlock();
	this->controlBlock = tmp.controlBlock;
	this->ptr = tmp.ptr;
	tmp.controlBlock = nullptr;
	tmp.ptr = nullptr;
}

/**************muve assignment**********/
template <typename T>
Shared_ptr<T> &Shared_ptr<T>::operator=(Shared_ptr<T> &&tmp)
{
	this->controlBlock = tmp.controlBlock;
	this->ptr = tmp.ptr;
	tmp.controlBlock = nullptr;
	tmp.ptr = nullptr;
	return *this;
}

/**************copy assignment**********/
template <typename T>
Shared_ptr<T> &Shared_ptr<T>::operator=(const Shared_ptr<T> &other)
{
	if (this == &other)
	{
		return *this;
	}
	if (this->ptr)
	{
		this->controlBlock->RC;
		this->controlBlock = other.controlBlock;
		this->ptr = other.ptr;
		this->controlBlock->RC++;
	}
	else
	{
		this->controlBlock = other.controlBlock;
		this->ptr = other.ptr;
		this->controlBlock->RC++;
	}
	return *this;
}
