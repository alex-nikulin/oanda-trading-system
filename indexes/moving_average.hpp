//
//  circular.cpp
//  2_term_1_sem
//
//  Created by Владимир Лазарев on 07.03.2019.
//  Copyright © 2019 Владимир Лазарев. All rights reserved.
//

#ifndef moving_averages_cpp
#define moving_averages_cpp

#include <iostream>
#include <boost/circular_buffer.hpp>
#include <utility>
#include <cmath>

using circular_buffer = boost::circular_buffer <double>;

/*
 class Moving_average
 {
 public:
 Moving_average(int period, int length):
 period(period), length(length)
 {
 buffer.set_capacity(length);
 }
 
 //self-check only
 size_t capacity()
 {
 return buffer.capacity();
 }
 
 //self-check only
 size_t size()
 {
 return buffer.size();
 }
 
 int get_period()
 {
 return period;
 }
 
 int get_length()
 {
 return length;
 }
 
 virtual void calculate();
 void push_back(std::pair<int, unsigned long> value)
 {
 buffer.push_back(value);
 this->calculate();
 }
 
 private:
 // period of time between points
 const int period;
 // count of points
 const int length;
 // value of SMA
 double value = 0;
 //container of points
 //every point is std::pair<int, unsigned long>, where int is value & unsigned long is time
 circular_buffer buffer;
 };
 */



//============================================================================================================================================
class SMA
{
public:
    friend class SMA_strategy;
    friend class ROPM;
    friend class CCI;
    friend class Stochastics_oscillator;
    friend class Awesome_oscillator;
    
    //self-check only
    size_t capacity()
    {
        return buffer.capacity();
    }
    
    //self-check only
    size_t size()
    {
        return buffer.size();
    }
    
    SMA() = default;
    
    SMA(int length):
    length(length)
    {
        buffer.set_capacity(length + 1);
    }
    
    int get_length()
    {
        return length;
    }
    
    //compute value of indicator SMA
    void calculate()
    {
        if (buffer.size() == buffer.capacity() - 1) {
            for (double i: buffer) {
                value += i;
            }
            value /= length;
            std::cout << "the value iss " << value << '\n';
        }
        if (buffer.size() == buffer.capacity()) {
            buffer.linearize();
            value -= (double)buffer.front() / length;
            value += (double)buffer.back() / length;
            std::cout << "the value is " << value << '\n';
        }
    }
    
    //every time buffer size increases, SMA value is calculated
    void push_back(double value)
    {
        buffer.push_back(value);
        this->calculate();
    }
    
private:
    // count of points
    int length;
    // value of SMA
    double value = 0;
    //container of points
    //every point is std::pair<int, unsigned long>, where int is value & unsigned long is time
    circular_buffer buffer;
};


//============================================================================================================================================
class EMA
{
public:
    friend class Season_indicator_13_26_9;
    friend class Season_indicator_3_33_3;
    friend class KST;
    friend class EMA_strategy;
    friend class Three_EMA_crossover;
    friend class RSI;
    friend class DEMA;
    friend class ASI;
    friend class EMV;
    friend class RVI;


    //self-check only
    size_t capacity()
    {
        return buffer.capacity();
    }
    
    //self-check only
    size_t size()
    {
        return buffer.size();
    }
    
    EMA() = default;
    
    EMA(int length):
    length(length)
    {
        buffer.set_capacity(length);
    }
    
    int get_length()
    {
        return length;
    }
    
    //compute value of indicator EMA
    void calculate()
    {
        if (buffer.size() == buffer.capacity()) {
            value = 0;
            buffer.linearize();
            auto array = buffer.array_one().first;
            
            for (int i = 0; i < length; i ++) {
                value = (array[length - 1 - i] - value) * 2/(i + 2) + value;
            }
            std::cout << "the value is " << value << '\n';
        }
    }
    
    //every time buffer size increases, EMA value is calculated
    void push_back(double value)
    {
        buffer.push_back(value);
        this->calculate();
    }
private:
    // count of points
    int length;
    // value of SMA
    double value = 0;
    //container of points
    //every point is std::pair<int, unsigned long>, where int is value & unsigned long is time
    circular_buffer buffer;
};


//============================================================================================================================================
class WMA
{
public:
    friend class WMA_strategy;
    friend class HMA;
    
    //self-check only
    size_t capacity()
    {
        return buffer.capacity();
    }
    
    //self-check only
    size_t size()
    {
        return buffer.size();
    }
    
    WMA() = default;

    WMA(int length):
    length(length)
    {
        buffer.set_capacity(length);
    }
    
    int get_length()
    {
        return length;
    }
    
    //compute value of indicator WMA
    void calculate()
    {
        if (buffer.size() == buffer.capacity()) {
            value = 0;
            int digit = 0;
            buffer.linearize();
            auto array = buffer.array_one().first;
            for (int i = 0; i < length; ) {
                value += array[i] * (i + 1);
                digit += ++ i;
            }
            value /= digit;
            std::cout << "the value is " << value << '\n';
        }
    }
    
    //every time buffer size increases, WMA value is calculated
    void push_back(double value)
    {
        buffer.push_back(value);
        this->calculate();
    }
private:
    // count of points
    int length;
    // value of SMA
    double value = 0;
    //container of points
    //every point is std::pair<int, unsigned long>, where int is value & unsigned long is time
    circular_buffer buffer;
};


//============================================================================================================================================
//Arnaud Legoux moving average
class ALMA
{
public:
    friend class ALMA_strategy;
    
    ALMA(int length):
    length(length)
    {
        buffer.set_capacity(length);
    }
    
    //self-check only
    size_t capacity()
    {
        return buffer.capacity();
    }
    
    //self-check only
    size_t size()
    {
        return buffer.size();
    }
    
    int get_length()
    {
        return length;
    }
    
    void push_back(double value)
    {
        buffer.push_back(value);
        this->calculate();
    }
    
    void calculate()
    {
        if (buffer.size() == length)
        {
            buffer.linearize();
            auto array = buffer.array_one().first;
            double wtd = 0;
            double wtdsum = 0;
            double sum = 0;
            for (int i = 0; i < length; ++ i) {
                wtd = std::exp(-(i - (((length - 1) * 0.85) * (i - (length - 1) * 0.85))) / 2 /  length / length * 36);
                wtdsum += wtd;
                sum += wtd * array[i];
            }
            value = sum / wtdsum;
            std::cout << "the value is " << value << '\n';
        }
    }
private:
    double value;
    const int length;
    char result;
    circular_buffer buffer;
};
#endif

