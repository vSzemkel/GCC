
#include <iostream>
#include <vector>
#include <list>
#include <tuple>

using namespace std;

/* Shift-Japko-B to build */
/* INCLUDE brane z ustawień XCode: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1 */
/* Aby odpalić debuggowanie w GDB trzeba podpisać kod https://sourceware.org/gdb/wiki/BuildingOnDarwin */

int main()
{
    vector<int> vs{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vs.push_back(36);
    vs[0] = 812;

    cout << "Hello GCC " << vs[0] << endl;

    float moc;
    tuple<string, float, float> piwo("Okocim", 5.6, 2.65);
    tie(ignore, moc, ignore) = piwo;
    cout << "Piwo " << get<string>(piwo) << " ma " << moc << "% alkoholu i kosztuje " << get<2>(piwo) << "PLN" << endl;

    list<int16_t> l;
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    auto n = *std::next(begin(l), 1);

    auto pos = std::find(begin(l), end(l), 30);
    if (pos != end(l))
        n = std::distance(begin(l), pos);

    auto a = 5;
    if (int b = a + 4; b > 1)
        cout << "This variable is inline declared: " << b << endl;

    return 0;
}