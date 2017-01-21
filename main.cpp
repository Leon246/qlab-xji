
#include "Quantlabcodingtest.h"

int main()
{
    query q;
    q.process("input.csv");
    std::ofstream output("output.csv");
    output << q;
    output.close();
    return 0;
}
