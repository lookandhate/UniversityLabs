#include <string>
#include <iostream>

std::string from10To2Base(int num) {
	std::string temp;
	while (num > 0)
	{
		if (num % 2 == 0) temp.insert(temp.begin(), '0');
		else temp.insert(temp.begin(),'1');
		num = num / 2;
	}
	return temp;

}
void convertNum()
{
	double fractpart, intpart;
	double number = -14923.23645;
	fractpart = std::modf(number * -1, &intpart);

	std::string intpart_decimal = from10To2Base(intpart);
	std::string fractpart_decimal = from10To2Base(fractpart);

	std::cout << "1" << intpart_decimal << " " << fractpart_decimal;

}

void main()
{
	int num = 2;
	//auto converted = from10To2Base(num);
	//std::cout << converted;
	convertNum();
}