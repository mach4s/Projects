// RoughLexer.cpp : Defines the entry point for the console application.
//
#include "RoughLexer.h"
#include "A2Lexer.h"

int main()
{
	RuleSet_A2 ruleset;
	vector<string> A2_Lexer = ruleset.ruleSet_();
	// Calls the parsing functions and translators. 
	vector<string> A2iD_  = ruleset.parseID(A2_Lexer);
	vector<string> A2Key_ = ruleset.parseKey(A2_Lexer);
	vector<string> A2Op_  = ruleset.parseOp(A2_Lexer);

	for (int i = 0; i < A2_Lexer.size(); i++)
	{
		//cout << A2_Lexer[i] << endl;
	}

//------------------------------------------------------------------------------
	string Textword_ = "";
	string Textline_ = "";
	vector<std::string> dummyText;

	int at_Line = 0;
	int number_of_lines = 0;

	//Reads in the A2 Lexicon ruleset and puts it into A2RuleSet variable. 
	//Returns error if unable to open text file with rules. 
	string dummyline  = "";
	string text_ = "";
	ifstream dummyfile("DummyText.txt");
	if (dummyfile.is_open())
	{
		while (getline(dummyfile, dummyline))
		{
			++number_of_lines;

			string temp_ = "Line " + to_string(number_of_lines) + ": ";
			//IF STATEMENT - This section is designed to remove any comments
			//               written by the user. This is due to the fact that
			//               we are allowed to treat comments as whitespace up to newline char;
			//
			// FURTHER TESTING NEEDED ( )
			size_t comment_ = dummyline.find("//");
			if (comment_ != string::npos)
			{
				dummyline.erase(comment_, dummyline.length());
			}
			//Line Vector: Overall structure of the program stack.
			dummyText.push_back(temp_ + dummyline);
		}
		dummyfile.close();
	}
	else cout << "Unable to open file";

	for (int i = 0; i < dummyText.size(); i++)
	{
		//cout << dummyText[i] << endl;
	}

	int line_ = 0;
	bool intFlag   = false;
	bool signFlag  = false;
	bool floatFlag = false;
	string temp_digit = "";
	for (int i = 0; i < dummyText.size(); i++)
	{
		//Getting the line number and getting rid of the "Line String"
		++line_;
		string key_  = "Line " + to_string(line_) + ": ";
		size_t L_ine = dummyText[i].find(key_);
		if (L_ine != string::npos)
		{
			//-----------------------++++
			//Parsing of the string 
			string temp_ = dummyText[i];
			int floatcount_ = 0;
			temp_.erase(L_ine, key_.length());

			//FloatLoop
			for (int j = 0; j < temp_.length(); j++)
		    {
				//if (temp_[j] == ';') { break; } //end of line count

				size_t found_Float = temp_.find(".");
				if (found_Float != string::npos)
				{
					floatFlag = true;
					//Modify for more then one of the keyword.
					//Next_Token() function would go here.
					//TRY BLOCK
					try
					{
						if (isdigit(temp_[j]) && (temp_[j] != ';'))
						{
							if (floatFlag)
							{
								for (int l = j; l < temp_.length(); l++)
								{
									j = l;
									if (temp_[l] == ';') { break; } //end of line count
									if (temp_[l] == ' ') { break; } //space count

									++floatcount_;
									temp_digit += temp_[l];
								}
							}
						}
					}
					catch (int Error)
					{
						cout << "Error code: " << Error << endl;
					}
				}
				
				//Modify for more then one of the keyword.
				//Next_Token() function would go here.

				//IF-STATEMENT INTEGER CHECK
				if (!floatFlag)
				{
					//TRY BLOCK
					try
					{
						if (isdigit(temp_[j]) && (temp_[j] != ';'))
						{
							intFlag = true;
							temp_digit += temp_[j];
							//No out of bounds
							//Checks to see if there is a sign in leading number.
							//OPTIMIZE THIS LATER ()
							if ((j - 1) >= 0)
							{
								if (temp_[(j - 1)] == '-')
								{
									signFlag = true;
									//sign would go here
									//cout << temp_[(j - 1)] << endl;

								}
							}//END OF OUT-OF-BOUNDS-IF-STATEMENT
						}//END OF INTEGERCHECK-IF-STATEMENT
					}//END OF TRY
					catch (int Error) { cout << "Error code: " << Error << endl; }

				}//END OF INTEGER-IF-STATEMENT
			}//END OF INTERGER-FLOAT-LOOP-CHECK

			string token_ = "";
			string token_S = "";
			bool tokenCheck = false;
			for (int j = 0; j < temp_.length(); j++)
			{
				if (temp_[j] == '"')
				{
					for (int v = (j + 1); v < temp_.size(); v++)
					{
						token_S += temp_[v];
						if ((v + 1) < temp_.size())
						{
							if (temp_[(v+1)] == '"')
							{
								cout << "(Tok: id= " << A2iD_[3] << "line= " << line_ << " " << "str= " << "\"" << token_S << "\"" << ")" << endl;
								token_.clear();
								token_S.clear();
								j = (v);
								//break;
							}
						}

					}
				}
				if (temp_[j] == '=') 
				{
					cout << "(Tok: id= " << A2iD_[0] << "line= " << line_ << " " << "str= " << "\"" << token_ << "\"" << ")" << endl;
					if ((j + 1) < temp_.length()) { j = (j + 1); }//Reasses j index.
					token_.clear();
				}

				token_ += temp_[j];
				token_.erase(remove_if(token_.begin(), token_.end(), isspace), token_.end());
				token_S = token_;
				for (int z = 0; z < A2Op_.size(); z++)
				{
					token_S += 
					tokenCheck = (token_ == A2Op_[z]);
					if (tokenCheck) 
					{ 
						cout << "(Tok: id= " << A2iD_[z] << "line= " << line_ << " " << "str= " << "\"" << A2Op_[z] << "\"" << ")" << endl;
						token_.clear();
						tokenCheck = false;
					}
				}

				//if (temp_[j] == ';')
				//{
				//	cout << "(Tok: id= " << A2iD_[5] << "line= " << line_ << " " << "str= " << "\"" << A2Op_[5] << "\"" << ")" << endl;
				//} //end of line count
			}
		}

		//OUTPUT - Int
		if ((intFlag) && !(floatFlag))
		{
			cout << "(Tok: id= " << A2iD_[1] << "line= " << line_ << " " << "str= " << "\"" << temp_digit << "\" " << "int=" << temp_digit << ")" << endl;
			temp_digit.clear();
			intFlag = false;
		}
		//OUTPUT - Float
		else if (!(intFlag) && (floatFlag))
		{
			cout << "(Tok: id= " << A2iD_[2] << "line= " << line_ << " " << "str= " << "\"" << temp_digit << "\" " << "float=" << temp_digit << ")" << endl;
			temp_digit.clear();
			intFlag = false;
			floatFlag = false;
		}

	}

	std::cin.ignore();
	std::cin.ignore();

	return 0;
}
