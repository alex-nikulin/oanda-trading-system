//
//  Japan_candle_indicators.hpp
//  finantial_system
//
//  Created by Владимир Лазарев on 17.03.2019.
//  Copyright © 2019 Владимир Лазарев. All rights reserved.
//

#ifndef Japan_candle_indicators_hpp
#define Japan_candle_indicators_hpp

#include <array>
#include <boost/circular_buffer.hpp>
#include "moving_average.hpp"
#include <cmath>

/*
 candle is array<double, 4>, where:
 array[0] - opening price
 array[1] - highest price
 array[2] - lowest price
 array[3] - closing price
 */

//1========================================================================================================================================================
// acumulation swing index
class ASI
{
public:
    ASI(int period):
    period(period)
    {}
    
    void push_back(std::array<double, 4> value)
    {
        buffer.push_back(value);
        buffer.linearize();
    }
    
    void calculate()
    {
        if (buffer.size() == 2)
        {
            auto array = buffer.array_one().first;
            double R;
            if ((array[1][1] - array[0][3]) >= (array[1][2] - array[0][3]) && (array[1][1] - array[0][3]) >= (array[1][1] - array[1][2]))
            {
                R = (array[1][1] - array[0][3]) - (array[1][2] - array[0][3]) / 2 + (array[0][3] - array[0][0]) / 4;
            }
            else if((array[1][2] - array[0][3]) >= (array[1][1] - array[0][3]) && (array[1][2] - array[0][3]) >= (array[1][1] - array[1][2]))
            {
                R = (array[1][2] - array[0][3]) - (array[1][1] - array[0][3]) / 2 + (array[0][3] - array[0][0]) / 4;
            }
            else if((array[1][1] - array[1][2]) >= (array[1][1] - array[0][3]) && (array[1][1] - array[1][2]) >= (array[1][2] - array[0][3]))
            {
                R = (array[1][1] - array[1][2]) + (array[0][3] - array[0][0]) / 4;
            }
            value = 50 * std::max(array[1][1] - array[0][3], array[1][2] - array[0][3]) * ((array[0][3] - array[0][3]) + (array[0][3] - array[1][0]) / 2 + (array[0][3] - array[0][0]) / 4) / R;
            ema.push_back(value);
        }
        else
        {
            result = 'n';
        }
    }
    
    void calculate_result()
    {
        this->calculate();
        if(ema.size() == 2)
        {
            ema.calculate();
            if (value > ema.value) {
                result = '1';
            }
            else
            {
                result = '0';
            }
        }
        else
        {
            result = 'n';
        }
    }
    
private:
    const int period;
    double value;
    char result;
    EMA ema{2};
    boost::circular_buffer<std::array<double, 4>> buffer{2};
};


//2========================================================================================================================================================
// ease of movement value
class EMV
{
public:
    EMV(int period):
    period(period)
    {}
    
    void push_back(std::array<double, 4> array)
    {
        buffer.push_back(array);
        buffer.linearize();
    }
    
    void calculate()
    {
        auto array = buffer.array_one().first;
        ema.push_back(((array[1][1] + array[1][2]) - (array[0][1] + array[0][2])) / (array[1][1] - array[1][2]));
    }
    
    void calculate_result()
    {
        this->calculate();
        if (ema.size() == 4) {
            ema.calculate();
            if (ema.value > 0) {
                result = '1';
            }
            else
            {
                result = '0';
            }
        }
        else
        {
            result = 'n';
        }
    }
private:
    const int period;
    boost::circular_buffer<std::array<double, 4>> buffer{2};
    EMA ema{4};
    char result;
};


//3========================================================================================================================================================
//commodity chanal index
class CCI
{
public:
    CCI(int period):
    period(period)
    {}
    
    void push_back(std::array<double, 4> p_array)
    {
        array = p_array;
        sma.push_back((array[1] + array[2] + array[3]) / 3);
        if (sma.size() == 5)
        {
            sma.calculate();
            buffer.push_back((array[1] + array[2] + array[3]) / 3 - sma.value);
        }
    }
    
