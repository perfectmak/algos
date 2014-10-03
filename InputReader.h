/* 
 * File:   InputReader.h
 * Author: perfectmak
 *
 */

#ifndef INPUTREADER_H
#define	INPUTREADER_H

#include <iostream>
#include <string>
#include <fstream>

//A cool better way for reading inputs

template <class T>
class InputReader
{
public:
    T readLine();
    
    static InputReader<T> get(std::string fileSource, std::string mode);
    static InputReader<T> get();
    
    ~InputReader()
    {
//        if(_stream.is_open())
//            _stream.close();
    }
    
private:
    InputReader(std::string fileSource, std::string mode) : 
        _stream(std::fstream(fileSource.c_str(), std::ios::in))
    {
    }
    
    InputReader() : 
        _stream(std::fstream("/dev/stdin", std::ios::in))
    {
        //set default buffer
    }
    
    T _currentLine;
    std::fstream _stream;
};

template<class T>
T InputReader<T>::readLine()
{
    getline(_stream, _currentLine);
    return _currentLine;
}

template<class T>
InputReader<T> InputReader<T>::get(std::string fileSource, std::string mode = "w+")
{
    return InputReader<T>(fileSource, mode);
}

template<class T>
InputReader<T> InputReader<T>::get()
{
    return InputReader<T>();
}

#endif	/* INPUTREADER_H */

