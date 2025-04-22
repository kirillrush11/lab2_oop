#ifndef M_VECTOR_ITERATOR_H
#define M_VECTOR_ITERATOR_H

template <typename T>
class m_vector;  

template <typename T>
class m_vector_iterator {
private:
    m_vector<T>* container;
    size_t currentIndex;    

public:
    explicit m_vector_iterator(m_vector<T>& cont, size_t startIndex = 0)
        : container(&cont), currentIndex(startIndex) {} //изменил выделение памяти//

    m_vector_iterator& operator++() {
        ++currentIndex;
        return *this;
    }

    bool is_end() const {  //добавил итератор//
        return currentIndex >= container->get_length();
    }

    m_vector_iterator operator++(int) {
        m_vector_iterator temp = *this;
        ++currentIndex;
        return temp;
    }

    T& operator*() {
        return (*container)[currentIndex];
    }

    const T& operator*() const {
        return (*container)[currentIndex];
    }

    T* operator->() {
        return &(*container)[currentIndex];
    }

    const T* operator->() const {
        return &(*container)[currentIndex];
    }

    bool operator==(const m_vector_iterator& other) const {
        return container == other.container && currentIndex == other.currentIndex;
    }

    bool operator!=(const m_vector_iterator& other) const {
        return !(*this == other);
    }
};

#endif // M_VECTOR_ITERATOR_H
