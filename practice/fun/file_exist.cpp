#include <fstream>

ofstream out("test", ios::out);
if(!out)
{
    cout << "Error opening file.\n";
    return 1;
}

ifstream in("test", ios::in);
if(!in)
{
    cout << "Error opening file.\n";
    return 1;
}
