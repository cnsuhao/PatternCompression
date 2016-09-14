#include "Compress.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#ifdef __APPLE__
#include <math.h>
#endif


using namespace std;

// trim from end (in place)
static inline void rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(),
                         not1(ptr_fun<int, int>(isspace))).base(), s.end());
}

string ReplaceString(string subject, const string& search, const string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
    return subject;
}

void ComputeScore(vector<string>* combos, map<string, int>* scores, int i) {
	if ((*scores).find((*combos)[i]) == (*scores).end()) {}
	else {
		return;
	}
	int duplicates = 0;
	for (int n = 0; n < (*combos).size(); n++)
	{
		if ((*combos)[n] == (*combos)[i])
		{
			duplicates++;
		}
	}
	(*scores)[(*combos)[i]] = duplicates * (*combos)[i].size() - duplicates - 2 - (*combos)[i].size();
}

int Compress::PatternCompress(const char* InputFileName, const char* OutputFileName)
{
	ifstream infile; infile.open(InputFileName); if (!infile) { cout << "Couldn't open " << InputFileName << endl; return -1; }
	vector<string> lines = vector<string>();
	string curLine;
	while (!infile.eof()) {
		getline(infile, curLine);
		lines.push_back(curLine);
	}
	map<char, bool> characters = map<char, bool>();
	vector<char> availables = vector<char>();
	for (int i = 0; i <= 255; i++) {
		characters[i] = false;
		availables.push_back(i);
	}
	for (int i = 0; i < lines.size(); i++) {
		for (int n = 0; n < lines[i].size(); n++) {
			if (characters[lines[i][n]] == false) {
				characters[lines[i][n]] = true;
#ifdef __APPLE__
				availables.erase(std::remove(availables.begin(), availables.end(), lines[i][n]), availables.end());
#elif _WIN32
				auto it = std::find(availables.begin(), availables.end(), lines[i][n]);
				if (it != availables.end())	availables.erase(it);
#endif // Platform
			}
		}
	}
#ifdef __APPLE__
	availables.erase(std::remove(availables.begin(), availables.end(), '\n'), availables.end());
#elif _WIN32
	auto it = std::find(availables.begin(), availables.end(), '\n');
	if (it != availables.end())	availables.erase(it);
#endif // Platform
	cout << "Available characters: " << availables.size() << endl;
	// Combine lines 
	stringstream ss;
	for (int i = 0; i < lines.size(); i++)
	{
		ss << lines[i] << '\n';
	}
	string file = ss.str();
	// Calculate filesize
	size_t filesize = file.size() * sizeof(char);
    cout << "Input file size: " << filesize << endl;
	// Calculate max combination size
#ifdef _WIN32
	int maxComboSize = floorf(((float)ss.str().size()) / 2.0f);
#elif __APPLE__
    int maxComboSize = floor(((float)ss.str().size()) / 2.0f);
#endif
    
    string curStr;
    map<char, string> patterns;
    string pattern;
    vector<char> keys;
    unsigned int savedChars = 0;
    
    for (int j = 0; j < availables.size(); j++) {
        // Populate combinations vector
        vector<string> combinations = vector<string>();
        for (int i = 2; i < maxComboSize; i++)
        {
            for (int n = 0; n < file.size() - (i-1); n++)
            {
                curStr = file.substr(n, i);
                combinations.push_back(curStr);
            }
        }

        // Count combinations and score
        map<string, int> scores;
        //map<string, int> finalScores;
        int score = 0;
        //for_each(combinations.begin(), combinations.end(), [&scores](string val) { scores[val]++; });
        for (int i = 0; i < combinations.size(); i++)
        {
            ComputeScore(&combinations, &scores, i);
        }
        // Destroy negative scores
        for (auto p : scores) {
            if (p.second > 1)
            {
                if (p.second > score) {
                    score = p.second;
                    pattern = p.first;
                    
                }
                //finalScores[p.first] = p.second;
            }
        }
        if (score == 0) {
            break;
        }
        
        savedChars += score;
        
        patterns[availables[j]] = pattern;
        keys.push_back(availables[j]);
        cout << availables[j] << "\t\t" << patterns[availables[j]] << endl;
        
        //Replace all occurences of pattern
        stringstream strstrm;
        strstrm << availables[j];
        file = ReplaceString(file, patterns[availables[j]], strstrm.str());
    }
    
    savedChars++;
    cout << "Pattern count: " << keys.size() << endl;
    cout << "Saved characters: " << savedChars << endl;
    
    stringstream newss;
    newss << (char)keys.size();
    for (int i = keys.size()-1; i >= 0; i--) {
        newss << (char)patterns[keys[i]].size() << keys[i] << patterns[keys[i]];
    }
    cout << "Header: " << newss.str() << endl;
    rtrim(file);
    newss << file;
    size_t ofilesize = newss.str().size() * sizeof(char);
    cout << "Output file size: " << ofilesize << endl;
    cout << "Percent saved: " << 100 - ((float)ofilesize / (float)filesize)*100.0f << "%" << endl;
    //Write result to file
    ofstream outfile(OutputFileName);
    outfile << newss.str();
    outfile.close();
	infile.close();
	return 0;
}



/*
	// Boost Compute Init
	bc::device gpu = bc::system::default_device();
	bc::context context(gpu);
	bc::buffer buffers[3];
	buffers[0] = bc::buffer(context, filesize);
	buffers[1] = bc::buffer(context, componentSize);
	buffers[2] = bc::buffer(context, 2 * sizeof(float));
	string kernelSource;
	b::filesystem::load_string_file(b::filesystem::path("Compress.cl"), kernelSource);
	bc::program program = bc::program::create_with_source(kernelSource, context);
	program.build();
	bc::kernel kernel(program, "computePosition");
	kernel.set_arg(0, buffers[0]);
	kernel.set_arg(1, buffers[1]);
	kernel.set_arg(2, buffers[2]);
	bc::command_queue queue(context, gpu);
	*/
