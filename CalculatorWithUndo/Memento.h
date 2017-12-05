#pragma once
template <class T>
class Memento
{
public:
	Memento(const T& var);
	~Memento();
	T* getData();
private:
	T data;
};

template <class T>
Memento<T>::Memento(const T& var)
{
	data = var;
}

template <class T>
Memento<T>::~Memento()
{
}

template <class T>
T* Memento<T>::getData()
{
	return &data;
}