#ifndef STRING_H
#define STRING_H

#include "list.h"
#include "../Utils/metrics.h"
#include <iostream>
#include <fstream>

class String
{
private:
    char *data; // Pointer to the string array
    unsigned int length;

    // returns the length of the string
    static unsigned int strLength(const char *str)
    {
        unsigned int len{0};
        while (str[len] != '\0') // while not the end of the string
        {
            len++;
            Metrics::addIteration();
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

            Metrics::addIteration();
        }
        *dest = '\0';
    }

    // check if two strings are equal
    static bool strEqual(const char *a, const char *b)
    {
        while (*a && *b)
        {
            Metrics::addIteration();

            if (*a != *b)
            {
                return false;
            }
            a++;
            b++;
        }

        return (*a == *b); // check if both strings end at the same time
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
        Metrics::addMemory(length + 1);
        strCopy(data, str);
    }

    // Copy constructor
    String(const String &other)
        : length(other.length), data(new char[other.length + 1])
    {
        Metrics::addMemory(length + 1);
        strCopy(data, other.data);
    }

    // * Operator Overloading

    String &operator=(const String &other)
    {
        if (this != &other) // avoid autodestruct
        {
            Metrics::removeMemory(length + 1);
            delete[] data; // delete for change the value of the string

            length = other.length;
            data = new char[length + 1];

            Metrics::addMemory(length + 1);

            strCopy(data, other.data);
        }

        return *this;
    }

    String operator+(const String &other) const
    {
        unsigned int newLength = length + other.length;
        char *newData = new char[newLength + 1];

        strCopy(newData, data);
        strCopy(newData + length, other.data);

        return String(newData); // Use the constructor whit char*
    }

    String operator+(const char *other) const
    {
        unsigned int newLength = length + strLength(other);
        char *newData = new char[newLength + 1];

        strCopy(newData, data);
        strCopy(newData + length, other);

        return String(newData);
    }

    bool operator==(const String &other) const
    {
        return strEqual(data, other.data);
    }

    friend std::ostream &operator<<(std::ostream &os, const String &str)
    {
        os << str.data;
        return os;
    }

    operator const char *() const
    {
        return data;
    }

    String &operator+=(char c)
    {
        char str[2] = {c, '\0'};
        *this = *this + str;
        return *this;
    }

    String &operator+=(String &other)
    {
        *this = *this + other;
        return *this;
    }

    String &operator+=(const char *other)
    {
        *this = *this + other;
        return *this;
    }

    // * Destructor
    ~String()
    {
        Metrics::removeMemory(length + 1);
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
        unsigned int start{0}; // start position of the substring

        for (unsigned int i = 0; i <= length; i++)
        {
            // Process substrings at delimiter or end of string
            if (i == length || data[i] == delimiter)
            {
                // Only create substring if it has content                                                                                                                                                                  ]
                if (i - start > 0) // Skip empty strings
                {
                    // Create the substring
                    char *part = new char[i - start + 1];
                    for (unsigned int j = 0; j < i - start; j++)
                    {
                        part[j] = data[start + j];
                        Metrics::addIteration();
                    }
                    part[i - start] = '\0';

                    // Add to list and clean up
                    parts.insertEnd(String(part));
                    delete[] part;
                }
                start = i + 1; // update the start position for the next substring
            }
        }

        return parts;
    }

    // Funtion to convert a integer to String Type
    static String toString(int value)
    {

        // Handle special case for 0
        if (value == 0)
        {
            return String("0");
        }

        bool isNegative{false};
        if (value < 0)
        {
            isNegative = true;
            value = -value;
        }

        char buffer[12]; // Enough for 32-bit int
        int pos{11};     // Start from the end of the buffer

        buffer[pos--] = '\0'; // Null-terminate the string

        while (value > 0)
        {
            buffer[pos--] = '0' + (value % 10); // Convert digit to char
            value /= 10;                        // Remove the last digit
            Metrics::addIteration();
        }

        if (isNegative)
        {
            buffer[pos--] = '-';
        }

        return String(buffer + pos + 1); // Create a String from the buffer
    }

    static int toInt(const String &str)
    {
        if (str.length == 0)
        {
            return 0;
        }

        int value{0};
        int sing{1};
        unsigned int i{0};

        if (str.data[0] == '-')
        {
            sing = -1;
            i++;
        }
        else if (str.data[0] == '+')
        {
            i++;
        }

        while (str.data[i] != '\0')
        {
            Metrics::addIteration();

            if (str.data[i] >= '0' && str.data[i] <= '9')
            {
                value = value * 10 + (str.data[i] - '0');
            }
            else
            {
                break; // Stop if a non-digit character is found
            }
            i++;
        }

        return value * sing;
    }

    // Funtion to clear de String
    void clear()
    {
        Metrics::removeMemory(length);
        delete[] data;

        Metrics::addMemory(1);
        data = new char[1];

        data[0] = '\0';
        length = 0;
    }

    // The same funtionality of std::getLine but with custom string
    static bool getLine(std::istream &in, String &output)
    {
        output.clear();
        char ch;
        bool read{false};

        while (in.get(ch))
        {
            Metrics::addIteration();

            if (ch == '\n')
                break;
            output += ch;
            read = true;
        }

        return read;
    }
};

#endif // STRING_H
