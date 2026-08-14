#include <iostream>
#include <string>
#include <sstream>
#include <vector>

int main() {
    std::string ipAddress;
    std::cout << "Enter an IPv4 address (e.g., 192.168.1.1): ";
    std::cin >> ipAddress;

    std::stringstream ss(ipAddress);
    std::string token;
    std::vector<int> octets;

    // Split and parse all 4 octets
    while (std::getline(ss, token, '.')) {
        try {
            octets.push_back(std::stoi(token));
        } catch (...) {
            std::cout << "Error: Invalid character input found." << std::endl;
            return 1;
        }
    }

    // Validate that we have exactly 4 octets
    if (octets.size() != 4) {
        std::cout << "Error: An IPv4 address must have exactly 4 octets separated by dots." << std::endl;
        return 1;
    }

    // Validate range of each individual octet
    for (int i = 0; i < 4; i++) {
        if (octets[i] < 0 || octets[i] > 255) {
            std::cout << "Error: Octet " << (i + 1) << " (" << octets[i] << ") is out of range (0-255)." << std::endl;
            return 1;
        }
    }

    int firstOctet = octets[0];

    std::cout << "\n================ IP ANALYSIS ================" << std::endl;

    // Check for Loopback Address first
    if (firstOctet == 127) {
        std::cout << "Special Status: LOOPBACK ADDRESS DETECTED" << std::endl;
        std::cout << "What is it?: A loopback address is used by your computer to route network traffic back to itself." << std::endl;
        std::cout << "Belongs to Range: Class A (Reserved entirely for local host testing)" << std::endl;
        std::cout << "Default Subnet Mask: 255.0.0.0" << std::endl;
        std::cout << "Class Range: 127.0.0.0 to 127.255.255.255" << std::endl;
        std::cout << "Total Networks in Class: 1 (The entire 127 network block is locked for loopback)" << std::endl;
        std::cout << "Usable Hosts per Subnet: 16,777,214 (2^24 - 2)" << std::endl;
        std::cout << "=============================================" << std::endl;
        return 0;
    }

    // Process standard classes
    if (firstOctet >= 0 && firstOctet <= 127) {
        std::cout << "Class: Class A" << std::endl;
        std::cout << "Default Subnet Mask: 255.0.0.0" << std::endl;
        std::cout << "Class Range: 0.0.0.0 to 127.255.255.255" << std::endl;
        std::cout << "Total Networks in Class: 128 (2^7 networks)" << std::endl;
        std::cout << "Total Hosts per Subnet: 16,777,216 (2^24)" << std::endl;
        std::cout << "Usable Hosts per Subnet: 16,777,214 (2^24 - 2)" << std::endl;
    } 
    else if (firstOctet >= 128 && firstOctet <= 191) {
        std::cout << "Class: Class B" << std::endl;
        std::cout << "Default Subnet Mask: 255.255.0.0" << std::endl;
        std::cout << "Class Range: 128.0.0.0 to 191.255.255.255" << std::endl;
        std::cout << "Total Networks in Class: 16,384 (2^14 networks)" << std::endl;
        std::cout << "Total Hosts per Subnet: 65,536 (2^16)" << std::endl;
        std::cout << "Usable Hosts per Subnet: 65,534 (2^16 - 2)" << std::endl;
    } 
    else if (firstOctet >= 192 && firstOctet <= 223) {
        std::cout << "Class: Class C" << std::endl;
        std::cout << "Default Subnet Mask: 255.255.255.0" << std::endl;
        std::cout << "Class Range: 192.0.0.0 to 223.255.255.255" << std::endl;
        std::cout << "Total Networks in Class: 2,097,152 (2^21 networks)" << std::endl;
        std::cout << "Total Hosts per Subnet: 256 (2^8)" << std::endl;
        std::cout << "Usable Hosts per Subnet: 254 (2^8 - 2)" << std::endl;
    } 
    else if (firstOctet >= 224 && firstOctet <= 239) {
        std::cout << "Class: Class D (Multicast)" << std::endl;
        std::cout << "Default Subnet Mask: N/A" << std::endl;
        std::cout << "Class Range: 224.0.0.0 to 239.255.255.255" << std::endl;
        std::cout << "Hosts per Subnet: N/A (Multicast streams stream data to destinations, not individual host subnets)" << std::endl;
    } 
    else if (firstOctet >= 240 && firstOctet <= 255) {
        std::cout << "Class: Class E (Experimental)" << std::endl;
        std::cout << "Default Subnet Mask: N/A" << std::endl;
        std::cout << "Class Range: 240.0.0.0 to 255.255.255.255" << std::endl;
        std::cout << "Hosts per Subnet: N/A (Reserved strictly for research)" << std::endl;
    }

    std::cout << "=============================================" << std::endl;
    return 0;
}
