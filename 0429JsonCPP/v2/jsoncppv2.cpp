#include <iostream>
#include <fstream>
#include <string>
#include "jsoncpp/json.h"
using namespace std;
using namespace Json;
/*
[
	"luffy",19,170,false,
	["ace","sabo"],
	{"sex":"man","girlfriend":"Hancock"}
]
*/

void writeJson() {
	Value root;
	root.append("luffy");
	root.append(19);
	root.append(170);
	root.append(false);

	Value subArray;
	subArray.append("ace");
	subArray.append("sabo");
	root.append(subArray);

	Value obj;
	obj["sex"] = "man";
	obj["girlfriend"] = "Hancock";
	root.append(obj);

#if 1
	string json = root.toStyledString();//带换行符
#else
	FastWriter w;
	string json = w.write(root);//不带换行符的字符串
#endif
	//write -> ofstream --> wo
	//read  -> ifstream --> ri
	//我日
	ofstream ofs("test.json");
	ofs << json;
	ofs.close();


}

void readJson() {
	ifstream ifs("test.json");
	Reader rd;
	Value root;
	rd.parse(ifs, root);

	if (root.isArray()) {
		for (int i = 0; i < root.size(); i++)
		{
			Value item = root[i];
			if (item.isInt()) {
				cout << item.asInt() << ",";
			}
			else if (item.isString()) {
				cout << item.asString() << ",";
			}
			else if (item.isBool()) {
				cout << item.asBool() << ",";
			}
			else if (item.isArray()) {
				//直接输出数组中的内容
				for (int j = 0; j < item.size(); j++)
				{
					cout << item[j].asString() << ",";
				}
			}
			else if (item.isObject()) {
				Value::Members keys = item.getMemberNames();
				for (int k = 0; k < keys.size(); k++)
				{
					cout << keys.at(k) << ":" << item[keys[k]].asCString() << ",";
				}
			}
			cout << endl;
		}
	}
	else if (root.isObject()) {

	}
}

int main() {

	writeJson();
	readJson();
	return 0;
}