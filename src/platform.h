#ifndef REDIS_PLATFORM_H
#define REDIS_PLATFORM_H
#ifdef _MSC_VER // WINDOWS


#   define PACK

#   define FD_SETSIZE 4096

#   pragma warning(disable: 4996)

#	include <winsock2.h>
#	include <ws2tcpip.h>

#	if defined(__MINGW32__)
#		error you can't build it on mingw mostly. wait for win32api for mingw released. http://sourceforge.net/p/mingw/bugs/1087/ http://sourceforge.net/p/mingw/bugs/1662/
#	else
#		include <mstcpip.h>
#	endif

#	define WIN32_LEAN_AND_MEAN
#	define NOMINMAX
#	include <windows.h>
#	include <io.h>
#	if defined( __MINGW32__ )
#		include <unistd.h>
#	endif

#   ifndef __FUNCTION__
#      ifndef __func__
#   	    define __FUNTION__ "%undefined_func%"
#      else
#   	    define __FUNTION__ __func__
#      endif
#   endif

#   ifndef __TIME__
#   	define __TIME__ "%undefined_time%"
#   endif

#   ifndef __DATE__
#   	define __DATE__ "%undefined_date%"
#   endif

#   define __WFILE__ 		WIDEN(__FILE__)
#   define __WFUNCTION__ 	WIDEN(__FUNCTION__)
#   define __WTIME__ 		WIDEN(__TIME__)
#   define __WDATE__ 		WIDEN(__DATE__)

#   ifndef EWOULDBLOCK
#   	define EWOULDBLOCK EAGAIN
#   endif

#   ifndef EINPROGRESS
#   	define EINPROGRESS EAGAIN
#   endif

#   ifndef TCP_QUICKACK
#   	define 	TCP_QUICKACK   12
#   endif

    inline int poll(struct pollfd* s, unsigned int count, int timeout)  { return (int)WSAPoll((struct pollfd*)s, count, timeout); };
    inline int close_platform(SOCKET s)                                 { return (int)closesocket(s); };

    inline int wsaToErrno(int errcode)
    {
        switch(errcode)
        {
        case WSAEBADF:				return EBADF;			//  10009 - File handle is not valid.
        case WSAEACCES:				return EACCES;			//  10013 - Permission denied.
        case WSAEFAULT:				return EFAULT;			//  10014 - Bad address.
        case WSAEINVAL:				return EINVAL;			//  10022 - Invalid argument.
        case WSAEMFILE:				return EMFILE;			//  10024 - Too many open files.
        case WSAEWOULDBLOCK:		return EWOULDBLOCK;		//	10035 - Not ready yet (Would block).
        case WSAEINPROGRESS:		return EINPROGRESS;		//  10036 - Operation now in progress.
        case WSAENOTSOCK:			return ENOTSOCK;		//	10038 - Not a socket.
        case WSAEMSGSIZE:			return EMSGSIZE;		//  10040 - Message too long.
        case WSAEPROTONOSUPPORT:	return EPROTONOSUPPORT;	//  10043 - Protocol not supported.
        case WSAEAFNOSUPPORT:		return EAFNOSUPPORT;	//  10047 - Address family not supported by protocol family.
        case WSAEADDRINUSE:			return EADDRINUSE;		//  10048 - Address already in use.
        case WSAEADDRNOTAVAIL:		return EADDRNOTAVAIL;	//  10049 - Cannot assign requested address.
        case WSAENETDOWN:			return ENETDOWN;		//  10050 - Network is down.
        case WSAENETUNREACH:		return ENETUNREACH;		//  10051 - Network is unreachable.
        case WSAENETRESET:			return ENETRESET;		//  10052 - Network dropped connection on reset.
        case WSAECONNABORTED:		return ECONNABORTED;	//  10053 - Software caused connection abort.
        case WSAECONNRESET:			return ECONNRESET;		//  10054 - Connection reset by peer.
        case WSAENOBUFS:			return ENOBUFS;			//  10055 - No buffer space available.
        case WSAENOTCONN:			return ENOTCONN;		//  10057 - Socket is not connected.
        case WSAETIMEDOUT:			return ETIMEDOUT;		//  10060 - Connection timed out.
        case WSAECONNREFUSED:		return ECONNREFUSED;	//  10061 - Connection refused.
        case WSAEHOSTUNREACH:		return EHOSTUNREACH;	//  10065 - No route to host.
        default:
            return errcode;
        };
    };

    typedef int mode_t;
    typedef int siginfo_t;
    typedef unsigned int rlim_t;

    struct sockaddr_un
    {
        u_short sun_family;               /* AF_UNIX */
        char    sun_path[108];            /* pathname */
    };

#include <sys/syslog.h>

#else // LINUX


#   define PACK __attribute__ ((__packed__))

inline int close_platform(int s) { return close_platform(s); };


#endif
#endif
