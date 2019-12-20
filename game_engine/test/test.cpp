#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/istreamwrapper.h>
#include <fstream>
#include <vector>
using namespace rapidjson;
using namespace std;



void enter(const Value& obj, size_t indent = 0) { //print JSON tree

    if (obj.IsObject()) { //check if object
        for (Value::ConstMemberIterator itr = obj.MemberBegin(); itr != obj.MemberEnd(); ++itr) {   //iterate through object   
            const Value& objName = obj[itr->name.GetString()]; //make object value

            for (size_t i = 0; i != indent; ++i) //indent
                cout << " ";
            cout << itr->name.GetString() << ": "; //key name

            if (itr->value.IsNumber()) //if integer
                std::cout << itr->value.GetInt();

            else if (itr->value.IsString()) //if string
                std::cout << itr->value.GetString();


            else if (itr->value.IsBool()) //if bool
                std::cout << itr->value.GetBool();

            else if (itr->value.IsArray()) { //if array

                for (SizeType i = 0; i < itr->value.Size(); i++) {
                    if (itr->value[i].IsNumber()) //if array value integer
                        std::cout << itr->value[i].GetInt();

                    else if (itr->value[i].IsString()) //if array value string
                        std::cout << itr->value[i].GetString();

                    else if (itr->value[i].IsBool()) //if array value bool
                        std::cout << itr->value[i].GetBool();

                    else if (itr->value[i].IsObject()) { //if array value object
                        cout << "\n  ";
                        const Value& m = itr->value[i];
                        for (auto& v : m.GetObject()) { //iterate through array object
                            if (m[v.name.GetString()].IsString()) //if array object value is string
                                cout << v.name.GetString() << ": " << m[v.name.GetString()].GetString();
                            else //if array object value is integer
                                cout << v.name.GetString() << ": " << m[v.name.GetString()].GetInt();

                            cout << "\t"; //indent
                        }
                    }
                    cout << "\t"; //indent
                }
            }

            cout << endl;
            enter(objName, indent + 1); //if couldn't find in object, enter object and repeat process recursively 
        }
    }
}

void SetUp(const Value& obj)
{
    if (obj.IsObject()) { //check if object
        for (Value::ConstMemberIterator itr = obj.MemberBegin(); itr != obj.MemberEnd(); ++itr) {   //iterate through object   
            if (obj[itr->name.GetString()].IsObject())
                SetUp(obj[itr->name.GetString()]);
            if(obj[itr->name.GetString()].IsArray())
            {
                for (SizeType i = 0; i < obj[itr->name.GetString()].Size(); i++)
                {
                    SetUp(obj[itr->name.GetString()][i]);
                }
            }
            if (obj[itr->name.GetString()].IsString())
                cout << obj[itr->name.GetString()].GetString() << "\n";
            if (obj[itr->name.GetString()].IsBool())
                cout << obj[itr->name.GetString()].GetBool() << "\n";
            if (obj[itr->name.GetString()].IsInt())
                cout << obj[itr->name.GetString()].GetInt() << "\n";
        }
    }
    if (obj.IsArray())
    {
        for (SizeType i = 0; i < obj.Size(); i++)
        {
            SetUp(obj[i]);
        }
    }
    if (obj.IsString())
        cout << obj.GetString() << "\n";
    if (obj.IsBool())
        cout << obj.GetBool() << "\n";
    if (obj.IsInt())
        cout << obj.GetInt() << "\n";
}

int main()
{
    ifstream ifs("D:/test.json");
    IStreamWrapper isw(ifs);
    Document document;
    document.ParseStream(isw);
    //const Value& a = d["audios"];
    //vector<int>* x = new vector<int>(0);
    //if (a.IsArray())
    const Value& a = document["Movable"];
    assert(a.IsArray());
    for (SizeType i = 0; i < a.Size(); i++)
    {
        SetUp(a[i]);
    } 
    return 0;
}