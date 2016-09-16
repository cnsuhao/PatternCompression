#include "Compress.h"
#include <iostream>
int main(int argc, char const *argv[])
{
    /*if (argc == 1) {
        // return Compress::PatternCompress("input.txt", "output.txt");
		return Decompress::PatternDecompress("output.txt", "newoutput.txt");
    }else if (argc == 3)
    {
        return Compress::PatternCompress(argv[1], argv[2]);
    }
    else
    {
        return 0;
    }*/

	if (argc == 4 || argc == 5)
	{
		if (argv[1][0] == 'c')
		{
			bool opencl = true;
			if (argc == 5)
			{
				if (argv[4][0] == 't')
				{
					opencl = true;
				}
				else if (argv[4][0] == 'f')
				{
					opencl = false;
				}
			}
			return Compress::PatternCompress(argv[2], argv[3], opencl);
		}
		else if (argv[1][0] == 'd')
		{
			bool debug = false;
			if (argc == 5)
			{
				if (argv[4][0] == 't' || argv[4][0] == 'd')
				{
					debug = true;
				}
				else if (argv[4][0] == 'f')
				{
					debug = false;
				}
			}
			return Decompress::PatternDecompress(argv[2], argv[3], debug);
		}
		else
		{
			std::cout << "Invalid command.\n";
		}
	}
	else
	{
		std::cout << "Usage:\n\t";
		std::cout << "pc compress <input> <output> <true/false - Use OpenCL>\n\t";
		std::cout << "pc decompress <input> <output> <true/false - Pattern debugging>\n";
	}
	
}
