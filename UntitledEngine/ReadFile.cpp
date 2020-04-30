
#include <string>
#include <json/json.h>
#include <iostream>
#include <fstream>
#include"LoadScene.h"
using namespace std;




/*void readFileJson()
{
	JSONCPP_STRING err;
	//Json::Reader reader;
	Json::Value root;
	
	


	ifstream in("test.json", ios::binary);
	//in.open("test.json", ios::binary);
	string rawJson = "in";
	const auto rawJsonLength = static_cast<int>(rawJson.length());

	Json::CharReaderBuilder builder;
	const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());

	if (!in.is_open())
	{
		cout << "Error opening file\n";
		return;
	}


	if (reader->parse(rawJson.c_str(), rawJson.c_str() + rawJsonLength, &root,&err))
	{

		string name = root["name"].asString();
		int age = root["age"].asInt();
		bool sex_is_male = root["sex_is_male"].asBool();

		cout << "My name is " << name << endl;
		cout << "I'm " << age << " years old" << endl;
		cout << "I'm a " << (sex_is_male ? "man" : "woman") << endl;


		string partner_name = root["partner"]["partner_name"].asString();
		int partner_age = root["partner"]["partner_age"].asInt();
		bool partner_sex_is_male = root["partner"]["partner_sex_is_male"].asBool();

		cout << "My partner's name is " << partner_name << endl;
		cout << (partner_sex_is_male ? "he" : "she") << " is "
			<< partner_age << " years old" << endl;


		cout << "Here's my achievements:" << endl;
		for (unsigned int i = 0; i < root["achievement"].size(); i++)
		{
			string ach = root["achievement"][i].asString();
			cout << ach << '\t';
		}
		cout << endl;

		cout << "Reading Complete!" << endl;
	}
	else
	{
		cout << "parse error\n" << endl;
	}

	in.close();
}*/