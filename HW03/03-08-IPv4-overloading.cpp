#include <iostream>
#include <array>

class ipv4
{
public:
    std::array<unsigned char, 4> octets; // array of octets

public:
    // class constructors
    constexpr ipv4(): octets{{0}} {}
    constexpr ipv4(unsigned char const a, unsigned char const b, unsigned char const c, unsigned char const d): octets{{a,b,c,d}} {}
    explicit constexpr ipv4(unsigned long a):
        octets{ { static_cast<unsigned char>((a >> 24) & 0xFF),
                static_cast<unsigned char>((a >> 16) & 0xFF),
                static_cast<unsigned char>((a >> 8) & 0xFF),
                static_cast<unsigned char>(a & 0xFF) } } {}
    ipv4(ipv4 const & other) noexcept : octets(other.octets) {}

    // conversion to ulong
    constexpr unsigned long toUlong() const noexcept
    {
        return (static_cast<unsigned long>(octets[0]) << 24) |
            (static_cast<unsigned long>(octets[1]) << 16) |
            (static_cast<unsigned long>(octets[2]) << 8) |
            static_cast<unsigned long>(octets[3]);
    }

    // base operator overloading
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

    // increment/decrement operator overloading
    ipv4& operator++()
    {
        *this = ipv4(toUlong() + 1);
        return *this;
    }

    ipv4& operator++(int)
    {
        ++(*this);
        return *this;
    }

    ipv4& operator--()
    {
        *this = ipv4(toUlong() - 1);
        return *this;
    }

    ipv4& operator--(int)
    {
        --(*this);
        return *this;
    }

    // comparison operator overloading
    friend bool operator==(ipv4 const & a1, ipv4 const & a2) noexcept
    {
        return a1.octets == a2.octets;
    }

    friend bool operator!=(ipv4 const & a1, ipv4 const & a2) noexcept
    {
        return !(a1 == a2);
    }

    friend bool operator<(ipv4 const & a1, ipv4 const & a2) noexcept
    {
        return a1.toUlong() < a2.toUlong();
    }

    friend bool operator>(ipv4 const & a1, ipv4 const & a2) noexcept
    {
        return a2 < a1;
    }

    friend bool operator<=(ipv4 const & a1, ipv4 const & a2) noexcept
    {
        return !(a1 > a2);
    }

    friend bool operator>=(ipv4 const & a1, ipv4 const & a2) noexcept
    {
        return !(a1 < a2);
    }
};


int main()
{
    std::cout << "This program can output a range of IPv4 addresses by boundary values (from left to right or from right to left)" << std::endl;
    std::cout << "input 2 boundary values:" << std::endl;
    ipv4 ip1, ip2;
    std::cin >> ip1 >> ip2;
    if(std::cin.fail())
    {
        std::cout << "incorrect input!" << std::endl;
        return 0;
    }
    
    std::cout << "IPv4 address range:" << std::endl;
    
    if (ip1 < ip2)
    {
        for (ipv4 ip = ip1; ip <= ip2; ++ip)
        {
            std::cout << ip << std::endl;
        }
    }

    else
    {
        for (ipv4 ip = ip1; ip >= ip2; ip--)
        {
            std::cout << ip << std::endl;
        }
    }

    return 0;
}
