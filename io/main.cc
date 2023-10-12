using namespace std;
#include <string>
#include <random>

#include <iostream>

#include <fstream>

using namespace std;

void appendFile(string filePath, string line)
{
    ofstream myfile;
    myfile.open(filePath, std::ios_base::app); // append option = std::ios_base::app

    myfile << line << "\n";
    myfile.close();
}
void readFile(string filePath)
{
    std::ifstream file(filePath); // Open the file named "example.txt" for reading

    if (!file.is_open())
    {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {                                   // Read the file line by line
        std::cout << line << std::endl; // Print each line
    }

    file.close(); // Close the file
}

#include <iostream>
#include <fstream>
#include <map>

int writeMap(string filePath)
{
    cout << "WRITING!\n";
    std::map<std::string, std::string> keyValuePairs = {
        {"key1", "value1z"},
        {"key2", "value2"},
        {"key3", "value3"}};

    for (const auto &pair : keyValuePairs)
    {
        string line = pair.first + "=" + pair.second;
        appendFile(filePath, line);
    }

    return 0;
}

#include <iostream>
#include <fstream>
#include <map>
#include <sstream>

int readMap(string filePath)
{
    cout << "READING!\n";
    std::ifstream file(filePath);
    if (!file)
    {
        std::cerr << "Failed to open file for reading." << std::endl;
        return 1;
    }

    std::map<std::string, std::string> readPairs;
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream lineStream(line);
        std::string key, value;
        if (std::getline(lineStream, key, '=') && std::getline(lineStream, value))
        {
            readPairs[key] = value;
        }
    }

    // Exporting all items read from file
    for (const auto &pair : readPairs)
    {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }

    file.close();
    return 0;
}

int main()
{
    cout << "starting.\n";

    string filePath = "/home/andrew/git/cpp_learning/io/data.txt";
    // readFile(filePath);
    // appendFile(filePath, "TEST!");

    writeMap(filePath);
    readMap(filePath);
    return 0;
}