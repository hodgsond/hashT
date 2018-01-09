/**********************************************
Author: Daniel Hodgson
main uses a command loop to take 
input from the user, which includes:
file->filename, for opening a text file
find->word,to see if a word exists in the file
size, to see the size of the table, and the
number of used elements in the table
end, to end the program
***********************************************/

#include <iostream>
#include <string>
#include "hashtable.h"
#include <fstream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <iterator>

using namespace std;

int main()
{
	hashtable<string, int> table;
	string command = "", fileName, word, result;
	cout << "Enter a command, ? for help.\n";
	while (command != "end")
	{
		cout << ">";
		cin >> command;
		if (command == "file")
		{
			cout << "file name? ";
			cin >> fileName;
			ifstream file(fileName);
			if (file.is_open())
			{
				while(!file.eof())
				{
					file >> word;
					transform(word.begin(), word.end(), word.begin(), ::tolower);
					if (word.back() < 'a' && word.size() > 1)
						word.pop_back();
					table.insert(word);
				}
			}
		}
		else if (command == "find")
		{
			cout << "word? ";
			cin >> word;
			table.lookup(word);
		}
		else if (command == "size")
		{
			cout << "Size of table: " << table.getSize() << endl;
			cout << "Number of words: " << table.getUsed() << endl;
			cout << "Number of collisions: " << table.getCollisions() << endl;
		}
		else if (command == "end")
			cout << "End of line.\n";
		else if (command == "display")
		{
			table.display();
		}
		else if (command == "?")
		{
			cout << "The commands are:\nfile : for opening a .txt file and parsing into our table\n"
			 << "find : checks our table for a word, and how many times that word appears\n"
			 << "size : see how large the table is, how many buckets are filled, how many uniqe words, and how many words\n"
			 << "end  : end the program\n";
		}
		else
			cout << "Unknown command, only use lowercase.\n";
	}
	return 0;
}