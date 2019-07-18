//Ira Pohl
 //Copyright 2016
 //Supplementary example on overloading operator
 #include<iostream>
 #include<cstdint>
 using namespace std;
 enum class days:std::int8_t
 {SUNDAY,MONDAY,TUESDAY,WEDNESDAY,THURSDAY,FRIDAY,SATURDAY};
 //unlike plain enums C++11 enum class is typesafe and does not silently
 //convert to int

 ostream& operator<<(ostream& out, const days& d) //call by reference d- czyli odwoluje do miejsca w pamieci
 //overloading OPERATOR WYPISANIA
  {
	 switch(d){
		 case days::SUNDAY: out <<"SUNDAY"; break;
		 case days::MONDAY: out <<"MONDAY"; break;
		 case days::TUESDAY: out <<"TUESDAY"; break;
		 case days::WEDNESDAY: out <<"WEDNESDAY"; break;
		 case days::THURSDAY: out <<"THURSDAY"; break;
		 case days::FRIDAY: out <<"FRIDAY"; break;
		 case days::SATURDAY: out <<"SATURDAY"; break;
	 }
	 return out;
 }

inline days operator++(days& d) //PREFIX OPERATOR
{
	return  d = static_cast<days>((static_cast<int>(d) + 1) % 7);
	//ZWRACA WARTOSC ZWIEKSZONA OD RAZU
}

inline days operator++(days& d, int) //POSTFIX OPERATOR
{
	 days temp = d;
	 d = static_cast<days>((static_cast<int>(d) + 1) % 7);
	 return temp; //CZYLI ZWROCI WARTOSC TE SAM¥- NIE ZWIÊKSZON¥- TEMP
	 //ALE WARTOSC ZMIENNEJ d ZOSTALA ZWIEKSZONA
 }

 int main()
 {
	 days today{days::MONDAY};//tworzy zmienna today typu days i przypisuje jej wartosc MONDAY
	 std::cout << "Demonstrate class enum" << std::endl;
	 std::cout << "MONDAY VALUE IS " << today << std::endl;
	 std::cout << "TOMORROW IS " << ++today << std::endl;
	 std::cout << "DAY AFTER TOMORROW IS " << today++ << std::endl;
	 std::cout << "REPEAT (postfix) " << today << std::endl;
	 return 0;
 }
