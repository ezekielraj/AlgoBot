#ifndef STRINGCLEANER_H
#define STRINGCLEANER_H

#include <string>

class StringCleaner {
private:
    const std::string str; // original string
    std::string toRemove;  // string to remove

public:
    // Constructor
    StringCleaner(const std::string& s);

    // Setter for string to remove
    void setToRemove(const std::string& s);

    // Method to remove all occurrences of toRemove from str
    std::string removeAll() const;

    // Getter for original string
    std::string getOriginal() const;

    std::string url_encode(const std::string& value);
};

#endif // STRINGCLEANER_H
