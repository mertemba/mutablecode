
#include <Tape.hpp>
#include <Program.hpp>
#include <Operation.hpp>

#include <iostream>

using namespace MutableCode;
using namespace std;

int main()
{
	Tape tape;
	tape.write('2');
	tape.moveRight();
	cin>>tape;
	tape.moveLeft();
	//read out '2'
	char c = tape.read();
	cout<<c<<endl;
	
	//print '2', '?'
	cout<<tape;
	
	Program program;
	std::vector<Operation>* operations = program.getOperations();
	for(int i = 0; i<100; i++){
		operations->push_back(Operation::randomOp());
	}
	program.run();
	program.dump();
	
	return 0;
}
