#include <iostream>
#include <array>

class ipv4
{
private:
    std::array<unsigned char, 4> octets; // array of octets

public:
    // class constructors
    constexpr ipv4(): octets{{0}} {}
    constexpr ipv4(unsigned char const a, unsigned char const b, unsigned char const c, unsigned char const d): octets{{a,b,c,d}} {}

    // operator overloading
    ipv4& operator=(ipv4 const & other) noexcept
    {
        octets = other.octets;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const ipv4& ip)
    {
        os << static_cast<int>(ip.octets[0]) << '.'
            << static_cast<int>(ip.octets[1]) << '.'
            << static_cast<int>(ip.octets[2]) << '.'
            << static_cast<int>(ip.octets[3]);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, ipv4& ip)
    {
        char p1, p2, p3;
        int a, b, c, d;
        is >> a >> p1 >> b >> p2 >> c >> p3 >> d;
        if (p1 == '.' && p2 == '.' && p3 == '.' && a >= 0 && a <= 255 && b >= 0 && b <= 255 && c >= 0 && c <= 255 && d >= 0 && d <= 255)
            ip = ipv4(a, b, c, d);
        else
            is.setstate(std::ios_base::failbit);
        return is;
    }
};


int main()
{
    std::cout << "My constructor test:" << std::endl;
    ipv4 ipRouter(192, 168, 1, 1);
    std::cout << "\trouter IPv4 address: " << ipRouter << std::endl;

    std::cout << "Default constructor test:" << std::endl;
    ipv4 ipUser;
    std::cout << "\tzero IPv4 address: " << ipUser << std::endl;

    std::cout << "IPv4 input test:" << std::endl << "\tenter your IPv4 address: ";
    std::cin >> ipUser;
    if(!std::cin.fail())
        std::cout << "\tentered IPv4 address: " << "" << ipUser << std::endl;
    else
        std::cout << "\tincorrect input!" << std::endl;

    std::cout << "Equality operator test:" << std::endl;
    ipv4 ipUserEqual = ipUser;
    std::cout << "\tIPv4 address equal to the entered one: " << ipUserEqual << std::endl;

    return 0;
}
