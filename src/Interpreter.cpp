
#include <Interpreter.hpp>
#include <Program.hpp>

using namespace MutableCode;
using namespace std;

Interpreter::Interpreter(Program* prog)
{
	program = prog;
        
        // cheking if <program> is not NULL before continuing
        if (programm != NULL)
        {
            this->execute();
        }
        else
        {
            cout << "Emty program!" << endl;
        }
}

void Interpreter::exectue()
{
    
}