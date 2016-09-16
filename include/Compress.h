namespace Compress
{
	int PatternCompress(const char* InputFileName, const char* OutputFileName, bool useOpenCL = true);
}
namespace Decompress {
    int PatternDecompress(const char* InputFileName, const char* OutputFileName, bool debug = false);
}
