#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
using namespace std;
// Key-Vlaue Pair

class KeyValue
{
private:
    string filename = "keyvalue.txt";
    unordered_map<string, string> memory_map;

public:
    void put(string key, string value);
    void get(string key);
    void load(string delimiter);
    void save();
};

void KeyValue::load(string delimiter)
{
    ifstream in;
    in.open(filename);
    if (in.is_open())
    {
        cout << "+++++++++++++++++++Data Loading+++++++++++++++++++" << endl;
        string s;
        while (getline(in, s))
        {
            size_t start = 0;
            size_t end = s.find(delimiter);
            vector<string> tokens;
            while (end != std::string::npos)
            {
                tokens.push_back(s.substr(start, end - start));
                start = end + delimiter.length();
                end = s.find(delimiter, start);
            }
            tokens.push_back(s.substr(start));
            string k = tokens[0];
            string v = tokens[1];
            memory_map[k] = v;
        }
        in.close();
        cout << "+++++++++++++++++++Data Loaded+++++++++++++++++++" << endl;
    }
    else
    {
        cout << "+++++++++++++++++++Failed to load data+++++++++++++++++++" << endl;
    }
}

void KeyValue::put(string key, string value)
{
    memory_map[key] = value;
    cout << "+++++++++++++++++++Data Added+++++++++++++++++++" << endl;
}

void KeyValue::get(string key)
{
    if (memory_map.find(key) != memory_map.end())
    {
        cout << key << " " << memory_map[key] << endl;
    }
    else
    {
        cout << "Error: Key not found: " << key << endl;
    }
    cout << endl;
}

void KeyValue::save()
{
    ofstream on;
    on.open(filename);
    if (on.is_open())
    {
        for (auto i : memory_map)
        {
            on << i.first << " " << i.second << endl;
        }
        on.close();
        cout << "+++++++++++++++++++Data Saved Successfully+++++++++++++++++++" << endl;
    }
    else
    {
        cout << "+++++++++++++++++++Data Failed To Save+++++++++++++++++++" << endl;
    }
}

int main()
{
    KeyValue k;
    string delimiter = " ";
    k.load(delimiter); 

    while (true) 
    {
        cout << "> "; 
        string user_input;
        getline(cin, user_input); 

        
        vector<string> tokens;
        size_t start = 0;
        size_t end = user_input.find(delimiter);
        while (end != std::string::npos)
        {
            tokens.push_back(user_input.substr(start, end - start));
            start = end + delimiter.length();
            end = user_input.find(delimiter, start);
        }
        tokens.push_back(user_input.substr(start));
        

        
        if (tokens.empty() || tokens[0] == "")
        {
            continue; 
        }

        // --- Command handling ---
        if (tokens[0] == "PUT")
        {
            if (tokens.size() < 3)
            {
                cout << "Error: PUT requires a key and a value." << endl;
            }
            else
            {
                k.put(tokens[1], tokens[2]);
            }
        }
        else if (tokens[0] == "GET")
        {
            if (tokens.size() < 2)
            {
                cout << "Error: GET requires a key." << endl;
            }
            else
            {
                k.get(tokens[1]); 
            }
        }
        else if (tokens[0] == "SAVE") // <-- ADD THIS
        {
            k.save();
        }
        else if (tokens[0] == "EXIT") // <-- ADD THIS
        {
            k.save(); 
            break;    // Exit the while loop
        }
        else
        {
            cout << "Error: Unknown command." << endl;
        }
    } // --- End of while loop ---

    return 0;
}
