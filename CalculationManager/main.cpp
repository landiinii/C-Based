#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "ExpressionManager.h"

const int NUM_FILES = 5; // the total number of files to be read from

const std::string fileArray[NUM_FILES] = { "file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt" }; // the string aray containing the file names

// This will take a string temp and an ExpressionManager object and will execute an instruction from the string
// no return, but writes the results of the instruction into the ofs filestream
void parse_instruction(std::string temp, std::ofstream &ofs, ExpressionManager* aptr);

// This function is a platform independent way of reading files of various line ending types.
// It's definiton is at the bottom of the file, don't worry if you don't understand it.
namespace ta {
	std::istream& getline(std::istream& is, std::string& line);
}


int main() {

	std::ifstream ifs; // create the stream to read in from the files
	std::ofstream ofs; // create the output stream to write to an output file
	std::string temp; // used to store the current instruction
	ExpressionManager* expptr = NULL;//the ExpressionManager

	for (int i = 0; i < NUM_FILES; i++) {
		ifs.open(fileArray[i]); // open the file to read from
		ofs.open("out_" + fileArray[i]); // open the file to write to
		expptr = new ExpressionManager();

		if (!ifs.is_open()) { // if the file did not open, there was no such file
			std::cout << "File " << i + 1 << " could not open, please check your lab setup" << std::endl;
		}
		else {
			std::cout << "Reading file" << i + 1 << ".txt..." << std::endl;
		}
		
		std::cout << "Beginning out_file" << i + 1 << ".txt write" << std::endl;
		while (ta::getline(ifs, temp)) { // while there are more instructions to get,
			parse_instruction(temp, ofs, expptr); // parse the instructions using the ExpressionManager
		}
		std::cout << "File write complete" << std::endl << std::endl;
		if (expptr != NULL) {
			delete expptr;
			expptr = NULL;
		}
		ifs.close();
		ofs.close();
	}
	std::cout << "end" << std::endl; // indicate that the program has successfuly executed all instructions
	getchar();
	
	return 0;
}

void parse_instruction(std::string temp, std::ofstream &ofs, ExpressionManager* aptr) {
	std::string command, expression;
	std::stringstream ss(temp);

	if (!(ss >> command)) { return; } // get command, but if string was empty, return
	if (command == "isBalanced") { // command to add a new node as a head node
		if (aptr->isBalanced(ss.str().substr(11, std::string::npos))) { // use the rest of the stringstream as isBalanced input
			ofs << temp << " True" << std::endl;
		}
		else {
			ofs << temp << " False" << std::endl;
		}
	}
	else if (command == "postfixToInfix") { // command to remove a fighter from the arena (given the fighters name)
		expression = aptr->postfixToInfix(ss.str().substr(15, std::string::npos));
		ofs << temp << "\n  " << expression << std::endl;
	}
	else if (command == "postfixEvaluate") { // command to return a pointer to a fighter (given the name of the fighter)
		expression = aptr->postfixEvaluate(ss.str().substr(16, std::string::npos));
		ofs << temp << "\n  " << expression << std::endl;
	}
	else if (command == "infixToPostfix") { // command to get the number of fighters in the arena
		expression = aptr->infixToPostfix(ss.str().substr(15, std::string::npos));
		ofs << temp << "\n  " << expression << std::endl;
	}
	else { // invalid command, wrong input file format
		std::cout << "Command: \"" << command << "\"" << std::endl;
		std::cout << "Invalid command.  Do you have the correct input file?" << std::endl;
	}
}

// Version of getline which does not preserve end of line characters
namespace ta {
	std::istream& getline(std::istream& in, std::string& line) {
		line.clear();

		std::istream::sentry guard(in, true); // Use a sentry to maintain the state of the stream
		std::streambuf *buffer = in.rdbuf();  // Use the stream's internal buffer directly to read characters
		int c = 0;

		while (true) { // Continue to loop until a line break if found (or end of file)
			c = buffer->sbumpc(); // Read one character
			switch (c) {
			case '\n': // Unix style, return stream for further parsing
				return in;
			case '\r': // Dos style, check for the following '\n' and advance buffer if needed
				if (buffer->sgetc() == '\n') { buffer->sbumpc(); }
				return in;
			case EOF:  // End of File, make sure that the stream gets flagged as empty
				in.setstate(std::ios::eofbit);
				return in;
			default:   // Non-linebreak character, go ahead and append the character to the line
				line.append(1, (char)c);
			}
		}
	}
}
