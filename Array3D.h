#ifndef ARRAY3D_H
#define ARRAY3D_H

#include <cstddef>   // std::size_t
#include <algorithm> // std::copy, std::swap
#include <cassert>   // assert

template <class T>
class Array3D
{

private:
    std::size_t _xmult, _ymult, _total;
    T* _data;

public:
    Array3D();
    Array3D(std::size_t width, std::size_t height, std::size_t depth);
    Array3D(const Array3D& other);
    Array3D& operator=(Array3D other);
    ~Array3D();
    inline       T& operator()(std::size_t x, std::size_t y, std::size_t z);
    inline const T& operator()(std::size_t x, std::size_t y, std::size_t z) const;

};

// ========================================================================

template <class T>
Array3D<T>::Array3D()
:_xmult(0), _ymult(0), _total(0), _data(NULL)
{
}

template <class T>
Array3D<T>::Array3D(std::size_t width, std::size_t height, std::size_t depth)
:_xmult(width * height), _ymult(height), _total(width*height*depth), _data(new T[_total])
{
}

template <class T>
Array3D<T>::Array3D(const Array3D& other)
:_xmult(other._xmult), _ymult(other._ymult), _total(other._total), _data(new T[_total])
{
    std::copy(other._data, other._data + _total, _data);
}

template <class T>
Array3D<T>& Array3D<T>::operator=(Array3D other)
{
    std::swap(_xmult, other._xmult);
    std::swap(_ymult, other._ymult);
    std::swap(_total, other._total);
    std::swap(_data, other._data);
    return *this;
}

template <class T>
Array3D<T>::~Array3D()
{
    if (_data != NULL) {
        delete[] _data;
    }
}

template <class T>
T& Array3D<T>::operator()(std::size_t x, std::size_t y, std::size_t z)
{
    assert(x * _xmult + y * _ymult + z < _total);
    return _data[x * _xmult + y * _ymult + z];
}

template <class T>
const T& Array3D<T>::operator()(std::size_t x, std::size_t y, std::size_t z) const
{
    assert(x * _xmult + y * _ymult + z < _total);
    return _data[x * _xmult + y * _ymult + z];
}

#endif
