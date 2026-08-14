#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int ip1, ip2, ip3, ip4;
    int prefix;
    char separator;

    cout << "Enter base IP address (e.g., 192.168.10.0): ";
    cin >> ip1 >> separator >> ip2 >> separator >> ip3 >> separator >> ip4;

    cout << "Enter CIDR prefix (e.g., 26 for /26): ";
    cin >> prefix;

    if (prefix < 24 || prefix > 30) {
        cout << "Error: This program currently supports Class C subnetting (CIDR 24 to 30)." << endl;
        return 1;
    }

    int hostBits = 32 - prefix;
    int range = 1 << hostBits;
    int subnetTotal = 256 / range;
    int hostTotal = range - 2;
    int subnetMask = 256 - range;

    cout << "\n--- General Subnet Information ---" << endl;
    cout << "Calculated Subnet Mask : 255.255.255." << subnetMask << endl;
    cout << "Total Usable Hosts     : " << hostTotal << " per subnet" << endl;
    cout << "Total Subnets Created  : " << subnetTotal << "\n" << endl;

    for (int n = 0; n < subnetTotal; n++) {

        int network = n * range;
        int firstHost = network + 1;
        int lastHost = network + range - 2;
        int broadcast = network + range - 1;

        cout << "Subnet " << n + 1 << endl;

        cout << "Network Address   : "
             << ip1 << "." << ip2 << "." << ip3 << "." << network << endl;

        cout << "First Host        : "
             << ip1 << "." << ip2 << "." << ip3 << "." << firstHost << endl;

        cout << "Last Host         : "
             << ip1 << "." << ip2 << "." << ip3 << "." << lastHost << endl;

        cout << "Broadcast Address : "
             << ip1 << "." << ip2 << "." << ip3 << "." << broadcast << endl;

        cout << "\nUsable IP Addresses:" << endl;

        for (int host = firstHost; host < broadcast; host++) {
            cout << "  "
                 << ip1 << "." << ip2 << "." << ip3 << "." << host << endl;
        }

        cout << endl;
    }

    return 0;
}
