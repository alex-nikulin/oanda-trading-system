//
//  some_file.cpp
//  finantial_system
//
//  Created by Владимир Лазарев on 16.03.2019.
//  Copyright © 2019 Владимир Лазарев. All rights reserved.
//

#include "MA_needed_indicators.hpp"
#include "Japan_candle_indicators.hpp"

int main()
{

    SMA some_sma(4);
    std::cout << some_sma.get_length() << '\n';
    some_sma.push_back(12);
    std::cout << some_sma.size() << '\n';
    some_sma.push_back(13);
    std::cout << some_sma.size() << '\n';
    some_sma.push_back(14);
    std::cout << some_sma.size() << '\n';
    some_sma.push_back(12);
    std::cout << some_sma.size() << '\n';
    some_sma.push_back(11);
    std::cout << some_sma.size() << '\n';
    some_sma.push_back(9);
    std::cout << some_sma.size() << '\n';
    some_sma.push_back(14);
    std::cout << some_sma.size() << '\n';
    some_sma.push_back(16);
    std::cout << some_sma.size() << '\n' << '\n';


    WMA some_wma(4);
    std::cout << some_wma.get_length() << '\n';
    some_wma.push_back(12);
    std::cout << some_wma.size() << '\n';
    some_wma.push_back(13);
    std::cout << some_wma.size() << '\n';
    some_wma.push_back(14);
    std::cout << some_wma.size() << '\n';
    some_wma.push_back(15);
    std::cout << some_wma.size() << '\n';
    some_wma.push_back(12);
    std::cout << some_wma.size() << '\n';
    some_wma.push_back(15);
    std::cout << some_wma.size() << '\n';
    some_wma.push_back(13);
    std::cout << some_wma.size() << '\n' << '\n';


    EMA some_ema(4);
    std::cout << some_ema.get_length() << '\n';
    some_ema.push_back(12);
    std::cout << some_ema.size() << '\n';
    some_ema.push_back(13);
    std::cout << some_ema.size() << '\n';
    some_ema.push_back(14);
    std::cout << some_ema.size() << '\n';
    some_ema.push_back(15);
    std::cout << some_ema.size() << '\n';
    some_ema.push_back(12);
    std::cout << some_ema.size() << '\n';
    some_ema.push_back(13);
    std::cout << some_ema.size() << '\n';
    
    
    ALMA some_alma(9);
    std::cout << some_alma.size() << '\n';
    some_alma.push_back(2);
    std::cout << some_alma.size() << '\n';
    some_alma.push_back(3);
    std::cout << some_alma.size() << '\n';
    some_alma.push_back(5);
    std::cout << some_alma.size() << '\n';
    some_alma.push_back(5);
    std::cout << some_alma.size() << '\n';
    some_alma.push_back(6);
    std::cout << some_alma.size() << '\n';
    some_alma.push_back(5);
    std::cout << some_alma.size() << '\n';
    some_alma.push_back(8);
    std::cout << some_alma.size() << '\n';
    some_alma.push_back(11);
    std::cout << some_alma.size() << '\n';
    some_alma.push_back(10);
    std::cout << some_alma.size() << '\n';
    some_alma.push_back(12);
    std::cout << some_alma.size() << '\n';
    some_alma.push_back(14);
    std::cout << some_alma.size() << '\n';
    some_alma.push_back(12);
    
    
    
    
  return 0;
}
