#include "Compress.h"
int main(int argc, char const *argv[])
{
    if (argc == 1) {
        return Compress::PatternCompress("input.txt", "output.txt", false);
    }else if (argc == 3)
    {
        return Compress::PatternCompress(argv[1], argv[2]);
    }
    else
    {
        return 0;
    }
	
}
