//
//  fixedpointnumber.hpp
//  fixedpoint
//
//  Created by Álvaro Lozano Rojo on 12/4/18.
//  Copyright © 2018 Álvaro Lozano Rojo. All rights reserved.
//

#include<cstdint>


#ifndef fixedpointnumber_h
#define fixedpointnumber_h

//
// A fixed point arithmetic number with 32 bits and
// N of them used for fractional part
// To-Do: overflows...
//
template<int N>
class fixedpointnumber {
public:
    fixedpointnumber(const fixedpointnumber& val) : data{val.data} { }
    fixedpointnumber(const int val) : data{val << N} {
        // No overflow check
    }
    fixedpointnumber(const double val) {
        // No overflow check
        data = static_cast<int32_t>(val * (1<<N));
    }
    fixedpointnumber(const float val) {
        // No overflow check
        data = static_cast<int32_t>(val * (1<<N));
    }
    
    fixedpointnumber& operator+=(const fixedpointnumber& rhs) {
        data += rhs.data;
        return *this;
    }
    friend fixedpointnumber operator+(fixedpointnumber a, const fixedpointnumber& b) {
        a += b;
        return a;
    }

    fixedpointnumber& operator-=(const fixedpointnumber& rhs) {
        data -= rhs.data;
        return *this;
    }
    friend fixedpointnumber operator-(fixedpointnumber a, const fixedpointnumber& b) {
        a -= b;
        return a;
    }
    
    fixedpointnumber& operator+(const fixedpointnumber &a) {
        return a;
    }
    fixedpointnumber& operator+(fixedpointnumber &a) {
        return a;
    }
    fixedpointnumber operator-(fixedpointnumber a) {
        a.data = -a.data;
        return a;
    }

    fixedpointnumber& operator*=(const fixedpointnumber& rhs) {
        fixedpointnumber<N> res;
        data = (static_cast<int64_t>(data)
                    * static_cast<int64_t>(rhs.data)) >> N;
        return *this;
    }
    friend fixedpointnumber operator*(fixedpointnumber a, const fixedpointnumber& b) {
        a *= b;
        return a;
    }

    fixedpointnumber& operator/=(const fixedpointnumber& rhs) {
        data = (static_cast<int64_t>(data) << N) / rhs.data;
        return *this;
    }
    friend fixedpointnumber operator/(fixedpointnumber a, const fixedpointnumber& b) {
        a /= b;
        return a;
    }

    operator double() const {
        return static_cast<double>(data)/(1<<N);
    }
    
protected:
    int32_t data;
};



#endif /* fixedpointnumber_h */
