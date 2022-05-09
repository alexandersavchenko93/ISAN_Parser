#include <iostream>
#include <string>
#include <map>

using namespace std;

#define ISAN_SEPARATOR ','
#define PATH_SEPARATOR '.'
#define OPEN_SYMBOL '['
#define CLOSE_SYMBOL ']'

#define INT_TYPE "int"
#define STRING_TYPE "string"
#define ARRAY_TYPE "array"

enum CODE {
    ISAN_SYNTAX_ERROR = -2,
    ISAN_PATH_ERROR = -3,
    SUCCESS = 0
};

namespace
{
    map<string, pair<string,string>> elements; // <key, <type,value>>
    char pathType;
}

// GET_ARRAY
string GetArray(const string& isan, int& pos)
{
    string array;
    int openSymbolCount = 0;
    int closeSymbolCount = 0;

    for(; pos < isan.size(); ++pos)
    {
        if(isan[pos] == OPEN_SYMBOL)
        {
            openSymbolCount++;
        }
        
        if(isan[pos] == CLOSE_SYMBOL)
        {
            closeSymbolCount++;
        }
        
        array.push_back(isan[pos]);
        
        if(closeSymbolCount == openSymbolCount)
        {
            return array;
        }
    }
    return string();
}

// IDENTIFY_TYPE_OF_VALUE
string IdentifyTypeOfValue(string value) try
{
    stoi(value);
    return INT_TYPE;
}
catch(...)
{
    return STRING_TYPE;
}

//VALIDATE ISAN
int ValidateIsan(const string& isan)
{
    if((isan.front() != OPEN_SYMBOL) && (isan.back() != CLOSE_SYMBOL))
    {
        cerr << "ISAN SYNTAX ERROR: The first or last character of the isan data is not valid." << endl;
        return CODE::ISAN_SYNTAX_ERROR;
    }
    
    int openSymbolCount = 0;
    int closeSymbolCount = 0;
    
    for(const auto& el: isan)
    {
        if(el == OPEN_SYMBOL)
        {
            openSymbolCount++;
        }
        
        if(el == CLOSE_SYMBOL)
        {
            closeSymbolCount++;
        }
    }
    
    if(openSymbolCount != closeSymbolCount)
    {
        cerr << "ISAN SYNTAX ERROR: Input data ISAN is not valid because it has a different number of characters OPEN_SYMBOL and symbols CLOSE_SYMBOL." << endl;
        return CODE::ISAN_SYNTAX_ERROR;
    }
    
    return CODE::SUCCESS;
}

// PARSE_ISAN
int ParseIsan(const string& isan, string root) // defautl root - ""
{
    int index = 0;
    const int EMPTY_ISAN_SIZE = 2;
    string value, type, key;
    
    // Handling the case with an empty isan array
    if(isan.size() == EMPTY_ISAN_SIZE)
    {
        if(isan[0] == OPEN_SYMBOL && isan[1] == CLOSE_SYMBOL)
        {
            key = root + to_string(index);
            type = "array";
            value = "array";
            elements.insert(pair<string,pair<string,string>>(key,make_pair(type, value)));
        }
        return CODE::SUCCESS;
    }
    
    // Proccess
    for(int i = 0; i < isan.size(); ++i)
    {
        // Separator ',' handling
        if((isan[i] == ISAN_SEPARATOR)
           // Handling last element in the aray
            || ((isan[i] == CLOSE_SYMBOL) && (i == isan.size() - 1)))
        {
            key = root + to_string(index);
            type = IdentifyTypeOfValue(value);
            elements.insert(pair<string,pair<string,string>>(key,make_pair(type, value)));
            value.clear();
            type.clear();
            index++;
        }
        // Subarray handling
        else if(isan[i] == OPEN_SYMBOL && i != 0)
        {
            key = root + to_string(index);
            type = ARRAY_TYPE;
            value = ARRAY_TYPE;
            elements.insert(pair<string,pair<string,string>>(key,make_pair(type, value)));
            key.push_back(PATH_SEPARATOR);
            value.clear();
            type.clear();
            
            ParseIsan(GetArray(isan, i), key);
        }
        // Writing valid characters to a value
        else if(isalnum(isan[i]) ||
                isan[i] == '-')
        {
            value.push_back(isan[i]);
        }
    }
    return CODE::SUCCESS;
}

// VALIDATE_PATH
int ValidatePath(const string& path)
{
    if((path.back() == PATH_SEPARATOR) || (path.front() == PATH_SEPARATOR))
    {
        cerr << "ISAN PATH ERROR: Path cannot start or end with a dot"  << endl;
        return CODE::ISAN_PATH_ERROR;
    }
    
    if(path.back() == 'v' || path.back() == 't')
    {
        pathType = path.back();
    }
    else
    {
        cerr << "ISAN PATH ERROR: Not a valid end of the path, please use t or v symbol. Current Symbol: " << path.back()  << endl;
        return CODE::ISAN_PATH_ERROR;
    }
    
    string part;
    for(int i = 0; i < path.size() - 1; ++i)
    {
        if(path[i] == PATH_SEPARATOR)
        {
            if(part[0] == '0' && part.size() > 1)
            {
                cerr << "ISAN PATH ERROR: Element path cannot be in the format 0 + number. Index: " << i << endl;
                return CODE::ISAN_PATH_ERROR;
            }
            
            string type;
            type = IdentifyTypeOfValue(part);
            if(type != INT_TYPE || part.empty())
            {
                cerr << "ISAN PATH ERROR: Not a valid part of the path. Index: " << i << endl;
                return CODE::ISAN_PATH_ERROR;
            }
            
            part.clear();
            continue;
        }
        part.push_back(path[i]);
    }
    return CODE::SUCCESS;
}

// GET_ELEMENT
void GetElement(const string& path)
{
    string tmpPath = path;
    tmpPath.pop_back();
    auto el = elements.find(tmpPath);
    
    if(el == elements.end())
    {
        cout << "Element not found at specified path" << endl;
        return;
    }
    
    if(pathType == 't')
    {
        cout << el->second.first << endl;
    }
    else if(pathType == 'v')
    {
        cout << el->second.second << endl;
    }
}

// PRINT_RESULT
void PrintResult()
{
    for(auto el: elements)
    {
        cout<< "Address: "<< el.first << " Type: " << el.second.first << " Value: " << el.second.second << endl;
    }
}
