#include "Compress.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int Compress::PatternCompress(char* InputFileName, char* OutputFileName)
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
#ifdef __unix__
				availables.erase(std::remove(availables.begin(), availables.end(), lines[i][n]), availables.end());
#elif _WIN32
				auto it = std::find(availables.begin(), availables.end(), lines[i][n]);
				if (it != availables.end())	availables.erase(it);
#endif // Platform
			}
		}
	}
#ifdef __unix__
	availables.erase(std::remove(availables.begin(), availables.end(), '\n'), availables.end());
#elif _WIN32
	auto it = std::find(availables.begin(), availables.end(), '\n');
	if (it != availables.end())	availables.erase(it);
#endif // Platform
	cout << "Available characters: " << availables.size() << endl;
	cout << "Characters: " << endl;
	for (int i = 0; i < availables.size(); i++)
	{
		cout << availables[i];
	}
	// Combine lines 
	stringstream ss;
	for (int i = 0; i < lines.size(); i++)
	{
		ss << lines[i] << '\n';
	}
	// Calculate filesize
	size_t filesize = ss.str().size() * sizeof(char);
	// Calculate max combination size
	int maxComboSize = floorf(((float)ss.str().size()) / 2.0f);
	// Populate combinations vector
	vector<string> combinations = vector<string>();
	for (int i = 2; i < maxComboSize; i++)
	{
		for (int n = 0; n < ss.str().size() - (i-1); n++)
		{
			combinations.push_back(ss.str().substr(n, n+i));
		}
	}

	// Count combinations
	map<string, int> dup;
	for_each(combinations.begin(), combinations.end(), [&dup](string val) { dup[val]++; });
	cout << ss.str().size() << endl;


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


	infile.close();
	return 0;
}
