#include <AES.h>
#include <iostream>
#include <math.h>
#include <string>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "enter args!\n";
        std::cout << "Usage: ./lab2 filename \n";
        return -1;
    }

    std::string filename(argv[1]);
    AES aes;

    aes.encrypt(filename);
    aes.decrypt("encrypted_" + filename);

    return 0;
}
