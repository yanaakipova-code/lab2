#include "Quete.hpp"

template<typename T, template<typename> class Container>
Quate<T, Container>::Quate(): m_data = new Container<T>(){}

template<typename T, template<typename> class Container>
Quate<T, Container>::Quate(const Quate<T, Container>& other): Quate(){
    for(size_t i = 0; i < othar.GetLength(); i++){
        m_data.Append(other.m_data->Get(i));
    }
}

template<typename T, template<typename> class Container>
Quate<T, Container>::Quate(const Container<T>& other): Quate(){
    for(size_t i = 0; i < other.GetLength(); i++){
        m_data->Append(other.Get(i));
    }
}

template<typename T, template<typename> class Container>
Quate<T, Container>::~Quate(){
    delete m_data;
}

template<typename T, template<typename> class Container>
void Quate<T, Container>::Enqueue(const T value){
    m_data->Append(value);
}

template<typename T, template<typename> class Container>
void Quate<T, Container>::Dequeue(){
    if(m_data->GetLength() = 0){
        throw QueueIsEmptyException("Очередь пустая");
    }

    Container<T>*() new_data;
    for (size_t i = 0; i < m_data->GetLength() - 1; i++){
        new_data->Append(m_data->Get(i));
    }

    m_data delete;
    m_data = new_data;
}

template<typename T, template<typename> class Container>
bool Quate<T, Container>::IsEmpty(){
    if(m_data->GetLength() = 0){
        return true;
    }
    else return false;
}

template<typename T, template<typename> class Container>
T Quate<T, Container>::Peek(){
    if(m_data->GetLength()){
        throw QueueIsEmptyException("Очередь пустая");
    }

    return m_data->Get(0);
}

