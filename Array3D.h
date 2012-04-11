//
//  Array3D.h
//  MarchingCubes
//
//  Created by Calvin Loncaric on 6/26/11.
//

#ifndef ARRAY3D_H
#define ARRAY3D_H

#include <cstdlib>

template <class T>
class Array3D
{
    
private:
    size_t _xmult, _ymult;
    T* _data;
    
public:
    Array3D(size_t width, size_t height, size_t depth);
    ~Array3D();
    inline void set(size_t x, size_t y, size_t z, const T& value);
    inline const T& get(size_t x, size_t y, size_t z);
    
};

// ========================================================================

template <class T>
Array3D<T>::Array3D(size_t width, size_t height, size_t depth)
:_xmult(width * height), _ymult(height), _data(new T[width*height*depth])
{
}

template <class T>
Array3D<T>::~Array3D()
{
    delete[] _data;
}

template <class T>
void Array3D<T>::set(size_t x, size_t y, size_t z, const T& value)
{
    _data[x * _xmult + y * _ymult + z] = value;
}

template <class T>
const T& Array3D<T>::get(size_t x, size_t y, size_t z)
{
    return _data[x * _xmult + y * _ymult + z];
}

#endif
