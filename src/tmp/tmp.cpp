#include <rapidjson/document.h>
#include <rapidjson/allocators.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include <iostream>
using namespace std;
using namespace rapidjson;

void json_test(Document& d);
int main() {

	Document d;

	json_test(d);

	StringBuffer sb;
	Writer<StringBuffer>  w(sb);
	d.Accept(w);
	cout << sb.GetString();
	
	return 0;
}


void json_test (Document & d){

	d.SetObject();
	Document::AllocatorType& allocator = d.GetAllocator();
	Value  arr(kArrayType), v, k;
	
	Value obj;
	obj.SetObject();
	v.SetDouble(20.);
	obj.AddMember("sales", v, allocator);

	v.SetDouble(20000.);
	obj.AddMember("revenue", v, allocator);
	
	v.SetString("IBM",  allocator);
	obj.AddMember ("company", v, allocator);

	Value obj2; obj2.SetObject();
		obj2.AddMember("one", v.SetDouble(3.5), allocator);
		obj2.AddMember("two", v.SetDouble(4.5), allocator);
		obj2.AddMember("three", v.SetDouble(6.0), allocator);
	arr.PushBack (obj2, allocator);
	Value obj3; obj3.SetObject();
		obj3.AddMember("one", v.SetDouble(3.5), allocator);
		obj3.AddMember("two", v.SetDouble(4.5), allocator);
		obj3.AddMember("three", v.SetDouble(6.0), allocator);
	arr.PushBack (obj3, allocator);

	obj.AddMember ("array", arr, allocator);

	d.AddMember("stats", obj, allocator);
}
