#include<sys/tarfs.h>
struct posix_header_ustar* traverse(char *filename);
struct posix_header_ustar* traverse_file(char *filename);
struct posix_header_ustar* traverse_file_content(char *filename);
struct posix_header_ustar* traverse_directory(char *filename);
uint64_t octaltodecimal(char *sy);
