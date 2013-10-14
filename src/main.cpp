
#include <Tape.hpp>
#include <Program.hpp>
#include <Operation.hpp>

#include <iostream>

using namespace MutableCode;
using namespace std;

void test(){
	Tape tape;
	tape.write(2);
	tape.moveRight();
	cout<<"input current tape value: ";
	cin>>tape;
	tape.moveLeft();
	//read out '2'
	char c = tape.read();
	//print '2', '?'
	cout<<tape<<endl<<endl;
}

int main()
{
	Program program;
	program.setState(BasicCharset[0]);
	std::vector<Operation>* operations = program.getOperations();
	for(int i = 0; i<1000; i++)
	{
		operations->push_back(Operation::randomOp());
	}
	program.run();
	cout<<program;
	
	return 0;
}
