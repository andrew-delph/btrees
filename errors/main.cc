using namespace std;
#include <string>
#include <iostream>
#include <csignal>
#include <cstdlib>

void raiseError()
{
    cout << "RAISING ERROR.\n";

    throw("ss");
}

void handle_divide_by_zero(int signal)
{
    std::cerr << "Divide by zero error!" << std::endl;
    std::exit(EXIT_FAILURE); // or handle in some other way
}

int main()
{
    std::signal(SIGFPE, handle_divide_by_zero);
    cout << "starting.\n";

    try
    {

        raiseError();
    }
    catch (const std::exception &ex)
    {
        cout << "catch ex\n";
    }
    catch (const std::string &ex)
    {
        cout << "catch string\n";
    }
    catch (...)
    {
        cout << "catch ...\n";
        std::exception_ptr p = std::current_exception();
        cout << (p ? p.__cxa_exception_type()->name() : "null") << std::endl;
    }

    cout << 1 / 0 << "starting.\n";

    return 0;
}
