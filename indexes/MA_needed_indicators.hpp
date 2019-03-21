//
//  some_file.hpp
//  finantial_system
//
//  Created by Владимир Лазарев on 16.03.2019.
//  Copyright © 2019 Владимир Лазарев. All rights reserved.
//

#ifndef some_file_hpp
#define some_file_hpp

#include "moving_average.hpp"
#include <cmath>


//1============================================================================================================================================
//season indicator with lengths 13/26/9
class Season_indicator_13_26_9
{
public:
    Season_indicator_13_26_9(int period):
    period(period)
    {}
    
    void push_back(double value)
    {
        ema_13.push_back(value);
        ema_26.push_back(value);
        if (ema_26.size() == 26) {
            ema_13.calculate();
            ema_26.calculate();
            ema_9.push_back(ema_13.value - ema_26.value);
        }
    }
    
    void calculate()
    {
        if (ema_9.size() == 9) {
            ema_9.calculate();
            value.push_back(ema_9.value);
        }
    }
    
    void calculate_result()
    {
        this->calculate();
        if (value.size() == 2) {
            auto array = value.array_one().first;
            if (array[1] > 0 and array[1] > array[2]) {
                result = '1';
                // you may open long position
            }
            else{
                result = '0';
                // you should close long position
            }
        }
        else{
            result = 'n';
            // indicator isn't done yet
        }
    }
    
    
private:
    EMA ema_13{13};
    EMA ema_26{26};
    EMA ema_9{9};
    boost::circular_buffer<double> value{2};
    char result;
    const int period;
};


//2============================================================================================================================================
// season_indicator with lengths 3/33/3
class Season_indicator_3_33_3
{
public:
    Season_indicator_3_33_3(int period):
    period(period)
    {}
    
    void push_back(double value)
    {
        ema_3.push_back(value);
        ema_33.push_back(value);
        if (ema_33.size() == 33) {
            ema_3.calculate();
            ema_33.calculate();
            ema_3_result.push_back(ema_3.value - ema_33.value);
        }
    }
    
    void calculate()
    {
        if (ema_3_result.size() == 3) {
            ema_3_result.calculate();
            value.push_back(ema_3_result.value);
        }
    }
    
    void calculate_result()
    {
        this->calculate();
        if (value.size() == 2) {
            auto array = value.array_one().first;
            if (array[1] > 0 and array[1] > array[2]) {
                result = '1';
                // you may open long position
            }
            else{
                result = '0';
                // you should close long position
            }
        }
        else{
            result = 'n';
            // indicator isn't done yet
        }
    }
    
    
private:
    EMA ema_3{3};
    EMA ema_33{33};
    EMA ema_3_result{3};
    boost::circular_buffer<double> value{2};
    char result;
    const int period;
};


//3============================================================================================================================================
//know sure thing
class KST
{
public:
    KST(int period):
    period(period)
    {}
    
    void pushback(double value)
    {
        buffer.push_back(value);
        buffer.linearize();
        size_t digit = buffer.size();
        if(digit == 25)
        {
            buffer.linearize();
            auto array = buffer.array_one().first;
            ema_26_1.push_back((array[digit - 1] - array[digit - 10])/ array[digit - 10]);
            ema_26_2.push_back((array[digit - 1] - array[digit - 13])/ array[digit - 13]);
            ema_26_3.push_back((array[digit - 1] - array[digit - 19])/ array[digit - 19]);
            ema_39.push_back((array[digit - 1] - array[digit - 25])/ array[digit - 25]);
        }
    }
    
    void calculate()
    {
        ema_39.calculate();
        if (ema_39.value != 0) {
            ema_26_1.calculate();
            ema_26_2.calculate();
            ema_26_3.calculate();
            
            value = (ema_39.value * 4 + ema_26_3.value * 3 + ema_26_2.value * 2 + ema_26_1.value * 1) / 10;
            ema_6.push_back(value);
        }
    }
    
    void calculate_result()
    {
        this->calculate();
        ema_6.calculate();
        if (ema_6.value != 0) {
            if (value > ema_6.value) {
                result = '1';
            //you may open long position
            }
            else
            {
                result = '0';
            // you should close your long position
            }
        }
        else
        {
            result = 'n';
        }
    }
    
private:
    const int period;
    EMA ema_26_1{26};
    EMA ema_26_2{26};
    EMA ema_26_3{26};
    EMA ema_39{39};
    EMA ema_6{6};
    char result;
    double value;
    boost::circular_buffer<double> buffer{25};
};


//4============================================================================================================================================
class SMA_strategy
{
public:
    SMA_strategy(int period):
    period(period)
    {}
    
    void push_back(double p_value)
    {
        value = p_value;
        sma.push_back(p_value);
    }
    
