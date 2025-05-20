#ifndef STRING_H
#define STRING_H

#include <iostream>
#include "list.h"

class String
{
private:
    char *data; // Pointer to the string array
    unsigned int length;

    // returns the length of the string
    static unsigned int strLength(const char *str)
    {
        unsigned int len {0};
        while (str[len] != '\0') // while not the end of the string
        {
            len++;
        }
        return len;
    }

    // copie a string src to dest. including the null terminator
    static void strCopy(char *dest, const char *src)
    {
        while (*src)
        {
            *dest = *src;
            dest++;
            src++;
        }
        *dest = '\0';
    }

    // check if two strings are equal
    static bool strEqual(const char *a, const char *b)
    {
        while (*a && *b)
        {
            if (*a != *b)
            {
                return false;
            }
            a++;
            b++;
        }

        return true;
    }

public:
    // * Contructors

    // Constructor to initialize the string without value
    String() : data(new char[1]), length(0)
    {
        data[0] = '\0';
    }

    // Constructor to initialize the string with a value
    String(const char *str) 
        : data(new char[strLength(str) + 1]), length(strLength(str))
    {
        strCopy(data, str);
    }


    // Copy constructor
    String(const String &other) 
        : length(other.length), data(new char[other.length + 1])
    {
        strCopy(data, other.data);
    }

    // * Operator Overloading

    String &operator=(const String &other)
    {
        if (this != &other) // avoid autodestruct
        {
            delete[] data; // delete for change the value of the string
            length = other.length;
            data = new char[length + 1];
            strCopy(data, other.data);
        }

        return *this;
    }

    String operator+(const String &other) const
    {
        String result;

        delete[] result.data; // delete the old data
        result.length = length + other.length;
        result.data = new char[result.length + 1];

        strCopy(result.data, data);
        strCopy(result.data + length, other.data);

        return result;
    }

    String operator+(const char *other) const
    {
        unsigned int otherLength = strLength(other);

        String result;

        delete[] result.data; 
        result.length = length + otherLength;
        result.data = new char[result.length + 1];

        strCopy(result.data, data);
        strCopy(result.data + length, other);

        return result;

    }

    bool operator==(const String &other) const
    {
        return strEqual(data, other.data);
    }

    // * Destructor
    ~String()
    {
        delete[] data;
    }

    // * Methods

    // return the size of the string
    unsigned int size() const
    {
        return length;
    }

    // Method to make compatible with C-Style(c_str)
    const char *getRawData() const
    {
        return data;
    }
 

    // Method to split the string into a list of strings
    List<String> split(char delimiter) const
    {
        List<String> parts;
        unsigned int start {0};  // start position of the substring
        
        for (unsigned int i = 0; i <= length; i++)
        {
            // Process substrings at delimiter or end of string
            if (i == length || data[i] == delimiter)
            {
                // Only create substring if it has content                                                                                                                                                                  ]
                if (i - start > 0)  // Skip empty strings
                {
                    // Create the substring
                    char* part = new char[i - start + 1];
                    for (unsigned int j = 0; j < i - start; j++)
                    {
                        part[j] = data[start + j];
                    }
                    part[i - start] = '\0';
                    
                    // Add to list and clean up
                    parts.insertEnd(String(part));
                    delete[] part;
                }
                start = i + 1;  // update the start position for the next substring
            }
        }
        
        return parts;
    }


    static String toString(int value)
    {
        
        // Handle special case for 0
        if (value == 0)
        {
            return String("0");
        }

        bool isNegative {false};
        if(value < 0)
        {
            isNegative = true;
            value = -value;
        }

        char buffer[12]; // Enough for 32-bit int 
        int pos {11}; // Start from the end of the buffer

        buffer[pos--] = '\0'; // Null-terminate the string

        while(value > 0)
        {
            buffer[pos--] = '0' + (value % 10); // Convert digit to char
            value /= 10; // Remove the last digit
        }

        if(isNegative)
        {
            buffer[pos--] = '-';
        }

        return String(buffer + pos + 1); // Create a String from the buffer

    }

};

#endif // STRING_H
