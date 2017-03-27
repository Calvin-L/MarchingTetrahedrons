//
//  Array3D.h
//  MarchingCubes
//
//  Created by Calvin Loncaric on 6/26/11.
//

#ifndef ARRAY3D_H
#define ARRAY3D_H

#include <cstring>   // size_t
#include <algorithm> // std::copy, std::swap
#include <cassert>   // assert

template <class T>
class Array3D
{

private:
    size_t _xmult, _ymult, _total;
    T* _data;

public:
    Array3D(size_t width, size_t height, size_t depth);
    Array3D(const Array3D& other);
    Array3D& operator=(Array3D other);
    ~Array3D();
    inline void set(size_t x, size_t y, size_t z, const T& value);
    inline const T& get(size_t x, size_t y, size_t z);

};

// ========================================================================

template <class T>
Array3D<T>::Array3D(size_t width, size_t height, size_t depth)
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
    delete[] _data;
}

template <class T>
void Array3D<T>::set(size_t x, size_t y, size_t z, const T& value)
{
    assert(x * _xmult + y * _ymult + z < _total);
    _data[x * _xmult + y * _ymult + z] = value;
}

template <class T>
const T& Array3D<T>::get(size_t x, size_t y, size_t z)
{
    assert(x * _xmult + y * _ymult + z < _total);
    return _data[x * _xmult + y * _ymult + z];
}

#endif
