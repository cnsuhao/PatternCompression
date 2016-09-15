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
				if (argv[4] == "true")
				{
					opencl = true;
				}
				else if (argv[4] == "false")
				{
					opencl = false;
				}
			}
			return Compress::PatternCompress(argv[2], argv[3], opencl);
		}
		else if (argv[1][0] == 'd')
		{
			return Decompress::PatternDecompress(argv[2], argv[3]);
		}
		else
		{
			std::cout << "Invalid command.\n";
		}
	}
	else
	{
		std::cout << "Usage:\n\t";
		std::cout << "pc <compress/decompress> <input> <output> <true/false - Use OpenCL>\n";
	}
	
}
