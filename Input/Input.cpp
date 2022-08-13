#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <bitset>
#include <typeinfo>
#include <algorithm>

using namespace std;

void LogError(std::string Msg) {

	std::cout << Msg << "\n";

}

unsigned int BinaryToGrayCode(unsigned int Binary) {

	return ((Binary >> 1) ^ Binary);

}

class cell
{
public:
	int bl, br, bd, bu, x, y;
	cell(int temp)
	{

		x = temp / 4;//should pass the y index later
		y = temp % 4;
		string str = "";
		str = bitset<4>(temp).to_string(); // this is the binary index of the current cell in 4 bits
		bitset<4> b1(str);
		// now calculate the index of the next cell
		bitset<4> b2(b1);
		bitset<4> b3(b1);
		bitset<4> b4(b1);
		bitset<4> b5(b1);

		if ((b1[0] ^ b1[1]) == 0)
		{
			b2.flip(0);
			b3.flip(1);
		}
		else
		{
			b2.flip(1);
			b3.flip(0);
		}
		if ((b1[2] ^ b1[3]) == 0)
		{
			b4.flip(2);
			b5.flip(3);
		}
		else
		{
			b4.flip(3);
			b5.flip(2);
		}

		br = (int)(b2.to_ulong());
		bl = (int)(b3.to_ulong());
		bd = (int)(b4.to_ulong());
		bu = (int)(b5.to_ulong());
	}


};
int convert(int n)
{
	int dec = 0, i = 0, rem;

	while (n != 0)
	{
		rem = n % 10;
		n /= 10;
		dec += rem * pow(2, i);
		++i;
	}
	return dec;
}
unsigned int binaryToGray(unsigned int num)
{
	return (num >> 1) ^ num;
}

unsigned int grayToBinary(unsigned int num)
{
	unsigned int mask;
	for (mask = num >> 1; mask != 0; mask = mask >> 1)
	{
		num = num ^ mask;
	}
	return num;
}

class CanonicalForm {

	unsigned int _getNumberOfInputs(std::string InputExpression) {

		char operators[4] = { '.', '+', '!', ' ' };

		unsigned int count = 0;

		unsigned int Size = InputExpression.size();

		bool Found = false;

		for (unsigned int Index = 0; Index < Size; Index++) {

			for (unsigned int i = 0; i < 4; i++) {

				Found = false;

			}

		}
		return 0;

	}

	bool _setInputs(unsigned char* Inputs) {

		return true;

	}

public:
	unsigned int NumberOfInputs = 0;
	unsigned char* Inputs = nullptr;
	/// <summary>
	/// Just Providing Some Structure To The Input Of Canonical Form
	/// </summary>
	/// <param name="InputExpression">Always Pass A String</param>
	CanonicalForm(const char* InputExpression = nullptr) {

		if (InputExpression == nullptr) {

			LogError("Nothing Passed");
			::exit(-1);

		}

		*this = CanonicalForm(std::string(InputExpression));

	}
	CanonicalForm(std::string InputExpression = "") {

		if (InputExpression == "") {

			LogError("Nothing Passed");
			::exit(-1);

		}

		NumberOfInputs = _getNumberOfInputs(InputExpression);

		Inputs = new unsigned char[NumberOfInputs];

		_setInputs(Inputs);

	}

};

class SOP_INPUT {

public:

	std::vector<unsigned int> vArray;
	unsigned int BitsRequired = 0;

	/// <summary>
	/// Can Be Optimized
	/// Debug Mode Time Taken for 0 - 65536 => 203ms
	/// Release Mode Time Taken for 0 - 65536 => 14ms
	/// </summary>
	/// <param name="">Send Unsigned Integer As Input But It Only Takes Into Account 31 Bits</param>
	/// <returns></returns>
	static std::string convertIntoBinaryString(unsigned int Number) {

		std::string Output = "";

		for (unsigned int i = 1; i < 31; i++) {

			((Number >> (30 - i)) & 1) ? Output += '1' : Output += '0';

		}

		unsigned int Index = 0;

		//Minimize
		while (Output[Index] == '0' && !(Index > Output.size())) {

			Index++;

		}

		std::string Temp = "";

		for (unsigned int i = Index; i < Output.size(); i++) {

			Temp += Output[i];

		}

		Output = Temp;

		if (Output.size() == 0) {

			Output = "0";

		}

		return Output;

	}

	static bool isANumber(char Character) {

		if (Character >= '0' && Character <= '9') {

			return true;

		}

		return false;

	}

