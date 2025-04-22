#ifndef M_VECTOR_ITERATOR_H
#define M_VECTOR_ITERATOR_H

template <typename T>
class m_vector;  // Предварительное объявление класса вектора

template <typename T>
class m_vector_iterator {
private:
    m_vector<T>* container;  // Ссылка на контейнер
    size_t currentIndex;     // Текущий индекс

public:
    // Конструктор с контейнером и начальным индексом
    explicit m_vector_iterator(m_vector<T>& cont, size_t startIndex = 0)
        : container(&cont), currentIndex(startIndex) {}

    // Префиксный инкремент
    m_vector_iterator& operator++() {
        ++currentIndex;
        return *this;
    }

    // Проверка на достижение конца
    bool is_end() const {
        return currentIndex >= container->get_length();
    }

    // Постфиксный инкремент
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

    // Доступ к членам
    T* operator->() {
        return &(*container)[currentIndex];
    }

    const T* operator->() const {
        return &(*container)[currentIndex];
    }

    // Операторы сравнения
    bool operator==(const m_vector_iterator& other) const {
        return container == other.container && currentIndex == other.currentIndex;
    }

    bool operator!=(const m_vector_iterator& other) const {
        return !(*this == other);
    }
};

#endif // M_VECTOR_ITERATOR_H
