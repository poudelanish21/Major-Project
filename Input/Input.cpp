#include <iostream>
#include <vector>

unsigned int getEquivalentGrayCode(unsigned int Number) {

	return (Number >> 1) ^ Number;

}

void LogError(std::string Msg) {

	std::cout << "\n" << "Msg \t:" << Msg << "\n";

}

class BITS {

	unsigned int NumberOfBits = 0;

public:

	unsigned char* Data = nullptr;

	BITS(unsigned int NumberOfBitsRequired) {

		unsigned int BytesRequired = ceil(NumberOfBitsRequired / (8.0f));

		Data = new unsigned char[BytesRequired];

		memset(Data, 0, BytesRequired);

		NumberOfBits = NumberOfBitsRequired;

	}

	//For Debug
	void setBits(unsigned int Value) {

		for (unsigned int index = 0; index < NumberOfBits; index+=8) {

			this->Data[index / 8] = (Value >> index) & 0b11111111;

		}

	}

	//Under Development
	bool flip(unsigned int BitIndex = 0) {

		//Replace % 8 with & 7 for around 20% performance gain
		unsigned int ByteIndex = (BitIndex - (BitIndex % 8)) / 8;

		BitIndex = BitIndex % 8;

		unsigned char tempData = Data[ByteIndex];

		if ((tempData >> BitIndex) & 1) {

			tempData &= (UINT8_MAX - 1) << BitIndex;

		}
		else {

			tempData |= 1 << BitIndex;

		}

		Data[ByteIndex] = tempData;

		return true;
	}

	//Easy Access To Individual Bits In Array
	//!!!->Warning<-!!! Donot Write
	BITS operator[] (unsigned int Index) {

		BITS Obj = BITS(1);

		unsigned int tempIndex = (Index - (Index % 8)) / 8;

		char tempData = Data[tempIndex];

		Obj.setBits((tempData >> (Index % 8)) & 1);

		return Obj;

	}

	friend std::ostream& operator<<(std::ostream& stream, BITS Obj) {

		std::string Output = "";

		unsigned int BytesRequired = ceil(Obj.NumberOfBits / (8.0f));

		unsigned int Temp = 0;

		for (unsigned int Index = 0; Index < BytesRequired; Index++) {

			Temp = Obj.Data[Index];

			for (unsigned int BitIndex = 0; BitIndex < 8; BitIndex++) {

				if (Index * 8 + BitIndex >= Obj.NumberOfBits) {

					break;

				}

				((Temp >> BitIndex) & 1) ? Output += '1' : Output += '0';

			}

		}

		stream << Output;

		return stream;

	}

};


