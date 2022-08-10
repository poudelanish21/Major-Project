#include <iostream>
#include <vector>

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
	std::string digits[4] = { "A", "B", "C", "D"};

	std::string Output = "";

	for (unsigned int i = 0; i < inputs; i++) {

		if (matched[i]) {

			if (matched[i] >> 1) {

				Output += digits[i];

			}
			else {

				Output += (std::string("!(") + std::string(digits[i]) + ")");

			}

		}

	}

	return Output;

}


class TRUTH_TABLE {

public:

	unsigned int* DataArray = nullptr;

	unsigned int NumberOfBits = 0;

	unsigned int x = 0, y = 0;

	TRUTH_TABLE(unsigned int* Array, unsigned int NumberOfInputs) {

		DataArray = Array;

		NumberOfBits = NumberOfInputs;

		if (NumberOfBits & 1) {



		}

	}




	std::vector<std::vector<int>> vGetGroups() {



	}

};

int main() {

	unsigned int arr[] = { 0, 1,2,3 };

	std::cout << "Expression is : " << GetExpressionFromGroup(arr, sizeof(arr)/4, 4);

}