	//Checks Are Not Perfomed
	static unsigned int convertIntoNumber(std::string Characters) {

		unsigned int Size = Characters.size();

		if (Size > 9) {

			return UINT32_MAX;

		}

		unsigned int Number = 0;

		for (unsigned int Index = 0; Index < Size; Index++) {

			Number += static_cast<unsigned int>(pow(10, (Size - Index - 1))) * (Characters[Index] - '0');

		}

		return Number;

	}

	unsigned int GetLargestInteger(std::vector<unsigned int> Input) {

		unsigned int LargestNumber = 0;

		for (unsigned int Index = 0; Index < Input.size(); Index++) {

			if (Input[Index] > LargestNumber) {

				LargestNumber = Input[Index];

			}

		}

		return LargestNumber;

	}

	std::vector<unsigned int>GetNumberArray(std::string Expression, unsigned int& BitsRequired) {

		std::vector<unsigned int>Output;

		std::vector<std::string>StringArray;

		std::string Temporary = "";

		for (unsigned int Index = 0; Index < Expression.size(); Index++) {

			if (SOP_INPUT::isANumber(Expression[Index])) {

				Temporary += Expression[Index];

			}
			else if (Expression[Index] == ',') {

				StringArray.push_back(Temporary);
				Temporary = "";

			}

		}

		StringArray.push_back(Temporary);

		for (unsigned int Index = 0; Index < StringArray.size(); Index++) {

			Output.push_back(SOP_INPUT::convertIntoNumber(StringArray[Index]));

		}

		unsigned int LargestNumber = GetLargestInteger(Output);

		BitsRequired = convertIntoBinaryString(LargestNumber).size();

		return Output;

	}


	SOP_INPUT(std::string Input = "") {

		if (Input == "") {

			LogError("No Input Provided");

			::exit(-1);

		}

		vArray = GetNumberArray(Input, BitsRequired);

	}

	unsigned int* GetBooleanArray() {

		unsigned int Size = pow(2, BitsRequired);

		unsigned int* Output = new unsigned int[Size];
		memset(Output, 0, Size);

		for (unsigned int Index = 0; Index < Size; Index++) {

			for (unsigned int vArrayIndex = 0; vArrayIndex < vArray.size(); vArrayIndex++) {

				if (Index == vArray[vArrayIndex]) {

					Output[Index] = 1;

				}

			}

			if (Output[Index] > 1) {

				Output[Index] = 0;

			}

		}

		return Output;

	}

};