std::string convertIntoBinaryString(unsigned int Number) {

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

bool getBit(unsigned int Number, unsigned int bitPosition) {

	return (Number >> (bitPosition)) & 1;

}

std::string GetExpressionFromGroup(unsigned int* Array, unsigned int size, unsigned int inputs = 4) {

	unsigned int* matched = new unsigned int[inputs];

	memset(matched, 0, inputs);

	bool fullyMatched = false;

	bool temp = getBit(Array[0], 0);

	for (unsigned int i = 0; i < inputs; i++) {

		fullyMatched = true;

		temp = getBit(Array[0], i);

		for (unsigned int x = 0; x < size; x++) {

			if (getBit(Array[x], i) != temp) {

				fullyMatched = false;

			}

		}

		if (fullyMatched) {

			matched[inputs - 1 - i] = 1;
			matched[inputs - 1 - i] |= temp << 1;

		}
		else {

			matched[inputs - 1 - i] = 0;

		}

	}
#ifdef DEBUG
	for (unsigned int i = 0; i < inputs; i++) {

		std::cout << "\nBits["<<i<<"] :\t" << matched[i];

	}
#endif
	std::string digits[4] = { "A", "B", "C", "D" };//, "E", "F", "G", "H"

	std::string Output = "";

	for (unsigned int i = 0; i < inputs; i++) {

		if (matched[i]) {

			if (matched[i] >> 1) {

				Output += digits[i];

			}
			else {

				Output += (std::string("!") + std::string(digits[i]) + "");

			}

		}

	}

	return Output;

}

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


class TRUTH_TABLE {

public:

	enum Directions { NONE, UP, DOWN, LEFT, RIGHT };

	unsigned int** DataArray = nullptr;

	unsigned int NumberOfBits = 0;

	unsigned int x = 0, y = 0, size = 0;

	TRUTH_TABLE(unsigned int* Array, unsigned int NumberOfInputs) {

		NumberOfBits = NumberOfInputs;

		if (NumberOfBits & 1) {

			x = static_cast<unsigned int>(pow(2, (NumberOfBits + 1)/2));
			y = static_cast<unsigned int>(pow(2, (NumberOfBits - 1)/2));

		}
		else {

			x = static_cast<unsigned int>(pow(2, NumberOfBits / 2));
			y = static_cast<unsigned int>(pow(2, NumberOfBits / 2));

		}

		size = x * y;

		DataArray = new unsigned int* [x];

		for (unsigned int Index = 0; Index < x; Index++) {

			DataArray[Index] = new unsigned int[y];
			memset(DataArray[Index], 0, y);

		}

		for (unsigned int i = 0; i < x; i++) {

			for (unsigned int j = 0; j < y; j++) {

#pragma warning( push )
#pragma warning( disable : 4101)
				//Optimize !-No Need To Call getEquivalentGrayCode every time
				DataArray[getEquivalentGrayCode(i)][getEquivalentGrayCode(j)] = Array[i * y + j];

#pragma warning( pop ) 

			}

		}

	}

	Directions check(unsigned int X, unsigned int Y, std::vector<unsigned int>ones) {

		Directions Output = NONE;

		for (unsigned int i = 1; i < 5; i++) {

			

		}

		return Output;
	}

	std::vector<unsigned int> vGetOnes() {

		std::vector<unsigned int>Output;

		for (unsigned int i = 0; i < x; i++) {

			for (unsigned int j = 0; j < y; j++) {

				if (DataArray[i][j]) {

					Output.push_back(i * y + j);

				}

			}

		}

		return Output;

	}


	std::vector<std::vector<unsigned int>> vGetGroups() {

		std::vector<std::vector<unsigned int>>Output;

		std::vector<unsigned int>temp = vGetOnes();

		for (unsigned int i = 0; i < size; i++) {

			check((unsigned int)floor((float)i / y), i % y, temp);

		}

		return Output;

	}

	friend std::ostream& operator<< (std::ostream& stream, TRUTH_TABLE& Table) {

		for (unsigned int i = 0; i < Table.x; i++) {

			for (unsigned int j = 0; j < Table.y; j++) {

				stream << "\t[" << i << "][" << j << "]:" << Table.DataArray[i][j] << "\t";

			}

			stream << "\n";

		}

		return stream;

	}

	~TRUTH_TABLE() {

		for (unsigned int Index = 0; Index < x; Index++) {

			delete[] DataArray[Index];

		}

		delete DataArray;

	}

};

class Groups {

public:

	std::vector<std::vector<unsigned int>>GroupArray;

	//Set Vector
	Groups(std::vector<std::vector<unsigned int>>InputVector) {

		GroupArray = InputVector;

	}

	unsigned int ReduceGroups() {

		unsigned int Output = GroupArray.size();

		bool fullyMatched = true;

		std::vector<std::vector<unsigned int>>TempArray;

		for (unsigned int i = 0; i < GroupArray.size(); i++) {

			fullyMatched = true;

			for (unsigned int j = 0; j < GroupArray[i].size(); j++) {

				for (unsigned int k = 0; k < GroupArray.size(); k++) {
				
					if (i != k) {

						if (GroupArray[i][j] != GroupArray[k][j]) {

							fullyMatched = false;

						}

					}
				
				}

			}

			if (!fullyMatched) {

				TempArray.push_back(GroupArray[i]);

			}
			else {

				Output--;

			}

		}

		Output = GroupArray.size() - Output;

		GroupArray = TempArray;

		return Output;

	}

};


int main() {

	SOP_INPUT Input = SOP_INPUT("{ 1, 7};");

#ifdef DEBUG
	std::cout << "\nInputs Required:\t" << Input.BitsRequired;
	std::cout << "\nSize of array:\t" << Input.vArray.size();

	for (unsigned int i = 0; i < Input.vArray.size(); i++) {

		std::cout << "\n\tIndex [" << i << "] :\t" << Input.vArray[i];

	}
#endif

	TRUTH_TABLE Table = TRUTH_TABLE(Input.GetBooleanArray(), Input.BitsRequired);

	std::cout << Table;

	std::cout << "\n";

	std::vector<std::vector<unsigned int>> vArray = Table.vGetGroups();

	

}