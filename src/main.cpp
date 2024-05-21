#include "../includes/website.hpp"

int main(int argc, char *argv[])
{
    Website *utms = new Website(argv[1], argv[2], argv[3], argv[4]);
    utms->import();
    delete utms;
    return 0;
}