    void calculate_result()
    {
        if (buffer.size() == 5)
        {
            buffer.linearize();
            double digit = 0;
            auto help_array = buffer.array_one().first;
            for(int i = 0; i < 4; digit += help_array[i], ++ i) {}
            double value = ((array[1] + array[2] + array[3]) / 3 - sma.value) / (0.015 * digit / 5);
            if(value > 0)
            {
                result = '1';
            }
            else
            {
                result = '0';
            }
        }
        else
        {
            result = 'n';
        }
    }
    
private:
    std::array<double, 4> array;
    const int period;
    char result;
    boost::circular_buffer<double> buffer{5};
    SMA sma{5};
};


//4========================================================================================================================================================
// relative volatility index
class RVI
{
public:
    RVI(int period):
    period(period)
    {}
    
    void push_back(std::array<double, 4> p_array)
    {
        ema.push_back((p_array[3] - p_array[0]) / (p_array[1] - p_array[2]));
    }
    
    void calculate_result()
    {
        if (ema.size() == 10) {
            ema.calculate();
            if (ema.value > 0)
            {
                result = '1';
            }
            else
            {
                result = '0';
            }
        }
        else
        {
            result = 'n';
        }
    }
private:
    const int period;
    char result;
    EMA ema{10};
};


//5========================================================================================================================================================
// stochastics oscillator
//shold be used with larger period, thet it has(period* = period * 6) !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
class Stochastics_oscillator
{
public:
    Stochastics_oscillator(int period):
    period(period)
    {}
    
    void push_back(std::array<double, 4> array)
    {
        sma.push_back(100 * (array[3] - array[2]) / (array[1] - array[2]));
    }
    
    void calculate_result()
    {
        if (sma.size() == 3)
        {
            sma.calculate();
            if(sma.value < 30)
            {
                result = '1';
            }
            else
            {
                result = '0';
            }
        }
        else
        {
            result = 'n';
        }
    }
private:
    const int period;
    SMA sma{3};
    char result;
    
};


//6============================================================================================================================================
//Awesome oscillator
class Awesome_oscillator
{
public:
    Awesome_oscillator(int period):
    period(period)
    {}
    
    void push_back(std::array<double, 4> array)
    {
        double value = (array[1] + array[2]) / 2;
        sma_5.push_back(value);
        sma_34.push_back(value);
    }
    
    void calculate_result()
    {
        if (sma_34.size() == 34) {
            sma_34.calculate();
            sma_5.calculate();
            if(sma_5.value - sma_34.value > 0)
            {
                result = '1';
            }
            else
            {
                result = '0';
            }
        }
        else
        {
            result = 'n';
        }
    }
private:
    const int period;
    char result;
    SMA sma_5{5};
    SMA sma_34{34};
};


//============================================================================================================================================
// average true range

/*class ATR
{
public:
    ATR(int period):
    period(period)
    {}
    
    void push_back(std::array<double, 4> array)
    {
        double value = std::max(array[1] - array[2], array[1] - array[3], array[3] - array[1]);
        sma.push_back(value);
    }
    
    void calculate_result()
    {
        
    }
    
private:
    const int period;
    char result;
    SMA sma{14};
};
*/


//============================================================================================================================================
// average true range
//shold be used with larger period, thet it has(period* = period * 6) !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
class Williams_R
{
public:
    Williams_R(int period):
    period(period)
    {}
    void push_back(std::array<double, 4> array)
    {
        value = 100 * (array[3] - array[1]) / (array[1] - array[2]);
    }
    
    void calculate_result()
    {
        if(value)
        {
            if (value < -80)
            {
                result = '1';
            }
            else if (value > -20)
            {
                result = '0';
            }
            else
            {
                result = 'n';
            }
        }
        else
        {
            result = 'n';
        }
    }
    
private:
    char result;
    const int period;
    double value = 0;
};





#endif /* Japan_candle_indicators_hpp */
