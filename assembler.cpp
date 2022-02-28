#include <bits/stdc++.h>
using namespace std;
const char q = '\n';
struct OPCODE
{
	string pneumonic; // pneumonic
	string opco;	  // opcode
};

// Hard-coding the class and mnemonic for respective opcode
struct OPCODE op[13] = {
	{"CLA", "0000"},
	{"LAC", "0001"},
	{"SAC", "0010"},
	{"ADD", "0011"},
	{"SUB", "0100"},
	{"BRZ", "0101"},
	{"BRN", "0110"},
	{"BRP", "0111"},
	{"INP", "1000"},
	{"DSP", "1001"},
	{"MUL", "1010"},
	{"DIV", "1011"},
	{"STP", "1100"}
	};
int getOP(string s)
{
	for (int i = 0; i < 13; ++i)
	{
		if (op[i].pneumonic == s)
			return i;
	}
	return -1;
}
int main()
{
	fstream f1, f2, f3;
	int LC = 0, id;
	string label, opcode, operand;
	f1.open("input.txt", ios::in);		  // open input.txt in read only mode
	f2.open("SymbolTable.txt", ios::out); // open SymbolTable.txt in write only mode, SymbolTable.txt contains symbols and labels with their respective address
	f3.open("OpcodeTable.txt", ios::out); // open OpcodeTable.txt in write only mode, OpcodeTable.txt contains assembly opcode with their respective opcode
	string str;
	vector<string> oper; // conatins all operands
	int count = 0;
	int yes = 0;

	while (!f1.eof())
	{
		getline(f1, str);
		stringstream ss;
		ss << str;
		ss >> label >> opcode >> operand;
		id = getOP(opcode);
		string comm;
		comm = label.substr(0, 1);

		if (comm == "#")
		{
			cout << "comment" << q;
			LC = LC + 12;
			continue;
		}
		if (((strcmp(label.c_str(), "STP") == 0) && count < 1))
		{
			++count;
			f3 << label.substr(0, opcode.length()) << '\t' << op[id].opco << endl;
			cout << label.substr(0, opcode.length()) << '\t' << op[id].opco << LC << endl;
			LC = LC + 12;
			continue;
		}
		if(count>1)
		{
			cout<<"ERROR:STP used multiple times";
		
		}
		if (oper.size() != 0)
		{
			if (strcmp(label.c_str(), "$") != 0)
			{
				for (int i = 0; i < oper.size(); i++)
				{
					if (label.c_str() == oper[i])
					{

						f2 << LC << '\t' << label.substr(0, label.length()) << endl;
						cout << LC << '\t' << label.substr(0, label.length()) << endl;
						LC = LC + 12;
						yes = 1;
						continue;
					}
				}
				if (yes == 1)
				{
					continue;
				}
			}
		}
		if (strcmp(label.c_str(), "$") != 0)
		{

			f2 << LC << "\t" << label.substr(0, label.length()) << endl; // returns a newly constructed string object with its value initialized to a copy of a sub-string of this object
			cout << LC << '\t' << label.substr(0, label.length()) << endl;
		}
		if (opcode.c_str() == op[id].pneumonic)
		{
			f3 << opcode.substr(0, opcode.length()) << '\t' << op[id].opco << endl;
			cout << opcode.substr(0, opcode.length()) << '\t' << op[id].opco << endl;
		}
		else
			{cout << opcode.substr(0, opcode.length()) << " does not exist!!" << q;
			return -1;}

		if ((strcmp(opcode.c_str(), "SAC") == 0) || (strcmp(opcode.c_str(), "ADD") == 0) ||
			(strcmp(opcode.c_str(), "SUB") == 0) ||
			(strcmp(opcode.c_str(), "BRZ") == 0) ||
			(strcmp(opcode.c_str(), "BRN") == 0) ||
			(strcmp(opcode.c_str(), "BRP") == 0) ||
			(strcmp(opcode.c_str(), "INP") == 0) ||
			(strcmp(opcode.c_str(), "DSP") == 0) ||
			(strcmp(opcode.c_str(), "MUL") == 0) ||
			(strcmp(opcode.c_str(), "DIV") == 0))
		{

			oper.push_back(operand.c_str());
		}
		LC = LC + 12;
	}
	if (count == 0)
		{cout << "STP is missing!!";
		}
		
	f1.close();
	f2.close();
	f3.close();
	return 0;
}