#ifndef LIST_HPP
#define LIST_HPP


template <typename T>
class List
{
	public:
		List(T tmp);
		List(T tmp, void *ptr);
		~List();

		void push_back(T tmp);
		void setData(T tmp);
		T getData(void);

	private:
		T		data;
		List<T> *next;
		List<T> *previous;

};

//###############################
//##							#
//###############################

template <typename T>
List<T>::List(T tmp)
{
	this->data = tmp;
	this->next = 0;
	this->previous = 0;
}

template <typename T>
List<T>::List(T tmp, void *ptr)
{
	this->data = tmp;
	this->previous = ptr;
}

template <typename T>
List<T>::~List()
{
	
}

//###############################
//##							#
//###############################

template <typename T>
void List<T>::push_back(T tmp)
{
	this->next = new List<T>(tmp, this);
}

template <typename T>
void List<T>::setData(T tmp)
{
	this->data = tmp;
}

template <typename T>
T List<T>::getData(void)
{
	return (this->data);
}
