
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <cmath>

#include <asio.hpp>

class sGET_TIME{
    private:
    std::chrono::time_point<std::chrono::high_resolution_clock> nFirst;
    std::chrono::time_point<std::chrono::high_resolution_clock> nLast;
    std::chrono::duration<float> dDuration;
    public:
    sGET_TIME(){
        nFirst = std::chrono::high_resolution_clock::now();
    }
    ~sGET_TIME(){
        nLast = std::chrono::high_resolution_clock::now();
        dDuration = nLast - nFirst;
        printf("%f seconds\n\n");
    }
};
template <class T>
struct v2d_generic{
    T x = 0.0f;
    T y = 0.0f;

    v2d_generic() : x(0), y(0)                         {}
    v2d_generic(T _x, T _y) : x(_x), y(_y)             {}
    v2d_generic(const v2d_generic& v) : x(v.x), y(v.y) {}
    
    T mag()                                         { return sqrt(x * x + y * y);                              }
    v2d_generic norm()                              { T r = 1 / mag(); return v2d_generic(x*r, y*r);           }
    v2d_generic perp()                              { return v2d_generic(-y, x);                               }
    T dot  (const v2d_generic& rhs)                 { return this->x * rhs.x + this->y * rhs.y;                }
    T cross(const v2d_generic& rhs)                 { return this->x * rhs.x + this->y * rhs.y;                }

    v2d_generic operator+  (const v2d_generic& rhs) { return v2d_generic(this->x + rhs.x, this->y + rhs.y);    }
    v2d_generic operator-  (const v2d_generic& rhs) { return v2d_generic(this->x - rhs.x, this->y - rhs.y);    }
    v2d_generic operator*  (const T& rhs          ) { return v2d_generic(this->x * rhs, this->y * rhs);        }
    v2d_generic operator/  (const T& rhs          ) { return v2d_generic(this->x / rhs, this->y / rhs);        }
    v2d_generic& operator+=(const v2d_generic& rhs) { this->x += rhs.x; this->y += rhs.y; return *this;        }
    v2d_generic& operator-=(const v2d_generic& rhs) { this->x -= rhs.x; this->y -= rhs.y; return *this;        }
    v2d_generic& operator*=(const T rhs           ) { this->x *= rhs; this->y *= rhs; return *this;            }
    v2d_generic& operator/=(const T rhs           ) { this->x /= rhs; this->y /= rhs; return *this;            }
    T& operator[]          (std::size_t i         ) { return *((T*)this + i);                                  }
};

#if _WIN32_WINNT
    #if _WIN32_WINNT_WIN10
        #ifdef _WIN32_WINNT_WIN10
        #define _WIN32_WINNT 0x0A00
        #endif
    #elif _WIN32_WINNT_NT4
        #ifdef _WIN32_WINNT_NT4
        #define _WIN32_WINNT 0x0400
        #endif
    #elif _WIN32_WINNT_WIN2K
        #ifdef _WIN32_WINNT_WIN2K
        #define _WIN32_WINNT 0x0500
        #endif
    #elif _WIN32_WINNT_WINXP
        #ifdef _WIN32_WINNT_WINXP
        #define _WIN32_WINNT 0x0501
        #endif
    #elif _WIN32_WINNT_WS03
        #ifdef _WIN32_WINNT_WS03
        #define _WIN32_WINNT 0x0502
        #endif
    #elif _WIN32_WINNT_WIN6
        #ifdef _WIN32_WINNT_WIN6
        #define _WIN32_WINNT 0x0600
        #endif
    #elif _WIN32_WINNT_VISTA
        #ifdef _WIN32_WINNT_VISTA
        #define _WIN32_WINNT 0x0600
        #endif
    #elif _WIN32_WINNT_WS08
        #ifdef _WIN32_WINNT_WS08
        #define _WIN32_WINNT 0x0600
        #endif
    #elif _WIN32_WINNT_LONGHORN
        #ifdef _WIN32_WINNT_LONGHORN
        #define _WIN32_WINNT 0x0600
        #endif
    #elif _WIN32_WINNT_WIN7
        #ifdef _WIN32_WINNT_WIN7
        #define _WIN32_WINNT 0x0601
        #endif
    #elif _WIN32_WINNT_WIN8
        #ifdef _WIN32_WINNT_WIN8
        #define _WIN32_WINNT 0x0602
        #endif
    #elif _WIN32_WINNT_WINBLUE
        #ifdef _WIN32_WINNT_WINBLUE
        #define _WIN32_WINNT 0x0603
        #endif
    #else
        #ifdef _WIN32_WINNT_WINTHRESHOLD
        #define _WIN32_WINNT 0x0A00
        #endif
    #endif
    inline static void(*WinSockV)(int) = [](int i) mutable
    {
        sGET_TIME s;
        std::cout << "OS WinSock -V : (" << typeid(i).name() << ") : " << i << " : ";

        OSVERSIONINFOEX info;
        ZeroMemory(&info, sizeof(OSVERSIONINFOEX));
        info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
        GetVersionEx((LPOSVERSIONINFO)&info);

        printf("WINDOWS %u.%u\n", info.dwMajorVersion, info.dwMinorVersion); 
    };
#else
    inline static void(*WinSockV)(int) = [](int i) mutable
    {
        sGET_TIME s;
        std::cout << "OS WinSock -V : (" << typeid(i).name() << ") : " << i << "  not defined : ";

        OSVERSIONINFOEX info;
        ZeroMemory(&info, sizeof(OSVERSIONINFOEX));
        info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
        GetVersionEx((LPOSVERSIONINFO)&info);

        printf("WINDOWS %u.%u\n", info.dwMajorVersion, info.dwMinorVersion);
    };
#endif

/*
#define _WIN32_WINNT_NT4                    0x0400 // Windows NT 4.0
#define _WIN32_WINNT_WIN2K                  0x0500 // Windows 2000
#define _WIN32_WINNT_WINXP                  0x0501 // Windows XP
#define _WIN32_WINNT_WS03                   0x0502 // Windows Server 2003
#define _WIN32_WINNT_WIN6                   0x0600 // Windows Vista
#define _WIN32_WINNT_VISTA                  0x0600 // Windows Vista
#define _WIN32_WINNT_WS08                   0x0600 // Windows Server 2008
#define _WIN32_WINNT_LONGHORN               0x0600 // Windows Vista
#define _WIN32_WINNT_WIN7                   0x0601 // Windows 7
#define _WIN32_WINNT_WIN8                   0x0602 // Windows 8
#define _WIN32_WINNT_WINBLUE                0x0603 // Windows 8.1
#define _WIN32_WINNT_WINTHRESHOLD           0x0A00 // Windows 10
#define _WIN32_WINNT_WIN10                  0x0A00 // Windows 10
*/

int main(){
    WinSockV(_WIN32_WINNT);
    std::cin.get();
    return 0;
}