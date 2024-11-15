#pragma once

#include <stdexcept>
#include <utility>

template <typename T>
class Vector {
private:
    T* data;
    size_t size;
    size_t capacity;

    void resize_capacity(size_t new_capacity);

public:
    class Iterator {
    private:
        T* ptr;
    public:
        explicit Iterator(T* ptr) : ptr(ptr) {}
        T& operator*() const { return *ptr; }
        T* operator->() const { return ptr; }
        Iterator& operator++() { ++ptr; return *this; }
        Iterator operator++(int) { Iterator temp = *this; ++ptr; return temp; }
        Iterator& operator--() { --ptr; return *this; }
        Iterator operator--(int) { Iterator temp = *this; --ptr; return temp; }
        bool operator==(const Iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    };

    Vector();
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    ~Vector();
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

    void push_back(const T& value);
    void pop_back();
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    size_t get_size() const;
    size_t get_capacity() const;
    bool is_empty() const;
    void clear();

    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + size); }
};

template <typename T>
Vector<T>::Vector() : data(nullptr), size(0), capacity(0) {}

template <typename T>
Vector<T>::Vector(const Vector& other) : data(new T[other.capacity]), size(other.size), capacity(other.capacity) {
    for (size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept : data(other.data), size(other.size), capacity(other.capacity) {
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}

template <typename T>
Vector<T>::~Vector() {
    delete[] data;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this == &other) return *this;
    delete[] data;
    data = new T[other.capacity];
    size = other.size;
    capacity = other.capacity;
    for (size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this == &other) return *this;
    delete[] data;
    data = other.data;
    size = other.size;
    capacity = other.capacity;
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
    return *this;
}

template <typename T>
void Vector<T>::resize_capacity(size_t new_capacity) {
    T* new_data = new T[new_capacity];
    for (size_t i = 0; i < size; ++i) {
        new_data[i] = std::move(data[i]);
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

template <typename T>
void Vector<T>::push_back(const T& value) {
    if (size == capacity) {
        resize_capacity((capacity == 0) ? 1 : capacity * 2);
    }
    data[size++] = value;
}

template <typename T>
void Vector<T>::pop_back() {
    if (size == 0) {
        throw std::out_of_range("Vector is empty");
    }
    --size;
}

template <typename T>
T& Vector<T>::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
size_t Vector<T>::get_size() const {
    return size;
}

template <typename T>
size_t Vector<T>::get_capacity() const {
    return capacity;
}

template <typename T>
bool Vector<T>::is_empty() const {
    return size == 0;
}

template <typename T>
void Vector<T>::clear() {
    size = 0;
}