    void calculate_result()
    {
        sma.calculate();
        if(sma.value != 0)
        {
            if (value > sma.value) {
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
    char result;
    double value;
    const int period;
    SMA sma{5};
};


//5============================================================================================================================================
class EMA_strategy
{
public:
    EMA_strategy(int period):
    period(period)
    {}
    
    void push_back(double p_value)
    {
        value = p_value;
        ema.push_back(p_value);
    }
    
    void calculate_result()
    {
        ema.calculate();
        if(ema.value != 0)
        {
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
    char result;
    double value;
    const int period;
    EMA ema{5};
    
};


//6============================================================================================================================================
class WMA_strategy
{
public:
    WMA_strategy(int p_period):
    period(p_period)
    {}
    
    void push_back(double p_value)
    {
        value = p_value;
        wma.push_back(p_value);
    }
    
    void calculate_result()
    {
        wma.calculate();
        if(wma.value != 0)
        {
            if (value > wma.value) {
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
    char result;
    double value;
    const int period;
    WMA wma{6};
};


//7============================================================================================================================================
//multiple time frame analyse using exponential moving averages crossover rule
class Three_EMA_crossover
{
public:
    Three_EMA_crossover(int period):
    period(period)
    {}
    
    void pushback(double p_value)
    {
        ema_5.push_back(p_value);
        ema_44.push_back(p_value);
        ema_120.push_back(p_value);
        value = p_value;
    }
    
    void calculate_result()
    {
        ema_120.calculate();
        if (ema_120.value != 0)
        {
            ema_44.calculate();
            ema_5.calculate();
            if(value > ema_5.value and value > ema_44.value and value > ema_120.value)
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
    double value;
    EMA ema_5{5};
    EMA ema_44{44};
    EMA ema_120{120};
};

//8============================================================================================================================================
//relative stregth index
//only long periods
// fucking issue!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
class RSI
{
public:
    RSI(int period):
    period(period)
    {}
    
    void push_back(double value)
    {
        buffer.push_back(value);
        if (buffer.size() == 2)
        {
            buffer.linearize();
            auto array = buffer.array_one().first;
            if (array[1] > array[0]) {
                ema_positive.push_back(array[1] - array[0]);
                ema_negative.push_back(0);
            }
            else
            {
                ema_positive.push_back(0);
                ema_negative.push_back(array[0] - array[1]);
            }
        }
    }
    
    void calculate_result()
    {
        ema_negative.calculate();
        ema_positive.calculate();
        if((ema_negative.value + ema_positive.value) > 0)
        {
            value = 100 * ( ema_positive.value ) / (ema_positive.value + ema_negative.value);
            if (value < 30) {
                result = '1';
            }
            if (value > 70)
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
    circular_buffer buffer{2};
    EMA ema_positive{5};
    EMA ema_negative{5};
};


//9============================================================================================================================================
// rate of change
class ROC
{
public:
    ROC(int period):
    period(period)
    {}
    
    void pushback(double value)
    {
        buffer.push_back(value);
        buffer.linearize();
    }
    
    void calculate_result()
    {
        if(buffer.size() == 90)
        {
            auto array = buffer.array_one().first;
            value = array[89] / array[0] - 1;
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
    const int period;
    circular_buffer buffer{90};
    char result;
    char value;
};


//10============================================================================================================================================
// double exponential moving average
class DEMA
{
public:
    DEMA(int period):
    period(period)
    {}
    
    void push_back(double p_value)
    {
        ema_unary.push_back(p_value);
        if (ema_unary.size() == 3)
        {
            ema_unary.calculate();
            ema_double.push_back(ema_unary.value);
        }
        value = p_value;
    }
    
    void calculate_result()
    {
        if(ema_double.size() == 3)
        {
            ema_double.calculate();
            double value = 2 * ema_unary.value - ema_double.value;
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
    const int period;
    char result;
    double value;
    EMA ema_unary{3};
    EMA ema_double{3};
};


//11============================================================================================================================================
// rate of price movement
class ROPM
{
public:
    ROPM(int period):
    period(period)
    {}
    
    void push_back(double value)
    {
        if (sma.size() == 5)
        {
            auto array = sma.buffer.array_one().first;
            sma_previous.push_back(array[0]);
            sma.push_back(value);
        }
        else
        {
            sma.push_back(value);
        }
    }
    
    void calculate_result()
    {
        sma.calculate();
        sma_previous.calculate();
        if(sma_previous.value > 0)
        {
            if((sma.value - sma_previous.value) > 0){
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
    SMA sma{5};
    SMA sma_previous{5};
    char result;
};


//12============================================================================================================================================
//Hull moving average
class HMA
{
public:
    HMA(int period):
    period(period)
    {}
    
    void push_back(double value)
    {
        wma_5.push_back(value);
        wma_10.push_back(value);
    }
    
    void calculate_result()
    {
        if(wma_10.size() == 10)
        {
            wma_10.calculate();
            wma_5.calculate();
            double value = wma_5.value * 2 - wma_10.value;
            if (buffer.size() == 3)
            {
                auto array = buffer.array_one().first;
                if (array[2] > std::max(array[0], array[1]) and array[2] > value) {
                    result = '0';
                }
                else if (array[2] < std::min(array[0], array[1]) and array[2] < value)
                {
                    result = '1';
                }
            }
            else
            {
                result = 'n';
            }
            buffer.push_back(value);
        }
    }
private:
    const int period;
    char result;
    WMA wma_10{10};
    WMA wma_5{5};
    circular_buffer buffer{3};
};


//13============================================================================================================================================
//Arnaud Legoux moving average
class ALMA_strategy
{
public:
    ALMA_strategy(int period):
    period(period)
    {}
    
    void push_back(double p_value)
    {
        value = p_value;
        alma.push_back(value);
    }
    
    void calculate_result()
    {
        if(alma.size() == 9)
        {
            alma.calculate();
            if (value > alma.value)
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
    double value;
    const int period;
    char result;
    ALMA alma{9};
};






#endif /* some_file_hpp */
