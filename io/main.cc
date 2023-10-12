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

int main()
{
    cout << "starting.\n";

    string filePath = "/home/andrew/git/cpp_learning/io/data.txt";
    readFile(filePath);
    appendFile(filePath, "TEST!");
    return 0;
}