#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>

int main() {
    rapidjson::Document d;
    d.SetObject();

    // Add key-value pairs
    rapidjson::Value key;
    rapidjson::Value value;

    key.SetString("name", d.GetAllocator());
    value.SetString("John", d.GetAllocator());
    d.AddMember(key, value, d.GetAllocator());

    key.SetString("age", d.GetAllocator());
    value.SetInt(30);
    d.AddMember(key, value, d.GetAllocator());

    key.SetString("city", d.GetAllocator());
    value.SetString("New York", d.GetAllocator());
    d.AddMember(key, value, d.GetAllocator());

    // Stringify the JSON document
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);

    std::cout << buffer.GetString() << std::endl;

    return 0;
}