int main(int argc, char** argw) {

	unsigned int BitsRequired = 0;

	SOP_INPUT Obj = SOP_INPUT("{0,1,2,3,6,8,11,12};");

	unsigned int* Output = Obj.GetBooleanArray();


#ifdef DEBUG
	for (unsigned int Index = 0; Index < pow(2, Obj.BitsRequired); Index++) {

		std::cout << "Num : " << Index << " Binary : " << SOP_INPUT::convertIntoBinaryString(Index) << " Boolean : " << Output[Index] << "\n";

	}
#endif

	unsigned int x = 0, y = 0;

	if (Obj.BitsRequired & 1) {

		x = pow(2, (Obj.BitsRequired + 1) / 2);
		y = pow(2, (Obj.BitsRequired - 1) / 2);


	}
	else {

		x = pow(2, Obj.BitsRequired / 2);
		y = pow(2, Obj.BitsRequired / 2);

	}

	unsigned int* Arr = Obj.GetBooleanArray();

	unsigned char Inputs[] = { 'A', 'B', 'C', 'D' };
#ifdef DEBUG
	std::cout << "\nArray is : \n";
	for (unsigned int i = 0; i < x; i++) {

		for (unsigned int j = 0; j < y; j++) {

			std::cout << Arr[i * y + j] << "\t";

		}

		std::cout << "\n";

	}
#endif

	bool** Matrixx = new bool* [x * y];

	for (unsigned int i = 0; i < x; i++) {

		Matrixx[i] = new bool[x];
		memset(Matrixx[i], 0, x);

	}

	for (int j = 0; j < x; j++)
	{
		for (int k = 0; k < y; k++)
		{
			Matrixx[j][k] = Arr[j * y + k];

		}

	}

#ifdef DEBUG
	std::cout << "\nMatrix is : \n";

	for (unsigned int i = 0; i < x; i++) {

		for (unsigned int j = 0; j < y; j++) {

			std::cout << Matrixx[i][j] << "\t";

		}

		std::cout << "\n";

	}
#endif


	int m = 0, n = 0;
	int s = x * y;
	int count = 0;
	vector<vector<unsigned int>>grp;
	vector<unsigned int> group1;
	vector<unsigned int> group2;

	while (count < s)
	{
		if (Matrixx[m][n] == 1)
		{
			int centralindex = m * y + n;//this is the position where we are working on
			int id = 0;

			for (auto i = grp.begin(); i != grp.end(); ++i)
			{
				if (std::find(grp[id].begin(), grp[id].end(), centralindex) != grp[id].end()) {
					goto label1;
				}
				id++;
			}

			{

				int temp = centralindex;
				group1.push_back(temp);
				group2.push_back(temp);
				cell* cll;
				cell* cright;
				cell* cdown;
				cell* cleft;
				cell* cup;
				cll = new cell(temp);
				int temp_count = 1;
				int temp_count2 = 1;
				int tcright = 1;
				int tcleft = 0;
				int tcdown = 1;
				int tcup = 0;

				// index of left,right,down,up cell has been calculated and stored as bl,br,bd,bu on class cell
				{
					int q = cll->br / y;
					int r = cll->br % y;
					int ql = cll->bl / y;//****
					int rl = cll->bl % y;//***



				   //if (Matrixx[q][r] == 1 || Matrixx[ql][rl]==1)


					cright = new cell(cll->br);
					cleft = new cell(cll->bl);//*****
					int temp_1 = cright->x * y + cright->y;
					int temp_left = cleft->x * y + cleft->y;//*****


					while (temp_1 != temp && Matrixx[cright->x][cright->y] == 1)
					{

						temp_1 = cright->x * y + cright->y;
						temp_count++;
						tcright++;
						group1.push_back(temp_1);
						cll = new cell(temp_1);

						cright = new cell(cll->br);
					}
					if (temp_1 != temp)
					{
						while (temp_left != temp && Matrixx[cleft->x][cleft->y] == 1)
						{

							temp_left = cleft->x * y + cleft->y;
							temp_count++;
							tcleft++;
							group1.push_back(temp_left);
							cll = new cell(temp_left);

							cleft = new cell(cll->bl);
						}
					}


					// here checking in right direction
					int poptemp = 0;
					std::string BString = SOP_INPUT::convertIntoBinaryString(temp_count);
					if (BString[0] == '1')
					{
						BString[0] = '0';
						const char* temp = BString.c_str();

						stringstream strValue;
						strValue << temp;

						unsigned int intValue;
						strValue >> intValue;
						poptemp = convert(intValue);

					}
					for (int i = 0; i < poptemp; i++)
					{
						group1.pop_back();
					}
					cll = new cell(centralindex);

					//now going down
					q = cll->bd / y;
					r = cll->bd % y;
					int tempt = cll->bd;

					int temp_count_row = 1;
					int count_total_row = 1;//purpose of this should be implemented
					int dtcright = 1;
					int dtcleft = 0;
					int end = 0;

					while (Matrixx[q][r] == 1 && temp_count_row != x && end == 0)
					{


						if (Matrixx[q][r] == 1)
						{

							tempt = cll->bd;
							group1.push_back(tempt);
							int temp_count_check = 1;
							cll = new cell(cll->bd);
							cright = new cell(cll->br);
							cleft = new cell(cll->bl);//**
							int temp_1 = cright->x * y + cright->y;
							int temp_left = cleft->x * y + cleft->y;

							while (temp_count_check != temp_count && Matrixx[cright->x][cright->y] == 1 && dtcright != tcright)
							{

								temp_1 = cright->x * y + cright->y;
								temp_count_check++;
								dtcright++;
								group1.push_back(temp_1);
								cll = new cell(temp_1);

								cright = new cell(cll->br);
							}
							if (Matrixx[cleft->x][cleft->y] == 1) {
								temp_count_check = 1;


								while (temp_count_check != temp_count && Matrixx[cleft->x][cleft->y] == 1 && dtcleft != tcleft)
								{
									temp_left = cleft->x * y + cleft->y;

									temp_count_check++;
									dtcleft++;
									group1.push_back(temp_left);
									cll = new cell(temp_left);

									cleft = new cell(cll->bl);
								}
							}

							if (temp_count_check != temp_count)
							{
								for (int i = 0; i < temp_count_check; i++)
								{
									group1.pop_back();
								}
								end++;
							}
							else
							{
								temp_count_row++;
								count_total_row++;
							}
							cll = new cell(tempt);



						}

						q = cll->bd / y;
						r = cll->bd % y;



					}
					cll = new cell(centralindex);
					//now going up
					q = cll->bu / y;
					r = cll->bu % y;
					int tempq = cll->bu;
					int ucright = 1;
					int ucleft = 0;
					int endup = 0;

					if (temp_count_row != x)
					{
						temp_count_row = 1;


						while (Matrixx[q][r] == 1 && temp_count_row != x && endup == 0)
						{


							if (Matrixx[q][r] == 1)
							{
								tempq = cll->bu;
								group1.push_back(tempq);
								int temp_count_check = 1;
								cll = new cell(cll->bu);
								cright = new cell(cll->br);
								cleft = new cell(cll->bl);
								int temp_1 = cright->x * y + cright->y;
								int temp_left = cleft->x * y + cleft->y;

								while (temp_count_check != temp_count && Matrixx[cright->x][cright->y] == 1 && ucright != tcright)
								{

									temp_1 = cright->x * y + cright->y;

									temp_count_check++;
									ucright++;
									group1.push_back(temp_1);
									cll = new cell(temp_1);

									cright = new cell(cll->br);
								}
								if (Matrixx[cleft->x][cleft->y] == 1) {
									temp_count_check = 1;

									while (temp_count_check != temp_count && Matrixx[cleft->x][cleft->y] == 1 && ucleft != tcleft)
									{
										temp_left = cleft->x * y + cleft->y;
										temp_count_check++;
										ucleft++;
										group1.push_back(temp_left);
										cll = new cell(temp_left);

										cleft = new cell(cll->bl);
									}
								}

								if (temp_count_check != temp_count)
								{
									for (int i = 0; i < temp_count_check; i++)
									{
										group1.pop_back();

									}
									endup++;
								}
								else
								{
									temp_count_row++;
									count_total_row++;
								}
								cll = new cell(tempq);



							}
							q = cll->bu / y;
							r = cll->bu % y;



						}

					}
					//elimination of rows
					int rowtemp = 0;
					std::string BString1 = SOP_INPUT::convertIntoBinaryString(count_total_row);
					if (BString1[0] == '1')
					{
						BString1[0] = '0';
						const char* temp = BString1.c_str();

						stringstream strValue;
						strValue << temp;

						unsigned int intValue;
						strValue >> intValue;
						rowtemp = convert(intValue);

					}
					for (int i = 0; i < rowtemp; i++)
					{
						for (int j = 0; j < temp_count; j++)
						{
							group1.pop_back();
						}
					}
				}


				//now checking if there is vertical group
				{
					cll = new cell(centralindex);
					int q = cll->bd / y;
					int r = cll->bd % y;
					int qu = cll->bu / y;//****
					int ru = cll->bu % y;//***


				   //if (Matrixx[q][r] == 1 || Matrixx[ql][rl]==1)


					cdown = new cell(cll->bd);
					cup = new cell(cll->bu);//*****
					int temp_1 = cdown->x * y + cdown->y;
					int temp_up = cup->x * y + cup->y;//*****

					while (temp_1 != temp && Matrixx[cdown->x][cdown->y] == 1)
					{

						temp_1 = cdown->x * y + cdown->y;
						temp_count2++;
						tcdown++;
						group2.push_back(temp_1);
						cll = new cell(temp_1);

						cdown = new cell(cll->bd);
					}
					if (temp_1 != temp)
					{
						while (temp_up != temp && Matrixx[cup->x][cup->y] == 1)
						{

							temp_up = cup->x * y + cup->y;
							temp_count2++;
							tcup++;
							group2.push_back(temp_up);

							cll = new cell(temp_up);

							cup = new cell(cll->bu);
						}
					}


					// here checking in right direction
					int poptemp = 0;
					std::string BString = SOP_INPUT::convertIntoBinaryString(temp_count2);
					if (BString[0] == '1')
					{
						BString[0] = '0';
						const char* temp = BString.c_str();

						stringstream strValue;
						strValue << temp;

						unsigned int intValue;
						strValue >> intValue;
						poptemp = convert(intValue);

					}
					for (int i = 0; i < poptemp; i++)
					{
						group2.pop_back();
					}
					cll = new cell(centralindex);

					//now going right
					q = cll->br / y;
					r = cll->br % y;
					int tempt = cll->br;

					int temp_count_row = 1;
					int count_total_row = 1;
					int dtcdown = 1;
					int dtcup = 0;
					int end = 0;

					while (Matrixx[q][r] == 1 && temp_count_row != x && end == 0)
					{


						if (Matrixx[q][r] == 1)
						{

							tempt = cll->br;
							group2.push_back(tempt);
							cout << tempt << "pushed\n";
							int temp_count_check = 1;
							cll = new cell(cll->br);
							cdown = new cell(cll->bd);
							cup = new cell(cll->bu);//**
							int temp_1 = cdown->x * y + cdown->y;
							int temp_up = cup->x * y + cup->y;

							while (temp_count_check != temp_count2 && Matrixx[cdown->x][cdown->y] == 1 && dtcdown != tcdown)
							{

								temp_1 = cdown->x * y + cdown->y;
								temp_count_check++;
								dtcdown++;
								group2.push_back(temp_1);
								cll = new cell(temp_1);

								cdown = new cell(cll->bd);
							}
							if (Matrixx[cup->x][cup->y] == 1) {
								temp_count_check = 1;


								while (temp_count_check != temp_count2 && Matrixx[cup->x][cup->y] == 1 && dtcup != tcup)
								{
									temp_up = cup->x * y + cup->y;

									temp_count_check++;
									dtcup++;
									group2.push_back(temp_up);
									cll = new cell(temp_up);

									cup = new cell(cll->bu);
								}
							}

							if (temp_count_check != temp_count2)
							{
								for (int i = 0; i < temp_count_check; i++)
								{
									group2.pop_back();
								}
								end++;
							}
							else
							{
								temp_count_row++;
								count_total_row++;
							}
							cll = new cell(tempt);



						}

						q = cll->br / y;
						r = cll->br % y;



					}
					cll = new cell(centralindex);
					//now going left
					q = cll->bl / y;
					r = cll->bl % y;
					int tempq = cll->bl;
					int ucdown = 1;
					int ucup = 0;
					int endup = 0;

					if (temp_count_row != x)
					{
						temp_count_row = 1;


						while (Matrixx[q][r] == 1 && temp_count_row != x && endup == 0)
						{


							if (Matrixx[q][r] == 1)
							{
								tempt = cll->bl;
								group2.push_back(tempq);
								int temp_count_check = 1;
								cll = new cell(cll->bl);
								cdown = new cell(cll->bd);
								cup = new cell(cll->bu);
								int temp_1 = cdown->x * y + cdown->y;
								int temp_up = cup->x * y + cup->y;

								while (temp_count_check != temp_count2 && Matrixx[cdown->x][cdown->y] == 1 && ucdown != tcdown)
								{

									temp_1 = cdown->x * y + cdown->y;

									temp_count_check++;
									ucdown++;
									group2.push_back(temp_1);
									cll = new cell(temp_1);

									cdown = new cell(cll->bd);
								}
								if (Matrixx[cup->x][cup->y] == 1) {
									temp_count_check = 1;

									while (temp_count_check != temp_count2 && Matrixx[cup->x][cup->y] == 1 && ucup != tcup)
									{
										temp_up = cup->x * y + cup->y;
										temp_count_check++;
										ucup++;
										group2.push_back(temp_up);
										cll = new cell(temp_up);

										cup = new cell(cll->bu);
									}
								}

								if (temp_count_check != temp_count2)
								{
									for (int i = 0; i < temp_count_check; i++)
									{
										group2.pop_back();

									}
									endup++;
								}
								else
								{
									temp_count_row++;
									count_total_row++;
								}
								cll = new cell(tempq);



							}
							q = cll->bl / y;
							r = cll->bl % y;



						}

					}
					//elimination of rows
					int rowtemp2 = 0;
					std::string BString2 = SOP_INPUT::convertIntoBinaryString(count_total_row);
					if (BString2[0] == '1')
					{
						BString2[0] = '0';
						const char* temp = BString2.c_str();

						stringstream strValue;
						strValue << temp;

						unsigned int intValue;
						strValue >> intValue;
						rowtemp2 = convert(intValue);

					}
					for (int i = 0; i < rowtemp2; i++)
					{
						for (int j = 0; j < temp_count2; j++)
						{
							group2.pop_back();
						}
					}
				}

				if (group1.size() < group2.size())
				{
					grp.push_back(group2);

				}
				else
				{
					grp.push_back(group1);

				}
				group1.clear();
				group2.clear();


			}
		}


	label1:
		int temp = m * y + n;
		int a = grayToBinary(temp);
		a++;
		int b = binaryToGray(a);
		m = b / y;
		n = b % y;

		count++;
	}


	int id = 0;
	for (auto i = grp.begin(); i != grp.end(); ++i)
	{

		cout << "\nGrp" << id << " : ";
		for (auto j = grp[id].begin(); j != grp[id].end(); ++j)
			cout << *j << " ";
		id++;
	}



	delete[] Arr;
	for (unsigned int i = 0; i < x; i++) {

		delete[] Matrixx[i];

	}

}