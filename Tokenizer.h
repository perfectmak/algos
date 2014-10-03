/* 
 * File:   Tokenizer.h
 * Author: perfectmak
 *
 */

#ifndef TOKENIZER_H
#define	TOKENIZER_H

#include <vector>
#include <string>
#include <algorithm>

// a Java style tokenizer using the power of c++ std::string

class Tokenizer{
public:
    Tokenizer(std::string str, std::string delimiter = " ")
    {
        _str = str;
        _strSize = _str.size();
        _delim = delimiter;
        _currentPos = _nextPos = 0;
    }
    
    std::string nextToken()
    {
        int first = _currentPos;        
        _currentPos = _nextPos;
        std::string subStr = _str.substr(first, (_currentPos - first));
        
        if(_currentPos != _strSize)
            _currentPos += _delim.size();
        return subStr;
    }
    
    bool hasNext()
    {        
        _nextPos = _findNextPoint(_currentPos);
        
        if(_nextPos == _currentPos)
        {
            if(_nextPos == _strSize)
            {
                return false;
            }
            else
            {
                _currentPos++;
                _nextPos = _findNextPoint(_currentPos);
                return true;
            }
        }
        
        return true;
    }
    
    std::vector<std::string> getAllTokens()
    {
        int oldCurrentPos = _currentPos;
        int oldNextPos = _nextPos;
        std::string token;
        
        _currentPos = 0;
        _nextPos = 0;
        
        while(hasNext())
        {
            token = nextToken();
            _allTokens.push_back(token);
        }
        
        _currentPos = oldCurrentPos;
        _nextPos = oldNextPos;
        
        return _allTokens;
    }
    
private:
    std::string _str;
    std::string _currentToken;
    std::string _delim;
    int _currentPos;
    int _nextPos;
    int _strSize;
    std::vector<std::string> _allTokens;
    
    int _findNextPoint(int start)
    {
        int nextPos = _str.find(_delim, _currentPos);
        if(nextPos != std::string::npos)
        {
            return nextPos;
        }
        else
        {
            return _strSize;
        }
    }
};

#endif	/* TOKENIZER_H */

