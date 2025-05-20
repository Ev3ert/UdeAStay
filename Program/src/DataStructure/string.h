#ifndef STRING_H
#define STRING_H

#include <iostream>

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
    String()
    {
        data = new char[1];
        data[0] = '\0';
        length = 0;
    }

    // Constructor to initialize the string with a value
    String(const char *str)
    {
        length = strLength(str);
        data = new char[length + 1]; // +1 for the null terminator
        strCopy(data, str);
    }

    // Copy constructor
    String(const String &other) // reference to avoid copying
    {
        length = other.length;
        data = new char[length + 1]; // ? Why not use data = other.data;?
        strCopy(data, other.data);   // to avoid indefinide behavior
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
};

#endif // STRING_H
