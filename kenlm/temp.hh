# 1 "lm/model.hh"
# 1 "<組み込み>"
# 1 "<コマンドライン>"
# 1 "lm/model.hh"



# 1 "./lm/bhiksha.hh" 1
# 16 "./lm/bhiksha.hh"
# 1 "./lm/model_type.hh" 1



namespace lm {
namespace ngram {



typedef enum {PROBING=0, REST_PROBING=1, TRIE=2, QUANT_TRIE=3, ARRAY_TRIE=4, QUANT_ARRAY_TRIE=5} ModelType;


const ModelType HASH_PROBING = PROBING;
const ModelType TRIE_SORTED = TRIE;
const ModelType QUANT_TRIE_SORTED = QUANT_TRIE;
const ModelType ARRAY_TRIE_SORTED = ARRAY_TRIE;
const ModelType QUANT_ARRAY_TRIE_SORTED = QUANT_ARRAY_TRIE;

const static ModelType kQuantAdd = static_cast<ModelType>(QUANT_TRIE - TRIE);
const static ModelType kArrayAdd = static_cast<ModelType>(ARRAY_TRIE - TRIE);

}
}
# 17 "./lm/bhiksha.hh" 2
# 1 "./lm/trie.hh" 1



# 1 "./lm/weights.hh" 1





namespace lm {
struct Prob {
  float prob;
};

struct ProbBackoff {
  float prob;
  float backoff;
};
struct RestWeights {
  float prob;
  float backoff;
  float rest;
};

}
# 5 "./lm/trie.hh" 2
# 1 "./lm/word_index.hh" 1




# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/climits" 1 3
# 39 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/climits" 3
       
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/climits" 3

# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/limits.h" 1 3 4
# 34 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/limits.h" 3 4
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/syslimits.h" 1 3 4






# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/limits.h" 1 3 4
# 168 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/limits.h" 3 4
# 1 "/usr/include/limits.h" 1 3 4
# 11 "/usr/include/limits.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
# 12 "/usr/include/features.h" 3 4
# 1 "/usr/include/sys/cdefs.h" 1 3 4
# 43 "/usr/include/sys/cdefs.h" 3 4
# 1 "/usr/include/machine/_default_types.h" 1 3 4







# 1 "/usr/include/sys/features.h" 1 3 4
# 25 "/usr/include/sys/features.h" 3 4

# 25 "/usr/include/sys/features.h" 3 4
extern "C" {


# 1 "/usr/include/_newlib_version.h" 1 3 4
# 29 "/usr/include/sys/features.h" 2 3 4
# 513 "/usr/include/sys/features.h" 3 4
}
# 9 "/usr/include/machine/_default_types.h" 2 3 4
# 23 "/usr/include/machine/_default_types.h" 3 4
extern "C" {



typedef signed char __int8_t;

typedef unsigned char __uint8_t;
# 41 "/usr/include/machine/_default_types.h" 3 4
typedef short int __int16_t;

typedef short unsigned int __uint16_t;
# 63 "/usr/include/machine/_default_types.h" 3 4
typedef int __int32_t;

typedef unsigned int __uint32_t;
# 89 "/usr/include/machine/_default_types.h" 3 4
typedef long int __int64_t;

typedef long unsigned int __uint64_t;
# 120 "/usr/include/machine/_default_types.h" 3 4
typedef signed char __int_least8_t;

typedef unsigned char __uint_least8_t;
# 146 "/usr/include/machine/_default_types.h" 3 4
typedef short int __int_least16_t;

typedef short unsigned int __uint_least16_t;
# 168 "/usr/include/machine/_default_types.h" 3 4
typedef int __int_least32_t;

typedef unsigned int __uint_least32_t;
# 186 "/usr/include/machine/_default_types.h" 3 4
typedef long int __int_least64_t;

typedef long unsigned int __uint_least64_t;
# 200 "/usr/include/machine/_default_types.h" 3 4
typedef long int __intptr_t;

typedef long unsigned int __uintptr_t;
# 217 "/usr/include/machine/_default_types.h" 3 4
}
# 44 "/usr/include/sys/cdefs.h" 2 3 4

# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/stddef.h" 1 3 4
# 149 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/stddef.h" 3 4
typedef long int ptrdiff_t;
# 216 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/stddef.h" 3 4
typedef long unsigned int size_t;
# 46 "/usr/include/sys/cdefs.h" 2 3 4
# 13 "/usr/include/features.h" 2 3 4
# 12 "/usr/include/limits.h" 2 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 13 "/usr/include/limits.h" 2 3 4
# 169 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/limits.h" 2 3 4
# 8 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/syslimits.h" 2 3 4
# 35 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/limits.h" 2 3 4
# 42 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/climits" 2 3
# 6 "./lm/word_index.hh" 2


# 7 "./lm/word_index.hh"
namespace lm {
typedef unsigned int WordIndex;
const WordIndex kMaxWordIndex = 
# 9 "./lm/word_index.hh" 3 4
                               (0x7fffffff * 2U + 1)
# 9 "./lm/word_index.hh"
                                       ;
const WordIndex kUNK = 0;
}

typedef lm::WordIndex LMWordIndex;
# 6 "./lm/trie.hh" 2
# 1 "./util/bit_packing.hh" 1
# 21 "./util/bit_packing.hh"
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 1 3
# 41 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 3
       
# 42 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 3

# 1 "/usr/include/assert.h" 1 3 4






# 6 "/usr/include/assert.h" 3 4
extern "C" {


# 1 "/usr/include/_ansi.h" 1 3 4
# 15 "/usr/include/_ansi.h" 3 4
# 1 "/usr/include/newlib.h" 1 3 4
# 16 "/usr/include/_ansi.h" 2 3 4
# 1 "/usr/include/sys/config.h" 1 3 4



# 1 "/usr/include/machine/ieeefp.h" 1 3 4
# 5 "/usr/include/sys/config.h" 2 3 4
# 233 "/usr/include/sys/config.h" 3 4
# 1 "/usr/include/cygwin/config.h" 1 3 4
# 16 "/usr/include/cygwin/config.h" 3 4
extern "C" {
# 98 "/usr/include/cygwin/config.h" 3 4
}
# 234 "/usr/include/sys/config.h" 2 3 4
# 17 "/usr/include/_ansi.h" 2 3 4
# 10 "/usr/include/assert.h" 2 3 4
# 39 "/usr/include/assert.h" 3 4
void __attribute__((__cdecl__)) __assert (const char *, int, const char *) __attribute__ ((__noreturn__))
                                 ;
void __attribute__((__cdecl__)) __assert_func (const char *, int, const char *, const char *) __attribute__ ((__noreturn__))
                                 ;






}
# 43 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 2 3
# 22 "./util/bit_packing.hh" 2





# 1 "/usr/include/arpa/nameser_compat.h" 1 3 4
# 43 "/usr/include/arpa/nameser_compat.h" 3 4
# 1 "/usr/include/endian.h" 1 3 4
# 13 "/usr/include/endian.h" 3 4
# 1 "/usr/include/machine/endian.h" 1 3 4




# 1 "/usr/include/sys/_types.h" 1 3 4
# 24 "/usr/include/sys/_types.h" 3 4
# 1 "/usr/include/machine/_types.h" 1 3 4
# 17 "/usr/include/machine/_types.h" 3 4
typedef __int64_t __blkcnt_t;


typedef __int32_t __blksize_t;


typedef __uint32_t __dev_t;



typedef unsigned long __fsblkcnt_t;



typedef unsigned long __fsfilcnt_t;


typedef __uint32_t __uid_t;


typedef __uint32_t __gid_t;


typedef __uint64_t __ino_t;


typedef long long __key_t;


typedef __uint16_t __sa_family_t;



typedef int __socklen_t;
# 25 "/usr/include/sys/_types.h" 2 3 4
# 1 "/usr/include/sys/lock.h" 1 3 4
# 12 "/usr/include/sys/lock.h" 3 4
typedef void *_LOCK_T;
# 39 "/usr/include/sys/lock.h" 3 4
extern "C"
{

void __cygwin_lock_init(_LOCK_T *);
void __cygwin_lock_init_recursive(_LOCK_T *);
void __cygwin_lock_fini(_LOCK_T *);
void __cygwin_lock_lock(_LOCK_T *);
int __cygwin_lock_trylock(_LOCK_T *);
void __cygwin_lock_unlock(_LOCK_T *);

}
# 26 "/usr/include/sys/_types.h" 2 3 4
# 44 "/usr/include/sys/_types.h" 3 4
typedef long _off_t;





typedef int __pid_t;
# 65 "/usr/include/sys/_types.h" 3 4
typedef __uint32_t __id_t;
# 88 "/usr/include/sys/_types.h" 3 4
typedef __uint32_t __mode_t;





__extension__ typedef long long _off64_t;





typedef _off_t __off_t;


typedef _off64_t __loff_t;
# 114 "/usr/include/sys/_types.h" 3 4
typedef long _fpos_t;





typedef _off64_t _fpos64_t;
# 129 "/usr/include/sys/_types.h" 3 4
typedef long unsigned int __size_t;
# 145 "/usr/include/sys/_types.h" 3 4
typedef long signed int _ssize_t;
# 156 "/usr/include/sys/_types.h" 3 4
typedef _ssize_t __ssize_t;


# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/stddef.h" 1 3 4
# 357 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/stddef.h" 3 4
typedef unsigned int wint_t;
# 160 "/usr/include/sys/_types.h" 2 3 4



typedef struct
{
  int __count;
  union
  {
    wint_t __wch;
    unsigned char __wchb[4];
  } __value;
} _mbstate_t;



typedef _LOCK_T _flock_t;




typedef void *_iconv_t;



typedef unsigned long __clock_t;


typedef long __time_t;


typedef unsigned long __clockid_t;


typedef unsigned long __timer_t;
# 203 "/usr/include/sys/_types.h" 3 4
typedef unsigned short __nlink_t;
typedef long __suseconds_t;
typedef unsigned long __useconds_t;


typedef __builtin_va_list __va_list;
# 6 "/usr/include/machine/endian.h" 2 3 4
# 1 "/usr/include/machine/_endian.h" 1 3 4
# 13 "/usr/include/machine/_endian.h" 3 4
# 1 "/usr/include/_ansi.h" 1 3 4
# 14 "/usr/include/machine/_endian.h" 2 3 4
# 1 "/usr/include/bits/endian.h" 1 3 4
# 15 "/usr/include/machine/_endian.h" 2 3 4
# 23 "/usr/include/machine/_endian.h" 3 4
extern __inline__ __attribute__ ((__always_inline__)) __uint32_t __ntohl(__uint32_t);
extern __inline__ __attribute__ ((__always_inline__)) __uint16_t __ntohs(__uint16_t);

extern __inline__ __attribute__ ((__always_inline__)) __uint32_t
__ntohl(__uint32_t _x)
{
 __asm__("bswap %0" : "=r" (_x) : "0" (_x));
 return _x;
}

extern __inline__ __attribute__ ((__always_inline__)) __uint16_t
__ntohs(__uint16_t _x)
{
 __asm__("xchgb %b0,%h0"
  : "=Q" (_x)
  : "0" (_x));
 return _x;
}
# 7 "/usr/include/machine/endian.h" 2 3 4
# 14 "/usr/include/endian.h" 2 3 4
# 38 "/usr/include/endian.h" 3 4
# 1 "/usr/include/byteswap.h" 1 3 4
# 13 "/usr/include/byteswap.h" 3 4
extern "C" {


static inline unsigned short
__bswap_16 (unsigned short __x)
{
  return (__x >> 8) | (__x << 8);
}

static inline unsigned int
__bswap_32 (unsigned int __x)
{
  return (__bswap_16 (__x & 0xffff) << 16) | (__bswap_16 (__x >> 16));
}

static inline unsigned long long
__bswap_64 (unsigned long long __x)
{
  return (((unsigned long long) __bswap_32 (__x & 0xffffffffull)) << 32) | (__bswap_32 (__x >> 32));
}






}
# 39 "/usr/include/endian.h" 2 3 4
# 44 "/usr/include/arpa/nameser_compat.h" 2 3 4
# 52 "/usr/include/arpa/nameser_compat.h" 3 4
typedef struct {
 unsigned id :16;
# 70 "/usr/include/arpa/nameser_compat.h" 3 4
 unsigned rd :1;
 unsigned tc :1;
 unsigned aa :1;
 unsigned opcode :4;
 unsigned qr :1;

 unsigned rcode :4;
 unsigned cd: 1;
 unsigned ad: 1;
 unsigned unused :1;
 unsigned ra :1;


 unsigned qdcount :16;
 unsigned ancount :16;
 unsigned nscount :16;
 unsigned arcount :16;
} HEADER;
# 28 "./util/bit_packing.hh" 2


# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/stdint.h" 1 3 4
# 9 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/stdint.h" 3 4
# 1 "/usr/include/stdint.h" 1 3 4
# 13 "/usr/include/stdint.h" 3 4
# 1 "/usr/include/sys/_intsup.h" 1 3 4
# 49 "/usr/include/sys/_intsup.h" 3 4
       
       
       
       
       
       
       
# 201 "/usr/include/sys/_intsup.h" 3 4
       
       
       
       
       
       
       
# 14 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/sys/_stdint.h" 1 3 4
# 15 "/usr/include/sys/_stdint.h" 3 4
extern "C" {




typedef __int8_t int8_t ;



typedef __uint8_t uint8_t ;







typedef __int16_t int16_t ;



typedef __uint16_t uint16_t ;







typedef __int32_t int32_t ;



typedef __uint32_t uint32_t ;







typedef __int64_t int64_t ;



typedef __uint64_t uint64_t ;






typedef __intptr_t intptr_t;




typedef __uintptr_t uintptr_t;




}
# 15 "/usr/include/stdint.h" 2 3 4


extern "C" {



typedef __int_least8_t int_least8_t;
typedef __uint_least8_t uint_least8_t;




typedef __int_least16_t int_least16_t;
typedef __uint_least16_t uint_least16_t;




typedef __int_least32_t int_least32_t;
typedef __uint_least32_t uint_least32_t;




typedef __int_least64_t int_least64_t;
typedef __uint_least64_t uint_least64_t;
# 51 "/usr/include/stdint.h" 3 4
  typedef signed char int_fast8_t;
  typedef unsigned char uint_fast8_t;
# 61 "/usr/include/stdint.h" 3 4
  typedef long int int_fast16_t;
  typedef long unsigned int uint_fast16_t;
# 71 "/usr/include/stdint.h" 3 4
  typedef long int int_fast32_t;
  typedef long unsigned int uint_fast32_t;
# 81 "/usr/include/stdint.h" 3 4
  typedef long int int_fast64_t;
  typedef long unsigned int uint_fast64_t;
# 130 "/usr/include/stdint.h" 3 4
  typedef long int intmax_t;
# 139 "/usr/include/stdint.h" 3 4
  typedef long unsigned int uintmax_t;
# 482 "/usr/include/stdint.h" 3 4
}
# 10 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/stdint.h" 2 3 4
# 31 "./util/bit_packing.hh" 2
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstring" 1 3
# 39 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstring" 3
       
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstring" 3

# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/c++config.h" 1 3
# 194 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/c++config.h" 3
namespace std
{
  typedef long unsigned int size_t;
  typedef long int ptrdiff_t;




}
# 482 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/c++config.h" 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/os_defines.h" 1 3
# 483 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/c++config.h" 2 3


# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/cpu_defines.h" 1 3
# 486 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/c++config.h" 2 3
# 42 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstring" 2 3
# 1 "/usr/include/string.h" 1 3 4
# 11 "/usr/include/string.h" 3 4
# 1 "/usr/include/sys/reent.h" 1 3 4
# 9 "/usr/include/sys/reent.h" 3 4
extern "C" {




# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/stddef.h" 1 3 4
# 15 "/usr/include/sys/reent.h" 2 3 4
# 25 "/usr/include/sys/reent.h" 3 4
typedef unsigned int __ULong;
# 38 "/usr/include/sys/reent.h" 3 4
struct _reent;

struct __locale_t;






struct _Bigint
{
  struct _Bigint *_next;
  int _k, _maxwds, _sign, _wds;
  __ULong _x[1];
};


struct __tm
{
  int __tm_sec;
  int __tm_min;
  int __tm_hour;
  int __tm_mday;
  int __tm_mon;
  int __tm_year;
  int __tm_wday;
  int __tm_yday;
  int __tm_isdst;
};







struct _on_exit_args {
 void * _fnargs[32];
 void * _dso_handle[32];

 __ULong _fntypes;


 __ULong _is_cxa;
};
# 93 "/usr/include/sys/reent.h" 3 4
struct _atexit {
 struct _atexit *_next;
 int _ind;

 void (*_fns[32])(void);
        struct _on_exit_args _on_exit_args;
};
# 117 "/usr/include/sys/reent.h" 3 4
struct __sbuf {
 unsigned char *_base;
 int _size;
};
# 181 "/usr/include/sys/reent.h" 3 4
struct __sFILE {
  unsigned char *_p;
  int _r;
  int _w;
  short _flags;
  short _file;
  struct __sbuf _bf;
  int _lbfsize;






  void * _cookie;

  _ssize_t (__attribute__((__cdecl__)) * _read) (struct _reent *, void *, char *, size_t)
                                          ;
  _ssize_t (__attribute__((__cdecl__)) * _write) (struct _reent *, void *, const char *, size_t)

                                   ;
  _fpos_t (__attribute__((__cdecl__)) * _seek) (struct _reent *, void *, _fpos_t, int);
  int (__attribute__((__cdecl__)) * _close) (struct _reent *, void *);


  struct __sbuf _ub;
  unsigned char *_up;
  int _ur;


  unsigned char _ubuf[3];
  unsigned char _nbuf[1];


  struct __sbuf _lb;


  int _blksize;
  _off_t _offset;


  struct _reent *_data;



  _flock_t _lock;

  _mbstate_t _mbstate;
  int _flags2;
};
# 239 "/usr/include/sys/reent.h" 3 4
struct __sFILE64 {
  unsigned char *_p;
  int _r;
  int _w;
  short _flags;
  short _file;
  struct __sbuf _bf;
  int _lbfsize;

  struct _reent *_data;


  void * _cookie;

  _ssize_t (__attribute__((__cdecl__)) * _read) (struct _reent *, void *, char *, size_t)
                                          ;
  _ssize_t (__attribute__((__cdecl__)) * _write) (struct _reent *, void *, const char *, size_t)

                                   ;
  _fpos_t (__attribute__((__cdecl__)) * _seek) (struct _reent *, void *, _fpos_t, int);
  int (__attribute__((__cdecl__)) * _close) (struct _reent *, void *);


  struct __sbuf _ub;
  unsigned char *_up;
  int _ur;


  unsigned char _ubuf[3];
  unsigned char _nbuf[1];


  struct __sbuf _lb;


  int _blksize;
  int _flags2;

  _off64_t _offset;
  _fpos64_t (__attribute__((__cdecl__)) * _seek64) (struct _reent *, void *, _fpos64_t, int);


  _flock_t _lock;

  _mbstate_t _mbstate;
};
typedef struct __sFILE64 __FILE;





struct _glue
{
  struct _glue *_next;
  int _niobs;
  __FILE *_iobs;
};
# 319 "/usr/include/sys/reent.h" 3 4
struct _rand48 {
  unsigned short _seed[3];
  unsigned short _mult[3];
  unsigned short _add;




};
# 569 "/usr/include/sys/reent.h" 3 4
struct _reent
{
  int _errno;




  __FILE *_stdin, *_stdout, *_stderr;

  int _inc;
  char _emergency[25];


  int _unspecified_locale_info;
  struct __locale_t *_locale;

  int __sdidinit;

  void (__attribute__((__cdecl__)) * __cleanup) (struct _reent *);


  struct _Bigint *_result;
  int _result_k;
  struct _Bigint *_p5s;
  struct _Bigint **_freelist;


  int _cvtlen;
  char *_cvtbuf;

  union
    {
      struct
        {
          unsigned int _unused_rand;
          char * _strtok_last;
          char _asctime_buf[26];
          struct __tm _localtime_buf;
          int _gamma_signgam;
          __extension__ unsigned long long _rand_next;
          struct _rand48 _r48;
          _mbstate_t _mblen_state;
          _mbstate_t _mbtowc_state;
          _mbstate_t _wctomb_state;
          char _l64a_buf[8];
          char _signal_buf[24];
          int _getdate_err;
          _mbstate_t _mbrlen_state;
          _mbstate_t _mbrtowc_state;
          _mbstate_t _mbsrtowcs_state;
          _mbstate_t _wcrtomb_state;
          _mbstate_t _wcsrtombs_state;
   int _h_errno;
        } _reent;



      struct
        {

          unsigned char * _nextf[30];
          unsigned int _nmalloc[30];
        } _unused;
    } _new;



  struct _atexit *_atexit;
  struct _atexit _atexit0;



  void (**(_sig_func))(int);




  struct _glue __sglue;
  __FILE __sf[3];
};
# 766 "/usr/include/sys/reent.h" 3 4
extern struct _reent *_impure_ptr ;
extern struct _reent *const _global_impure_ptr ;

void _reclaim_reent (struct _reent *);





  struct _reent * __attribute__((__cdecl__)) __getreent (void);
# 792 "/usr/include/sys/reent.h" 3 4
}
# 12 "/usr/include/string.h" 2 3 4





# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/stddef.h" 1 3 4
# 18 "/usr/include/string.h" 2 3 4


# 1 "/usr/include/sys/_locale.h" 1 3 4
# 9 "/usr/include/sys/_locale.h" 3 4
struct __locale_t;
typedef struct __locale_t *locale_t;
# 21 "/usr/include/string.h" 2 3 4


extern "C" {

void * __attribute__((__cdecl__)) memchr (const void *, int, size_t);
int __attribute__((__cdecl__)) memcmp (const void *, const void *, size_t);
void * __attribute__((__cdecl__)) memcpy (void * , const void * , size_t);
void * __attribute__((__cdecl__)) memmove (void *, const void *, size_t);
void * __attribute__((__cdecl__)) memset (void *, int, size_t);
char *__attribute__((__cdecl__)) strcat (char *, const char *);
char *__attribute__((__cdecl__)) strchr (const char *, int);
int __attribute__((__cdecl__)) strcmp (const char *, const char *);
int __attribute__((__cdecl__)) strcoll (const char *, const char *);
char *__attribute__((__cdecl__)) strcpy (char *, const char *);
size_t __attribute__((__cdecl__)) strcspn (const char *, const char *);
char *__attribute__((__cdecl__)) strerror (int);
size_t __attribute__((__cdecl__)) strlen (const char *);
char *__attribute__((__cdecl__)) strncat (char *, const char *, size_t);
int __attribute__((__cdecl__)) strncmp (const char *, const char *, size_t);
char *__attribute__((__cdecl__)) strncpy (char *, const char *, size_t);
char *__attribute__((__cdecl__)) strpbrk (const char *, const char *);
char *__attribute__((__cdecl__)) strrchr (const char *, int);
size_t __attribute__((__cdecl__)) strspn (const char *, const char *);
char *__attribute__((__cdecl__)) strstr (const char *, const char *);

char *__attribute__((__cdecl__)) strtok (char *, const char *);

size_t __attribute__((__cdecl__)) strxfrm (char *, const char *, size_t);


int strcoll_l (const char *, const char *, locale_t);
char *strerror_l (int, locale_t);
size_t strxfrm_l (char *, const char *, size_t, locale_t);






char *__attribute__((__cdecl__)) strtok_r (char *, const char *, char **);


int __attribute__((__cdecl__)) bcmp (const void *, const void *, size_t);
void __attribute__((__cdecl__)) bcopy (const void *, void *, size_t);
void __attribute__((__cdecl__)) bzero (void *, size_t);


void __attribute__((__cdecl__)) explicit_bzero (void *, size_t);
int __attribute__((__cdecl__)) timingsafe_bcmp (const void *, const void *, size_t);
int __attribute__((__cdecl__)) timingsafe_memcmp (const void *, const void *, size_t);


int __attribute__((__cdecl__)) ffs (int);
char *__attribute__((__cdecl__)) index (const char *, int);


void * __attribute__((__cdecl__)) memccpy (void * , const void * , int, size_t);
# 86 "/usr/include/string.h" 3 4
char *__attribute__((__cdecl__)) rindex (const char *, int);


char *__attribute__((__cdecl__)) stpcpy (char *, const char *);
char *__attribute__((__cdecl__)) stpncpy (char *, const char *, size_t);


int __attribute__((__cdecl__)) strcasecmp (const char *, const char *);






char *__attribute__((__cdecl__)) strdup (const char *);

char *__attribute__((__cdecl__)) _strdup_r (struct _reent *, const char *);

char *__attribute__((__cdecl__)) strndup (const char *, size_t);

char *__attribute__((__cdecl__)) _strndup_r (struct _reent *, const char *, size_t);
# 121 "/usr/include/string.h" 3 4
int __attribute__((__cdecl__)) strerror_r (int, char *, size_t)

             __asm__ ("" "__xpg_strerror_r")

  ;







char * __attribute__((__cdecl__)) _strerror_r (struct _reent *, int, int, int *);


size_t __attribute__((__cdecl__)) strlcat (char *, const char *, size_t);
size_t __attribute__((__cdecl__)) strlcpy (char *, const char *, size_t);


int __attribute__((__cdecl__)) strncasecmp (const char *, const char *, size_t);


size_t __attribute__((__cdecl__)) strnlen (const char *, size_t);


char *__attribute__((__cdecl__)) strsep (char **, const char *);



char *__attribute__((__cdecl__)) strlwr (char *);
char *__attribute__((__cdecl__)) strupr (char *);



char *__attribute__((__cdecl__)) strsignal (int __signo);



int __attribute__((__cdecl__)) strtosigno (const char *__name);
# 192 "/usr/include/string.h" 3 4
# 1 "/usr/include/sys/string.h" 1 3 4
# 193 "/usr/include/string.h" 2 3 4

}
# 43 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstring" 2 3
# 71 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstring" 3
namespace std
{


  using ::memchr;
  using ::memcmp;
  using ::memcpy;
  using ::memmove;
  using ::memset;
  using ::strcat;
  using ::strcmp;
  using ::strcoll;
  using ::strcpy;
  using ::strcspn;
  using ::strerror;
  using ::strlen;
  using ::strncat;
  using ::strncmp;
  using ::strncpy;
  using ::strspn;
  using ::strtok;
  using ::strxfrm;
  using ::strchr;
  using ::strpbrk;
  using ::strrchr;
  using ::strstr;


  inline void*
  memchr(void* __s, int __c, size_t __n)
  { return __builtin_memchr(__s, __c, __n); }

  inline char*
  strchr(char* __s, int __n)
  { return __builtin_strchr(__s, __n); }

  inline char*
  strpbrk(char* __s1, const char* __s2)
  { return __builtin_strpbrk(__s1, __s2); }

  inline char*
  strrchr(char* __s, int __n)
  { return __builtin_strrchr(__s, __n); }

  inline char*
  strstr(char* __s1, const char* __s2)
  { return __builtin_strstr(__s1, __s2); }



}
# 32 "./util/bit_packing.hh" 2


# 33 "./util/bit_packing.hh"
namespace util {



inline uint8_t BitPackShift(uint8_t bit, uint8_t ) {
  return bit;
}
# 48 "./util/bit_packing.hh"
inline uint64_t ReadOff(const void *base, uint64_t bit_off) {






  return *reinterpret_cast<const uint64_t*>(reinterpret_cast<const uint8_t*>(base) + (bit_off >> 3));

}





inline uint64_t ReadInt57(const void *base, uint64_t bit_off, uint8_t length, uint64_t mask) {
  return (ReadOff(base, bit_off) >> BitPackShift(bit_off & 7, length)) & mask;
}



inline void WriteInt57(void *base, uint64_t bit_off, uint8_t length, uint64_t value) {







  *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(base) + (bit_off >> 3)) |=
    (value << BitPackShift(bit_off & 7, length));

}


inline uint32_t ReadInt25(const void *base, uint64_t bit_off, uint8_t length, uint32_t mask) {






  return (*reinterpret_cast<const uint32_t*>(reinterpret_cast<const uint8_t*>(base) + (bit_off >> 3)) >> BitPackShift(bit_off & 7, length)) & mask;

}

inline void WriteInt25(void *base, uint64_t bit_off, uint8_t length, uint32_t value) {







  *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(base) + (bit_off >> 3)) |=
    (value << BitPackShift(bit_off & 7, length));

}

typedef union { float f; uint32_t i; } FloatEnc;

inline float ReadFloat32(const void *base, uint64_t bit_off) {
  FloatEnc encoded;
  encoded.i = ReadOff(base, bit_off) >> BitPackShift(bit_off & 7, 32);
  return encoded.f;
}
inline void WriteFloat32(void *base, uint64_t bit_off, float value) {
  FloatEnc encoded;
  encoded.f = value;
  WriteInt57(base, bit_off, 32, encoded.i);
}

const uint32_t kSignBit = 0x80000000;

inline void SetSign(float &to) {
  FloatEnc enc;
  enc.f = to;
  enc.i |= kSignBit;
  to = enc.f;
}

inline void UnsetSign(float &to) {
  FloatEnc enc;
  enc.f = to;
  enc.i &= ~kSignBit;
  to = enc.f;
}

inline float ReadNonPositiveFloat31(const void *base, uint64_t bit_off) {
  FloatEnc encoded;
  encoded.i = ReadOff(base, bit_off) >> BitPackShift(bit_off & 7, 31);

  encoded.i |= kSignBit;
  return encoded.f;
}
inline void WriteNonPositiveFloat31(void *base, uint64_t bit_off, float value) {
  FloatEnc encoded;
  encoded.f = value;
  encoded.i &= ~kSignBit;
  WriteInt57(base, bit_off, 31, encoded.i);
}

void BitPackingSanity();



uint8_t RequiredBits(uint64_t max_value);

struct BitsMask {
  static BitsMask ByMax(uint64_t max_value) {
    BitsMask ret;
    ret.FromMax(max_value);
    return ret;
  }
  static BitsMask ByBits(uint8_t bits) {
    BitsMask ret;
    ret.bits = bits;
    ret.mask = (1ULL << bits) - 1;
    return ret;
  }
  void FromMax(uint64_t max_value) {
    bits = RequiredBits(max_value);
    mask = (1ULL << bits) - 1;
  }
  uint8_t bits;
  uint64_t mask;
};

struct BitAddress {
  BitAddress(void *in_base, uint64_t in_offset) : base(in_base), offset(in_offset) {}

  void *base;
  uint64_t offset;
};

}
# 7 "./lm/trie.hh" 2

# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstddef" 1 3
# 42 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstddef" 3
       
# 43 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstddef" 3


# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/stddef.h" 1 3 4
# 46 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstddef" 2 3
# 9 "./lm/trie.hh" 2



namespace lm {
namespace ngram {
struct Config;
namespace trie {

struct NodeRange {
  uint64_t begin, end;
};


struct UnigramValue {
  ProbBackoff weights;
  uint64_t next;
  uint64_t Next() const { return next; }
};

class UnigramPointer {
  public:
    explicit UnigramPointer(const ProbBackoff &to) : to_(&to) {}

    UnigramPointer() : to_(
# 32 "./lm/trie.hh" 3 4
                          __null
# 32 "./lm/trie.hh"
                              ) {}

    bool Found() const { return to_ != 
# 34 "./lm/trie.hh" 3 4
                                      __null
# 34 "./lm/trie.hh"
                                          ; }

    float Prob() const { return to_->prob; }
    float Backoff() const { return to_->backoff; }
    float Rest() const { return Prob(); }

  private:
    const ProbBackoff *to_;
};

class Unigram {
  public:
    Unigram() {}

    void Init(void *start) {
      unigram_ = static_cast<UnigramValue*>(start);
    }

    static uint64_t Size(uint64_t count) {

      return (count + 2) * sizeof(UnigramValue);
    }

    const ProbBackoff &Lookup(WordIndex index) const { return unigram_[index].weights; }

    ProbBackoff &Unknown() { return unigram_[0].weights; }

    UnigramValue *Raw() {
      return unigram_;
    }

    UnigramPointer Find(WordIndex word, NodeRange &next) const {
      UnigramValue *val = unigram_ + word;
      next.begin = val->next;
      next.end = (val+1)->next;
      return UnigramPointer(val->weights);
    }

  private:
    UnigramValue *unigram_;
};

class BitPacked {
  public:
    BitPacked() {}

    uint64_t InsertIndex() const {
      return insert_index_;
    }

  protected:
    static uint64_t BaseSize(uint64_t entries, uint64_t max_vocab, uint8_t remaining_bits);

    void BaseInit(void *base, uint64_t max_vocab, uint8_t remaining_bits);

    uint8_t word_bits_;
    uint8_t total_bits_;
    uint64_t word_mask_;

    uint8_t *base_;

    uint64_t insert_index_, max_vocab_;
};

template <class Bhiksha> class BitPackedMiddle : public BitPacked {
  public:
    static uint64_t Size(uint8_t quant_bits, uint64_t entries, uint64_t max_vocab, uint64_t max_next, const Config &config);


    BitPackedMiddle(void *base, uint8_t quant_bits, uint64_t entries, uint64_t max_vocab, uint64_t max_next, const BitPacked &next_source, const Config &config);

    util::BitAddress Insert(WordIndex word);

    void FinishedLoading(uint64_t next_end, const Config &config);

    util::BitAddress Find(WordIndex word, NodeRange &range, uint64_t &pointer) const;

    util::BitAddress ReadEntry(uint64_t pointer, NodeRange &range) {
      uint64_t addr = pointer * total_bits_;
      addr += word_bits_;
      bhiksha_.ReadNext(base_, addr + quant_bits_, pointer, total_bits_, range);
      return util::BitAddress(base_, addr);
    }

  private:
    uint8_t quant_bits_;
    Bhiksha bhiksha_;

    const BitPacked *next_source_;
};

class BitPackedLongest : public BitPacked {
  public:
    static uint64_t Size(uint8_t quant_bits, uint64_t entries, uint64_t max_vocab) {
      return BaseSize(entries, max_vocab, quant_bits);
    }

    BitPackedLongest() {}

    void Init(void *base, uint8_t quant_bits, uint64_t max_vocab) {
      BaseInit(base, max_vocab, quant_bits);
    }

    util::BitAddress Insert(WordIndex word);

    util::BitAddress Find(WordIndex word, const NodeRange &node) const;
};

}
}
}
# 18 "./lm/bhiksha.hh" 2

# 1 "./util/sorted_uniform.hh" 1



# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/algorithm" 1 3
# 58 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/algorithm" 3
       
# 59 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/algorithm" 3

# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/utility" 1 3
# 58 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/utility" 3
       
# 59 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/utility" 3
# 69 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/utility" 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_relops.h" 1 3
# 67 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_relops.h" 3

# 67 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_relops.h" 3
namespace std
{
  namespace rel_ops
  {
 
# 85 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_relops.h" 3
    template <class _Tp>
      inline bool
      operator!=(const _Tp& __x, const _Tp& __y)
      { return !(__x == __y); }
# 98 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_relops.h" 3
    template <class _Tp>
      inline bool
      operator>(const _Tp& __x, const _Tp& __y)
      { return __y < __x; }
# 111 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_relops.h" 3
    template <class _Tp>
      inline bool
      operator<=(const _Tp& __x, const _Tp& __y)
      { return !(__y < __x); }
# 124 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_relops.h" 3
    template <class _Tp>
      inline bool
      operator>=(const _Tp& __x, const _Tp& __y)
      { return !(__x < __y); }

 
  }

}
# 70 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/utility" 2 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_pair.h" 1 3
# 59 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_pair.h" 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/move.h" 1 3
# 34 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/move.h" 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/concept_check.h" 1 3
# 33 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/concept_check.h" 3
       
# 34 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/concept_check.h" 3
# 35 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/move.h" 2 3

namespace std
{







  template<typename _Tp>
    inline _Tp*
    __addressof(_Tp& __r)
    {
      return reinterpret_cast<_Tp*>
 (&const_cast<char&>(reinterpret_cast<const volatile char&>(__r)));
    }


}
# 159 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/move.h" 3
namespace std
{

# 174 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/move.h" 3
  template<typename _Tp>
    inline void
    swap(_Tp& __a, _Tp& __b)




    {

     

      _Tp __tmp = (__a);
      __a = (__b);
      __b = (__tmp);
    }




  template<typename _Tp, size_t _Nm>
    inline void
    swap(_Tp (&__a)[_Nm], _Tp (&__b)[_Nm])



    {
      for (size_t __n = 0; __n < _Nm; ++__n)
 swap(__a[__n], __b[__n]);
    }



}
# 60 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_pair.h" 2 3





namespace std
{

# 95 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_pair.h" 3
  template<class _T1, class _T2>
    struct pair
    {
      typedef _T1 first_type;
      typedef _T2 second_type;

      _T1 first;
      _T2 second;





      pair()
      : first(), second() { }


      pair(const _T1& __a, const _T2& __b)
      : first(__a), second(__b) { }



      template<class _U1, class _U2>
 pair(const pair<_U1, _U2>& __p)
 : first(__p.first), second(__p.second) { }
# 209 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_pair.h" 3
    };


  template<class _T1, class _T2>
    inline bool
    operator==(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return __x.first == __y.first && __x.second == __y.second; }


  template<class _T1, class _T2>
    inline bool
    operator<(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return __x.first < __y.first
      || (!(__y.first < __x.first) && __x.second < __y.second); }


  template<class _T1, class _T2>
    inline bool
    operator!=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return !(__x == __y); }


  template<class _T1, class _T2>
    inline bool
    operator>(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return __y < __x; }


  template<class _T1, class _T2>
    inline bool
    operator<=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return !(__y < __x); }


  template<class _T1, class _T2>
    inline bool
    operator>=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return !(__x < __y); }
# 284 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_pair.h" 3
  template<class _T1, class _T2>
    inline pair<_T1, _T2>
    make_pair(_T1 __x, _T2 __y)
    { return pair<_T1, _T2>(__x, __y); }





}
# 71 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/utility" 2 3
# 61 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/algorithm" 2 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 1 3
# 60 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/functexcept.h" 1 3
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/functexcept.h" 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/exception_defines.h" 1 3
# 41 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/functexcept.h" 2 3

namespace std
{



  void
  __throw_bad_exception(void) __attribute__((__noreturn__));


  void
  __throw_bad_alloc(void) __attribute__((__noreturn__));


  void
  __throw_bad_cast(void) __attribute__((__noreturn__));

  void
  __throw_bad_typeid(void) __attribute__((__noreturn__));


  void
  __throw_logic_error(const char*) __attribute__((__noreturn__));

  void
  __throw_domain_error(const char*) __attribute__((__noreturn__));

  void
  __throw_invalid_argument(const char*) __attribute__((__noreturn__));

  void
  __throw_length_error(const char*) __attribute__((__noreturn__));

  void
  __throw_out_of_range(const char*) __attribute__((__noreturn__));

  void
  __throw_out_of_range_fmt(const char*, ...) __attribute__((__noreturn__))
    __attribute__((__format__(__gnu_printf__, 1, 2)));

  void
  __throw_runtime_error(const char*) __attribute__((__noreturn__));

  void
  __throw_range_error(const char*) __attribute__((__noreturn__));

  void
  __throw_overflow_error(const char*) __attribute__((__noreturn__));

  void
  __throw_underflow_error(const char*) __attribute__((__noreturn__));


  void
  __throw_ios_failure(const char*) __attribute__((__noreturn__));

  void
  __throw_system_error(int) __attribute__((__noreturn__));

  void
  __throw_future_error(int) __attribute__((__noreturn__));


  void
  __throw_bad_function_call() __attribute__((__noreturn__));


}
# 61 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 2 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/cpp_type_traits.h" 1 3
# 35 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/cpp_type_traits.h" 3
       
# 36 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/cpp_type_traits.h" 3
# 68 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/cpp_type_traits.h" 3
namespace __gnu_cxx
{


  template<typename _Iterator, typename _Container>
    class __normal_iterator;


}

namespace std
{


  struct __true_type { };
  struct __false_type { };

  template<bool>
    struct __truth_type
    { typedef __false_type __type; };

  template<>
    struct __truth_type<true>
    { typedef __true_type __type; };



  template<class _Sp, class _Tp>
    struct __traitor
    {
      enum { __value = bool(_Sp::__value) || bool(_Tp::__value) };
      typedef typename __truth_type<__value>::__type __type;
    };


  template<typename, typename>
    struct __are_same
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };

  template<typename _Tp>
    struct __are_same<_Tp, _Tp>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };


  template<typename _Tp>
    struct __is_void
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };

  template<>
    struct __is_void<void>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };




  template<typename _Tp>
    struct __is_integer
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };





  template<>
    struct __is_integer<bool>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<signed char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<unsigned char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };


  template<>
    struct __is_integer<wchar_t>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
# 199 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/cpp_type_traits.h" 3
  template<>
    struct __is_integer<short>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<unsigned short>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<int>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<unsigned int>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<long>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<unsigned long>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<long long>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<unsigned long long>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
# 270 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/cpp_type_traits.h" 3
template<> struct __is_integer<__int128> { enum { __value = 1 }; typedef __true_type __type; }; template<> struct __is_integer<unsigned __int128> { enum { __value = 1 }; typedef __true_type __type; };
# 287 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/cpp_type_traits.h" 3
  template<typename _Tp>
    struct __is_floating
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };


  template<>
    struct __is_floating<float>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_floating<double>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_floating<long double>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };




  template<typename _Tp>
    struct __is_pointer
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };

  template<typename _Tp>
    struct __is_pointer<_Tp*>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };




  template<typename _Tp>
    struct __is_normal_iterator
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };

  template<typename _Iterator, typename _Container>
    struct __is_normal_iterator< __gnu_cxx::__normal_iterator<_Iterator,
             _Container> >
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };




  template<typename _Tp>
    struct __is_arithmetic
    : public __traitor<__is_integer<_Tp>, __is_floating<_Tp> >
    { };




  template<typename _Tp>
    struct __is_scalar
    : public __traitor<__is_arithmetic<_Tp>, __is_pointer<_Tp> >
    { };




  template<typename _Tp>
    struct __is_char
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };

  template<>
    struct __is_char<char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };


  template<>
    struct __is_char<wchar_t>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };


  template<typename _Tp>
    struct __is_byte
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };

  template<>
    struct __is_byte<char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_byte<signed char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_byte<unsigned char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };




  template<typename _Tp>
    struct __is_move_iterator
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };
# 443 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/cpp_type_traits.h" 3

}
# 62 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 2 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ext/type_traits.h" 1 3
# 32 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ext/type_traits.h" 3
       
# 33 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ext/type_traits.h" 3




namespace __gnu_cxx
{



  template<bool, typename>
    struct __enable_if
    { };

  template<typename _Tp>
    struct __enable_if<true, _Tp>
    { typedef _Tp __type; };



  template<bool _Cond, typename _Iftrue, typename _Iffalse>
    struct __conditional_type
    { typedef _Iftrue __type; };

  template<typename _Iftrue, typename _Iffalse>
    struct __conditional_type<false, _Iftrue, _Iffalse>
    { typedef _Iffalse __type; };



  template<typename _Tp>
    struct __add_unsigned
    {
    private:
      typedef __enable_if<std::__is_integer<_Tp>::__value, _Tp> __if_type;

    public:
      typedef typename __if_type::__type __type;
    };

  template<>
    struct __add_unsigned<char>
    { typedef unsigned char __type; };

  template<>
    struct __add_unsigned<signed char>
    { typedef unsigned char __type; };

  template<>
    struct __add_unsigned<short>
    { typedef unsigned short __type; };

  template<>
    struct __add_unsigned<int>
    { typedef unsigned int __type; };

  template<>
    struct __add_unsigned<long>
    { typedef unsigned long __type; };

  template<>
    struct __add_unsigned<long long>
    { typedef unsigned long long __type; };


  template<>
    struct __add_unsigned<bool>;

  template<>
    struct __add_unsigned<wchar_t>;



  template<typename _Tp>
    struct __remove_unsigned
    {
    private:
      typedef __enable_if<std::__is_integer<_Tp>::__value, _Tp> __if_type;

    public:
      typedef typename __if_type::__type __type;
    };

  template<>
    struct __remove_unsigned<char>
    { typedef signed char __type; };

  template<>
    struct __remove_unsigned<unsigned char>
    { typedef signed char __type; };

  template<>
    struct __remove_unsigned<unsigned short>
    { typedef short __type; };

  template<>
    struct __remove_unsigned<unsigned int>
    { typedef int __type; };

  template<>
    struct __remove_unsigned<unsigned long>
    { typedef long __type; };

  template<>
    struct __remove_unsigned<unsigned long long>
    { typedef long long __type; };


  template<>
    struct __remove_unsigned<bool>;

  template<>
    struct __remove_unsigned<wchar_t>;



  template<typename _Type>
    inline bool
    __is_null_pointer(_Type* __ptr)
    { return __ptr == 0; }

  template<typename _Type>
    inline bool
    __is_null_pointer(_Type)
    { return false; }
# 165 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ext/type_traits.h" 3
  template<typename _Tp, bool = std::__is_integer<_Tp>::__value>
    struct __promote
    { typedef double __type; };




  template<typename _Tp>
    struct __promote<_Tp, false>
    { };

  template<>
    struct __promote<long double>
    { typedef long double __type; };

  template<>
    struct __promote<double>
    { typedef double __type; };

  template<>
    struct __promote<float>
    { typedef float __type; };

  template<typename _Tp, typename _Up,
           typename _Tp2 = typename __promote<_Tp>::__type,
           typename _Up2 = typename __promote<_Up>::__type>
    struct __promote_2
    {
      typedef __typeof__(_Tp2() + _Up2()) __type;
    };

  template<typename _Tp, typename _Up, typename _Vp,
           typename _Tp2 = typename __promote<_Tp>::__type,
           typename _Up2 = typename __promote<_Up>::__type,
           typename _Vp2 = typename __promote<_Vp>::__type>
    struct __promote_3
    {
      typedef __typeof__(_Tp2() + _Up2() + _Vp2()) __type;
    };

  template<typename _Tp, typename _Up, typename _Vp, typename _Wp,
           typename _Tp2 = typename __promote<_Tp>::__type,
           typename _Up2 = typename __promote<_Up>::__type,
           typename _Vp2 = typename __promote<_Vp>::__type,
           typename _Wp2 = typename __promote<_Wp>::__type>
    struct __promote_4
    {
      typedef __typeof__(_Tp2() + _Up2() + _Vp2() + _Wp2()) __type;
    };


}
# 63 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 2 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ext/numeric_traits.h" 1 3
# 32 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ext/numeric_traits.h" 3
       
# 33 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ext/numeric_traits.h" 3




namespace __gnu_cxx
{

# 54 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ext/numeric_traits.h" 3
  template<typename _Value>
    struct __numeric_traits_integer
    {

      static const _Value __min = (((_Value)(-1) < 0) ? (_Value)1 << (sizeof(_Value) * 8 - ((_Value)(-1) < 0)) : (_Value)0);
      static const _Value __max = (((_Value)(-1) < 0) ? (((((_Value)1 << ((sizeof(_Value) * 8 - ((_Value)(-1) < 0)) - 1)) - 1) << 1) + 1) : ~(_Value)0);



      static const bool __is_signed = ((_Value)(-1) < 0);
      static const int __digits = (sizeof(_Value) * 8 - ((_Value)(-1) < 0));
    };

  template<typename _Value>
    const _Value __numeric_traits_integer<_Value>::__min;

  template<typename _Value>
    const _Value __numeric_traits_integer<_Value>::__max;

  template<typename _Value>
    const bool __numeric_traits_integer<_Value>::__is_signed;

  template<typename _Value>
    const int __numeric_traits_integer<_Value>::__digits;
# 99 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ext/numeric_traits.h" 3
  template<typename _Value>
    struct __numeric_traits_floating
    {

      static const int __max_digits10 = (2 + (std::__are_same<_Value, float>::__value ? 24 : std::__are_same<_Value, double>::__value ? 53 : 64) * 643L / 2136);


      static const bool __is_signed = true;
      static const int __digits10 = (std::__are_same<_Value, float>::__value ? 6 : std::__are_same<_Value, double>::__value ? 15 : 18);
      static const int __max_exponent10 = (std::__are_same<_Value, float>::__value ? 38 : std::__are_same<_Value, double>::__value ? 308 : 4932);
    };

  template<typename _Value>
    const int __numeric_traits_floating<_Value>::__max_digits10;

  template<typename _Value>
    const bool __numeric_traits_floating<_Value>::__is_signed;

  template<typename _Value>
    const int __numeric_traits_floating<_Value>::__digits10;

  template<typename _Value>
    const int __numeric_traits_floating<_Value>::__max_exponent10;

  template<typename _Value>
    struct __numeric_traits
    : public __conditional_type<std::__is_integer<_Value>::__value,
    __numeric_traits_integer<_Value>,
    __numeric_traits_floating<_Value> >::__type
    { };


}
# 64 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 2 3

# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator_base_types.h" 1 3
# 62 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator_base_types.h" 3
       
# 63 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator_base_types.h" 3







namespace std
{

# 89 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator_base_types.h" 3
  struct input_iterator_tag { };


  struct output_iterator_tag { };


  struct forward_iterator_tag : public input_iterator_tag { };



  struct bidirectional_iterator_tag : public forward_iterator_tag { };



  struct random_access_iterator_tag : public bidirectional_iterator_tag { };
# 116 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator_base_types.h" 3
  template<typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
           typename _Pointer = _Tp*, typename _Reference = _Tp&>
    struct iterator
    {

      typedef _Category iterator_category;

      typedef _Tp value_type;

      typedef _Distance difference_type;

      typedef _Pointer pointer;

      typedef _Reference reference;
    };
# 165 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator_base_types.h" 3
  template<typename _Iterator>
    struct iterator_traits
    {
      typedef typename _Iterator::iterator_category iterator_category;
      typedef typename _Iterator::value_type value_type;
      typedef typename _Iterator::difference_type difference_type;
      typedef typename _Iterator::pointer pointer;
      typedef typename _Iterator::reference reference;
    };



  template<typename _Tp>
    struct iterator_traits<_Tp*>
    {
      typedef random_access_iterator_tag iterator_category;
      typedef _Tp value_type;
      typedef ptrdiff_t difference_type;
      typedef _Tp* pointer;
      typedef _Tp& reference;
    };


  template<typename _Tp>
    struct iterator_traits<const _Tp*>
    {
      typedef random_access_iterator_tag iterator_category;
      typedef _Tp value_type;
      typedef ptrdiff_t difference_type;
      typedef const _Tp* pointer;
      typedef const _Tp& reference;
    };





  template<typename _Iter>
    inline typename iterator_traits<_Iter>::iterator_category
    __iterator_category(const _Iter&)
    { return typename iterator_traits<_Iter>::iterator_category(); }





  template<typename _Iterator, bool _HasBase>
    struct _Iter_base
    {
      typedef _Iterator iterator_type;
      static iterator_type _S_base(_Iterator __it)
      { return __it; }
    };

  template<typename _Iterator>
    struct _Iter_base<_Iterator, true>
    {
      typedef typename _Iterator::iterator_type iterator_type;
      static iterator_type _S_base(_Iterator __it)
      { return __it.base(); }
    };
# 235 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator_base_types.h" 3

}
# 66 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 2 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator_base_funcs.h" 1 3
# 62 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator_base_funcs.h" 3
       
# 63 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator_base_funcs.h" 3


# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/debug/debug.h" 1 3
# 46 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/debug/debug.h" 3
namespace std
{
  namespace __debug { }
}




namespace __gnu_debug
{
  using namespace std::__debug;
}
# 66 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator_base_funcs.h" 2 3

namespace std
{


  template<typename _InputIterator>
    inline typename iterator_traits<_InputIterator>::difference_type
    __distance(_InputIterator __first, _InputIterator __last,
               input_iterator_tag)
    {

     

      typename iterator_traits<_InputIterator>::difference_type __n = 0;
      while (__first != __last)
 {
   ++__first;
   ++__n;
 }
      return __n;
    }

  template<typename _RandomAccessIterator>
    inline typename iterator_traits<_RandomAccessIterator>::difference_type
    __distance(_RandomAccessIterator __first, _RandomAccessIterator __last,
               random_access_iterator_tag)
    {

     

      return __last - __first;
    }
# 112 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator_base_funcs.h" 3
  template<typename _InputIterator>
    inline typename iterator_traits<_InputIterator>::difference_type
    distance(_InputIterator __first, _InputIterator __last)
    {

      return std::__distance(__first, __last,
        std::__iterator_category(__first));
    }

  template<typename _InputIterator, typename _Distance>
    inline void
    __advance(_InputIterator& __i, _Distance __n, input_iterator_tag)
    {

     
      ;
      while (__n--)
 ++__i;
    }

  template<typename _BidirectionalIterator, typename _Distance>
    inline void
    __advance(_BidirectionalIterator& __i, _Distance __n,
       bidirectional_iterator_tag)
    {

     

      if (__n > 0)
        while (__n--)
   ++__i;
      else
        while (__n++)
   --__i;
    }

  template<typename _RandomAccessIterator, typename _Distance>
    inline void
    __advance(_RandomAccessIterator& __i, _Distance __n,
              random_access_iterator_tag)
    {

     

      __i += __n;
    }
# 171 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator_base_funcs.h" 3
  template<typename _InputIterator, typename _Distance>
    inline void
    advance(_InputIterator& __i, _Distance __n)
    {

      typename iterator_traits<_InputIterator>::difference_type __d = __n;
      std::__advance(__i, __d, std::__iterator_category(__i));
    }
# 202 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator_base_funcs.h" 3

}
# 67 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 2 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator.h" 1 3
# 66 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator.h" 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ptr_traits.h" 1 3
# 67 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator.h" 2 3

namespace std
{

# 96 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator.h" 3
  template<typename _Iterator>
    class reverse_iterator
    : public iterator<typename iterator_traits<_Iterator>::iterator_category,
        typename iterator_traits<_Iterator>::value_type,
        typename iterator_traits<_Iterator>::difference_type,
        typename iterator_traits<_Iterator>::pointer,
                      typename iterator_traits<_Iterator>::reference>
    {
    protected:
      _Iterator current;

      typedef iterator_traits<_Iterator> __traits_type;

    public:
      typedef _Iterator iterator_type;
      typedef typename __traits_type::difference_type difference_type;
      typedef typename __traits_type::pointer pointer;
      typedef typename __traits_type::reference reference;







      reverse_iterator() : current() { }




      explicit
      reverse_iterator(iterator_type __x) : current(__x) { }




      reverse_iterator(const reverse_iterator& __x)
      : current(__x.current) { }





      template<typename _Iter>
        reverse_iterator(const reverse_iterator<_Iter>& __x)
 : current(__x.base()) { }




      iterator_type
      base() const
      { return current; }
# 160 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator.h" 3
      reference
      operator*() const
      {
 _Iterator __tmp = current;
 return *--__tmp;
      }






      pointer
      operator->() const
      { return &(operator*()); }






      reverse_iterator&
      operator++()
      {
 --current;
 return *this;
      }






      reverse_iterator
      operator++(int)
      {
 reverse_iterator __tmp = *this;
 --current;
 return __tmp;
      }






      reverse_iterator&
      operator--()
      {
 ++current;
 return *this;
      }






      reverse_iterator
      operator--(int)
      {
 reverse_iterator __tmp = *this;
 ++current;
 return __tmp;
      }






      reverse_iterator
      operator+(difference_type __n) const
      { return reverse_iterator(current - __n); }







      reverse_iterator&
      operator+=(difference_type __n)
      {
 current -= __n;
 return *this;
      }






      reverse_iterator
      operator-(difference_type __n) const
      { return reverse_iterator(current + __n); }







      reverse_iterator&
      operator-=(difference_type __n)
      {
 current += __n;
 return *this;
      }






      reference
      operator[](difference_type __n) const
      { return *(*this + __n); }
    };
# 290 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator.h" 3
  template<typename _Iterator>
    inline bool
    operator==(const reverse_iterator<_Iterator>& __x,
        const reverse_iterator<_Iterator>& __y)
    { return __x.base() == __y.base(); }

  template<typename _Iterator>
    inline bool
    operator<(const reverse_iterator<_Iterator>& __x,
       const reverse_iterator<_Iterator>& __y)
    { return __y.base() < __x.base(); }

  template<typename _Iterator>
    inline bool
    operator!=(const reverse_iterator<_Iterator>& __x,
        const reverse_iterator<_Iterator>& __y)
    { return !(__x == __y); }

  template<typename _Iterator>
    inline bool
    operator>(const reverse_iterator<_Iterator>& __x,
       const reverse_iterator<_Iterator>& __y)
    { return __y < __x; }

  template<typename _Iterator>
    inline bool
    operator<=(const reverse_iterator<_Iterator>& __x,
        const reverse_iterator<_Iterator>& __y)
    { return !(__y < __x); }

  template<typename _Iterator>
    inline bool
    operator>=(const reverse_iterator<_Iterator>& __x,
        const reverse_iterator<_Iterator>& __y)
    { return !(__x < __y); }

  template<typename _Iterator>
    inline typename reverse_iterator<_Iterator>::difference_type
    operator-(const reverse_iterator<_Iterator>& __x,
       const reverse_iterator<_Iterator>& __y)
    { return __y.base() - __x.base(); }

  template<typename _Iterator>
    inline reverse_iterator<_Iterator>
    operator+(typename reverse_iterator<_Iterator>::difference_type __n,
       const reverse_iterator<_Iterator>& __x)
    { return reverse_iterator<_Iterator>(__x.base() - __n); }



  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator==(const reverse_iterator<_IteratorL>& __x,
        const reverse_iterator<_IteratorR>& __y)
    { return __x.base() == __y.base(); }

  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator<(const reverse_iterator<_IteratorL>& __x,
       const reverse_iterator<_IteratorR>& __y)
    { return __y.base() < __x.base(); }

  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator!=(const reverse_iterator<_IteratorL>& __x,
        const reverse_iterator<_IteratorR>& __y)
    { return !(__x == __y); }

  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator>(const reverse_iterator<_IteratorL>& __x,
       const reverse_iterator<_IteratorR>& __y)
    { return __y < __x; }

  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator<=(const reverse_iterator<_IteratorL>& __x,
        const reverse_iterator<_IteratorR>& __y)
    { return !(__y < __x); }

  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator>=(const reverse_iterator<_IteratorL>& __x,
        const reverse_iterator<_IteratorR>& __y)
    { return !(__x < __y); }

  template<typename _IteratorL, typename _IteratorR>







    inline typename reverse_iterator<_IteratorL>::difference_type
    operator-(const reverse_iterator<_IteratorL>& __x,
       const reverse_iterator<_IteratorR>& __y)

    { return __y.base() - __x.base(); }
# 414 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator.h" 3
  template<typename _Container>
    class back_insert_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
    {
    protected:
      _Container* container;

    public:

      typedef _Container container_type;


      explicit
      back_insert_iterator(_Container& __x) : container(&__x) { }
# 441 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator.h" 3
      back_insert_iterator&
      operator=(typename _Container::const_reference __value)
      {
 container->push_back(__value);
 return *this;
      }
# 464 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator.h" 3
      back_insert_iterator&
      operator*()
      { return *this; }


      back_insert_iterator&
      operator++()
      { return *this; }


      back_insert_iterator
      operator++(int)
      { return *this; }
    };
# 490 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator.h" 3
  template<typename _Container>
    inline back_insert_iterator<_Container>
    back_inserter(_Container& __x)
    { return back_insert_iterator<_Container>(__x); }
# 505 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator.h" 3
  template<typename _Container>
    class front_insert_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
    {
    protected:
      _Container* container;

    public:

      typedef _Container container_type;


      explicit front_insert_iterator(_Container& __x) : container(&__x) { }
# 531 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator.h" 3
      front_insert_iterator&
      operator=(typename _Container::const_reference __value)
      {
 container->push_front(__value);
 return *this;
      }
# 554 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator.h" 3
      front_insert_iterator&
      operator*()
      { return *this; }


      front_insert_iterator&
      operator++()
      { return *this; }


      front_insert_iterator
      operator++(int)
      { return *this; }
    };
# 580 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator.h" 3
  template<typename _Container>
    inline front_insert_iterator<_Container>
    front_inserter(_Container& __x)
    { return front_insert_iterator<_Container>(__x); }
# 599 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator.h" 3
  template<typename _Container>
    class insert_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
    {
    protected:
      _Container* container;
      typename _Container::iterator iter;

    public:

      typedef _Container container_type;





      insert_iterator(_Container& __x, typename _Container::iterator __i)
      : container(&__x), iter(__i) {}
# 642 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator.h" 3
      insert_iterator&
      operator=(typename _Container::const_reference __value)
      {
 iter = container->insert(iter, __value);
 ++iter;
 return *this;
      }
# 668 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator.h" 3
      insert_iterator&
      operator*()
      { return *this; }


      insert_iterator&
      operator++()
      { return *this; }


      insert_iterator&
      operator++(int)
      { return *this; }
    };
# 694 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator.h" 3
  template<typename _Container, typename _Iterator>
    inline insert_iterator<_Container>
    inserter(_Container& __x, _Iterator __i)
    {
      return insert_iterator<_Container>(__x,
      typename _Container::iterator(__i));
    }




}

namespace __gnu_cxx
{

# 718 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator.h" 3
  using std::iterator_traits;
  using std::iterator;
  template<typename _Iterator, typename _Container>
    class __normal_iterator
    {
    protected:
      _Iterator _M_current;

      typedef iterator_traits<_Iterator> __traits_type;

    public:
      typedef _Iterator iterator_type;
      typedef typename __traits_type::iterator_category iterator_category;
      typedef typename __traits_type::value_type value_type;
      typedef typename __traits_type::difference_type difference_type;
      typedef typename __traits_type::reference reference;
      typedef typename __traits_type::pointer pointer;

      __normal_iterator()
      : _M_current(_Iterator()) { }

      explicit
      __normal_iterator(const _Iterator& __i)
      : _M_current(__i) { }


      template<typename _Iter>
        __normal_iterator(const __normal_iterator<_Iter,
     typename __enable_if<
              (std::__are_same<_Iter, typename _Container::pointer>::__value),
        _Container>::__type>& __i)
        : _M_current(__i.base()) { }


      reference
      operator*() const
      { return *_M_current; }

      pointer
      operator->() const
      { return _M_current; }

      __normal_iterator&
      operator++()
      {
 ++_M_current;
 return *this;
      }

      __normal_iterator
      operator++(int)
      { return __normal_iterator(_M_current++); }


      __normal_iterator&
      operator--()
      {
 --_M_current;
 return *this;
      }

      __normal_iterator
      operator--(int)
      { return __normal_iterator(_M_current--); }


      reference
      operator[](difference_type __n) const
      { return _M_current[__n]; }

      __normal_iterator&
      operator+=(difference_type __n)
      { _M_current += __n; return *this; }

      __normal_iterator
      operator+(difference_type __n) const
      { return __normal_iterator(_M_current + __n); }

      __normal_iterator&
      operator-=(difference_type __n)
      { _M_current -= __n; return *this; }

      __normal_iterator
      operator-(difference_type __n) const
      { return __normal_iterator(_M_current - __n); }

      const _Iterator&
      base() const
      { return _M_current; }
    };
# 818 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_iterator.h" 3
  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator==(const __normal_iterator<_IteratorL, _Container>& __lhs,
        const __normal_iterator<_IteratorR, _Container>& __rhs)
   
    { return __lhs.base() == __rhs.base(); }

  template<typename _Iterator, typename _Container>
    inline bool
    operator==(const __normal_iterator<_Iterator, _Container>& __lhs,
        const __normal_iterator<_Iterator, _Container>& __rhs)
   
    { return __lhs.base() == __rhs.base(); }

  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator!=(const __normal_iterator<_IteratorL, _Container>& __lhs,
        const __normal_iterator<_IteratorR, _Container>& __rhs)
   
    { return __lhs.base() != __rhs.base(); }

  template<typename _Iterator, typename _Container>
    inline bool
    operator!=(const __normal_iterator<_Iterator, _Container>& __lhs,
        const __normal_iterator<_Iterator, _Container>& __rhs)
   
    { return __lhs.base() != __rhs.base(); }


  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator<(const __normal_iterator<_IteratorL, _Container>& __lhs,
       const __normal_iterator<_IteratorR, _Container>& __rhs)
   
    { return __lhs.base() < __rhs.base(); }

  template<typename _Iterator, typename _Container>
    inline bool
    operator<(const __normal_iterator<_Iterator, _Container>& __lhs,
       const __normal_iterator<_Iterator, _Container>& __rhs)
   
    { return __lhs.base() < __rhs.base(); }

  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator>(const __normal_iterator<_IteratorL, _Container>& __lhs,
       const __normal_iterator<_IteratorR, _Container>& __rhs)
   
    { return __lhs.base() > __rhs.base(); }

  template<typename _Iterator, typename _Container>
    inline bool
    operator>(const __normal_iterator<_Iterator, _Container>& __lhs,
       const __normal_iterator<_Iterator, _Container>& __rhs)
   
    { return __lhs.base() > __rhs.base(); }

  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator<=(const __normal_iterator<_IteratorL, _Container>& __lhs,
        const __normal_iterator<_IteratorR, _Container>& __rhs)
   
    { return __lhs.base() <= __rhs.base(); }

  template<typename _Iterator, typename _Container>
    inline bool
    operator<=(const __normal_iterator<_Iterator, _Container>& __lhs,
        const __normal_iterator<_Iterator, _Container>& __rhs)
   
    { return __lhs.base() <= __rhs.base(); }

  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator>=(const __normal_iterator<_IteratorL, _Container>& __lhs,
        const __normal_iterator<_IteratorR, _Container>& __rhs)
   
    { return __lhs.base() >= __rhs.base(); }

  template<typename _Iterator, typename _Container>
    inline bool
    operator>=(const __normal_iterator<_Iterator, _Container>& __lhs,
        const __normal_iterator<_Iterator, _Container>& __rhs)
   
    { return __lhs.base() >= __rhs.base(); }





  template<typename _IteratorL, typename _IteratorR, typename _Container>







    inline typename __normal_iterator<_IteratorL, _Container>::difference_type
    operator-(const __normal_iterator<_IteratorL, _Container>& __lhs,
       const __normal_iterator<_IteratorR, _Container>& __rhs)

    { return __lhs.base() - __rhs.base(); }

  template<typename _Iterator, typename _Container>
    inline typename __normal_iterator<_Iterator, _Container>::difference_type
    operator-(const __normal_iterator<_Iterator, _Container>& __lhs,
       const __normal_iterator<_Iterator, _Container>& __rhs)
   
    { return __lhs.base() - __rhs.base(); }

  template<typename _Iterator, typename _Container>
    inline __normal_iterator<_Iterator, _Container>
    operator+(typename __normal_iterator<_Iterator, _Container>::difference_type
       __n, const __normal_iterator<_Iterator, _Container>& __i)
   
    { return __normal_iterator<_Iterator, _Container>(__i.base() + __n); }


}
# 68 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 2 3



# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/predefined_ops.h" 1 3
# 33 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/predefined_ops.h" 3
namespace __gnu_cxx
{
namespace __ops
{
  struct _Iter_less_iter
  {
    template<typename _Iterator1, typename _Iterator2>
     
      bool
      operator()(_Iterator1 __it1, _Iterator2 __it2) const
      { return *__it1 < *__it2; }
  };
 
  inline _Iter_less_iter
  __iter_less_iter()
  { return _Iter_less_iter(); }

  struct _Iter_less_val
  {
    template<typename _Iterator, typename _Value>
      bool
      operator()(_Iterator __it, _Value& __val) const
      { return *__it < __val; }
    };

  inline _Iter_less_val
  __iter_less_val()
  { return _Iter_less_val(); }

  inline _Iter_less_val
  __iter_comp_val(_Iter_less_iter)
  { return _Iter_less_val(); }

  struct _Val_less_iter
  {
    template<typename _Value, typename _Iterator>
      bool
      operator()(_Value& __val, _Iterator __it) const
      { return __val < *__it; }
    };

  inline _Val_less_iter
  __val_less_iter()
  { return _Val_less_iter(); }

  inline _Val_less_iter
  __val_comp_iter(_Iter_less_iter)
  { return _Val_less_iter(); }

  struct _Iter_equal_to_iter
  {
    template<typename _Iterator1, typename _Iterator2>
      bool
      operator()(_Iterator1 __it1, _Iterator2 __it2) const
      { return *__it1 == *__it2; }
    };

  inline _Iter_equal_to_iter
  __iter_equal_to_iter()
  { return _Iter_equal_to_iter(); }

  struct _Iter_equal_to_val
  {
    template<typename _Iterator, typename _Value>
      bool
      operator()(_Iterator __it, _Value& __val) const
      { return *__it == __val; }
    };

  inline _Iter_equal_to_val
  __iter_equal_to_val()
  { return _Iter_equal_to_val(); }

  inline _Iter_equal_to_val
  __iter_comp_val(_Iter_equal_to_iter)
  { return _Iter_equal_to_val(); }

  template<typename _Compare>
    struct _Iter_comp_iter
    {
      _Compare _M_comp;
     
      _Iter_comp_iter(_Compare __comp)
 : _M_comp(__comp)
      { }

      template<typename _Iterator1, typename _Iterator2>
       
        bool
        operator()(_Iterator1 __it1, _Iterator2 __it2)
        { return bool(_M_comp(*__it1, *__it2)); }
    };

  template<typename _Compare>
   
    inline _Iter_comp_iter<_Compare>
    __iter_comp_iter(_Compare __comp)
    { return _Iter_comp_iter<_Compare>(__comp); }

  template<typename _Compare>
    struct _Iter_comp_val
    {
      _Compare _M_comp;

      _Iter_comp_val(_Compare __comp)
 : _M_comp(__comp)
      { }

      template<typename _Iterator, typename _Value>
 bool
 operator()(_Iterator __it, _Value& __val)
 { return bool(_M_comp(*__it, __val)); }
    };

  template<typename _Compare>
   inline _Iter_comp_val<_Compare>
    __iter_comp_val(_Compare __comp)
    { return _Iter_comp_val<_Compare>(__comp); }

  template<typename _Compare>
    inline _Iter_comp_val<_Compare>
    __iter_comp_val(_Iter_comp_iter<_Compare> __comp)
    { return _Iter_comp_val<_Compare>(__comp._M_comp); }

  template<typename _Compare>
    struct _Val_comp_iter
    {
      _Compare _M_comp;

      _Val_comp_iter(_Compare __comp)
 : _M_comp(__comp)
      { }

      template<typename _Value, typename _Iterator>
 bool
 operator()(_Value& __val, _Iterator __it)
 { return bool(_M_comp(__val, *__it)); }
    };

  template<typename _Compare>
    inline _Val_comp_iter<_Compare>
    __val_comp_iter(_Compare __comp)
    { return _Val_comp_iter<_Compare>(__comp); }

  template<typename _Compare>
    inline _Val_comp_iter<_Compare>
    __val_comp_iter(_Iter_comp_iter<_Compare> __comp)
    { return _Val_comp_iter<_Compare>(__comp._M_comp); }

  template<typename _Value>
    struct _Iter_equals_val
    {
      _Value& _M_value;

      _Iter_equals_val(_Value& __value)
 : _M_value(__value)
      { }

      template<typename _Iterator>
 bool
 operator()(_Iterator __it)
 { return *__it == _M_value; }
    };

  template<typename _Value>
    inline _Iter_equals_val<_Value>
    __iter_equals_val(_Value& __val)
    { return _Iter_equals_val<_Value>(__val); }

  template<typename _Iterator1>
    struct _Iter_equals_iter
    {
      typename std::iterator_traits<_Iterator1>::reference _M_ref;

      _Iter_equals_iter(_Iterator1 __it1)
 : _M_ref(*__it1)
      { }

      template<typename _Iterator2>
 bool
 operator()(_Iterator2 __it2)
 { return *__it2 == _M_ref; }
    };

  template<typename _Iterator>
    inline _Iter_equals_iter<_Iterator>
    __iter_comp_iter(_Iter_equal_to_iter, _Iterator __it)
    { return _Iter_equals_iter<_Iterator>(__it); }

  template<typename _Predicate>
    struct _Iter_pred
    {
      _Predicate _M_pred;

      _Iter_pred(_Predicate __pred)
 : _M_pred(__pred)
      { }

      template<typename _Iterator>
 bool
 operator()(_Iterator __it)
 { return bool(_M_pred(*__it)); }
    };

  template<typename _Predicate>
    inline _Iter_pred<_Predicate>
    __pred_iter(_Predicate __pred)
    { return _Iter_pred<_Predicate>(__pred); }

  template<typename _Compare, typename _Value>
    struct _Iter_comp_to_val
    {
      _Compare _M_comp;
      _Value& _M_value;

      _Iter_comp_to_val(_Compare __comp, _Value& __value)
 : _M_comp(__comp), _M_value(__value)
      { }

      template<typename _Iterator>
 bool
 operator()(_Iterator __it)
 { return bool(_M_comp(*__it, _M_value)); }
    };

  template<typename _Compare, typename _Value>
    _Iter_comp_to_val<_Compare, _Value>
    __iter_comp_val(_Compare __comp, _Value &__val)
    { return _Iter_comp_to_val<_Compare, _Value>(__comp, __val); }

  template<typename _Compare, typename _Iterator1>
    struct _Iter_comp_to_iter
    {
      _Compare _M_comp;
      typename std::iterator_traits<_Iterator1>::reference _M_ref;

      _Iter_comp_to_iter(_Compare __comp, _Iterator1 __it1)
 : _M_comp(__comp), _M_ref(*__it1)
      { }

      template<typename _Iterator2>
 bool
 operator()(_Iterator2 __it2)
 { return bool(_M_comp(*__it2, _M_ref)); }
    };

  template<typename _Compare, typename _Iterator>
    inline _Iter_comp_to_iter<_Compare, _Iterator>
    __iter_comp_iter(_Iter_comp_iter<_Compare> __comp, _Iterator __it)
    { return _Iter_comp_to_iter<_Compare, _Iterator>(__comp._M_comp, __it); }

  template<typename _Predicate>
    struct _Iter_negate
    {
      _Predicate _M_pred;

      _Iter_negate(_Predicate __pred)
 : _M_pred(__pred)
      { }

      template<typename _Iterator>
 bool
 operator()(_Iterator __it)
 { return !bool(_M_pred(*__it)); }
    };

  template<typename _Predicate>
    inline _Iter_negate<_Predicate>
    __negate(_Iter_pred<_Predicate> __pred)
    { return _Iter_negate<_Predicate>(__pred._M_pred); }

}
}
# 72 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 2 3

namespace std
{






  template<bool _BoolType>
    struct __iter_swap
    {
      template<typename _ForwardIterator1, typename _ForwardIterator2>
        static void
        iter_swap(_ForwardIterator1 __a, _ForwardIterator2 __b)
        {
          typedef typename iterator_traits<_ForwardIterator1>::value_type
            _ValueType1;
          _ValueType1 __tmp = (*__a);
          *__a = (*__b);
          *__b = (__tmp);
 }
    };

  template<>
    struct __iter_swap<true>
    {
      template<typename _ForwardIterator1, typename _ForwardIterator2>
        static void
        iter_swap(_ForwardIterator1 __a, _ForwardIterator2 __b)
        {
          swap(*__a, *__b);
        }
    };
# 118 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 3
  template<typename _ForwardIterator1, typename _ForwardIterator2>
    inline void
    iter_swap(_ForwardIterator1 __a, _ForwardIterator2 __b)
    {

     

     



      typedef typename iterator_traits<_ForwardIterator1>::value_type
 _ValueType1;
      typedef typename iterator_traits<_ForwardIterator2>::value_type
 _ValueType2;

     

     


      typedef typename iterator_traits<_ForwardIterator1>::reference
 _ReferenceType1;
      typedef typename iterator_traits<_ForwardIterator2>::reference
 _ReferenceType2;
      std::__iter_swap<__are_same<_ValueType1, _ValueType2>::__value
 && __are_same<_ValueType1&, _ReferenceType1>::__value
 && __are_same<_ValueType2&, _ReferenceType2>::__value>::
 iter_swap(__a, __b);



    }
# 164 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 3
  template<typename _ForwardIterator1, typename _ForwardIterator2>
    _ForwardIterator2
    swap_ranges(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
  _ForwardIterator2 __first2)
    {

     

     

      ;

      for (; __first1 != __last1; ++__first1, ++__first2)
 std::iter_swap(__first1, __first2);
      return __first2;
    }
# 192 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 3
  template<typename _Tp>
   
    inline const _Tp&
    min(const _Tp& __a, const _Tp& __b)
    {

     

      if (__b < __a)
 return __b;
      return __a;
    }
# 216 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 3
  template<typename _Tp>
   
    inline const _Tp&
    max(const _Tp& __a, const _Tp& __b)
    {

     

      if (__a < __b)
 return __b;
      return __a;
    }
# 240 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 3
  template<typename _Tp, typename _Compare>
   
    inline const _Tp&
    min(const _Tp& __a, const _Tp& __b, _Compare __comp)
    {

      if (__comp(__b, __a))
 return __b;
      return __a;
    }
# 262 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 3
  template<typename _Tp, typename _Compare>
   
    inline const _Tp&
    max(const _Tp& __a, const _Tp& __b, _Compare __comp)
    {

      if (__comp(__a, __b))
 return __b;
      return __a;
    }



  template<typename _Iterator>
    struct _Niter_base
    : _Iter_base<_Iterator, __is_normal_iterator<_Iterator>::__value>
    { };

  template<typename _Iterator>
    inline typename _Niter_base<_Iterator>::iterator_type
    __niter_base(_Iterator __it)
    { return std::_Niter_base<_Iterator>::_S_base(__it); }


  template<typename _Iterator>
    struct _Miter_base
    : _Iter_base<_Iterator, __is_move_iterator<_Iterator>::__value>
    { };

  template<typename _Iterator>
    inline typename _Miter_base<_Iterator>::iterator_type
    __miter_base(_Iterator __it)
    { return std::_Miter_base<_Iterator>::_S_base(__it); }







  template<bool, bool, typename>
    struct __copy_move
    {
      template<typename _II, typename _OI>
        static _OI
        __copy_m(_II __first, _II __last, _OI __result)
        {
   for (; __first != __last; ++__result, ++__first)
     *__result = *__first;
   return __result;
 }
    };
# 330 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 3
  template<>
    struct __copy_move<false, false, random_access_iterator_tag>
    {
      template<typename _II, typename _OI>
        static _OI
        __copy_m(_II __first, _II __last, _OI __result)
        {
   typedef typename iterator_traits<_II>::difference_type _Distance;
   for(_Distance __n = __last - __first; __n > 0; --__n)
     {
       *__result = *__first;
       ++__first;
       ++__result;
     }
   return __result;
 }
    };
# 368 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 3
  template<bool _IsMove>
    struct __copy_move<_IsMove, true, random_access_iterator_tag>
    {
      template<typename _Tp>
        static _Tp*
        __copy_m(const _Tp* __first, const _Tp* __last, _Tp* __result)
        {







   const ptrdiff_t _Num = __last - __first;
   if (_Num)
     __builtin_memmove(__result, __first, sizeof(_Tp) * _Num);
   return __result + _Num;
 }
    };

  template<bool _IsMove, typename _II, typename _OI>
    inline _OI
    __copy_move_a(_II __first, _II __last, _OI __result)
    {
      typedef typename iterator_traits<_II>::value_type _ValueTypeI;
      typedef typename iterator_traits<_OI>::value_type _ValueTypeO;
      typedef typename iterator_traits<_II>::iterator_category _Category;
      const bool __simple = (__is_trivial(_ValueTypeI)
                      && __is_pointer<_II>::__value
                      && __is_pointer<_OI>::__value
        && __are_same<_ValueTypeI, _ValueTypeO>::__value);

      return std::__copy_move<_IsMove, __simple,
                       _Category>::__copy_m(__first, __last, __result);
    }



  template<typename _CharT>
    struct char_traits;

  template<typename _CharT, typename _Traits>
    class istreambuf_iterator;

  template<typename _CharT, typename _Traits>
    class ostreambuf_iterator;

  template<bool _IsMove, typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
      ostreambuf_iterator<_CharT, char_traits<_CharT> > >::__type
    __copy_move_a2(_CharT*, _CharT*,
     ostreambuf_iterator<_CharT, char_traits<_CharT> >);

  template<bool _IsMove, typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
      ostreambuf_iterator<_CharT, char_traits<_CharT> > >::__type
    __copy_move_a2(const _CharT*, const _CharT*,
     ostreambuf_iterator<_CharT, char_traits<_CharT> >);

  template<bool _IsMove, typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
        _CharT*>::__type
    __copy_move_a2(istreambuf_iterator<_CharT, char_traits<_CharT> >,
     istreambuf_iterator<_CharT, char_traits<_CharT> >, _CharT*);

  template<bool _IsMove, typename _II, typename _OI>
    inline _OI
    __copy_move_a2(_II __first, _II __last, _OI __result)
    {
      return _OI(std::__copy_move_a<_IsMove>(std::__niter_base(__first),
          std::__niter_base(__last),
          std::__niter_base(__result)));
    }
# 460 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 3
  template<typename _II, typename _OI>
    inline _OI
    copy(_II __first, _II __last, _OI __result)
    {

     
     

      ;

      return (std::__copy_move_a2<__is_move_iterator<_II>::__value>
       (std::__miter_base(__first), std::__miter_base(__last),
        __result));
    }
# 512 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 3
  template<bool, bool, typename>
    struct __copy_move_backward
    {
      template<typename _BI1, typename _BI2>
        static _BI2
        __copy_move_b(_BI1 __first, _BI1 __last, _BI2 __result)
        {
   while (__first != __last)
     *--__result = *--__last;
   return __result;
 }
    };
# 540 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 3
  template<>
    struct __copy_move_backward<false, false, random_access_iterator_tag>
    {
      template<typename _BI1, typename _BI2>
        static _BI2
        __copy_move_b(_BI1 __first, _BI1 __last, _BI2 __result)
        {
   typename iterator_traits<_BI1>::difference_type __n;
   for (__n = __last - __first; __n > 0; --__n)
     *--__result = *--__last;
   return __result;
 }
    };
# 570 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 3
  template<bool _IsMove>
    struct __copy_move_backward<_IsMove, true, random_access_iterator_tag>
    {
      template<typename _Tp>
        static _Tp*
        __copy_move_b(const _Tp* __first, const _Tp* __last, _Tp* __result)
        {







   const ptrdiff_t _Num = __last - __first;
   if (_Num)
     __builtin_memmove(__result - _Num, __first, sizeof(_Tp) * _Num);
   return __result - _Num;
 }
    };

  template<bool _IsMove, typename _BI1, typename _BI2>
    inline _BI2
    __copy_move_backward_a(_BI1 __first, _BI1 __last, _BI2 __result)
    {
      typedef typename iterator_traits<_BI1>::value_type _ValueType1;
      typedef typename iterator_traits<_BI2>::value_type _ValueType2;
      typedef typename iterator_traits<_BI1>::iterator_category _Category;
      const bool __simple = (__is_trivial(_ValueType1)
                      && __is_pointer<_BI1>::__value
                      && __is_pointer<_BI2>::__value
        && __are_same<_ValueType1, _ValueType2>::__value);

      return std::__copy_move_backward<_IsMove, __simple,
                                _Category>::__copy_move_b(__first,
         __last,
         __result);
    }

  template<bool _IsMove, typename _BI1, typename _BI2>
    inline _BI2
    __copy_move_backward_a2(_BI1 __first, _BI1 __last, _BI2 __result)
    {
      return _BI2(std::__copy_move_backward_a<_IsMove>
    (std::__niter_base(__first), std::__niter_base(__last),
     std::__niter_base(__result)));
    }
# 636 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 3
  template<typename _BI1, typename _BI2>
    inline _BI2
    copy_backward(_BI1 __first, _BI1 __last, _BI2 __result)
    {

     
     
     


      ;

      return (std::__copy_move_backward_a2<__is_move_iterator<_BI1>::__value>
       (std::__miter_base(__first), std::__miter_base(__last),
        __result));
    }
# 694 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 3
  template<typename _ForwardIterator, typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<!__is_scalar<_Tp>::__value, void>::__type
    __fill_a(_ForwardIterator __first, _ForwardIterator __last,
       const _Tp& __value)
    {
      for (; __first != __last; ++__first)
 *__first = __value;
    }

  template<typename _ForwardIterator, typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<__is_scalar<_Tp>::__value, void>::__type
    __fill_a(_ForwardIterator __first, _ForwardIterator __last,
      const _Tp& __value)
    {
      const _Tp __tmp = __value;
      for (; __first != __last; ++__first)
 *__first = __tmp;
    }


  template<typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<__is_byte<_Tp>::__value, void>::__type
    __fill_a(_Tp* __first, _Tp* __last, const _Tp& __c)
    {
      const _Tp __tmp = __c;
      if (const size_t __len = __last - __first)
 __builtin_memset(__first, static_cast<unsigned char>(__tmp), __len);
    }
# 738 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 3
  template<typename _ForwardIterator, typename _Tp>
    inline void
    fill(_ForwardIterator __first, _ForwardIterator __last, const _Tp& __value)
    {

     

      ;

      std::__fill_a(std::__niter_base(__first), std::__niter_base(__last),
      __value);
    }

  template<typename _OutputIterator, typename _Size, typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<!__is_scalar<_Tp>::__value, _OutputIterator>::__type
    __fill_n_a(_OutputIterator __first, _Size __n, const _Tp& __value)
    {
      for (__decltype(__n + 0) __niter = __n;
    __niter > 0; --__niter, ++__first)
 *__first = __value;
      return __first;
    }

  template<typename _OutputIterator, typename _Size, typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<__is_scalar<_Tp>::__value, _OutputIterator>::__type
    __fill_n_a(_OutputIterator __first, _Size __n, const _Tp& __value)
    {
      const _Tp __tmp = __value;
      for (__decltype(__n + 0) __niter = __n;
    __niter > 0; --__niter, ++__first)
 *__first = __tmp;
      return __first;
    }

  template<typename _Size, typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<__is_byte<_Tp>::__value, _Tp*>::__type
    __fill_n_a(_Tp* __first, _Size __n, const _Tp& __c)
    {
      std::__fill_a(__first, __first + __n, __c);
      return __first + __n;
    }
# 798 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 3
  template<typename _OI, typename _Size, typename _Tp>
    inline _OI
    fill_n(_OI __first, _Size __n, const _Tp& __value)
    {

     

      return _OI(std::__fill_n_a(std::__niter_base(__first), __n, __value));
    }

  template<bool _BoolType>
    struct __equal
    {
      template<typename _II1, typename _II2>
        static bool
        equal(_II1 __first1, _II1 __last1, _II2 __first2)
        {
   for (; __first1 != __last1; ++__first1, ++__first2)
     if (!(*__first1 == *__first2))
       return false;
   return true;
 }
    };

  template<>
    struct __equal<true>
    {
      template<typename _Tp>
        static bool
        equal(const _Tp* __first1, const _Tp* __last1, const _Tp* __first2)
        {
   if (const size_t __len = (__last1 - __first1))
     return !__builtin_memcmp(__first1, __first2, sizeof(_Tp) * __len);
   return true;
 }
    };

  template<typename _II1, typename _II2>
    inline bool
    __equal_aux(_II1 __first1, _II1 __last1, _II2 __first2)
    {
      typedef typename iterator_traits<_II1>::value_type _ValueType1;
      typedef typename iterator_traits<_II2>::value_type _ValueType2;
      const bool __simple = ((__is_integer<_ValueType1>::__value
         || __is_pointer<_ValueType1>::__value)
                      && __is_pointer<_II1>::__value
                      && __is_pointer<_II2>::__value
        && __are_same<_ValueType1, _ValueType2>::__value);

      return std::__equal<__simple>::equal(__first1, __last1, __first2);
    }

  template<typename, typename>
    struct __lc_rai
    {
      template<typename _II1, typename _II2>
        static _II1
        __newlast1(_II1, _II1 __last1, _II2, _II2)
        { return __last1; }

      template<typename _II>
        static bool
        __cnd2(_II __first, _II __last)
        { return __first != __last; }
    };

  template<>
    struct __lc_rai<random_access_iterator_tag, random_access_iterator_tag>
    {
      template<typename _RAI1, typename _RAI2>
        static _RAI1
        __newlast1(_RAI1 __first1, _RAI1 __last1,
     _RAI2 __first2, _RAI2 __last2)
        {
   const typename iterator_traits<_RAI1>::difference_type
     __diff1 = __last1 - __first1;
   const typename iterator_traits<_RAI2>::difference_type
     __diff2 = __last2 - __first2;
   return __diff2 < __diff1 ? __first1 + __diff2 : __last1;
 }

      template<typename _RAI>
        static bool
        __cnd2(_RAI, _RAI)
        { return true; }
    };

  template<typename _II1, typename _II2, typename _Compare>
    bool
    __lexicographical_compare_impl(_II1 __first1, _II1 __last1,
       _II2 __first2, _II2 __last2,
       _Compare __comp)
    {
      typedef typename iterator_traits<_II1>::iterator_category _Category1;
      typedef typename iterator_traits<_II2>::iterator_category _Category2;
      typedef std::__lc_rai<_Category1, _Category2> __rai_type;

      __last1 = __rai_type::__newlast1(__first1, __last1, __first2, __last2);
      for (; __first1 != __last1 && __rai_type::__cnd2(__first2, __last2);
    ++__first1, ++__first2)
 {
   if (__comp(__first1, __first2))
     return true;
   if (__comp(__first2, __first1))
     return false;
 }
      return __first1 == __last1 && __first2 != __last2;
    }

  template<bool _BoolType>
    struct __lexicographical_compare
    {
      template<typename _II1, typename _II2>
        static bool __lc(_II1, _II1, _II2, _II2);
    };

  template<bool _BoolType>
    template<typename _II1, typename _II2>
      bool
      __lexicographical_compare<_BoolType>::
      __lc(_II1 __first1, _II1 __last1, _II2 __first2, _II2 __last2)
      {
 return std::__lexicographical_compare_impl(__first1, __last1,
         __first2, __last2,
     __gnu_cxx::__ops::__iter_less_iter());
      }

  template<>
    struct __lexicographical_compare<true>
    {
      template<typename _Tp, typename _Up>
        static bool
        __lc(const _Tp* __first1, const _Tp* __last1,
      const _Up* __first2, const _Up* __last2)
 {
   const size_t __len1 = __last1 - __first1;
   const size_t __len2 = __last2 - __first2;
   if (const size_t __len = std::min(__len1, __len2))
     if (int __result = __builtin_memcmp(__first1, __first2, __len))
       return __result < 0;
   return __len1 < __len2;
 }
    };

  template<typename _II1, typename _II2>
    inline bool
    __lexicographical_compare_aux(_II1 __first1, _II1 __last1,
      _II2 __first2, _II2 __last2)
    {
      typedef typename iterator_traits<_II1>::value_type _ValueType1;
      typedef typename iterator_traits<_II2>::value_type _ValueType2;
      const bool __simple =
 (__is_byte<_ValueType1>::__value && __is_byte<_ValueType2>::__value
  && !__gnu_cxx::__numeric_traits<_ValueType1>::__is_signed
  && !__gnu_cxx::__numeric_traits<_ValueType2>::__is_signed
  && __is_pointer<_II1>::__value
  && __is_pointer<_II2>::__value);

      return std::__lexicographical_compare<__simple>::__lc(__first1, __last1,
           __first2, __last2);
    }

  template<typename _ForwardIterator, typename _Tp, typename _Compare>
    _ForwardIterator
    __lower_bound(_ForwardIterator __first, _ForwardIterator __last,
    const _Tp& __val, _Compare __comp)
    {
      typedef typename iterator_traits<_ForwardIterator>::difference_type
 _DistanceType;

      _DistanceType __len = std::distance(__first, __last);

      while (__len > 0)
 {
   _DistanceType __half = __len >> 1;
   _ForwardIterator __middle = __first;
   std::advance(__middle, __half);
   if (__comp(__middle, __val))
     {
       __first = __middle;
       ++__first;
       __len = __len - __half - 1;
     }
   else
     __len = __half;
 }
      return __first;
    }
# 998 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 3
  template<typename _ForwardIterator, typename _Tp>
    inline _ForwardIterator
    lower_bound(_ForwardIterator __first, _ForwardIterator __last,
  const _Tp& __val)
    {

     
     

      ;

      return std::__lower_bound(__first, __last, __val,
    __gnu_cxx::__ops::__iter_less_val());
    }



  inline int
  __lg(int __n)
  { return sizeof(int) * 8 - 1 - __builtin_clz(__n); }

  inline unsigned
  __lg(unsigned __n)
  { return sizeof(int) * 8 - 1 - __builtin_clz(__n); }

  inline long
  __lg(long __n)
  { return sizeof(long) * 8 - 1 - __builtin_clzl(__n); }

  inline unsigned long
  __lg(unsigned long __n)
  { return sizeof(long) * 8 - 1 - __builtin_clzl(__n); }

  inline long long
  __lg(long long __n)
  { return sizeof(long long) * 8 - 1 - __builtin_clzll(__n); }

  inline unsigned long long
  __lg(unsigned long long __n)
  { return sizeof(long long) * 8 - 1 - __builtin_clzll(__n); }




# 1055 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 3
  template<typename _II1, typename _II2>
    inline bool
    equal(_II1 __first1, _II1 __last1, _II2 __first2)
    {

     
     
     


      ;

      return std::__equal_aux(std::__niter_base(__first1),
         std::__niter_base(__last1),
         std::__niter_base(__first2));
    }
# 1087 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 3
  template<typename _IIter1, typename _IIter2, typename _BinaryPredicate>
    inline bool
    equal(_IIter1 __first1, _IIter1 __last1,
   _IIter2 __first2, _BinaryPredicate __binary_pred)
    {

     
     
      ;

      for (; __first1 != __last1; ++__first1, ++__first2)
 if (!bool(__binary_pred(*__first1, *__first2)))
   return false;
      return true;
    }
# 1215 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 3
  template<typename _II1, typename _II2>
    inline bool
    lexicographical_compare(_II1 __first1, _II1 __last1,
       _II2 __first2, _II2 __last2)
    {





     
     
     
     
      ;
      ;

      return std::__lexicographical_compare_aux(std::__niter_base(__first1),
      std::__niter_base(__last1),
      std::__niter_base(__first2),
      std::__niter_base(__last2));
    }
# 1251 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 3
  template<typename _II1, typename _II2, typename _Compare>
    inline bool
    lexicographical_compare(_II1 __first1, _II1 __last1,
       _II2 __first2, _II2 __last2, _Compare __comp)
    {

     
     
      ;
      ;

      return std::__lexicographical_compare_impl
 (__first1, __last1, __first2, __last2,
  __gnu_cxx::__ops::__iter_comp_iter(__comp));
    }

  template<typename _InputIterator1, typename _InputIterator2,
    typename _BinaryPredicate>
    pair<_InputIterator1, _InputIterator2>
    __mismatch(_InputIterator1 __first1, _InputIterator1 __last1,
        _InputIterator2 __first2, _BinaryPredicate __binary_pred)
    {
      while (__first1 != __last1 && __binary_pred(__first1, __first2))
        {
   ++__first1;
   ++__first2;
        }
      return pair<_InputIterator1, _InputIterator2>(__first1, __first2);
    }
# 1294 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 3
  template<typename _InputIterator1, typename _InputIterator2>
    inline pair<_InputIterator1, _InputIterator2>
    mismatch(_InputIterator1 __first1, _InputIterator1 __last1,
      _InputIterator2 __first2)
    {

     
     
     


      ;

      return std::__mismatch(__first1, __last1, __first2,
        __gnu_cxx::__ops::__iter_equal_to_iter());
    }
# 1327 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 3
  template<typename _InputIterator1, typename _InputIterator2,
    typename _BinaryPredicate>
    inline pair<_InputIterator1, _InputIterator2>
    mismatch(_InputIterator1 __first1, _InputIterator1 __last1,
      _InputIterator2 __first2, _BinaryPredicate __binary_pred)
    {

     
     
      ;

      return std::__mismatch(__first1, __last1, __first2,
 __gnu_cxx::__ops::__iter_comp_iter(__binary_pred));
    }
# 1427 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algobase.h" 3

}
# 62 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/algorithm" 2 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 1 3
# 59 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstdlib" 1 3
# 39 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstdlib" 3
       
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstdlib" 3
# 72 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstdlib" 3
# 1 "/usr/include/stdlib.h" 1 3 4
# 10 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/machine/ieeefp.h" 1 3 4
# 11 "/usr/include/stdlib.h" 2 3 4





# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/stddef.h" 1 3 4
# 17 "/usr/include/stdlib.h" 2 3 4



# 1 "/usr/include/machine/stdlib.h" 1 3 4
# 12 "/usr/include/machine/stdlib.h" 3 4
extern "C" {


char *mkdtemp (char *);


}
# 21 "/usr/include/stdlib.h" 2 3 4

# 1 "/usr/include/alloca.h" 1 3 4
# 23 "/usr/include/stdlib.h" 2 3 4



# 1 "/usr/include/cygwin/stdlib.h" 1 3 4
# 13 "/usr/include/cygwin/stdlib.h" 3 4
# 1 "/usr/include/cygwin/wait.h" 1 3 4
# 14 "/usr/include/cygwin/stdlib.h" 2 3 4


extern "C"
{


const char *getprogname (void);
void setprogname (const char *);





int unsetenv (const char *);
# 48 "/usr/include/cygwin/stdlib.h" 3 4
extern void * memalign (size_t, size_t);

extern void * valloc (size_t);
# 81 "/usr/include/cygwin/stdlib.h" 3 4
}
# 27 "/usr/include/stdlib.h" 2 3 4






extern "C" {

typedef struct
{
  int quot;
  int rem;
} div_t;

typedef struct
{
  long quot;
  long rem;
} ldiv_t;


typedef struct
{
  long long int quot;
  long long int rem;
} lldiv_t;




typedef int (*__compar_fn_t) (const void *, const void *);







int __attribute__((__cdecl__)) __locale_mb_cur_max (void);



void __attribute__((__cdecl__)) abort (void) __attribute__ ((__noreturn__));
int __attribute__((__cdecl__)) abs (int);

__uint32_t __attribute__((__cdecl__)) arc4random (void);
__uint32_t __attribute__((__cdecl__)) arc4random_uniform (__uint32_t);
void __attribute__((__cdecl__)) arc4random_buf (void *, size_t);

int __attribute__((__cdecl__)) atexit (void (*__func)(void));
double __attribute__((__cdecl__)) atof (const char *__nptr);

float __attribute__((__cdecl__)) atoff (const char *__nptr);

int __attribute__((__cdecl__)) atoi (const char *__nptr);
int __attribute__((__cdecl__)) _atoi_r (struct _reent *, const char *__nptr);
long __attribute__((__cdecl__)) atol (const char *__nptr);
long __attribute__((__cdecl__)) _atol_r (struct _reent *, const char *__nptr);
void * __attribute__((__cdecl__)) bsearch (const void * __key, const void * __base, size_t __nmemb, size_t __size, __compar_fn_t _compar)



                                ;
void * __attribute__((__cdecl__)) calloc (size_t __nmemb, size_t __size) __attribute__ ((__nothrow__));
div_t __attribute__((__cdecl__)) div (int __numer, int __denom);
void __attribute__((__cdecl__)) exit (int __status) __attribute__ ((__noreturn__));
void __attribute__((__cdecl__)) free (void *) __attribute__ ((__nothrow__));
char * __attribute__((__cdecl__)) getenv (const char *__string);
char * __attribute__((__cdecl__)) _getenv_r (struct _reent *, const char *__string);
char * __attribute__((__cdecl__)) _findenv (const char *, int *);
char * __attribute__((__cdecl__)) _findenv_r (struct _reent *, const char *, int *);

extern char *suboptarg;
int __attribute__((__cdecl__)) getsubopt (char **, char * const *, char **);

long __attribute__((__cdecl__)) labs (long);
ldiv_t __attribute__((__cdecl__)) ldiv (long __numer, long __denom);
void * __attribute__((__cdecl__)) malloc (size_t __size) __attribute__ ((__nothrow__));
int __attribute__((__cdecl__)) mblen (const char *, size_t);
int __attribute__((__cdecl__)) _mblen_r (struct _reent *, const char *, size_t, _mbstate_t *);
int __attribute__((__cdecl__)) mbtowc (wchar_t *, const char *, size_t);
int __attribute__((__cdecl__)) _mbtowc_r (struct _reent *, wchar_t *, const char *, size_t, _mbstate_t *);
int __attribute__((__cdecl__)) wctomb (char *, wchar_t);
int __attribute__((__cdecl__)) _wctomb_r (struct _reent *, char *, wchar_t, _mbstate_t *);
size_t __attribute__((__cdecl__)) mbstowcs (wchar_t *, const char *, size_t);
size_t __attribute__((__cdecl__)) _mbstowcs_r (struct _reent *, wchar_t *, const char *, size_t, _mbstate_t *);
size_t __attribute__((__cdecl__)) wcstombs (char *, const wchar_t *, size_t);
size_t __attribute__((__cdecl__)) _wcstombs_r (struct _reent *, char *, const wchar_t *, size_t, _mbstate_t *);


char * __attribute__((__cdecl__)) mkdtemp (char *);






int __attribute__((__cdecl__)) mkstemp (char *);


int __attribute__((__cdecl__)) mkstemps (char *, int);


char * __attribute__((__cdecl__)) mktemp (char *) __attribute__ ((__deprecated__("the use of `mktemp' is dangerous; use `mkstemp' instead")));


char * __attribute__((__cdecl__)) _mkdtemp_r (struct _reent *, char *);
int __attribute__((__cdecl__)) _mkostemp_r (struct _reent *, char *, int);
int __attribute__((__cdecl__)) _mkostemps_r (struct _reent *, char *, int, int);
int __attribute__((__cdecl__)) _mkstemp_r (struct _reent *, char *);
int __attribute__((__cdecl__)) _mkstemps_r (struct _reent *, char *, int);
char * __attribute__((__cdecl__)) _mktemp_r (struct _reent *, char *) __attribute__ ((__deprecated__("the use of `mktemp' is dangerous; use `mkstemp' instead")));
void __attribute__((__cdecl__)) qsort (void * __base, size_t __nmemb, size_t __size, __compar_fn_t _compar);
int __attribute__((__cdecl__)) rand (void);
void * __attribute__((__cdecl__)) realloc (void * __r, size_t __size) __attribute__ ((__nothrow__));

void * __attribute__((__cdecl__)) reallocf (void * __r, size_t __size);


char * __attribute__((__cdecl__)) realpath (const char * path, char * resolved_path);


int __attribute__((__cdecl__)) rpmatch (const char *response);




void __attribute__((__cdecl__)) srand (unsigned __seed);
double __attribute__((__cdecl__)) strtod (const char * __n, char ** __end_PTR);
double __attribute__((__cdecl__)) _strtod_r (struct _reent *,const char * __n, char ** __end_PTR);

float __attribute__((__cdecl__)) strtof (const char * __n, char ** __end_PTR);







long __attribute__((__cdecl__)) strtol (const char * __n, char ** __end_PTR, int __base);
long __attribute__((__cdecl__)) _strtol_r (struct _reent *,const char * __n, char ** __end_PTR, int __base);
unsigned long __attribute__((__cdecl__)) strtoul (const char * __n, char ** __end_PTR, int __base);
unsigned long __attribute__((__cdecl__)) _strtoul_r (struct _reent *,const char * __n, char ** __end_PTR, int __base);
# 186 "/usr/include/stdlib.h" 3 4
int __attribute__((__cdecl__)) system (const char *__string);


long __attribute__((__cdecl__)) a64l (const char *__input);
char * __attribute__((__cdecl__)) l64a (long __input);
char * __attribute__((__cdecl__)) _l64a_r (struct _reent *,long __input);


int __attribute__((__cdecl__)) on_exit (void (*__func)(int, void *),void * __arg);


void __attribute__((__cdecl__)) _Exit (int __status) __attribute__ ((__noreturn__));


int __attribute__((__cdecl__)) putenv (char *__string);

int __attribute__((__cdecl__)) _putenv_r (struct _reent *, char *__string);
void * __attribute__((__cdecl__)) _reallocf_r (struct _reent *, void *, size_t);

int __attribute__((__cdecl__)) setenv (const char *__string, const char *__value, int __overwrite);

int __attribute__((__cdecl__)) _setenv_r (struct _reent *, const char *__string, const char *__value, int __overwrite);
# 219 "/usr/include/stdlib.h" 3 4
char * __attribute__((__cdecl__)) __itoa (int, char *, int);
char * __attribute__((__cdecl__)) __utoa (unsigned, char *, int);

char * __attribute__((__cdecl__)) itoa (int, char *, int);
char * __attribute__((__cdecl__)) utoa (unsigned, char *, int);


int __attribute__((__cdecl__)) rand_r (unsigned *__seed);



double __attribute__((__cdecl__)) drand48 (void);
double __attribute__((__cdecl__)) _drand48_r (struct _reent *);
double __attribute__((__cdecl__)) erand48 (unsigned short [3]);
double __attribute__((__cdecl__)) _erand48_r (struct _reent *, unsigned short [3]);
long __attribute__((__cdecl__)) jrand48 (unsigned short [3]);
long __attribute__((__cdecl__)) _jrand48_r (struct _reent *, unsigned short [3]);
void __attribute__((__cdecl__)) lcong48 (unsigned short [7]);
void __attribute__((__cdecl__)) _lcong48_r (struct _reent *, unsigned short [7]);
long __attribute__((__cdecl__)) lrand48 (void);
long __attribute__((__cdecl__)) _lrand48_r (struct _reent *);
long __attribute__((__cdecl__)) mrand48 (void);
long __attribute__((__cdecl__)) _mrand48_r (struct _reent *);
long __attribute__((__cdecl__)) nrand48 (unsigned short [3]);
long __attribute__((__cdecl__)) _nrand48_r (struct _reent *, unsigned short [3]);
unsigned short *
       __attribute__((__cdecl__)) seed48 (unsigned short [3]);
unsigned short *
       __attribute__((__cdecl__)) _seed48_r (struct _reent *, unsigned short [3]);
void __attribute__((__cdecl__)) srand48 (long);
void __attribute__((__cdecl__)) _srand48_r (struct _reent *, long);


char * __attribute__((__cdecl__)) initstate (unsigned, char *, size_t);
long __attribute__((__cdecl__)) random (void);
char * __attribute__((__cdecl__)) setstate (char *);
void __attribute__((__cdecl__)) srandom (unsigned);


long long __attribute__((__cdecl__)) atoll (const char *__nptr);

long long __attribute__((__cdecl__)) _atoll_r (struct _reent *, const char *__nptr);

long long __attribute__((__cdecl__)) llabs (long long);
lldiv_t __attribute__((__cdecl__)) lldiv (long long __numer, long long __denom);
long long __attribute__((__cdecl__)) strtoll (const char * __n, char ** __end_PTR, int __base);

long long __attribute__((__cdecl__)) _strtoll_r (struct _reent *, const char * __n, char ** __end_PTR, int __base);

unsigned long long __attribute__((__cdecl__)) strtoull (const char * __n, char ** __end_PTR, int __base);

unsigned long long __attribute__((__cdecl__)) _strtoull_r (struct _reent *, const char * __n, char ** __end_PTR, int __base);
# 283 "/usr/include/stdlib.h" 3 4
int __attribute__((__cdecl__)) __attribute__((__nonnull__(1))) posix_memalign (void **, size_t, size_t);


char * __attribute__((__cdecl__)) _dtoa_r (struct _reent *, double, int, int, int *, int*, char**);







int __attribute__((__cdecl__)) _system_r (struct _reent *, const char *);

void __attribute__((__cdecl__)) __eprintf (const char *, const char *, unsigned int, const char *);
# 306 "/usr/include/stdlib.h" 3 4
void __attribute__((__cdecl__)) qsort_r (void * __base, size_t __nmemb, size_t __size, void * __thunk, int (*_compar)(void *, const void *, const void *))
             __asm__ ("" "__bsd_qsort_r");
# 316 "/usr/include/stdlib.h" 3 4
extern long double _strtold_r (struct _reent *, const char *, char **);

extern long double strtold (const char *, char **);
# 333 "/usr/include/stdlib.h" 3 4
}
# 73 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstdlib" 2 3
# 114 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstdlib" 3
namespace std
{


  using ::div_t;
  using ::ldiv_t;

  using ::abort;
  using ::abs;
  using ::atexit;





  using ::atof;
  using ::atoi;
  using ::atol;
  using ::bsearch;
  using ::calloc;
  using ::div;
  using ::exit;
  using ::free;
  using ::getenv;
  using ::labs;
  using ::ldiv;
  using ::malloc;

  using ::mblen;
  using ::mbstowcs;
  using ::mbtowc;

  using ::qsort;





  using ::rand;
  using ::realloc;
  using ::srand;
  using ::strtod;
  using ::strtol;
  using ::strtoul;
  using ::system;

  using ::wcstombs;
  using ::wctomb;



  inline long
  abs(long __i) { return __builtin_labs(__i); }

  inline ldiv_t
  div(long __i, long __j) { return ldiv(__i, __j); }



  inline long long
  abs(long long __x) { return __builtin_llabs (__x); }



  inline __int128
  abs(__int128 __x) { return __x >= 0 ? __x : -__x; }
# 195 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstdlib" 3

}
# 209 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstdlib" 3
namespace __gnu_cxx
{



  using ::lldiv_t;





  using ::_Exit;



  using ::llabs;

  inline lldiv_t
  div(long long __n, long long __d)
  { lldiv_t __q; __q.quot = __n / __d; __q.rem = __n % __d; return __q; }

  using ::lldiv;
# 241 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstdlib" 3
  using ::atoll;
  using ::strtoll;
  using ::strtoull;

  using ::strtof;
  using ::strtold;


}

namespace std
{

  using ::__gnu_cxx::lldiv_t;

  using ::__gnu_cxx::_Exit;

  using ::__gnu_cxx::llabs;
  using ::__gnu_cxx::div;
  using ::__gnu_cxx::lldiv;

  using ::__gnu_cxx::atoll;
  using ::__gnu_cxx::strtof;
  using ::__gnu_cxx::strtoll;
  using ::__gnu_cxx::strtoull;
  using ::__gnu_cxx::strtold;
}
# 60 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 2 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/algorithmfwd.h" 1 3
# 33 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/algorithmfwd.h" 3
       
# 34 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/algorithmfwd.h" 3
# 42 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/algorithmfwd.h" 3
namespace std
{

# 203 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/algorithmfwd.h" 3
  template<typename _FIter, typename _Tp>
    bool
    binary_search(_FIter, _FIter, const _Tp&);

  template<typename _FIter, typename _Tp, typename _Compare>
    bool
    binary_search(_FIter, _FIter, const _Tp&, _Compare);

  template<typename _IIter, typename _OIter>
    _OIter
    copy(_IIter, _IIter, _OIter);

  template<typename _BIter1, typename _BIter2>
    _BIter2
    copy_backward(_BIter1, _BIter1, _BIter2);
# 232 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/algorithmfwd.h" 3
  template<typename _FIter, typename _Tp>
    pair<_FIter, _FIter>
    equal_range(_FIter, _FIter, const _Tp&);

  template<typename _FIter, typename _Tp, typename _Compare>
    pair<_FIter, _FIter>
    equal_range(_FIter, _FIter, const _Tp&, _Compare);

  template<typename _FIter, typename _Tp>
    void
    fill(_FIter, _FIter, const _Tp&);

  template<typename _OIter, typename _Size, typename _Tp>
    _OIter
    fill_n(_OIter, _Size, const _Tp&);



  template<typename _FIter1, typename _FIter2>
    _FIter1
    find_end(_FIter1, _FIter1, _FIter2, _FIter2);

  template<typename _FIter1, typename _FIter2, typename _BinaryPredicate>
    _FIter1
    find_end(_FIter1, _FIter1, _FIter2, _FIter2, _BinaryPredicate);
# 271 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/algorithmfwd.h" 3
  template<typename _IIter1, typename _IIter2>
    bool
    includes(_IIter1, _IIter1, _IIter2, _IIter2);

  template<typename _IIter1, typename _IIter2, typename _Compare>
    bool
    includes(_IIter1, _IIter1, _IIter2, _IIter2, _Compare);

  template<typename _BIter>
    void
    inplace_merge(_BIter, _BIter, _BIter);

  template<typename _BIter, typename _Compare>
    void
    inplace_merge(_BIter, _BIter, _BIter, _Compare);
# 334 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/algorithmfwd.h" 3
  template<typename _FIter1, typename _FIter2>
    void
    iter_swap(_FIter1, _FIter2);

  template<typename _FIter, typename _Tp>
    _FIter
    lower_bound(_FIter, _FIter, const _Tp&);

  template<typename _FIter, typename _Tp, typename _Compare>
    _FIter
    lower_bound(_FIter, _FIter, const _Tp&, _Compare);

  template<typename _RAIter>
    void
    make_heap(_RAIter, _RAIter);

  template<typename _RAIter, typename _Compare>
    void
    make_heap(_RAIter, _RAIter, _Compare);

  template<typename _Tp>
   
    const _Tp&
    max(const _Tp&, const _Tp&);

  template<typename _Tp, typename _Compare>
   
    const _Tp&
    max(const _Tp&, const _Tp&, _Compare);




  template<typename _Tp>
   
    const _Tp&
    min(const _Tp&, const _Tp&);

  template<typename _Tp, typename _Compare>
   
    const _Tp&
    min(const _Tp&, const _Tp&, _Compare);
# 433 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/algorithmfwd.h" 3
  template<typename _BIter>
    bool
    next_permutation(_BIter, _BIter);

  template<typename _BIter, typename _Compare>
    bool
    next_permutation(_BIter, _BIter, _Compare);
# 450 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/algorithmfwd.h" 3
  template<typename _IIter, typename _RAIter>
    _RAIter
    partial_sort_copy(_IIter, _IIter, _RAIter, _RAIter);

  template<typename _IIter, typename _RAIter, typename _Compare>
    _RAIter
    partial_sort_copy(_IIter, _IIter, _RAIter, _RAIter, _Compare);
# 471 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/algorithmfwd.h" 3
  template<typename _RAIter>
    void
    pop_heap(_RAIter, _RAIter);

  template<typename _RAIter, typename _Compare>
    void
    pop_heap(_RAIter, _RAIter, _Compare);

  template<typename _BIter>
    bool
    prev_permutation(_BIter, _BIter);

  template<typename _BIter, typename _Compare>
    bool
    prev_permutation(_BIter, _BIter, _Compare);

  template<typename _RAIter>
    void
    push_heap(_RAIter, _RAIter);

  template<typename _RAIter, typename _Compare>
    void
    push_heap(_RAIter, _RAIter, _Compare);



  template<typename _FIter, typename _Tp>
    _FIter
    remove(_FIter, _FIter, const _Tp&);

  template<typename _FIter, typename _Predicate>
    _FIter
    remove_if(_FIter, _FIter, _Predicate);

  template<typename _IIter, typename _OIter, typename _Tp>
    _OIter
    remove_copy(_IIter, _IIter, _OIter, const _Tp&);

  template<typename _IIter, typename _OIter, typename _Predicate>
    _OIter
    remove_copy_if(_IIter, _IIter, _OIter, _Predicate);



  template<typename _IIter, typename _OIter, typename _Tp>
    _OIter
    replace_copy(_IIter, _IIter, _OIter, const _Tp&, const _Tp&);

  template<typename _Iter, typename _OIter, typename _Predicate, typename _Tp>
    _OIter
    replace_copy_if(_Iter, _Iter, _OIter, _Predicate, const _Tp&);



  template<typename _BIter>
    void
    reverse(_BIter, _BIter);

  template<typename _BIter, typename _OIter>
    _OIter
    reverse_copy(_BIter, _BIter, _OIter);

  inline namespace _V2
  {
    template<typename _FIter>
      _FIter
      rotate(_FIter, _FIter, _FIter);
  }

  template<typename _FIter, typename _OIter>
    _OIter
    rotate_copy(_FIter, _FIter, _FIter, _OIter);
# 557 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/algorithmfwd.h" 3
  template<typename _RAIter>
    void
    sort_heap(_RAIter, _RAIter);

  template<typename _RAIter, typename _Compare>
    void
    sort_heap(_RAIter, _RAIter, _Compare);

  template<typename _BIter, typename _Predicate>
    _BIter
    stable_partition(_BIter, _BIter, _Predicate);

  template<typename _Tp>
    void
    swap(_Tp&, _Tp&)




    ;

  template<typename _Tp, size_t _Nm>
    void
    swap(_Tp (&__a)[_Nm], _Tp (&__b)[_Nm])



    ;

  template<typename _FIter1, typename _FIter2>
    _FIter2
    swap_ranges(_FIter1, _FIter1, _FIter2);



  template<typename _FIter>
    _FIter
    unique(_FIter, _FIter);

  template<typename _FIter, typename _BinaryPredicate>
    _FIter
    unique(_FIter, _FIter, _BinaryPredicate);



  template<typename _FIter, typename _Tp>
    _FIter
    upper_bound(_FIter, _FIter, const _Tp&);

  template<typename _FIter, typename _Tp, typename _Compare>
    _FIter
    upper_bound(_FIter, _FIter, const _Tp&, _Compare);





  template<typename _FIter>
    _FIter
    adjacent_find(_FIter, _FIter);

  template<typename _FIter, typename _BinaryPredicate>
    _FIter
    adjacent_find(_FIter, _FIter, _BinaryPredicate);

  template<typename _IIter, typename _Tp>
    typename iterator_traits<_IIter>::difference_type
    count(_IIter, _IIter, const _Tp&);

  template<typename _IIter, typename _Predicate>
    typename iterator_traits<_IIter>::difference_type
    count_if(_IIter, _IIter, _Predicate);

  template<typename _IIter1, typename _IIter2>
    bool
    equal(_IIter1, _IIter1, _IIter2);

  template<typename _IIter1, typename _IIter2, typename _BinaryPredicate>
    bool
    equal(_IIter1, _IIter1, _IIter2, _BinaryPredicate);

  template<typename _IIter, typename _Tp>
    _IIter
    find(_IIter, _IIter, const _Tp&);

  template<typename _FIter1, typename _FIter2>
    _FIter1
    find_first_of(_FIter1, _FIter1, _FIter2, _FIter2);

  template<typename _FIter1, typename _FIter2, typename _BinaryPredicate>
    _FIter1
    find_first_of(_FIter1, _FIter1, _FIter2, _FIter2, _BinaryPredicate);

  template<typename _IIter, typename _Predicate>
    _IIter
    find_if(_IIter, _IIter, _Predicate);

  template<typename _IIter, typename _Funct>
    _Funct
    for_each(_IIter, _IIter, _Funct);

  template<typename _FIter, typename _Generator>
    void
    generate(_FIter, _FIter, _Generator);

  template<typename _OIter, typename _Size, typename _Generator>
    _OIter
    generate_n(_OIter, _Size, _Generator);

  template<typename _IIter1, typename _IIter2>
    bool
    lexicographical_compare(_IIter1, _IIter1, _IIter2, _IIter2);

  template<typename _IIter1, typename _IIter2, typename _Compare>
    bool
    lexicographical_compare(_IIter1, _IIter1, _IIter2, _IIter2, _Compare);

  template<typename _FIter>
   
    _FIter
    max_element(_FIter, _FIter);

  template<typename _FIter, typename _Compare>
   
    _FIter
    max_element(_FIter, _FIter, _Compare);

  template<typename _IIter1, typename _IIter2, typename _OIter>
    _OIter
    merge(_IIter1, _IIter1, _IIter2, _IIter2, _OIter);

  template<typename _IIter1, typename _IIter2, typename _OIter,
    typename _Compare>
    _OIter
    merge(_IIter1, _IIter1, _IIter2, _IIter2, _OIter, _Compare);

  template<typename _FIter>
   
    _FIter
    min_element(_FIter, _FIter);

  template<typename _FIter, typename _Compare>
   
    _FIter
    min_element(_FIter, _FIter, _Compare);

  template<typename _IIter1, typename _IIter2>
    pair<_IIter1, _IIter2>
    mismatch(_IIter1, _IIter1, _IIter2);

  template<typename _IIter1, typename _IIter2, typename _BinaryPredicate>
    pair<_IIter1, _IIter2>
    mismatch(_IIter1, _IIter1, _IIter2, _BinaryPredicate);

  template<typename _RAIter>
    void
    nth_element(_RAIter, _RAIter, _RAIter);

  template<typename _RAIter, typename _Compare>
    void
    nth_element(_RAIter, _RAIter, _RAIter, _Compare);

  template<typename _RAIter>
    void
    partial_sort(_RAIter, _RAIter, _RAIter);

  template<typename _RAIter, typename _Compare>
    void
    partial_sort(_RAIter, _RAIter, _RAIter, _Compare);

  template<typename _BIter, typename _Predicate>
    _BIter
    partition(_BIter, _BIter, _Predicate);

  template<typename _RAIter>
    void
    random_shuffle(_RAIter, _RAIter);

  template<typename _RAIter, typename _Generator>
    void
    random_shuffle(_RAIter, _RAIter,



     _Generator&);


  template<typename _FIter, typename _Tp>
    void
    replace(_FIter, _FIter, const _Tp&, const _Tp&);

  template<typename _FIter, typename _Predicate, typename _Tp>
    void
    replace_if(_FIter, _FIter, _Predicate, const _Tp&);

  template<typename _FIter1, typename _FIter2>
    _FIter1
    search(_FIter1, _FIter1, _FIter2, _FIter2);

  template<typename _FIter1, typename _FIter2, typename _BinaryPredicate>
    _FIter1
    search(_FIter1, _FIter1, _FIter2, _FIter2, _BinaryPredicate);

  template<typename _FIter, typename _Size, typename _Tp>
    _FIter
    search_n(_FIter, _FIter, _Size, const _Tp&);

  template<typename _FIter, typename _Size, typename _Tp,
    typename _BinaryPredicate>
    _FIter
    search_n(_FIter, _FIter, _Size, const _Tp&, _BinaryPredicate);

  template<typename _IIter1, typename _IIter2, typename _OIter>
    _OIter
    set_difference(_IIter1, _IIter1, _IIter2, _IIter2, _OIter);

  template<typename _IIter1, typename _IIter2, typename _OIter,
    typename _Compare>
    _OIter
    set_difference(_IIter1, _IIter1, _IIter2, _IIter2, _OIter, _Compare);

  template<typename _IIter1, typename _IIter2, typename _OIter>
    _OIter
    set_intersection(_IIter1, _IIter1, _IIter2, _IIter2, _OIter);

  template<typename _IIter1, typename _IIter2, typename _OIter,
    typename _Compare>
    _OIter
    set_intersection(_IIter1, _IIter1, _IIter2, _IIter2, _OIter, _Compare);

  template<typename _IIter1, typename _IIter2, typename _OIter>
    _OIter
    set_symmetric_difference(_IIter1, _IIter1, _IIter2, _IIter2, _OIter);

  template<typename _IIter1, typename _IIter2, typename _OIter,
    typename _Compare>
    _OIter
    set_symmetric_difference(_IIter1, _IIter1, _IIter2, _IIter2,
        _OIter, _Compare);

  template<typename _IIter1, typename _IIter2, typename _OIter>
    _OIter
    set_union(_IIter1, _IIter1, _IIter2, _IIter2, _OIter);

  template<typename _IIter1, typename _IIter2, typename _OIter,
    typename _Compare>
    _OIter
    set_union(_IIter1, _IIter1, _IIter2, _IIter2, _OIter, _Compare);

  template<typename _RAIter>
    void
    sort(_RAIter, _RAIter);

  template<typename _RAIter, typename _Compare>
    void
    sort(_RAIter, _RAIter, _Compare);

  template<typename _RAIter>
    void
    stable_sort(_RAIter, _RAIter);

  template<typename _RAIter, typename _Compare>
    void
    stable_sort(_RAIter, _RAIter, _Compare);

  template<typename _IIter, typename _OIter, typename _UnaryOperation>
    _OIter
    transform(_IIter, _IIter, _OIter, _UnaryOperation);

  template<typename _IIter1, typename _IIter2, typename _OIter,
    typename _BinaryOperation>
    _OIter
    transform(_IIter1, _IIter1, _IIter2, _OIter, _BinaryOperation);

  template<typename _IIter, typename _OIter>
    _OIter
    unique_copy(_IIter, _IIter, _OIter);

  template<typename _IIter, typename _OIter, typename _BinaryPredicate>
    _OIter
    unique_copy(_IIter, _IIter, _OIter, _BinaryPredicate);


}
# 61 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 2 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_heap.h" 1 3
# 62 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_heap.h" 3
namespace std
{







  template<typename _RandomAccessIterator, typename _Distance,
    typename _Compare>
    _Distance
    __is_heap_until(_RandomAccessIterator __first, _Distance __n,
      _Compare __comp)
    {
      _Distance __parent = 0;
      for (_Distance __child = 1; __child < __n; ++__child)
 {
   if (__comp(__first + __parent, __first + __child))
     return __child;
   if ((__child & 1) == 0)
     ++__parent;
 }
      return __n;
    }



  template<typename _RandomAccessIterator, typename _Distance>
    inline bool
    __is_heap(_RandomAccessIterator __first, _Distance __n)
    {
      return std::__is_heap_until(__first, __n,
   __gnu_cxx::__ops::__iter_less_iter()) == __n;
    }

  template<typename _RandomAccessIterator, typename _Compare,
    typename _Distance>
    inline bool
    __is_heap(_RandomAccessIterator __first, _Compare __comp, _Distance __n)
    {
      return std::__is_heap_until(__first, __n,
 __gnu_cxx::__ops::__iter_comp_iter(__comp)) == __n;
    }

  template<typename _RandomAccessIterator>
    inline bool
    __is_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
    { return std::__is_heap(__first, std::distance(__first, __last)); }

  template<typename _RandomAccessIterator, typename _Compare>
    inline bool
    __is_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
       _Compare __comp)
    { return std::__is_heap(__first, __comp, std::distance(__first, __last)); }




  template<typename _RandomAccessIterator, typename _Distance, typename _Tp,
    typename _Compare>
    void
    __push_heap(_RandomAccessIterator __first,
  _Distance __holeIndex, _Distance __topIndex, _Tp __value,
  _Compare __comp)
    {
      _Distance __parent = (__holeIndex - 1) / 2;
      while (__holeIndex > __topIndex && __comp(__first + __parent, __value))
 {
   *(__first + __holeIndex) = (*(__first + __parent));
   __holeIndex = __parent;
   __parent = (__holeIndex - 1) / 2;
 }
      *(__first + __holeIndex) = (__value);
    }
# 148 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_heap.h" 3
  template<typename _RandomAccessIterator>
    inline void
    push_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
   _ValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
   _DistanceType;


     

     
      ;
      ;

      _ValueType __value = (*(__last - 1));
      std::__push_heap(__first, _DistanceType((__last - __first) - 1),
         _DistanceType(0), (__value),
         __gnu_cxx::__ops::__iter_less_val());
    }
# 182 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_heap.h" 3
  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    push_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
       _Compare __comp)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
   _ValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
   _DistanceType;


     

      ;
      ;

      _ValueType __value = (*(__last - 1));
      std::__push_heap(__first, _DistanceType((__last - __first) - 1),
         _DistanceType(0), (__value),
         __gnu_cxx::__ops::__iter_comp_val(__comp));
    }

  template<typename _RandomAccessIterator, typename _Distance,
    typename _Tp, typename _Compare>
    void
    __adjust_heap(_RandomAccessIterator __first, _Distance __holeIndex,
    _Distance __len, _Tp __value, _Compare __comp)
    {
      const _Distance __topIndex = __holeIndex;
      _Distance __secondChild = __holeIndex;
      while (__secondChild < (__len - 1) / 2)
 {
   __secondChild = 2 * (__secondChild + 1);
   if (__comp(__first + __secondChild,
       __first + (__secondChild - 1)))
     __secondChild--;
   *(__first + __holeIndex) = (*(__first + __secondChild));
   __holeIndex = __secondChild;
 }
      if ((__len & 1) == 0 && __secondChild == (__len - 2) / 2)
 {
   __secondChild = 2 * (__secondChild + 1);
   *(__first + __holeIndex) = (*(__first + (__secondChild - 1)))
                                  ;
   __holeIndex = __secondChild - 1;
 }
      std::__push_heap(__first, __holeIndex, __topIndex,
         (__value),
         __gnu_cxx::__ops::__iter_comp_val(__comp));
    }

  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    __pop_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
        _RandomAccessIterator __result, _Compare __comp)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
 _ValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
 _DistanceType;

      _ValueType __value = (*__result);
      *__result = (*__first);
      std::__adjust_heap(__first, _DistanceType(0),
    _DistanceType(__last - __first),
    (__value), __comp);
    }
# 261 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_heap.h" 3
  template<typename _RandomAccessIterator>
    inline void
    pop_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
 _ValueType;


     

     
      ;
      ;
      ;

      if (__last - __first > 1)
 {
   --__last;
   std::__pop_heap(__first, __last, __last,
     __gnu_cxx::__ops::__iter_less_iter());
 }
    }
# 295 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_heap.h" 3
  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    pop_heap(_RandomAccessIterator __first,
      _RandomAccessIterator __last, _Compare __comp)
    {

     

      ;
      ;
      ;

      if (__last - __first > 1)
 {
   --__last;
   std::__pop_heap(__first, __last, __last,
     __gnu_cxx::__ops::__iter_comp_iter(__comp));
 }
    }

  template<typename _RandomAccessIterator, typename _Compare>
    void
    __make_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
  _Compare __comp)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
   _ValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
   _DistanceType;

      if (__last - __first < 2)
 return;

      const _DistanceType __len = __last - __first;
      _DistanceType __parent = (__len - 2) / 2;
      while (true)
 {
   _ValueType __value = (*(__first + __parent));
   std::__adjust_heap(__first, __parent, __len, (__value),
        __comp);
   if (__parent == 0)
     return;
   __parent--;
 }
    }
# 349 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_heap.h" 3
  template<typename _RandomAccessIterator>
    inline void
    make_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {

     

     

      ;

      std::__make_heap(__first, __last,
         __gnu_cxx::__ops::__iter_less_iter());
    }
# 374 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_heap.h" 3
  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    make_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
       _Compare __comp)
    {

     

      ;

      std::__make_heap(__first, __last,
         __gnu_cxx::__ops::__iter_comp_iter(__comp));
    }

  template<typename _RandomAccessIterator, typename _Compare>
    void
    __sort_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
  _Compare __comp)
    {
      while (__last - __first > 1)
 {
   --__last;
   std::__pop_heap(__first, __last, __last, __comp);
 }
    }
# 408 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_heap.h" 3
  template<typename _RandomAccessIterator>
    inline void
    sort_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {

     

     

      ;
      ;

      std::__sort_heap(__first, __last,
         __gnu_cxx::__ops::__iter_less_iter());
    }
# 434 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_heap.h" 3
  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    sort_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
       _Compare __comp)
    {

     

      ;
      ;

      std::__sort_heap(__first, __last,
         __gnu_cxx::__ops::__iter_comp_iter(__comp));
    }
# 529 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_heap.h" 3

}
# 62 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 2 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_tempbuf.h" 1 3
# 60 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_tempbuf.h" 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_construct.h" 1 3
# 59 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_construct.h" 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/new" 1 3
# 37 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/new" 3
       
# 38 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/new" 3


# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/exception" 1 3
# 33 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/exception" 3
       
# 34 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/exception" 3

#pragma GCC visibility push(default)


# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/atomic_lockfree_defines.h" 1 3
# 33 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/atomic_lockfree_defines.h" 3
       
# 34 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/atomic_lockfree_defines.h" 3
# 39 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/exception" 2 3

extern "C++" {

namespace std
{
# 60 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/exception" 3
  class exception
  {
  public:
    exception() throw() { }
    virtual ~exception() throw();



    virtual const char* what() const throw();
  };



  class bad_exception : public exception
  {
  public:
    bad_exception() throw() { }



    virtual ~bad_exception() throw();


    virtual const char* what() const throw();
  };


  typedef void (*terminate_handler) ();


  typedef void (*unexpected_handler) ();


  terminate_handler set_terminate(terminate_handler) throw();
# 102 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/exception" 3
  void terminate() throw() __attribute__ ((__noreturn__));


  unexpected_handler set_unexpected(unexpected_handler) throw();
# 114 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/exception" 3
  void unexpected() __attribute__ ((__noreturn__));
# 127 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/exception" 3
  bool uncaught_exception() throw() __attribute__ ((__pure__));


}

namespace __gnu_cxx
{

# 152 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/exception" 3
  void __verbose_terminate_handler();


}

}

#pragma GCC visibility pop
# 41 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/new" 2 3

#pragma GCC visibility push(default)

extern "C++" {

namespace std
{






  class bad_alloc : public exception
  {
  public:
    bad_alloc() throw() { }



    virtual ~bad_alloc() throw();


    virtual const char* what() const throw();
  };
# 82 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/new" 3
  struct nothrow_t { };

  extern const nothrow_t nothrow;



  typedef void (*new_handler)();



  new_handler set_new_handler(new_handler) throw();





}
# 111 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/new" 3
void* operator new(std::size_t) throw(std::bad_alloc)
  __attribute__((__externally_visible__));
void* operator new[](std::size_t) throw(std::bad_alloc)
  __attribute__((__externally_visible__));
void operator delete(void*) throw()
  __attribute__((__externally_visible__));
void operator delete[](void*) throw()
  __attribute__((__externally_visible__));
void* operator new(std::size_t, const std::nothrow_t&) throw()
  __attribute__((__externally_visible__));
void* operator new[](std::size_t, const std::nothrow_t&) throw()
  __attribute__((__externally_visible__));
void operator delete(void*, const std::nothrow_t&) throw()
  __attribute__((__externally_visible__));
void operator delete[](void*, const std::nothrow_t&) throw()
  __attribute__((__externally_visible__));


inline void* operator new(std::size_t, void* __p) throw()
{ return __p; }
inline void* operator new[](std::size_t, void* __p) throw()
{ return __p; }


inline void operator delete (void*, void*) throw() { }
inline void operator delete[](void*, void*) throw() { }

}

#pragma GCC visibility pop
# 60 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_construct.h" 2 3

# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ext/alloc_traits.h" 1 3
# 32 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ext/alloc_traits.h" 3
       
# 33 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ext/alloc_traits.h" 3





# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/allocator.h" 1 3
# 46 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/allocator.h" 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/c++allocator.h" 1 3
# 33 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/c++allocator.h" 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ext/new_allocator.h" 1 3
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ext/new_allocator.h" 3
namespace __gnu_cxx
{


  using std::size_t;
  using std::ptrdiff_t;
# 57 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ext/new_allocator.h" 3
  template<typename _Tp>
    class new_allocator
    {
    public:
      typedef size_t size_type;
      typedef ptrdiff_t difference_type;
      typedef _Tp* pointer;
      typedef const _Tp* const_pointer;
      typedef _Tp& reference;
      typedef const _Tp& const_reference;
      typedef _Tp value_type;

      template<typename _Tp1>
        struct rebind
        { typedef new_allocator<_Tp1> other; };







      new_allocator() throw() { }

      new_allocator(const new_allocator&) throw() { }

      template<typename _Tp1>
        new_allocator(const new_allocator<_Tp1>&) throw() { }

      ~new_allocator() throw() { }

      pointer
      address(reference __x) const
      { return std::__addressof(__x); }

      const_pointer
      address(const_reference __x) const
      { return std::__addressof(__x); }



      pointer
      allocate(size_type __n, const void* = 0)
      {
 if (__n > this->max_size())
   std::__throw_bad_alloc();

 return static_cast<_Tp*>(::operator new(__n * sizeof(_Tp)));
      }


      void
      deallocate(pointer __p, size_type)
      { ::operator delete(__p); }

      size_type
      max_size() const throw()
      { return size_t(-1) / sizeof(_Tp); }
# 128 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ext/new_allocator.h" 3
      void
      construct(pointer __p, const _Tp& __val)
      { ::new((void *)__p) _Tp(__val); }

      void
      destroy(pointer __p) { __p->~_Tp(); }

    };

  template<typename _Tp>
    inline bool
    operator==(const new_allocator<_Tp>&, const new_allocator<_Tp>&)
    { return true; }

  template<typename _Tp>
    inline bool
    operator!=(const new_allocator<_Tp>&, const new_allocator<_Tp>&)
    { return false; }


}
# 34 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/c++allocator.h" 2 3
# 47 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/allocator.h" 2 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/memoryfwd.h" 1 3
# 46 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/memoryfwd.h" 3
       
# 47 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/memoryfwd.h" 3



namespace std
{

# 63 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/memoryfwd.h" 3
  template<typename>
    class allocator;

  template<>
    class allocator<void>;


  template<typename, typename>
    struct uses_allocator;




}
# 48 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/allocator.h" 2 3




namespace std
{








  template<>
    class allocator<void>
    {
    public:
      typedef size_t size_type;
      typedef ptrdiff_t difference_type;
      typedef void* pointer;
      typedef const void* const_pointer;
      typedef void value_type;

      template<typename _Tp1>
        struct rebind
        { typedef allocator<_Tp1> other; };






    };
# 91 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/allocator.h" 3
  template<typename _Tp>
    class allocator: public __gnu_cxx::new_allocator<_Tp>
    {
   public:
      typedef size_t size_type;
      typedef ptrdiff_t difference_type;
      typedef _Tp* pointer;
      typedef const _Tp* const_pointer;
      typedef _Tp& reference;
      typedef const _Tp& const_reference;
      typedef _Tp value_type;

      template<typename _Tp1>
        struct rebind
        { typedef allocator<_Tp1> other; };







      allocator() throw() { }

      allocator(const allocator& __a) throw()
      : __gnu_cxx::new_allocator<_Tp>(__a) { }

      template<typename _Tp1>
        allocator(const allocator<_Tp1>&) throw() { }

      ~allocator() throw() { }


    };

  template<typename _T1, typename _T2>
    inline bool
    operator==(const allocator<_T1>&, const allocator<_T2>&)
    throw()
    { return true; }

  template<typename _Tp>
    inline bool
    operator==(const allocator<_Tp>&, const allocator<_Tp>&)
    throw()
    { return true; }

  template<typename _T1, typename _T2>
    inline bool
    operator!=(const allocator<_T1>&, const allocator<_T2>&)
    throw()
    { return false; }

  template<typename _Tp>
    inline bool
    operator!=(const allocator<_Tp>&, const allocator<_Tp>&)
    throw()
    { return false; }






  extern template class allocator<char>;
  extern template class allocator<wchar_t>;






  template<typename _Alloc, bool = __is_empty(_Alloc)>
    struct __alloc_swap
    { static void _S_do_it(_Alloc&, _Alloc&) { } };

  template<typename _Alloc>
    struct __alloc_swap<_Alloc, false>
    {
      static void
      _S_do_it(_Alloc& __one, _Alloc& __two)
      {

 if (__one != __two)
   swap(__one, __two);
      }
    };


  template<typename _Alloc, bool = __is_empty(_Alloc)>
    struct __alloc_neq
    {
      static bool
      _S_do_it(const _Alloc&, const _Alloc&)
      { return false; }
    };

  template<typename _Alloc>
    struct __alloc_neq<_Alloc, false>
    {
      static bool
      _S_do_it(const _Alloc& __one, const _Alloc& __two)
      { return __one != __two; }
    };
# 226 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/allocator.h" 3

}
# 39 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ext/alloc_traits.h" 2 3


namespace __gnu_cxx
{

# 94 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ext/alloc_traits.h" 3
template<typename _Alloc>
  struct __alloc_traits



  {
    typedef _Alloc allocator_type;
# 172 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ext/alloc_traits.h" 3
    typedef typename _Alloc::pointer pointer;
    typedef typename _Alloc::const_pointer const_pointer;
    typedef typename _Alloc::value_type value_type;
    typedef typename _Alloc::reference reference;
    typedef typename _Alloc::const_reference const_reference;
    typedef typename _Alloc::size_type size_type;
    typedef typename _Alloc::difference_type difference_type;

    static pointer
    allocate(_Alloc& __a, size_type __n)
    { return __a.allocate(__n); }

    static void deallocate(_Alloc& __a, pointer __p, size_type __n)
    { __a.deallocate(__p, __n); }

    template<typename _Tp>
      static void construct(_Alloc& __a, pointer __p, const _Tp& __arg)
      { __a.construct(__p, __arg); }

    static void destroy(_Alloc& __a, pointer __p)
    { __a.destroy(__p); }

    static size_type max_size(const _Alloc& __a)
    { return __a.max_size(); }

    static const _Alloc& _S_select_on_copy(const _Alloc& __a) { return __a; }

    static void _S_on_swap(_Alloc& __a, _Alloc& __b)
    {


      std::__alloc_swap<_Alloc>::_S_do_it(__a, __b);
    }

    template<typename _Tp>
      struct rebind
      { typedef typename _Alloc::template rebind<_Tp>::other other; };

  };


}
# 62 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_construct.h" 2 3

namespace std
{

# 77 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_construct.h" 3
  template<typename _T1, typename _T2>
    inline void
    _Construct(_T1* __p, const _T2& __value)
    {


      ::new(static_cast<void*>(__p)) _T1(__value);
    }





  template<typename _Tp>
    inline void
    _Destroy(_Tp* __pointer)
    { __pointer->~_Tp(); }

  template<bool>
    struct _Destroy_aux
    {
      template<typename _ForwardIterator>
        static void
        __destroy(_ForwardIterator __first, _ForwardIterator __last)
 {
   for (; __first != __last; ++__first)
     std::_Destroy(std::__addressof(*__first));
 }
    };

  template<>
    struct _Destroy_aux<true>
    {
      template<typename _ForwardIterator>
        static void
        __destroy(_ForwardIterator, _ForwardIterator) { }
    };






  template<typename _ForwardIterator>
    inline void
    _Destroy(_ForwardIterator __first, _ForwardIterator __last)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
                       _Value_type;
      std::_Destroy_aux<__has_trivial_destructor(_Value_type)>::
 __destroy(__first, __last);
    }







  template<typename _ForwardIterator, typename _Allocator>
    void
    _Destroy(_ForwardIterator __first, _ForwardIterator __last,
      _Allocator& __alloc)
    {
      typedef __gnu_cxx::__alloc_traits<_Allocator> __traits;
      for (; __first != __last; ++__first)
 __traits::destroy(__alloc, std::__addressof(*__first));
    }

  template<typename _ForwardIterator, typename _Tp>
    inline void
    _Destroy(_ForwardIterator __first, _ForwardIterator __last,
      allocator<_Tp>&)
    {
      _Destroy(__first, __last);
    }


}
# 61 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_tempbuf.h" 2 3

namespace std
{

# 83 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_tempbuf.h" 3
  template<typename _Tp>
    pair<_Tp*, ptrdiff_t>
    get_temporary_buffer(ptrdiff_t __len)
    {
      const ptrdiff_t __max =
 __gnu_cxx::__numeric_traits<ptrdiff_t>::__max / sizeof(_Tp);
      if (__len > __max)
 __len = __max;

      while (__len > 0)
 {
   _Tp* __tmp = static_cast<_Tp*>(::operator new(__len * sizeof(_Tp),
       std::nothrow));
   if (__tmp != 0)
     return std::pair<_Tp*, ptrdiff_t>(__tmp, __len);
   __len /= 2;
 }
      return std::pair<_Tp*, ptrdiff_t>(static_cast<_Tp*>(0), 0);
    }
# 110 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_tempbuf.h" 3
  template<typename _Tp>
    inline void
    return_temporary_buffer(_Tp* __p)
    { ::operator delete(__p, std::nothrow); }







  template<typename _ForwardIterator, typename _Tp>
    class _Temporary_buffer
    {

     

    public:
      typedef _Tp value_type;
      typedef value_type* pointer;
      typedef pointer iterator;
      typedef ptrdiff_t size_type;

    protected:
      size_type _M_original_len;
      size_type _M_len;
      pointer _M_buffer;

    public:

      size_type
      size() const
      { return _M_len; }


      size_type
      requested_size() const
      { return _M_original_len; }


      iterator
      begin()
      { return _M_buffer; }


      iterator
      end()
      { return _M_buffer + _M_len; }





      _Temporary_buffer(_ForwardIterator __first, _ForwardIterator __last);

      ~_Temporary_buffer()
      {
 std::_Destroy(_M_buffer, _M_buffer + _M_len);
 std::return_temporary_buffer(_M_buffer);
      }

    private:

      _Temporary_buffer(const _Temporary_buffer&);

      void
      operator=(const _Temporary_buffer&);
    };


  template<bool>
    struct __uninitialized_construct_buf_dispatch
    {
      template<typename _Pointer, typename _ForwardIterator>
        static void
        __ucr(_Pointer __first, _Pointer __last,
       _ForwardIterator __seed)
        {
   if(__first == __last)
     return;

   _Pointer __cur = __first;
   try
     {
       std::_Construct(std::__addressof(*__first),
         (*__seed));
       _Pointer __prev = __cur;
       ++__cur;
       for(; __cur != __last; ++__cur, ++__prev)
  std::_Construct(std::__addressof(*__cur),
    (*__prev));
       *__seed = (*__prev);
     }
   catch(...)
     {
       std::_Destroy(__first, __cur);
       throw;
     }
 }
    };

  template<>
    struct __uninitialized_construct_buf_dispatch<true>
    {
      template<typename _Pointer, typename _ForwardIterator>
        static void
        __ucr(_Pointer, _Pointer, _ForwardIterator) { }
    };
# 229 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_tempbuf.h" 3
  template<typename _Pointer, typename _ForwardIterator>
    inline void
    __uninitialized_construct_buf(_Pointer __first, _Pointer __last,
      _ForwardIterator __seed)
    {
      typedef typename std::iterator_traits<_Pointer>::value_type
 _ValueType;

      std::__uninitialized_construct_buf_dispatch<
        __has_trivial_constructor(_ValueType)>::
   __ucr(__first, __last, __seed);
    }

  template<typename _ForwardIterator, typename _Tp>
    _Temporary_buffer<_ForwardIterator, _Tp>::
    _Temporary_buffer(_ForwardIterator __first, _ForwardIterator __last)
    : _M_original_len(std::distance(__first, __last)),
      _M_len(0), _M_buffer(0)
    {
      try
 {
   std::pair<pointer, size_type> __p(std::get_temporary_buffer<
         value_type>(_M_original_len));
   _M_buffer = __p.first;
   _M_len = __p.second;
   if (_M_buffer)
     std::__uninitialized_construct_buf(_M_buffer, _M_buffer + _M_len,
            __first);
 }
      catch(...)
 {
   std::return_temporary_buffer(_M_buffer);
   _M_buffer = 0;
   _M_len = 0;
   throw;
 }
    }


}
# 63 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 2 3
# 71 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
namespace std
{



  template<typename _Iterator, typename _Compare>
    void
    __move_median_to_first(_Iterator __result,_Iterator __a, _Iterator __b,
      _Iterator __c, _Compare __comp)
    {
      if (__comp(__a, __b))
 {
   if (__comp(__b, __c))
     std::iter_swap(__result, __b);
   else if (__comp(__a, __c))
     std::iter_swap(__result, __c);
   else
     std::iter_swap(__result, __a);
 }
      else if (__comp(__a, __c))
 std::iter_swap(__result, __a);
      else if (__comp(__b, __c))
 std::iter_swap(__result, __c);
      else
 std::iter_swap(__result, __b);
    }


  template<typename _InputIterator, typename _Predicate>
    inline _InputIterator
    __find_if(_InputIterator __first, _InputIterator __last,
       _Predicate __pred, input_iterator_tag)
    {
      while (__first != __last && !__pred(__first))
 ++__first;
      return __first;
    }


  template<typename _RandomAccessIterator, typename _Predicate>
    _RandomAccessIterator
    __find_if(_RandomAccessIterator __first, _RandomAccessIterator __last,
       _Predicate __pred, random_access_iterator_tag)
    {
      typename iterator_traits<_RandomAccessIterator>::difference_type
 __trip_count = (__last - __first) >> 2;

      for (; __trip_count > 0; --__trip_count)
 {
   if (__pred(__first))
     return __first;
   ++__first;

   if (__pred(__first))
     return __first;
   ++__first;

   if (__pred(__first))
     return __first;
   ++__first;

   if (__pred(__first))
     return __first;
   ++__first;
 }

      switch (__last - __first)
 {
 case 3:
   if (__pred(__first))
     return __first;
   ++__first;
 case 2:
   if (__pred(__first))
     return __first;
   ++__first;
 case 1:
   if (__pred(__first))
     return __first;
   ++__first;
 case 0:
 default:
   return __last;
 }
    }

  template<typename _Iterator, typename _Predicate>
    inline _Iterator
    __find_if(_Iterator __first, _Iterator __last, _Predicate __pred)
    {
      return __find_if(__first, __last, __pred,
         std::__iterator_category(__first));
    }


  template<typename _InputIterator, typename _Predicate>
    inline _InputIterator
    __find_if_not(_InputIterator __first, _InputIterator __last,
    _Predicate __pred)
    {
      return std::__find_if(__first, __last,
       __gnu_cxx::__ops::__negate(__pred),
       std::__iterator_category(__first));
    }




  template<typename _InputIterator, typename _Predicate, typename _Distance>
    _InputIterator
    __find_if_not_n(_InputIterator __first, _Distance& __len, _Predicate __pred)
    {
      for (; __len; --__len, ++__first)
 if (!__pred(__first))
   break;
      return __first;
    }
# 202 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator1, typename _ForwardIterator2,
    typename _BinaryPredicate>
    _ForwardIterator1
    __search(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
      _ForwardIterator2 __first2, _ForwardIterator2 __last2,
      _BinaryPredicate __predicate)
    {

      if (__first1 == __last1 || __first2 == __last2)
 return __first1;


      _ForwardIterator2 __p1(__first2);
      if (++__p1 == __last2)
 return std::__find_if(__first1, __last1,
  __gnu_cxx::__ops::__iter_comp_iter(__predicate, __first2));


      _ForwardIterator2 __p;
      _ForwardIterator1 __current = __first1;

      for (;;)
 {
   __first1 =
     std::__find_if(__first1, __last1,
  __gnu_cxx::__ops::__iter_comp_iter(__predicate, __first2));

   if (__first1 == __last1)
     return __last1;

   __p = __p1;
   __current = __first1;
   if (++__current == __last1)
     return __last1;

   while (__predicate(__current, __p))
     {
       if (++__p == __last2)
  return __first1;
       if (++__current == __last1)
  return __last1;
     }
   ++__first1;
 }
      return __first1;
    }






  template<typename _ForwardIterator, typename _Integer,
    typename _UnaryPredicate>
    _ForwardIterator
    __search_n_aux(_ForwardIterator __first, _ForwardIterator __last,
     _Integer __count, _UnaryPredicate __unary_pred,
     std::forward_iterator_tag)
    {
      __first = std::__find_if(__first, __last, __unary_pred);
      while (__first != __last)
 {
   typename iterator_traits<_ForwardIterator>::difference_type
     __n = __count;
   _ForwardIterator __i = __first;
   ++__i;
   while (__i != __last && __n != 1 && __unary_pred(__i))
     {
       ++__i;
       --__n;
     }
   if (__n == 1)
     return __first;
   if (__i == __last)
     return __last;
   __first = std::__find_if(++__i, __last, __unary_pred);
 }
      return __last;
    }





  template<typename _RandomAccessIter, typename _Integer,
    typename _UnaryPredicate>
    _RandomAccessIter
    __search_n_aux(_RandomAccessIter __first, _RandomAccessIter __last,
     _Integer __count, _UnaryPredicate __unary_pred,
     std::random_access_iterator_tag)
    {
      typedef typename std::iterator_traits<_RandomAccessIter>::difference_type
 _DistanceType;

      _DistanceType __tailSize = __last - __first;
      _DistanceType __remainder = __count;

      while (__remainder <= __tailSize)
 {
   __first += __remainder;
   __tailSize -= __remainder;


   _RandomAccessIter __backTrack = __first;
   while (__unary_pred(--__backTrack))
     {
       if (--__remainder == 0)
         return (__first - __count);
     }
   __remainder = __count + 1 - (__first - __backTrack);
 }
      return __last;
    }

  template<typename _ForwardIterator, typename _Integer,
           typename _UnaryPredicate>
    _ForwardIterator
    __search_n(_ForwardIterator __first, _ForwardIterator __last,
        _Integer __count,
        _UnaryPredicate __unary_pred)
    {
      if (__count <= 0)
 return __first;

      if (__count == 1)
 return std::__find_if(__first, __last, __unary_pred);

      return std::__search_n_aux(__first, __last, __count, __unary_pred,
     std::__iterator_category(__first));
    }


  template<typename _ForwardIterator1, typename _ForwardIterator2,
    typename _BinaryPredicate>
    _ForwardIterator1
    __find_end(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
        _ForwardIterator2 __first2, _ForwardIterator2 __last2,
        forward_iterator_tag, forward_iterator_tag,
        _BinaryPredicate __comp)
    {
      if (__first2 == __last2)
 return __last1;

      _ForwardIterator1 __result = __last1;
      while (1)
 {
   _ForwardIterator1 __new_result
     = std::__search(__first1, __last1, __first2, __last2, __comp);
   if (__new_result == __last1)
     return __result;
   else
     {
       __result = __new_result;
       __first1 = __new_result;
       ++__first1;
     }
 }
    }


  template<typename _BidirectionalIterator1, typename _BidirectionalIterator2,
    typename _BinaryPredicate>
    _BidirectionalIterator1
    __find_end(_BidirectionalIterator1 __first1,
        _BidirectionalIterator1 __last1,
        _BidirectionalIterator2 __first2,
        _BidirectionalIterator2 __last2,
        bidirectional_iterator_tag, bidirectional_iterator_tag,
        _BinaryPredicate __comp)
    {

     

     


      typedef reverse_iterator<_BidirectionalIterator1> _RevIterator1;
      typedef reverse_iterator<_BidirectionalIterator2> _RevIterator2;

      _RevIterator1 __rlast1(__first1);
      _RevIterator2 __rlast2(__first2);
      _RevIterator1 __rresult = std::__search(_RevIterator1(__last1), __rlast1,
           _RevIterator2(__last2), __rlast2,
           __comp);

      if (__rresult == __rlast1)
 return __last1;
      else
 {
   _BidirectionalIterator1 __result = __rresult.base();
   std::advance(__result, -std::distance(__first2, __last2));
   return __result;
 }
    }
# 423 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator1, typename _ForwardIterator2>
    inline _ForwardIterator1
    find_end(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
      _ForwardIterator2 __first2, _ForwardIterator2 __last2)
    {

     
     
     


      ;
      ;

      return std::__find_end(__first1, __last1, __first2, __last2,
        std::__iterator_category(__first1),
        std::__iterator_category(__first2),
        __gnu_cxx::__ops::__iter_equal_to_iter());
    }
# 471 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator1, typename _ForwardIterator2,
    typename _BinaryPredicate>
    inline _ForwardIterator1
    find_end(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
      _ForwardIterator2 __first2, _ForwardIterator2 __last2,
      _BinaryPredicate __comp)
    {

     
     
     


      ;
      ;

      return std::__find_end(__first1, __last1, __first2, __last2,
        std::__iterator_category(__first1),
        std::__iterator_category(__first2),
        __gnu_cxx::__ops::__iter_comp_iter(__comp));
    }
# 636 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator, typename _OutputIterator,
    typename _Predicate>
    _OutputIterator
    __remove_copy_if(_InputIterator __first, _InputIterator __last,
       _OutputIterator __result, _Predicate __pred)
    {
      for (; __first != __last; ++__first)
 if (!__pred(__first))
   {
     *__result = *__first;
     ++__result;
   }
      return __result;
    }
# 665 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator, typename _OutputIterator, typename _Tp>
    inline _OutputIterator
    remove_copy(_InputIterator __first, _InputIterator __last,
  _OutputIterator __result, const _Tp& __value)
    {

     
     

     

      ;

      return std::__remove_copy_if(__first, __last, __result,
 __gnu_cxx::__ops::__iter_equals_val(__value));
    }
# 697 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator, typename _OutputIterator,
    typename _Predicate>
    inline _OutputIterator
    remove_copy_if(_InputIterator __first, _InputIterator __last,
     _OutputIterator __result, _Predicate __pred)
    {

     
     

     

      ;

      return std::__remove_copy_if(__first, __last, __result,
       __gnu_cxx::__ops::__pred_iter(__pred));
    }
# 855 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator, typename _Predicate>
    _ForwardIterator
    __remove_if(_ForwardIterator __first, _ForwardIterator __last,
  _Predicate __pred)
    {
      __first = std::__find_if(__first, __last, __pred);
      if (__first == __last)
        return __first;
      _ForwardIterator __result = __first;
      ++__first;
      for (; __first != __last; ++__first)
        if (!__pred(__first))
          {
            *__result = (*__first);
            ++__result;
          }
      return __result;
    }
# 891 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator, typename _Tp>
    inline _ForwardIterator
    remove(_ForwardIterator __first, _ForwardIterator __last,
    const _Tp& __value)
    {

     

     

      ;

      return std::__remove_if(__first, __last,
  __gnu_cxx::__ops::__iter_equals_val(__value));
    }
# 924 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator, typename _Predicate>
    inline _ForwardIterator
    remove_if(_ForwardIterator __first, _ForwardIterator __last,
       _Predicate __pred)
    {

     

     

      ;

      return std::__remove_if(__first, __last,
         __gnu_cxx::__ops::__pred_iter(__pred));
    }

  template<typename _ForwardIterator, typename _BinaryPredicate>
    _ForwardIterator
    __adjacent_find(_ForwardIterator __first, _ForwardIterator __last,
      _BinaryPredicate __binary_pred)
    {
      if (__first == __last)
 return __last;
      _ForwardIterator __next = __first;
      while (++__next != __last)
 {
   if (__binary_pred(__first, __next))
     return __first;
   __first = __next;
 }
      return __last;
    }

  template<typename _ForwardIterator, typename _BinaryPredicate>
    _ForwardIterator
    __unique(_ForwardIterator __first, _ForwardIterator __last,
      _BinaryPredicate __binary_pred)
    {

      __first = std::__adjacent_find(__first, __last, __binary_pred);
      if (__first == __last)
 return __last;


      _ForwardIterator __dest = __first;
      ++__first;
      while (++__first != __last)
 if (!__binary_pred(__dest, __first))
   *++__dest = (*__first);
      return ++__dest;
    }
# 990 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator>
    inline _ForwardIterator
    unique(_ForwardIterator __first, _ForwardIterator __last)
    {

     

     

      ;

      return std::__unique(__first, __last,
      __gnu_cxx::__ops::__iter_equal_to_iter());
    }
# 1020 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator, typename _BinaryPredicate>
    inline _ForwardIterator
    unique(_ForwardIterator __first, _ForwardIterator __last,
           _BinaryPredicate __binary_pred)
    {

     

     


      ;

      return std::__unique(__first, __last,
      __gnu_cxx::__ops::__iter_comp_iter(__binary_pred));
    }







  template<typename _ForwardIterator, typename _OutputIterator,
    typename _BinaryPredicate>
    _OutputIterator
    __unique_copy(_ForwardIterator __first, _ForwardIterator __last,
    _OutputIterator __result, _BinaryPredicate __binary_pred,
    forward_iterator_tag, output_iterator_tag)
    {

     



      _ForwardIterator __next = __first;
      *__result = *__first;
      while (++__next != __last)
 if (!__binary_pred(__first, __next))
   {
     __first = __next;
     *++__result = *__first;
   }
      return ++__result;
    }







  template<typename _InputIterator, typename _OutputIterator,
    typename _BinaryPredicate>
    _OutputIterator
    __unique_copy(_InputIterator __first, _InputIterator __last,
    _OutputIterator __result, _BinaryPredicate __binary_pred,
    input_iterator_tag, output_iterator_tag)
    {

     



      typename iterator_traits<_InputIterator>::value_type __value = *__first;
      __decltype(__gnu_cxx::__ops::__iter_comp_val(__binary_pred))
 __rebound_pred
 = __gnu_cxx::__ops::__iter_comp_val(__binary_pred);
      *__result = __value;
      while (++__first != __last)
 if (!__rebound_pred(__first, __value))
   {
     __value = *__first;
     *++__result = __value;
   }
      return ++__result;
    }







  template<typename _InputIterator, typename _ForwardIterator,
    typename _BinaryPredicate>
    _ForwardIterator
    __unique_copy(_InputIterator __first, _InputIterator __last,
    _ForwardIterator __result, _BinaryPredicate __binary_pred,
    input_iterator_tag, forward_iterator_tag)
    {

     


      *__result = *__first;
      while (++__first != __last)
 if (!__binary_pred(__result, __first))
   *++__result = *__first;
      return ++__result;
    }






  template<typename _BidirectionalIterator>
    void
    __reverse(_BidirectionalIterator __first, _BidirectionalIterator __last,
       bidirectional_iterator_tag)
    {
      while (true)
 if (__first == __last || __first == --__last)
   return;
 else
   {
     std::iter_swap(__first, __last);
     ++__first;
   }
    }






  template<typename _RandomAccessIterator>
    void
    __reverse(_RandomAccessIterator __first, _RandomAccessIterator __last,
       random_access_iterator_tag)
    {
      if (__first == __last)
 return;
      --__last;
      while (__first < __last)
 {
   std::iter_swap(__first, __last);
   ++__first;
   --__last;
 }
    }
# 1175 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _BidirectionalIterator>
    inline void
    reverse(_BidirectionalIterator __first, _BidirectionalIterator __last)
    {

     

      ;
      std::__reverse(__first, __last, std::__iterator_category(__first));
    }
# 1202 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _BidirectionalIterator, typename _OutputIterator>
    _OutputIterator
    reverse_copy(_BidirectionalIterator __first, _BidirectionalIterator __last,
   _OutputIterator __result)
    {

     

     

      ;

      while (__first != __last)
 {
   --__last;
   *__result = *__last;
   ++__result;
 }
      return __result;
    }





  template<typename _EuclideanRingElement>
    _EuclideanRingElement
    __gcd(_EuclideanRingElement __m, _EuclideanRingElement __n)
    {
      while (__n != 0)
 {
   _EuclideanRingElement __t = __m % __n;
   __m = __n;
   __n = __t;
 }
      return __m;
    }

  inline namespace _V2
  {


  template<typename _ForwardIterator>
    _ForwardIterator
    __rotate(_ForwardIterator __first,
      _ForwardIterator __middle,
      _ForwardIterator __last,
      forward_iterator_tag)
    {
      if (__first == __middle)
 return __last;
      else if (__last == __middle)
 return __first;

      _ForwardIterator __first2 = __middle;
      do
 {
   std::iter_swap(__first, __first2);
   ++__first;
   ++__first2;
   if (__first == __middle)
     __middle = __first2;
 }
      while (__first2 != __last);

      _ForwardIterator __ret = __first;

      __first2 = __middle;

      while (__first2 != __last)
 {
   std::iter_swap(__first, __first2);
   ++__first;
   ++__first2;
   if (__first == __middle)
     __middle = __first2;
   else if (__first2 == __last)
     __first2 = __middle;
 }
      return __ret;
    }


  template<typename _BidirectionalIterator>
    _BidirectionalIterator
    __rotate(_BidirectionalIterator __first,
      _BidirectionalIterator __middle,
      _BidirectionalIterator __last,
       bidirectional_iterator_tag)
    {

     


      if (__first == __middle)
 return __last;
      else if (__last == __middle)
 return __first;

      std::__reverse(__first, __middle, bidirectional_iterator_tag());
      std::__reverse(__middle, __last, bidirectional_iterator_tag());

      while (__first != __middle && __middle != __last)
 {
   std::iter_swap(__first, --__last);
   ++__first;
 }

      if (__first == __middle)
 {
   std::__reverse(__middle, __last, bidirectional_iterator_tag());
   return __last;
 }
      else
 {
   std::__reverse(__first, __middle, bidirectional_iterator_tag());
   return __first;
 }
    }


  template<typename _RandomAccessIterator>
    _RandomAccessIterator
    __rotate(_RandomAccessIterator __first,
      _RandomAccessIterator __middle,
      _RandomAccessIterator __last,
      random_access_iterator_tag)
    {

     


      if (__first == __middle)
 return __last;
      else if (__last == __middle)
 return __first;

      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
 _Distance;
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
 _ValueType;

      _Distance __n = __last - __first;
      _Distance __k = __middle - __first;

      if (__k == __n - __k)
 {
   std::swap_ranges(__first, __middle, __middle);
   return __middle;
 }

      _RandomAccessIterator __p = __first;
      _RandomAccessIterator __ret = __first + (__last - __middle);

      for (;;)
 {
   if (__k < __n - __k)
     {
       if (__is_pod(_ValueType) && __k == 1)
  {
    _ValueType __t = (*__p);
    std::copy(__p + 1, __p + __n, __p);
    *(__p + __n - 1) = (__t);
    return __ret;
  }
       _RandomAccessIterator __q = __p + __k;
       for (_Distance __i = 0; __i < __n - __k; ++ __i)
  {
    std::iter_swap(__p, __q);
    ++__p;
    ++__q;
  }
       __n %= __k;
       if (__n == 0)
  return __ret;
       std::swap(__n, __k);
       __k = __n - __k;
     }
   else
     {
       __k = __n - __k;
       if (__is_pod(_ValueType) && __k == 1)
  {
    _ValueType __t = (*(__p + __n - 1));
    std::copy_backward(__p, __p + __n - 1, __p + __n);
    *__p = (__t);
    return __ret;
  }
       _RandomAccessIterator __q = __p + __n;
       __p = __q - __k;
       for (_Distance __i = 0; __i < __n - __k; ++ __i)
  {
    --__p;
    --__q;
    std::iter_swap(__p, __q);
  }
       __n %= __k;
       if (__n == 0)
  return __ret;
       std::swap(__n, __k);
     }
 }
    }
# 1429 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator>
    inline _ForwardIterator
    rotate(_ForwardIterator __first, _ForwardIterator __middle,
    _ForwardIterator __last)
    {

     

      ;
      ;

      return std::__rotate(__first, __middle, __last,
      std::__iterator_category(__first));
    }

  }
# 1466 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator, typename _OutputIterator>
    inline _OutputIterator
    rotate_copy(_ForwardIterator __first, _ForwardIterator __middle,
                _ForwardIterator __last, _OutputIterator __result)
    {

     
     

      ;
      ;

      return std::copy(__first, __middle,
                       std::copy(__middle, __last, __result));
    }


  template<typename _ForwardIterator, typename _Predicate>
    _ForwardIterator
    __partition(_ForwardIterator __first, _ForwardIterator __last,
  _Predicate __pred, forward_iterator_tag)
    {
      if (__first == __last)
 return __first;

      while (__pred(*__first))
 if (++__first == __last)
   return __first;

      _ForwardIterator __next = __first;

      while (++__next != __last)
 if (__pred(*__next))
   {
     std::iter_swap(__first, __next);
     ++__first;
   }

      return __first;
    }


  template<typename _BidirectionalIterator, typename _Predicate>
    _BidirectionalIterator
    __partition(_BidirectionalIterator __first, _BidirectionalIterator __last,
  _Predicate __pred, bidirectional_iterator_tag)
    {
      while (true)
 {
   while (true)
     if (__first == __last)
       return __first;
     else if (__pred(*__first))
       ++__first;
     else
       break;
   --__last;
   while (true)
     if (__first == __last)
       return __first;
     else if (!bool(__pred(*__last)))
       --__last;
     else
       break;
   std::iter_swap(__first, __last);
   ++__first;
 }
    }
# 1543 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator, typename _Pointer, typename _Predicate,
    typename _Distance>
    _ForwardIterator
    __stable_partition_adaptive(_ForwardIterator __first,
    _ForwardIterator __last,
    _Predicate __pred, _Distance __len,
    _Pointer __buffer,
    _Distance __buffer_size)
    {
      if (__len == 1)
 return __first;

      if (__len <= __buffer_size)
 {
   _ForwardIterator __result1 = __first;
   _Pointer __result2 = __buffer;




   *__result2 = (*__first);
   ++__result2;
   ++__first;
   for (; __first != __last; ++__first)
     if (__pred(__first))
       {
  *__result1 = (*__first);
  ++__result1;
       }
     else
       {
  *__result2 = (*__first);
  ++__result2;
       }

   std::copy(__buffer, __result2, __result1);
   return __result1;
 }

      _ForwardIterator __middle = __first;
      std::advance(__middle, __len / 2);
      _ForwardIterator __left_split =
 std::__stable_partition_adaptive(__first, __middle, __pred,
      __len / 2, __buffer,
      __buffer_size);



      _Distance __right_len = __len - __len / 2;
      _ForwardIterator __right_split =
 std::__find_if_not_n(__middle, __right_len, __pred);

      if (__right_len)
 __right_split =
   std::__stable_partition_adaptive(__right_split, __last, __pred,
        __right_len,
        __buffer, __buffer_size);

      std::rotate(__left_split, __middle, __right_split);
      std::advance(__left_split, std::distance(__middle, __right_split));
      return __left_split;
    }

  template<typename _ForwardIterator, typename _Predicate>
    _ForwardIterator
    __stable_partition(_ForwardIterator __first, _ForwardIterator __last,
         _Predicate __pred)
    {
      __first = std::__find_if_not(__first, __last, __pred);

      if (__first == __last)
 return __first;

      typedef typename iterator_traits<_ForwardIterator>::value_type
 _ValueType;
      typedef typename iterator_traits<_ForwardIterator>::difference_type
 _DistanceType;

      _Temporary_buffer<_ForwardIterator, _ValueType> __buf(__first, __last);
      return
 std::__stable_partition_adaptive(__first, __last, __pred,
      _DistanceType(__buf.requested_size()),
      __buf.begin(),
      _DistanceType(__buf.size()));
    }
# 1646 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator, typename _Predicate>
    inline _ForwardIterator
    stable_partition(_ForwardIterator __first, _ForwardIterator __last,
       _Predicate __pred)
    {

     

     

      ;

      return std::__stable_partition(__first, __last,
         __gnu_cxx::__ops::__pred_iter(__pred));
    }


  template<typename _RandomAccessIterator, typename _Compare>
    void
    __heap_select(_RandomAccessIterator __first,
    _RandomAccessIterator __middle,
    _RandomAccessIterator __last, _Compare __comp)
    {
      std::__make_heap(__first, __middle, __comp);
      for (_RandomAccessIterator __i = __middle; __i < __last; ++__i)
 if (__comp(__i, __first))
   std::__pop_heap(__first, __middle, __i, __comp);
    }



  template<typename _InputIterator, typename _RandomAccessIterator,
    typename _Compare>
    _RandomAccessIterator
    __partial_sort_copy(_InputIterator __first, _InputIterator __last,
   _RandomAccessIterator __result_first,
   _RandomAccessIterator __result_last,
   _Compare __comp)
    {
      typedef typename iterator_traits<_InputIterator>::value_type
 _InputValueType;
      typedef iterator_traits<_RandomAccessIterator> _RItTraits;
      typedef typename _RItTraits::difference_type _DistanceType;

      if (__result_first == __result_last)
 return __result_last;
      _RandomAccessIterator __result_real_last = __result_first;
      while (__first != __last && __result_real_last != __result_last)
 {
   *__result_real_last = *__first;
   ++__result_real_last;
   ++__first;
 }

      std::__make_heap(__result_first, __result_real_last, __comp);
      while (__first != __last)
 {
   if (__comp(__first, __result_first))
     std::__adjust_heap(__result_first, _DistanceType(0),
          _DistanceType(__result_real_last
          - __result_first),
          _InputValueType(*__first), __comp);
   ++__first;
 }
      std::__sort_heap(__result_first, __result_real_last, __comp);
      return __result_real_last;
    }
# 1732 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator, typename _RandomAccessIterator>
    inline _RandomAccessIterator
    partial_sort_copy(_InputIterator __first, _InputIterator __last,
        _RandomAccessIterator __result_first,
        _RandomAccessIterator __result_last)
    {
      typedef typename iterator_traits<_InputIterator>::value_type
 _InputValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
 _OutputValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
 _DistanceType;


     
     

     

     
      ;
      ;

      return std::__partial_sort_copy(__first, __last,
          __result_first, __result_last,
          __gnu_cxx::__ops::__iter_less_iter());
    }
# 1780 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator, typename _RandomAccessIterator,
    typename _Compare>
    inline _RandomAccessIterator
    partial_sort_copy(_InputIterator __first, _InputIterator __last,
        _RandomAccessIterator __result_first,
        _RandomAccessIterator __result_last,
        _Compare __comp)
    {
      typedef typename iterator_traits<_InputIterator>::value_type
 _InputValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
 _OutputValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
 _DistanceType;


     
     

     

     

     

      ;
      ;

      return std::__partial_sort_copy(__first, __last,
          __result_first, __result_last,
    __gnu_cxx::__ops::__iter_comp_iter(__comp));
    }


  template<typename _RandomAccessIterator, typename _Compare>
    void
    __unguarded_linear_insert(_RandomAccessIterator __last,
         _Compare __comp)
    {
      typename iterator_traits<_RandomAccessIterator>::value_type
 __val = (*__last);
      _RandomAccessIterator __next = __last;
      --__next;
      while (__comp(__val, __next))
 {
   *__last = (*__next);
   __last = __next;
   --__next;
 }
      *__last = (__val);
    }


  template<typename _RandomAccessIterator, typename _Compare>
    void
    __insertion_sort(_RandomAccessIterator __first,
       _RandomAccessIterator __last, _Compare __comp)
    {
      if (__first == __last) return;

      for (_RandomAccessIterator __i = __first + 1; __i != __last; ++__i)
 {
   if (__comp(__i, __first))
     {
       typename iterator_traits<_RandomAccessIterator>::value_type
  __val = (*__i);
       std::copy_backward(__first, __i, __i + 1);
       *__first = (__val);
     }
   else
     std::__unguarded_linear_insert(__i,
    __gnu_cxx::__ops::__val_comp_iter(__comp));
 }
    }


  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    __unguarded_insertion_sort(_RandomAccessIterator __first,
          _RandomAccessIterator __last, _Compare __comp)
    {
      for (_RandomAccessIterator __i = __first; __i != __last; ++__i)
 std::__unguarded_linear_insert(__i,
    __gnu_cxx::__ops::__val_comp_iter(__comp));
    }





  enum { _S_threshold = 16 };


  template<typename _RandomAccessIterator, typename _Compare>
    void
    __final_insertion_sort(_RandomAccessIterator __first,
      _RandomAccessIterator __last, _Compare __comp)
    {
      if (__last - __first > int(_S_threshold))
 {
   std::__insertion_sort(__first, __first + int(_S_threshold), __comp);
   std::__unguarded_insertion_sort(__first + int(_S_threshold), __last,
       __comp);
 }
      else
 std::__insertion_sort(__first, __last, __comp);
    }


  template<typename _RandomAccessIterator, typename _Compare>
    _RandomAccessIterator
    __unguarded_partition(_RandomAccessIterator __first,
     _RandomAccessIterator __last,
     _RandomAccessIterator __pivot, _Compare __comp)
    {
      while (true)
 {
   while (__comp(__first, __pivot))
     ++__first;
   --__last;
   while (__comp(__pivot, __last))
     --__last;
   if (!(__first < __last))
     return __first;
   std::iter_swap(__first, __last);
   ++__first;
 }
    }


  template<typename _RandomAccessIterator, typename _Compare>
    inline _RandomAccessIterator
    __unguarded_partition_pivot(_RandomAccessIterator __first,
    _RandomAccessIterator __last, _Compare __comp)
    {
      _RandomAccessIterator __mid = __first + (__last - __first) / 2;
      std::__move_median_to_first(__first, __first + 1, __mid, __last - 1,
      __comp);
      return std::__unguarded_partition(__first + 1, __last, __first, __comp);
    }

  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    __partial_sort(_RandomAccessIterator __first,
     _RandomAccessIterator __middle,
     _RandomAccessIterator __last,
     _Compare __comp)
    {
      std::__heap_select(__first, __middle, __last, __comp);
      std::__sort_heap(__first, __middle, __comp);
    }


  template<typename _RandomAccessIterator, typename _Size, typename _Compare>
    void
    __introsort_loop(_RandomAccessIterator __first,
       _RandomAccessIterator __last,
       _Size __depth_limit, _Compare __comp)
    {
      while (__last - __first > int(_S_threshold))
 {
   if (__depth_limit == 0)
     {
       std::__partial_sort(__first, __last, __last, __comp);
       return;
     }
   --__depth_limit;
   _RandomAccessIterator __cut =
     std::__unguarded_partition_pivot(__first, __last, __comp);
   std::__introsort_loop(__cut, __last, __depth_limit, __comp);
   __last = __cut;
 }
    }



  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    __sort(_RandomAccessIterator __first, _RandomAccessIterator __last,
    _Compare __comp)
    {
      if (__first != __last)
 {
   std::__introsort_loop(__first, __last,
    std::__lg(__last - __first) * 2,
    __comp);
   std::__final_insertion_sort(__first, __last, __comp);
 }
    }

  template<typename _RandomAccessIterator, typename _Size, typename _Compare>
    void
    __introselect(_RandomAccessIterator __first, _RandomAccessIterator __nth,
    _RandomAccessIterator __last, _Size __depth_limit,
    _Compare __comp)
    {
      while (__last - __first > 3)
 {
   if (__depth_limit == 0)
     {
       std::__heap_select(__first, __nth + 1, __last, __comp);

       std::iter_swap(__first, __nth);
       return;
     }
   --__depth_limit;
   _RandomAccessIterator __cut =
     std::__unguarded_partition_pivot(__first, __last, __comp);
   if (__cut <= __nth)
     __first = __cut;
   else
     __last = __cut;
 }
      std::__insertion_sort(__first, __last, __comp);
    }
# 2016 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator, typename _Tp, typename _Compare>
    inline _ForwardIterator
    lower_bound(_ForwardIterator __first, _ForwardIterator __last,
  const _Tp& __val, _Compare __comp)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
 _ValueType;


     
     

     
                    ;

      return std::__lower_bound(__first, __last, __val,
    __gnu_cxx::__ops::__iter_comp_val(__comp));
    }

  template<typename _ForwardIterator, typename _Tp, typename _Compare>
    _ForwardIterator
    __upper_bound(_ForwardIterator __first, _ForwardIterator __last,
    const _Tp& __val, _Compare __comp)
    {
      typedef typename iterator_traits<_ForwardIterator>::difference_type
 _DistanceType;

      _DistanceType __len = std::distance(__first, __last);

      while (__len > 0)
 {
   _DistanceType __half = __len >> 1;
   _ForwardIterator __middle = __first;
   std::advance(__middle, __half);
   if (__comp(__val, __middle))
     __len = __half;
   else
     {
       __first = __middle;
       ++__first;
       __len = __len - __half - 1;
     }
 }
      return __first;
    }
# 2073 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator, typename _Tp>
    inline _ForwardIterator
    upper_bound(_ForwardIterator __first, _ForwardIterator __last,
  const _Tp& __val)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
 _ValueType;


     
     
      ;

      return std::__upper_bound(__first, __last, __val,
    __gnu_cxx::__ops::__val_less_iter());
    }
# 2105 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator, typename _Tp, typename _Compare>
    inline _ForwardIterator
    upper_bound(_ForwardIterator __first, _ForwardIterator __last,
  const _Tp& __val, _Compare __comp)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
 _ValueType;


     
     

     
                    ;

      return std::__upper_bound(__first, __last, __val,
    __gnu_cxx::__ops::__val_comp_iter(__comp));
    }

  template<typename _ForwardIterator, typename _Tp,
    typename _CompareItTp, typename _CompareTpIt>
    pair<_ForwardIterator, _ForwardIterator>
    __equal_range(_ForwardIterator __first, _ForwardIterator __last,
    const _Tp& __val,
    _CompareItTp __comp_it_val, _CompareTpIt __comp_val_it)
    {
      typedef typename iterator_traits<_ForwardIterator>::difference_type
 _DistanceType;

      _DistanceType __len = std::distance(__first, __last);

      while (__len > 0)
 {
   _DistanceType __half = __len >> 1;
   _ForwardIterator __middle = __first;
   std::advance(__middle, __half);
   if (__comp_it_val(__middle, __val))
     {
       __first = __middle;
       ++__first;
       __len = __len - __half - 1;
     }
   else if (__comp_val_it(__val, __middle))
     __len = __half;
   else
     {
       _ForwardIterator __left
  = std::__lower_bound(__first, __middle, __val, __comp_it_val);
       std::advance(__first, __len);
       _ForwardIterator __right
  = std::__upper_bound(++__middle, __first, __val, __comp_val_it);
       return pair<_ForwardIterator, _ForwardIterator>(__left, __right);
     }
 }
      return pair<_ForwardIterator, _ForwardIterator>(__first, __first);
    }
# 2179 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator, typename _Tp>
    inline pair<_ForwardIterator, _ForwardIterator>
    equal_range(_ForwardIterator __first, _ForwardIterator __last,
  const _Tp& __val)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
 _ValueType;


     
     
     
      ;
      ;

      return std::__equal_range(__first, __last, __val,
    __gnu_cxx::__ops::__iter_less_val(),
    __gnu_cxx::__ops::__val_less_iter());
    }
# 2216 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator, typename _Tp, typename _Compare>
    inline pair<_ForwardIterator, _ForwardIterator>
    equal_range(_ForwardIterator __first, _ForwardIterator __last,
  const _Tp& __val, _Compare __comp)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
 _ValueType;


     
     

     

     
                    ;
     
                    ;

      return std::__equal_range(__first, __last, __val,
    __gnu_cxx::__ops::__iter_comp_val(__comp),
    __gnu_cxx::__ops::__val_comp_iter(__comp));
    }
# 2252 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator, typename _Tp>
    bool
    binary_search(_ForwardIterator __first, _ForwardIterator __last,
                  const _Tp& __val)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
 _ValueType;


     
     
      ;
      ;

      _ForwardIterator __i
 = std::__lower_bound(__first, __last, __val,
        __gnu_cxx::__ops::__iter_less_val());
      return __i != __last && !(__val < *__i);
    }
# 2287 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator, typename _Tp, typename _Compare>
    bool
    binary_search(_ForwardIterator __first, _ForwardIterator __last,
                  const _Tp& __val, _Compare __comp)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
 _ValueType;


     
     

     
                    ;
     
                    ;

      _ForwardIterator __i
 = std::__lower_bound(__first, __last, __val,
        __gnu_cxx::__ops::__iter_comp_val(__comp));
      return __i != __last && !bool(__comp(__val, *__i));
    }




  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator, typename _Compare>
    void
    __move_merge_adaptive(_InputIterator1 __first1, _InputIterator1 __last1,
     _InputIterator2 __first2, _InputIterator2 __last2,
     _OutputIterator __result, _Compare __comp)
    {
      while (__first1 != __last1 && __first2 != __last2)
 {
   if (__comp(__first2, __first1))
     {
       *__result = (*__first2);
       ++__first2;
     }
   else
     {
       *__result = (*__first1);
       ++__first1;
     }
   ++__result;
 }
      if (__first1 != __last1)
 std::copy(__first1, __last1, __result);
    }


  template<typename _BidirectionalIterator1, typename _BidirectionalIterator2,
    typename _BidirectionalIterator3, typename _Compare>
    void
    __move_merge_adaptive_backward(_BidirectionalIterator1 __first1,
       _BidirectionalIterator1 __last1,
       _BidirectionalIterator2 __first2,
       _BidirectionalIterator2 __last2,
       _BidirectionalIterator3 __result,
       _Compare __comp)
    {
      if (__first1 == __last1)
 {
   std::copy_backward(__first2, __last2, __result);
   return;
 }
      else if (__first2 == __last2)
 return;

      --__last1;
      --__last2;
      while (true)
 {
   if (__comp(__last2, __last1))
     {
       *--__result = (*__last1);
       if (__first1 == __last1)
  {
    std::copy_backward(__first2, ++__last2, __result);
    return;
  }
       --__last1;
     }
   else
     {
       *--__result = (*__last2);
       if (__first2 == __last2)
  return;
       --__last2;
     }
 }
    }


  template<typename _BidirectionalIterator1, typename _BidirectionalIterator2,
    typename _Distance>
    _BidirectionalIterator1
    __rotate_adaptive(_BidirectionalIterator1 __first,
        _BidirectionalIterator1 __middle,
        _BidirectionalIterator1 __last,
        _Distance __len1, _Distance __len2,
        _BidirectionalIterator2 __buffer,
        _Distance __buffer_size)
    {
      _BidirectionalIterator2 __buffer_end;
      if (__len1 > __len2 && __len2 <= __buffer_size)
 {
   if (__len2)
     {
       __buffer_end = std::copy(__middle, __last, __buffer);
       std::copy_backward(__first, __middle, __last);
       return std::copy(__buffer, __buffer_end, __first);
     }
   else
     return __first;
 }
      else if (__len1 <= __buffer_size)
 {
   if (__len1)
     {
       __buffer_end = std::copy(__first, __middle, __buffer);
       std::copy(__middle, __last, __first);
       return std::copy_backward(__buffer, __buffer_end, __last);
     }
   else
     return __last;
 }
      else
 {
   std::rotate(__first, __middle, __last);
   std::advance(__first, std::distance(__middle, __last));
   return __first;
 }
    }


  template<typename _BidirectionalIterator, typename _Distance,
    typename _Pointer, typename _Compare>
    void
    __merge_adaptive(_BidirectionalIterator __first,
                     _BidirectionalIterator __middle,
       _BidirectionalIterator __last,
       _Distance __len1, _Distance __len2,
       _Pointer __buffer, _Distance __buffer_size,
       _Compare __comp)
    {
      if (__len1 <= __len2 && __len1 <= __buffer_size)
 {
   _Pointer __buffer_end = std::copy(__first, __middle, __buffer);
   std::__move_merge_adaptive(__buffer, __buffer_end, __middle, __last,
         __first, __comp);
 }
      else if (__len2 <= __buffer_size)
 {
   _Pointer __buffer_end = std::copy(__middle, __last, __buffer);
   std::__move_merge_adaptive_backward(__first, __middle, __buffer,
           __buffer_end, __last, __comp);
 }
      else
 {
   _BidirectionalIterator __first_cut = __first;
   _BidirectionalIterator __second_cut = __middle;
   _Distance __len11 = 0;
   _Distance __len22 = 0;
   if (__len1 > __len2)
     {
       __len11 = __len1 / 2;
       std::advance(__first_cut, __len11);
       __second_cut
  = std::__lower_bound(__middle, __last, *__first_cut,
         __gnu_cxx::__ops::__iter_comp_val(__comp));
       __len22 = std::distance(__middle, __second_cut);
     }
   else
     {
       __len22 = __len2 / 2;
       std::advance(__second_cut, __len22);
       __first_cut
  = std::__upper_bound(__first, __middle, *__second_cut,
         __gnu_cxx::__ops::__val_comp_iter(__comp));
       __len11 = std::distance(__first, __first_cut);
     }

   _BidirectionalIterator __new_middle
     = std::__rotate_adaptive(__first_cut, __middle, __second_cut,
         __len1 - __len11, __len22, __buffer,
         __buffer_size);
   std::__merge_adaptive(__first, __first_cut, __new_middle, __len11,
    __len22, __buffer, __buffer_size, __comp);
   std::__merge_adaptive(__new_middle, __second_cut, __last,
    __len1 - __len11,
    __len2 - __len22, __buffer,
    __buffer_size, __comp);
 }
    }


  template<typename _BidirectionalIterator, typename _Distance,
    typename _Compare>
    void
    __merge_without_buffer(_BidirectionalIterator __first,
                           _BidirectionalIterator __middle,
      _BidirectionalIterator __last,
      _Distance __len1, _Distance __len2,
      _Compare __comp)
    {
      if (__len1 == 0 || __len2 == 0)
 return;

      if (__len1 + __len2 == 2)
 {
   if (__comp(__middle, __first))
     std::iter_swap(__first, __middle);
   return;
 }

      _BidirectionalIterator __first_cut = __first;
      _BidirectionalIterator __second_cut = __middle;
      _Distance __len11 = 0;
      _Distance __len22 = 0;
      if (__len1 > __len2)
 {
   __len11 = __len1 / 2;
   std::advance(__first_cut, __len11);
   __second_cut
     = std::__lower_bound(__middle, __last, *__first_cut,
     __gnu_cxx::__ops::__iter_comp_val(__comp));
   __len22 = std::distance(__middle, __second_cut);
 }
      else
 {
   __len22 = __len2 / 2;
   std::advance(__second_cut, __len22);
   __first_cut
     = std::__upper_bound(__first, __middle, *__second_cut,
     __gnu_cxx::__ops::__val_comp_iter(__comp));
   __len11 = std::distance(__first, __first_cut);
 }

      std::rotate(__first_cut, __middle, __second_cut);
      _BidirectionalIterator __new_middle = __first_cut;
      std::advance(__new_middle, std::distance(__middle, __second_cut));
      std::__merge_without_buffer(__first, __first_cut, __new_middle,
      __len11, __len22, __comp);
      std::__merge_without_buffer(__new_middle, __second_cut, __last,
      __len1 - __len11, __len2 - __len22, __comp);
    }

  template<typename _BidirectionalIterator, typename _Compare>
    void
    __inplace_merge(_BidirectionalIterator __first,
      _BidirectionalIterator __middle,
      _BidirectionalIterator __last,
      _Compare __comp)
    {
      typedef typename iterator_traits<_BidirectionalIterator>::value_type
          _ValueType;
      typedef typename iterator_traits<_BidirectionalIterator>::difference_type
          _DistanceType;

      if (__first == __middle || __middle == __last)
 return;

      const _DistanceType __len1 = std::distance(__first, __middle);
      const _DistanceType __len2 = std::distance(__middle, __last);

      typedef _Temporary_buffer<_BidirectionalIterator, _ValueType> _TmpBuf;
      _TmpBuf __buf(__first, __last);

      if (__buf.begin() == 0)
 std::__merge_without_buffer
   (__first, __middle, __last, __len1, __len2, __comp);
      else
 std::__merge_adaptive
   (__first, __middle, __last, __len1, __len2, __buf.begin(),
    _DistanceType(__buf.size()), __comp);
    }
# 2584 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _BidirectionalIterator>
    inline void
    inplace_merge(_BidirectionalIterator __first,
    _BidirectionalIterator __middle,
    _BidirectionalIterator __last)
    {

     

     

      ;
      ;

      std::__inplace_merge(__first, __middle, __last,
      __gnu_cxx::__ops::__iter_less_iter());
    }
# 2624 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _BidirectionalIterator, typename _Compare>
    inline void
    inplace_merge(_BidirectionalIterator __first,
    _BidirectionalIterator __middle,
    _BidirectionalIterator __last,
    _Compare __comp)
    {

     

     


      ;
      ;

      std::__inplace_merge(__first, __middle, __last,
      __gnu_cxx::__ops::__iter_comp_iter(__comp));
    }



  template<typename _InputIterator, typename _OutputIterator,
    typename _Compare>
    _OutputIterator
    __move_merge(_InputIterator __first1, _InputIterator __last1,
   _InputIterator __first2, _InputIterator __last2,
   _OutputIterator __result, _Compare __comp)
    {
      while (__first1 != __last1 && __first2 != __last2)
 {
   if (__comp(__first2, __first1))
     {
       *__result = (*__first2);
       ++__first2;
     }
   else
     {
       *__result = (*__first1);
       ++__first1;
     }
   ++__result;
 }
      return std::copy(__first2, __last2, std::copy(__first1, __last1, __result))

                  ;
    }

  template<typename _RandomAccessIterator1, typename _RandomAccessIterator2,
    typename _Distance, typename _Compare>
    void
    __merge_sort_loop(_RandomAccessIterator1 __first,
        _RandomAccessIterator1 __last,
        _RandomAccessIterator2 __result, _Distance __step_size,
        _Compare __comp)
    {
      const _Distance __two_step = 2 * __step_size;

      while (__last - __first >= __two_step)
 {
   __result = std::__move_merge(__first, __first + __step_size,
           __first + __step_size,
           __first + __two_step,
           __result, __comp);
   __first += __two_step;
 }
      __step_size = std::min(_Distance(__last - __first), __step_size);

      std::__move_merge(__first, __first + __step_size,
   __first + __step_size, __last, __result, __comp);
    }

  template<typename _RandomAccessIterator, typename _Distance,
    typename _Compare>
    void
    __chunk_insertion_sort(_RandomAccessIterator __first,
      _RandomAccessIterator __last,
      _Distance __chunk_size, _Compare __comp)
    {
      while (__last - __first >= __chunk_size)
 {
   std::__insertion_sort(__first, __first + __chunk_size, __comp);
   __first += __chunk_size;
 }
      std::__insertion_sort(__first, __last, __comp);
    }

  enum { _S_chunk_size = 7 };

  template<typename _RandomAccessIterator, typename _Pointer, typename _Compare>
    void
    __merge_sort_with_buffer(_RandomAccessIterator __first,
        _RandomAccessIterator __last,
                             _Pointer __buffer, _Compare __comp)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
 _Distance;

      const _Distance __len = __last - __first;
      const _Pointer __buffer_last = __buffer + __len;

      _Distance __step_size = _S_chunk_size;
      std::__chunk_insertion_sort(__first, __last, __step_size, __comp);

      while (__step_size < __len)
 {
   std::__merge_sort_loop(__first, __last, __buffer,
     __step_size, __comp);
   __step_size *= 2;
   std::__merge_sort_loop(__buffer, __buffer_last, __first,
     __step_size, __comp);
   __step_size *= 2;
 }
    }

  template<typename _RandomAccessIterator, typename _Pointer,
    typename _Distance, typename _Compare>
    void
    __stable_sort_adaptive(_RandomAccessIterator __first,
      _RandomAccessIterator __last,
                           _Pointer __buffer, _Distance __buffer_size,
                           _Compare __comp)
    {
      const _Distance __len = (__last - __first + 1) / 2;
      const _RandomAccessIterator __middle = __first + __len;
      if (__len > __buffer_size)
 {
   std::__stable_sort_adaptive(__first, __middle, __buffer,
          __buffer_size, __comp);
   std::__stable_sort_adaptive(__middle, __last, __buffer,
          __buffer_size, __comp);
 }
      else
 {
   std::__merge_sort_with_buffer(__first, __middle, __buffer, __comp);
   std::__merge_sort_with_buffer(__middle, __last, __buffer, __comp);
 }
      std::__merge_adaptive(__first, __middle, __last,
       _Distance(__middle - __first),
       _Distance(__last - __middle),
       __buffer, __buffer_size,
       __comp);
    }


  template<typename _RandomAccessIterator, typename _Compare>
    void
    __inplace_stable_sort(_RandomAccessIterator __first,
     _RandomAccessIterator __last, _Compare __comp)
    {
      if (__last - __first < 15)
 {
   std::__insertion_sort(__first, __last, __comp);
   return;
 }
      _RandomAccessIterator __middle = __first + (__last - __first) / 2;
      std::__inplace_stable_sort(__first, __middle, __comp);
      std::__inplace_stable_sort(__middle, __last, __comp);
      std::__merge_without_buffer(__first, __middle, __last,
      __middle - __first,
      __last - __middle,
      __comp);
    }
# 2795 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator1, typename _InputIterator2,
    typename _Compare>
    bool
    __includes(_InputIterator1 __first1, _InputIterator1 __last1,
        _InputIterator2 __first2, _InputIterator2 __last2,
        _Compare __comp)
    {
      while (__first1 != __last1 && __first2 != __last2)
 if (__comp(__first2, __first1))
   return false;
 else if (__comp(__first1, __first2))
   ++__first1;
 else
   ++__first1, ++__first2;

      return __first2 == __last2;
    }
# 2831 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator1, typename _InputIterator2>
    inline bool
    includes(_InputIterator1 __first1, _InputIterator1 __last1,
      _InputIterator2 __first2, _InputIterator2 __last2)
    {

     
     
     


     


      ;
      ;

      return std::__includes(__first1, __last1, __first2, __last2,
        __gnu_cxx::__ops::__iter_less_iter());
    }
# 2873 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator1, typename _InputIterator2,
    typename _Compare>
    inline bool
    includes(_InputIterator1 __first1, _InputIterator1 __last1,
      _InputIterator2 __first2, _InputIterator2 __last2,
      _Compare __comp)
    {

     
     
     


     


      ;
      ;

      return std::__includes(__first1, __last1, __first2, __last2,
        __gnu_cxx::__ops::__iter_comp_iter(__comp));
    }
# 2906 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _BidirectionalIterator, typename _Compare>
    bool
    __next_permutation(_BidirectionalIterator __first,
         _BidirectionalIterator __last, _Compare __comp)
    {
      if (__first == __last)
 return false;
      _BidirectionalIterator __i = __first;
      ++__i;
      if (__i == __last)
 return false;
      __i = __last;
      --__i;

      for(;;)
 {
   _BidirectionalIterator __ii = __i;
   --__i;
   if (__comp(__i, __ii))
     {
       _BidirectionalIterator __j = __last;
       while (!__comp(__i, --__j))
  {}
       std::iter_swap(__i, __j);
       std::__reverse(__ii, __last,
        std::__iterator_category(__first));
       return true;
     }
   if (__i == __first)
     {
       std::__reverse(__first, __last,
        std::__iterator_category(__first));
       return false;
     }
 }
    }
# 2955 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _BidirectionalIterator>
    inline bool
    next_permutation(_BidirectionalIterator __first,
       _BidirectionalIterator __last)
    {

     

     

      ;

      return std::__next_permutation
 (__first, __last, __gnu_cxx::__ops::__iter_less_iter());
    }
# 2986 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _BidirectionalIterator, typename _Compare>
    inline bool
    next_permutation(_BidirectionalIterator __first,
       _BidirectionalIterator __last, _Compare __comp)
    {

     

     


      ;

      return std::__next_permutation
 (__first, __last, __gnu_cxx::__ops::__iter_comp_iter(__comp));
    }

  template<typename _BidirectionalIterator, typename _Compare>
    bool
    __prev_permutation(_BidirectionalIterator __first,
         _BidirectionalIterator __last, _Compare __comp)
    {
      if (__first == __last)
 return false;
      _BidirectionalIterator __i = __first;
      ++__i;
      if (__i == __last)
 return false;
      __i = __last;
      --__i;

      for(;;)
 {
   _BidirectionalIterator __ii = __i;
   --__i;
   if (__comp(__ii, __i))
     {
       _BidirectionalIterator __j = __last;
       while (!__comp(--__j, __i))
  {}
       std::iter_swap(__i, __j);
       std::__reverse(__ii, __last,
        std::__iterator_category(__first));
       return true;
     }
   if (__i == __first)
     {
       std::__reverse(__first, __last,
        std::__iterator_category(__first));
       return false;
     }
 }
    }
# 3053 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _BidirectionalIterator>
    inline bool
    prev_permutation(_BidirectionalIterator __first,
       _BidirectionalIterator __last)
    {

     

     

      ;

      return std::__prev_permutation(__first, __last,
         __gnu_cxx::__ops::__iter_less_iter());
    }
# 3084 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _BidirectionalIterator, typename _Compare>
    inline bool
    prev_permutation(_BidirectionalIterator __first,
       _BidirectionalIterator __last, _Compare __comp)
    {

     

     


      ;

      return std::__prev_permutation(__first, __last,
    __gnu_cxx::__ops::__iter_comp_iter(__comp));
    }




  template<typename _InputIterator, typename _OutputIterator,
    typename _Predicate, typename _Tp>
    _OutputIterator
    __replace_copy_if(_InputIterator __first, _InputIterator __last,
        _OutputIterator __result,
        _Predicate __pred, const _Tp& __new_value)
    {
      for (; __first != __last; ++__first, ++__result)
 if (__pred(__first))
   *__result = __new_value;
 else
   *__result = *__first;
      return __result;
    }
# 3133 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator, typename _OutputIterator, typename _Tp>
    inline _OutputIterator
    replace_copy(_InputIterator __first, _InputIterator __last,
   _OutputIterator __result,
   const _Tp& __old_value, const _Tp& __new_value)
    {

     
     

     

      ;

      return std::__replace_copy_if(__first, __last, __result,
   __gnu_cxx::__ops::__iter_equals_val(__old_value),
           __new_value);
    }
# 3167 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator, typename _OutputIterator,
    typename _Predicate, typename _Tp>
    inline _OutputIterator
    replace_copy_if(_InputIterator __first, _InputIterator __last,
      _OutputIterator __result,
      _Predicate __pred, const _Tp& __new_value)
    {

     
     

     

      ;

      return std::__replace_copy_if(__first, __last, __result,
    __gnu_cxx::__ops::__pred_iter(__pred),
           __new_value);
    }

  template<typename _InputIterator, typename _Predicate>
    typename iterator_traits<_InputIterator>::difference_type
    __count_if(_InputIterator __first, _InputIterator __last, _Predicate __pred)
    {
      typename iterator_traits<_InputIterator>::difference_type __n = 0;
      for (; __first != __last; ++__first)
 if (__pred(__first))
   ++__n;
      return __n;
    }
# 3743 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3



# 3759 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator, typename _Function>
    _Function
    for_each(_InputIterator __first, _InputIterator __last, _Function __f)
    {

     
      ;
      for (; __first != __last; ++__first)
 __f(*__first);
      return (__f);
    }
# 3780 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator, typename _Tp>
    inline _InputIterator
    find(_InputIterator __first, _InputIterator __last,
  const _Tp& __val)
    {

     
     

      ;
      return std::__find_if(__first, __last,
       __gnu_cxx::__ops::__iter_equals_val(__val));
    }
# 3804 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator, typename _Predicate>
    inline _InputIterator
    find_if(_InputIterator __first, _InputIterator __last,
     _Predicate __pred)
    {

     
     

      ;

      return std::__find_if(__first, __last,
       __gnu_cxx::__ops::__pred_iter(__pred));
    }
# 3835 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator, typename _ForwardIterator>
    _InputIterator
    find_first_of(_InputIterator __first1, _InputIterator __last1,
    _ForwardIterator __first2, _ForwardIterator __last2)
    {

     
     
     


      ;
      ;

      for (; __first1 != __last1; ++__first1)
 for (_ForwardIterator __iter = __first2; __iter != __last2; ++__iter)
   if (*__first1 == *__iter)
     return __first1;
      return __last1;
    }
# 3875 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator, typename _ForwardIterator,
    typename _BinaryPredicate>
    _InputIterator
    find_first_of(_InputIterator __first1, _InputIterator __last1,
    _ForwardIterator __first2, _ForwardIterator __last2,
    _BinaryPredicate __comp)
    {

     
     
     


      ;
      ;

      for (; __first1 != __last1; ++__first1)
 for (_ForwardIterator __iter = __first2; __iter != __last2; ++__iter)
   if (__comp(*__first1, *__iter))
     return __first1;
      return __last1;
    }
# 3907 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator>
    inline _ForwardIterator
    adjacent_find(_ForwardIterator __first, _ForwardIterator __last)
    {

     
     

      ;

      return std::__adjacent_find(__first, __last,
      __gnu_cxx::__ops::__iter_equal_to_iter());
    }
# 3932 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator, typename _BinaryPredicate>
    inline _ForwardIterator
    adjacent_find(_ForwardIterator __first, _ForwardIterator __last,
    _BinaryPredicate __binary_pred)
    {

     
     


      ;

      return std::__adjacent_find(__first, __last,
   __gnu_cxx::__ops::__iter_comp_iter(__binary_pred));
    }
# 3957 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator, typename _Tp>
    inline typename iterator_traits<_InputIterator>::difference_type
    count(_InputIterator __first, _InputIterator __last, const _Tp& __value)
    {

     
     

      ;

      return std::__count_if(__first, __last,
        __gnu_cxx::__ops::__iter_equals_val(__value));
    }
# 3980 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator, typename _Predicate>
    inline typename iterator_traits<_InputIterator>::difference_type
    count_if(_InputIterator __first, _InputIterator __last, _Predicate __pred)
    {

     
     

      ;

      return std::__count_if(__first, __last,
        __gnu_cxx::__ops::__pred_iter(__pred));
    }
# 4020 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator1, typename _ForwardIterator2>
    inline _ForwardIterator1
    search(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
    _ForwardIterator2 __first2, _ForwardIterator2 __last2)
    {

     
     
     


      ;
      ;

      return std::__search(__first1, __last1, __first2, __last2,
      __gnu_cxx::__ops::__iter_equal_to_iter());
    }
# 4059 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator1, typename _ForwardIterator2,
    typename _BinaryPredicate>
    inline _ForwardIterator1
    search(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
    _ForwardIterator2 __first2, _ForwardIterator2 __last2,
    _BinaryPredicate __predicate)
    {

     
     
     


      ;
      ;

      return std::__search(__first1, __last1, __first2, __last2,
      __gnu_cxx::__ops::__iter_comp_iter(__predicate));
    }
# 4094 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator, typename _Integer, typename _Tp>
    inline _ForwardIterator
    search_n(_ForwardIterator __first, _ForwardIterator __last,
      _Integer __count, const _Tp& __val)
    {

     
     

      ;

      return std::__search_n(__first, __last, __count,
        __gnu_cxx::__ops::__iter_equals_val(__val));
    }
# 4127 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator, typename _Integer, typename _Tp,
           typename _BinaryPredicate>
    inline _ForwardIterator
    search_n(_ForwardIterator __first, _ForwardIterator __last,
      _Integer __count, const _Tp& __val,
      _BinaryPredicate __binary_pred)
    {

     
     

      ;

      return std::__search_n(__first, __last, __count,
  __gnu_cxx::__ops::__iter_comp_val(__binary_pred, __val));
    }
# 4161 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator, typename _OutputIterator,
    typename _UnaryOperation>
    _OutputIterator
    transform(_InputIterator __first, _InputIterator __last,
       _OutputIterator __result, _UnaryOperation __unary_op)
    {

     
     


      ;

      for (; __first != __last; ++__first, ++__result)
 *__result = __unary_op(*__first);
      return __result;
    }
# 4198 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator, typename _BinaryOperation>
    _OutputIterator
    transform(_InputIterator1 __first1, _InputIterator1 __last1,
       _InputIterator2 __first2, _OutputIterator __result,
       _BinaryOperation __binary_op)
    {

     
     
     


      ;

      for (; __first1 != __last1; ++__first1, ++__first2, ++__result)
 *__result = __binary_op(*__first1, *__first2);
      return __result;
    }
# 4231 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator, typename _Tp>
    void
    replace(_ForwardIterator __first, _ForwardIterator __last,
     const _Tp& __old_value, const _Tp& __new_value)
    {

     

     

     

      ;

      for (; __first != __last; ++__first)
 if (*__first == __old_value)
   *__first = __new_value;
    }
# 4263 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator, typename _Predicate, typename _Tp>
    void
    replace_if(_ForwardIterator __first, _ForwardIterator __last,
        _Predicate __pred, const _Tp& __new_value)
    {

     

     

     

      ;

      for (; __first != __last; ++__first)
 if (__pred(*__first))
   *__first = __new_value;
    }
# 4295 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator, typename _Generator>
    void
    generate(_ForwardIterator __first, _ForwardIterator __last,
      _Generator __gen)
    {

     
     

      ;

      for (; __first != __last; ++__first)
 *__first = __gen();
    }
# 4326 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _OutputIterator, typename _Size, typename _Generator>
    _OutputIterator
    generate_n(_OutputIterator __first, _Size __n, _Generator __gen)
    {

     



      for (__decltype(__n + 0) __niter = __n;
    __niter > 0; --__niter, ++__first)
 *__first = __gen();
      return __first;
    }
# 4362 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator, typename _OutputIterator>
    inline _OutputIterator
    unique_copy(_InputIterator __first, _InputIterator __last,
  _OutputIterator __result)
    {

     
     

     

      ;

      if (__first == __last)
 return __result;
      return std::__unique_copy(__first, __last, __result,
    __gnu_cxx::__ops::__iter_equal_to_iter(),
    std::__iterator_category(__first),
    std::__iterator_category(__result));
    }
# 4402 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator, typename _OutputIterator,
    typename _BinaryPredicate>
    inline _OutputIterator
    unique_copy(_InputIterator __first, _InputIterator __last,
  _OutputIterator __result,
  _BinaryPredicate __binary_pred)
    {

     
     

      ;

      if (__first == __last)
 return __result;
      return std::__unique_copy(__first, __last, __result,
   __gnu_cxx::__ops::__iter_comp_iter(__binary_pred),
    std::__iterator_category(__first),
    std::__iterator_category(__result));
    }
# 4434 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _RandomAccessIterator>
    inline void
    random_shuffle(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {

     

      ;

      if (__first != __last)
 for (_RandomAccessIterator __i = __first + 1; __i != __last; ++__i)
   {

     _RandomAccessIterator __j = __first
     + std::rand() % ((__i - __first) + 1);
     if (__i != __j)
       std::iter_swap(__i, __j);
   }
    }
# 4468 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _RandomAccessIterator, typename _RandomNumberGenerator>
    void
    random_shuffle(_RandomAccessIterator __first, _RandomAccessIterator __last,



     _RandomNumberGenerator& __rand)

    {

     

      ;

      if (__first == __last)
 return;
      for (_RandomAccessIterator __i = __first + 1; __i != __last; ++__i)
 {
   _RandomAccessIterator __j = __first + __rand((__i - __first) + 1);
   if (__i != __j)
     std::iter_swap(__i, __j);
 }
    }
# 4508 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator, typename _Predicate>
    inline _ForwardIterator
    partition(_ForwardIterator __first, _ForwardIterator __last,
       _Predicate __pred)
    {

     

     

      ;

      return std::__partition(__first, __last, __pred,
         std::__iterator_category(__first));
    }
# 4541 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _RandomAccessIterator>
    inline void
    partial_sort(_RandomAccessIterator __first,
   _RandomAccessIterator __middle,
   _RandomAccessIterator __last)
    {

     

     

      ;
      ;

      std::__partial_sort(__first, __middle, __last,
     __gnu_cxx::__ops::__iter_less_iter());
    }
# 4578 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    partial_sort(_RandomAccessIterator __first,
   _RandomAccessIterator __middle,
   _RandomAccessIterator __last,
   _Compare __comp)
    {

     

     


      ;
      ;

      std::__partial_sort(__first, __middle, __last,
     __gnu_cxx::__ops::__iter_comp_iter(__comp));
    }
# 4613 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _RandomAccessIterator>
    inline void
    nth_element(_RandomAccessIterator __first, _RandomAccessIterator __nth,
  _RandomAccessIterator __last)
    {

     

     

      ;
      ;

      if (__first == __last || __nth == __last)
 return;

      std::__introselect(__first, __nth, __last,
    std::__lg(__last - __first) * 2,
    __gnu_cxx::__ops::__iter_less_iter());
    }
# 4651 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    nth_element(_RandomAccessIterator __first, _RandomAccessIterator __nth,
  _RandomAccessIterator __last, _Compare __comp)
    {

     

     


      ;
      ;

      if (__first == __last || __nth == __last)
 return;

      std::__introselect(__first, __nth, __last,
    std::__lg(__last - __first) * 2,
    __gnu_cxx::__ops::__iter_comp_iter(__comp));
    }
# 4687 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _RandomAccessIterator>
    inline void
    sort(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {

     

     

      ;

      std::__sort(__first, __last, __gnu_cxx::__ops::__iter_less_iter());
    }
# 4716 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    sort(_RandomAccessIterator __first, _RandomAccessIterator __last,
  _Compare __comp)
    {

     

     


      ;

      std::__sort(__first, __last, __gnu_cxx::__ops::__iter_comp_iter(__comp));
    }

  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator, typename _Compare>
    _OutputIterator
    __merge(_InputIterator1 __first1, _InputIterator1 __last1,
     _InputIterator2 __first2, _InputIterator2 __last2,
     _OutputIterator __result, _Compare __comp)
    {
      while (__first1 != __last1 && __first2 != __last2)
 {
   if (__comp(__first2, __first1))
     {
       *__result = *__first2;
       ++__first2;
     }
   else
     {
       *__result = *__first1;
       ++__first1;
     }
   ++__result;
 }
      return std::copy(__first2, __last2,
         std::copy(__first1, __last1, __result));
    }
# 4776 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator>
    inline _OutputIterator
    merge(_InputIterator1 __first1, _InputIterator1 __last1,
   _InputIterator2 __first2, _InputIterator2 __last2,
   _OutputIterator __result)
    {

     
     
     

     

     


      ;
      ;

      return std::__merge(__first1, __last1,
         __first2, __last2, __result,
         __gnu_cxx::__ops::__iter_less_iter());
    }
# 4824 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator, typename _Compare>
    inline _OutputIterator
    merge(_InputIterator1 __first1, _InputIterator1 __last1,
   _InputIterator2 __first2, _InputIterator2 __last2,
   _OutputIterator __result, _Compare __comp)
    {

     
     
     

     

     


      ;
      ;

      return std::__merge(__first1, __last1,
    __first2, __last2, __result,
    __gnu_cxx::__ops::__iter_comp_iter(__comp));
    }

  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    __stable_sort(_RandomAccessIterator __first, _RandomAccessIterator __last,
    _Compare __comp)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
 _ValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
 _DistanceType;

      typedef _Temporary_buffer<_RandomAccessIterator, _ValueType> _TmpBuf;
      _TmpBuf __buf(__first, __last);

      if (__buf.begin() == 0)
 std::__inplace_stable_sort(__first, __last, __comp);
      else
 std::__stable_sort_adaptive(__first, __last, __buf.begin(),
        _DistanceType(__buf.size()), __comp);
    }
# 4886 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _RandomAccessIterator>
    inline void
    stable_sort(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {

     

     

      ;

      std::__stable_sort(__first, __last,
        __gnu_cxx::__ops::__iter_less_iter());
    }
# 4919 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    stable_sort(_RandomAccessIterator __first, _RandomAccessIterator __last,
  _Compare __comp)
    {

     

     


      ;

      std::__stable_sort(__first, __last,
        __gnu_cxx::__ops::__iter_comp_iter(__comp));
    }

  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator,
    typename _Compare>
    _OutputIterator
    __set_union(_InputIterator1 __first1, _InputIterator1 __last1,
  _InputIterator2 __first2, _InputIterator2 __last2,
  _OutputIterator __result, _Compare __comp)
    {
      while (__first1 != __last1 && __first2 != __last2)
 {
   if (__comp(__first1, __first2))
     {
       *__result = *__first1;
       ++__first1;
     }
   else if (__comp(__first2, __first1))
     {
       *__result = *__first2;
       ++__first2;
     }
   else
     {
       *__result = *__first1;
       ++__first1;
       ++__first2;
     }
   ++__result;
 }
      return std::copy(__first2, __last2,
         std::copy(__first1, __last1, __result));
    }
# 4986 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator>
    inline _OutputIterator
    set_union(_InputIterator1 __first1, _InputIterator1 __last1,
       _InputIterator2 __first2, _InputIterator2 __last2,
       _OutputIterator __result)
    {

     
     
     

     

     


     


      ;
      ;

      return std::__set_union(__first1, __last1,
    __first2, __last2, __result,
    __gnu_cxx::__ops::__iter_less_iter());
    }
# 5033 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator, typename _Compare>
    inline _OutputIterator
    set_union(_InputIterator1 __first1, _InputIterator1 __last1,
       _InputIterator2 __first2, _InputIterator2 __last2,
       _OutputIterator __result, _Compare __comp)
    {

     
     
     

     

     


     


      ;
      ;

      return std::__set_union(__first1, __last1,
    __first2, __last2, __result,
    __gnu_cxx::__ops::__iter_comp_iter(__comp));
    }

  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator,
    typename _Compare>
    _OutputIterator
    __set_intersection(_InputIterator1 __first1, _InputIterator1 __last1,
         _InputIterator2 __first2, _InputIterator2 __last2,
         _OutputIterator __result, _Compare __comp)
    {
      while (__first1 != __last1 && __first2 != __last2)
 if (__comp(__first1, __first2))
   ++__first1;
 else if (__comp(__first2, __first1))
   ++__first2;
 else
   {
     *__result = *__first1;
     ++__first1;
     ++__first2;
     ++__result;
   }
      return __result;
    }
# 5101 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator>
    inline _OutputIterator
    set_intersection(_InputIterator1 __first1, _InputIterator1 __last1,
       _InputIterator2 __first2, _InputIterator2 __last2,
       _OutputIterator __result)
    {

     
     
     

     


     


      ;
      ;

      return std::__set_intersection(__first1, __last1,
         __first2, __last2, __result,
         __gnu_cxx::__ops::__iter_less_iter());
    }
# 5147 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator, typename _Compare>
    inline _OutputIterator
    set_intersection(_InputIterator1 __first1, _InputIterator1 __last1,
       _InputIterator2 __first2, _InputIterator2 __last2,
       _OutputIterator __result, _Compare __comp)
    {

     
     
     

     


     


      ;
      ;

      return std::__set_intersection(__first1, __last1,
    __first2, __last2, __result,
    __gnu_cxx::__ops::__iter_comp_iter(__comp));
    }

  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator,
    typename _Compare>
    _OutputIterator
    __set_difference(_InputIterator1 __first1, _InputIterator1 __last1,
       _InputIterator2 __first2, _InputIterator2 __last2,
       _OutputIterator __result, _Compare __comp)
    {
      while (__first1 != __last1 && __first2 != __last2)
 if (__comp(__first1, __first2))
   {
     *__result = *__first1;
     ++__first1;
     ++__result;
   }
 else if (__comp(__first2, __first1))
   ++__first2;
 else
   {
     ++__first1;
     ++__first2;
   }
      return std::copy(__first1, __last1, __result);
    }
# 5217 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator>
    inline _OutputIterator
    set_difference(_InputIterator1 __first1, _InputIterator1 __last1,
     _InputIterator2 __first2, _InputIterator2 __last2,
     _OutputIterator __result)
    {

     
     
     

     


     


      ;
      ;

      return std::__set_difference(__first1, __last1,
       __first2, __last2, __result,
       __gnu_cxx::__ops::__iter_less_iter());
    }
# 5265 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator, typename _Compare>
    inline _OutputIterator
    set_difference(_InputIterator1 __first1, _InputIterator1 __last1,
     _InputIterator2 __first2, _InputIterator2 __last2,
     _OutputIterator __result, _Compare __comp)
    {

     
     
     

     


     


      ;
      ;

      return std::__set_difference(__first1, __last1,
       __first2, __last2, __result,
       __gnu_cxx::__ops::__iter_comp_iter(__comp));
    }

  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator,
    typename _Compare>
    _OutputIterator
    __set_symmetric_difference(_InputIterator1 __first1,
          _InputIterator1 __last1,
          _InputIterator2 __first2,
          _InputIterator2 __last2,
          _OutputIterator __result,
          _Compare __comp)
    {
      while (__first1 != __last1 && __first2 != __last2)
 if (__comp(__first1, __first2))
   {
     *__result = *__first1;
     ++__first1;
     ++__result;
   }
 else if (__comp(__first2, __first1))
   {
     *__result = *__first2;
     ++__first2;
     ++__result;
   }
 else
   {
     ++__first1;
     ++__first2;
   }
      return std::copy(__first2, __last2,
         std::copy(__first1, __last1, __result));
    }
# 5341 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator>
    inline _OutputIterator
    set_symmetric_difference(_InputIterator1 __first1, _InputIterator1 __last1,
        _InputIterator2 __first2, _InputIterator2 __last2,
        _OutputIterator __result)
    {

     
     
     

     

     


     


      ;
      ;

      return std::__set_symmetric_difference(__first1, __last1,
     __first2, __last2, __result,
     __gnu_cxx::__ops::__iter_less_iter());
    }
# 5389 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator, typename _Compare>
    inline _OutputIterator
    set_symmetric_difference(_InputIterator1 __first1, _InputIterator1 __last1,
        _InputIterator2 __first2, _InputIterator2 __last2,
        _OutputIterator __result,
        _Compare __comp)
    {

     
     
     

     

     


     


      ;
      ;

      return std::__set_symmetric_difference(__first1, __last1,
    __first2, __last2, __result,
    __gnu_cxx::__ops::__iter_comp_iter(__comp));
    }

  template<typename _ForwardIterator, typename _Compare>
   
    _ForwardIterator
    __min_element(_ForwardIterator __first, _ForwardIterator __last,
    _Compare __comp)
    {
      if (__first == __last)
 return __first;
      _ForwardIterator __result = __first;
      while (++__first != __last)
 if (__comp(__first, __result))
   __result = __first;
      return __result;
    }
# 5440 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator>
   
    _ForwardIterator
    inline min_element(_ForwardIterator __first, _ForwardIterator __last)
    {

     
     

      ;

      return std::__min_element(__first, __last,
    __gnu_cxx::__ops::__iter_less_iter());
    }
# 5464 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator, typename _Compare>
   
    inline _ForwardIterator
    min_element(_ForwardIterator __first, _ForwardIterator __last,
  _Compare __comp)
    {

     
     


      ;

      return std::__min_element(__first, __last,
    __gnu_cxx::__ops::__iter_comp_iter(__comp));
    }

  template<typename _ForwardIterator, typename _Compare>
   
    _ForwardIterator
    __max_element(_ForwardIterator __first, _ForwardIterator __last,
    _Compare __comp)
    {
      if (__first == __last) return __first;
      _ForwardIterator __result = __first;
      while (++__first != __last)
 if (__comp(__result, __first))
   __result = __first;
      return __result;
    }
# 5502 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator>
   
    inline _ForwardIterator
    max_element(_ForwardIterator __first, _ForwardIterator __last)
    {

     
     

      ;

      return std::__max_element(__first, __last,
    __gnu_cxx::__ops::__iter_less_iter());
    }
# 5526 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_algo.h" 3
  template<typename _ForwardIterator, typename _Compare>
   
    inline _ForwardIterator
    max_element(_ForwardIterator __first, _ForwardIterator __last,
  _Compare __comp)
    {

     
     


      ;

      return std::__max_element(__first, __last,
    __gnu_cxx::__ops::__iter_comp_iter(__comp));
    }


}
# 63 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/algorithm" 2 3
# 5 "./util/sorted_uniform.hh" 2

# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 1 3
# 41 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 3
       
# 42 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 3

# 1 "/usr/include/assert.h" 1 3 4





extern "C" {
# 39 "/usr/include/assert.h" 3 4
void __attribute__((__cdecl__)) __assert (const char *, int, const char *) __attribute__ ((__noreturn__))
                                 ;
void __attribute__((__cdecl__)) __assert_func (const char *, int, const char *, const char *) __attribute__ ((__noreturn__))
                                 ;






}
# 43 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 2 3
# 7 "./util/sorted_uniform.hh" 2



# 9 "./util/sorted_uniform.hh"
namespace util {

template <class T> class IdentityAccessor {
  public:
    typedef T Key;
    T operator()(const T *in) const { return *in; }
};

struct Pivot64 {
  static inline std::size_t Calc(uint64_t off, uint64_t range, std::size_t width) {
    std::size_t ret = static_cast<std::size_t>(static_cast<float>(off) / static_cast<float>(range) * static_cast<float>(width));

    return (ret < width) ? ret : width - 1;
  }
};


struct Pivot32 {
  static inline std::size_t Calc(uint64_t off, uint64_t range, uint64_t width) {
    return static_cast<std::size_t>((off * width) / (range + 1));
  }
};


template <unsigned> struct PivotSelect;
template <> struct PivotSelect<8> { typedef Pivot64 T; };
template <> struct PivotSelect<4> { typedef Pivot32 T; };
template <> struct PivotSelect<2> { typedef Pivot32 T; };


template <class Iterator, class Accessor> bool BinaryFind(
    const Accessor &accessor,
    Iterator begin,
    Iterator end,
    const typename Accessor::Key key, Iterator &out) {
  while (end > begin) {
    Iterator pivot(begin + (end - begin) / 2);
    typename Accessor::Key mid(accessor(pivot));
    if (mid < key) {
      begin = pivot + 1;
    } else if (mid > key) {
      end = pivot;
    } else {
      out = pivot;
      return true;
    }
  }
  return false;
}






template <class Iterator, class Accessor, class Pivot> bool BoundedSortedUniformFind(
    const Accessor &accessor,
    Iterator before_it, typename Accessor::Key before_v,
    Iterator after_it, typename Accessor::Key after_v,
    const typename Accessor::Key key, Iterator &out) {
  while (after_it - before_it > 1) {
    Iterator pivot(before_it + (1 + Pivot::Calc(key - before_v, after_v - before_v, after_it - before_it - 1)));
    typename Accessor::Key mid(accessor(pivot));
    if (mid < key) {
      before_it = pivot;
      before_v = mid;
    } else if (mid > key) {
      after_it = pivot;
      after_v = mid;
    } else {
      out = pivot;
      return true;
    }
  }
  return false;
}

template <class Iterator, class Accessor, class Pivot> bool SortedUniformFind(const Accessor &accessor, Iterator begin, Iterator end, const typename Accessor::Key key, Iterator &out) {
  if (begin == end) return false;
  typename Accessor::Key below(accessor(begin));
  if (key <= below) {
    if (key == below) { out = begin; return true; }
    return false;
  }

  --end;
  typename Accessor::Key above(accessor(end));
  if (key >= above) {
    if (key == above) { out = end; return true; }
    return false;
  }
  return BoundedSortedUniformFind<Iterator, Accessor, Pivot>(accessor, begin, below, end, above, key, out);
}

}
# 20 "./lm/bhiksha.hh" 2



# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 1 3
# 41 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 3
       
# 42 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 3

# 1 "/usr/include/assert.h" 1 3 4






# 6 "/usr/include/assert.h" 3 4
extern "C" {
# 39 "/usr/include/assert.h" 3 4
void __attribute__((__cdecl__)) __assert (const char *, int, const char *) __attribute__ ((__noreturn__))
                                 ;
void __attribute__((__cdecl__)) __assert_func (const char *, int, const char *, const char *) __attribute__ ((__noreturn__))
                                 ;






}
# 43 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 2 3
# 24 "./lm/bhiksha.hh" 2


# 25 "./lm/bhiksha.hh"
namespace lm {
namespace ngram {
struct Config;
class BinaryFormat;

namespace trie {

class DontBhiksha {
  public:
    static const ModelType kModelTypeAdd = static_cast<ModelType>(0);

    static void UpdateConfigFromBinary(const BinaryFormat &, uint64_t, Config & ) {}

    static uint64_t Size(uint64_t , uint64_t , const Config & ) { return 0; }

    static uint8_t InlineBits(uint64_t , uint64_t max_next, const Config & ) {
      return util::RequiredBits(max_next);
    }

    DontBhiksha(const void *base, uint64_t max_offset, uint64_t max_next, const Config &config);

    void ReadNext(const void *base, uint64_t bit_offset, uint64_t , uint8_t total_bits, NodeRange &out) const {
      out.begin = util::ReadInt57(base, bit_offset, next_.bits, next_.mask);
      out.end = util::ReadInt57(base, bit_offset + total_bits, next_.bits, next_.mask);

    }

    void WriteNext(void *base, uint64_t bit_offset, uint64_t , uint64_t value) {
      util::WriteInt57(base, bit_offset, next_.bits, value);
    }

    void FinishedLoading(const Config & ) {}

    uint8_t InlineBits() const { return next_.bits; }

  private:
    util::BitsMask next_;
};

class ArrayBhiksha {
  public:
    static const ModelType kModelTypeAdd = kArrayAdd;

    static void UpdateConfigFromBinary(const BinaryFormat &file, uint64_t offset, Config &config);

    static uint64_t Size(uint64_t max_offset, uint64_t max_next, const Config &config);

    static uint8_t InlineBits(uint64_t max_offset, uint64_t max_next, const Config &config);

    ArrayBhiksha(void *base, uint64_t max_offset, uint64_t max_value, const Config &config);

    void ReadNext(const void *base, uint64_t bit_offset, uint64_t index, uint8_t total_bits, NodeRange &out) const {




      const uint64_t *begin_it = std::upper_bound(offset_begin_, offset_end_, index) - 1;


      const uint64_t *end_it;
      for (end_it = begin_it + 1; (end_it < offset_end_) && (*end_it <= index + 1); ++end_it) {}

      --end_it;

      out.begin = ((begin_it - offset_begin_) << next_inline_.bits) |
        util::ReadInt57(base, bit_offset, next_inline_.bits, next_inline_.mask);
      out.end = ((end_it - offset_begin_) << next_inline_.bits) |
        util::ReadInt57(base, bit_offset + total_bits, next_inline_.bits, next_inline_.mask);

      
# 94 "./lm/bhiksha.hh" 3 4
     ((
# 94 "./lm/bhiksha.hh"
     out.end >= out.begin
# 94 "./lm/bhiksha.hh" 3 4
     ) ? (void)0 : __assert_func ("./lm/bhiksha.hh", 94, __PRETTY_FUNCTION__, 
# 94 "./lm/bhiksha.hh"
     "out.end >= out.begin"
# 94 "./lm/bhiksha.hh" 3 4
     ))
# 94 "./lm/bhiksha.hh"
                                 ;
    }

    void WriteNext(void *base, uint64_t bit_offset, uint64_t index, uint64_t value) {
      uint64_t encode = value >> next_inline_.bits;
      for (; write_to_ <= offset_begin_ + encode; ++write_to_) *write_to_ = index;
      util::WriteInt57(base, bit_offset, next_inline_.bits, value & next_inline_.mask);
    }

    void FinishedLoading(const Config &config);

    uint8_t InlineBits() const { return next_inline_.bits; }

  private:
    const util::BitsMask next_inline_;

    const uint64_t *const offset_begin_;
    const uint64_t *const offset_end_;

    uint64_t *write_to_;

    void *original_base_;
};

}
}
}
# 5 "lm/model.hh" 2
# 1 "./lm/binary_format.hh" 1



# 1 "./lm/config.hh" 1



# 1 "./lm/lm_exception.hh" 1





# 1 "./util/exception.hh" 1



# 1 "./util/string_stream.hh" 1



# 1 "./util/fake_ostream.hh" 1



# 1 "./util/float_to_string.hh" 1




# 1 "./util/integer_to_string.hh" 1





namespace util {



char *ToString(uint32_t value, char *to);
char *ToString(uint64_t value, char *to);


char *ToString(int32_t value, char *to);
char *ToString(int64_t value, char *to);


char *ToString(uint16_t value, char *to);
char *ToString(int16_t value, char *to);

char *ToString(const void *value, char *to);

inline char *ToString(bool value, char *to) {
  *to++ = '0' + value;
  return to;
}





template <class T> struct ToStringBuf;
template <> struct ToStringBuf<bool> {
  enum { kBytes = 1 };
};
template <> struct ToStringBuf<uint16_t> {
  enum { kBytes = 5 };
};
template <> struct ToStringBuf<int16_t> {
  enum { kBytes = 6 };
};
template <> struct ToStringBuf<uint32_t> {
  enum { kBytes = 10 };
};
template <> struct ToStringBuf<int32_t> {
  enum { kBytes = 11 };
};
template <> struct ToStringBuf<uint64_t> {
  enum { kBytes = 20 };
};
template <> struct ToStringBuf<int64_t> {

  enum { kBytes = 20 };
};

template <> struct ToStringBuf<const void*> {

  enum { kBytes = sizeof(const void*) * 2 + 2 };
};


enum { kToStringMaxBytes = 20 };

}
# 6 "./util/float_to_string.hh" 2

namespace util {

template <> struct ToStringBuf<double> {

  static const unsigned kBytes = 19;
};



template <> struct ToStringBuf<float> {
  static const unsigned kBytes = 19;
};

char *ToString(double value, char *to);
char *ToString(float value, char *to);

}
# 5 "./util/fake_ostream.hh" 2

# 1 "./util/string_piece.hh" 1
# 51 "./util/string_piece.hh"
# 1 "./util/have.hh" 1
# 52 "./util/string_piece.hh" 2

# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstring" 1 3
# 39 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstring" 3
       
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstring" 3
# 54 "./util/string_piece.hh" 2
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/iosfwd" 1 3
# 36 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/iosfwd" 3
       
# 37 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/iosfwd" 3


# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stringfwd.h" 1 3
# 37 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stringfwd.h" 3
       
# 38 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stringfwd.h" 3





# 42 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stringfwd.h" 3
namespace std
{








  template<class _CharT>
    struct char_traits;

  template<> struct char_traits<char>;


  template<> struct char_traits<wchar_t>;
# 67 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stringfwd.h" 3


  template<typename _CharT, typename _Traits = char_traits<_CharT>,
           typename _Alloc = allocator<_CharT> >
    class basic_string;


  typedef basic_string<char> string;



  typedef basic_string<wchar_t> wstring;
# 90 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stringfwd.h" 3





}
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/iosfwd" 2 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/postypes.h" 1 3
# 38 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/postypes.h" 3
       
# 39 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/postypes.h" 3

# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cwchar" 1 3
# 39 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cwchar" 3
       
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cwchar" 3




# 1 "/usr/include/wchar.h" 1 3 4
# 12 "/usr/include/wchar.h" 3 4
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/stddef.h" 1 3 4
# 13 "/usr/include/wchar.h" 2 3 4
# 22 "/usr/include/wchar.h" 3 4
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/stdarg.h" 1 3 4
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 23 "/usr/include/wchar.h" 2 3 4





typedef __gnuc_va_list va_list;
# 70 "/usr/include/wchar.h" 3 4
extern "C" {




typedef __FILE FILE;






struct tm;



typedef _mbstate_t mbstate_t;


wint_t __attribute__((__cdecl__)) btowc (int);
int __attribute__((__cdecl__)) wctob (wint_t);
size_t __attribute__((__cdecl__)) mbrlen (const char *, size_t, mbstate_t *);
size_t __attribute__((__cdecl__)) mbrtowc (wchar_t *, const char *, size_t, mbstate_t *)
                             ;
size_t __attribute__((__cdecl__)) _mbrtowc_r (struct _reent *, wchar_t * , const char * , size_t, mbstate_t *)
                        ;
int __attribute__((__cdecl__)) mbsinit (const mbstate_t *);

size_t __attribute__((__cdecl__)) mbsnrtowcs (wchar_t *, const char **, size_t, size_t, mbstate_t *)
                                           ;

size_t __attribute__((__cdecl__)) _mbsnrtowcs_r (struct _reent *, wchar_t * , const char ** , size_t, size_t, mbstate_t *)
                                ;
size_t __attribute__((__cdecl__)) mbsrtowcs (wchar_t *, const char **, size_t, mbstate_t *)
                           ;
size_t __attribute__((__cdecl__)) _mbsrtowcs_r (struct _reent *, wchar_t * , const char ** , size_t, mbstate_t *);
size_t __attribute__((__cdecl__)) wcrtomb (char *, wchar_t, mbstate_t *);
size_t __attribute__((__cdecl__)) _wcrtomb_r (struct _reent *, char * , wchar_t, mbstate_t *);

size_t __attribute__((__cdecl__)) wcsnrtombs (char *, const wchar_t **, size_t, size_t, mbstate_t *)
                                           ;

size_t __attribute__((__cdecl__)) _wcsnrtombs_r (struct _reent *, char * , const wchar_t ** , size_t, size_t, mbstate_t *)
                                ;
size_t __attribute__((__cdecl__)) wcsrtombs (char *, const wchar_t **, size_t, mbstate_t *)
                                   ;
size_t __attribute__((__cdecl__)) _wcsrtombs_r (struct _reent *, char * , const wchar_t ** , size_t, mbstate_t *)
                        ;

int __attribute__((__cdecl__)) wcscasecmp (const wchar_t *, const wchar_t *);

wchar_t *__attribute__((__cdecl__)) wcscat (wchar_t *, const wchar_t *);
wchar_t *__attribute__((__cdecl__)) wcschr (const wchar_t *, wchar_t);
int __attribute__((__cdecl__)) wcscmp (const wchar_t *, const wchar_t *);
int __attribute__((__cdecl__)) wcscoll (const wchar_t *, const wchar_t *);
wchar_t *__attribute__((__cdecl__)) wcscpy (wchar_t *, const wchar_t *);

wchar_t *__attribute__((__cdecl__)) wcpcpy (wchar_t *, const wchar_t *)
                                ;
wchar_t *__attribute__((__cdecl__)) wcsdup (const wchar_t *);

wchar_t *__attribute__((__cdecl__)) _wcsdup_r (struct _reent *, const wchar_t * );
size_t __attribute__((__cdecl__)) wcscspn (const wchar_t *, const wchar_t *);
size_t __attribute__((__cdecl__)) wcsftime (wchar_t *, size_t, const wchar_t *, const struct tm *)
                                                            ;




size_t __attribute__((__cdecl__)) wcslcat (wchar_t *, const wchar_t *, size_t);
size_t __attribute__((__cdecl__)) wcslcpy (wchar_t *, const wchar_t *, size_t);
size_t __attribute__((__cdecl__)) wcslen (const wchar_t *);

int __attribute__((__cdecl__)) wcsncasecmp (const wchar_t *, const wchar_t *, size_t);

wchar_t *__attribute__((__cdecl__)) wcsncat (wchar_t *, const wchar_t *, size_t)
                                        ;
int __attribute__((__cdecl__)) wcsncmp (const wchar_t *, const wchar_t *, size_t);
wchar_t *__attribute__((__cdecl__)) wcsncpy (wchar_t *, const wchar_t *, size_t)
                                        ;

wchar_t *__attribute__((__cdecl__)) wcpncpy (wchar_t *, const wchar_t *, size_t)
                                        ;
size_t __attribute__((__cdecl__)) wcsnlen (const wchar_t *, size_t);

wchar_t *__attribute__((__cdecl__)) wcspbrk (const wchar_t *, const wchar_t *);
wchar_t *__attribute__((__cdecl__)) wcsrchr (const wchar_t *, wchar_t);
size_t __attribute__((__cdecl__)) wcsspn (const wchar_t *, const wchar_t *);
wchar_t *__attribute__((__cdecl__)) wcsstr (const wchar_t *, const wchar_t *)
                                ;
wchar_t *__attribute__((__cdecl__)) wcstok (wchar_t *, const wchar_t *, wchar_t **)
                           ;
double __attribute__((__cdecl__)) wcstod (const wchar_t *, wchar_t **);
double __attribute__((__cdecl__)) _wcstod_r (struct _reent *, const wchar_t *, wchar_t **);

float __attribute__((__cdecl__)) wcstof (const wchar_t *, wchar_t **);

float __attribute__((__cdecl__)) _wcstof_r (struct _reent *, const wchar_t *, wchar_t **);



size_t __attribute__((__cdecl__)) wcsxfrm (wchar_t *, const wchar_t *, size_t)
            ;

extern int wcscasecmp_l (const wchar_t *, const wchar_t *, locale_t);
extern int wcsncasecmp_l (const wchar_t *, const wchar_t *, size_t, locale_t);
extern int wcscoll_l (const wchar_t *, const wchar_t *, locale_t);
extern size_t wcsxfrm_l (wchar_t *, const wchar_t *, size_t,
    locale_t);





wchar_t *__attribute__((__cdecl__)) wmemchr (const wchar_t *, wchar_t, size_t);
int __attribute__((__cdecl__)) wmemcmp (const wchar_t *, const wchar_t *, size_t);
wchar_t *__attribute__((__cdecl__)) wmemcpy (wchar_t *, const wchar_t *, size_t)
             ;
wchar_t *__attribute__((__cdecl__)) wmemmove (wchar_t *, const wchar_t *, size_t);
wchar_t *__attribute__((__cdecl__)) wmemset (wchar_t *, wchar_t, size_t);

long __attribute__((__cdecl__)) wcstol (const wchar_t *, wchar_t **, int);

long long __attribute__((__cdecl__)) wcstoll (const wchar_t *, wchar_t **, int)
           ;

unsigned long __attribute__((__cdecl__)) wcstoul (const wchar_t *, wchar_t **, int)
            ;

unsigned long long __attribute__((__cdecl__)) wcstoull (const wchar_t *, wchar_t **, int)
                                    ;

long __attribute__((__cdecl__)) _wcstol_r (struct _reent *, const wchar_t *, wchar_t **, int);
long long __attribute__((__cdecl__)) _wcstoll_r (struct _reent *, const wchar_t *, wchar_t **, int);
unsigned long __attribute__((__cdecl__)) _wcstoul_r (struct _reent *, const wchar_t *, wchar_t **, int);
unsigned long long __attribute__((__cdecl__)) _wcstoull_r (struct _reent *, const wchar_t *, wchar_t **, int);

long double __attribute__((__cdecl__)) wcstold (const wchar_t *, wchar_t **);
# 223 "/usr/include/wchar.h" 3 4
wint_t __attribute__((__cdecl__)) fgetwc (__FILE *);
wchar_t *__attribute__((__cdecl__)) fgetws (wchar_t *, int, __FILE *);
wint_t __attribute__((__cdecl__)) fputwc (wchar_t, __FILE *);
int __attribute__((__cdecl__)) fputws (const wchar_t *, __FILE *);

int __attribute__((__cdecl__)) fwide (__FILE *, int);

wint_t __attribute__((__cdecl__)) getwc (__FILE *);
wint_t __attribute__((__cdecl__)) getwchar (void);
wint_t __attribute__((__cdecl__)) putwc (wchar_t, __FILE *);
wint_t __attribute__((__cdecl__)) putwchar (wchar_t);
wint_t __attribute__((__cdecl__)) ungetwc (wint_t wc, __FILE *);

wint_t __attribute__((__cdecl__)) _fgetwc_r (struct _reent *, __FILE *);
wint_t __attribute__((__cdecl__)) _fgetwc_unlocked_r (struct _reent *, __FILE *);
wchar_t *__attribute__((__cdecl__)) _fgetws_r (struct _reent *, wchar_t *, int, __FILE *);
wchar_t *__attribute__((__cdecl__)) _fgetws_unlocked_r (struct _reent *, wchar_t *, int, __FILE *);
wint_t __attribute__((__cdecl__)) _fputwc_r (struct _reent *, wchar_t, __FILE *);
wint_t __attribute__((__cdecl__)) _fputwc_unlocked_r (struct _reent *, wchar_t, __FILE *);
int __attribute__((__cdecl__)) _fputws_r (struct _reent *, const wchar_t *, __FILE *);
int __attribute__((__cdecl__)) _fputws_unlocked_r (struct _reent *, const wchar_t *, __FILE *);
int __attribute__((__cdecl__)) _fwide_r (struct _reent *, __FILE *, int);
wint_t __attribute__((__cdecl__)) _getwc_r (struct _reent *, __FILE *);
wint_t __attribute__((__cdecl__)) _getwc_unlocked_r (struct _reent *, __FILE *);
wint_t __attribute__((__cdecl__)) _getwchar_r (struct _reent *ptr);
wint_t __attribute__((__cdecl__)) _getwchar_unlocked_r (struct _reent *ptr);
wint_t __attribute__((__cdecl__)) _putwc_r (struct _reent *, wchar_t, __FILE *);
wint_t __attribute__((__cdecl__)) _putwc_unlocked_r (struct _reent *, wchar_t, __FILE *);
wint_t __attribute__((__cdecl__)) _putwchar_r (struct _reent *, wchar_t);
wint_t __attribute__((__cdecl__)) _putwchar_unlocked_r (struct _reent *, wchar_t);
wint_t __attribute__((__cdecl__)) _ungetwc_r (struct _reent *, wint_t wc, __FILE *);
# 267 "/usr/include/wchar.h" 3 4
__FILE *__attribute__((__cdecl__)) open_wmemstream (wchar_t **, size_t *);

__FILE *__attribute__((__cdecl__)) _open_wmemstream_r (struct _reent *, wchar_t **, size_t *);
# 280 "/usr/include/wchar.h" 3 4
int __attribute__((__cdecl__)) fwprintf (__FILE *, const wchar_t *, ...);
int __attribute__((__cdecl__)) swprintf (wchar_t *, size_t, const wchar_t *, ...)
                                   ;
int __attribute__((__cdecl__)) vfwprintf (__FILE *, const wchar_t *, __gnuc_va_list)
             ;
int __attribute__((__cdecl__)) vswprintf (wchar_t *, size_t, const wchar_t *, __gnuc_va_list)
                                        ;
int __attribute__((__cdecl__)) vwprintf (const wchar_t *, __gnuc_va_list);
int __attribute__((__cdecl__)) wprintf (const wchar_t *, ...);


int __attribute__((__cdecl__)) _fwprintf_r (struct _reent *, __FILE *, const wchar_t *, ...);
int __attribute__((__cdecl__)) _swprintf_r (struct _reent *, wchar_t *, size_t, const wchar_t *, ...);
int __attribute__((__cdecl__)) _vfwprintf_r (struct _reent *, __FILE *, const wchar_t *, __gnuc_va_list);
int __attribute__((__cdecl__)) _vswprintf_r (struct _reent *, wchar_t *, size_t, const wchar_t *, __gnuc_va_list);
int __attribute__((__cdecl__)) _vwprintf_r (struct _reent *, const wchar_t *, __gnuc_va_list);
int __attribute__((__cdecl__)) _wprintf_r (struct _reent *, const wchar_t *, ...);


int __attribute__((__cdecl__)) fwscanf (__FILE *, const wchar_t *, ...);
int __attribute__((__cdecl__)) swscanf (const wchar_t *, const wchar_t *, ...)
                                   ;
int __attribute__((__cdecl__)) vfwscanf (__FILE *, const wchar_t *, __gnuc_va_list)
             ;
int __attribute__((__cdecl__)) vswscanf (const wchar_t *, const wchar_t *, __gnuc_va_list)
             ;
int __attribute__((__cdecl__)) vwscanf (const wchar_t *, __gnuc_va_list);
int __attribute__((__cdecl__)) wscanf (const wchar_t *, ...);


int __attribute__((__cdecl__)) _fwscanf_r (struct _reent *, __FILE *, const wchar_t *, ...);
int __attribute__((__cdecl__)) _swscanf_r (struct _reent *, const wchar_t *, const wchar_t *, ...);
int __attribute__((__cdecl__)) _vfwscanf_r (struct _reent *, __FILE *, const wchar_t *, __gnuc_va_list);
int __attribute__((__cdecl__)) _vswscanf_r (struct _reent *, const wchar_t *, const wchar_t *, __gnuc_va_list);
int __attribute__((__cdecl__)) _vwscanf_r (struct _reent *, const wchar_t *, __gnuc_va_list);
int __attribute__((__cdecl__)) _wscanf_r (struct _reent *, const wchar_t *, ...);
# 329 "/usr/include/wchar.h" 3 4
}
# 45 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cwchar" 2 3
# 62 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cwchar" 3
namespace std
{
  using ::mbstate_t;
}
# 135 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cwchar" 3
namespace std
{


  using ::wint_t;

  using ::btowc;
  using ::fgetwc;
  using ::fgetws;
  using ::fputwc;
  using ::fputws;
  using ::fwide;
  using ::fwprintf;
  using ::fwscanf;
  using ::getwc;
  using ::getwchar;
  using ::mbrlen;
  using ::mbrtowc;
  using ::mbsinit;
  using ::mbsrtowcs;
  using ::putwc;
  using ::putwchar;

  using ::swprintf;

  using ::swscanf;
  using ::ungetwc;
  using ::vfwprintf;

  using ::vfwscanf;


  using ::vswprintf;


  using ::vswscanf;

  using ::vwprintf;

  using ::vwscanf;

  using ::wcrtomb;
  using ::wcscat;
  using ::wcscmp;
  using ::wcscoll;
  using ::wcscpy;
  using ::wcscspn;
  using ::wcsftime;
  using ::wcslen;
  using ::wcsncat;
  using ::wcsncmp;
  using ::wcsncpy;
  using ::wcsrtombs;
  using ::wcsspn;
  using ::wcstod;

  using ::wcstof;

  using ::wcstok;
  using ::wcstol;
  using ::wcstoul;
  using ::wcsxfrm;
  using ::wctob;
  using ::wmemcmp;
  using ::wmemcpy;
  using ::wmemmove;
  using ::wmemset;
  using ::wprintf;
  using ::wscanf;
  using ::wcschr;
  using ::wcspbrk;
  using ::wcsrchr;
  using ::wcsstr;
  using ::wmemchr;


  inline wchar_t*
  wcschr(wchar_t* __p, wchar_t __c)
  { return wcschr(const_cast<const wchar_t*>(__p), __c); }

  inline wchar_t*
  wcspbrk(wchar_t* __s1, const wchar_t* __s2)
  { return wcspbrk(const_cast<const wchar_t*>(__s1), __s2); }

  inline wchar_t*
  wcsrchr(wchar_t* __p, wchar_t __c)
  { return wcsrchr(const_cast<const wchar_t*>(__p), __c); }

  inline wchar_t*
  wcsstr(wchar_t* __s1, const wchar_t* __s2)
  { return wcsstr(const_cast<const wchar_t*>(__s1), __s2); }

  inline wchar_t*
  wmemchr(wchar_t* __p, wchar_t __c, size_t __n)
  { return wmemchr(const_cast<const wchar_t*>(__p), __c, __n); }



}







namespace __gnu_cxx
{





  using ::wcstold;
# 257 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cwchar" 3
  using ::wcstoll;
  using ::wcstoull;

}

namespace std
{
  using ::__gnu_cxx::wcstold;
  using ::__gnu_cxx::wcstoll;
  using ::__gnu_cxx::wcstoull;
}
# 41 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/postypes.h" 2 3
# 68 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/postypes.h" 3
namespace std
{

# 88 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/postypes.h" 3
  typedef long streamoff;
# 98 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/postypes.h" 3
  typedef ptrdiff_t streamsize;
# 111 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/postypes.h" 3
  template<typename _StateT>
    class fpos
    {
    private:
      streamoff _M_off;
      _StateT _M_state;

    public:




      fpos()
      : _M_off(0), _M_state() { }
# 133 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/postypes.h" 3
      fpos(streamoff __off)
      : _M_off(__off), _M_state() { }


      operator streamoff() const { return _M_off; }


      void
      state(_StateT __st)
      { _M_state = __st; }


      _StateT
      state() const
      { return _M_state; }





      fpos&
      operator+=(streamoff __off)
      {
 _M_off += __off;
 return *this;
      }





      fpos&
      operator-=(streamoff __off)
      {
 _M_off -= __off;
 return *this;
      }







      fpos
      operator+(streamoff __off) const
      {
 fpos __pos(*this);
 __pos += __off;
 return __pos;
      }







      fpos
      operator-(streamoff __off) const
      {
 fpos __pos(*this);
 __pos -= __off;
 return __pos;
      }






      streamoff
      operator-(const fpos& __other) const
      { return _M_off - __other._M_off; }
    };






  template<typename _StateT>
    inline bool
    operator==(const fpos<_StateT>& __lhs, const fpos<_StateT>& __rhs)
    { return streamoff(__lhs) == streamoff(__rhs); }

  template<typename _StateT>
    inline bool
    operator!=(const fpos<_StateT>& __lhs, const fpos<_StateT>& __rhs)
    { return streamoff(__lhs) != streamoff(__rhs); }





  typedef fpos<mbstate_t> streampos;

  typedef fpos<mbstate_t> wstreampos;
# 239 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/postypes.h" 3

}
# 41 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/iosfwd" 2 3

namespace std
{

# 74 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/iosfwd" 3
  class ios_base;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_ios;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_streambuf;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_istream;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_ostream;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_iostream;




  template<typename _CharT, typename _Traits = char_traits<_CharT>,
     typename _Alloc = allocator<_CharT> >
    class basic_stringbuf;

  template<typename _CharT, typename _Traits = char_traits<_CharT>,
    typename _Alloc = allocator<_CharT> >
    class basic_istringstream;

  template<typename _CharT, typename _Traits = char_traits<_CharT>,
    typename _Alloc = allocator<_CharT> >
    class basic_ostringstream;

  template<typename _CharT, typename _Traits = char_traits<_CharT>,
    typename _Alloc = allocator<_CharT> >
    class basic_stringstream;



  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_filebuf;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_ifstream;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_ofstream;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_fstream;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class istreambuf_iterator;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class ostreambuf_iterator;



  typedef basic_ios<char> ios;


  typedef basic_streambuf<char> streambuf;


  typedef basic_istream<char> istream;


  typedef basic_ostream<char> ostream;


  typedef basic_iostream<char> iostream;


  typedef basic_stringbuf<char> stringbuf;


  typedef basic_istringstream<char> istringstream;


  typedef basic_ostringstream<char> ostringstream;


  typedef basic_stringstream<char> stringstream;


  typedef basic_filebuf<char> filebuf;


  typedef basic_ifstream<char> ifstream;


  typedef basic_ofstream<char> ofstream;


  typedef basic_fstream<char> fstream;



  typedef basic_ios<wchar_t> wios;


  typedef basic_streambuf<wchar_t> wstreambuf;


  typedef basic_istream<wchar_t> wistream;


  typedef basic_ostream<wchar_t> wostream;


  typedef basic_iostream<wchar_t> wiostream;


  typedef basic_stringbuf<wchar_t> wstringbuf;


  typedef basic_istringstream<wchar_t> wistringstream;


  typedef basic_ostringstream<wchar_t> wostringstream;


  typedef basic_stringstream<wchar_t> wstringstream;


  typedef basic_filebuf<wchar_t> wfilebuf;


  typedef basic_ifstream<wchar_t> wifstream;


  typedef basic_ofstream<wchar_t> wofstream;


  typedef basic_fstream<wchar_t> wfstream;




}
# 55 "./util/string_piece.hh" 2
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 1 3
# 36 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 3
       
# 37 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 3

# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ios" 1 3
# 36 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ios" 3
       
# 37 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ios" 3



# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/char_traits.h" 1 3
# 37 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/char_traits.h" 3
       
# 38 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/char_traits.h" 3



# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cwchar" 1 3
# 39 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cwchar" 3
       
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cwchar" 3
# 42 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/char_traits.h" 2 3

namespace __gnu_cxx
{

# 57 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/char_traits.h" 3
  template<typename _CharT>
    struct _Char_types
    {
      typedef unsigned long int_type;
      typedef std::streampos pos_type;
      typedef std::streamoff off_type;
      typedef std::mbstate_t state_type;
    };
# 82 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/char_traits.h" 3
  template<typename _CharT>
    struct char_traits
    {
      typedef _CharT char_type;
      typedef typename _Char_types<_CharT>::int_type int_type;
      typedef typename _Char_types<_CharT>::pos_type pos_type;
      typedef typename _Char_types<_CharT>::off_type off_type;
      typedef typename _Char_types<_CharT>::state_type state_type;

      static void
      assign(char_type& __c1, const char_type& __c2)
      { __c1 = __c2; }

      static bool
      eq(const char_type& __c1, const char_type& __c2)
      { return __c1 == __c2; }

      static bool
      lt(const char_type& __c1, const char_type& __c2)
      { return __c1 < __c2; }

      static int
      compare(const char_type* __s1, const char_type* __s2, std::size_t __n);

      static std::size_t
      length(const char_type* __s);

      static const char_type*
      find(const char_type* __s, std::size_t __n, const char_type& __a);

      static char_type*
      move(char_type* __s1, const char_type* __s2, std::size_t __n);

      static char_type*
      copy(char_type* __s1, const char_type* __s2, std::size_t __n);

      static char_type*
      assign(char_type* __s, std::size_t __n, char_type __a);

      static char_type
      to_char_type(const int_type& __c)
      { return static_cast<char_type>(__c); }

      static int_type
      to_int_type(const char_type& __c)
      { return static_cast<int_type>(__c); }

      static bool
      eq_int_type(const int_type& __c1, const int_type& __c2)
      { return __c1 == __c2; }

      static int_type
      eof()
      { return static_cast<int_type>(-1); }

      static int_type
      not_eof(const int_type& __c)
      { return !eq_int_type(__c, eof()) ? __c : to_int_type(char_type()); }
    };

  template<typename _CharT>
    int
    char_traits<_CharT>::
    compare(const char_type* __s1, const char_type* __s2, std::size_t __n)
    {
      for (std::size_t __i = 0; __i < __n; ++__i)
 if (lt(__s1[__i], __s2[__i]))
   return -1;
 else if (lt(__s2[__i], __s1[__i]))
   return 1;
      return 0;
    }

  template<typename _CharT>
    std::size_t
    char_traits<_CharT>::
    length(const char_type* __p)
    {
      std::size_t __i = 0;
      while (!eq(__p[__i], char_type()))
        ++__i;
      return __i;
    }

  template<typename _CharT>
    const typename char_traits<_CharT>::char_type*
    char_traits<_CharT>::
    find(const char_type* __s, std::size_t __n, const char_type& __a)
    {
      for (std::size_t __i = 0; __i < __n; ++__i)
        if (eq(__s[__i], __a))
          return __s + __i;
      return 0;
    }

  template<typename _CharT>
    typename char_traits<_CharT>::char_type*
    char_traits<_CharT>::
    move(char_type* __s1, const char_type* __s2, std::size_t __n)
    {
      return static_cast<_CharT*>(__builtin_memmove(__s1, __s2,
          __n * sizeof(char_type)));
    }

  template<typename _CharT>
    typename char_traits<_CharT>::char_type*
    char_traits<_CharT>::
    copy(char_type* __s1, const char_type* __s2, std::size_t __n)
    {

      std::copy(__s2, __s2 + __n, __s1);
      return __s1;
    }

  template<typename _CharT>
    typename char_traits<_CharT>::char_type*
    char_traits<_CharT>::
    assign(char_type* __s, std::size_t __n, char_type __a)
    {

      std::fill_n(__s, __n, __a);
      return __s;
    }


}

namespace std
{

# 226 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/char_traits.h" 3
  template<class _CharT>
    struct char_traits : public __gnu_cxx::char_traits<_CharT>
    { };



  template<>
    struct char_traits<char>
    {
      typedef char char_type;
      typedef int int_type;
      typedef streampos pos_type;
      typedef streamoff off_type;
      typedef mbstate_t state_type;

      static void
      assign(char_type& __c1, const char_type& __c2)
      { __c1 = __c2; }

      static bool
      eq(const char_type& __c1, const char_type& __c2)
      { return __c1 == __c2; }

      static bool
      lt(const char_type& __c1, const char_type& __c2)
      {

 return (static_cast<unsigned char>(__c1)
  < static_cast<unsigned char>(__c2));
      }

      static int
      compare(const char_type* __s1, const char_type* __s2, size_t __n)
      {
 if (__n == 0)
   return 0;
 return __builtin_memcmp(__s1, __s2, __n);
      }

      static size_t
      length(const char_type* __s)
      { return __builtin_strlen(__s); }

      static const char_type*
      find(const char_type* __s, size_t __n, const char_type& __a)
      {
 if (__n == 0)
   return 0;
 return static_cast<const char_type*>(__builtin_memchr(__s, __a, __n));
      }

      static char_type*
      move(char_type* __s1, const char_type* __s2, size_t __n)
      {
 if (__n == 0)
   return __s1;
 return static_cast<char_type*>(__builtin_memmove(__s1, __s2, __n));
      }

      static char_type*
      copy(char_type* __s1, const char_type* __s2, size_t __n)
      {
 if (__n == 0)
   return __s1;
 return static_cast<char_type*>(__builtin_memcpy(__s1, __s2, __n));
      }

      static char_type*
      assign(char_type* __s, size_t __n, char_type __a)
      {
 if (__n == 0)
   return __s;
 return static_cast<char_type*>(__builtin_memset(__s, __a, __n));
      }

      static char_type
      to_char_type(const int_type& __c)
      { return static_cast<char_type>(__c); }



      static int_type
      to_int_type(const char_type& __c)
      { return static_cast<int_type>(static_cast<unsigned char>(__c)); }

      static bool
      eq_int_type(const int_type& __c1, const int_type& __c2)
      { return __c1 == __c2; }

      static int_type
      eof()
      { return static_cast<int_type>(-1); }

      static int_type
      not_eof(const int_type& __c)
      { return (__c == eof()) ? 0 : __c; }
  };




  template<>
    struct char_traits<wchar_t>
    {
      typedef wchar_t char_type;
      typedef wint_t int_type;
      typedef streamoff off_type;
      typedef wstreampos pos_type;
      typedef mbstate_t state_type;

      static void
      assign(char_type& __c1, const char_type& __c2)
      { __c1 = __c2; }

      static bool
      eq(const char_type& __c1, const char_type& __c2)
      { return __c1 == __c2; }

      static bool
      lt(const char_type& __c1, const char_type& __c2)
      { return __c1 < __c2; }

      static int
      compare(const char_type* __s1, const char_type* __s2, size_t __n)
      {
 if (__n == 0)
   return 0;
 return wmemcmp(__s1, __s2, __n);
      }

      static size_t
      length(const char_type* __s)
      { return wcslen(__s); }

      static const char_type*
      find(const char_type* __s, size_t __n, const char_type& __a)
      {
 if (__n == 0)
   return 0;
 return wmemchr(__s, __a, __n);
      }

      static char_type*
      move(char_type* __s1, const char_type* __s2, size_t __n)
      {
 if (__n == 0)
   return __s1;
 return wmemmove(__s1, __s2, __n);
      }

      static char_type*
      copy(char_type* __s1, const char_type* __s2, size_t __n)
      {
 if (__n == 0)
   return __s1;
 return wmemcpy(__s1, __s2, __n);
      }

      static char_type*
      assign(char_type* __s, size_t __n, char_type __a)
      {
 if (__n == 0)
   return __s;
 return wmemset(__s, __a, __n);
      }

      static char_type
      to_char_type(const int_type& __c)
      { return char_type(__c); }

      static int_type
      to_int_type(const char_type& __c)
      { return int_type(__c); }

      static bool
      eq_int_type(const int_type& __c1, const int_type& __c2)
      { return __c1 == __c2; }

      static int_type
      eof()
      { return static_cast<int_type>(((wint_t)-1)); }

      static int_type
      not_eof(const int_type& __c)
      { return eq_int_type(__c, eof()) ? 0 : __c; }
  };



}
# 41 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ios" 2 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/localefwd.h" 1 3
# 37 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/localefwd.h" 3
       
# 38 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/localefwd.h" 3


# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/c++locale.h" 1 3
# 39 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/c++locale.h" 3
       
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/c++locale.h" 3

# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/clocale" 1 3
# 39 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/clocale" 3
       
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/clocale" 3


# 1 "/usr/include/locale.h" 1 3 4
# 14 "/usr/include/locale.h" 3 4
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/stddef.h" 1 3 4
# 15 "/usr/include/locale.h" 2 3 4
# 40 "/usr/include/locale.h" 3 4
extern "C" {

struct lconv
{
  char *decimal_point;
  char *thousands_sep;
  char *grouping;
  char *int_curr_symbol;
  char *currency_symbol;
  char *mon_decimal_point;
  char *mon_thousands_sep;
  char *mon_grouping;
  char *positive_sign;
  char *negative_sign;
  char int_frac_digits;
  char frac_digits;
  char p_cs_precedes;
  char p_sep_by_space;
  char n_cs_precedes;
  char n_sep_by_space;
  char p_sign_posn;
  char n_sign_posn;
  char int_n_cs_precedes;
  char int_n_sep_by_space;
  char int_n_sign_posn;
  char int_p_cs_precedes;
  char int_p_sep_by_space;
  char int_p_sign_posn;
};

struct _reent;
char *__attribute__((__cdecl__)) _setlocale_r (struct _reent *, int, const char *);
struct lconv *__attribute__((__cdecl__)) _localeconv_r (struct _reent *);

struct __locale_t *_newlocale_r (struct _reent *, int, const char *,
     struct __locale_t *);
void _freelocale_r (struct _reent *, struct __locale_t *);
struct __locale_t *_duplocale_r (struct _reent *, struct __locale_t *);
struct __locale_t *_uselocale_r (struct _reent *, struct __locale_t *);



char *__attribute__((__cdecl__)) setlocale (int, const char *);
struct lconv *__attribute__((__cdecl__)) localeconv (void);


locale_t newlocale (int, const char *, locale_t);
void freelocale (locale_t);
locale_t duplocale (locale_t);
locale_t uselocale (locale_t);




}
# 43 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/clocale" 2 3
# 51 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/clocale" 3
namespace std
{
  using ::lconv;
  using ::setlocale;
  using ::localeconv;
}
# 42 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/c++locale.h" 2 3



namespace std
{


  typedef int* __c_locale;





  inline int
  __convert_from_v(const __c_locale&, char* __out,
     const int __size __attribute__((__unused__)),
     const char* __fmt, ...)
  {
    char* __old = std::setlocale(4, 0);
    char* __sav = 0;
    if (__builtin_strcmp(__old, "C"))
      {
 const size_t __len = __builtin_strlen(__old) + 1;
 __sav = new char[__len];
 __builtin_memcpy(__sav, __old, __len);
 std::setlocale(4, "C");
      }

    __builtin_va_list __args;
    __builtin_va_start(__args, __fmt);


    const int __ret = __builtin_vsnprintf(__out, __size, __fmt, __args);




    __builtin_va_end(__args);

    if (__sav)
      {
 std::setlocale(4, __sav);
 delete [] __sav;
      }
    return __ret;
  }


}
# 41 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/localefwd.h" 2 3

# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cctype" 1 3
# 39 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cctype" 3
       
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cctype" 3


# 1 "/usr/include/ctype.h" 1 3 4
# 11 "/usr/include/ctype.h" 3 4
extern "C" {

int __attribute__((__cdecl__)) isalnum (int __c);
int __attribute__((__cdecl__)) isalpha (int __c);
int __attribute__((__cdecl__)) iscntrl (int __c);
int __attribute__((__cdecl__)) isdigit (int __c);
int __attribute__((__cdecl__)) isgraph (int __c);
int __attribute__((__cdecl__)) islower (int __c);
int __attribute__((__cdecl__)) isprint (int __c);
int __attribute__((__cdecl__)) ispunct (int __c);
int __attribute__((__cdecl__)) isspace (int __c);
int __attribute__((__cdecl__)) isupper (int __c);
int __attribute__((__cdecl__)) isxdigit (int __c);
int __attribute__((__cdecl__)) tolower (int __c);
int __attribute__((__cdecl__)) toupper (int __c);


int __attribute__((__cdecl__)) isblank (int __c);



int __attribute__((__cdecl__)) isascii (int __c);
int __attribute__((__cdecl__)) toascii (int __c);





extern int isalnum_l (int __c, locale_t __l);
extern int isalpha_l (int __c, locale_t __l);
extern int isblank_l (int __c, locale_t __l);
extern int iscntrl_l (int __c, locale_t __l);
extern int isdigit_l (int __c, locale_t __l);
extern int isgraph_l (int __c, locale_t __l);
extern int islower_l (int __c, locale_t __l);
extern int isprint_l (int __c, locale_t __l);
extern int ispunct_l (int __c, locale_t __l);
extern int isspace_l (int __c, locale_t __l);
extern int isupper_l (int __c, locale_t __l);
extern int isxdigit_l(int __c, locale_t __l);
extern int tolower_l (int __c, locale_t __l);
extern int toupper_l (int __c, locale_t __l);



extern int isascii_l (int __c, locale_t __l);
extern int toascii_l (int __c, locale_t __l);
# 69 "/usr/include/ctype.h" 3 4
const char *__locale_ctype_ptr (void);
# 165 "/usr/include/ctype.h" 3 4
extern __attribute__((dllimport)) const char _ctype_[];

}
# 43 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cctype" 2 3
# 62 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cctype" 3
namespace std
{
  using ::isalnum;
  using ::isalpha;
  using ::iscntrl;
  using ::isdigit;
  using ::isgraph;
  using ::islower;
  using ::isprint;
  using ::ispunct;
  using ::isspace;
  using ::isupper;
  using ::isxdigit;
  using ::tolower;
  using ::toupper;
}
# 43 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/localefwd.h" 2 3

namespace std
{

# 55 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/localefwd.h" 3
  class locale;

  template<typename _Facet>
    bool
    has_facet(const locale&) throw();

  template<typename _Facet>
    const _Facet&
    use_facet(const locale&);


  template<typename _CharT>
    bool
    isspace(_CharT, const locale&);

  template<typename _CharT>
    bool
    isprint(_CharT, const locale&);

  template<typename _CharT>
    bool
    iscntrl(_CharT, const locale&);

  template<typename _CharT>
    bool
    isupper(_CharT, const locale&);

  template<typename _CharT>
    bool
    islower(_CharT, const locale&);

  template<typename _CharT>
    bool
    isalpha(_CharT, const locale&);

  template<typename _CharT>
    bool
    isdigit(_CharT, const locale&);

  template<typename _CharT>
    bool
    ispunct(_CharT, const locale&);

  template<typename _CharT>
    bool
    isxdigit(_CharT, const locale&);

  template<typename _CharT>
    bool
    isalnum(_CharT, const locale&);

  template<typename _CharT>
    bool
    isgraph(_CharT, const locale&);







  template<typename _CharT>
    _CharT
    toupper(_CharT, const locale&);

  template<typename _CharT>
    _CharT
    tolower(_CharT, const locale&);


  class ctype_base;
  template<typename _CharT>
    class ctype;
  template<> class ctype<char>;

  template<> class ctype<wchar_t>;

  template<typename _CharT>
    class ctype_byname;


  class codecvt_base;
  template<typename _InternT, typename _ExternT, typename _StateT>
    class codecvt;
  template<> class codecvt<char, char, mbstate_t>;

  template<> class codecvt<wchar_t, char, mbstate_t>;

  template<typename _InternT, typename _ExternT, typename _StateT>
    class codecvt_byname;



  template<typename _CharT, typename _InIter = istreambuf_iterator<_CharT> >
    class num_get;
  template<typename _CharT, typename _OutIter = ostreambuf_iterator<_CharT> >
    class num_put;


  template<typename _CharT> class numpunct;
  template<typename _CharT> class numpunct_byname;




  template<typename _CharT>
    class collate;
  template<typename _CharT>
    class collate_byname;



  class time_base;

  template<typename _CharT, typename _InIter = istreambuf_iterator<_CharT> >
    class time_get;
  template<typename _CharT, typename _InIter = istreambuf_iterator<_CharT> >
    class time_get_byname;

  template<typename _CharT, typename _OutIter = ostreambuf_iterator<_CharT> >
    class time_put;
  template<typename _CharT, typename _OutIter = ostreambuf_iterator<_CharT> >
    class time_put_byname;


  class money_base;

  template<typename _CharT, typename _InIter = istreambuf_iterator<_CharT> >
    class money_get;
  template<typename _CharT, typename _OutIter = ostreambuf_iterator<_CharT> >
    class money_put;


  template<typename _CharT, bool _Intl = false>
    class moneypunct;
  template<typename _CharT, bool _Intl = false>
    class moneypunct_byname;



  class messages_base;

  template<typename _CharT>
    class messages;
  template<typename _CharT>
    class messages_byname;



}
# 42 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ios" 2 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 1 3
# 37 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 3
       
# 38 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 3

# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ext/atomicity.h" 1 3
# 32 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ext/atomicity.h" 3
       
# 33 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ext/atomicity.h" 3


# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/gthr.h" 1 3
# 30 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/gthr.h" 3
#pragma GCC visibility push(default)
# 148 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/gthr.h" 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/gthr-default.h" 1 3
# 35 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/gthr-default.h" 3
# 1 "/usr/include/pthread.h" 1 3 4
# 11 "/usr/include/pthread.h" 3 4
# 1 "/usr/include/sys/types.h" 1 3 4
# 28 "/usr/include/sys/types.h" 3 4
typedef __uint8_t u_int8_t;


typedef __uint16_t u_int16_t;


typedef __uint32_t u_int32_t;


typedef __uint64_t u_int64_t;

typedef int register_t;
# 62 "/usr/include/sys/types.h" 3 4
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/stddef.h" 1 3 4
# 63 "/usr/include/sys/types.h" 2 3 4





# 1 "/usr/include/sys/select.h" 1 3 4
# 25 "/usr/include/sys/select.h" 3 4
# 1 "/usr/include/sys/_sigset.h" 1 3 4
# 41 "/usr/include/sys/_sigset.h" 3 4
typedef unsigned long __sigset_t;
# 26 "/usr/include/sys/select.h" 2 3 4
# 1 "/usr/include/sys/_timeval.h" 1 3 4
# 35 "/usr/include/sys/_timeval.h" 3 4
typedef __suseconds_t suseconds_t;




typedef long time_t;
# 52 "/usr/include/sys/_timeval.h" 3 4
struct timeval {
 time_t tv_sec;
 suseconds_t tv_usec;
};
# 27 "/usr/include/sys/select.h" 2 3 4
# 1 "/usr/include/sys/timespec.h" 1 3 4
# 38 "/usr/include/sys/timespec.h" 3 4
# 1 "/usr/include/sys/_timespec.h" 1 3 4
# 45 "/usr/include/sys/_timespec.h" 3 4
struct timespec {
 time_t tv_sec;
 long tv_nsec;
};
# 39 "/usr/include/sys/timespec.h" 2 3 4
# 58 "/usr/include/sys/timespec.h" 3 4
struct itimerspec {
 struct timespec it_interval;
 struct timespec it_value;
};
# 28 "/usr/include/sys/select.h" 2 3 4



typedef __sigset_t sigset_t;
# 45 "/usr/include/sys/select.h" 3 4
typedef unsigned long fd_mask;







typedef struct _types_fd_set {
 fd_mask fds_bits[(((64)+(((sizeof (fd_mask) * 8))-1))/((sizeof (fd_mask) * 8)))];
} _types_fd_set;
# 71 "/usr/include/sys/select.h" 3 4
extern "C" {

int select (int __n, _types_fd_set *__readfds, _types_fd_set *__writefds, _types_fd_set *__exceptfds, struct timeval *__timeout)
                                                   ;

int pselect (int __n, _types_fd_set *__readfds, _types_fd_set *__writefds, _types_fd_set *__exceptfds, const struct timespec *__timeout, const sigset_t *__set)

                           ;


}
# 69 "/usr/include/sys/types.h" 2 3 4




typedef __uint32_t in_addr_t;




typedef __uint16_t in_port_t;
# 87 "/usr/include/sys/types.h" 3 4
typedef unsigned char u_char;



typedef unsigned short u_short;



typedef unsigned int u_int;



typedef unsigned long u_long;







typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;



typedef __blkcnt_t blkcnt_t;




typedef __blksize_t blksize_t;




typedef unsigned long clock_t;
# 135 "/usr/include/sys/types.h" 3 4
typedef long daddr_t;



typedef char * caddr_t;




typedef __fsblkcnt_t fsblkcnt_t;
typedef __fsfilcnt_t fsfilcnt_t;




typedef __id_t id_t;




typedef __ino_t ino_t;
# 173 "/usr/include/sys/types.h" 3 4
typedef __off_t off_t;



typedef __dev_t dev_t;



typedef __uid_t uid_t;



typedef __gid_t gid_t;




typedef __pid_t pid_t;




typedef __key_t key_t;




typedef _ssize_t ssize_t;




typedef __mode_t mode_t;




typedef __nlink_t nlink_t;




typedef __clockid_t clockid_t;





typedef __timer_t timer_t;





typedef __useconds_t useconds_t;
# 236 "/usr/include/sys/types.h" 3 4
typedef __int64_t sbintime_t;
# 465 "/usr/include/sys/types.h" 3 4
# 1 "/usr/include/machine/types.h" 1 3 4
# 15 "/usr/include/machine/types.h" 3 4
extern "C"
{
# 25 "/usr/include/machine/types.h" 3 4
typedef struct timespec timespec_t;




typedef struct timespec timestruc_t;


typedef __loff_t loff_t;
# 46 "/usr/include/machine/types.h" 3 4
struct flock {
 short l_type;
 short l_whence;
 off_t l_start;
 off_t l_len;
 pid_t l_pid;
};






typedef unsigned long vm_offset_t;




typedef unsigned long vm_size_t;




typedef void *vm_object_t;




typedef char *addr_t;






typedef struct __pthread_t {char __dummy;} *pthread_t;
typedef struct __pthread_mutex_t {char __dummy;} *pthread_mutex_t;

typedef struct __pthread_key_t {char __dummy;} *pthread_key_t;
typedef struct __pthread_attr_t {char __dummy;} *pthread_attr_t;
typedef struct __pthread_mutexattr_t {char __dummy;} *pthread_mutexattr_t;
typedef struct __pthread_condattr_t {char __dummy;} *pthread_condattr_t;
typedef struct __pthread_cond_t {char __dummy;} *pthread_cond_t;
typedef struct __pthread_barrierattr_t {char __dummy;} *pthread_barrierattr_t;
typedef struct __pthread_barrier_t {char __dummy;} *pthread_barrier_t;


typedef struct
{
  pthread_mutex_t mutex;
  int state;
}
pthread_once_t;
typedef struct __pthread_spinlock_t {char __dummy;} *pthread_spinlock_t;
typedef struct __pthread_rwlock_t {char __dummy;} *pthread_rwlock_t;
typedef struct __pthread_rwlockattr_t {char __dummy;} *pthread_rwlockattr_t;
# 126 "/usr/include/machine/types.h" 3 4
# 1 "/usr/include/sys/sysmacros.h" 1 3 4
# 12 "/usr/include/sys/sysmacros.h" 3 4
# 1 "/usr/include/sys/types.h" 1 3 4
# 13 "/usr/include/sys/sysmacros.h" 2 3 4

extern __inline__ __attribute__ ((__always_inline__)) int gnu_dev_major(dev_t);
extern __inline__ __attribute__ ((__always_inline__)) int gnu_dev_minor(dev_t);
extern __inline__ __attribute__ ((__always_inline__)) dev_t gnu_dev_makedev(int, int);

extern __inline__ __attribute__ ((__always_inline__)) int
gnu_dev_major(dev_t dev)
{
 return (int)(((dev) >> 16) & 0xffff);
}

extern __inline__ __attribute__ ((__always_inline__)) int
gnu_dev_minor(dev_t dev)
{
 return (int)((dev) & 0xffff);
}

extern __inline__ __attribute__ ((__always_inline__)) dev_t
gnu_dev_makedev(int maj, int min)
{
 return (((maj) << 16) | ((min) & 0xffff));
}
# 127 "/usr/include/machine/types.h" 2 3 4


}
# 466 "/usr/include/sys/types.h" 2 3 4
# 12 "/usr/include/pthread.h" 2 3 4
# 1 "/usr/include/signal.h" 1 3 4





# 1 "/usr/include/sys/signal.h" 1 3 4





extern "C" {
# 112 "/usr/include/sys/signal.h" 3 4
# 1 "/usr/include/cygwin/signal.h" 1 3 4
# 15 "/usr/include/cygwin/signal.h" 3 4
extern "C" {
# 24 "/usr/include/cygwin/signal.h" 3 4
struct _uc_fpxreg {
  __uint16_t significand[4];
  __uint16_t exponent;
  __uint16_t padding[3];
};

struct _uc_xmmreg {
  __uint32_t element[4];
};

struct _fpstate
{
  __uint16_t cwd;
  __uint16_t swd;
  __uint16_t ftw;
  __uint16_t fop;
  __uint64_t rip;
  __uint64_t rdp;
  __uint32_t mxcsr;
  __uint32_t mxcr_mask;
  struct _uc_fpxreg st[8];
  struct _uc_xmmreg xmm[16];
  __uint32_t padding[24];
};

struct __attribute__ ((aligned (16))) __mcontext
{
  __uint64_t p1home;
  __uint64_t p2home;
  __uint64_t p3home;
  __uint64_t p4home;
  __uint64_t p5home;
  __uint64_t p6home;
  __uint32_t ctxflags;
  __uint32_t mxcsr;
  __uint16_t cs;
  __uint16_t ds;
  __uint16_t es;
  __uint16_t fs;
  __uint16_t gs;
  __uint16_t ss;
  __uint32_t eflags;
  __uint64_t dr0;
  __uint64_t dr1;
  __uint64_t dr2;
  __uint64_t dr3;
  __uint64_t dr6;
  __uint64_t dr7;
  __uint64_t rax;
  __uint64_t rcx;
  __uint64_t rdx;
  __uint64_t rbx;
  __uint64_t rsp;
  __uint64_t rbp;
  __uint64_t rsi;
  __uint64_t rdi;
  __uint64_t r8;
  __uint64_t r9;
  __uint64_t r10;
  __uint64_t r11;
  __uint64_t r12;
  __uint64_t r13;
  __uint64_t r14;
  __uint64_t r15;
  __uint64_t rip;
  struct _fpstate fpregs;
  __uint64_t vregs[52];
  __uint64_t vcx;
  __uint64_t dbc;
  __uint64_t btr;
  __uint64_t bfr;
  __uint64_t etr;
  __uint64_t efr;
  __uint64_t oldmask;
  __uint64_t cr2;
};
# 163 "/usr/include/cygwin/signal.h" 3 4
typedef union sigval
{
  int sival_int;
  void *sival_ptr;
} sigval_t;

typedef struct sigevent
{
  sigval_t sigev_value;
  int sigev_signo;
  int sigev_notify;
  void (*sigev_notify_function) (sigval_t);
  pthread_attr_t *sigev_notify_attributes;
} sigevent_t;

#pragma pack(push,4)
struct _sigcommune
{
  __uint32_t _si_code;
  void *_si_read_handle;
  void *_si_write_handle;
  void *_si_process_handle;
  __extension__ union
  {
    int _si_fd;
    int64_t _si_pipe_unique_id;
    char *_si_str;
  };
};
# 206 "/usr/include/cygwin/signal.h" 3 4
typedef struct
{
  int si_signo;
  int si_code;
  pid_t si_pid;
  uid_t si_uid;
  int si_errno;

  __extension__ union
  {
    __uint32_t __pad[32];
    struct _sigcommune _si_commune;
    __extension__ struct
    {
      __extension__ union
      {
 sigval_t si_sigval;
 sigval_t si_value;
      };
      __extension__ struct
      {
 timer_t si_tid;
 unsigned int si_overrun;
      };
    };

    __extension__ struct
    {
      int si_status;
      clock_t si_utime;
      clock_t si_stime;
    };

    void *si_addr;
# 250 "/usr/include/cygwin/signal.h" 3 4
  };
} siginfo_t;
#pragma pack(pop)

enum
{
  SI_USER = 0,
  SI_ASYNCIO = 2,

  SI_MESGQ,

  SI_TIMER,
  SI_QUEUE,

  SI_KERNEL,

  ILL_ILLOPC,
  ILL_ILLOPN,
  ILL_ILLADR,
  ILL_ILLTRP,
  ILL_PRVOPC,
  ILL_PRVREG,
  ILL_COPROC,
  ILL_BADSTK,

  FPE_INTDIV,
  FPE_INTOVF,
  FPE_FLTDIV,
  FPE_FLTOVF,
  FPE_FLTUND,
  FPE_FLTRES,
  FPE_FLTINV,
  FPE_FLTSUB,

  SEGV_MAPERR,
  SEGV_ACCERR,

  BUS_ADRALN,
  BUS_ADRERR,
  BUS_OBJERR,

  CLD_EXITED,
  CLD_KILLED,
  CLD_DUMPED,
  CLD_TRAPPED,
  CLD_STOPPED,
  CLD_CONTINUED
};

enum
{
  SIGEV_SIGNAL = 0,


  SIGEV_NONE,


  SIGEV_THREAD

};





typedef void (*_sig_func_ptr)(int);

struct sigaction
{
  __extension__ union
  {
    _sig_func_ptr sa_handler;
    void (*sa_sigaction) ( int, siginfo_t *, void * );
  };
  sigset_t sa_mask;
  int sa_flags;
};
# 400 "/usr/include/cygwin/signal.h" 3 4
void psiginfo (const siginfo_t *, const char *);
int sigwait (const sigset_t *, int *);
int sigwaitinfo (const sigset_t *, siginfo_t *);
int sighold (int);
int sigignore (int);
int sigrelse (int);
_sig_func_ptr sigset (int, _sig_func_ptr);

int sigqueue(pid_t, int, const union sigval);
int siginterrupt (int, int);




extern const char __attribute__((dllimport)) *sys_sigabbrev[];
extern const char __attribute__((dllimport)) *sys_siglist[];



}
# 113 "/usr/include/sys/signal.h" 2 3 4
# 149 "/usr/include/sys/signal.h" 3 4
typedef struct sigaltstack {
  void *ss_sp;
  int ss_flags;
  size_t ss_size;
} stack_t;





int __attribute__((__cdecl__)) sigprocmask (int how, const sigset_t *set, sigset_t *oset);


int __attribute__((__cdecl__)) pthread_sigmask (int how, const sigset_t *set, sigset_t *oset);
# 171 "/usr/include/sys/signal.h" 3 4
int __attribute__((__cdecl__)) kill (pid_t, int);


int __attribute__((__cdecl__)) killpg (pid_t, int);
int __attribute__((__cdecl__)) sigaction (int, const struct sigaction *, struct sigaction *);
int __attribute__((__cdecl__)) sigaddset (sigset_t *, const int);
int __attribute__((__cdecl__)) sigdelset (sigset_t *, const int);
int __attribute__((__cdecl__)) sigismember (const sigset_t *, int);
int __attribute__((__cdecl__)) sigfillset (sigset_t *);
int __attribute__((__cdecl__)) sigemptyset (sigset_t *);
int __attribute__((__cdecl__)) sigpending (sigset_t *);
int __attribute__((__cdecl__)) sigsuspend (const sigset_t *);
int __attribute__((__cdecl__)) sigpause (int);
# 198 "/usr/include/sys/signal.h" 3 4
int __attribute__((__cdecl__)) sigaltstack (const stack_t *, stack_t *);



int __attribute__((__cdecl__)) pthread_kill (pthread_t thread, int sig);







int __attribute__((__cdecl__)) sigwaitinfo (const sigset_t *set, siginfo_t *info);
int __attribute__((__cdecl__)) sigtimedwait (const sigset_t *set, siginfo_t *info, const struct timespec *timeout)

 ;
int __attribute__((__cdecl__)) sigwait (const sigset_t *set, int *sig);


int __attribute__((__cdecl__)) sigqueue (pid_t pid, int signo, const union sigval value);
# 337 "/usr/include/sys/signal.h" 3 4
}




# 1 "/usr/include/sys/ucontext.h" 1 3 4
# 12 "/usr/include/sys/ucontext.h" 3 4
# 1 "/usr/include/signal.h" 1 3 4
# 13 "/usr/include/sys/ucontext.h" 2 3 4

typedef struct __mcontext mcontext_t;

typedef __attribute__ ((aligned (16))) struct __ucontext {
 mcontext_t uc_mcontext;
 struct __ucontext *uc_link;
 sigset_t uc_sigmask;
 stack_t uc_stack;
 unsigned long int uc_flags;
} ucontext_t;
# 343 "/usr/include/sys/signal.h" 2 3 4
# 7 "/usr/include/signal.h" 2 3 4

extern "C" {

typedef int sig_atomic_t;

typedef _sig_func_ptr sig_t;
# 22 "/usr/include/signal.h" 3 4
struct _reent;

_sig_func_ptr __attribute__((__cdecl__)) _signal_r (struct _reent *, int, _sig_func_ptr);
int __attribute__((__cdecl__)) _raise_r (struct _reent *, int);


_sig_func_ptr __attribute__((__cdecl__)) signal (int, _sig_func_ptr);
int __attribute__((__cdecl__)) raise (int);
void __attribute__((__cdecl__)) psignal (int, const char *);


}
# 13 "/usr/include/pthread.h" 2 3 4
# 1 "/usr/include/sched.h" 1 3 4
# 24 "/usr/include/sched.h" 3 4
# 1 "/usr/include/sys/sched.h" 1 3 4
# 27 "/usr/include/sys/sched.h" 3 4
extern "C" {
# 48 "/usr/include/sys/sched.h" 3 4
struct sched_param {
  int sched_priority;
# 61 "/usr/include/sys/sched.h" 3 4
};


}
# 25 "/usr/include/sched.h" 2 3 4


extern "C" {






int sched_setparam(
  pid_t __pid,
  const struct sched_param *__param
);




int sched_getparam(
  pid_t __pid,
  struct sched_param *__param
);





int sched_setscheduler(
  pid_t __pid,
  int __policy,
  const struct sched_param *__param
);




int sched_getscheduler(
  pid_t __pid
);




int sched_get_priority_max(
  int __policy
);

int sched_get_priority_min(
  int __policy
);




int sched_rr_get_interval(
  pid_t __pid,
  struct timespec *__interval
);







int sched_yield( void );




}
# 14 "/usr/include/pthread.h" 2 3 4
# 1 "/usr/include/time.h" 1 3 4
# 16 "/usr/include/time.h" 3 4
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/stddef.h" 1 3 4
# 17 "/usr/include/time.h" 2 3 4


# 1 "/usr/include/machine/time.h" 1 3 4
# 20 "/usr/include/time.h" 2 3 4
# 35 "/usr/include/time.h" 3 4
extern "C" {

struct tm
{
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;

  long tm_gmtoff;


  const char *tm_zone;

};

clock_t __attribute__((__cdecl__)) clock (void);
double __attribute__((__cdecl__)) difftime (time_t _time2, time_t _time1);
time_t __attribute__((__cdecl__)) mktime (struct tm *_timeptr);
time_t __attribute__((__cdecl__)) time (time_t *_timer);

char *__attribute__((__cdecl__)) asctime (const struct tm *_tblock);
char *__attribute__((__cdecl__)) ctime (const time_t *_time);
struct tm *__attribute__((__cdecl__)) gmtime (const time_t *_timer);
struct tm *__attribute__((__cdecl__)) localtime (const time_t *_timer);

size_t __attribute__((__cdecl__)) strftime (char * _s, size_t _maxsize, const char * _fmt, const struct tm * _t)

                                        ;


extern size_t strftime_l (char * _s, size_t _maxsize,
     const char * _fmt,
     const struct tm * _t, locale_t _l);


char *__attribute__((__cdecl__)) asctime_r (const struct tm *, char *)
                       ;
char *__attribute__((__cdecl__)) ctime_r (const time_t *, char *);
struct tm *__attribute__((__cdecl__)) gmtime_r (const time_t *, struct tm *)
                            ;
struct tm *__attribute__((__cdecl__)) localtime_r (const time_t *, struct tm *)
                            ;

}


extern "C" {
# 101 "/usr/include/time.h" 3 4
void __attribute__((__cdecl__)) tzset (void);

void __attribute__((__cdecl__)) _tzset_r (struct _reent *);

typedef struct __tzrule_struct
{
  char ch;
  int m;
  int n;
  int d;
  int s;
  time_t change;
  long offset;
} __tzrule_type;

typedef struct __tzinfo_struct
{
  int __tznorth;
  int __tzyear;
  __tzrule_type __tzrule[2];
} __tzinfo_type;

__tzinfo_type *__attribute__((__cdecl__)) __gettzinfo (void);
# 154 "/usr/include/time.h" 3 4
extern __attribute__((dllimport)) long _timezone;
extern __attribute__((dllimport)) int _daylight;


extern __attribute__((dllimport)) char *_tzname[2];
# 167 "/usr/include/time.h" 3 4
}





# 1 "/usr/include/cygwin/time.h" 1 3 4
# 12 "/usr/include/cygwin/time.h" 3 4
extern "C"
{



int __attribute__((__cdecl__)) clock_setres (clockid_t, struct timespec *);


time_t __attribute__((__cdecl__)) timelocal (struct tm *);
time_t __attribute__((__cdecl__)) timegm (struct tm *);




extern int stime (const time_t *);



extern int daylight __asm__ ( "_daylight");


extern long timezone __asm__ ( "_timezone");





}
# 174 "/usr/include/time.h" 2 3 4







extern "C" {




int __attribute__((__cdecl__)) clock_settime (clockid_t clock_id, const struct timespec *tp);
int __attribute__((__cdecl__)) clock_gettime (clockid_t clock_id, struct timespec *tp);
int __attribute__((__cdecl__)) clock_getres (clockid_t clock_id, struct timespec *res);



int __attribute__((__cdecl__)) timer_create (clockid_t clock_id, struct sigevent * evp, timer_t * timerid)


                              ;



int __attribute__((__cdecl__)) timer_delete (timer_t timerid);



int __attribute__((__cdecl__)) timer_settime (timer_t timerid, int flags, const struct itimerspec * value, struct itimerspec * ovalue)


                                       ;
int __attribute__((__cdecl__)) timer_gettime (timer_t timerid, struct itimerspec *value);
int __attribute__((__cdecl__)) timer_getoverrun (timer_t timerid);



int __attribute__((__cdecl__)) nanosleep (const struct timespec *rqtp, struct timespec *rmtp);


}






extern "C" {


int __attribute__((__cdecl__)) clock_nanosleep (clockid_t clock_id, int flags, const struct timespec *rqtp, struct timespec *rmtp)

                          ;


}





extern "C" {
# 300 "/usr/include/time.h" 3 4
int __attribute__((__cdecl__)) clock_getcpuclockid (pid_t pid, clockid_t *clock_id);







int __attribute__((__cdecl__)) clock_setenable_attr (clockid_t clock_id, int attr);
int __attribute__((__cdecl__)) clock_getenable_attr (clockid_t clock_id, int *attr);




}
# 15 "/usr/include/pthread.h" 2 3 4





extern "C"
{
# 65 "/usr/include/pthread.h" 3 4
int pthread_atfork (void (*)(void), void (*)(void), void (*)(void));


int pthread_attr_destroy (pthread_attr_t *);
int pthread_attr_getdetachstate (const pthread_attr_t *, int *);
int pthread_attr_getguardsize (const pthread_attr_t *, size_t *);
int pthread_attr_getinheritsched (const pthread_attr_t *, int *);
int pthread_attr_getschedparam (const pthread_attr_t *, struct sched_param *);
int pthread_attr_getschedpolicy (const pthread_attr_t *, int *);
int pthread_attr_getscope (const pthread_attr_t *, int *);
int pthread_attr_init (pthread_attr_t *);
int pthread_attr_setdetachstate (pthread_attr_t *, int);
int pthread_attr_setguardsize (pthread_attr_t *, size_t);
int pthread_attr_setinheritsched (pthread_attr_t *, int);
int pthread_attr_setschedparam (pthread_attr_t *, const struct sched_param *);
int pthread_attr_setschedpolicy (pthread_attr_t *, int);
int pthread_attr_setscope (pthread_attr_t *, int);


int pthread_attr_getstack (const pthread_attr_t *, void **, size_t *);
int pthread_attr_setstack (pthread_attr_t *, void *, size_t);







int pthread_attr_getstacksize (const pthread_attr_t *, size_t *);
int pthread_attr_setstacksize (pthread_attr_t *, size_t);

int pthread_cancel (pthread_t);





typedef void (*__cleanup_routine_type) (void *);
typedef struct _pthread_cleanup_handler
{
  __cleanup_routine_type function;
  void *arg;
  struct _pthread_cleanup_handler *next;
} __pthread_cleanup_handler;

void _pthread_cleanup_push (__pthread_cleanup_handler *handler);
void _pthread_cleanup_pop (int execute);







int pthread_cond_broadcast (pthread_cond_t *);
int pthread_cond_destroy (pthread_cond_t *);
int pthread_cond_init (pthread_cond_t *, const pthread_condattr_t *);
int pthread_cond_signal (pthread_cond_t *);
int pthread_cond_timedwait (pthread_cond_t *,
       pthread_mutex_t *, const struct timespec *);
int pthread_cond_wait (pthread_cond_t *, pthread_mutex_t *);
int pthread_condattr_destroy (pthread_condattr_t *);
int pthread_condattr_getclock (const pthread_condattr_t *, clockid_t *);
int pthread_condattr_getpshared (const pthread_condattr_t *, int *);
int pthread_condattr_init (pthread_condattr_t *);
int pthread_condattr_setclock (pthread_condattr_t *, clockid_t);
int pthread_condattr_setpshared (pthread_condattr_t *, int);



int pthread_barrierattr_init (pthread_barrierattr_t *);
int pthread_barrierattr_setpshared (pthread_barrierattr_t *, int);
int pthread_barrierattr_getpshared (const pthread_barrierattr_t *, int *);
int pthread_barrierattr_destroy (pthread_barrierattr_t *);
int pthread_barrier_init (pthread_barrier_t *,
                          const pthread_barrierattr_t *, unsigned);
int pthread_barrier_destroy (pthread_barrier_t *);
int pthread_barrier_wait (pthread_barrier_t *);



int pthread_create (pthread_t *, const pthread_attr_t *,
      void *(*)(void *), void *);
int pthread_detach (pthread_t);
int pthread_equal (pthread_t, pthread_t);
void pthread_exit (void *) __attribute__ ((__noreturn__));

int pthread_getcpuclockid (pthread_t, clockid_t *);

int pthread_getschedparam (pthread_t, int *, struct sched_param *);
void *pthread_getspecific (pthread_key_t);
int pthread_join (pthread_t, void **);
int pthread_key_create (pthread_key_t *, void (*)(void *));
int pthread_key_delete (pthread_key_t);


int pthread_mutex_destroy (pthread_mutex_t *);
int pthread_mutex_getprioceiling (const pthread_mutex_t *, int *);
int pthread_mutex_init (pthread_mutex_t *, const pthread_mutexattr_t *);
int pthread_mutex_lock (pthread_mutex_t *);
int pthread_mutex_setprioceiling (pthread_mutex_t *, int, int *);
int pthread_mutex_trylock (pthread_mutex_t *);
int pthread_mutex_unlock (pthread_mutex_t *);
int pthread_mutexattr_destroy (pthread_mutexattr_t *);
int pthread_mutexattr_getprioceiling (const pthread_mutexattr_t *, int *);
int pthread_mutexattr_getprotocol (const pthread_mutexattr_t *, int *);
int pthread_mutexattr_getpshared (const pthread_mutexattr_t *, int *);
int pthread_mutexattr_gettype (const pthread_mutexattr_t *, int *);
int pthread_mutexattr_init (pthread_mutexattr_t *);
int pthread_mutexattr_setprioceiling (pthread_mutexattr_t *, int);
int pthread_mutexattr_setprotocol (pthread_mutexattr_t *, int);
int pthread_mutexattr_setpshared (pthread_mutexattr_t *, int);
int pthread_mutexattr_settype (pthread_mutexattr_t *, int);



int pthread_spin_destroy (pthread_spinlock_t *);
int pthread_spin_init (pthread_spinlock_t *, int);
int pthread_spin_lock (pthread_spinlock_t *);
int pthread_spin_trylock (pthread_spinlock_t *);
int pthread_spin_unlock (pthread_spinlock_t *);




int pthread_rwlock_destroy (pthread_rwlock_t *rwlock);
int pthread_rwlock_init (pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *attr);
int pthread_rwlock_rdlock (pthread_rwlock_t *rwlock);
int pthread_rwlock_tryrdlock (pthread_rwlock_t *rwlock);
int pthread_rwlock_wrlock (pthread_rwlock_t *rwlock);
int pthread_rwlock_trywrlock (pthread_rwlock_t *rwlock);
int pthread_rwlock_unlock (pthread_rwlock_t *rwlock);
int pthread_rwlockattr_init (pthread_rwlockattr_t *rwlockattr);
int pthread_rwlockattr_getpshared (const pthread_rwlockattr_t *attr,
       int *pshared);
int pthread_rwlockattr_setpshared (pthread_rwlockattr_t *attr, int pshared);
int pthread_rwlockattr_destroy (pthread_rwlockattr_t *rwlockattr);


int pthread_once (pthread_once_t *, void (*)(void));
# 213 "/usr/include/pthread.h" 3 4
pthread_t pthread_self (void);
int pthread_setcancelstate (int, int *);
int pthread_setcanceltype (int, int *);
int pthread_setschedparam (pthread_t, int, const struct sched_param *);
int pthread_setschedprio (pthread_t, int);
int pthread_setspecific (pthread_key_t, const void *);
void pthread_testcancel (void);
# 231 "/usr/include/pthread.h" 3 4
int pthread_suspend (pthread_t);
int pthread_continue (pthread_t);



}
# 36 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/gthr-default.h" 2 3
# 47 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/gthr-default.h" 3
typedef pthread_t __gthread_t;
typedef pthread_key_t __gthread_key_t;
typedef pthread_once_t __gthread_once_t;
typedef pthread_mutex_t __gthread_mutex_t;
typedef pthread_mutex_t __gthread_recursive_mutex_t;
typedef pthread_cond_t __gthread_cond_t;
typedef struct timespec __gthread_time_t;
# 101 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/gthr-default.h" 3



































# 298 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/gthr-default.h" 3
static inline int
__gthread_active_p (void)
{
  return 1;
}
# 658 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/gthr-default.h" 3
static inline int
__gthread_create (__gthread_t *__threadid, void *(*__func) (void*),
    void *__args)
{
  return pthread_create (__threadid, __null, __func, __args);
}

static inline int
__gthread_join (__gthread_t __threadid, void **__value_ptr)
{
  return pthread_join (__threadid, __value_ptr);
}

static inline int
__gthread_detach (__gthread_t __threadid)
{
  return pthread_detach (__threadid);
}

static inline int
__gthread_equal (__gthread_t __t1, __gthread_t __t2)
{
  return pthread_equal (__t1, __t2);
}

static inline __gthread_t
__gthread_self (void)
{
  return pthread_self ();
}

static inline int
__gthread_yield (void)
{
  return sched_yield ();
}

static inline int
__gthread_once (__gthread_once_t *__once, void (*__func) (void))
{
  if (__gthread_active_p ())
    return pthread_once (__once, __func);
  else
    return -1;
}

static inline int
__gthread_key_create (__gthread_key_t *__key, void (*__dtor) (void *))
{
  return pthread_key_create (__key, __dtor);
}

static inline int
__gthread_key_delete (__gthread_key_t __key)
{
  return pthread_key_delete (__key);
}

static inline void *
__gthread_getspecific (__gthread_key_t __key)
{
  return pthread_getspecific (__key);
}

static inline int
__gthread_setspecific (__gthread_key_t __key, const void *__ptr)
{
  return pthread_setspecific (__key, __ptr);
}

static inline void
__gthread_mutex_init_function (__gthread_mutex_t *__mutex)
{
  if (__gthread_active_p ())
    pthread_mutex_init (__mutex, __null);
}

static inline int
__gthread_mutex_destroy (__gthread_mutex_t *__mutex)
{
  if (__gthread_active_p ())
    return pthread_mutex_destroy (__mutex);
  else
    return 0;
}

static inline int
__gthread_mutex_lock (__gthread_mutex_t *__mutex)
{
  if (__gthread_active_p ())
    return pthread_mutex_lock (__mutex);
  else
    return 0;
}

static inline int
__gthread_mutex_trylock (__gthread_mutex_t *__mutex)
{
  if (__gthread_active_p ())
    return pthread_mutex_trylock (__mutex);
  else
    return 0;
}
# 774 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/gthr-default.h" 3
static inline int
__gthread_mutex_unlock (__gthread_mutex_t *__mutex)
{
  if (__gthread_active_p ())
    return pthread_mutex_unlock (__mutex);
  else
    return 0;
}
# 807 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/gthr-default.h" 3
static inline int
__gthread_recursive_mutex_lock (__gthread_recursive_mutex_t *__mutex)
{
  return __gthread_mutex_lock (__mutex);
}

static inline int
__gthread_recursive_mutex_trylock (__gthread_recursive_mutex_t *__mutex)
{
  return __gthread_mutex_trylock (__mutex);
}
# 828 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/gthr-default.h" 3
static inline int
__gthread_recursive_mutex_unlock (__gthread_recursive_mutex_t *__mutex)
{
  return __gthread_mutex_unlock (__mutex);
}

static inline int
__gthread_recursive_mutex_destroy (__gthread_recursive_mutex_t *__mutex)
{
  return __gthread_mutex_destroy (__mutex);
}
# 849 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/gthr-default.h" 3
static inline int
__gthread_cond_broadcast (__gthread_cond_t *__cond)
{
  return pthread_cond_broadcast (__cond);
}

static inline int
__gthread_cond_signal (__gthread_cond_t *__cond)
{
  return pthread_cond_signal (__cond);
}

static inline int
__gthread_cond_wait (__gthread_cond_t *__cond, __gthread_mutex_t *__mutex)
{
  return pthread_cond_wait (__cond, __mutex);
}

static inline int
__gthread_cond_timedwait (__gthread_cond_t *__cond, __gthread_mutex_t *__mutex,
     const __gthread_time_t *__abs_timeout)
{
  return pthread_cond_timedwait (__cond, __mutex, __abs_timeout);
}

static inline int
__gthread_cond_wait_recursive (__gthread_cond_t *__cond,
          __gthread_recursive_mutex_t *__mutex)
{
  return __gthread_cond_wait (__cond, __mutex);
}

static inline int
__gthread_cond_destroy (__gthread_cond_t* __cond)
{
  return pthread_cond_destroy (__cond);
}
# 149 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/gthr.h" 2 3


#pragma GCC visibility pop
# 36 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ext/atomicity.h" 2 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/atomic_word.h" 1 3
# 32 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/atomic_word.h" 3
typedef int _Atomic_word;
# 37 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ext/atomicity.h" 2 3

namespace __gnu_cxx
{







  static inline _Atomic_word
  __exchange_and_add(volatile _Atomic_word* __mem, int __val)
  { return __atomic_fetch_add(__mem, __val, 4); }

  static inline void
  __atomic_add(volatile _Atomic_word* __mem, int __val)
  { __atomic_fetch_add(__mem, __val, 4); }
# 64 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ext/atomicity.h" 3
  static inline _Atomic_word
  __exchange_and_add_single(_Atomic_word* __mem, int __val)
  {
    _Atomic_word __result = *__mem;
    *__mem += __val;
    return __result;
  }

  static inline void
  __atomic_add_single(_Atomic_word* __mem, int __val)
  { *__mem += __val; }

  static inline _Atomic_word
  __attribute__ ((__unused__))
  __exchange_and_add_dispatch(_Atomic_word* __mem, int __val)
  {

    if (__gthread_active_p())
      return __exchange_and_add(__mem, __val);
    else
      return __exchange_and_add_single(__mem, __val);



  }

  static inline void
  __attribute__ ((__unused__))
  __atomic_add_dispatch(_Atomic_word* __mem, int __val)
  {

    if (__gthread_active_p())
      __atomic_add(__mem, __val);
    else
      __atomic_add_single(__mem, __val);



  }


}
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 2 3

# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 1 3
# 37 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3
       
# 38 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3


# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/string" 1 3
# 36 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/string" 3
       
# 37 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/string" 3







# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ostream_insert.h" 1 3
# 33 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ostream_insert.h" 3
       
# 34 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ostream_insert.h" 3


# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/cxxabi_forced.h" 1 3
# 34 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/cxxabi_forced.h" 3
       
# 35 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/cxxabi_forced.h" 3

#pragma GCC visibility push(default)


namespace __cxxabiv1
{







  class __forced_unwind
  {
    virtual ~__forced_unwind() throw();


    virtual void __pure_dummy() = 0;
  };
}


#pragma GCC visibility pop
# 37 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ostream_insert.h" 2 3

namespace std
{


  template<typename _CharT, typename _Traits>
    inline void
    __ostream_write(basic_ostream<_CharT, _Traits>& __out,
      const _CharT* __s, streamsize __n)
    {
      typedef basic_ostream<_CharT, _Traits> __ostream_type;
      typedef typename __ostream_type::ios_base __ios_base;

      const streamsize __put = __out.rdbuf()->sputn(__s, __n);
      if (__put != __n)
 __out.setstate(__ios_base::badbit);
    }

  template<typename _CharT, typename _Traits>
    inline void
    __ostream_fill(basic_ostream<_CharT, _Traits>& __out, streamsize __n)
    {
      typedef basic_ostream<_CharT, _Traits> __ostream_type;
      typedef typename __ostream_type::ios_base __ios_base;

      const _CharT __c = __out.fill();
      for (; __n > 0; --__n)
 {
   const typename _Traits::int_type __put = __out.rdbuf()->sputc(__c);
   if (_Traits::eq_int_type(__put, _Traits::eof()))
     {
       __out.setstate(__ios_base::badbit);
       break;
     }
 }
    }

  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    __ostream_insert(basic_ostream<_CharT, _Traits>& __out,
       const _CharT* __s, streamsize __n)
    {
      typedef basic_ostream<_CharT, _Traits> __ostream_type;
      typedef typename __ostream_type::ios_base __ios_base;

      typename __ostream_type::sentry __cerb(__out);
      if (__cerb)
 {
   try
     {
       const streamsize __w = __out.width();
       if (__w > __n)
  {
    const bool __left = ((__out.flags()
     & __ios_base::adjustfield)
           == __ios_base::left);
    if (!__left)
      __ostream_fill(__out, __w - __n);
    if (__out.good())
      __ostream_write(__out, __s, __n);
    if (__left && __out.good())
      __ostream_fill(__out, __w - __n);
  }
       else
  __ostream_write(__out, __s, __n);
       __out.width(0);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       __out._M_setstate(__ios_base::badbit);
       throw;
     }
   catch(...)
     { __out._M_setstate(__ios_base::badbit); }
 }
      return __out;
    }




  extern template ostream& __ostream_insert(ostream&, const char*, streamsize);


  extern template wostream& __ostream_insert(wostream&, const wchar_t*,
          streamsize);




}
# 45 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/string" 2 3



# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_function.h" 1 3
# 63 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_function.h" 3
namespace std
{

# 104 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_function.h" 3
  template<typename _Arg, typename _Result>
    struct unary_function
    {

      typedef _Arg argument_type;


      typedef _Result result_type;
    };




  template<typename _Arg1, typename _Arg2, typename _Result>
    struct binary_function
    {

      typedef _Arg1 first_argument_type;


      typedef _Arg2 second_argument_type;


      typedef _Result result_type;
    };
# 166 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_function.h" 3
  template<typename _Tp>
    struct plus : public binary_function<_Tp, _Tp, _Tp>
    {
     
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x + __y; }
    };


  template<typename _Tp>
    struct minus : public binary_function<_Tp, _Tp, _Tp>
    {
     
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x - __y; }
    };


  template<typename _Tp>
    struct multiplies : public binary_function<_Tp, _Tp, _Tp>
    {
     
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x * __y; }
    };


  template<typename _Tp>
    struct divides : public binary_function<_Tp, _Tp, _Tp>
    {
     
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x / __y; }
    };


  template<typename _Tp>
    struct modulus : public binary_function<_Tp, _Tp, _Tp>
    {
     
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x % __y; }
    };


  template<typename _Tp>
    struct negate : public unary_function<_Tp, _Tp>
    {
     
      _Tp
      operator()(const _Tp& __x) const
      { return -__x; }
    };
# 351 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_function.h" 3
  template<typename _Tp>
    struct equal_to : public binary_function<_Tp, _Tp, bool>
    {
     
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x == __y; }
    };


  template<typename _Tp>
    struct not_equal_to : public binary_function<_Tp, _Tp, bool>
    {
     
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x != __y; }
    };


  template<typename _Tp>
    struct greater : public binary_function<_Tp, _Tp, bool>
    {
     
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x > __y; }
    };


  template<typename _Tp>
    struct less : public binary_function<_Tp, _Tp, bool>
    {
     
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x < __y; }
    };


  template<typename _Tp>
    struct greater_equal : public binary_function<_Tp, _Tp, bool>
    {
     
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x >= __y; }
    };


  template<typename _Tp>
    struct less_equal : public binary_function<_Tp, _Tp, bool>
    {
     
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x <= __y; }
    };
# 524 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_function.h" 3
  template<typename _Tp>
    struct logical_and : public binary_function<_Tp, _Tp, bool>
    {
     
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x && __y; }
    };


  template<typename _Tp>
    struct logical_or : public binary_function<_Tp, _Tp, bool>
    {
     
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x || __y; }
    };


  template<typename _Tp>
    struct logical_not : public unary_function<_Tp, bool>
    {
     
      bool
      operator()(const _Tp& __x) const
      { return !__x; }
    };
# 617 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_function.h" 3
  template<typename _Tp>
    struct bit_and : public binary_function<_Tp, _Tp, _Tp>
    {
     
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x & __y; }
    };

  template<typename _Tp>
    struct bit_or : public binary_function<_Tp, _Tp, _Tp>
    {
     
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x | __y; }
    };

  template<typename _Tp>
    struct bit_xor : public binary_function<_Tp, _Tp, _Tp>
    {
     
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x ^ __y; }
    };

  template<typename _Tp>
    struct bit_not : public unary_function<_Tp, _Tp>
    {
   
      _Tp
      operator()(const _Tp& __x) const
      { return ~__x; }
    };
# 741 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_function.h" 3
  template<typename _Predicate>
    class unary_negate
    : public unary_function<typename _Predicate::argument_type, bool>
    {
    protected:
      _Predicate _M_pred;

    public:
     
      explicit
      unary_negate(const _Predicate& __x) : _M_pred(__x) { }

     
      bool
      operator()(const typename _Predicate::argument_type& __x) const
      { return !_M_pred(__x); }
    };


  template<typename _Predicate>
   
    inline unary_negate<_Predicate>
    not1(const _Predicate& __pred)
    { return unary_negate<_Predicate>(__pred); }


  template<typename _Predicate>
    class binary_negate
    : public binary_function<typename _Predicate::first_argument_type,
        typename _Predicate::second_argument_type, bool>
    {
    protected:
      _Predicate _M_pred;

    public:
     
      explicit
      binary_negate(const _Predicate& __x) : _M_pred(__x) { }

     
      bool
      operator()(const typename _Predicate::first_argument_type& __x,
   const typename _Predicate::second_argument_type& __y) const
      { return !_M_pred(__x, __y); }
    };


  template<typename _Predicate>
   
    inline binary_negate<_Predicate>
    not2(const _Predicate& __pred)
    { return binary_negate<_Predicate>(__pred); }
# 818 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_function.h" 3
  template<typename _Arg, typename _Result>
    class pointer_to_unary_function : public unary_function<_Arg, _Result>
    {
    protected:
      _Result (*_M_ptr)(_Arg);

    public:
      pointer_to_unary_function() { }

      explicit
      pointer_to_unary_function(_Result (*__x)(_Arg))
      : _M_ptr(__x) { }

      _Result
      operator()(_Arg __x) const
      { return _M_ptr(__x); }
    };


  template<typename _Arg, typename _Result>
    inline pointer_to_unary_function<_Arg, _Result>
    ptr_fun(_Result (*__x)(_Arg))
    { return pointer_to_unary_function<_Arg, _Result>(__x); }


  template<typename _Arg1, typename _Arg2, typename _Result>
    class pointer_to_binary_function
    : public binary_function<_Arg1, _Arg2, _Result>
    {
    protected:
      _Result (*_M_ptr)(_Arg1, _Arg2);

    public:
      pointer_to_binary_function() { }

      explicit
      pointer_to_binary_function(_Result (*__x)(_Arg1, _Arg2))
      : _M_ptr(__x) { }

      _Result
      operator()(_Arg1 __x, _Arg2 __y) const
      { return _M_ptr(__x, __y); }
    };


  template<typename _Arg1, typename _Arg2, typename _Result>
    inline pointer_to_binary_function<_Arg1, _Arg2, _Result>
    ptr_fun(_Result (*__x)(_Arg1, _Arg2))
    { return pointer_to_binary_function<_Arg1, _Arg2, _Result>(__x); }


  template<typename _Tp>
    struct _Identity
    : public unary_function<_Tp,_Tp>
    {
      _Tp&
      operator()(_Tp& __x) const
      { return __x; }

      const _Tp&
      operator()(const _Tp& __x) const
      { return __x; }
    };

  template<typename _Pair>
    struct _Select1st
    : public unary_function<_Pair, typename _Pair::first_type>
    {
      typename _Pair::first_type&
      operator()(_Pair& __x) const
      { return __x.first; }

      const typename _Pair::first_type&
      operator()(const _Pair& __x) const
      { return __x.first; }
# 905 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_function.h" 3
    };

  template<typename _Pair>
    struct _Select2nd
    : public unary_function<_Pair, typename _Pair::second_type>
    {
      typename _Pair::second_type&
      operator()(_Pair& __x) const
      { return __x.second; }

      const typename _Pair::second_type&
      operator()(const _Pair& __x) const
      { return __x.second; }
    };
# 938 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_function.h" 3
  template<typename _Ret, typename _Tp>
    class mem_fun_t : public unary_function<_Tp*, _Ret>
    {
    public:
      explicit
      mem_fun_t(_Ret (_Tp::*__pf)())
      : _M_f(__pf) { }

      _Ret
      operator()(_Tp* __p) const
      { return (__p->*_M_f)(); }

    private:
      _Ret (_Tp::*_M_f)();
    };



  template<typename _Ret, typename _Tp>
    class const_mem_fun_t : public unary_function<const _Tp*, _Ret>
    {
    public:
      explicit
      const_mem_fun_t(_Ret (_Tp::*__pf)() const)
      : _M_f(__pf) { }

      _Ret
      operator()(const _Tp* __p) const
      { return (__p->*_M_f)(); }

    private:
      _Ret (_Tp::*_M_f)() const;
    };



  template<typename _Ret, typename _Tp>
    class mem_fun_ref_t : public unary_function<_Tp, _Ret>
    {
    public:
      explicit
      mem_fun_ref_t(_Ret (_Tp::*__pf)())
      : _M_f(__pf) { }

      _Ret
      operator()(_Tp& __r) const
      { return (__r.*_M_f)(); }

    private:
      _Ret (_Tp::*_M_f)();
  };



  template<typename _Ret, typename _Tp>
    class const_mem_fun_ref_t : public unary_function<_Tp, _Ret>
    {
    public:
      explicit
      const_mem_fun_ref_t(_Ret (_Tp::*__pf)() const)
      : _M_f(__pf) { }

      _Ret
      operator()(const _Tp& __r) const
      { return (__r.*_M_f)(); }

    private:
      _Ret (_Tp::*_M_f)() const;
    };



  template<typename _Ret, typename _Tp, typename _Arg>
    class mem_fun1_t : public binary_function<_Tp*, _Arg, _Ret>
    {
    public:
      explicit
      mem_fun1_t(_Ret (_Tp::*__pf)(_Arg))
      : _M_f(__pf) { }

      _Ret
      operator()(_Tp* __p, _Arg __x) const
      { return (__p->*_M_f)(__x); }

    private:
      _Ret (_Tp::*_M_f)(_Arg);
    };



  template<typename _Ret, typename _Tp, typename _Arg>
    class const_mem_fun1_t : public binary_function<const _Tp*, _Arg, _Ret>
    {
    public:
      explicit
      const_mem_fun1_t(_Ret (_Tp::*__pf)(_Arg) const)
      : _M_f(__pf) { }

      _Ret
      operator()(const _Tp* __p, _Arg __x) const
      { return (__p->*_M_f)(__x); }

    private:
      _Ret (_Tp::*_M_f)(_Arg) const;
    };



  template<typename _Ret, typename _Tp, typename _Arg>
    class mem_fun1_ref_t : public binary_function<_Tp, _Arg, _Ret>
    {
    public:
      explicit
      mem_fun1_ref_t(_Ret (_Tp::*__pf)(_Arg))
      : _M_f(__pf) { }

      _Ret
      operator()(_Tp& __r, _Arg __x) const
      { return (__r.*_M_f)(__x); }

    private:
      _Ret (_Tp::*_M_f)(_Arg);
    };



  template<typename _Ret, typename _Tp, typename _Arg>
    class const_mem_fun1_ref_t : public binary_function<_Tp, _Arg, _Ret>
    {
    public:
      explicit
      const_mem_fun1_ref_t(_Ret (_Tp::*__pf)(_Arg) const)
      : _M_f(__pf) { }

      _Ret
      operator()(const _Tp& __r, _Arg __x) const
      { return (__r.*_M_f)(__x); }

    private:
      _Ret (_Tp::*_M_f)(_Arg) const;
    };



  template<typename _Ret, typename _Tp>
    inline mem_fun_t<_Ret, _Tp>
    mem_fun(_Ret (_Tp::*__f)())
    { return mem_fun_t<_Ret, _Tp>(__f); }

  template<typename _Ret, typename _Tp>
    inline const_mem_fun_t<_Ret, _Tp>
    mem_fun(_Ret (_Tp::*__f)() const)
    { return const_mem_fun_t<_Ret, _Tp>(__f); }

  template<typename _Ret, typename _Tp>
    inline mem_fun_ref_t<_Ret, _Tp>
    mem_fun_ref(_Ret (_Tp::*__f)())
    { return mem_fun_ref_t<_Ret, _Tp>(__f); }

  template<typename _Ret, typename _Tp>
    inline const_mem_fun_ref_t<_Ret, _Tp>
    mem_fun_ref(_Ret (_Tp::*__f)() const)
    { return const_mem_fun_ref_t<_Ret, _Tp>(__f); }

  template<typename _Ret, typename _Tp, typename _Arg>
    inline mem_fun1_t<_Ret, _Tp, _Arg>
    mem_fun(_Ret (_Tp::*__f)(_Arg))
    { return mem_fun1_t<_Ret, _Tp, _Arg>(__f); }

  template<typename _Ret, typename _Tp, typename _Arg>
    inline const_mem_fun1_t<_Ret, _Tp, _Arg>
    mem_fun(_Ret (_Tp::*__f)(_Arg) const)
    { return const_mem_fun1_t<_Ret, _Tp, _Arg>(__f); }

  template<typename _Ret, typename _Tp, typename _Arg>
    inline mem_fun1_ref_t<_Ret, _Tp, _Arg>
    mem_fun_ref(_Ret (_Tp::*__f)(_Arg))
    { return mem_fun1_ref_t<_Ret, _Tp, _Arg>(__f); }

  template<typename _Ret, typename _Tp, typename _Arg>
    inline const_mem_fun1_ref_t<_Ret, _Tp, _Arg>
    mem_fun_ref(_Ret (_Tp::*__f)(_Arg) const)
    { return const_mem_fun1_ref_t<_Ret, _Tp, _Arg>(__f); }




}


# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/backward/binders.h" 1 3
# 60 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/backward/binders.h" 3
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

namespace std
{

# 107 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/backward/binders.h" 3
  template<typename _Operation>
    class binder1st
    : public unary_function<typename _Operation::second_argument_type,
       typename _Operation::result_type>
    {
    protected:
      _Operation op;
      typename _Operation::first_argument_type value;

    public:
      binder1st(const _Operation& __x,
  const typename _Operation::first_argument_type& __y)
      : op(__x), value(__y) { }

      typename _Operation::result_type
      operator()(const typename _Operation::second_argument_type& __x) const
      { return op(value, __x); }



      typename _Operation::result_type
      operator()(typename _Operation::second_argument_type& __x) const
      { return op(value, __x); }
    } ;


  template<typename _Operation, typename _Tp>
    inline binder1st<_Operation>
    bind1st(const _Operation& __fn, const _Tp& __x)
    {
      typedef typename _Operation::first_argument_type _Arg1_type;
      return binder1st<_Operation>(__fn, _Arg1_type(__x));
    }


  template<typename _Operation>
    class binder2nd
    : public unary_function<typename _Operation::first_argument_type,
       typename _Operation::result_type>
    {
    protected:
      _Operation op;
      typename _Operation::second_argument_type value;

    public:
      binder2nd(const _Operation& __x,
  const typename _Operation::second_argument_type& __y)
      : op(__x), value(__y) { }

      typename _Operation::result_type
      operator()(const typename _Operation::first_argument_type& __x) const
      { return op(__x, value); }



      typename _Operation::result_type
      operator()(typename _Operation::first_argument_type& __x) const
      { return op(__x, value); }
    } ;


  template<typename _Operation, typename _Tp>
    inline binder2nd<_Operation>
    bind2nd(const _Operation& __fn, const _Tp& __x)
    {
      typedef typename _Operation::second_argument_type _Arg2_type;
      return binder2nd<_Operation>(__fn, _Arg2_type(__x));
    }



}

#pragma GCC diagnostic pop
# 1129 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_function.h" 2 3
# 49 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/string" 2 3


# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/range_access.h" 1 3
# 33 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/range_access.h" 3
       
# 34 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/range_access.h" 3
# 52 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/string" 2 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 1 3
# 37 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
       
# 38 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
# 46 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
namespace std
{

# 2508 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    class basic_string
    {
      typedef typename _Alloc::template rebind<_CharT>::other _CharT_alloc_type;


    public:
      typedef _Traits traits_type;
      typedef typename _Traits::char_type value_type;
      typedef _Alloc allocator_type;
      typedef typename _CharT_alloc_type::size_type size_type;
      typedef typename _CharT_alloc_type::difference_type difference_type;
      typedef typename _CharT_alloc_type::reference reference;
      typedef typename _CharT_alloc_type::const_reference const_reference;
      typedef typename _CharT_alloc_type::pointer pointer;
      typedef typename _CharT_alloc_type::const_pointer const_pointer;
      typedef __gnu_cxx::__normal_iterator<pointer, basic_string> iterator;
      typedef __gnu_cxx::__normal_iterator<const_pointer, basic_string>
                                                            const_iterator;
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
      typedef std::reverse_iterator<iterator> reverse_iterator;

    private:
# 2545 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      struct _Rep_base
      {
 size_type _M_length;
 size_type _M_capacity;
 _Atomic_word _M_refcount;
      };

      struct _Rep : _Rep_base
      {

 typedef typename _Alloc::template rebind<char>::other _Raw_bytes_alloc;
# 2570 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
 static const size_type _S_max_size;
 static const _CharT _S_terminal;



        static size_type _S_empty_rep_storage[];

        static _Rep&
        _S_empty_rep()
        {



   void* __p = reinterpret_cast<void*>(&_S_empty_rep_storage);
   return *reinterpret_cast<_Rep*>(__p);
 }

        bool
 _M_is_leaked() const
        { return this->_M_refcount < 0; }

        bool
 _M_is_shared() const
        { return this->_M_refcount > 0; }

        void
 _M_set_leaked()
        { this->_M_refcount = -1; }

        void
 _M_set_sharable()
        { this->_M_refcount = 0; }

 void
 _M_set_length_and_sharable(size_type __n)
 {

   if (__builtin_expect(this != &_S_empty_rep(), false))

     {
       this->_M_set_sharable();
       this->_M_length = __n;
       traits_type::assign(this->_M_refdata()[__n], _S_terminal);


     }
 }

 _CharT*
 _M_refdata() throw()
 { return reinterpret_cast<_CharT*>(this + 1); }

 _CharT*
 _M_grab(const _Alloc& __alloc1, const _Alloc& __alloc2)
 {
   return (!_M_is_leaked() && __alloc1 == __alloc2)
           ? _M_refcopy() : _M_clone(__alloc1);
 }


 static _Rep*
 _S_create(size_type, size_type, const _Alloc&);

 void
 _M_dispose(const _Alloc& __a)
 {

   if (__builtin_expect(this != &_S_empty_rep(), false))

     {

       ;
       if (__gnu_cxx::__exchange_and_add_dispatch(&this->_M_refcount,
        -1) <= 0)
  {
    ;
    _M_destroy(__a);
  }
     }
 }

 void
 _M_destroy(const _Alloc&) throw();

 _CharT*
 _M_refcopy() throw()
 {

   if (__builtin_expect(this != &_S_empty_rep(), false))

            __gnu_cxx::__atomic_add_dispatch(&this->_M_refcount, 1);
   return _M_refdata();
 }

 _CharT*
 _M_clone(const _Alloc&, size_type __res = 0);
      };


      struct _Alloc_hider : _Alloc
      {
 _Alloc_hider(_CharT* __dat, const _Alloc& __a)
 : _Alloc(__a), _M_p(__dat) { }

 _CharT* _M_p;
      };

    public:




      static const size_type npos = static_cast<size_type>(-1);

    private:

      mutable _Alloc_hider _M_dataplus;

      _CharT*
      _M_data() const
      { return _M_dataplus._M_p; }

      _CharT*
      _M_data(_CharT* __p)
      { return (_M_dataplus._M_p = __p); }

      _Rep*
      _M_rep() const
      { return &((reinterpret_cast<_Rep*> (_M_data()))[-1]); }



      iterator
      _M_ibegin() const
      { return iterator(_M_data()); }

      iterator
      _M_iend() const
      { return iterator(_M_data() + this->size()); }

      void
      _M_leak()
      {
 if (!_M_rep()->_M_is_leaked())
   _M_leak_hard();
      }

      size_type
      _M_check(size_type __pos, const char* __s) const
      {
 if (__pos > this->size())
   __throw_out_of_range_fmt(("%s: __pos (which is %zu) > " "this->size() (which is %zu)")
                                         ,
       __s, __pos, this->size());
 return __pos;
      }

      void
      _M_check_length(size_type __n1, size_type __n2, const char* __s) const
      {
 if (this->max_size() - (this->size() - __n1) < __n2)
   __throw_length_error((__s));
      }


      size_type
      _M_limit(size_type __pos, size_type __off) const
      {
 const bool __testoff = __off < this->size() - __pos;
 return __testoff ? __off : this->size() - __pos;
      }


      bool
      _M_disjunct(const _CharT* __s) const
      {
 return (less<const _CharT*>()(__s, _M_data())
  || less<const _CharT*>()(_M_data() + this->size(), __s));
      }



      static void
      _M_copy(_CharT* __d, const _CharT* __s, size_type __n)
      {
 if (__n == 1)
   traits_type::assign(*__d, *__s);
 else
   traits_type::copy(__d, __s, __n);
      }

      static void
      _M_move(_CharT* __d, const _CharT* __s, size_type __n)
      {
 if (__n == 1)
   traits_type::assign(*__d, *__s);
 else
   traits_type::move(__d, __s, __n);
      }

      static void
      _M_assign(_CharT* __d, size_type __n, _CharT __c)
      {
 if (__n == 1)
   traits_type::assign(*__d, __c);
 else
   traits_type::assign(__d, __n, __c);
      }



      template<class _Iterator>
        static void
        _S_copy_chars(_CharT* __p, _Iterator __k1, _Iterator __k2)
        {
   for (; __k1 != __k2; ++__k1, ++__p)
     traits_type::assign(*__p, *__k1);
 }

      static void
      _S_copy_chars(_CharT* __p, iterator __k1, iterator __k2)
      { _S_copy_chars(__p, __k1.base(), __k2.base()); }

      static void
      _S_copy_chars(_CharT* __p, const_iterator __k1, const_iterator __k2)
     
      { _S_copy_chars(__p, __k1.base(), __k2.base()); }

      static void
      _S_copy_chars(_CharT* __p, _CharT* __k1, _CharT* __k2)
      { _M_copy(__p, __k1, __k2 - __k1); }

      static void
      _S_copy_chars(_CharT* __p, const _CharT* __k1, const _CharT* __k2)
     
      { _M_copy(__p, __k1, __k2 - __k1); }

      static int
      _S_compare(size_type __n1, size_type __n2)
      {
 const difference_type __d = difference_type(__n1 - __n2);

 if (__d > __gnu_cxx::__numeric_traits<int>::__max)
   return __gnu_cxx::__numeric_traits<int>::__max;
 else if (__d < __gnu_cxx::__numeric_traits<int>::__min)
   return __gnu_cxx::__numeric_traits<int>::__min;
 else
   return int(__d);
      }

      void
      _M_mutate(size_type __pos, size_type __len1, size_type __len2);

      void
      _M_leak_hard();

      static _Rep&
      _S_empty_rep()
      { return _Rep::_S_empty_rep(); }

    public:







      basic_string()

      : _M_dataplus(_S_empty_rep()._M_refdata(), _Alloc()) { }







      explicit
      basic_string(const _Alloc& __a);






      basic_string(const basic_string& __str);






      basic_string(const basic_string& __str, size_type __pos,
     size_type __n = npos);







      basic_string(const basic_string& __str, size_type __pos,
     size_type __n, const _Alloc& __a);
# 2884 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      basic_string(const _CharT* __s, size_type __n,
     const _Alloc& __a = _Alloc());





      basic_string(const _CharT* __s, const _Alloc& __a = _Alloc());






      basic_string(size_type __n, _CharT __c, const _Alloc& __a = _Alloc());
# 2935 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      template<class _InputIterator>
        basic_string(_InputIterator __beg, _InputIterator __end,
       const _Alloc& __a = _Alloc());




      ~basic_string()
      { _M_rep()->_M_dispose(this->get_allocator()); }





      basic_string&
      operator=(const basic_string& __str)
      { return this->assign(__str); }





      basic_string&
      operator=(const _CharT* __s)
      { return this->assign(__s); }
# 2968 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      basic_string&
      operator=(_CharT __c)
      {
 this->assign(1, __c);
 return *this;
      }
# 3009 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      iterator
      begin()
      {
 _M_leak();
 return iterator(_M_data());
      }





      const_iterator
      begin() const
      { return const_iterator(_M_data()); }





      iterator
      end()
      {
 _M_leak();
 return iterator(_M_data() + this->size());
      }





      const_iterator
      end() const
      { return const_iterator(_M_data() + this->size()); }






      reverse_iterator
      rbegin()
      { return reverse_iterator(this->end()); }






      const_reverse_iterator
      rbegin() const
      { return const_reverse_iterator(this->end()); }






      reverse_iterator
      rend()
      { return reverse_iterator(this->begin()); }






      const_reverse_iterator
      rend() const
      { return const_reverse_iterator(this->begin()); }
# 3115 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
    public:



      size_type
      size() const
      { return _M_rep()->_M_length; }



      size_type
      length() const
      { return _M_rep()->_M_length; }


      size_type
      max_size() const
      { return _Rep::_S_max_size; }
# 3144 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      void
      resize(size_type __n, _CharT __c);
# 3157 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      void
      resize(size_type __n)
      { this->resize(__n, _CharT()); }
# 3182 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      size_type
      capacity() const
      { return _M_rep()->_M_capacity; }
# 3203 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      void
      reserve(size_type __res_arg = 0);





      void
      clear()
      { _M_mutate(0, this->size(), 0); }





      bool
      empty() const
      { return this->size() == 0; }
# 3233 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      const_reference
      operator[] (size_type __pos) const
      {
 ;
 return _M_data()[__pos];
      }
# 3250 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      reference
      operator[](size_type __pos)
      {


 ;

 ;
 _M_leak();
 return _M_data()[__pos];
      }
# 3272 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      const_reference
      at(size_type __n) const
      {
 if (__n >= this->size())
   __throw_out_of_range_fmt(("basic_string::at: __n " "(which is %zu) >= this->size() " "(which is %zu)")

                            ,
       __n, this->size());
 return _M_data()[__n];
      }
# 3294 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      reference
      at(size_type __n)
      {
 if (__n >= size())
   __throw_out_of_range_fmt(("basic_string::at: __n " "(which is %zu) >= this->size() " "(which is %zu)")

                            ,
       __n, this->size());
 _M_leak();
 return _M_data()[__n];
      }
# 3346 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      basic_string&
      operator+=(const basic_string& __str)
      { return this->append(__str); }






      basic_string&
      operator+=(const _CharT* __s)
      { return this->append(__s); }






      basic_string&
      operator+=(_CharT __c)
      {
 this->push_back(__c);
 return *this;
      }
# 3387 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      basic_string&
      append(const basic_string& __str);
# 3403 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      basic_string&
      append(const basic_string& __str, size_type __pos, size_type __n);







      basic_string&
      append(const _CharT* __s, size_type __n);






      basic_string&
      append(const _CharT* __s)
      {
 ;
 return this->append(__s, traits_type::length(__s));
      }
# 3435 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      basic_string&
      append(size_type __n, _CharT __c);
# 3457 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      template<class _InputIterator>
        basic_string&
        append(_InputIterator __first, _InputIterator __last)
        { return this->replace(_M_iend(), _M_iend(), __first, __last); }





      void
      push_back(_CharT __c)
      {
 const size_type __len = 1 + this->size();
 if (__len > this->capacity() || _M_rep()->_M_is_shared())
   this->reserve(__len);
 traits_type::assign(_M_data()[this->size()], __c);
 _M_rep()->_M_set_length_and_sharable(__len);
      }






      basic_string&
      assign(const basic_string& __str);
# 3515 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      basic_string&
      assign(const basic_string& __str, size_type __pos, size_type __n)
      { return this->assign(__str._M_data()
       + __str._M_check(__pos, "basic_string::assign"),
       __str._M_limit(__pos, __n)); }
# 3531 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      basic_string&
      assign(const _CharT* __s, size_type __n);
# 3543 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      basic_string&
      assign(const _CharT* __s)
      {
 ;
 return this->assign(__s, traits_type::length(__s));
      }
# 3559 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      basic_string&
      assign(size_type __n, _CharT __c)
      { return _M_replace_aux(size_type(0), this->size(), __n, __c); }
# 3571 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      template<class _InputIterator>
        basic_string&
        assign(_InputIterator __first, _InputIterator __last)
        { return this->replace(_M_ibegin(), _M_iend(), __first, __last); }
# 3600 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      void
      insert(iterator __p, size_type __n, _CharT __c)
      { this->replace(__p, __p, __n, __c); }
# 3616 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      template<class _InputIterator>
        void
        insert(iterator __p, _InputIterator __beg, _InputIterator __end)
        { this->replace(__p, __p, __beg, __end); }
# 3648 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      basic_string&
      insert(size_type __pos1, const basic_string& __str)
      { return this->insert(__pos1, __str, size_type(0), __str.size()); }
# 3670 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      basic_string&
      insert(size_type __pos1, const basic_string& __str,
      size_type __pos2, size_type __n)
      { return this->insert(__pos1, __str._M_data()
       + __str._M_check(__pos2, "basic_string::insert"),
       __str._M_limit(__pos2, __n)); }
# 3693 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      basic_string&
      insert(size_type __pos, const _CharT* __s, size_type __n);
# 3711 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      basic_string&
      insert(size_type __pos, const _CharT* __s)
      {
 ;
 return this->insert(__pos, __s, traits_type::length(__s));
      }
# 3734 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      basic_string&
      insert(size_type __pos, size_type __n, _CharT __c)
      { return _M_replace_aux(_M_check(__pos, "basic_string::insert"),
         size_type(0), __n, __c); }
# 3752 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      iterator
      insert(iterator __p, _CharT __c)
      {
 ;
 const size_type __pos = __p - _M_ibegin();
 _M_replace_aux(__pos, size_type(0), size_type(1), __c);
 _M_rep()->_M_set_leaked();
 return iterator(_M_data() + __pos);
      }
# 3777 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      basic_string&
      erase(size_type __pos = 0, size_type __n = npos)
      {
 _M_mutate(_M_check(__pos, "basic_string::erase"),
    _M_limit(__pos, __n), size_type(0));
 return *this;
      }
# 3793 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      iterator
      erase(iterator __position)
      {

                               ;
 const size_type __pos = __position - _M_ibegin();
 _M_mutate(__pos, size_type(1), size_type(0));
 _M_rep()->_M_set_leaked();
 return iterator(_M_data() + __pos);
      }
# 3813 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      iterator
      erase(iterator __first, iterator __last);
# 3844 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      basic_string&
      replace(size_type __pos, size_type __n, const basic_string& __str)
      { return this->replace(__pos, __n, __str._M_data(), __str.size()); }
# 3866 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      basic_string&
      replace(size_type __pos1, size_type __n1, const basic_string& __str,
       size_type __pos2, size_type __n2)
      { return this->replace(__pos1, __n1, __str._M_data()
        + __str._M_check(__pos2, "basic_string::replace"),
        __str._M_limit(__pos2, __n2)); }
# 3891 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      basic_string&
      replace(size_type __pos, size_type __n1, const _CharT* __s,
       size_type __n2);
# 3911 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      basic_string&
      replace(size_type __pos, size_type __n1, const _CharT* __s)
      {
 ;
 return this->replace(__pos, __n1, __s, traits_type::length(__s));
      }
# 3935 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      basic_string&
      replace(size_type __pos, size_type __n1, size_type __n2, _CharT __c)
      { return _M_replace_aux(_M_check(__pos, "basic_string::replace"),
         _M_limit(__pos, __n1), __n2, __c); }
# 3953 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      basic_string&
      replace(iterator __i1, iterator __i2, const basic_string& __str)
      { return this->replace(__i1, __i2, __str._M_data(), __str.size()); }
# 3972 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      basic_string&
      replace(iterator __i1, iterator __i2, const _CharT* __s, size_type __n)
      {

                          ;
 return this->replace(__i1 - _M_ibegin(), __i2 - __i1, __s, __n);
      }
# 3993 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      basic_string&
      replace(iterator __i1, iterator __i2, const _CharT* __s)
      {
 ;
 return this->replace(__i1, __i2, __s, traits_type::length(__s));
      }
# 4014 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      basic_string&
      replace(iterator __i1, iterator __i2, size_type __n, _CharT __c)
      {

                          ;
 return _M_replace_aux(__i1 - _M_ibegin(), __i2 - __i1, __n, __c);
      }
# 4037 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      template<class _InputIterator>
        basic_string&
        replace(iterator __i1, iterator __i2,
  _InputIterator __k1, _InputIterator __k2)
        {
  
                            ;
   ;
   typedef typename std::__is_integer<_InputIterator>::__type _Integral;
   return _M_replace_dispatch(__i1, __i2, __k1, __k2, _Integral());
 }



      basic_string&
      replace(iterator __i1, iterator __i2, _CharT* __k1, _CharT* __k2)
      {

                          ;
 ;
 return this->replace(__i1 - _M_ibegin(), __i2 - __i1,
        __k1, __k2 - __k1);
      }

      basic_string&
      replace(iterator __i1, iterator __i2,
       const _CharT* __k1, const _CharT* __k2)
      {

                          ;
 ;
 return this->replace(__i1 - _M_ibegin(), __i2 - __i1,
        __k1, __k2 - __k1);
      }

      basic_string&
      replace(iterator __i1, iterator __i2, iterator __k1, iterator __k2)
      {

                          ;
 ;
 return this->replace(__i1 - _M_ibegin(), __i2 - __i1,
        __k1.base(), __k2 - __k1);
      }

      basic_string&
      replace(iterator __i1, iterator __i2,
       const_iterator __k1, const_iterator __k2)
      {

                          ;
 ;
 return this->replace(__i1 - _M_ibegin(), __i2 - __i1,
        __k1.base(), __k2 - __k1);
      }
# 4113 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
    private:
      template<class _Integer>
 basic_string&
 _M_replace_dispatch(iterator __i1, iterator __i2, _Integer __n,
       _Integer __val, __true_type)
        { return _M_replace_aux(__i1 - _M_ibegin(), __i2 - __i1, __n, __val); }

      template<class _InputIterator>
 basic_string&
 _M_replace_dispatch(iterator __i1, iterator __i2, _InputIterator __k1,
       _InputIterator __k2, __false_type);

      basic_string&
      _M_replace_aux(size_type __pos1, size_type __n1, size_type __n2,
       _CharT __c);

      basic_string&
      _M_replace_safe(size_type __pos1, size_type __n1, const _CharT* __s,
        size_type __n2);



      template<class _InIterator>
        static _CharT*
        _S_construct_aux(_InIterator __beg, _InIterator __end,
    const _Alloc& __a, __false_type)
 {
          typedef typename iterator_traits<_InIterator>::iterator_category _Tag;
          return _S_construct(__beg, __end, __a, _Tag());
 }



      template<class _Integer>
        static _CharT*
        _S_construct_aux(_Integer __beg, _Integer __end,
    const _Alloc& __a, __true_type)
        { return _S_construct_aux_2(static_cast<size_type>(__beg),
        __end, __a); }

      static _CharT*
      _S_construct_aux_2(size_type __req, _CharT __c, const _Alloc& __a)
      { return _S_construct(__req, __c, __a); }

      template<class _InIterator>
        static _CharT*
        _S_construct(_InIterator __beg, _InIterator __end, const _Alloc& __a)
 {
   typedef typename std::__is_integer<_InIterator>::__type _Integral;
   return _S_construct_aux(__beg, __end, __a, _Integral());
        }


      template<class _InIterator>
        static _CharT*
         _S_construct(_InIterator __beg, _InIterator __end, const _Alloc& __a,
        input_iterator_tag);



      template<class _FwdIterator>
        static _CharT*
        _S_construct(_FwdIterator __beg, _FwdIterator __end, const _Alloc& __a,
       forward_iterator_tag);

      static _CharT*
      _S_construct(size_type __req, _CharT __c, const _Alloc& __a);

    public:
# 4195 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      size_type
      copy(_CharT* __s, size_type __n, size_type __pos = 0) const;
# 4206 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      void
      swap(basic_string& __s);
# 4216 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      const _CharT*
      c_str() const
      { return _M_data(); }







      const _CharT*
      data() const
      { return _M_data(); }




      allocator_type
      get_allocator() const
      { return _M_dataplus; }
# 4249 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      size_type
      find(const _CharT* __s, size_type __pos, size_type __n) const;
# 4262 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      size_type
      find(const basic_string& __str, size_type __pos = 0) const

      { return this->find(__str.data(), __pos, __str.size()); }
# 4277 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      size_type
      find(const _CharT* __s, size_type __pos = 0) const
      {
 ;
 return this->find(__s, __pos, traits_type::length(__s));
      }
# 4294 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      size_type
      find(_CharT __c, size_type __pos = 0) const ;
# 4307 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      size_type
      rfind(const basic_string& __str, size_type __pos = npos) const

      { return this->rfind(__str.data(), __pos, __str.size()); }
# 4324 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      size_type
      rfind(const _CharT* __s, size_type __pos, size_type __n) const;
# 4337 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      size_type
      rfind(const _CharT* __s, size_type __pos = npos) const
      {
 ;
 return this->rfind(__s, __pos, traits_type::length(__s));
      }
# 4354 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      size_type
      rfind(_CharT __c, size_type __pos = npos) const ;
# 4368 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      size_type
      find_first_of(const basic_string& __str, size_type __pos = 0) const

      { return this->find_first_of(__str.data(), __pos, __str.size()); }
# 4385 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      size_type
      find_first_of(const _CharT* __s, size_type __pos, size_type __n) const;
# 4398 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      size_type
      find_first_of(const _CharT* __s, size_type __pos = 0) const
      {
 ;
 return this->find_first_of(__s, __pos, traits_type::length(__s));
      }
# 4417 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      size_type
      find_first_of(_CharT __c, size_type __pos = 0) const
      { return this->find(__c, __pos); }
# 4432 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      size_type
      find_last_of(const basic_string& __str, size_type __pos = npos) const

      { return this->find_last_of(__str.data(), __pos, __str.size()); }
# 4449 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      size_type
      find_last_of(const _CharT* __s, size_type __pos, size_type __n) const;
# 4462 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      size_type
      find_last_of(const _CharT* __s, size_type __pos = npos) const
      {
 ;
 return this->find_last_of(__s, __pos, traits_type::length(__s));
      }
# 4481 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      size_type
      find_last_of(_CharT __c, size_type __pos = npos) const
      { return this->rfind(__c, __pos); }
# 4495 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      size_type
      find_first_not_of(const basic_string& __str, size_type __pos = 0) const

      { return this->find_first_not_of(__str.data(), __pos, __str.size()); }
# 4512 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      size_type
      find_first_not_of(const _CharT* __s, size_type __pos,
   size_type __n) const;
# 4526 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      size_type
      find_first_not_of(const _CharT* __s, size_type __pos = 0) const
      {
 ;
 return this->find_first_not_of(__s, __pos, traits_type::length(__s));
      }
# 4543 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      size_type
      find_first_not_of(_CharT __c, size_type __pos = 0) const
 ;
# 4558 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      size_type
      find_last_not_of(const basic_string& __str, size_type __pos = npos) const

      { return this->find_last_not_of(__str.data(), __pos, __str.size()); }
# 4575 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      size_type
      find_last_not_of(const _CharT* __s, size_type __pos,
         size_type __n) const;
# 4589 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      size_type
      find_last_not_of(const _CharT* __s, size_type __pos = npos) const
      {
 ;
 return this->find_last_not_of(__s, __pos, traits_type::length(__s));
      }
# 4606 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      size_type
      find_last_not_of(_CharT __c, size_type __pos = npos) const
 ;
# 4622 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      basic_string
      substr(size_type __pos = 0, size_type __n = npos) const
      { return basic_string(*this,
       _M_check(__pos, "basic_string::substr"), __n); }
# 4641 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      int
      compare(const basic_string& __str) const
      {
 const size_type __size = this->size();
 const size_type __osize = __str.size();
 const size_type __len = std::min(__size, __osize);

 int __r = traits_type::compare(_M_data(), __str.data(), __len);
 if (!__r)
   __r = _S_compare(__size, __osize);
 return __r;
      }
# 4673 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      int
      compare(size_type __pos, size_type __n, const basic_string& __str) const;
# 4699 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      int
      compare(size_type __pos1, size_type __n1, const basic_string& __str,
       size_type __pos2, size_type __n2) const;
# 4717 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      int
      compare(const _CharT* __s) const;
# 4741 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      int
      compare(size_type __pos, size_type __n1, const _CharT* __s) const;
# 4768 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
      int
      compare(size_type __pos, size_type __n1, const _CharT* __s,
       size_type __n2) const;
  };
# 4781 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>
    operator+(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    {
      basic_string<_CharT, _Traits, _Alloc> __str(__lhs);
      __str.append(__rhs);
      return __str;
    }







  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT,_Traits,_Alloc>
    operator+(const _CharT* __lhs,
       const basic_string<_CharT,_Traits,_Alloc>& __rhs);







  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT,_Traits,_Alloc>
    operator+(_CharT __lhs, const basic_string<_CharT,_Traits,_Alloc>& __rhs);







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_string<_CharT, _Traits, _Alloc>
    operator+(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
       const _CharT* __rhs)
    {
      basic_string<_CharT, _Traits, _Alloc> __str(__lhs);
      __str.append(__rhs);
      return __str;
    }







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_string<_CharT, _Traits, _Alloc>
    operator+(const basic_string<_CharT, _Traits, _Alloc>& __lhs, _CharT __rhs)
    {
      typedef basic_string<_CharT, _Traits, _Alloc> __string_type;
      typedef typename __string_type::size_type __size_type;
      __string_type __str(__lhs);
      __str.append(__size_type(1), __rhs);
      return __str;
    }
# 4902 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator==(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __lhs.compare(__rhs) == 0; }

  template<typename _CharT>
    inline
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value, bool>::__type
    operator==(const basic_string<_CharT>& __lhs,
        const basic_string<_CharT>& __rhs)
    { return (__lhs.size() == __rhs.size()
       && !std::char_traits<_CharT>::compare(__lhs.data(), __rhs.data(),
          __lhs.size())); }







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator==(const _CharT* __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __rhs.compare(__lhs) == 0; }







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator==(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const _CharT* __rhs)
    { return __lhs.compare(__rhs) == 0; }
# 4948 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator!=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return !(__lhs == __rhs); }







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator!=(const _CharT* __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return !(__lhs == __rhs); }







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator!=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const _CharT* __rhs)
    { return !(__lhs == __rhs); }
# 4985 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __lhs.compare(__rhs) < 0; }







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
       const _CharT* __rhs)
    { return __lhs.compare(__rhs) < 0; }







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<(const _CharT* __lhs,
       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __rhs.compare(__lhs) > 0; }
# 5022 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __lhs.compare(__rhs) > 0; }







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
       const _CharT* __rhs)
    { return __lhs.compare(__rhs) > 0; }







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>(const _CharT* __lhs,
       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __rhs.compare(__lhs) < 0; }
# 5059 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __lhs.compare(__rhs) <= 0; }







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const _CharT* __rhs)
    { return __lhs.compare(__rhs) <= 0; }







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<=(const _CharT* __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __rhs.compare(__lhs) >= 0; }
# 5096 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __lhs.compare(__rhs) >= 0; }







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const _CharT* __rhs)
    { return __lhs.compare(__rhs) >= 0; }







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>=(const _CharT* __lhs,
      const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __rhs.compare(__lhs) <= 0; }
# 5133 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline void
    swap(basic_string<_CharT, _Traits, _Alloc>& __lhs,
  basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { __lhs.swap(__rhs); }
# 5152 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __is,
        basic_string<_CharT, _Traits, _Alloc>& __str);

  template<>
    basic_istream<char>&
    operator>>(basic_istream<char>& __is, basic_string<char>& __str);
# 5170 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __os,
        const basic_string<_CharT, _Traits, _Alloc>& __str)
    {


      return __ostream_insert(__os, __str.data(), __str.size());
    }
# 5193 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_istream<_CharT, _Traits>&
    getline(basic_istream<_CharT, _Traits>& __is,
     basic_string<_CharT, _Traits, _Alloc>& __str, _CharT __delim);
# 5210 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_istream<_CharT, _Traits>&
    getline(basic_istream<_CharT, _Traits>& __is,
     basic_string<_CharT, _Traits, _Alloc>& __str)
    { return std::getline(__is, __str, __is.widen('\n')); }
# 5232 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.h" 3
  template<>
    basic_istream<char>&
    getline(basic_istream<char>& __in, basic_string<char>& __str,
     char __delim);


  template<>
    basic_istream<wchar_t>&
    getline(basic_istream<wchar_t>& __in, basic_string<wchar_t>& __str,
     wchar_t __delim);



}
# 53 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/string" 2 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.tcc" 1 3
# 42 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.tcc" 3
       
# 43 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.tcc" 3



namespace std
{

# 492 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.tcc" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    const typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    _Rep::_S_max_size = (((npos - sizeof(_Rep_base))/sizeof(_CharT)) - 1) / 4;

  template<typename _CharT, typename _Traits, typename _Alloc>
    const _CharT
    basic_string<_CharT, _Traits, _Alloc>::
    _Rep::_S_terminal = _CharT();

  template<typename _CharT, typename _Traits, typename _Alloc>
    const typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::npos;



  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::_Rep::_S_empty_rep_storage[
    (sizeof(_Rep_base) + sizeof(_CharT) + sizeof(size_type) - 1) /
      sizeof(size_type)];





  template<typename _CharT, typename _Traits, typename _Alloc>
    template<typename _InIterator>
      _CharT*
      basic_string<_CharT, _Traits, _Alloc>::
      _S_construct(_InIterator __beg, _InIterator __end, const _Alloc& __a,
     input_iterator_tag)
      {

 if (__beg == __end && __a == _Alloc())
   return _S_empty_rep()._M_refdata();


 _CharT __buf[128];
 size_type __len = 0;
 while (__beg != __end && __len < sizeof(__buf) / sizeof(_CharT))
   {
     __buf[__len++] = *__beg;
     ++__beg;
   }
 _Rep* __r = _Rep::_S_create(__len, size_type(0), __a);
 _M_copy(__r->_M_refdata(), __buf, __len);
 try
   {
     while (__beg != __end)
       {
  if (__len == __r->_M_capacity)
    {

      _Rep* __another = _Rep::_S_create(__len + 1, __len, __a);
      _M_copy(__another->_M_refdata(), __r->_M_refdata(), __len);
      __r->_M_destroy(__a);
      __r = __another;
    }
  __r->_M_refdata()[__len++] = *__beg;
  ++__beg;
       }
   }
 catch(...)
   {
     __r->_M_destroy(__a);
     throw;
   }
 __r->_M_set_length_and_sharable(__len);
 return __r->_M_refdata();
      }

  template<typename _CharT, typename _Traits, typename _Alloc>
    template <typename _InIterator>
      _CharT*
      basic_string<_CharT, _Traits, _Alloc>::
      _S_construct(_InIterator __beg, _InIterator __end, const _Alloc& __a,
     forward_iterator_tag)
      {

 if (__beg == __end && __a == _Alloc())
   return _S_empty_rep()._M_refdata();


 if (__gnu_cxx::__is_null_pointer(__beg) && __beg != __end)
   __throw_logic_error(("basic_string::_S_construct null not valid"));

 const size_type __dnew = static_cast<size_type>(std::distance(__beg,
              __end));

 _Rep* __r = _Rep::_S_create(__dnew, size_type(0), __a);
 try
   { _S_copy_chars(__r->_M_refdata(), __beg, __end); }
 catch(...)
   {
     __r->_M_destroy(__a);
     throw;
   }
 __r->_M_set_length_and_sharable(__dnew);
 return __r->_M_refdata();
      }

  template<typename _CharT, typename _Traits, typename _Alloc>
    _CharT*
    basic_string<_CharT, _Traits, _Alloc>::
    _S_construct(size_type __n, _CharT __c, const _Alloc& __a)
    {

      if (__n == 0 && __a == _Alloc())
 return _S_empty_rep()._M_refdata();


      _Rep* __r = _Rep::_S_create(__n, size_type(0), __a);
      if (__n)
 _M_assign(__r->_M_refdata(), __n, __c);

      __r->_M_set_length_and_sharable(__n);
      return __r->_M_refdata();
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const basic_string& __str)
    : _M_dataplus(__str._M_rep()->_M_grab(_Alloc(__str.get_allocator()),
       __str.get_allocator()),
    __str.get_allocator())
    { }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const _Alloc& __a)
    : _M_dataplus(_S_construct(size_type(), _CharT(), __a), __a)
    { }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const basic_string& __str, size_type __pos, size_type __n)
    : _M_dataplus(_S_construct(__str._M_data()
          + __str._M_check(__pos,
      "basic_string::basic_string"),
          __str._M_data() + __str._M_limit(__pos, __n)
          + __pos, _Alloc()), _Alloc())
    { }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const basic_string& __str, size_type __pos,
   size_type __n, const _Alloc& __a)
    : _M_dataplus(_S_construct(__str._M_data()
          + __str._M_check(__pos,
      "basic_string::basic_string"),
          __str._M_data() + __str._M_limit(__pos, __n)
          + __pos, __a), __a)
    { }


  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const _CharT* __s, size_type __n, const _Alloc& __a)
    : _M_dataplus(_S_construct(__s, __s + __n, __a), __a)
    { }


  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const _CharT* __s, const _Alloc& __a)
    : _M_dataplus(_S_construct(__s, __s ? __s + traits_type::length(__s) :
          __s + npos, __a), __a)
    { }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(size_type __n, _CharT __c, const _Alloc& __a)
    : _M_dataplus(_S_construct(__n, __c, __a), __a)
    { }


  template<typename _CharT, typename _Traits, typename _Alloc>
    template<typename _InputIterator>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(_InputIterator __beg, _InputIterator __end, const _Alloc& __a)
    : _M_dataplus(_S_construct(__beg, __end, __a), __a)
    { }
# 684 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.tcc" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    assign(const basic_string& __str)
    {
      if (_M_rep() != __str._M_rep())
 {

   const allocator_type __a = this->get_allocator();
   _CharT* __tmp = __str._M_rep()->_M_grab(__a, __str.get_allocator());
   _M_rep()->_M_dispose(__a);
   _M_data(__tmp);
 }
      return *this;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    assign(const _CharT* __s, size_type __n)
    {
      ;
      _M_check_length(this->size(), __n, "basic_string::assign");
      if (_M_disjunct(__s) || _M_rep()->_M_is_shared())
 return _M_replace_safe(size_type(0), this->size(), __s, __n);
      else
 {

   const size_type __pos = __s - _M_data();
   if (__pos >= __n)
     _M_copy(_M_data(), __s, __n);
   else if (__pos)
     _M_move(_M_data(), __s, __n);
   _M_rep()->_M_set_length_and_sharable(__n);
   return *this;
 }
     }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    append(size_type __n, _CharT __c)
    {
      if (__n)
 {
   _M_check_length(size_type(0), __n, "basic_string::append");
   const size_type __len = __n + this->size();
   if (__len > this->capacity() || _M_rep()->_M_is_shared())
     this->reserve(__len);
   _M_assign(_M_data() + this->size(), __n, __c);
   _M_rep()->_M_set_length_and_sharable(__len);
 }
      return *this;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    append(const _CharT* __s, size_type __n)
    {
      ;
      if (__n)
 {
   _M_check_length(size_type(0), __n, "basic_string::append");
   const size_type __len = __n + this->size();
   if (__len > this->capacity() || _M_rep()->_M_is_shared())
     {
       if (_M_disjunct(__s))
  this->reserve(__len);
       else
  {
    const size_type __off = __s - _M_data();
    this->reserve(__len);
    __s = _M_data() + __off;
  }
     }
   _M_copy(_M_data() + this->size(), __s, __n);
   _M_rep()->_M_set_length_and_sharable(__len);
 }
      return *this;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    append(const basic_string& __str)
    {
      const size_type __size = __str.size();
      if (__size)
 {
   const size_type __len = __size + this->size();
   if (__len > this->capacity() || _M_rep()->_M_is_shared())
     this->reserve(__len);
   _M_copy(_M_data() + this->size(), __str._M_data(), __size);
   _M_rep()->_M_set_length_and_sharable(__len);
 }
      return *this;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    append(const basic_string& __str, size_type __pos, size_type __n)
    {
      __str._M_check(__pos, "basic_string::append");
      __n = __str._M_limit(__pos, __n);
      if (__n)
 {
   const size_type __len = __n + this->size();
   if (__len > this->capacity() || _M_rep()->_M_is_shared())
     this->reserve(__len);
   _M_copy(_M_data() + this->size(), __str._M_data() + __pos, __n);
   _M_rep()->_M_set_length_and_sharable(__len);
 }
      return *this;
    }

   template<typename _CharT, typename _Traits, typename _Alloc>
     basic_string<_CharT, _Traits, _Alloc>&
     basic_string<_CharT, _Traits, _Alloc>::
     insert(size_type __pos, const _CharT* __s, size_type __n)
     {
       ;
       _M_check(__pos, "basic_string::insert");
       _M_check_length(size_type(0), __n, "basic_string::insert");
       if (_M_disjunct(__s) || _M_rep()->_M_is_shared())
         return _M_replace_safe(__pos, size_type(0), __s, __n);
       else
         {

           const size_type __off = __s - _M_data();
           _M_mutate(__pos, 0, __n);
           __s = _M_data() + __off;
           _CharT* __p = _M_data() + __pos;
           if (__s + __n <= __p)
             _M_copy(__p, __s, __n);
           else if (__s >= __p)
             _M_copy(__p, __s + __n, __n);
           else
             {
        const size_type __nleft = __p - __s;
               _M_copy(__p, __s, __nleft);
               _M_copy(__p + __nleft, __p + __n, __n - __nleft);
             }
           return *this;
         }
     }

   template<typename _CharT, typename _Traits, typename _Alloc>
     typename basic_string<_CharT, _Traits, _Alloc>::iterator
     basic_string<_CharT, _Traits, _Alloc>::
     erase(iterator __first, iterator __last)
     {
      
                           ;




       const size_type __size = __last - __first;
       if (__size)
  {
    const size_type __pos = __first - _M_ibegin();
    _M_mutate(__pos, __size, size_type(0));
    _M_rep()->_M_set_leaked();
    return iterator(_M_data() + __pos);
  }
       else
  return __first;
     }

   template<typename _CharT, typename _Traits, typename _Alloc>
     basic_string<_CharT, _Traits, _Alloc>&
     basic_string<_CharT, _Traits, _Alloc>::
     replace(size_type __pos, size_type __n1, const _CharT* __s,
      size_type __n2)
     {
       ;
       _M_check(__pos, "basic_string::replace");
       __n1 = _M_limit(__pos, __n1);
       _M_check_length(__n1, __n2, "basic_string::replace");
       bool __left;
       if (_M_disjunct(__s) || _M_rep()->_M_is_shared())
         return _M_replace_safe(__pos, __n1, __s, __n2);
       else if ((__left = __s + __n2 <= _M_data() + __pos)
  || _M_data() + __pos + __n1 <= __s)
  {

    size_type __off = __s - _M_data();
    __left ? __off : (__off += __n2 - __n1);
    _M_mutate(__pos, __n1, __n2);
    _M_copy(_M_data() + __pos, _M_data() + __off, __n2);
    return *this;
  }
       else
  {

    const basic_string __tmp(__s, __n2);
    return _M_replace_safe(__pos, __n1, __tmp._M_data(), __n2);
  }
     }

  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::_Rep::
    _M_destroy(const _Alloc& __a) throw ()
    {
      const size_type __size = sizeof(_Rep_base) +
                        (this->_M_capacity + 1) * sizeof(_CharT);
      _Raw_bytes_alloc(__a).deallocate(reinterpret_cast<char*>(this), __size);
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::
    _M_leak_hard()
    {

      if (_M_rep() == &_S_empty_rep())
 return;

      if (_M_rep()->_M_is_shared())
 _M_mutate(0, 0, 0);
      _M_rep()->_M_set_leaked();
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::
    _M_mutate(size_type __pos, size_type __len1, size_type __len2)
    {
      const size_type __old_size = this->size();
      const size_type __new_size = __old_size + __len2 - __len1;
      const size_type __how_much = __old_size - __pos - __len1;

      if (__new_size > this->capacity() || _M_rep()->_M_is_shared())
 {

   const allocator_type __a = get_allocator();
   _Rep* __r = _Rep::_S_create(__new_size, this->capacity(), __a);

   if (__pos)
     _M_copy(__r->_M_refdata(), _M_data(), __pos);
   if (__how_much)
     _M_copy(__r->_M_refdata() + __pos + __len2,
      _M_data() + __pos + __len1, __how_much);

   _M_rep()->_M_dispose(__a);
   _M_data(__r->_M_refdata());
 }
      else if (__how_much && __len1 != __len2)
 {

   _M_move(_M_data() + __pos + __len2,
    _M_data() + __pos + __len1, __how_much);
 }
      _M_rep()->_M_set_length_and_sharable(__new_size);
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::
    reserve(size_type __res)
    {
      if (__res != this->capacity() || _M_rep()->_M_is_shared())
        {

   if (__res < this->size())
     __res = this->size();
   const allocator_type __a = get_allocator();
   _CharT* __tmp = _M_rep()->_M_clone(__a, __res - this->size());
   _M_rep()->_M_dispose(__a);
   _M_data(__tmp);
        }
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::
    swap(basic_string& __s)
    {
      if (_M_rep()->_M_is_leaked())
 _M_rep()->_M_set_sharable();
      if (__s._M_rep()->_M_is_leaked())
 __s._M_rep()->_M_set_sharable();
      if (this->get_allocator() == __s.get_allocator())
 {
   _CharT* __tmp = _M_data();
   _M_data(__s._M_data());
   __s._M_data(__tmp);
 }

      else
 {
   const basic_string __tmp1(_M_ibegin(), _M_iend(),
        __s.get_allocator());
   const basic_string __tmp2(__s._M_ibegin(), __s._M_iend(),
        this->get_allocator());
   *this = __tmp2;
   __s = __tmp1;
 }
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::_Rep*
    basic_string<_CharT, _Traits, _Alloc>::_Rep::
    _S_create(size_type __capacity, size_type __old_capacity,
       const _Alloc& __alloc)
    {


      if (__capacity > _S_max_size)
 __throw_length_error(("basic_string::_S_create"));
# 1021 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_string.tcc" 3
      const size_type __pagesize = 4096;
      const size_type __malloc_header_size = 4 * sizeof(void*);







      if (__capacity > __old_capacity && __capacity < 2 * __old_capacity)
 __capacity = 2 * __old_capacity;




      size_type __size = (__capacity + 1) * sizeof(_CharT) + sizeof(_Rep);

      const size_type __adj_size = __size + __malloc_header_size;
      if (__adj_size > __pagesize && __capacity > __old_capacity)
 {
   const size_type __extra = __pagesize - __adj_size % __pagesize;
   __capacity += __extra / sizeof(_CharT);

   if (__capacity > _S_max_size)
     __capacity = _S_max_size;
   __size = (__capacity + 1) * sizeof(_CharT) + sizeof(_Rep);
 }



      void* __place = _Raw_bytes_alloc(__alloc).allocate(__size);
      _Rep *__p = new (__place) _Rep;
      __p->_M_capacity = __capacity;







      __p->_M_set_sharable();
      return __p;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    _CharT*
    basic_string<_CharT, _Traits, _Alloc>::_Rep::
    _M_clone(const _Alloc& __alloc, size_type __res)
    {

      const size_type __requested_cap = this->_M_length + __res;
      _Rep* __r = _Rep::_S_create(__requested_cap, this->_M_capacity,
      __alloc);
      if (this->_M_length)
 _M_copy(__r->_M_refdata(), _M_refdata(), this->_M_length);

      __r->_M_set_length_and_sharable(this->_M_length);
      return __r->_M_refdata();
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::
    resize(size_type __n, _CharT __c)
    {
      const size_type __size = this->size();
      _M_check_length(__size, __n, "basic_string::resize");
      if (__size < __n)
 this->append(__n - __size, __c);
      else if (__n < __size)
 this->erase(__n);

    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    template<typename _InputIterator>
      basic_string<_CharT, _Traits, _Alloc>&
      basic_string<_CharT, _Traits, _Alloc>::
      _M_replace_dispatch(iterator __i1, iterator __i2, _InputIterator __k1,
     _InputIterator __k2, __false_type)
      {
 const basic_string __s(__k1, __k2);
 const size_type __n1 = __i2 - __i1;
 _M_check_length(__n1, __s.size(), "basic_string::_M_replace_dispatch");
 return _M_replace_safe(__i1 - _M_ibegin(), __n1, __s._M_data(),
          __s.size());
      }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    _M_replace_aux(size_type __pos1, size_type __n1, size_type __n2,
     _CharT __c)
    {
      _M_check_length(__n1, __n2, "basic_string::_M_replace_aux");
      _M_mutate(__pos1, __n1, __n2);
      if (__n2)
 _M_assign(_M_data() + __pos1, __n2, __c);
      return *this;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    _M_replace_safe(size_type __pos1, size_type __n1, const _CharT* __s,
      size_type __n2)
    {
      _M_mutate(__pos1, __n1, __n2);
      if (__n2)
 _M_copy(_M_data() + __pos1, __s, __n2);
      return *this;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    copy(_CharT* __s, size_type __n, size_type __pos) const
    {
      _M_check(__pos, "basic_string::copy");
      __n = _M_limit(__pos, __n);
      ;
      if (__n)
 _M_copy(__s, _M_data() + __pos, __n);

      return __n;
    }


  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>
    operator+(const _CharT* __lhs,
       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    {
      ;
      typedef basic_string<_CharT, _Traits, _Alloc> __string_type;
      typedef typename __string_type::size_type __size_type;
      const __size_type __len = _Traits::length(__lhs);
      __string_type __str;
      __str.reserve(__len + __rhs.size());
      __str.append(__lhs, __len);
      __str.append(__rhs);
      return __str;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>
    operator+(_CharT __lhs, const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    {
      typedef basic_string<_CharT, _Traits, _Alloc> __string_type;
      typedef typename __string_type::size_type __size_type;
      __string_type __str;
      const __size_type __len = __rhs.size();
      __str.reserve(__len + 1);
      __str.append(__size_type(1), __lhs);
      __str.append(__rhs);
      return __str;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      const size_type __size = this->size();
      const _CharT* __data = _M_data();

      if (__n == 0)
 return __pos <= __size ? __pos : npos;

      if (__n <= __size)
 {
   for (; __pos <= __size - __n; ++__pos)
     if (traits_type::eq(__data[__pos], __s[0])
  && traits_type::compare(__data + __pos + 1,
     __s + 1, __n - 1) == 0)
       return __pos;
 }
      return npos;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find(_CharT __c, size_type __pos) const
    {
      size_type __ret = npos;
      const size_type __size = this->size();
      if (__pos < __size)
 {
   const _CharT* __data = _M_data();
   const size_type __n = __size - __pos;
   const _CharT* __p = traits_type::find(__data + __pos, __n, __c);
   if (__p)
     __ret = __p - __data;
 }
      return __ret;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    rfind(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      const size_type __size = this->size();
      if (__n <= __size)
 {
   __pos = std::min(size_type(__size - __n), __pos);
   const _CharT* __data = _M_data();
   do
     {
       if (traits_type::compare(__data + __pos, __s, __n) == 0)
  return __pos;
     }
   while (__pos-- > 0);
 }
      return npos;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    rfind(_CharT __c, size_type __pos) const
    {
      size_type __size = this->size();
      if (__size)
 {
   if (--__size > __pos)
     __size = __pos;
   for (++__size; __size-- > 0; )
     if (traits_type::eq(_M_data()[__size], __c))
       return __size;
 }
      return npos;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_first_of(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      for (; __n && __pos < this->size(); ++__pos)
 {
   const _CharT* __p = traits_type::find(__s, __n, _M_data()[__pos]);
   if (__p)
     return __pos;
 }
      return npos;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_last_of(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      size_type __size = this->size();
      if (__size && __n)
 {
   if (--__size > __pos)
     __size = __pos;
   do
     {
       if (traits_type::find(__s, __n, _M_data()[__size]))
  return __size;
     }
   while (__size-- != 0);
 }
      return npos;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_first_not_of(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      for (; __pos < this->size(); ++__pos)
 if (!traits_type::find(__s, __n, _M_data()[__pos]))
   return __pos;
      return npos;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_first_not_of(_CharT __c, size_type __pos) const
    {
      for (; __pos < this->size(); ++__pos)
 if (!traits_type::eq(_M_data()[__pos], __c))
   return __pos;
      return npos;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_last_not_of(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      size_type __size = this->size();
      if (__size)
 {
   if (--__size > __pos)
     __size = __pos;
   do
     {
       if (!traits_type::find(__s, __n, _M_data()[__size]))
  return __size;
     }
   while (__size--);
 }
      return npos;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_last_not_of(_CharT __c, size_type __pos) const
    {
      size_type __size = this->size();
      if (__size)
 {
   if (--__size > __pos)
     __size = __pos;
   do
     {
       if (!traits_type::eq(_M_data()[__size], __c))
  return __size;
     }
   while (__size--);
 }
      return npos;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    int
    basic_string<_CharT, _Traits, _Alloc>::
    compare(size_type __pos, size_type __n, const basic_string& __str) const
    {
      _M_check(__pos, "basic_string::compare");
      __n = _M_limit(__pos, __n);
      const size_type __osize = __str.size();
      const size_type __len = std::min(__n, __osize);
      int __r = traits_type::compare(_M_data() + __pos, __str.data(), __len);
      if (!__r)
 __r = _S_compare(__n, __osize);
      return __r;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    int
    basic_string<_CharT, _Traits, _Alloc>::
    compare(size_type __pos1, size_type __n1, const basic_string& __str,
     size_type __pos2, size_type __n2) const
    {
      _M_check(__pos1, "basic_string::compare");
      __str._M_check(__pos2, "basic_string::compare");
      __n1 = _M_limit(__pos1, __n1);
      __n2 = __str._M_limit(__pos2, __n2);
      const size_type __len = std::min(__n1, __n2);
      int __r = traits_type::compare(_M_data() + __pos1,
         __str.data() + __pos2, __len);
      if (!__r)
 __r = _S_compare(__n1, __n2);
      return __r;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    int
    basic_string<_CharT, _Traits, _Alloc>::
    compare(const _CharT* __s) const
    {
      ;
      const size_type __size = this->size();
      const size_type __osize = traits_type::length(__s);
      const size_type __len = std::min(__size, __osize);
      int __r = traits_type::compare(_M_data(), __s, __len);
      if (!__r)
 __r = _S_compare(__size, __osize);
      return __r;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    int
    basic_string <_CharT, _Traits, _Alloc>::
    compare(size_type __pos, size_type __n1, const _CharT* __s) const
    {
      ;
      _M_check(__pos, "basic_string::compare");
      __n1 = _M_limit(__pos, __n1);
      const size_type __osize = traits_type::length(__s);
      const size_type __len = std::min(__n1, __osize);
      int __r = traits_type::compare(_M_data() + __pos, __s, __len);
      if (!__r)
 __r = _S_compare(__n1, __osize);
      return __r;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    int
    basic_string <_CharT, _Traits, _Alloc>::
    compare(size_type __pos, size_type __n1, const _CharT* __s,
     size_type __n2) const
    {
      ;
      _M_check(__pos, "basic_string::compare");
      __n1 = _M_limit(__pos, __n1);
      const size_type __len = std::min(__n1, __n2);
      int __r = traits_type::compare(_M_data() + __pos, __s, __len);
      if (!__r)
 __r = _S_compare(__n1, __n2);
      return __r;
    }


  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __in,
        basic_string<_CharT, _Traits, _Alloc>& __str)
    {
      typedef basic_istream<_CharT, _Traits> __istream_type;
      typedef basic_string<_CharT, _Traits, _Alloc> __string_type;
      typedef typename __istream_type::ios_base __ios_base;
      typedef typename __istream_type::int_type __int_type;
      typedef typename __string_type::size_type __size_type;
      typedef ctype<_CharT> __ctype_type;
      typedef typename __ctype_type::ctype_base __ctype_base;

      __size_type __extracted = 0;
      typename __ios_base::iostate __err = __ios_base::goodbit;
      typename __istream_type::sentry __cerb(__in, false);
      if (__cerb)
 {
   try
     {

       __str.erase();
       _CharT __buf[128];
       __size_type __len = 0;
       const streamsize __w = __in.width();
       const __size_type __n = __w > 0 ? static_cast<__size_type>(__w)
                                : __str.max_size();
       const __ctype_type& __ct = use_facet<__ctype_type>(__in.getloc());
       const __int_type __eof = _Traits::eof();
       __int_type __c = __in.rdbuf()->sgetc();

       while (__extracted < __n
       && !_Traits::eq_int_type(__c, __eof)
       && !__ct.is(__ctype_base::space,
     _Traits::to_char_type(__c)))
  {
    if (__len == sizeof(__buf) / sizeof(_CharT))
      {
        __str.append(__buf, sizeof(__buf) / sizeof(_CharT));
        __len = 0;
      }
    __buf[__len++] = _Traits::to_char_type(__c);
    ++__extracted;
    __c = __in.rdbuf()->snextc();
  }
       __str.append(__buf, __len);

       if (_Traits::eq_int_type(__c, __eof))
  __err |= __ios_base::eofbit;
       __in.width(0);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       __in._M_setstate(__ios_base::badbit);
       throw;
     }
   catch(...)
     {



       __in._M_setstate(__ios_base::badbit);
     }
 }

      if (!__extracted)
 __err |= __ios_base::failbit;
      if (__err)
 __in.setstate(__err);
      return __in;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_istream<_CharT, _Traits>&
    getline(basic_istream<_CharT, _Traits>& __in,
     basic_string<_CharT, _Traits, _Alloc>& __str, _CharT __delim)
    {
      typedef basic_istream<_CharT, _Traits> __istream_type;
      typedef basic_string<_CharT, _Traits, _Alloc> __string_type;
      typedef typename __istream_type::ios_base __ios_base;
      typedef typename __istream_type::int_type __int_type;
      typedef typename __string_type::size_type __size_type;

      __size_type __extracted = 0;
      const __size_type __n = __str.max_size();
      typename __ios_base::iostate __err = __ios_base::goodbit;
      typename __istream_type::sentry __cerb(__in, true);
      if (__cerb)
 {
   try
     {
       __str.erase();
       const __int_type __idelim = _Traits::to_int_type(__delim);
       const __int_type __eof = _Traits::eof();
       __int_type __c = __in.rdbuf()->sgetc();

       while (__extracted < __n
       && !_Traits::eq_int_type(__c, __eof)
       && !_Traits::eq_int_type(__c, __idelim))
  {
    __str += _Traits::to_char_type(__c);
    ++__extracted;
    __c = __in.rdbuf()->snextc();
  }

       if (_Traits::eq_int_type(__c, __eof))
  __err |= __ios_base::eofbit;
       else if (_Traits::eq_int_type(__c, __idelim))
  {
    ++__extracted;
    __in.rdbuf()->sbumpc();
  }
       else
  __err |= __ios_base::failbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       __in._M_setstate(__ios_base::badbit);
       throw;
     }
   catch(...)
     {



       __in._M_setstate(__ios_base::badbit);
     }
 }
      if (!__extracted)
 __err |= __ios_base::failbit;
      if (__err)
 __in.setstate(__err);
      return __in;
    }




  extern template class basic_string<char>;
  extern template
    basic_istream<char>&
    operator>>(basic_istream<char>&, string&);
  extern template
    basic_ostream<char>&
    operator<<(basic_ostream<char>&, const string&);
  extern template
    basic_istream<char>&
    getline(basic_istream<char>&, string&, char);
  extern template
    basic_istream<char>&
    getline(basic_istream<char>&, string&);


  extern template class basic_string<wchar_t>;
  extern template
    basic_istream<wchar_t>&
    operator>>(basic_istream<wchar_t>&, wstring&);
  extern template
    basic_ostream<wchar_t>&
    operator<<(basic_ostream<wchar_t>&, const wstring&);
  extern template
    basic_istream<wchar_t>&
    getline(basic_istream<wchar_t>&, wstring&, wchar_t);
  extern template
    basic_istream<wchar_t>&
    getline(basic_istream<wchar_t>&, wstring&);




}
# 54 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/string" 2 3
# 41 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 2 3


namespace std
{

# 62 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3
  class locale
  {
  public:


    typedef int category;


    class facet;
    class id;
    class _Impl;

    friend class facet;
    friend class _Impl;

    template<typename _Facet>
      friend bool
      has_facet(const locale&) throw();

    template<typename _Facet>
      friend const _Facet&
      use_facet(const locale&);

    template<typename _Cache>
      friend struct __use_cache;
# 98 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3
    static const category none = 0;
    static const category ctype = 1L << 0;
    static const category numeric = 1L << 1;
    static const category collate = 1L << 2;
    static const category time = 1L << 3;
    static const category monetary = 1L << 4;
    static const category messages = 1L << 5;
    static const category all = (ctype | numeric | collate |
        time | monetary | messages);
# 117 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3
    locale() throw();
# 126 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3
    locale(const locale& __other) throw();
# 136 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3
    explicit
    locale(const char* __s);
# 151 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3
    locale(const locale& __base, const char* __s, category __cat);
# 192 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3
    locale(const locale& __base, const locale& __add, category __cat);
# 205 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3
    template<typename _Facet>
      locale(const locale& __other, _Facet* __f);


    ~locale() throw();
# 219 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3
    const locale&
    operator=(const locale& __other) throw();
# 234 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3
    template<typename _Facet>
      locale
      combine(const locale& __other) const;






   
    string
    name() const;
# 254 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3
    bool
    operator==(const locale& __other) const throw();







    bool
    operator!=(const locale& __other) const throw()
    { return !(this->operator==(__other)); }
# 282 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3
    template<typename _Char, typename _Traits, typename _Alloc>
      bool
      operator()(const basic_string<_Char, _Traits, _Alloc>& __s1,
   const basic_string<_Char, _Traits, _Alloc>& __s2) const;
# 298 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3
    static locale
    global(const locale& __loc);




    static const locale&
    classic();

  private:

    _Impl* _M_impl;


    static _Impl* _S_classic;


    static _Impl* _S_global;





    static const char* const* const _S_categories;
# 333 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3
    enum { _S_categories_size = 6 + 0 };


    static __gthread_once_t _S_once;


    explicit
    locale(_Impl*) throw();

    static void
    _S_initialize();

    static void
    _S_initialize_once() throw();

    static category
    _S_normalize_category(category);

    void
    _M_coalesce(const locale& __base, const locale& __add, category __cat);




  };
# 371 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3
  class locale::facet
  {
  private:
    friend class locale;
    friend class locale::_Impl;

    mutable _Atomic_word _M_refcount;


    static __c_locale _S_c_locale;


    static const char _S_c_name[2];


    static __gthread_once_t _S_once;


    static void
    _S_initialize_once();

  protected:
# 402 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3
    explicit
    facet(size_t __refs = 0) throw() : _M_refcount(__refs ? 1 : 0)
    { }


    virtual
    ~facet();

    static void
    _S_create_c_locale(__c_locale& __cloc, const char* __s,
         __c_locale __old = 0);

    static __c_locale
    _S_clone_c_locale(__c_locale& __cloc) throw();

    static void
    _S_destroy_c_locale(__c_locale& __cloc);

    static __c_locale
    _S_lc_ctype_c_locale(__c_locale __cloc, const char* __s);



    static __c_locale
    _S_get_c_locale();

    __attribute__ ((__const__)) static const char*
    _S_get_c_name() throw();

  private:
    void
    _M_add_reference() const throw()
    { __gnu_cxx::__atomic_add_dispatch(&_M_refcount, 1); }

    void
    _M_remove_reference() const throw()
    {

      ;
      if (__gnu_cxx::__exchange_and_add_dispatch(&_M_refcount, -1) == 1)
 {
          ;
   try
     { delete this; }
   catch(...)
     { }
 }
    }

    facet(const facet&);

    facet&
    operator=(const facet&);

    class __shim;

    const facet* _M_sso_shim(const id*) const;
    const facet* _M_cow_shim(const id*) const;
  };
# 474 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3
  class locale::id
  {
  private:
    friend class locale;
    friend class locale::_Impl;

    template<typename _Facet>
      friend const _Facet&
      use_facet(const locale&);

    template<typename _Facet>
      friend bool
      has_facet(const locale&) throw();




    mutable size_t _M_index;


    static _Atomic_word _S_refcount;

    void
    operator=(const id&);

    id(const id&);

  public:



    id() { }

    size_t
    _M_id() const throw();
  };



  class locale::_Impl
  {
  public:

    friend class locale;
    friend class locale::facet;

    template<typename _Facet>
      friend bool
      has_facet(const locale&) throw();

    template<typename _Facet>
      friend const _Facet&
      use_facet(const locale&);

    template<typename _Cache>
      friend struct __use_cache;

  private:

    _Atomic_word _M_refcount;
    const facet** _M_facets;
    size_t _M_facets_size;
    const facet** _M_caches;
    char** _M_names;
    static const locale::id* const _S_id_ctype[];
    static const locale::id* const _S_id_numeric[];
    static const locale::id* const _S_id_collate[];
    static const locale::id* const _S_id_time[];
    static const locale::id* const _S_id_monetary[];
    static const locale::id* const _S_id_messages[];
    static const locale::id* const* const _S_facet_categories[];

    void
    _M_add_reference() throw()
    { __gnu_cxx::__atomic_add_dispatch(&_M_refcount, 1); }

    void
    _M_remove_reference() throw()
    {

      ;
      if (__gnu_cxx::__exchange_and_add_dispatch(&_M_refcount, -1) == 1)
 {
          ;
   try
     { delete this; }
   catch(...)
     { }
 }
    }

    _Impl(const _Impl&, size_t);
    _Impl(const char*, size_t);
    _Impl(size_t) throw();

   ~_Impl() throw();

    _Impl(const _Impl&);

    void
    operator=(const _Impl&);

    bool
    _M_check_same_name()
    {
      bool __ret = true;
      if (_M_names[1])

 for (size_t __i = 0; __ret && __i < _S_categories_size - 1; ++__i)
   __ret = __builtin_strcmp(_M_names[__i], _M_names[__i + 1]) == 0;
      return __ret;
    }

    void
    _M_replace_categories(const _Impl*, category);

    void
    _M_replace_category(const _Impl*, const locale::id* const*);

    void
    _M_replace_facet(const _Impl*, const locale::id*);

    void
    _M_install_facet(const locale::id*, const facet*);

    template<typename _Facet>
      void
      _M_init_facet(_Facet* __facet)
      { _M_install_facet(&_Facet::id, __facet); }

    template<typename _Facet>
      void
      _M_init_facet_unchecked(_Facet* __facet)
      {
 __facet->_M_add_reference();
 _M_facets[_Facet::id._M_id()] = __facet;
      }

    void
    _M_install_cache(const facet*, size_t);

    void _M_init_extra(facet**);
    void _M_init_extra(void*, void*, const char*, const char*);
  };
# 632 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3
  template<typename _CharT>
    class collate : public locale::facet
    {
    public:



      typedef _CharT char_type;
      typedef basic_string<_CharT> string_type;


    protected:


      __c_locale _M_c_locale_collate;

    public:

      static locale::id id;
# 659 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3
      explicit
      collate(size_t __refs = 0)
      : facet(__refs), _M_c_locale_collate(_S_get_c_locale())
      { }
# 673 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3
      explicit
      collate(__c_locale __cloc, size_t __refs = 0)
      : facet(__refs), _M_c_locale_collate(_S_clone_c_locale(__cloc))
      { }
# 690 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3
      int
      compare(const _CharT* __lo1, const _CharT* __hi1,
       const _CharT* __lo2, const _CharT* __hi2) const
      { return this->do_compare(__lo1, __hi1, __lo2, __hi2); }
# 709 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3
      string_type
      transform(const _CharT* __lo, const _CharT* __hi) const
      { return this->do_transform(__lo, __hi); }
# 723 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3
      long
      hash(const _CharT* __lo, const _CharT* __hi) const
      { return this->do_hash(__lo, __hi); }


      int
      _M_compare(const _CharT*, const _CharT*) const throw();

      size_t
      _M_transform(_CharT*, const _CharT*, size_t) const throw();

  protected:

      virtual
      ~collate()
      { _S_destroy_c_locale(_M_c_locale_collate); }
# 752 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3
      virtual int
      do_compare(const _CharT* __lo1, const _CharT* __hi1,
   const _CharT* __lo2, const _CharT* __hi2) const;
# 766 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3
      virtual string_type
      do_transform(const _CharT* __lo, const _CharT* __hi) const;
# 779 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 3
      virtual long
      do_hash(const _CharT* __lo, const _CharT* __hi) const;
    };

  template<typename _CharT>
    locale::id collate<_CharT>::id;


  template<>
    int
    collate<char>::_M_compare(const char*, const char*) const throw();

  template<>
    size_t
    collate<char>::_M_transform(char*, const char*, size_t) const throw();


  template<>
    int
    collate<wchar_t>::_M_compare(const wchar_t*, const wchar_t*) const throw();

  template<>
    size_t
    collate<wchar_t>::_M_transform(wchar_t*, const wchar_t*, size_t) const throw();



  template<typename _CharT>
    class collate_byname : public collate<_CharT>
    {
    public:


      typedef _CharT char_type;
      typedef basic_string<_CharT> string_type;


      explicit
      collate_byname(const char* __s, size_t __refs = 0)
      : collate<_CharT>(__refs)
      {
 if (__builtin_strcmp(__s, "C") != 0
     && __builtin_strcmp(__s, "POSIX") != 0)
   {
     this->_S_destroy_c_locale(this->_M_c_locale_collate);
     this->_S_create_c_locale(this->_M_c_locale_collate, __s);
   }
      }







    protected:
      virtual
      ~collate_byname() { }
    };


}

# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.tcc" 1 3
# 37 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.tcc" 3
       
# 38 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.tcc" 3

namespace std
{


  template<typename _Facet>
    locale::
    locale(const locale& __other, _Facet* __f)
    {
      _M_impl = new _Impl(*__other._M_impl, 1);

      try
 { _M_impl->_M_install_facet(&_Facet::id, __f); }
      catch(...)
 {
   _M_impl->_M_remove_reference();
   throw;
 }
      delete [] _M_impl->_M_names[0];
      _M_impl->_M_names[0] = 0;
    }

  template<typename _Facet>
    locale
    locale::
    combine(const locale& __other) const
    {
      _Impl* __tmp = new _Impl(*_M_impl, 1);
      try
 {
   __tmp->_M_replace_facet(__other._M_impl, &_Facet::id);
 }
      catch(...)
 {
   __tmp->_M_remove_reference();
   throw;
 }
      return locale(__tmp);
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    bool
    locale::
    operator()(const basic_string<_CharT, _Traits, _Alloc>& __s1,
        const basic_string<_CharT, _Traits, _Alloc>& __s2) const
    {
      typedef std::collate<_CharT> __collate_type;
      const __collate_type& __collate = use_facet<__collate_type>(*this);
      return (__collate.compare(__s1.data(), __s1.data() + __s1.length(),
    __s2.data(), __s2.data() + __s2.length()) < 0);
    }
# 102 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.tcc" 3
  template<typename _Facet>
    bool
    has_facet(const locale& __loc) throw()
    {
      const size_t __i = _Facet::id._M_id();
      const locale::facet** __facets = __loc._M_impl->_M_facets;
      return (__i < __loc._M_impl->_M_facets_size

       && dynamic_cast<const _Facet*>(__facets[__i]));



    }
# 130 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.tcc" 3
  template<typename _Facet>
    const _Facet&
    use_facet(const locale& __loc)
    {
      const size_t __i = _Facet::id._M_id();
      const locale::facet** __facets = __loc._M_impl->_M_facets;
      if (__i >= __loc._M_impl->_M_facets_size || !__facets[__i])
        __throw_bad_cast();

      return dynamic_cast<const _Facet&>(*__facets[__i]);



    }



  template<typename _CharT>
    int
    collate<_CharT>::_M_compare(const _CharT*, const _CharT*) const throw ()
    { return 0; }


  template<typename _CharT>
    size_t
    collate<_CharT>::_M_transform(_CharT*, const _CharT*, size_t) const throw ()
    { return 0; }

  template<typename _CharT>
    int
    collate<_CharT>::
    do_compare(const _CharT* __lo1, const _CharT* __hi1,
        const _CharT* __lo2, const _CharT* __hi2) const
    {


      const string_type __one(__lo1, __hi1);
      const string_type __two(__lo2, __hi2);

      const _CharT* __p = __one.c_str();
      const _CharT* __pend = __one.data() + __one.length();
      const _CharT* __q = __two.c_str();
      const _CharT* __qend = __two.data() + __two.length();




      for (;;)
 {
   const int __res = _M_compare(__p, __q);
   if (__res)
     return __res;

   __p += char_traits<_CharT>::length(__p);
   __q += char_traits<_CharT>::length(__q);
   if (__p == __pend && __q == __qend)
     return 0;
   else if (__p == __pend)
     return -1;
   else if (__q == __qend)
     return 1;

   __p++;
   __q++;
 }
    }

  template<typename _CharT>
    typename collate<_CharT>::string_type
    collate<_CharT>::
    do_transform(const _CharT* __lo, const _CharT* __hi) const
    {
      string_type __ret;


      const string_type __str(__lo, __hi);

      const _CharT* __p = __str.c_str();
      const _CharT* __pend = __str.data() + __str.length();

      size_t __len = (__hi - __lo) * 2;

      _CharT* __c = new _CharT[__len];

      try
 {



   for (;;)
     {

       size_t __res = _M_transform(__c, __p, __len);


       if (__res >= __len)
  {
    __len = __res + 1;
    delete [] __c, __c = 0;
    __c = new _CharT[__len];
    __res = _M_transform(__c, __p, __len);
  }

       __ret.append(__c, __res);
       __p += char_traits<_CharT>::length(__p);
       if (__p == __pend)
  break;

       __p++;
       __ret.push_back(_CharT());
     }
 }
      catch(...)
 {
   delete [] __c;
   throw;
 }

      delete [] __c;

      return __ret;
    }

  template<typename _CharT>
    long
    collate<_CharT>::
    do_hash(const _CharT* __lo, const _CharT* __hi) const
    {
      unsigned long __val = 0;
      for (; __lo < __hi; ++__lo)
 __val =
   *__lo + ((__val << 7)
     | (__val >> (__gnu_cxx::__numeric_traits<unsigned long>::
    __digits - 7)));
      return static_cast<long>(__val);
    }




  extern template class collate<char>;
  extern template class collate_byname<char>;

  extern template
    const collate<char>&
    use_facet<collate<char> >(const locale&);

  extern template
    bool
    has_facet<collate<char> >(const locale&);


  extern template class collate<wchar_t>;
  extern template class collate_byname<wchar_t>;

  extern template
    const collate<wchar_t>&
    use_facet<collate<wchar_t> >(const locale&);

  extern template
    bool
    has_facet<collate<wchar_t> >(const locale&);




}
# 843 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_classes.h" 2 3
# 42 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 2 3


# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/stdexcept" 1 3
# 36 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/stdexcept" 3
       
# 37 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/stdexcept" 3




namespace std
{

# 69 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/stdexcept" 3
  typedef basic_string<char> __cow_string;


  struct __sso_string
  {
    struct __str
    {
      const char* _M_p;
      size_t _M_string_length;
      char _M_local_buf[16];
    };

    union {
      __str _M_s;
      char _M_bytes[sizeof(__str)];
    };

    __sso_string() throw();
    __sso_string(const std::string&);
    __sso_string(const char*, size_t);
    __sso_string(const __sso_string&);
    __sso_string& operator=(const __sso_string&);
    ~__sso_string();




  };
# 113 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/stdexcept" 3
  class logic_error : public exception
  {
    __cow_string _M_msg;

  public:

    explicit
    logic_error(const string& __arg);
# 132 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/stdexcept" 3
    virtual ~logic_error() throw();



    virtual const char*
    what() const throw();
  };



  class domain_error : public logic_error
  {
  public:
    explicit domain_error(const string& __arg);



    virtual ~domain_error() throw();
  };


  class invalid_argument : public logic_error
  {
  public:
    explicit invalid_argument(const string& __arg);



    virtual ~invalid_argument() throw();
  };



  class length_error : public logic_error
  {
  public:
    explicit length_error(const string& __arg);



    virtual ~length_error() throw();
  };



  class out_of_range : public logic_error
  {
  public:
    explicit out_of_range(const string& __arg);



    virtual ~out_of_range() throw();
  };






  class runtime_error : public exception
  {
    __cow_string _M_msg;

  public:

    explicit
    runtime_error(const string& __arg);
# 211 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/stdexcept" 3
    virtual ~runtime_error() throw();



    virtual const char*
    what() const throw();
  };


  class range_error : public runtime_error
  {
  public:
    explicit range_error(const string& __arg);



    virtual ~range_error() throw();
  };


  class overflow_error : public runtime_error
  {
  public:
    explicit overflow_error(const string& __arg);



    virtual ~overflow_error() throw();
  };


  class underflow_error : public runtime_error
  {
  public:
    explicit underflow_error(const string& __arg);



    virtual ~underflow_error() throw();
  };




}
# 45 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 2 3




namespace std
{






  enum _Ios_Fmtflags
    {
      _S_boolalpha = 1L << 0,
      _S_dec = 1L << 1,
      _S_fixed = 1L << 2,
      _S_hex = 1L << 3,
      _S_internal = 1L << 4,
      _S_left = 1L << 5,
      _S_oct = 1L << 6,
      _S_right = 1L << 7,
      _S_scientific = 1L << 8,
      _S_showbase = 1L << 9,
      _S_showpoint = 1L << 10,
      _S_showpos = 1L << 11,
      _S_skipws = 1L << 12,
      _S_unitbuf = 1L << 13,
      _S_uppercase = 1L << 14,
      _S_adjustfield = _S_left | _S_right | _S_internal,
      _S_basefield = _S_dec | _S_oct | _S_hex,
      _S_floatfield = _S_scientific | _S_fixed,
      _S_ios_fmtflags_end = 1L << 16,
      _S_ios_fmtflags_max = 0x7fffffff,
      _S_ios_fmtflags_min = ~0x7fffffff
    };

  inline _Ios_Fmtflags
  operator&(_Ios_Fmtflags __a, _Ios_Fmtflags __b)
  { return _Ios_Fmtflags(static_cast<int>(__a) & static_cast<int>(__b)); }

  inline _Ios_Fmtflags
  operator|(_Ios_Fmtflags __a, _Ios_Fmtflags __b)
  { return _Ios_Fmtflags(static_cast<int>(__a) | static_cast<int>(__b)); }

  inline _Ios_Fmtflags
  operator^(_Ios_Fmtflags __a, _Ios_Fmtflags __b)
  { return _Ios_Fmtflags(static_cast<int>(__a) ^ static_cast<int>(__b)); }

  inline _Ios_Fmtflags
  operator~(_Ios_Fmtflags __a)
  { return _Ios_Fmtflags(~static_cast<int>(__a)); }

  inline const _Ios_Fmtflags&
  operator|=(_Ios_Fmtflags& __a, _Ios_Fmtflags __b)
  { return __a = __a | __b; }

  inline const _Ios_Fmtflags&
  operator&=(_Ios_Fmtflags& __a, _Ios_Fmtflags __b)
  { return __a = __a & __b; }

  inline const _Ios_Fmtflags&
  operator^=(_Ios_Fmtflags& __a, _Ios_Fmtflags __b)
  { return __a = __a ^ __b; }


  enum _Ios_Openmode
    {
      _S_app = 1L << 0,
      _S_ate = 1L << 1,
      _S_bin = 1L << 2,
      _S_in = 1L << 3,
      _S_out = 1L << 4,
      _S_trunc = 1L << 5,
      _S_ios_openmode_end = 1L << 16,
      _S_ios_openmode_max = 0x7fffffff,
      _S_ios_openmode_min = ~0x7fffffff
    };

  inline _Ios_Openmode
  operator&(_Ios_Openmode __a, _Ios_Openmode __b)
  { return _Ios_Openmode(static_cast<int>(__a) & static_cast<int>(__b)); }

  inline _Ios_Openmode
  operator|(_Ios_Openmode __a, _Ios_Openmode __b)
  { return _Ios_Openmode(static_cast<int>(__a) | static_cast<int>(__b)); }

  inline _Ios_Openmode
  operator^(_Ios_Openmode __a, _Ios_Openmode __b)
  { return _Ios_Openmode(static_cast<int>(__a) ^ static_cast<int>(__b)); }

  inline _Ios_Openmode
  operator~(_Ios_Openmode __a)
  { return _Ios_Openmode(~static_cast<int>(__a)); }

  inline const _Ios_Openmode&
  operator|=(_Ios_Openmode& __a, _Ios_Openmode __b)
  { return __a = __a | __b; }

  inline const _Ios_Openmode&
  operator&=(_Ios_Openmode& __a, _Ios_Openmode __b)
  { return __a = __a & __b; }

  inline const _Ios_Openmode&
  operator^=(_Ios_Openmode& __a, _Ios_Openmode __b)
  { return __a = __a ^ __b; }


  enum _Ios_Iostate
    {
      _S_goodbit = 0,
      _S_badbit = 1L << 0,
      _S_eofbit = 1L << 1,
      _S_failbit = 1L << 2,
      _S_ios_iostate_end = 1L << 16,
      _S_ios_iostate_max = 0x7fffffff,
      _S_ios_iostate_min = ~0x7fffffff
    };

  inline _Ios_Iostate
  operator&(_Ios_Iostate __a, _Ios_Iostate __b)
  { return _Ios_Iostate(static_cast<int>(__a) & static_cast<int>(__b)); }

  inline _Ios_Iostate
  operator|(_Ios_Iostate __a, _Ios_Iostate __b)
  { return _Ios_Iostate(static_cast<int>(__a) | static_cast<int>(__b)); }

  inline _Ios_Iostate
  operator^(_Ios_Iostate __a, _Ios_Iostate __b)
  { return _Ios_Iostate(static_cast<int>(__a) ^ static_cast<int>(__b)); }

  inline _Ios_Iostate
  operator~(_Ios_Iostate __a)
  { return _Ios_Iostate(~static_cast<int>(__a)); }

  inline const _Ios_Iostate&
  operator|=(_Ios_Iostate& __a, _Ios_Iostate __b)
  { return __a = __a | __b; }

  inline const _Ios_Iostate&
  operator&=(_Ios_Iostate& __a, _Ios_Iostate __b)
  { return __a = __a & __b; }

  inline const _Ios_Iostate&
  operator^=(_Ios_Iostate& __a, _Ios_Iostate __b)
  { return __a = __a ^ __b; }


  enum _Ios_Seekdir
    {
      _S_beg = 0,
      _S_cur = 1,
      _S_end = 2,
      _S_ios_seekdir_end = 1L << 16
    };
# 228 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 3
  class ios_base
  {
# 246 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 3
  public:
# 276 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 3
    class failure : public exception
    {
    public:


      explicit
      failure(const string& __str) throw();



      virtual
      ~failure() throw();

      virtual const char*
      what() const throw();

    private:
      string _M_msg;
    };
# 323 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 3
    typedef _Ios_Fmtflags fmtflags;


    static const fmtflags boolalpha = _S_boolalpha;


    static const fmtflags dec = _S_dec;


    static const fmtflags fixed = _S_fixed;


    static const fmtflags hex = _S_hex;




    static const fmtflags internal = _S_internal;



    static const fmtflags left = _S_left;


    static const fmtflags oct = _S_oct;



    static const fmtflags right = _S_right;


    static const fmtflags scientific = _S_scientific;



    static const fmtflags showbase = _S_showbase;



    static const fmtflags showpoint = _S_showpoint;


    static const fmtflags showpos = _S_showpos;


    static const fmtflags skipws = _S_skipws;


    static const fmtflags unitbuf = _S_unitbuf;



    static const fmtflags uppercase = _S_uppercase;


    static const fmtflags adjustfield = _S_adjustfield;


    static const fmtflags basefield = _S_basefield;


    static const fmtflags floatfield = _S_floatfield;
# 398 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 3
    typedef _Ios_Iostate iostate;



    static const iostate badbit = _S_badbit;


    static const iostate eofbit = _S_eofbit;




    static const iostate failbit = _S_failbit;


    static const iostate goodbit = _S_goodbit;
# 429 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 3
    typedef _Ios_Openmode openmode;


    static const openmode app = _S_app;


    static const openmode ate = _S_ate;




    static const openmode binary = _S_bin;


    static const openmode in = _S_in;


    static const openmode out = _S_out;


    static const openmode trunc = _S_trunc;
# 461 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 3
    typedef _Ios_Seekdir seekdir;


    static const seekdir beg = _S_beg;


    static const seekdir cur = _S_cur;


    static const seekdir end = _S_end;


    typedef int io_state;
    typedef int open_mode;
    typedef int seek_dir;

    typedef std::streampos streampos;
    typedef std::streamoff streamoff;
# 487 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 3
    enum event
    {
      erase_event,
      imbue_event,
      copyfmt_event
    };
# 504 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 3
    typedef void (*event_callback) (event __e, ios_base& __b, int __i);
# 516 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 3
    void
    register_callback(event_callback __fn, int __index);

  protected:
    streamsize _M_precision;
    streamsize _M_width;
    fmtflags _M_flags;
    iostate _M_exception;
    iostate _M_streambuf_state;



    struct _Callback_list
    {

      _Callback_list* _M_next;
      ios_base::event_callback _M_fn;
      int _M_index;
      _Atomic_word _M_refcount;

      _Callback_list(ios_base::event_callback __fn, int __index,
       _Callback_list* __cb)
      : _M_next(__cb), _M_fn(__fn), _M_index(__index), _M_refcount(0) { }

      void
      _M_add_reference() { __gnu_cxx::__atomic_add_dispatch(&_M_refcount, 1); }


      int
      _M_remove_reference()
      {

        ;
        int __res = __gnu_cxx::__exchange_and_add_dispatch(&_M_refcount, -1);
        if (__res == 0)
          {
            ;
          }
        return __res;
      }
    };

     _Callback_list* _M_callbacks;

    void
    _M_call_callbacks(event __ev) throw();

    void
    _M_dispose_callbacks(void) throw();


    struct _Words
    {
      void* _M_pword;
      long _M_iword;
      _Words() : _M_pword(0), _M_iword(0) { }
    };


    _Words _M_word_zero;



    enum { _S_local_word_size = 8 };
    _Words _M_local_word[_S_local_word_size];


    int _M_word_size;
    _Words* _M_word;

    _Words&
    _M_grow_words(int __index, bool __iword);


    locale _M_ios_locale;

    void
    _M_init() throw();

  public:





    class Init
    {
      friend class ios_base;
    public:
      Init();
      ~Init();

    private:
      static _Atomic_word _S_refcount;
      static bool _S_synced_with_stdio;
    };






    fmtflags
    flags() const
    { return _M_flags; }
# 629 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 3
    fmtflags
    flags(fmtflags __fmtfl)
    {
      fmtflags __old = _M_flags;
      _M_flags = __fmtfl;
      return __old;
    }
# 645 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 3
    fmtflags
    setf(fmtflags __fmtfl)
    {
      fmtflags __old = _M_flags;
      _M_flags |= __fmtfl;
      return __old;
    }
# 662 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 3
    fmtflags
    setf(fmtflags __fmtfl, fmtflags __mask)
    {
      fmtflags __old = _M_flags;
      _M_flags &= ~__mask;
      _M_flags |= (__fmtfl & __mask);
      return __old;
    }







    void
    unsetf(fmtflags __mask)
    { _M_flags &= ~__mask; }
# 688 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 3
    streamsize
    precision() const
    { return _M_precision; }






    streamsize
    precision(streamsize __prec)
    {
      streamsize __old = _M_precision;
      _M_precision = __prec;
      return __old;
    }







    streamsize
    width() const
    { return _M_width; }






    streamsize
    width(streamsize __wide)
    {
      streamsize __old = _M_width;
      _M_width = __wide;
      return __old;
    }
# 739 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 3
    static bool
    sync_with_stdio(bool __sync = true);
# 751 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 3
    locale
    imbue(const locale& __loc) throw();
# 762 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 3
    locale
    getloc() const
    { return _M_ios_locale; }
# 773 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 3
    const locale&
    _M_getloc() const
    { return _M_ios_locale; }
# 792 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 3
    static int
    xalloc() throw();
# 808 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 3
    long&
    iword(int __ix)
    {
      _Words& __word = (__ix < _M_word_size)
   ? _M_word[__ix] : _M_grow_words(__ix, true);
      return __word._M_iword;
    }
# 829 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 3
    void*&
    pword(int __ix)
    {
      _Words& __word = (__ix < _M_word_size)
   ? _M_word[__ix] : _M_grow_words(__ix, false);
      return __word._M_pword;
    }
# 846 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 3
    virtual ~ios_base();

  protected:
    ios_base() throw ();




  private:
    ios_base(const ios_base&);

    ios_base&
    operator=(const ios_base&);
# 873 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 3
  };



  inline ios_base&
  boolalpha(ios_base& __base)
  {
    __base.setf(ios_base::boolalpha);
    return __base;
  }


  inline ios_base&
  noboolalpha(ios_base& __base)
  {
    __base.unsetf(ios_base::boolalpha);
    return __base;
  }


  inline ios_base&
  showbase(ios_base& __base)
  {
    __base.setf(ios_base::showbase);
    return __base;
  }


  inline ios_base&
  noshowbase(ios_base& __base)
  {
    __base.unsetf(ios_base::showbase);
    return __base;
  }


  inline ios_base&
  showpoint(ios_base& __base)
  {
    __base.setf(ios_base::showpoint);
    return __base;
  }


  inline ios_base&
  noshowpoint(ios_base& __base)
  {
    __base.unsetf(ios_base::showpoint);
    return __base;
  }


  inline ios_base&
  showpos(ios_base& __base)
  {
    __base.setf(ios_base::showpos);
    return __base;
  }


  inline ios_base&
  noshowpos(ios_base& __base)
  {
    __base.unsetf(ios_base::showpos);
    return __base;
  }


  inline ios_base&
  skipws(ios_base& __base)
  {
    __base.setf(ios_base::skipws);
    return __base;
  }


  inline ios_base&
  noskipws(ios_base& __base)
  {
    __base.unsetf(ios_base::skipws);
    return __base;
  }


  inline ios_base&
  uppercase(ios_base& __base)
  {
    __base.setf(ios_base::uppercase);
    return __base;
  }


  inline ios_base&
  nouppercase(ios_base& __base)
  {
    __base.unsetf(ios_base::uppercase);
    return __base;
  }


  inline ios_base&
  unitbuf(ios_base& __base)
  {
     __base.setf(ios_base::unitbuf);
     return __base;
  }


  inline ios_base&
  nounitbuf(ios_base& __base)
  {
     __base.unsetf(ios_base::unitbuf);
     return __base;
  }



  inline ios_base&
  internal(ios_base& __base)
  {
     __base.setf(ios_base::internal, ios_base::adjustfield);
     return __base;
  }


  inline ios_base&
  left(ios_base& __base)
  {
    __base.setf(ios_base::left, ios_base::adjustfield);
    return __base;
  }


  inline ios_base&
  right(ios_base& __base)
  {
    __base.setf(ios_base::right, ios_base::adjustfield);
    return __base;
  }



  inline ios_base&
  dec(ios_base& __base)
  {
    __base.setf(ios_base::dec, ios_base::basefield);
    return __base;
  }


  inline ios_base&
  hex(ios_base& __base)
  {
    __base.setf(ios_base::hex, ios_base::basefield);
    return __base;
  }


  inline ios_base&
  oct(ios_base& __base)
  {
    __base.setf(ios_base::oct, ios_base::basefield);
    return __base;
  }



  inline ios_base&
  fixed(ios_base& __base)
  {
    __base.setf(ios_base::fixed, ios_base::floatfield);
    return __base;
  }


  inline ios_base&
  scientific(ios_base& __base)
  {
    __base.setf(ios_base::scientific, ios_base::floatfield);
    return __base;
  }
# 1076 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ios_base.h" 3

}
# 43 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ios" 2 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 1 3
# 36 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
       
# 37 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
# 45 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
namespace std
{


  template<typename _CharT, typename _Traits>
    streamsize
    __copy_streambufs_eof(basic_streambuf<_CharT, _Traits>*,
     basic_streambuf<_CharT, _Traits>*, bool&);
# 119 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
  template<typename _CharT, typename _Traits>
    class basic_streambuf
    {
    public:






      typedef _CharT char_type;
      typedef _Traits traits_type;
      typedef typename traits_type::int_type int_type;
      typedef typename traits_type::pos_type pos_type;
      typedef typename traits_type::off_type off_type;




      typedef basic_streambuf<char_type, traits_type> __streambuf_type;


      friend class basic_ios<char_type, traits_type>;
      friend class basic_istream<char_type, traits_type>;
      friend class basic_ostream<char_type, traits_type>;
      friend class istreambuf_iterator<char_type, traits_type>;
      friend class ostreambuf_iterator<char_type, traits_type>;

      friend streamsize
      __copy_streambufs_eof<>(basic_streambuf*, basic_streambuf*, bool&);

      template<bool _IsMove, typename _CharT2>
        friend typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value,
            _CharT2*>::__type
        __copy_move_a2(istreambuf_iterator<_CharT2>,
         istreambuf_iterator<_CharT2>, _CharT2*);

      template<typename _CharT2>
        friend typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value,
      istreambuf_iterator<_CharT2> >::__type
        find(istreambuf_iterator<_CharT2>, istreambuf_iterator<_CharT2>,
      const _CharT2&);

      template<typename _CharT2, typename _Traits2>
        friend basic_istream<_CharT2, _Traits2>&
        operator>>(basic_istream<_CharT2, _Traits2>&, _CharT2*);

      template<typename _CharT2, typename _Traits2, typename _Alloc>
        friend basic_istream<_CharT2, _Traits2>&
        operator>>(basic_istream<_CharT2, _Traits2>&,
     basic_string<_CharT2, _Traits2, _Alloc>&);

      template<typename _CharT2, typename _Traits2, typename _Alloc>
        friend basic_istream<_CharT2, _Traits2>&
        getline(basic_istream<_CharT2, _Traits2>&,
  basic_string<_CharT2, _Traits2, _Alloc>&, _CharT2);

    protected:







      char_type* _M_in_beg;
      char_type* _M_in_cur;
      char_type* _M_in_end;
      char_type* _M_out_beg;
      char_type* _M_out_cur;
      char_type* _M_out_end;


      locale _M_buf_locale;

  public:

      virtual
      ~basic_streambuf()
      { }
# 208 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      locale
      pubimbue(const locale& __loc)
      {
 locale __tmp(this->getloc());
 this->imbue(__loc);
 _M_buf_locale = __loc;
 return __tmp;
      }
# 225 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      locale
      getloc() const
      { return _M_buf_locale; }
# 238 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      basic_streambuf*
      pubsetbuf(char_type* __s, streamsize __n)
      { return this->setbuf(__s, __n); }
# 250 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      pos_type
      pubseekoff(off_type __off, ios_base::seekdir __way,
   ios_base::openmode __mode = ios_base::in | ios_base::out)
      { return this->seekoff(__off, __way, __mode); }
# 262 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      pos_type
      pubseekpos(pos_type __sp,
   ios_base::openmode __mode = ios_base::in | ios_base::out)
      { return this->seekpos(__sp, __mode); }




      int
      pubsync() { return this->sync(); }
# 283 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      streamsize
      in_avail()
      {
 const streamsize __ret = this->egptr() - this->gptr();
 return __ret ? __ret : this->showmanyc();
      }
# 297 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      int_type
      snextc()
      {
 int_type __ret = traits_type::eof();
 if (__builtin_expect(!traits_type::eq_int_type(this->sbumpc(),
             __ret), true))
   __ret = this->sgetc();
 return __ret;
      }
# 315 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      int_type
      sbumpc()
      {
 int_type __ret;
 if (__builtin_expect(this->gptr() < this->egptr(), true))
   {
     __ret = traits_type::to_int_type(*this->gptr());
     this->gbump(1);
   }
 else
   __ret = this->uflow();
 return __ret;
      }
# 337 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      int_type
      sgetc()
      {
 int_type __ret;
 if (__builtin_expect(this->gptr() < this->egptr(), true))
   __ret = traits_type::to_int_type(*this->gptr());
 else
   __ret = this->underflow();
 return __ret;
      }
# 356 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      streamsize
      sgetn(char_type* __s, streamsize __n)
      { return this->xsgetn(__s, __n); }
# 371 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      int_type
      sputbackc(char_type __c)
      {
 int_type __ret;
 const bool __testpos = this->eback() < this->gptr();
 if (__builtin_expect(!__testpos ||
        !traits_type::eq(__c, this->gptr()[-1]), false))
   __ret = this->pbackfail(traits_type::to_int_type(__c));
 else
   {
     this->gbump(-1);
     __ret = traits_type::to_int_type(*this->gptr());
   }
 return __ret;
      }
# 396 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      int_type
      sungetc()
      {
 int_type __ret;
 if (__builtin_expect(this->eback() < this->gptr(), true))
   {
     this->gbump(-1);
     __ret = traits_type::to_int_type(*this->gptr());
   }
 else
   __ret = this->pbackfail();
 return __ret;
      }
# 423 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      int_type
      sputc(char_type __c)
      {
 int_type __ret;
 if (__builtin_expect(this->pptr() < this->epptr(), true))
   {
     *this->pptr() = __c;
     this->pbump(1);
     __ret = traits_type::to_int_type(__c);
   }
 else
   __ret = this->overflow(traits_type::to_int_type(__c));
 return __ret;
      }
# 449 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      streamsize
      sputn(const char_type* __s, streamsize __n)
      { return this->xsputn(__s, __n); }

    protected:
# 463 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      basic_streambuf()
      : _M_in_beg(0), _M_in_cur(0), _M_in_end(0),
      _M_out_beg(0), _M_out_cur(0), _M_out_end(0),
      _M_buf_locale(locale())
      { }
# 481 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      char_type*
      eback() const { return _M_in_beg; }

      char_type*
      gptr() const { return _M_in_cur; }

      char_type*
      egptr() const { return _M_in_end; }
# 497 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      void
      gbump(int __n) { _M_in_cur += __n; }
# 508 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      void
      setg(char_type* __gbeg, char_type* __gnext, char_type* __gend)
      {
 _M_in_beg = __gbeg;
 _M_in_cur = __gnext;
 _M_in_end = __gend;
      }
# 528 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      char_type*
      pbase() const { return _M_out_beg; }

      char_type*
      pptr() const { return _M_out_cur; }

      char_type*
      epptr() const { return _M_out_end; }
# 544 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      void
      pbump(int __n) { _M_out_cur += __n; }
# 554 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      void
      setp(char_type* __pbeg, char_type* __pend)
      {
 _M_out_beg = _M_out_cur = __pbeg;
 _M_out_end = __pend;
      }
# 575 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      virtual void
      imbue(const locale& __loc)
      { }
# 590 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      virtual basic_streambuf<char_type,_Traits>*
      setbuf(char_type*, streamsize)
      { return this; }
# 601 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      virtual pos_type
      seekoff(off_type, ios_base::seekdir,
       ios_base::openmode = ios_base::in | ios_base::out)
      { return pos_type(off_type(-1)); }
# 613 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      virtual pos_type
      seekpos(pos_type,
       ios_base::openmode = ios_base::in | ios_base::out)
      { return pos_type(off_type(-1)); }
# 626 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      virtual int
      sync() { return 0; }
# 648 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      virtual streamsize
      showmanyc() { return 0; }
# 664 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      virtual streamsize
      xsgetn(char_type* __s, streamsize __n);
# 686 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      virtual int_type
      underflow()
      { return traits_type::eof(); }
# 699 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      virtual int_type
      uflow()
      {
 int_type __ret = traits_type::eof();
 const bool __testeof = traits_type::eq_int_type(this->underflow(),
       __ret);
 if (!__testeof)
   {
     __ret = traits_type::to_int_type(*this->gptr());
     this->gbump(1);
   }
 return __ret;
      }
# 723 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      virtual int_type
      pbackfail(int_type __c = traits_type::eof())
      { return traits_type::eof(); }
# 741 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      virtual streamsize
      xsputn(const char_type* __s, streamsize __n);
# 767 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      virtual int_type
      overflow(int_type __c = traits_type::eof())
      { return traits_type::eof(); }



    public:
# 782 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
      void
      stossc()
      {
 if (this->gptr() < this->egptr())
   this->gbump(1);
 else
   this->uflow();
      }



      void
      __safe_gbump(streamsize __n) { _M_in_cur += __n; }

      void
      __safe_pbump(streamsize __n) { _M_out_cur += __n; }


    private:



      basic_streambuf(const basic_streambuf&);

      basic_streambuf&
      operator=(const basic_streambuf&);
# 822 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
    };
# 836 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 3
  template<>
    streamsize
    __copy_streambufs_eof(basic_streambuf<char>* __sbin,
     basic_streambuf<char>* __sbout, bool& __ineof);

  template<>
    streamsize
    __copy_streambufs_eof(basic_streambuf<wchar_t>* __sbin,
     basic_streambuf<wchar_t>* __sbout, bool& __ineof);



}

# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/streambuf.tcc" 1 3
# 37 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/streambuf.tcc" 3
       
# 38 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/streambuf.tcc" 3

namespace std
{


  template<typename _CharT, typename _Traits>
    streamsize
    basic_streambuf<_CharT, _Traits>::
    xsgetn(char_type* __s, streamsize __n)
    {
      streamsize __ret = 0;
      while (__ret < __n)
 {
   const streamsize __buf_len = this->egptr() - this->gptr();
   if (__buf_len)
     {
       const streamsize __remaining = __n - __ret;
       const streamsize __len = std::min(__buf_len, __remaining);
       traits_type::copy(__s, this->gptr(), __len);
       __ret += __len;
       __s += __len;
       this->__safe_gbump(__len);
     }

   if (__ret < __n)
     {
       const int_type __c = this->uflow();
       if (!traits_type::eq_int_type(__c, traits_type::eof()))
  {
    traits_type::assign(*__s++, traits_type::to_char_type(__c));
    ++__ret;
  }
       else
  break;
     }
 }
      return __ret;
    }

  template<typename _CharT, typename _Traits>
    streamsize
    basic_streambuf<_CharT, _Traits>::
    xsputn(const char_type* __s, streamsize __n)
    {
      streamsize __ret = 0;
      while (__ret < __n)
 {
   const streamsize __buf_len = this->epptr() - this->pptr();
   if (__buf_len)
     {
       const streamsize __remaining = __n - __ret;
       const streamsize __len = std::min(__buf_len, __remaining);
       traits_type::copy(this->pptr(), __s, __len);
       __ret += __len;
       __s += __len;
       this->__safe_pbump(__len);
     }

   if (__ret < __n)
     {
       int_type __c = this->overflow(traits_type::to_int_type(*__s));
       if (!traits_type::eq_int_type(__c, traits_type::eof()))
  {
    ++__ret;
    ++__s;
  }
       else
  break;
     }
 }
      return __ret;
    }




  template<typename _CharT, typename _Traits>
    streamsize
    __copy_streambufs_eof(basic_streambuf<_CharT, _Traits>* __sbin,
     basic_streambuf<_CharT, _Traits>* __sbout,
     bool& __ineof)
    {
      streamsize __ret = 0;
      __ineof = true;
      typename _Traits::int_type __c = __sbin->sgetc();
      while (!_Traits::eq_int_type(__c, _Traits::eof()))
 {
   __c = __sbout->sputc(_Traits::to_char_type(__c));
   if (_Traits::eq_int_type(__c, _Traits::eof()))
     {
       __ineof = false;
       break;
     }
   ++__ret;
   __c = __sbin->snextc();
 }
      return __ret;
    }

  template<typename _CharT, typename _Traits>
    inline streamsize
    __copy_streambufs(basic_streambuf<_CharT, _Traits>* __sbin,
        basic_streambuf<_CharT, _Traits>* __sbout)
    {
      bool __ineof;
      return __copy_streambufs_eof(__sbin, __sbout, __ineof);
    }




  extern template class basic_streambuf<char>;
  extern template
    streamsize
    __copy_streambufs(basic_streambuf<char>*,
        basic_streambuf<char>*);
  extern template
    streamsize
    __copy_streambufs_eof(basic_streambuf<char>*,
     basic_streambuf<char>*, bool&);


  extern template class basic_streambuf<wchar_t>;
  extern template
    streamsize
    __copy_streambufs(basic_streambuf<wchar_t>*,
        basic_streambuf<wchar_t>*);
  extern template
    streamsize
    __copy_streambufs_eof(basic_streambuf<wchar_t>*,
     basic_streambuf<wchar_t>*, bool&);




}
# 851 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/streambuf" 2 3
# 44 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ios" 2 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_ios.h" 1 3
# 33 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_ios.h" 3
       
# 34 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_ios.h" 3



# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 1 3
# 37 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
       
# 38 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3

# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cwctype" 1 3
# 39 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cwctype" 3
       
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cwctype" 3
# 50 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cwctype" 3
# 1 "/usr/include/wctype.h" 1 3 4







# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/stddef.h" 1 3 4
# 9 "/usr/include/wctype.h" 2 3 4
# 18 "/usr/include/wctype.h" 3 4
extern "C" {



typedef int wctype_t;




typedef int wctrans_t;


int __attribute__((__cdecl__)) iswalpha (wint_t);
int __attribute__((__cdecl__)) iswalnum (wint_t);

int __attribute__((__cdecl__)) iswblank (wint_t);

int __attribute__((__cdecl__)) iswcntrl (wint_t);
int __attribute__((__cdecl__)) iswctype (wint_t, wctype_t);
int __attribute__((__cdecl__)) iswdigit (wint_t);
int __attribute__((__cdecl__)) iswgraph (wint_t);
int __attribute__((__cdecl__)) iswlower (wint_t);
int __attribute__((__cdecl__)) iswprint (wint_t);
int __attribute__((__cdecl__)) iswpunct (wint_t);
int __attribute__((__cdecl__)) iswspace (wint_t);
int __attribute__((__cdecl__)) iswupper (wint_t);
int __attribute__((__cdecl__)) iswxdigit (wint_t);
wint_t __attribute__((__cdecl__)) towctrans (wint_t, wctrans_t);
wint_t __attribute__((__cdecl__)) towupper (wint_t);
wint_t __attribute__((__cdecl__)) towlower (wint_t);
wctrans_t __attribute__((__cdecl__)) wctrans (const char *);
wctype_t __attribute__((__cdecl__)) wctype (const char *);


extern int iswalpha_l (wint_t, locale_t);
extern int iswalnum_l (wint_t, locale_t);
extern int iswblank_l (wint_t, locale_t);
extern int iswcntrl_l (wint_t, locale_t);
extern int iswctype_l (wint_t, wctype_t, locale_t);
extern int iswdigit_l (wint_t, locale_t);
extern int iswgraph_l (wint_t, locale_t);
extern int iswlower_l (wint_t, locale_t);
extern int iswprint_l (wint_t, locale_t);
extern int iswpunct_l (wint_t, locale_t);
extern int iswspace_l (wint_t, locale_t);
extern int iswupper_l (wint_t, locale_t);
extern int iswxdigit_l (wint_t, locale_t);
extern wint_t towctrans_l (wint_t, wctrans_t, locale_t);
extern wint_t towupper_l (wint_t, locale_t);
extern wint_t towlower_l (wint_t, locale_t);
extern wctrans_t wctrans_l (const char *, locale_t);
extern wctype_t wctype_l (const char *, locale_t);


}
# 51 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cwctype" 2 3
# 80 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cwctype" 3
namespace std
{
  using ::wctrans_t;
  using ::wctype_t;
  using ::wint_t;

  using ::iswalnum;
  using ::iswalpha;

  using ::iswblank;

  using ::iswcntrl;
  using ::iswctype;
  using ::iswdigit;
  using ::iswgraph;
  using ::iswlower;
  using ::iswprint;
  using ::iswpunct;
  using ::iswspace;
  using ::iswupper;
  using ::iswxdigit;
  using ::towctrans;
  using ::towlower;
  using ::towupper;
  using ::wctrans;
  using ::wctype;
}
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 2 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cctype" 1 3
# 39 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cctype" 3
       
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cctype" 3
# 41 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 2 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/ctype_base.h" 1 3
# 31 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/ctype_base.h" 3
namespace std
{



  struct ctype_base
  {

    typedef const int* __to_type;



    typedef char mask;
    static const mask upper = 01;
    static const mask lower = 02;
    static const mask alpha = 01 | 02;
    static const mask digit = 04;
    static const mask xdigit = 0100 | 04;
    static const mask space = 010;
    static const mask print = 020 | 01 | 02 | 04 | 0200;
    static const mask graph = 020 | 01 | 02 | 04;
    static const mask cntrl = 040;
    static const mask punct = 020;
    static const mask alnum = 01 | 02 | 04;



  };


}
# 42 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 2 3






# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/streambuf_iterator.h" 1 3
# 33 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/streambuf_iterator.h" 3
       
# 34 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/streambuf_iterator.h" 3




namespace std
{

# 49 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/streambuf_iterator.h" 3
  template<typename _CharT, typename _Traits>
    class istreambuf_iterator
    : public iterator<input_iterator_tag, _CharT, typename _Traits::off_type,
                      _CharT*,




        _CharT&>

    {
    public:



      typedef _CharT char_type;
      typedef _Traits traits_type;
      typedef typename _Traits::int_type int_type;
      typedef basic_streambuf<_CharT, _Traits> streambuf_type;
      typedef basic_istream<_CharT, _Traits> istream_type;


      template<typename _CharT2>
 friend typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value,
                      ostreambuf_iterator<_CharT2> >::__type
 copy(istreambuf_iterator<_CharT2>, istreambuf_iterator<_CharT2>,
      ostreambuf_iterator<_CharT2>);

      template<bool _IsMove, typename _CharT2>
 friend typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value,
            _CharT2*>::__type
 __copy_move_a2(istreambuf_iterator<_CharT2>,
         istreambuf_iterator<_CharT2>, _CharT2*);

      template<typename _CharT2>
 friend typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value,
               istreambuf_iterator<_CharT2> >::__type
 find(istreambuf_iterator<_CharT2>, istreambuf_iterator<_CharT2>,
      const _CharT2&);

    private:







      mutable streambuf_type* _M_sbuf;
      mutable int_type _M_c;

    public:

      istreambuf_iterator() throw()
      : _M_sbuf(0), _M_c(traits_type::eof()) { }
# 112 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/streambuf_iterator.h" 3
      istreambuf_iterator(istream_type& __s) throw()
      : _M_sbuf(__s.rdbuf()), _M_c(traits_type::eof()) { }


      istreambuf_iterator(streambuf_type* __s) throw()
      : _M_sbuf(__s), _M_c(traits_type::eof()) { }




      char_type
      operator*() const
      {







 return traits_type::to_char_type(_M_get());
      }


      istreambuf_iterator&
      operator++()
      {


                        ;
 if (_M_sbuf)
   {
     _M_sbuf->sbumpc();
     _M_c = traits_type::eof();
   }
 return *this;
      }


      istreambuf_iterator
      operator++(int)
      {


                        ;

 istreambuf_iterator __old = *this;
 if (_M_sbuf)
   {
     __old._M_c = _M_sbuf->sbumpc();
     _M_c = traits_type::eof();
   }
 return __old;
      }





      bool
      equal(const istreambuf_iterator& __b) const
      { return _M_at_eof() == __b._M_at_eof(); }

    private:
      int_type
      _M_get() const
      {
 const int_type __eof = traits_type::eof();
 int_type __ret = __eof;
 if (_M_sbuf)
   {
     if (!traits_type::eq_int_type(_M_c, __eof))
       __ret = _M_c;
     else if (!traits_type::eq_int_type((__ret = _M_sbuf->sgetc()),
            __eof))
       _M_c = __ret;
     else
       _M_sbuf = 0;
   }
 return __ret;
      }

      bool
      _M_at_eof() const
      {
 const int_type __eof = traits_type::eof();
 return traits_type::eq_int_type(_M_get(), __eof);
      }
    };

  template<typename _CharT, typename _Traits>
    inline bool
    operator==(const istreambuf_iterator<_CharT, _Traits>& __a,
        const istreambuf_iterator<_CharT, _Traits>& __b)
    { return __a.equal(__b); }

  template<typename _CharT, typename _Traits>
    inline bool
    operator!=(const istreambuf_iterator<_CharT, _Traits>& __a,
        const istreambuf_iterator<_CharT, _Traits>& __b)
    { return !__a.equal(__b); }


  template<typename _CharT, typename _Traits>
    class ostreambuf_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
    {
    public:



      typedef _CharT char_type;
      typedef _Traits traits_type;
      typedef basic_streambuf<_CharT, _Traits> streambuf_type;
      typedef basic_ostream<_CharT, _Traits> ostream_type;


      template<typename _CharT2>
 friend typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value,
                      ostreambuf_iterator<_CharT2> >::__type
 copy(istreambuf_iterator<_CharT2>, istreambuf_iterator<_CharT2>,
      ostreambuf_iterator<_CharT2>);

    private:
      streambuf_type* _M_sbuf;
      bool _M_failed;

    public:

      ostreambuf_iterator(ostream_type& __s) throw()
      : _M_sbuf(__s.rdbuf()), _M_failed(!_M_sbuf) { }


      ostreambuf_iterator(streambuf_type* __s) throw()
      : _M_sbuf(__s), _M_failed(!_M_sbuf) { }


      ostreambuf_iterator&
      operator=(_CharT __c)
      {
 if (!_M_failed &&
     _Traits::eq_int_type(_M_sbuf->sputc(__c), _Traits::eof()))
   _M_failed = true;
 return *this;
      }


      ostreambuf_iterator&
      operator*()
      { return *this; }


      ostreambuf_iterator&
      operator++(int)
      { return *this; }


      ostreambuf_iterator&
      operator++()
      { return *this; }


      bool
      failed() const throw()
      { return _M_failed; }

      ostreambuf_iterator&
      _M_put(const _CharT* __ws, streamsize __len)
      {
 if (__builtin_expect(!_M_failed, true)
     && __builtin_expect(this->_M_sbuf->sputn(__ws, __len) != __len,
    false))
   _M_failed = true;
 return *this;
      }
    };


  template<typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
                           ostreambuf_iterator<_CharT> >::__type
    copy(istreambuf_iterator<_CharT> __first,
  istreambuf_iterator<_CharT> __last,
  ostreambuf_iterator<_CharT> __result)
    {
      if (__first._M_sbuf && !__last._M_sbuf && !__result._M_failed)
 {
   bool __ineof;
   __copy_streambufs_eof(__first._M_sbuf, __result._M_sbuf, __ineof);
   if (!__ineof)
     __result._M_failed = true;
 }
      return __result;
    }

  template<bool _IsMove, typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
            ostreambuf_iterator<_CharT> >::__type
    __copy_move_a2(_CharT* __first, _CharT* __last,
     ostreambuf_iterator<_CharT> __result)
    {
      const streamsize __num = __last - __first;
      if (__num > 0)
 __result._M_put(__first, __num);
      return __result;
    }

  template<bool _IsMove, typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
        ostreambuf_iterator<_CharT> >::__type
    __copy_move_a2(const _CharT* __first, const _CharT* __last,
     ostreambuf_iterator<_CharT> __result)
    {
      const streamsize __num = __last - __first;
      if (__num > 0)
 __result._M_put(__first, __num);
      return __result;
    }

  template<bool _IsMove, typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
            _CharT*>::__type
    __copy_move_a2(istreambuf_iterator<_CharT> __first,
     istreambuf_iterator<_CharT> __last, _CharT* __result)
    {
      typedef istreambuf_iterator<_CharT> __is_iterator_type;
      typedef typename __is_iterator_type::traits_type traits_type;
      typedef typename __is_iterator_type::streambuf_type streambuf_type;
      typedef typename traits_type::int_type int_type;

      if (__first._M_sbuf && !__last._M_sbuf)
 {
   streambuf_type* __sb = __first._M_sbuf;
   int_type __c = __sb->sgetc();
   while (!traits_type::eq_int_type(__c, traits_type::eof()))
     {
       const streamsize __n = __sb->egptr() - __sb->gptr();
       if (__n > 1)
  {
    traits_type::copy(__result, __sb->gptr(), __n);
    __sb->__safe_gbump(__n);
    __result += __n;
    __c = __sb->underflow();
  }
       else
  {
    *__result++ = traits_type::to_char_type(__c);
    __c = __sb->snextc();
  }
     }
 }
      return __result;
    }

  template<typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
          istreambuf_iterator<_CharT> >::__type
    find(istreambuf_iterator<_CharT> __first,
  istreambuf_iterator<_CharT> __last, const _CharT& __val)
    {
      typedef istreambuf_iterator<_CharT> __is_iterator_type;
      typedef typename __is_iterator_type::traits_type traits_type;
      typedef typename __is_iterator_type::streambuf_type streambuf_type;
      typedef typename traits_type::int_type int_type;

      if (__first._M_sbuf && !__last._M_sbuf)
 {
   const int_type __ival = traits_type::to_int_type(__val);
   streambuf_type* __sb = __first._M_sbuf;
   int_type __c = __sb->sgetc();
   while (!traits_type::eq_int_type(__c, traits_type::eof())
   && !traits_type::eq_int_type(__c, __ival))
     {
       streamsize __n = __sb->egptr() - __sb->gptr();
       if (__n > 1)
  {
    const _CharT* __p = traits_type::find(__sb->gptr(),
       __n, __val);
    if (__p)
      __n = __p - __sb->gptr();
    __sb->__safe_gbump(__n);
    __c = __sb->sgetc();
  }
       else
  __c = __sb->snextc();
     }

   if (!traits_type::eq_int_type(__c, traits_type::eof()))
     __first._M_c = __c;
   else
     __first._M_sbuf = 0;
 }
      return __first;
    }




}
# 49 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 2 3

namespace std
{

# 71 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
  template<typename _Tp>
    void
    __convert_to_v(const char*, _Tp&, ios_base::iostate&,
     const __c_locale&) throw();


  template<>
    void
    __convert_to_v(const char*, float&, ios_base::iostate&,
     const __c_locale&) throw();

  template<>
    void
    __convert_to_v(const char*, double&, ios_base::iostate&,
     const __c_locale&) throw();

  template<>
    void
    __convert_to_v(const char*, long double&, ios_base::iostate&,
     const __c_locale&) throw();



  template<typename _CharT, typename _Traits>
    struct __pad
    {
      static void
      _S_pad(ios_base& __io, _CharT __fill, _CharT* __news,
      const _CharT* __olds, streamsize __newlen, streamsize __oldlen);
    };






  template<typename _CharT>
    _CharT*
    __add_grouping(_CharT* __s, _CharT __sep,
     const char* __gbeg, size_t __gsize,
     const _CharT* __first, const _CharT* __last);




  template<typename _CharT>
    inline
    ostreambuf_iterator<_CharT>
    __write(ostreambuf_iterator<_CharT> __s, const _CharT* __ws, int __len)
    {
      __s._M_put(__ws, __len);
      return __s;
    }


  template<typename _CharT, typename _OutIter>
    inline
    _OutIter
    __write(_OutIter __s, const _CharT* __ws, int __len)
    {
      for (int __j = 0; __j < __len; __j++, ++__s)
 *__s = __ws[__j];
      return __s;
    }
# 149 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
  template<typename _CharT>
    class __ctype_abstract_base : public locale::facet, public ctype_base
    {
    public:


      typedef _CharT char_type;
# 168 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      bool
      is(mask __m, char_type __c) const
      { return this->do_is(__m, __c); }
# 185 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      const char_type*
      is(const char_type *__lo, const char_type *__hi, mask *__vec) const
      { return this->do_is(__lo, __hi, __vec); }
# 201 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      const char_type*
      scan_is(mask __m, const char_type* __lo, const char_type* __hi) const
      { return this->do_scan_is(__m, __lo, __hi); }
# 217 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      const char_type*
      scan_not(mask __m, const char_type* __lo, const char_type* __hi) const
      { return this->do_scan_not(__m, __lo, __hi); }
# 231 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      char_type
      toupper(char_type __c) const
      { return this->do_toupper(__c); }
# 246 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      const char_type*
      toupper(char_type *__lo, const char_type* __hi) const
      { return this->do_toupper(__lo, __hi); }
# 260 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      char_type
      tolower(char_type __c) const
      { return this->do_tolower(__c); }
# 275 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      const char_type*
      tolower(char_type* __lo, const char_type* __hi) const
      { return this->do_tolower(__lo, __hi); }
# 292 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      char_type
      widen(char __c) const
      { return this->do_widen(__c); }
# 311 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      const char*
      widen(const char* __lo, const char* __hi, char_type* __to) const
      { return this->do_widen(__lo, __hi, __to); }
# 330 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      char
      narrow(char_type __c, char __dfault) const
      { return this->do_narrow(__c, __dfault); }
# 352 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      const char_type*
      narrow(const char_type* __lo, const char_type* __hi,
       char __dfault, char* __to) const
      { return this->do_narrow(__lo, __hi, __dfault, __to); }

    protected:
      explicit
      __ctype_abstract_base(size_t __refs = 0): facet(__refs) { }

      virtual
      ~__ctype_abstract_base() { }
# 377 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual bool
      do_is(mask __m, char_type __c) const = 0;
# 396 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual const char_type*
      do_is(const char_type* __lo, const char_type* __hi,
     mask* __vec) const = 0;
# 415 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual const char_type*
      do_scan_is(mask __m, const char_type* __lo,
   const char_type* __hi) const = 0;
# 434 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual const char_type*
      do_scan_not(mask __m, const char_type* __lo,
    const char_type* __hi) const = 0;
# 452 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual char_type
      do_toupper(char_type __c) const = 0;
# 469 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual const char_type*
      do_toupper(char_type* __lo, const char_type* __hi) const = 0;
# 485 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual char_type
      do_tolower(char_type __c) const = 0;
# 502 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual const char_type*
      do_tolower(char_type* __lo, const char_type* __hi) const = 0;
# 521 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual char_type
      do_widen(char __c) const = 0;
# 542 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual const char*
      do_widen(const char* __lo, const char* __hi, char_type* __to) const = 0;
# 563 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual char
      do_narrow(char_type __c, char __dfault) const = 0;
# 588 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual const char_type*
      do_narrow(const char_type* __lo, const char_type* __hi,
  char __dfault, char* __to) const = 0;
    };
# 611 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
  template<typename _CharT>
    class ctype : public __ctype_abstract_base<_CharT>
    {
    public:

      typedef _CharT char_type;
      typedef typename __ctype_abstract_base<_CharT>::mask mask;


      static locale::id id;

      explicit
      ctype(size_t __refs = 0) : __ctype_abstract_base<_CharT>(__refs) { }

   protected:
      virtual
      ~ctype();

      virtual bool
      do_is(mask __m, char_type __c) const;

      virtual const char_type*
      do_is(const char_type* __lo, const char_type* __hi, mask* __vec) const;

      virtual const char_type*
      do_scan_is(mask __m, const char_type* __lo, const char_type* __hi) const;

      virtual const char_type*
      do_scan_not(mask __m, const char_type* __lo,
    const char_type* __hi) const;

      virtual char_type
      do_toupper(char_type __c) const;

      virtual const char_type*
      do_toupper(char_type* __lo, const char_type* __hi) const;

      virtual char_type
      do_tolower(char_type __c) const;

      virtual const char_type*
      do_tolower(char_type* __lo, const char_type* __hi) const;

      virtual char_type
      do_widen(char __c) const;

      virtual const char*
      do_widen(const char* __lo, const char* __hi, char_type* __dest) const;

      virtual char
      do_narrow(char_type, char __dfault) const;

      virtual const char_type*
      do_narrow(const char_type* __lo, const char_type* __hi,
  char __dfault, char* __to) const;
    };

  template<typename _CharT>
    locale::id ctype<_CharT>::id;
# 680 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
  template<>
    class ctype<char> : public locale::facet, public ctype_base
    {
    public:


      typedef char char_type;

    protected:

      __c_locale _M_c_locale_ctype;
      bool _M_del;
      __to_type _M_toupper;
      __to_type _M_tolower;
      const mask* _M_table;
      mutable char _M_widen_ok;
      mutable char _M_widen[1 + static_cast<unsigned char>(-1)];
      mutable char _M_narrow[1 + static_cast<unsigned char>(-1)];
      mutable char _M_narrow_ok;


    public:

      static locale::id id;

      static const size_t table_size = 1 + static_cast<unsigned char>(-1);
# 717 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      explicit
      ctype(const mask* __table = 0, bool __del = false, size_t __refs = 0);
# 730 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      explicit
      ctype(__c_locale __cloc, const mask* __table = 0, bool __del = false,
     size_t __refs = 0);
# 743 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      inline bool
      is(mask __m, char __c) const;
# 758 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      inline const char*
      is(const char* __lo, const char* __hi, mask* __vec) const;
# 772 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      inline const char*
      scan_is(mask __m, const char* __lo, const char* __hi) const;
# 786 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      inline const char*
      scan_not(mask __m, const char* __lo, const char* __hi) const;
# 801 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      char_type
      toupper(char_type __c) const
      { return this->do_toupper(__c); }
# 818 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      const char_type*
      toupper(char_type *__lo, const char_type* __hi) const
      { return this->do_toupper(__lo, __hi); }
# 834 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      char_type
      tolower(char_type __c) const
      { return this->do_tolower(__c); }
# 851 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      const char_type*
      tolower(char_type* __lo, const char_type* __hi) const
      { return this->do_tolower(__lo, __hi); }
# 871 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      char_type
      widen(char __c) const
      {
 if (_M_widen_ok)
   return _M_widen[static_cast<unsigned char>(__c)];
 this->_M_widen_init();
 return this->do_widen(__c);
      }
# 898 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      const char*
      widen(const char* __lo, const char* __hi, char_type* __to) const
      {
 if (_M_widen_ok == 1)
   {
     __builtin_memcpy(__to, __lo, __hi - __lo);
     return __hi;
   }
 if (!_M_widen_ok)
   _M_widen_init();
 return this->do_widen(__lo, __hi, __to);
      }
# 929 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      char
      narrow(char_type __c, char __dfault) const
      {
 if (_M_narrow[static_cast<unsigned char>(__c)])
   return _M_narrow[static_cast<unsigned char>(__c)];
 const char __t = do_narrow(__c, __dfault);
 if (__t != __dfault)
   _M_narrow[static_cast<unsigned char>(__c)] = __t;
 return __t;
      }
# 962 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      const char_type*
      narrow(const char_type* __lo, const char_type* __hi,
      char __dfault, char* __to) const
      {
 if (__builtin_expect(_M_narrow_ok == 1, true))
   {
     __builtin_memcpy(__to, __lo, __hi - __lo);
     return __hi;
   }
 if (!_M_narrow_ok)
   _M_narrow_init();
 return this->do_narrow(__lo, __hi, __dfault, __to);
      }





      const mask*
      table() const throw()
      { return _M_table; }


      static const mask*
      classic_table() throw();
    protected:







      virtual
      ~ctype();
# 1011 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual char_type
      do_toupper(char_type __c) const;
# 1028 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual const char_type*
      do_toupper(char_type* __lo, const char_type* __hi) const;
# 1044 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual char_type
      do_tolower(char_type __c) const;
# 1061 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual const char_type*
      do_tolower(char_type* __lo, const char_type* __hi) const;
# 1081 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual char_type
      do_widen(char __c) const
      { return __c; }
# 1104 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual const char*
      do_widen(const char* __lo, const char* __hi, char_type* __to) const
      {
 __builtin_memcpy(__to, __lo, __hi - __lo);
 return __hi;
      }
# 1130 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual char
      do_narrow(char_type __c, char __dfault) const
      { return __c; }
# 1156 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual const char_type*
      do_narrow(const char_type* __lo, const char_type* __hi,
  char __dfault, char* __to) const
      {
 __builtin_memcpy(__to, __lo, __hi - __lo);
 return __hi;
      }

    private:
      void _M_narrow_init() const;
      void _M_widen_init() const;
    };
# 1181 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
  template<>
    class ctype<wchar_t> : public __ctype_abstract_base<wchar_t>
    {
    public:


      typedef wchar_t char_type;
      typedef wctype_t __wmask_type;

    protected:
      __c_locale _M_c_locale_ctype;


      bool _M_narrow_ok;
      char _M_narrow[128];
      wint_t _M_widen[1 + static_cast<unsigned char>(-1)];


      mask _M_bit[16];
      __wmask_type _M_wmask[16];

    public:


      static locale::id id;
# 1214 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      explicit
      ctype(size_t __refs = 0);
# 1225 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      explicit
      ctype(__c_locale __cloc, size_t __refs = 0);

    protected:
      __wmask_type
      _M_convert_to_wmask(const mask __m) const throw();


      virtual
      ~ctype();
# 1249 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual bool
      do_is(mask __m, char_type __c) const;
# 1268 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual const char_type*
      do_is(const char_type* __lo, const char_type* __hi, mask* __vec) const;
# 1286 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual const char_type*
      do_scan_is(mask __m, const char_type* __lo, const char_type* __hi) const;
# 1304 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual const char_type*
      do_scan_not(mask __m, const char_type* __lo,
    const char_type* __hi) const;
# 1321 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual char_type
      do_toupper(char_type __c) const;
# 1338 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual const char_type*
      do_toupper(char_type* __lo, const char_type* __hi) const;
# 1354 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual char_type
      do_tolower(char_type __c) const;
# 1371 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual const char_type*
      do_tolower(char_type* __lo, const char_type* __hi) const;
# 1391 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual char_type
      do_widen(char __c) const;
# 1413 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual const char*
      do_widen(const char* __lo, const char* __hi, char_type* __to) const;
# 1436 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual char
      do_narrow(char_type __c, char __dfault) const;
# 1462 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual const char_type*
      do_narrow(const char_type* __lo, const char_type* __hi,
  char __dfault, char* __to) const;


      void
      _M_initialize_ctype() throw();
    };



  template<typename _CharT>
    class ctype_byname : public ctype<_CharT>
    {
    public:
      typedef typename ctype<_CharT>::mask mask;

      explicit
      ctype_byname(const char* __s, size_t __refs = 0);







    protected:
      virtual
      ~ctype_byname() { };
    };


  template<>
    class ctype_byname<char> : public ctype<char>
    {
    public:
      explicit
      ctype_byname(const char* __s, size_t __refs = 0);






    protected:
      virtual
      ~ctype_byname();
    };


  template<>
    class ctype_byname<wchar_t> : public ctype<wchar_t>
    {
    public:
      explicit
      ctype_byname(const char* __s, size_t __refs = 0);






    protected:
      virtual
      ~ctype_byname();
    };



}


# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/ctype_inline.h" 1 3
# 37 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/x86_64-pc-cygwin/bits/ctype_inline.h" 3
namespace std
{


  bool
  ctype<char>::
  is(mask __m, char __c) const
  { return _M_table[static_cast<unsigned char>(__c)] & __m; }

  const char*
  ctype<char>::
  is(const char* __low, const char* __high, mask* __vec) const
  {
    while (__low < __high)
      *__vec++ = _M_table[static_cast<unsigned char>(*__low++)];
    return __high;
  }

  const char*
  ctype<char>::
  scan_is(mask __m, const char* __low, const char* __high) const
  {
    while (__low < __high && !this->is(__m, *__low))
      ++__low;
    return __low;
  }

  const char*
  ctype<char>::
  scan_not(mask __m, const char* __low, const char* __high) const
  {
    while (__low < __high && this->is(__m, *__low) != 0)
      ++__low;
    return __low;
  }


}
# 1535 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 2 3

namespace std
{



  class __num_base
  {
  public:


    enum
      {
 _S_ominus,
 _S_oplus,
 _S_ox,
 _S_oX,
 _S_odigits,
 _S_odigits_end = _S_odigits + 16,
 _S_oudigits = _S_odigits_end,
 _S_oudigits_end = _S_oudigits + 16,
 _S_oe = _S_odigits + 14,
 _S_oE = _S_oudigits + 14,
 _S_oend = _S_oudigits_end
      };






    static const char* _S_atoms_out;



    static const char* _S_atoms_in;

    enum
    {
      _S_iminus,
      _S_iplus,
      _S_ix,
      _S_iX,
      _S_izero,
      _S_ie = _S_izero + 14,
      _S_iE = _S_izero + 20,
      _S_iend = 26
    };



    static void
    _S_format_float(const ios_base& __io, char* __fptr, char __mod) throw();
  };

  template<typename _CharT>
    struct __numpunct_cache : public locale::facet
    {
      const char* _M_grouping;
      size_t _M_grouping_size;
      bool _M_use_grouping;
      const _CharT* _M_truename;
      size_t _M_truename_size;
      const _CharT* _M_falsename;
      size_t _M_falsename_size;
      _CharT _M_decimal_point;
      _CharT _M_thousands_sep;





      _CharT _M_atoms_out[__num_base::_S_oend];





      _CharT _M_atoms_in[__num_base::_S_iend];

      bool _M_allocated;

      __numpunct_cache(size_t __refs = 0)
      : facet(__refs), _M_grouping(0), _M_grouping_size(0),
 _M_use_grouping(false),
 _M_truename(0), _M_truename_size(0), _M_falsename(0),
 _M_falsename_size(0), _M_decimal_point(_CharT()),
 _M_thousands_sep(_CharT()), _M_allocated(false)
 { }

      ~__numpunct_cache();

      void
      _M_cache(const locale& __loc);

    private:
      __numpunct_cache&
      operator=(const __numpunct_cache&);

      explicit
      __numpunct_cache(const __numpunct_cache&);
    };

  template<typename _CharT>
    __numpunct_cache<_CharT>::~__numpunct_cache()
    {
      if (_M_allocated)
 {
   delete [] _M_grouping;
   delete [] _M_truename;
   delete [] _M_falsename;
 }
    }


# 1665 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
  template<typename _CharT>
    class numpunct : public locale::facet
    {
    public:



      typedef _CharT char_type;
      typedef basic_string<_CharT> string_type;

      typedef __numpunct_cache<_CharT> __cache_type;

    protected:
      __cache_type* _M_data;

    public:

      static locale::id id;






      explicit
      numpunct(size_t __refs = 0)
      : facet(__refs), _M_data(0)
      { _M_initialize_numpunct(); }
# 1703 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      explicit
      numpunct(__cache_type* __cache, size_t __refs = 0)
      : facet(__refs), _M_data(__cache)
      { _M_initialize_numpunct(); }
# 1717 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      explicit
      numpunct(__c_locale __cloc, size_t __refs = 0)
      : facet(__refs), _M_data(0)
      { _M_initialize_numpunct(__cloc); }
# 1731 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      char_type
      decimal_point() const
      { return this->do_decimal_point(); }
# 1744 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      char_type
      thousands_sep() const
      { return this->do_thousands_sep(); }
# 1775 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      string
      grouping() const
      { return this->do_grouping(); }
# 1788 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      string_type
      truename() const
      { return this->do_truename(); }
# 1801 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      string_type
      falsename() const
      { return this->do_falsename(); }

    protected:

      virtual
      ~numpunct();
# 1818 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual char_type
      do_decimal_point() const
      { return _M_data->_M_decimal_point; }
# 1830 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual char_type
      do_thousands_sep() const
      { return _M_data->_M_thousands_sep; }
# 1843 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual string
      do_grouping() const
      { return _M_data->_M_grouping; }
# 1856 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual string_type
      do_truename() const
      { return _M_data->_M_truename; }
# 1869 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual string_type
      do_falsename() const
      { return _M_data->_M_falsename; }


      void
      _M_initialize_numpunct(__c_locale __cloc = 0);
    };

  template<typename _CharT>
    locale::id numpunct<_CharT>::id;

  template<>
    numpunct<char>::~numpunct();

  template<>
    void
    numpunct<char>::_M_initialize_numpunct(__c_locale __cloc);


  template<>
    numpunct<wchar_t>::~numpunct();

  template<>
    void
    numpunct<wchar_t>::_M_initialize_numpunct(__c_locale __cloc);



  template<typename _CharT>
    class numpunct_byname : public numpunct<_CharT>
    {
    public:
      typedef _CharT char_type;
      typedef basic_string<_CharT> string_type;

      explicit
      numpunct_byname(const char* __s, size_t __refs = 0)
      : numpunct<_CharT>(__refs)
      {
 if (__builtin_strcmp(__s, "C") != 0
     && __builtin_strcmp(__s, "POSIX") != 0)
   {
     __c_locale __tmp;
     this->_S_create_c_locale(__tmp, __s);
     this->_M_initialize_numpunct(__tmp);
     this->_S_destroy_c_locale(__tmp);
   }
      }







    protected:
      virtual
      ~numpunct_byname() { }
    };




# 1947 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
  template<typename _CharT, typename _InIter>
    class num_get : public locale::facet
    {
    public:



      typedef _CharT char_type;
      typedef _InIter iter_type;



      static locale::id id;
# 1968 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      explicit
      num_get(size_t __refs = 0) : facet(__refs) { }
# 1994 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, bool& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }
# 2031 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, long& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }

      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, unsigned short& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }

      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, unsigned int& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }

      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, unsigned long& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }


      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, long long& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }

      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, unsigned long long& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }
# 2091 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, float& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }

      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, double& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }

      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, long double& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }
# 2134 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, void*& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }

    protected:

      virtual ~num_get() { }

     
      iter_type
      _M_extract_float(iter_type, iter_type, ios_base&, ios_base::iostate&,
         string&) const;

      template<typename _ValueT>

 iter_type
 _M_extract_int(iter_type, iter_type, ios_base&, ios_base::iostate&,
         _ValueT&) const;

      template<typename _CharT2>
      typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value, int>::__type
 _M_find(const _CharT2*, size_t __len, _CharT2 __c) const
 {
   int __ret = -1;
   if (__len <= 10)
     {
       if (__c >= _CharT2('0') && __c < _CharT2(_CharT2('0') + __len))
  __ret = __c - _CharT2('0');
     }
   else
     {
       if (__c >= _CharT2('0') && __c <= _CharT2('9'))
  __ret = __c - _CharT2('0');
       else if (__c >= _CharT2('a') && __c <= _CharT2('f'))
  __ret = 10 + (__c - _CharT2('a'));
       else if (__c >= _CharT2('A') && __c <= _CharT2('F'))
  __ret = 10 + (__c - _CharT2('A'));
     }
   return __ret;
 }

      template<typename _CharT2>
      typename __gnu_cxx::__enable_if<!__is_char<_CharT2>::__value,
          int>::__type
 _M_find(const _CharT2* __zero, size_t __len, _CharT2 __c) const
 {
   int __ret = -1;
   const char_type* __q = char_traits<_CharT2>::find(__zero, __len, __c);
   if (__q)
     {
       __ret = __q - __zero;
       if (__ret > 15)
  __ret -= 6;
     }
   return __ret;
 }
# 2207 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual iter_type
      do_get(iter_type, iter_type, ios_base&, ios_base::iostate&, bool&) const;

      virtual iter_type
      do_get(iter_type __beg, iter_type __end, ios_base& __io,
      ios_base::iostate& __err, long& __v) const
      { return _M_extract_int(__beg, __end, __io, __err, __v); }

      virtual iter_type
      do_get(iter_type __beg, iter_type __end, ios_base& __io,
      ios_base::iostate& __err, unsigned short& __v) const
      { return _M_extract_int(__beg, __end, __io, __err, __v); }

      virtual iter_type
      do_get(iter_type __beg, iter_type __end, ios_base& __io,
      ios_base::iostate& __err, unsigned int& __v) const
      { return _M_extract_int(__beg, __end, __io, __err, __v); }

      virtual iter_type
      do_get(iter_type __beg, iter_type __end, ios_base& __io,
      ios_base::iostate& __err, unsigned long& __v) const
      { return _M_extract_int(__beg, __end, __io, __err, __v); }


      virtual iter_type
      do_get(iter_type __beg, iter_type __end, ios_base& __io,
      ios_base::iostate& __err, long long& __v) const
      { return _M_extract_int(__beg, __end, __io, __err, __v); }

      virtual iter_type
      do_get(iter_type __beg, iter_type __end, ios_base& __io,
      ios_base::iostate& __err, unsigned long long& __v) const
      { return _M_extract_int(__beg, __end, __io, __err, __v); }


      virtual iter_type
      do_get(iter_type, iter_type, ios_base&, ios_base::iostate&, float&) const;

      virtual iter_type
      do_get(iter_type, iter_type, ios_base&, ios_base::iostate&,
      double&) const;







      virtual iter_type
      do_get(iter_type, iter_type, ios_base&, ios_base::iostate&,
      long double&) const;


      virtual iter_type
      do_get(iter_type, iter_type, ios_base&, ios_base::iostate&, void*&) const;
# 2270 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
    };

  template<typename _CharT, typename _InIter>
    locale::id num_get<_CharT, _InIter>::id;
# 2288 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
  template<typename _CharT, typename _OutIter>
    class num_put : public locale::facet
    {
    public:



      typedef _CharT char_type;
      typedef _OutIter iter_type;



      static locale::id id;
# 2309 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      explicit
      num_put(size_t __refs = 0) : facet(__refs) { }
# 2327 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      iter_type
      put(iter_type __s, ios_base& __io, char_type __fill, bool __v) const
      { return this->do_put(__s, __io, __fill, __v); }
# 2369 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      iter_type
      put(iter_type __s, ios_base& __io, char_type __fill, long __v) const
      { return this->do_put(__s, __io, __fill, __v); }

      iter_type
      put(iter_type __s, ios_base& __io, char_type __fill,
   unsigned long __v) const
      { return this->do_put(__s, __io, __fill, __v); }


      iter_type
      put(iter_type __s, ios_base& __io, char_type __fill, long long __v) const
      { return this->do_put(__s, __io, __fill, __v); }

      iter_type
      put(iter_type __s, ios_base& __io, char_type __fill,
   unsigned long long __v) const
      { return this->do_put(__s, __io, __fill, __v); }
# 2432 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      iter_type
      put(iter_type __s, ios_base& __io, char_type __fill, double __v) const
      { return this->do_put(__s, __io, __fill, __v); }

      iter_type
      put(iter_type __s, ios_base& __io, char_type __fill,
   long double __v) const
      { return this->do_put(__s, __io, __fill, __v); }
# 2457 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      iter_type
      put(iter_type __s, ios_base& __io, char_type __fill,
   const void* __v) const
      { return this->do_put(__s, __io, __fill, __v); }

    protected:
      template<typename _ValueT>
 iter_type
 _M_insert_float(iter_type, ios_base& __io, char_type __fill,
   char __mod, _ValueT __v) const;

      void
      _M_group_float(const char* __grouping, size_t __grouping_size,
       char_type __sep, const char_type* __p, char_type* __new,
       char_type* __cs, int& __len) const;

      template<typename _ValueT>
 iter_type
 _M_insert_int(iter_type, ios_base& __io, char_type __fill,
        _ValueT __v) const;

      void
      _M_group_int(const char* __grouping, size_t __grouping_size,
     char_type __sep, ios_base& __io, char_type* __new,
     char_type* __cs, int& __len) const;

      void
      _M_pad(char_type __fill, streamsize __w, ios_base& __io,
      char_type* __new, const char_type* __cs, int& __len) const;


      virtual
      ~num_put() { };
# 2505 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
      virtual iter_type
      do_put(iter_type __s, ios_base& __io, char_type __fill, bool __v) const;

      virtual iter_type
      do_put(iter_type __s, ios_base& __io, char_type __fill, long __v) const
      { return _M_insert_int(__s, __io, __fill, __v); }

      virtual iter_type
      do_put(iter_type __s, ios_base& __io, char_type __fill,
      unsigned long __v) const
      { return _M_insert_int(__s, __io, __fill, __v); }


      virtual iter_type
      do_put(iter_type __s, ios_base& __io, char_type __fill,
      long long __v) const
      { return _M_insert_int(__s, __io, __fill, __v); }

      virtual iter_type
      do_put(iter_type __s, ios_base& __io, char_type __fill,
      unsigned long long __v) const
      { return _M_insert_int(__s, __io, __fill, __v); }


      virtual iter_type
      do_put(iter_type, ios_base&, char_type, double) const;






      virtual iter_type
      do_put(iter_type, ios_base&, char_type, long double) const;


      virtual iter_type
      do_put(iter_type, ios_base&, char_type, const void*) const;







    };

  template <typename _CharT, typename _OutIter>
    locale::id num_put<_CharT, _OutIter>::id;









  template<typename _CharT>
    inline bool
    isspace(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::space, __c); }


  template<typename _CharT>
    inline bool
    isprint(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::print, __c); }


  template<typename _CharT>
    inline bool
    iscntrl(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::cntrl, __c); }


  template<typename _CharT>
    inline bool
    isupper(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::upper, __c); }


  template<typename _CharT>
    inline bool
    islower(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::lower, __c); }


  template<typename _CharT>
    inline bool
    isalpha(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::alpha, __c); }


  template<typename _CharT>
    inline bool
    isdigit(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::digit, __c); }


  template<typename _CharT>
    inline bool
    ispunct(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::punct, __c); }


  template<typename _CharT>
    inline bool
    isxdigit(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::xdigit, __c); }


  template<typename _CharT>
    inline bool
    isalnum(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::alnum, __c); }


  template<typename _CharT>
    inline bool
    isgraph(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::graph, __c); }
# 2637 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 3
  template<typename _CharT>
    inline _CharT
    toupper(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).toupper(__c); }


  template<typename _CharT>
    inline _CharT
    tolower(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).tolower(__c); }


}

# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.tcc" 1 3
# 33 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.tcc" 3
       
# 34 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.tcc" 3

namespace std
{




  template<typename _Facet>
    struct __use_cache
    {
      const _Facet*
      operator() (const locale& __loc) const;
    };


  template<typename _CharT>
    struct __use_cache<__numpunct_cache<_CharT> >
    {
      const __numpunct_cache<_CharT>*
      operator() (const locale& __loc) const
      {
 const size_t __i = numpunct<_CharT>::id._M_id();
 const locale::facet** __caches = __loc._M_impl->_M_caches;
 if (!__caches[__i])
   {
     __numpunct_cache<_CharT>* __tmp = 0;
     try
       {
  __tmp = new __numpunct_cache<_CharT>;
  __tmp->_M_cache(__loc);
       }
     catch(...)
       {
  delete __tmp;
  throw;
       }
     __loc._M_impl->_M_install_cache(__tmp, __i);
   }
 return static_cast<const __numpunct_cache<_CharT>*>(__caches[__i]);
      }
    };

  template<typename _CharT>
    void
    __numpunct_cache<_CharT>::_M_cache(const locale& __loc)
    {
      const numpunct<_CharT>& __np = use_facet<numpunct<_CharT> >(__loc);

      char* __grouping = 0;
      _CharT* __truename = 0;
      _CharT* __falsename = 0;
      try
 {
   const string& __g = __np.grouping();
   _M_grouping_size = __g.size();
   __grouping = new char[_M_grouping_size];
   __g.copy(__grouping, _M_grouping_size);
   _M_use_grouping = (_M_grouping_size
        && static_cast<signed char>(__grouping[0]) > 0
        && (__grouping[0]
     != __gnu_cxx::__numeric_traits<char>::__max));

   const basic_string<_CharT>& __tn = __np.truename();
   _M_truename_size = __tn.size();
   __truename = new _CharT[_M_truename_size];
   __tn.copy(__truename, _M_truename_size);

   const basic_string<_CharT>& __fn = __np.falsename();
   _M_falsename_size = __fn.size();
   __falsename = new _CharT[_M_falsename_size];
   __fn.copy(__falsename, _M_falsename_size);

   _M_decimal_point = __np.decimal_point();
   _M_thousands_sep = __np.thousands_sep();

   const ctype<_CharT>& __ct = use_facet<ctype<_CharT> >(__loc);
   __ct.widen(__num_base::_S_atoms_out,
       __num_base::_S_atoms_out
       + __num_base::_S_oend, _M_atoms_out);
   __ct.widen(__num_base::_S_atoms_in,
       __num_base::_S_atoms_in
       + __num_base::_S_iend, _M_atoms_in);

   _M_grouping = __grouping;
   _M_truename = __truename;
   _M_falsename = __falsename;
   _M_allocated = true;
 }
      catch(...)
 {
   delete [] __grouping;
   delete [] __truename;
   delete [] __falsename;
   throw;
 }
    }
# 139 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.tcc" 3
  __attribute__ ((__pure__)) bool
  __verify_grouping(const char* __grouping, size_t __grouping_size,
      const string& __grouping_tmp) throw ();



  template<typename _CharT, typename _InIter>
   
    _InIter
    num_get<_CharT, _InIter>::
    _M_extract_float(_InIter __beg, _InIter __end, ios_base& __io,
       ios_base::iostate& __err, string& __xtrc) const
    {
      typedef char_traits<_CharT> __traits_type;
      typedef __numpunct_cache<_CharT> __cache_type;
      __use_cache<__cache_type> __uc;
      const locale& __loc = __io._M_getloc();
      const __cache_type* __lc = __uc(__loc);
      const _CharT* __lit = __lc->_M_atoms_in;
      char_type __c = char_type();


      bool __testeof = __beg == __end;


      if (!__testeof)
 {
   __c = *__beg;
   const bool __plus = __c == __lit[__num_base::_S_iplus];
   if ((__plus || __c == __lit[__num_base::_S_iminus])
       && !(__lc->_M_use_grouping && __c == __lc->_M_thousands_sep)
       && !(__c == __lc->_M_decimal_point))
     {
       __xtrc += __plus ? '+' : '-';
       if (++__beg != __end)
  __c = *__beg;
       else
  __testeof = true;
     }
 }


      bool __found_mantissa = false;
      int __sep_pos = 0;
      while (!__testeof)
 {
   if ((__lc->_M_use_grouping && __c == __lc->_M_thousands_sep)
       || __c == __lc->_M_decimal_point)
     break;
   else if (__c == __lit[__num_base::_S_izero])
     {
       if (!__found_mantissa)
  {
    __xtrc += '0';
    __found_mantissa = true;
  }
       ++__sep_pos;

       if (++__beg != __end)
  __c = *__beg;
       else
  __testeof = true;
     }
   else
     break;
 }


      bool __found_dec = false;
      bool __found_sci = false;
      string __found_grouping;
      if (__lc->_M_use_grouping)
 __found_grouping.reserve(32);
      const char_type* __lit_zero = __lit + __num_base::_S_izero;

      if (!__lc->_M_allocated)

 while (!__testeof)
   {
     const int __digit = _M_find(__lit_zero, 10, __c);
     if (__digit != -1)
       {
  __xtrc += '0' + __digit;
  __found_mantissa = true;
       }
     else if (__c == __lc->_M_decimal_point
       && !__found_dec && !__found_sci)
       {
  __xtrc += '.';
  __found_dec = true;
       }
     else if ((__c == __lit[__num_base::_S_ie]
        || __c == __lit[__num_base::_S_iE])
       && !__found_sci && __found_mantissa)
       {

  __xtrc += 'e';
  __found_sci = true;


  if (++__beg != __end)
    {
      __c = *__beg;
      const bool __plus = __c == __lit[__num_base::_S_iplus];
      if (__plus || __c == __lit[__num_base::_S_iminus])
        __xtrc += __plus ? '+' : '-';
      else
        continue;
    }
  else
    {
      __testeof = true;
      break;
    }
       }
     else
       break;

     if (++__beg != __end)
       __c = *__beg;
     else
       __testeof = true;
   }
      else
 while (!__testeof)
   {


     if (__lc->_M_use_grouping && __c == __lc->_M_thousands_sep)
       {
  if (!__found_dec && !__found_sci)
    {


      if (__sep_pos)
        {
   __found_grouping += static_cast<char>(__sep_pos);
   __sep_pos = 0;
        }
      else
        {


   __xtrc.clear();
   break;
        }
    }
  else
    break;
       }
     else if (__c == __lc->_M_decimal_point)
       {
  if (!__found_dec && !__found_sci)
    {



      if (__found_grouping.size())
        __found_grouping += static_cast<char>(__sep_pos);
      __xtrc += '.';
      __found_dec = true;
    }
  else
    break;
       }
     else
       {
  const char_type* __q =
    __traits_type::find(__lit_zero, 10, __c);
  if (__q)
    {
      __xtrc += '0' + (__q - __lit_zero);
      __found_mantissa = true;
      ++__sep_pos;
    }
  else if ((__c == __lit[__num_base::_S_ie]
     || __c == __lit[__num_base::_S_iE])
    && !__found_sci && __found_mantissa)
    {

      if (__found_grouping.size() && !__found_dec)
        __found_grouping += static_cast<char>(__sep_pos);
      __xtrc += 'e';
      __found_sci = true;


      if (++__beg != __end)
        {
   __c = *__beg;
   const bool __plus = __c == __lit[__num_base::_S_iplus];
   if ((__plus || __c == __lit[__num_base::_S_iminus])
       && !(__lc->_M_use_grouping
     && __c == __lc->_M_thousands_sep)
       && !(__c == __lc->_M_decimal_point))
        __xtrc += __plus ? '+' : '-';
   else
     continue;
        }
      else
        {
   __testeof = true;
   break;
        }
    }
  else
    break;
       }

     if (++__beg != __end)
       __c = *__beg;
     else
       __testeof = true;
   }



      if (__found_grouping.size())
        {

   if (!__found_dec && !__found_sci)
     __found_grouping += static_cast<char>(__sep_pos);

          if (!std::__verify_grouping(__lc->_M_grouping,
          __lc->_M_grouping_size,
          __found_grouping))
     __err = ios_base::failbit;
        }

      return __beg;
    }

  template<typename _CharT, typename _InIter>
    template<typename _ValueT>
     
      _InIter
      num_get<_CharT, _InIter>::
      _M_extract_int(_InIter __beg, _InIter __end, ios_base& __io,
       ios_base::iostate& __err, _ValueT& __v) const
      {
        typedef char_traits<_CharT> __traits_type;
 using __gnu_cxx::__add_unsigned;
 typedef typename __add_unsigned<_ValueT>::__type __unsigned_type;
 typedef __numpunct_cache<_CharT> __cache_type;
 __use_cache<__cache_type> __uc;
 const locale& __loc = __io._M_getloc();
 const __cache_type* __lc = __uc(__loc);
 const _CharT* __lit = __lc->_M_atoms_in;
 char_type __c = char_type();


 const ios_base::fmtflags __basefield = __io.flags()
                                        & ios_base::basefield;
 const bool __oct = __basefield == ios_base::oct;
 int __base = __oct ? 8 : (__basefield == ios_base::hex ? 16 : 10);


 bool __testeof = __beg == __end;


 bool __negative = false;
 if (!__testeof)
   {
     __c = *__beg;
     __negative = __c == __lit[__num_base::_S_iminus];
     if ((__negative || __c == __lit[__num_base::_S_iplus])
  && !(__lc->_M_use_grouping && __c == __lc->_M_thousands_sep)
  && !(__c == __lc->_M_decimal_point))
       {
  if (++__beg != __end)
    __c = *__beg;
  else
    __testeof = true;
       }
   }



 bool __found_zero = false;
 int __sep_pos = 0;
 while (!__testeof)
   {
     if ((__lc->_M_use_grouping && __c == __lc->_M_thousands_sep)
  || __c == __lc->_M_decimal_point)
       break;
     else if (__c == __lit[__num_base::_S_izero]
       && (!__found_zero || __base == 10))
       {
  __found_zero = true;
  ++__sep_pos;
  if (__basefield == 0)
    __base = 8;
  if (__base == 8)
    __sep_pos = 0;
       }
     else if (__found_zero
       && (__c == __lit[__num_base::_S_ix]
    || __c == __lit[__num_base::_S_iX]))
       {
  if (__basefield == 0)
    __base = 16;
  if (__base == 16)
    {
      __found_zero = false;
      __sep_pos = 0;
    }
  else
    break;
       }
     else
       break;

     if (++__beg != __end)
       {
  __c = *__beg;
  if (!__found_zero)
    break;
       }
     else
       __testeof = true;
   }



 const size_t __len = (__base == 16 ? __num_base::_S_iend
         - __num_base::_S_izero : __base);


 string __found_grouping;
 if (__lc->_M_use_grouping)
   __found_grouping.reserve(32);
 bool __testfail = false;
 bool __testoverflow = false;
 const __unsigned_type __max =
   (__negative && __gnu_cxx::__numeric_traits<_ValueT>::__is_signed)
   ? -__gnu_cxx::__numeric_traits<_ValueT>::__min
   : __gnu_cxx::__numeric_traits<_ValueT>::__max;
 const __unsigned_type __smax = __max / __base;
 __unsigned_type __result = 0;
 int __digit = 0;
 const char_type* __lit_zero = __lit + __num_base::_S_izero;

 if (!__lc->_M_allocated)

   while (!__testeof)
     {
       __digit = _M_find(__lit_zero, __len, __c);
       if (__digit == -1)
  break;

       if (__result > __smax)
  __testoverflow = true;
       else
  {
    __result *= __base;
    __testoverflow |= __result > __max - __digit;
    __result += __digit;
    ++__sep_pos;
  }

       if (++__beg != __end)
  __c = *__beg;
       else
  __testeof = true;
     }
 else
   while (!__testeof)
     {


       if (__lc->_M_use_grouping && __c == __lc->_M_thousands_sep)
  {


    if (__sep_pos)
      {
        __found_grouping += static_cast<char>(__sep_pos);
        __sep_pos = 0;
      }
    else
      {
        __testfail = true;
        break;
      }
  }
       else if (__c == __lc->_M_decimal_point)
  break;
       else
  {
    const char_type* __q =
      __traits_type::find(__lit_zero, __len, __c);
    if (!__q)
      break;

    __digit = __q - __lit_zero;
    if (__digit > 15)
      __digit -= 6;
    if (__result > __smax)
      __testoverflow = true;
    else
      {
        __result *= __base;
        __testoverflow |= __result > __max - __digit;
        __result += __digit;
        ++__sep_pos;
      }
  }

       if (++__beg != __end)
  __c = *__beg;
       else
  __testeof = true;
     }



 if (__found_grouping.size())
   {

     __found_grouping += static_cast<char>(__sep_pos);

     if (!std::__verify_grouping(__lc->_M_grouping,
     __lc->_M_grouping_size,
     __found_grouping))
       __err = ios_base::failbit;
   }



 if ((!__sep_pos && !__found_zero && !__found_grouping.size())
     || __testfail)
   {
     __v = 0;
     __err = ios_base::failbit;
   }
 else if (__testoverflow)
   {
     if (__negative
  && __gnu_cxx::__numeric_traits<_ValueT>::__is_signed)
       __v = __gnu_cxx::__numeric_traits<_ValueT>::__min;
     else
       __v = __gnu_cxx::__numeric_traits<_ValueT>::__max;
     __err = ios_base::failbit;
   }
 else
   __v = __negative ? -__result : __result;

 if (__testeof)
   __err |= ios_base::eofbit;
 return __beg;
      }



  template<typename _CharT, typename _InIter>
    _InIter
    num_get<_CharT, _InIter>::
    do_get(iter_type __beg, iter_type __end, ios_base& __io,
           ios_base::iostate& __err, bool& __v) const
    {
      if (!(__io.flags() & ios_base::boolalpha))
        {



   long __l = -1;
          __beg = _M_extract_int(__beg, __end, __io, __err, __l);
   if (__l == 0 || __l == 1)
     __v = bool(__l);
   else
     {


       __v = true;
       __err = ios_base::failbit;
       if (__beg == __end)
  __err |= ios_base::eofbit;
     }
        }
      else
        {

   typedef __numpunct_cache<_CharT> __cache_type;
   __use_cache<__cache_type> __uc;
   const locale& __loc = __io._M_getloc();
   const __cache_type* __lc = __uc(__loc);

   bool __testf = true;
   bool __testt = true;
   bool __donef = __lc->_M_falsename_size == 0;
   bool __donet = __lc->_M_truename_size == 0;
   bool __testeof = false;
   size_t __n = 0;
   while (!__donef || !__donet)
     {
       if (__beg == __end)
  {
    __testeof = true;
    break;
  }

       const char_type __c = *__beg;

       if (!__donef)
  __testf = __c == __lc->_M_falsename[__n];

       if (!__testf && __donet)
  break;

       if (!__donet)
  __testt = __c == __lc->_M_truename[__n];

       if (!__testt && __donef)
  break;

       if (!__testt && !__testf)
  break;

       ++__n;
       ++__beg;

       __donef = !__testf || __n >= __lc->_M_falsename_size;
       __donet = !__testt || __n >= __lc->_M_truename_size;
     }
   if (__testf && __n == __lc->_M_falsename_size && __n)
     {
       __v = false;
       if (__testt && __n == __lc->_M_truename_size)
  __err = ios_base::failbit;
       else
  __err = __testeof ? ios_base::eofbit : ios_base::goodbit;
     }
   else if (__testt && __n == __lc->_M_truename_size && __n)
     {
       __v = true;
       __err = __testeof ? ios_base::eofbit : ios_base::goodbit;
     }
   else
     {


       __v = false;
       __err = ios_base::failbit;
       if (__testeof)
  __err |= ios_base::eofbit;
     }
 }
      return __beg;
    }

  template<typename _CharT, typename _InIter>
    _InIter
    num_get<_CharT, _InIter>::
    do_get(iter_type __beg, iter_type __end, ios_base& __io,
    ios_base::iostate& __err, float& __v) const
    {
      string __xtrc;
      __xtrc.reserve(32);
      __beg = _M_extract_float(__beg, __end, __io, __err, __xtrc);
      std::__convert_to_v(__xtrc.c_str(), __v, __err, _S_get_c_locale());
      if (__beg == __end)
 __err |= ios_base::eofbit;
      return __beg;
    }

  template<typename _CharT, typename _InIter>
    _InIter
    num_get<_CharT, _InIter>::
    do_get(iter_type __beg, iter_type __end, ios_base& __io,
           ios_base::iostate& __err, double& __v) const
    {
      string __xtrc;
      __xtrc.reserve(32);
      __beg = _M_extract_float(__beg, __end, __io, __err, __xtrc);
      std::__convert_to_v(__xtrc.c_str(), __v, __err, _S_get_c_locale());
      if (__beg == __end)
 __err |= ios_base::eofbit;
      return __beg;
    }
# 735 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.tcc" 3
  template<typename _CharT, typename _InIter>
    _InIter
    num_get<_CharT, _InIter>::
    do_get(iter_type __beg, iter_type __end, ios_base& __io,
           ios_base::iostate& __err, long double& __v) const
    {
      string __xtrc;
      __xtrc.reserve(32);
      __beg = _M_extract_float(__beg, __end, __io, __err, __xtrc);
      std::__convert_to_v(__xtrc.c_str(), __v, __err, _S_get_c_locale());
      if (__beg == __end)
 __err |= ios_base::eofbit;
      return __beg;
    }

  template<typename _CharT, typename _InIter>
    _InIter
    num_get<_CharT, _InIter>::
    do_get(iter_type __beg, iter_type __end, ios_base& __io,
           ios_base::iostate& __err, void*& __v) const
    {

      typedef ios_base::fmtflags fmtflags;
      const fmtflags __fmt = __io.flags();
      __io.flags((__fmt & ~ios_base::basefield) | ios_base::hex);

      typedef __gnu_cxx::__conditional_type<(sizeof(void*)
          <= sizeof(unsigned long)),
 unsigned long, unsigned long long>::__type _UIntPtrType;

      _UIntPtrType __ul;
      __beg = _M_extract_int(__beg, __end, __io, __err, __ul);


      __io.flags(__fmt);

      __v = reinterpret_cast<void*>(__ul);
      return __beg;
    }



  template<typename _CharT, typename _OutIter>
    void
    num_put<_CharT, _OutIter>::
    _M_pad(_CharT __fill, streamsize __w, ios_base& __io,
    _CharT* __new, const _CharT* __cs, int& __len) const
    {


      __pad<_CharT, char_traits<_CharT> >::_S_pad(__io, __fill, __new,
        __cs, __w, __len);
      __len = static_cast<int>(__w);
    }



  template<typename _CharT, typename _ValueT>
    int
    __int_to_char(_CharT* __bufend, _ValueT __v, const _CharT* __lit,
    ios_base::fmtflags __flags, bool __dec)
    {
      _CharT* __buf = __bufend;
      if (__builtin_expect(__dec, true))
 {

   do
     {
       *--__buf = __lit[(__v % 10) + __num_base::_S_odigits];
       __v /= 10;
     }
   while (__v != 0);
 }
      else if ((__flags & ios_base::basefield) == ios_base::oct)
 {

   do
     {
       *--__buf = __lit[(__v & 0x7) + __num_base::_S_odigits];
       __v >>= 3;
     }
   while (__v != 0);
 }
      else
 {

   const bool __uppercase = __flags & ios_base::uppercase;
   const int __case_offset = __uppercase ? __num_base::_S_oudigits
                                         : __num_base::_S_odigits;
   do
     {
       *--__buf = __lit[(__v & 0xf) + __case_offset];
       __v >>= 4;
     }
   while (__v != 0);
 }
      return __bufend - __buf;
    }



  template<typename _CharT, typename _OutIter>
    void
    num_put<_CharT, _OutIter>::
    _M_group_int(const char* __grouping, size_t __grouping_size, _CharT __sep,
   ios_base&, _CharT* __new, _CharT* __cs, int& __len) const
    {
      _CharT* __p = std::__add_grouping(__new, __sep, __grouping,
     __grouping_size, __cs, __cs + __len);
      __len = __p - __new;
    }

  template<typename _CharT, typename _OutIter>
    template<typename _ValueT>
      _OutIter
      num_put<_CharT, _OutIter>::
      _M_insert_int(_OutIter __s, ios_base& __io, _CharT __fill,
      _ValueT __v) const
      {
 using __gnu_cxx::__add_unsigned;
 typedef typename __add_unsigned<_ValueT>::__type __unsigned_type;
 typedef __numpunct_cache<_CharT> __cache_type;
 __use_cache<__cache_type> __uc;
 const locale& __loc = __io._M_getloc();
 const __cache_type* __lc = __uc(__loc);
 const _CharT* __lit = __lc->_M_atoms_out;
 const ios_base::fmtflags __flags = __io.flags();


 const int __ilen = 5 * sizeof(_ValueT);
 _CharT* __cs = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
            * __ilen));



 const ios_base::fmtflags __basefield = __flags & ios_base::basefield;
 const bool __dec = (__basefield != ios_base::oct
       && __basefield != ios_base::hex);
 const __unsigned_type __u = ((__v > 0 || !__dec)
         ? __unsigned_type(__v)
         : -__unsigned_type(__v));
  int __len = __int_to_char(__cs + __ilen, __u, __lit, __flags, __dec);
 __cs += __ilen - __len;


 if (__lc->_M_use_grouping)
   {


     _CharT* __cs2 = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
          * (__len + 1)
          * 2));
     _M_group_int(__lc->_M_grouping, __lc->_M_grouping_size,
    __lc->_M_thousands_sep, __io, __cs2 + 2, __cs, __len);
     __cs = __cs2 + 2;
   }


 if (__builtin_expect(__dec, true))
   {

     if (__v >= 0)
       {
  if (bool(__flags & ios_base::showpos)
      && __gnu_cxx::__numeric_traits<_ValueT>::__is_signed)
    *--__cs = __lit[__num_base::_S_oplus], ++__len;
       }
     else
       *--__cs = __lit[__num_base::_S_ominus], ++__len;
   }
 else if (bool(__flags & ios_base::showbase) && __v)
   {
     if (__basefield == ios_base::oct)
       *--__cs = __lit[__num_base::_S_odigits], ++__len;
     else
       {

  const bool __uppercase = __flags & ios_base::uppercase;
  *--__cs = __lit[__num_base::_S_ox + __uppercase];

  *--__cs = __lit[__num_base::_S_odigits];
  __len += 2;
       }
   }


 const streamsize __w = __io.width();
 if (__w > static_cast<streamsize>(__len))
   {
     _CharT* __cs3 = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
          * __w));
     _M_pad(__fill, __w, __io, __cs3, __cs, __len);
     __cs = __cs3;
   }
 __io.width(0);



 return std::__write(__s, __cs, __len);
      }

  template<typename _CharT, typename _OutIter>
    void
    num_put<_CharT, _OutIter>::
    _M_group_float(const char* __grouping, size_t __grouping_size,
     _CharT __sep, const _CharT* __p, _CharT* __new,
     _CharT* __cs, int& __len) const
    {



      const int __declen = __p ? __p - __cs : __len;
      _CharT* __p2 = std::__add_grouping(__new, __sep, __grouping,
      __grouping_size,
      __cs, __cs + __declen);


      int __newlen = __p2 - __new;
      if (__p)
 {
   char_traits<_CharT>::copy(__p2, __p, __len - __declen);
   __newlen += __len - __declen;
 }
      __len = __newlen;
    }
# 971 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.tcc" 3
  template<typename _CharT, typename _OutIter>
    template<typename _ValueT>
      _OutIter
      num_put<_CharT, _OutIter>::
      _M_insert_float(_OutIter __s, ios_base& __io, _CharT __fill, char __mod,
         _ValueT __v) const
      {
 typedef __numpunct_cache<_CharT> __cache_type;
 __use_cache<__cache_type> __uc;
 const locale& __loc = __io._M_getloc();
 const __cache_type* __lc = __uc(__loc);


 const streamsize __prec = __io.precision() < 0 ? 6 : __io.precision();

 const int __max_digits =
   __gnu_cxx::__numeric_traits<_ValueT>::__digits10;


 int __len;

 char __fbuf[16];
 __num_base::_S_format_float(__io, __fbuf, __mod);



 const bool __use_prec =
   (__io.flags() & ios_base::floatfield) != ios_base::floatfield;



 int __cs_size = __max_digits * 3;
 char* __cs = static_cast<char*>(__builtin_alloca(__cs_size));
 if (__use_prec)
   __len = std::__convert_from_v(_S_get_c_locale(), __cs, __cs_size,
     __fbuf, __prec, __v);
 else
   __len = std::__convert_from_v(_S_get_c_locale(), __cs, __cs_size,
     __fbuf, __v);


 if (__len >= __cs_size)
   {
     __cs_size = __len + 1;
     __cs = static_cast<char*>(__builtin_alloca(__cs_size));
     if (__use_prec)
       __len = std::__convert_from_v(_S_get_c_locale(), __cs, __cs_size,
         __fbuf, __prec, __v);
     else
       __len = std::__convert_from_v(_S_get_c_locale(), __cs, __cs_size,
         __fbuf, __v);
   }
# 1044 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.tcc" 3
 const ctype<_CharT>& __ctype = use_facet<ctype<_CharT> >(__loc);

 _CharT* __ws = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
            * __len));
 __ctype.widen(__cs, __cs + __len, __ws);


 _CharT* __wp = 0;
 const char* __p = char_traits<char>::find(__cs, __len, '.');
 if (__p)
   {
     __wp = __ws + (__p - __cs);
     *__wp = __lc->_M_decimal_point;
   }




 if (__lc->_M_use_grouping
     && (__wp || __len < 3 || (__cs[1] <= '9' && __cs[2] <= '9'
          && __cs[1] >= '0' && __cs[2] >= '0')))
   {


     _CharT* __ws2 = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
          * __len * 2));

     streamsize __off = 0;
     if (__cs[0] == '-' || __cs[0] == '+')
       {
  __off = 1;
  __ws2[0] = __ws[0];
  __len -= 1;
       }

     _M_group_float(__lc->_M_grouping, __lc->_M_grouping_size,
      __lc->_M_thousands_sep, __wp, __ws2 + __off,
      __ws + __off, __len);
     __len += __off;

     __ws = __ws2;
   }


 const streamsize __w = __io.width();
 if (__w > static_cast<streamsize>(__len))
   {
     _CharT* __ws3 = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
          * __w));
     _M_pad(__fill, __w, __io, __ws3, __ws, __len);
     __ws = __ws3;
   }
 __io.width(0);



 return std::__write(__s, __ws, __len);
      }

  template<typename _CharT, typename _OutIter>
    _OutIter
    num_put<_CharT, _OutIter>::
    do_put(iter_type __s, ios_base& __io, char_type __fill, bool __v) const
    {
      const ios_base::fmtflags __flags = __io.flags();
      if ((__flags & ios_base::boolalpha) == 0)
        {
          const long __l = __v;
          __s = _M_insert_int(__s, __io, __fill, __l);
        }
      else
        {
   typedef __numpunct_cache<_CharT> __cache_type;
   __use_cache<__cache_type> __uc;
   const locale& __loc = __io._M_getloc();
   const __cache_type* __lc = __uc(__loc);

   const _CharT* __name = __v ? __lc->_M_truename
                              : __lc->_M_falsename;
   int __len = __v ? __lc->_M_truename_size
                   : __lc->_M_falsename_size;

   const streamsize __w = __io.width();
   if (__w > static_cast<streamsize>(__len))
     {
       const streamsize __plen = __w - __len;
       _CharT* __ps
  = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
       * __plen));

       char_traits<_CharT>::assign(__ps, __plen, __fill);
       __io.width(0);

       if ((__flags & ios_base::adjustfield) == ios_base::left)
  {
    __s = std::__write(__s, __name, __len);
    __s = std::__write(__s, __ps, __plen);
  }
       else
  {
    __s = std::__write(__s, __ps, __plen);
    __s = std::__write(__s, __name, __len);
  }
       return __s;
     }
   __io.width(0);
   __s = std::__write(__s, __name, __len);
 }
      return __s;
    }

  template<typename _CharT, typename _OutIter>
    _OutIter
    num_put<_CharT, _OutIter>::
    do_put(iter_type __s, ios_base& __io, char_type __fill, double __v) const
    { return _M_insert_float(__s, __io, __fill, char(), __v); }
# 1169 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.tcc" 3
  template<typename _CharT, typename _OutIter>
    _OutIter
    num_put<_CharT, _OutIter>::
    do_put(iter_type __s, ios_base& __io, char_type __fill,
    long double __v) const
    { return _M_insert_float(__s, __io, __fill, 'L', __v); }

  template<typename _CharT, typename _OutIter>
    _OutIter
    num_put<_CharT, _OutIter>::
    do_put(iter_type __s, ios_base& __io, char_type __fill,
           const void* __v) const
    {
      const ios_base::fmtflags __flags = __io.flags();
      const ios_base::fmtflags __fmt = ~(ios_base::basefield
      | ios_base::uppercase);
      __io.flags((__flags & __fmt) | (ios_base::hex | ios_base::showbase));

      typedef __gnu_cxx::__conditional_type<(sizeof(const void*)
          <= sizeof(unsigned long)),
 unsigned long, unsigned long long>::__type _UIntPtrType;

      __s = _M_insert_int(__s, __io, __fill,
     reinterpret_cast<_UIntPtrType>(__v));
      __io.flags(__flags);
      return __s;
    }


# 1206 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.tcc" 3
  template<typename _CharT, typename _Traits>
    void
    __pad<_CharT, _Traits>::_S_pad(ios_base& __io, _CharT __fill,
       _CharT* __news, const _CharT* __olds,
       streamsize __newlen, streamsize __oldlen)
    {
      const size_t __plen = static_cast<size_t>(__newlen - __oldlen);
      const ios_base::fmtflags __adjust = __io.flags() & ios_base::adjustfield;


      if (__adjust == ios_base::left)
 {
   _Traits::copy(__news, __olds, __oldlen);
   _Traits::assign(__news + __oldlen, __plen, __fill);
   return;
 }

      size_t __mod = 0;
      if (__adjust == ios_base::internal)
 {



          const locale& __loc = __io._M_getloc();
   const ctype<_CharT>& __ctype = use_facet<ctype<_CharT> >(__loc);

   if (__ctype.widen('-') == __olds[0]
       || __ctype.widen('+') == __olds[0])
     {
       __news[0] = __olds[0];
       __mod = 1;
       ++__news;
     }
   else if (__ctype.widen('0') == __olds[0]
     && __oldlen > 1
     && (__ctype.widen('x') == __olds[1]
         || __ctype.widen('X') == __olds[1]))
     {
       __news[0] = __olds[0];
       __news[1] = __olds[1];
       __mod = 2;
       __news += 2;
     }

 }
      _Traits::assign(__news, __plen, __fill);
      _Traits::copy(__news + __plen, __olds + __mod, __oldlen - __mod);
    }

  template<typename _CharT>
    _CharT*
    __add_grouping(_CharT* __s, _CharT __sep,
     const char* __gbeg, size_t __gsize,
     const _CharT* __first, const _CharT* __last)
    {
      size_t __idx = 0;
      size_t __ctr = 0;

      while (__last - __first > __gbeg[__idx]
      && static_cast<signed char>(__gbeg[__idx]) > 0
      && __gbeg[__idx] != __gnu_cxx::__numeric_traits<char>::__max)
 {
   __last -= __gbeg[__idx];
   __idx < __gsize - 1 ? ++__idx : ++__ctr;
 }

      while (__first != __last)
 *__s++ = *__first++;

      while (__ctr--)
 {
   *__s++ = __sep;
   for (char __i = __gbeg[__idx]; __i > 0; --__i)
     *__s++ = *__first++;
 }

      while (__idx--)
 {
   *__s++ = __sep;
   for (char __i = __gbeg[__idx]; __i > 0; --__i)
     *__s++ = *__first++;
 }

      return __s;
    }




  extern template class numpunct<char>;
  extern template class numpunct_byname<char>;
  extern template class num_get<char>;
  extern template class num_put<char>;
  extern template class ctype_byname<char>;

  extern template
    const ctype<char>&
    use_facet<ctype<char> >(const locale&);

  extern template
    const numpunct<char>&
    use_facet<numpunct<char> >(const locale&);

  extern template
    const num_put<char>&
    use_facet<num_put<char> >(const locale&);

  extern template
    const num_get<char>&
    use_facet<num_get<char> >(const locale&);

  extern template
    bool
    has_facet<ctype<char> >(const locale&);

  extern template
    bool
    has_facet<numpunct<char> >(const locale&);

  extern template
    bool
    has_facet<num_put<char> >(const locale&);

  extern template
    bool
    has_facet<num_get<char> >(const locale&);


  extern template class numpunct<wchar_t>;
  extern template class numpunct_byname<wchar_t>;
  extern template class num_get<wchar_t>;
  extern template class num_put<wchar_t>;
  extern template class ctype_byname<wchar_t>;

  extern template
    const ctype<wchar_t>&
    use_facet<ctype<wchar_t> >(const locale&);

  extern template
    const numpunct<wchar_t>&
    use_facet<numpunct<wchar_t> >(const locale&);

  extern template
    const num_put<wchar_t>&
    use_facet<num_put<wchar_t> >(const locale&);

  extern template
    const num_get<wchar_t>&
    use_facet<num_get<wchar_t> >(const locale&);

 extern template
    bool
    has_facet<ctype<wchar_t> >(const locale&);

  extern template
    bool
    has_facet<numpunct<wchar_t> >(const locale&);

  extern template
    bool
    has_facet<num_put<wchar_t> >(const locale&);

  extern template
    bool
    has_facet<num_get<wchar_t> >(const locale&);




}
# 2652 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/locale_facets.h" 2 3
# 38 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_ios.h" 2 3



namespace std
{


  template<typename _Facet>
    inline const _Facet&
    __check_facet(const _Facet* __f)
    {
      if (!__f)
 __throw_bad_cast();
      return *__f;
    }
# 66 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_ios.h" 3
  template<typename _CharT, typename _Traits>
    class basic_ios : public ios_base
    {
    public:






      typedef _CharT char_type;
      typedef typename _Traits::int_type int_type;
      typedef typename _Traits::pos_type pos_type;
      typedef typename _Traits::off_type off_type;
      typedef _Traits traits_type;






      typedef ctype<_CharT> __ctype_type;
      typedef num_put<_CharT, ostreambuf_iterator<_CharT, _Traits> >
           __num_put_type;
      typedef num_get<_CharT, istreambuf_iterator<_CharT, _Traits> >
           __num_get_type;



    protected:
      basic_ostream<_CharT, _Traits>* _M_tie;
      mutable char_type _M_fill;
      mutable bool _M_fill_init;
      basic_streambuf<_CharT, _Traits>* _M_streambuf;


      const __ctype_type* _M_ctype;

      const __num_put_type* _M_num_put;

      const __num_get_type* _M_num_get;

    public:
# 120 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_ios.h" 3
      operator void*() const
      { return this->fail() ? 0 : const_cast<basic_ios*>(this); }


      bool
      operator!() const
      { return this->fail(); }
# 136 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_ios.h" 3
      iostate
      rdstate() const
      { return _M_streambuf_state; }
# 147 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_ios.h" 3
      void
      clear(iostate __state = goodbit);







      void
      setstate(iostate __state)
      { this->clear(this->rdstate() | __state); }




      void
      _M_setstate(iostate __state)
      {


 _M_streambuf_state |= __state;
 if (this->exceptions() & __state)
   throw;
      }







      bool
      good() const
      { return this->rdstate() == 0; }







      bool
      eof() const
      { return (this->rdstate() & eofbit) != 0; }
# 200 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_ios.h" 3
      bool
      fail() const
      { return (this->rdstate() & (badbit | failbit)) != 0; }







      bool
      bad() const
      { return (this->rdstate() & badbit) != 0; }
# 221 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_ios.h" 3
      iostate
      exceptions() const
      { return _M_exception; }
# 256 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_ios.h" 3
      void
      exceptions(iostate __except)
      {
        _M_exception = __except;
        this->clear(_M_streambuf_state);
      }







      explicit
      basic_ios(basic_streambuf<_CharT, _Traits>* __sb)
      : ios_base(), _M_tie(0), _M_fill(), _M_fill_init(false), _M_streambuf(0),
 _M_ctype(0), _M_num_put(0), _M_num_get(0)
      { this->init(__sb); }







      virtual
      ~basic_ios() { }
# 294 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_ios.h" 3
      basic_ostream<_CharT, _Traits>*
      tie() const
      { return _M_tie; }
# 306 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_ios.h" 3
      basic_ostream<_CharT, _Traits>*
      tie(basic_ostream<_CharT, _Traits>* __tiestr)
      {
        basic_ostream<_CharT, _Traits>* __old = _M_tie;
        _M_tie = __tiestr;
        return __old;
      }







      basic_streambuf<_CharT, _Traits>*
      rdbuf() const
      { return _M_streambuf; }
# 346 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_ios.h" 3
      basic_streambuf<_CharT, _Traits>*
      rdbuf(basic_streambuf<_CharT, _Traits>* __sb);
# 360 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_ios.h" 3
      basic_ios&
      copyfmt(const basic_ios& __rhs);







      char_type
      fill() const
      {
 if (!_M_fill_init)
   {
     _M_fill = this->widen(' ');
     _M_fill_init = true;
   }
 return _M_fill;
      }
# 389 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_ios.h" 3
      char_type
      fill(char_type __ch)
      {
 char_type __old = this->fill();
 _M_fill = __ch;
 return __old;
      }
# 409 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_ios.h" 3
      locale
      imbue(const locale& __loc);
# 429 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_ios.h" 3
      char
      narrow(char_type __c, char __dfault) const
      { return __check_facet(_M_ctype).narrow(__c, __dfault); }
# 448 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_ios.h" 3
      char_type
      widen(char __c) const
      { return __check_facet(_M_ctype).widen(__c); }

    protected:







      basic_ios()
      : ios_base(), _M_tie(0), _M_fill(char_type()), _M_fill_init(false),
 _M_streambuf(0), _M_ctype(0), _M_num_put(0), _M_num_get(0)
      { }







      void
      init(basic_streambuf<_CharT, _Traits>* __sb);
# 509 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_ios.h" 3
      void
      _M_cache_locale(const locale& __loc);
    };


}

# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_ios.tcc" 1 3
# 33 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_ios.tcc" 3
       
# 34 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_ios.tcc" 3

namespace std
{


  template<typename _CharT, typename _Traits>
    void
    basic_ios<_CharT, _Traits>::clear(iostate __state)
    {
      if (this->rdbuf())
 _M_streambuf_state = __state;
      else
   _M_streambuf_state = __state | badbit;
      if (this->exceptions() & this->rdstate())
 __throw_ios_failure(("basic_ios::clear"));
    }

  template<typename _CharT, typename _Traits>
    basic_streambuf<_CharT, _Traits>*
    basic_ios<_CharT, _Traits>::rdbuf(basic_streambuf<_CharT, _Traits>* __sb)
    {
      basic_streambuf<_CharT, _Traits>* __old = _M_streambuf;
      _M_streambuf = __sb;
      this->clear();
      return __old;
    }

  template<typename _CharT, typename _Traits>
    basic_ios<_CharT, _Traits>&
    basic_ios<_CharT, _Traits>::copyfmt(const basic_ios& __rhs)
    {


      if (this != &__rhs)
 {




   _Words* __words = (__rhs._M_word_size <= _S_local_word_size) ?
                      _M_local_word : new _Words[__rhs._M_word_size];


   _Callback_list* __cb = __rhs._M_callbacks;
   if (__cb)
     __cb->_M_add_reference();
   _M_call_callbacks(erase_event);
   if (_M_word != _M_local_word)
     {
       delete [] _M_word;
       _M_word = 0;
     }
   _M_dispose_callbacks();


   _M_callbacks = __cb;
   for (int __i = 0; __i < __rhs._M_word_size; ++__i)
     __words[__i] = __rhs._M_word[__i];
   _M_word = __words;
   _M_word_size = __rhs._M_word_size;

   this->flags(__rhs.flags());
   this->width(__rhs.width());
   this->precision(__rhs.precision());
   this->tie(__rhs.tie());
   this->fill(__rhs.fill());
   _M_ios_locale = __rhs.getloc();
   _M_cache_locale(_M_ios_locale);

   _M_call_callbacks(copyfmt_event);


   this->exceptions(__rhs.exceptions());
 }
      return *this;
    }


  template<typename _CharT, typename _Traits>
    locale
    basic_ios<_CharT, _Traits>::imbue(const locale& __loc)
    {
      locale __old(this->getloc());
      ios_base::imbue(__loc);
      _M_cache_locale(__loc);
      if (this->rdbuf() != 0)
 this->rdbuf()->pubimbue(__loc);
      return __old;
    }

  template<typename _CharT, typename _Traits>
    void
    basic_ios<_CharT, _Traits>::init(basic_streambuf<_CharT, _Traits>* __sb)
    {

      ios_base::_M_init();


      _M_cache_locale(_M_ios_locale);
# 146 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_ios.tcc" 3
      _M_fill = _CharT();
      _M_fill_init = false;

      _M_tie = 0;
      _M_exception = goodbit;
      _M_streambuf = __sb;
      _M_streambuf_state = __sb ? goodbit : badbit;
    }

  template<typename _CharT, typename _Traits>
    void
    basic_ios<_CharT, _Traits>::_M_cache_locale(const locale& __loc)
    {
      if (__builtin_expect(has_facet<__ctype_type>(__loc), true))
 _M_ctype = &use_facet<__ctype_type>(__loc);
      else
 _M_ctype = 0;

      if (__builtin_expect(has_facet<__num_put_type>(__loc), true))
 _M_num_put = &use_facet<__num_put_type>(__loc);
      else
 _M_num_put = 0;

      if (__builtin_expect(has_facet<__num_get_type>(__loc), true))
 _M_num_get = &use_facet<__num_get_type>(__loc);
      else
 _M_num_get = 0;
    }




  extern template class basic_ios<char>;


  extern template class basic_ios<wchar_t>;




}
# 517 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/basic_ios.h" 2 3
# 45 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ios" 2 3
# 39 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 2 3


namespace std
{

# 57 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 3
  template<typename _CharT, typename _Traits>
    class basic_ostream : virtual public basic_ios<_CharT, _Traits>
    {
    public:

      typedef _CharT char_type;
      typedef typename _Traits::int_type int_type;
      typedef typename _Traits::pos_type pos_type;
      typedef typename _Traits::off_type off_type;
      typedef _Traits traits_type;


      typedef basic_streambuf<_CharT, _Traits> __streambuf_type;
      typedef basic_ios<_CharT, _Traits> __ios_type;
      typedef basic_ostream<_CharT, _Traits> __ostream_type;
      typedef num_put<_CharT, ostreambuf_iterator<_CharT, _Traits> >
             __num_put_type;
      typedef ctype<_CharT> __ctype_type;
# 83 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 3
      explicit
      basic_ostream(__streambuf_type* __sb)
      { this->init(__sb); }






      virtual
      ~basic_ostream() { }


      class sentry;
      friend class sentry;
# 107 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 3
      __ostream_type&
      operator<<(__ostream_type& (*__pf)(__ostream_type&))
      {



 return __pf(*this);
      }

      __ostream_type&
      operator<<(__ios_type& (*__pf)(__ios_type&))
      {



 __pf(*this);
 return *this;
      }

      __ostream_type&
      operator<<(ios_base& (*__pf) (ios_base&))
      {



 __pf(*this);
 return *this;
      }
# 165 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 3
      __ostream_type&
      operator<<(long __n)
      { return _M_insert(__n); }

      __ostream_type&
      operator<<(unsigned long __n)
      { return _M_insert(__n); }

      __ostream_type&
      operator<<(bool __n)
      { return _M_insert(__n); }

      __ostream_type&
      operator<<(short __n);

      __ostream_type&
      operator<<(unsigned short __n)
      {


 return _M_insert(static_cast<unsigned long>(__n));
      }

      __ostream_type&
      operator<<(int __n);

      __ostream_type&
      operator<<(unsigned int __n)
      {


 return _M_insert(static_cast<unsigned long>(__n));
      }


      __ostream_type&
      operator<<(long long __n)
      { return _M_insert(__n); }

      __ostream_type&
      operator<<(unsigned long long __n)
      { return _M_insert(__n); }
# 219 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 3
      __ostream_type&
      operator<<(double __f)
      { return _M_insert(__f); }

      __ostream_type&
      operator<<(float __f)
      {


 return _M_insert(static_cast<double>(__f));
      }

      __ostream_type&
      operator<<(long double __f)
      { return _M_insert(__f); }
# 244 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 3
      __ostream_type&
      operator<<(const void* __p)
      { return _M_insert(__p); }
# 269 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 3
      __ostream_type&
      operator<<(__streambuf_type* __sb);
# 302 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 3
      __ostream_type&
      put(char_type __c);






      void
      _M_write(const char_type* __s, streamsize __n)
      {
 const streamsize __put = this->rdbuf()->sputn(__s, __n);
 if (__put != __n)
   this->setstate(ios_base::badbit);
      }
# 334 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 3
      __ostream_type&
      write(const char_type* __s, streamsize __n);
# 347 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 3
      __ostream_type&
      flush();
# 357 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 3
      pos_type
      tellp();
# 368 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 3
      __ostream_type&
      seekp(pos_type);
# 380 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 3
       __ostream_type&
      seekp(off_type, ios_base::seekdir);

    protected:
      basic_ostream()
      { this->init(0); }
# 413 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 3
      template<typename _ValueT>
 __ostream_type&
 _M_insert(_ValueT __v);
    };
# 425 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 3
  template <typename _CharT, typename _Traits>
    class basic_ostream<_CharT, _Traits>::sentry
    {

      bool _M_ok;
      basic_ostream<_CharT, _Traits>& _M_os;

    public:
# 444 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 3
      explicit
      sentry(basic_ostream<_CharT, _Traits>& __os);
# 454 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 3
      ~sentry()
      {

 if (bool(_M_os.flags() & ios_base::unitbuf) && !uncaught_exception())
   {

     if (_M_os.rdbuf() && _M_os.rdbuf()->pubsync() == -1)
       _M_os.setstate(ios_base::badbit);
   }
      }
# 475 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 3
      operator bool() const
      { return _M_ok; }
    };
# 495 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 3
  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __out, _CharT __c)
    { return __ostream_insert(__out, &__c, 1); }

  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __out, char __c)
    { return (__out << __out.widen(__c)); }


  template <class _Traits>
    inline basic_ostream<char, _Traits>&
    operator<<(basic_ostream<char, _Traits>& __out, char __c)
    { return __ostream_insert(__out, &__c, 1); }


  template<class _Traits>
    inline basic_ostream<char, _Traits>&
    operator<<(basic_ostream<char, _Traits>& __out, signed char __c)
    { return (__out << static_cast<char>(__c)); }

  template<class _Traits>
    inline basic_ostream<char, _Traits>&
    operator<<(basic_ostream<char, _Traits>& __out, unsigned char __c)
    { return (__out << static_cast<char>(__c)); }
# 537 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 3
  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __out, const _CharT* __s)
    {
      if (!__s)
 __out.setstate(ios_base::badbit);
      else
 __ostream_insert(__out, __s,
    static_cast<streamsize>(_Traits::length(__s)));
      return __out;
    }

  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits> &
    operator<<(basic_ostream<_CharT, _Traits>& __out, const char* __s);


  template<class _Traits>
    inline basic_ostream<char, _Traits>&
    operator<<(basic_ostream<char, _Traits>& __out, const char* __s)
    {
      if (!__s)
 __out.setstate(ios_base::badbit);
      else
 __ostream_insert(__out, __s,
    static_cast<streamsize>(_Traits::length(__s)));
      return __out;
    }


  template<class _Traits>
    inline basic_ostream<char, _Traits>&
    operator<<(basic_ostream<char, _Traits>& __out, const signed char* __s)
    { return (__out << reinterpret_cast<const char*>(__s)); }

  template<class _Traits>
    inline basic_ostream<char, _Traits> &
    operator<<(basic_ostream<char, _Traits>& __out, const unsigned char* __s)
    { return (__out << reinterpret_cast<const char*>(__s)); }
# 588 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 3
  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>&
    endl(basic_ostream<_CharT, _Traits>& __os)
    { return flush(__os.put(__os.widen('\n'))); }
# 600 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 3
  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>&
    ends(basic_ostream<_CharT, _Traits>& __os)
    { return __os.put(_CharT()); }






  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>&
    flush(basic_ostream<_CharT, _Traits>& __os)
    { return __os.flush(); }
# 635 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 3

}

# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ostream.tcc" 1 3
# 37 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ostream.tcc" 3
       
# 38 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/ostream.tcc" 3



namespace std
{


  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>::sentry::
    sentry(basic_ostream<_CharT, _Traits>& __os)
    : _M_ok(false), _M_os(__os)
    {

      if (__os.tie() && __os.good())
 __os.tie()->flush();

      if (__os.good())
 _M_ok = true;
      else
 __os.setstate(ios_base::failbit);
    }

  template<typename _CharT, typename _Traits>
    template<typename _ValueT>
      basic_ostream<_CharT, _Traits>&
      basic_ostream<_CharT, _Traits>::
      _M_insert(_ValueT __v)
      {
 sentry __cerb(*this);
 if (__cerb)
   {
     ios_base::iostate __err = ios_base::goodbit;
     try
       {
  const __num_put_type& __np = __check_facet(this->_M_num_put);
  if (__np.put(*this, *this, this->fill(), __v).failed())
    __err |= ios_base::badbit;
       }
     catch(__cxxabiv1::__forced_unwind&)
       {
  this->_M_setstate(ios_base::badbit);
  throw;
       }
     catch(...)
       { this->_M_setstate(ios_base::badbit); }
     if (__err)
       this->setstate(__err);
   }
 return *this;
      }

  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    operator<<(short __n)
    {


      const ios_base::fmtflags __fmt = this->flags() & ios_base::basefield;
      if (__fmt == ios_base::oct || __fmt == ios_base::hex)
 return _M_insert(static_cast<long>(static_cast<unsigned short>(__n)));
      else
 return _M_insert(static_cast<long>(__n));
    }

  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    operator<<(int __n)
    {


      const ios_base::fmtflags __fmt = this->flags() & ios_base::basefield;
      if (__fmt == ios_base::oct || __fmt == ios_base::hex)
 return _M_insert(static_cast<long>(static_cast<unsigned int>(__n)));
      else
 return _M_insert(static_cast<long>(__n));
    }

  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    operator<<(__streambuf_type* __sbin)
    {
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this);
      if (__cerb && __sbin)
 {
   try
     {
       if (!__copy_streambufs(__sbin, this->rdbuf()))
  __err |= ios_base::failbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::failbit); }
 }
      else if (!__sbin)
 __err |= ios_base::badbit;
      if (__err)
 this->setstate(__err);
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    put(char_type __c)
    {






      sentry __cerb(*this);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       const int_type __put = this->rdbuf()->sputc(__c);
       if (traits_type::eq_int_type(__put, traits_type::eof()))
  __err |= ios_base::badbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    write(const _CharT* __s, streamsize __n)
    {







      sentry __cerb(*this);
      if (__cerb)
 {
   try
     { _M_write(__s, __n); }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
 }
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    flush()
    {



      ios_base::iostate __err = ios_base::goodbit;
      try
 {
   if (this->rdbuf() && this->rdbuf()->pubsync() == -1)
     __err |= ios_base::badbit;
 }
      catch(__cxxabiv1::__forced_unwind&)
 {
   this->_M_setstate(ios_base::badbit);
   throw;
 }
      catch(...)
 { this->_M_setstate(ios_base::badbit); }
      if (__err)
 this->setstate(__err);
      return *this;
    }

  template<typename _CharT, typename _Traits>
    typename basic_ostream<_CharT, _Traits>::pos_type
    basic_ostream<_CharT, _Traits>::
    tellp()
    {
      pos_type __ret = pos_type(-1);
      try
 {
   if (!this->fail())
     __ret = this->rdbuf()->pubseekoff(0, ios_base::cur, ios_base::out);
 }
      catch(__cxxabiv1::__forced_unwind&)
 {
   this->_M_setstate(ios_base::badbit);
   throw;
 }
      catch(...)
 { this->_M_setstate(ios_base::badbit); }
      return __ret;
    }

  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    seekp(pos_type __pos)
    {
      ios_base::iostate __err = ios_base::goodbit;
      try
 {
   if (!this->fail())
     {


       const pos_type __p = this->rdbuf()->pubseekpos(__pos,
            ios_base::out);


       if (__p == pos_type(off_type(-1)))
  __err |= ios_base::failbit;
     }
 }
      catch(__cxxabiv1::__forced_unwind&)
 {
   this->_M_setstate(ios_base::badbit);
   throw;
 }
      catch(...)
 { this->_M_setstate(ios_base::badbit); }
      if (__err)
 this->setstate(__err);
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    seekp(off_type __off, ios_base::seekdir __dir)
    {
      ios_base::iostate __err = ios_base::goodbit;
      try
 {
   if (!this->fail())
     {


       const pos_type __p = this->rdbuf()->pubseekoff(__off, __dir,
            ios_base::out);


       if (__p == pos_type(off_type(-1)))
  __err |= ios_base::failbit;
     }
 }
      catch(__cxxabiv1::__forced_unwind&)
 {
   this->_M_setstate(ios_base::badbit);
   throw;
 }
      catch(...)
 { this->_M_setstate(ios_base::badbit); }
      if (__err)
 this->setstate(__err);
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __out, const char* __s)
    {
      if (!__s)
 __out.setstate(ios_base::badbit);
      else
 {


   const size_t __clen = char_traits<char>::length(__s);
   try
     {
       struct __ptr_guard
       {
  _CharT *__p;
  __ptr_guard (_CharT *__ip): __p(__ip) { }
  ~__ptr_guard() { delete[] __p; }
  _CharT* __get() { return __p; }
       } __pg (new _CharT[__clen]);

       _CharT *__ws = __pg.__get();
       for (size_t __i = 0; __i < __clen; ++__i)
  __ws[__i] = __out.widen(__s[__i]);
       __ostream_insert(__out, __ws, __clen);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       __out._M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { __out._M_setstate(ios_base::badbit); }
 }
      return __out;
    }




  extern template class basic_ostream<char>;
  extern template ostream& endl(ostream&);
  extern template ostream& ends(ostream&);
  extern template ostream& flush(ostream&);
  extern template ostream& operator<<(ostream&, char);
  extern template ostream& operator<<(ostream&, unsigned char);
  extern template ostream& operator<<(ostream&, signed char);
  extern template ostream& operator<<(ostream&, const char*);
  extern template ostream& operator<<(ostream&, const unsigned char*);
  extern template ostream& operator<<(ostream&, const signed char*);

  extern template ostream& ostream::_M_insert(long);
  extern template ostream& ostream::_M_insert(unsigned long);
  extern template ostream& ostream::_M_insert(bool);

  extern template ostream& ostream::_M_insert(long long);
  extern template ostream& ostream::_M_insert(unsigned long long);

  extern template ostream& ostream::_M_insert(double);
  extern template ostream& ostream::_M_insert(long double);
  extern template ostream& ostream::_M_insert(const void*);


  extern template class basic_ostream<wchar_t>;
  extern template wostream& endl(wostream&);
  extern template wostream& ends(wostream&);
  extern template wostream& flush(wostream&);
  extern template wostream& operator<<(wostream&, wchar_t);
  extern template wostream& operator<<(wostream&, char);
  extern template wostream& operator<<(wostream&, const wchar_t*);
  extern template wostream& operator<<(wostream&, const char*);

  extern template wostream& wostream::_M_insert(long);
  extern template wostream& wostream::_M_insert(unsigned long);
  extern template wostream& wostream::_M_insert(bool);

  extern template wostream& wostream::_M_insert(long long);
  extern template wostream& wostream::_M_insert(unsigned long long);

  extern template wostream& wostream::_M_insert(double);
  extern template wostream& wostream::_M_insert(long double);
  extern template wostream& wostream::_M_insert(const void*);




}
# 639 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/ostream" 2 3
# 56 "./util/string_piece.hh" 2
# 88 "./util/string_piece.hh"
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstring" 1 3
# 39 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstring" 3
       
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstring" 3
# 89 "./util/string_piece.hh" 2







# 95 "./util/string_piece.hh"
class StringPiece {
 public:
  typedef size_t size_type;

 private:
  const char* ptr_;
  size_type length_;

 public:



  StringPiece() : ptr_(
# 107 "./util/string_piece.hh" 3 4
                      __null
# 107 "./util/string_piece.hh"
                          ), length_(0) { }
  StringPiece(const char* str)
    : ptr_(str), length_((str == 
# 109 "./util/string_piece.hh" 3 4
                                __null
# 109 "./util/string_piece.hh"
                                    ) ? 0 : strlen(str)) { }
  StringPiece(const std::string& str)
    : ptr_(str.data()), length_(str.size()) { }
  StringPiece(const char* offset, size_type len)
    : ptr_(offset), length_(len) { }





  const char* data() const { return ptr_; }
  size_type size() const { return length_; }
  size_type length() const { return length_; }
  bool empty() const { return length_ == 0; }

  void clear() { ptr_ = 
# 124 "./util/string_piece.hh" 3 4
                       __null
# 124 "./util/string_piece.hh"
                           ; length_ = 0; }
  void set(const char* data, size_type len) { ptr_ = data; length_ = len; }
  void set(const char* str) {
    ptr_ = str;
    length_ = str ? strlen(str) : 0;
  }
  void set(const void* data, size_type len) {
    ptr_ = reinterpret_cast<const char*>(data);
    length_ = len;
  }

  char operator[](size_type i) const { return ptr_[i]; }

  void remove_prefix(size_type n) {
    ptr_ += n;
    length_ -= n;
  }

  void remove_suffix(size_type n) {
    length_ -= n;
  }

  int compare(const StringPiece& x) const {
    int r = wordmemcmp(ptr_, x.ptr_, std::min(length_, x.length_));
    if (r == 0) {
      if (length_ < x.length_) r = -1;
      else if (length_ > x.length_) r = +1;
    }
    return r;
  }

  std::string as_string() const {

    return std::string(!empty() ? data() : "", size());
  }

  void CopyToString(std::string* target) const;
  void AppendToString(std::string* target) const;


  bool starts_with(const StringPiece& x) const {
    return ((length_ >= x.length_) &&
            (wordmemcmp(ptr_, x.ptr_, x.length_) == 0));
  }


  bool ends_with(const StringPiece& x) const {
    return ((length_ >= x.length_) &&
            (wordmemcmp(ptr_ + (length_-x.length_), x.ptr_, x.length_) == 0));
  }


  typedef char value_type;
  typedef const char* pointer;
  typedef const char& reference;
  typedef const char& const_reference;
  typedef ptrdiff_t difference_type;
  static const size_type npos;
  typedef const char* const_iterator;
  typedef const char* iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  iterator begin() const { return ptr_; }
  iterator end() const { return ptr_ + length_; }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(ptr_ + length_);
  }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(ptr_);
  }

  size_type max_size() const { return length_; }
  size_type capacity() const { return length_; }

  size_type copy(char* buf, size_type n, size_type pos = 0) const;

  size_type find(const StringPiece& s, size_type pos = 0) const;
  size_type find(char c, size_type pos = 0) const;
  size_type rfind(const StringPiece& s, size_type pos = npos) const;
  size_type rfind(char c, size_type pos = npos) const;

  size_type find_first_of(const StringPiece& s, size_type pos = 0) const;
  size_type find_first_of(char c, size_type pos = 0) const {
    return find(c, pos);
  }
  size_type find_first_not_of(const StringPiece& s, size_type pos = 0) const;
  size_type find_first_not_of(char c, size_type pos = 0) const;
  size_type find_last_of(const StringPiece& s, size_type pos = npos) const;
  size_type find_last_of(char c, size_type pos = npos) const {
    return rfind(c, pos);
  }
  size_type find_last_not_of(const StringPiece& s, size_type pos = npos) const;
  size_type find_last_not_of(char c, size_type pos = npos) const;

  StringPiece substr(size_type pos, size_type n = npos) const;

  static int wordmemcmp(const char* p, const char* p2, size_type N) {
    return std::memcmp(p, p2, N);
  }
};

inline bool operator==(const StringPiece& x, const StringPiece& y) {
  if (x.size() != y.size())
    return false;

  return std::memcmp(x.data(), y.data(), x.size()) == 0;
}

inline bool operator!=(const StringPiece& x, const StringPiece& y) {
  return !(x == y);
}

inline bool starts_with(const StringPiece& longer, const StringPiece& prefix) {
  return longer.starts_with(prefix);
}



inline bool operator<(const StringPiece& x, const StringPiece& y) {
  const int r = std::memcmp(x.data(), y.data(),
                                       std::min(x.size(), y.size()));
  return ((r < 0) || ((r == 0) && (x.size() < y.size())));
}

inline bool operator>(const StringPiece& x, const StringPiece& y) {
  return y < x;
}

inline bool operator<=(const StringPiece& x, const StringPiece& y) {
  return !(x > y);
}

inline bool operator>=(const StringPiece& x, const StringPiece& y) {
  return !(x < y);
}


inline std::ostream& operator<<(std::ostream& o, const StringPiece& piece) {
  return o.write(piece.data(), static_cast<std::streamsize>(piece.size()));
}
# 7 "./util/fake_ostream.hh" 2

# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 1 3
# 41 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 3
       
# 42 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 3

# 1 "/usr/include/assert.h" 1 3 4






# 6 "/usr/include/assert.h" 3 4
extern "C" {
# 39 "/usr/include/assert.h" 3 4
void __attribute__((__cdecl__)) __assert (const char *, int, const char *) __attribute__ ((__noreturn__))
                                 ;
void __attribute__((__cdecl__)) __assert_func (const char *, int, const char *, const char *) __attribute__ ((__noreturn__))
                                 ;






}
# 43 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 2 3
# 9 "./util/fake_ostream.hh" 2
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/limits" 1 3
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/limits" 3
       
# 41 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/limits" 3
# 158 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/limits" 3
namespace std
{







  enum float_round_style
  {
    round_indeterminate = -1,
    round_toward_zero = 0,
    round_to_nearest = 1,
    round_toward_infinity = 2,
    round_toward_neg_infinity = 3
  };







  enum float_denorm_style
  {

    denorm_indeterminate = -1,

    denorm_absent = 0,

    denorm_present = 1
  };
# 202 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/limits" 3
  struct __numeric_limits_base
  {


    static const bool is_specialized = false;




    static const int digits = 0;


    static const int digits10 = 0;
# 223 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/limits" 3
    static const bool is_signed = false;


    static const bool is_integer = false;




    static const bool is_exact = false;



    static const int radix = 0;



    static const int min_exponent = 0;



    static const int min_exponent10 = 0;




    static const int max_exponent = 0;



    static const int max_exponent10 = 0;


    static const bool has_infinity = false;



    static const bool has_quiet_NaN = false;



    static const bool has_signaling_NaN = false;


    static const float_denorm_style has_denorm = denorm_absent;



    static const bool has_denorm_loss = false;



    static const bool is_iec559 = false;




    static const bool is_bounded = false;
# 288 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/limits" 3
    static const bool is_modulo = false;


    static const bool traps = false;


    static const bool tinyness_before = false;




    static const float_round_style round_style =
          round_toward_zero;
  };
# 314 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/limits" 3
  template<typename _Tp>
    struct numeric_limits : public __numeric_limits_base
    {


      static _Tp
      min() throw() { return _Tp(); }


      static _Tp
      max() throw() { return _Tp(); }
# 335 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/limits" 3
      static _Tp
      epsilon() throw() { return _Tp(); }


      static _Tp
      round_error() throw() { return _Tp(); }


      static _Tp
      infinity() throw() { return _Tp(); }



      static _Tp
      quiet_NaN() throw() { return _Tp(); }



      static _Tp
      signaling_NaN() throw() { return _Tp(); }




      static _Tp
      denorm_min() throw() { return _Tp(); }
    };
# 381 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/limits" 3
  template<>
    struct numeric_limits<bool>
    {
      static const bool is_specialized = true;

      static bool
      min() throw() { return false; }

      static bool
      max() throw() { return true; }





      static const int digits = 1;
      static const int digits10 = 0;



      static const bool is_signed = false;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static bool
      epsilon() throw() { return false; }

      static bool
      round_error() throw() { return false; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm
       = denorm_absent;
      static const bool has_denorm_loss = false;

      static bool
      infinity() throw() { return false; }

      static bool
      quiet_NaN() throw() { return false; }

      static bool
      signaling_NaN() throw() { return false; }

      static bool
      denorm_min() throw() { return false; }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = false;




      static const bool traps = true;
      static const bool tinyness_before = false;
      static const float_round_style round_style
       = round_toward_zero;
    };


  template<>
    struct numeric_limits<char>
    {
      static const bool is_specialized = true;

      static char
      min() throw() { return (((char)(-1) < 0) ? -(((char)(-1) < 0) ? (((((char)1 << ((sizeof(char) * 8 - ((char)(-1) < 0)) - 1)) - 1) << 1) + 1) : ~(char)0) - 1 : (char)0); }

      static char
      max() throw() { return (((char)(-1) < 0) ? (((((char)1 << ((sizeof(char) * 8 - ((char)(-1) < 0)) - 1)) - 1) << 1) + 1) : ~(char)0); }






      static const int digits = (sizeof(char) * 8 - ((char)(-1) < 0));
      static const int digits10 = ((sizeof(char) * 8 - ((char)(-1) < 0)) * 643L / 2136);



      static const bool is_signed = ((char)(-1) < 0);
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static char
      epsilon() throw() { return 0; }

      static char
      round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm
       = denorm_absent;
      static const bool has_denorm_loss = false;

      static
      char infinity() throw() { return char(); }

      static char
      quiet_NaN() throw() { return char(); }

      static char
      signaling_NaN() throw() { return char(); }

      static char
      denorm_min() throw() { return static_cast<char>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = !is_signed;

      static const bool traps = true;
      static const bool tinyness_before = false;
      static const float_round_style round_style
       = round_toward_zero;
    };


  template<>
    struct numeric_limits<signed char>
    {
      static const bool is_specialized = true;

      static signed char
      min() throw() { return -0x7f - 1; }

      static signed char
      max() throw() { return 0x7f; }






      static const int digits = (sizeof(signed char) * 8 - ((signed char)(-1) < 0));
      static const int digits10
       = ((sizeof(signed char) * 8 - ((signed char)(-1) < 0)) * 643L / 2136);



      static const bool is_signed = true;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static signed char
      epsilon() throw() { return 0; }

      static signed char
      round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm
       = denorm_absent;
      static const bool has_denorm_loss = false;

      static signed char
      infinity() throw() { return static_cast<signed char>(0); }

      static signed char
      quiet_NaN() throw() { return static_cast<signed char>(0); }

      static signed char
      signaling_NaN() throw()
      { return static_cast<signed char>(0); }

      static signed char
      denorm_min() throw()
      { return static_cast<signed char>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = false;

      static const bool traps = true;
      static const bool tinyness_before = false;
      static const float_round_style round_style
       = round_toward_zero;
    };


  template<>
    struct numeric_limits<unsigned char>
    {
      static const bool is_specialized = true;

      static unsigned char
      min() throw() { return 0; }

      static unsigned char
      max() throw() { return 0x7f * 2U + 1; }






      static const int digits
       = (sizeof(unsigned char) * 8 - ((unsigned char)(-1) < 0));
      static const int digits10
       = ((sizeof(unsigned char) * 8 - ((unsigned char)(-1) < 0)) * 643L / 2136);



      static const bool is_signed = false;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static unsigned char
      epsilon() throw() { return 0; }

      static unsigned char
      round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm
       = denorm_absent;
      static const bool has_denorm_loss = false;

      static unsigned char
      infinity() throw()
      { return static_cast<unsigned char>(0); }

      static unsigned char
      quiet_NaN() throw()
      { return static_cast<unsigned char>(0); }

      static unsigned char
      signaling_NaN() throw()
      { return static_cast<unsigned char>(0); }

      static unsigned char
      denorm_min() throw()
      { return static_cast<unsigned char>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;

      static const bool traps = true;
      static const bool tinyness_before = false;
      static const float_round_style round_style
       = round_toward_zero;
    };


  template<>
    struct numeric_limits<wchar_t>
    {
      static const bool is_specialized = true;

      static wchar_t
      min() throw() { return (((wchar_t)(-1) < 0) ? -(((wchar_t)(-1) < 0) ? (((((wchar_t)1 << ((sizeof(wchar_t) * 8 - ((wchar_t)(-1) < 0)) - 1)) - 1) << 1) + 1) : ~(wchar_t)0) - 1 : (wchar_t)0); }

      static wchar_t
      max() throw() { return (((wchar_t)(-1) < 0) ? (((((wchar_t)1 << ((sizeof(wchar_t) * 8 - ((wchar_t)(-1) < 0)) - 1)) - 1) << 1) + 1) : ~(wchar_t)0); }






      static const int digits = (sizeof(wchar_t) * 8 - ((wchar_t)(-1) < 0));
      static const int digits10
       = ((sizeof(wchar_t) * 8 - ((wchar_t)(-1) < 0)) * 643L / 2136);



      static const bool is_signed = ((wchar_t)(-1) < 0);
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static wchar_t
      epsilon() throw() { return 0; }

      static wchar_t
      round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm
       = denorm_absent;
      static const bool has_denorm_loss = false;

      static wchar_t
      infinity() throw() { return wchar_t(); }

      static wchar_t
      quiet_NaN() throw() { return wchar_t(); }

      static wchar_t
      signaling_NaN() throw() { return wchar_t(); }

      static wchar_t
      denorm_min() throw() { return wchar_t(); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = !is_signed;

      static const bool traps = true;
      static const bool tinyness_before = false;
      static const float_round_style round_style
       = round_toward_zero;
    };
# 852 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/limits" 3
  template<>
    struct numeric_limits<short>
    {
      static const bool is_specialized = true;

      static short
      min() throw() { return -0x7fff - 1; }

      static short
      max() throw() { return 0x7fff; }






      static const int digits = (sizeof(short) * 8 - ((short)(-1) < 0));
      static const int digits10 = ((sizeof(short) * 8 - ((short)(-1) < 0)) * 643L / 2136);



      static const bool is_signed = true;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static short
      epsilon() throw() { return 0; }

      static short
      round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm
       = denorm_absent;
      static const bool has_denorm_loss = false;

      static short
      infinity() throw() { return short(); }

      static short
      quiet_NaN() throw() { return short(); }

      static short
      signaling_NaN() throw() { return short(); }

      static short
      denorm_min() throw() { return short(); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = false;

      static const bool traps = true;
      static const bool tinyness_before = false;
      static const float_round_style round_style
       = round_toward_zero;
    };


  template<>
    struct numeric_limits<unsigned short>
    {
      static const bool is_specialized = true;

      static unsigned short
      min() throw() { return 0; }

      static unsigned short
      max() throw() { return 0x7fff * 2U + 1; }






      static const int digits
       = (sizeof(unsigned short) * 8 - ((unsigned short)(-1) < 0));
      static const int digits10
       = ((sizeof(unsigned short) * 8 - ((unsigned short)(-1) < 0)) * 643L / 2136);



      static const bool is_signed = false;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static unsigned short
      epsilon() throw() { return 0; }

      static unsigned short
      round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm
       = denorm_absent;
      static const bool has_denorm_loss = false;

      static unsigned short
      infinity() throw()
      { return static_cast<unsigned short>(0); }

      static unsigned short
      quiet_NaN() throw()
      { return static_cast<unsigned short>(0); }

      static unsigned short
      signaling_NaN() throw()
      { return static_cast<unsigned short>(0); }

      static unsigned short
      denorm_min() throw()
      { return static_cast<unsigned short>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;

      static const bool traps = true;
      static const bool tinyness_before = false;
      static const float_round_style round_style
       = round_toward_zero;
    };


  template<>
    struct numeric_limits<int>
    {
      static const bool is_specialized = true;

      static int
      min() throw() { return -0x7fffffff - 1; }

      static int
      max() throw() { return 0x7fffffff; }






      static const int digits = (sizeof(int) * 8 - ((int)(-1) < 0));
      static const int digits10 = ((sizeof(int) * 8 - ((int)(-1) < 0)) * 643L / 2136);



      static const bool is_signed = true;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static int
      epsilon() throw() { return 0; }

      static int
      round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm
       = denorm_absent;
      static const bool has_denorm_loss = false;

      static int
      infinity() throw() { return static_cast<int>(0); }

      static int
      quiet_NaN() throw() { return static_cast<int>(0); }

      static int
      signaling_NaN() throw() { return static_cast<int>(0); }

      static int
      denorm_min() throw() { return static_cast<int>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = false;

      static const bool traps = true;
      static const bool tinyness_before = false;
      static const float_round_style round_style
       = round_toward_zero;
    };


  template<>
    struct numeric_limits<unsigned int>
    {
      static const bool is_specialized = true;

      static unsigned int
      min() throw() { return 0; }

      static unsigned int
      max() throw() { return 0x7fffffff * 2U + 1; }






      static const int digits
       = (sizeof(unsigned int) * 8 - ((unsigned int)(-1) < 0));
      static const int digits10
       = ((sizeof(unsigned int) * 8 - ((unsigned int)(-1) < 0)) * 643L / 2136);



      static const bool is_signed = false;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static unsigned int
      epsilon() throw() { return 0; }

      static unsigned int
      round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm
       = denorm_absent;
      static const bool has_denorm_loss = false;

      static unsigned int
      infinity() throw() { return static_cast<unsigned int>(0); }

      static unsigned int
      quiet_NaN() throw()
      { return static_cast<unsigned int>(0); }

      static unsigned int
      signaling_NaN() throw()
      { return static_cast<unsigned int>(0); }

      static unsigned int
      denorm_min() throw()
      { return static_cast<unsigned int>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;

      static const bool traps = true;
      static const bool tinyness_before = false;
      static const float_round_style round_style
       = round_toward_zero;
    };


  template<>
    struct numeric_limits<long>
    {
      static const bool is_specialized = true;

      static long
      min() throw() { return -0x7fffffffffffffffL - 1; }

      static long
      max() throw() { return 0x7fffffffffffffffL; }






      static const int digits = (sizeof(long) * 8 - ((long)(-1) < 0));
      static const int digits10 = ((sizeof(long) * 8 - ((long)(-1) < 0)) * 643L / 2136);



      static const bool is_signed = true;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static long
      epsilon() throw() { return 0; }

      static long
      round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm
       = denorm_absent;
      static const bool has_denorm_loss = false;

      static long
      infinity() throw() { return static_cast<long>(0); }

      static long
      quiet_NaN() throw() { return static_cast<long>(0); }

      static long
      signaling_NaN() throw() { return static_cast<long>(0); }

      static long
      denorm_min() throw() { return static_cast<long>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = false;

      static const bool traps = true;
      static const bool tinyness_before = false;
      static const float_round_style round_style
       = round_toward_zero;
    };


  template<>
    struct numeric_limits<unsigned long>
    {
      static const bool is_specialized = true;

      static unsigned long
      min() throw() { return 0; }

      static unsigned long
      max() throw() { return 0x7fffffffffffffffL * 2UL + 1; }






      static const int digits
       = (sizeof(unsigned long) * 8 - ((unsigned long)(-1) < 0));
      static const int digits10
       = ((sizeof(unsigned long) * 8 - ((unsigned long)(-1) < 0)) * 643L / 2136);



      static const bool is_signed = false;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static unsigned long
      epsilon() throw() { return 0; }

      static unsigned long
      round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm
       = denorm_absent;
      static const bool has_denorm_loss = false;

      static unsigned long
      infinity() throw()
      { return static_cast<unsigned long>(0); }

      static unsigned long
      quiet_NaN() throw()
      { return static_cast<unsigned long>(0); }

      static unsigned long
      signaling_NaN() throw()
      { return static_cast<unsigned long>(0); }

      static unsigned long
      denorm_min() throw()
      { return static_cast<unsigned long>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;

      static const bool traps = true;
      static const bool tinyness_before = false;
      static const float_round_style round_style
       = round_toward_zero;
    };


  template<>
    struct numeric_limits<long long>
    {
      static const bool is_specialized = true;

      static long long
      min() throw() { return -0x7fffffffffffffffLL - 1; }

      static long long
      max() throw() { return 0x7fffffffffffffffLL; }






      static const int digits
       = (sizeof(long long) * 8 - ((long long)(-1) < 0));
      static const int digits10
       = ((sizeof(long long) * 8 - ((long long)(-1) < 0)) * 643L / 2136);



      static const bool is_signed = true;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static long long
      epsilon() throw() { return 0; }

      static long long
      round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm
       = denorm_absent;
      static const bool has_denorm_loss = false;

      static long long
      infinity() throw() { return static_cast<long long>(0); }

      static long long
      quiet_NaN() throw() { return static_cast<long long>(0); }

      static long long
      signaling_NaN() throw()
      { return static_cast<long long>(0); }

      static long long
      denorm_min() throw() { return static_cast<long long>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = false;

      static const bool traps = true;
      static const bool tinyness_before = false;
      static const float_round_style round_style
       = round_toward_zero;
    };


  template<>
    struct numeric_limits<unsigned long long>
    {
      static const bool is_specialized = true;

      static unsigned long long
      min() throw() { return 0; }

      static unsigned long long
      max() throw() { return 0x7fffffffffffffffLL * 2ULL + 1; }






      static const int digits
       = (sizeof(unsigned long long) * 8 - ((unsigned long long)(-1) < 0));
      static const int digits10
       = ((sizeof(unsigned long long) * 8 - ((unsigned long long)(-1) < 0)) * 643L / 2136);



      static const bool is_signed = false;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static unsigned long long
      epsilon() throw() { return 0; }

      static unsigned long long
      round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm
       = denorm_absent;
      static const bool has_denorm_loss = false;

      static unsigned long long
      infinity() throw()
      { return static_cast<unsigned long long>(0); }

      static unsigned long long
      quiet_NaN() throw()
      { return static_cast<unsigned long long>(0); }

      static unsigned long long
      signaling_NaN() throw()
      { return static_cast<unsigned long long>(0); }

      static unsigned long long
      denorm_min() throw()
      { return static_cast<unsigned long long>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;

      static const bool traps = true;
      static const bool tinyness_before = false;
      static const float_round_style round_style
       = round_toward_zero;
    };
# 1569 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/limits" 3
  template<> struct numeric_limits<__int128> { static const bool is_specialized = true; static __int128 min() throw() { return (((__int128)(-1) < 0) ? -(((__int128)(-1) < 0) ? (((((__int128)1 << ((128 - ((__int128)(-1) < 0)) - 1)) - 1) << 1) + 1) : ~(__int128)0) - 1 : (__int128)0); } static __int128 max() throw() { return (((__int128)(-1) < 0) ? (((((__int128)1 << ((128 - ((__int128)(-1) < 0)) - 1)) - 1) << 1) + 1) : ~(__int128)0); } static const int digits = 128 - 1; static const int digits10 = (128 - 1) * 643L / 2136; static const bool is_signed = true; static const bool is_integer = true; static const bool is_exact = true; static const int radix = 2; static __int128 epsilon() throw() { return 0; } static __int128 round_error() throw() { return 0; } static const int min_exponent = 0; static const int min_exponent10 = 0; static const int max_exponent = 0; static const int max_exponent10 = 0; static const bool has_infinity = false; static const bool has_quiet_NaN = false; static const bool has_signaling_NaN = false; static const float_denorm_style has_denorm = denorm_absent; static const bool has_denorm_loss = false; static __int128 infinity() throw() { return static_cast<__int128>(0); } static __int128 quiet_NaN() throw() { return static_cast<__int128>(0); } static __int128 signaling_NaN() throw() { return static_cast<__int128>(0); } static __int128 denorm_min() throw() { return static_cast<__int128>(0); } static const bool is_iec559 = false; static const bool is_bounded = true; static const bool is_modulo = false; static const bool traps = true; static const bool tinyness_before = false; static const float_round_style round_style = round_toward_zero; }; template<> struct numeric_limits<unsigned __int128> { static const bool is_specialized = true; static unsigned __int128 min() throw() { return 0; } static unsigned __int128 max() throw() { return (((unsigned __int128)(-1) < 0) ? (((((unsigned __int128)1 << ((128 - ((unsigned __int128)(-1) < 0)) - 1)) - 1) << 1) + 1) : ~(unsigned __int128)0); } static const int digits = 128; static const int digits10 = 128 * 643L / 2136; static const bool is_signed = false; static const bool is_integer = true; static const bool is_exact = true; static const int radix = 2; static unsigned __int128 epsilon() throw() { return 0; } static unsigned __int128 round_error() throw() { return 0; } static const int min_exponent = 0; static const int min_exponent10 = 0; static const int max_exponent = 0; static const int max_exponent10 = 0; static const bool has_infinity = false; static const bool has_quiet_NaN = false; static const bool has_signaling_NaN = false; static const float_denorm_style has_denorm = denorm_absent; static const bool has_denorm_loss = false; static unsigned __int128 infinity() throw() { return static_cast<unsigned __int128>(0); } static unsigned __int128 quiet_NaN() throw() { return static_cast<unsigned __int128>(0); } static unsigned __int128 signaling_NaN() throw() { return static_cast<unsigned __int128>(0); } static unsigned __int128 denorm_min() throw() { return static_cast<unsigned __int128>(0); } static const bool is_iec559 = false; static const bool is_bounded = true; static const bool is_modulo = true; static const bool traps = true; static const bool tinyness_before = false; static const float_round_style round_style = round_toward_zero; };
# 1592 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/limits" 3
  template<>
    struct numeric_limits<float>
    {
      static const bool is_specialized = true;

      static float
      min() throw() { return 1.17549435082228750797e-38F; }

      static float
      max() throw() { return 3.40282346638528859812e+38F; }






      static const int digits = 24;
      static const int digits10 = 6;




      static const bool is_signed = true;
      static const bool is_integer = false;
      static const bool is_exact = false;
      static const int radix = 2;

      static float
      epsilon() throw() { return 1.19209289550781250000e-7F; }

      static float
      round_error() throw() { return 0.5F; }

      static const int min_exponent = (-125);
      static const int min_exponent10 = (-37);
      static const int max_exponent = 128;
      static const int max_exponent10 = 38;

      static const bool has_infinity = 1;
      static const bool has_quiet_NaN = 1;
      static const bool has_signaling_NaN = has_quiet_NaN;
      static const float_denorm_style has_denorm
 = bool(1) ? denorm_present : denorm_absent;
      static const bool has_denorm_loss
       = false;

      static float
      infinity() throw() { return __builtin_huge_valf(); }

      static float
      quiet_NaN() throw() { return __builtin_nanf(""); }

      static float
      signaling_NaN() throw() { return __builtin_nansf(""); }

      static float
      denorm_min() throw() { return 1.40129846432481707092e-45F; }

      static const bool is_iec559
 = has_infinity && has_quiet_NaN && has_denorm == denorm_present;
      static const bool is_bounded = true;
      static const bool is_modulo = false;

      static const bool traps = false;
      static const bool tinyness_before
       = false;
      static const float_round_style round_style
       = round_to_nearest;
    };






  template<>
    struct numeric_limits<double>
    {
      static const bool is_specialized = true;

      static double
      min() throw() { return double(2.22507385850720138309e-308L); }

      static double
      max() throw() { return double(1.79769313486231570815e+308L); }






      static const int digits = 53;
      static const int digits10 = 15;




      static const bool is_signed = true;
      static const bool is_integer = false;
      static const bool is_exact = false;
      static const int radix = 2;

      static double
      epsilon() throw() { return double(2.22044604925031308085e-16L); }

      static double
      round_error() throw() { return 0.5; }

      static const int min_exponent = (-1021);
      static const int min_exponent10 = (-307);
      static const int max_exponent = 1024;
      static const int max_exponent10 = 308;

      static const bool has_infinity = 1;
      static const bool has_quiet_NaN = 1;
      static const bool has_signaling_NaN = has_quiet_NaN;
      static const float_denorm_style has_denorm
 = bool(1) ? denorm_present : denorm_absent;
      static const bool has_denorm_loss
        = false;

      static double
      infinity() throw() { return __builtin_huge_val(); }

      static double
      quiet_NaN() throw() { return __builtin_nan(""); }

      static double
      signaling_NaN() throw() { return __builtin_nans(""); }

      static double
      denorm_min() throw() { return double(4.94065645841246544177e-324L); }

      static const bool is_iec559
 = has_infinity && has_quiet_NaN && has_denorm == denorm_present;
      static const bool is_bounded = true;
      static const bool is_modulo = false;

      static const bool traps = false;
      static const bool tinyness_before
       = false;
      static const float_round_style round_style
       = round_to_nearest;
    };






  template<>
    struct numeric_limits<long double>
    {
      static const bool is_specialized = true;

      static long double
      min() throw() { return 3.36210314311209350626e-4932L; }

      static long double
      max() throw() { return 1.18973149535723176502e+4932L; }






      static const int digits = 64;
      static const int digits10 = 18;




      static const bool is_signed = true;
      static const bool is_integer = false;
      static const bool is_exact = false;
      static const int radix = 2;

      static long double
      epsilon() throw() { return 1.08420217248550443401e-19L; }

      static long double
      round_error() throw() { return 0.5L; }

      static const int min_exponent = (-16381);
      static const int min_exponent10 = (-4931);
      static const int max_exponent = 16384;
      static const int max_exponent10 = 4932;

      static const bool has_infinity = 1;
      static const bool has_quiet_NaN = 1;
      static const bool has_signaling_NaN = has_quiet_NaN;
      static const float_denorm_style has_denorm
 = bool(1) ? denorm_present : denorm_absent;
      static const bool has_denorm_loss
 = false;

      static long double
      infinity() throw() { return __builtin_huge_vall(); }

      static long double
      quiet_NaN() throw() { return __builtin_nanl(""); }

      static long double
      signaling_NaN() throw() { return __builtin_nansl(""); }

      static long double
      denorm_min() throw() { return 3.64519953188247460253e-4951L; }

      static const bool is_iec559
 = has_infinity && has_quiet_NaN && has_denorm == denorm_present;
      static const bool is_bounded = true;
      static const bool is_modulo = false;

      static const bool traps = false;
      static const bool tinyness_before =
      false;
      static const float_round_style round_style =
            round_to_nearest;
    };






}
# 10 "./util/fake_ostream.hh" 2




# 13 "./util/fake_ostream.hh"
namespace util {
# 36 "./util/fake_ostream.hh"
template <class Derived> class FakeOStream {
  public:
    FakeOStream() {}


    Derived &operator<<(StringPiece str) {
      return C().write(str.data(), str.size());
    }


  private:
    template <class Arg> struct EnableIfKludge {
      typedef Derived type;
    };
    template <class From, unsigned Length = sizeof(From), bool Signed = std::numeric_limits<From>::is_signed, bool IsInteger = std::numeric_limits<From>::is_integer> struct Coerce {};

    template <class From> struct Coerce<From, 2, false, true> { typedef uint16_t To; };
    template <class From> struct Coerce<From, 4, false, true> { typedef uint32_t To; };
    template <class From> struct Coerce<From, 8, false, true> { typedef uint64_t To; };

    template <class From> struct Coerce<From, 2, true, true> { typedef int16_t To; };
    template <class From> struct Coerce<From, 4, true, true> { typedef int32_t To; };
    template <class From> struct Coerce<From, 8, true, true> { typedef int64_t To; };
  public:
    template <class From> typename EnableIfKludge<typename Coerce<From>::To>::type &operator<<(const From value) {
      return CallToString(static_cast<typename Coerce<From>::To>(value));
    }


    Derived &operator<<(char val) { return put(val); }
    Derived &operator<<(signed char val) { return put(static_cast<char>(val)); }
    Derived &operator<<(unsigned char val) { return put(static_cast<char>(val)); }

    Derived &operator<<(bool val) { return put(val + '0'); }

    Derived &operator<<(int val) { return CallToString(static_cast<typename Coerce<int>::To>(val)); }

    Derived &operator<<(float val) { return CallToString(val); }
    Derived &operator<<(double val) { return CallToString(val); }


    Derived &operator<<(const void *value) { return CallToString(value); }

    Derived &operator<<(const char *value) { return *this << StringPiece(value); }
    Derived &operator<<(char *value) { return *this << StringPiece(value); }

    Derived &put(char val) {
      char *c = C().Ensure(1);
      *c = val;
      C().AdvanceTo(++c);
      return C();
    }

    char widen(char val) const { return val; }

  private:

    Derived &C() {
      return *static_cast<Derived*>(this);
    }

    const Derived &C() const {
      return *static_cast<const Derived*>(this);
    }



    template <class T> Derived &CallToString(const T value) {
      C().AdvanceTo(ToString(value, C().Ensure(ToStringBuf<T>::kBytes)));
      return C();
    }
};

}
# 5 "./util/string_stream.hh" 2

# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 1 3
# 41 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 3
       
# 42 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 3

# 1 "/usr/include/assert.h" 1 3 4






# 6 "/usr/include/assert.h" 3 4
extern "C" {
# 39 "/usr/include/assert.h" 3 4
void __attribute__((__cdecl__)) __assert (const char *, int, const char *) __attribute__ ((__noreturn__))
                                 ;
void __attribute__((__cdecl__)) __assert_func (const char *, int, const char *, const char *) __attribute__ ((__noreturn__))
                                 ;






}
# 43 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 2 3
# 7 "./util/string_stream.hh" 2



# 9 "./util/string_stream.hh"
namespace util {

class StringStream : public FakeOStream<StringStream> {
  public:
    StringStream() {}

    StringStream &flush() { return *this; }

    StringStream &write(const void *data, std::size_t length) {
      out_.append(static_cast<const char*>(data), length);
      return *this;
    }

    const std::string &str() const { return out_; }

    void str(const std::string &val) { out_ = val; }

    void swap(std::string &str) { std::swap(out_, str); }

  protected:
    friend class FakeOStream<StringStream>;
    char *Ensure(std::size_t amount) {
      std::size_t current = out_.size();
      out_.resize(out_.size() + amount);
      return &out_[current];
    }

    void AdvanceTo(char *to) {
      
# 37 "./util/string_stream.hh" 3 4
     ((
# 37 "./util/string_stream.hh"
     to <= &*out_.end()
# 37 "./util/string_stream.hh" 3 4
     ) ? (void)0 : __assert_func ("./util/string_stream.hh", 37, __PRETTY_FUNCTION__, 
# 37 "./util/string_stream.hh"
     "to <= &*out_.end()"
# 37 "./util/string_stream.hh" 3 4
     ))
# 37 "./util/string_stream.hh"
                               ;
      
# 38 "./util/string_stream.hh" 3 4
     ((
# 38 "./util/string_stream.hh"
     to >= &*out_.begin()
# 38 "./util/string_stream.hh" 3 4
     ) ? (void)0 : __assert_func ("./util/string_stream.hh", 38, __PRETTY_FUNCTION__, 
# 38 "./util/string_stream.hh"
     "to >= &*out_.begin()"
# 38 "./util/string_stream.hh" 3 4
     ))
# 38 "./util/string_stream.hh"
                                 ;
      out_.resize(to - &*out_.begin());
    }

  private:
    std::string out_;
};

}
# 5 "./util/exception.hh" 2






namespace util {

template <class Except, class Data> typename Except::template ExceptionTag<Except&>::Identity operator<<(Except &e, const Data &data);

class Exception : public std::exception {
  public:
    Exception() throw();
    virtual ~Exception() throw();

    const char *what() const throw() { return what_.str().c_str(); }


    void SetLocation(
        const char *file,
        unsigned int line,
        const char *func,
        const char *child_name,
        const char *condition);

  private:
    template <class Except, class Data> friend typename Except::template ExceptionTag<Except&>::Identity operator<<(Except &e, const Data &data);


    template <class T> struct ExceptionTag {
      typedef T Identity;
    };

    StringStream what_;
};





template <class Except, class Data> typename Except::template ExceptionTag<Except&>::Identity operator<<(Except &e, const Data &data) {
  e.what_ << data;
  return e;
}
# 109 "./util/exception.hh"
class ErrnoException : public Exception {
  public:
    ErrnoException() throw();

    virtual ~ErrnoException() throw();

    int Error() const throw() { return errno_; }

  private:
    int errno_;
};


class FileOpenException : public Exception {
  public:
 FileOpenException() throw() {}
    ~FileOpenException() throw() {}
};


class OverflowException : public Exception {
  public:
    OverflowException() throw();
    ~OverflowException() throw();
};

template <unsigned len> inline std::size_t CheckOverflowInternal(uint64_t value) {
  do { if (__builtin_expect (!!(value > static_cast<uint64_t>(std::numeric_limits<std::size_t>::max())), 0)) { do { OverflowException UTIL_e ; UTIL_e.SetLocation("./util/exception.hh", 136, __PRETTY_FUNCTION__, "OverflowException", "value > static_cast<uint64_t>(std::numeric_limits<std::size_t>::max())"); UTIL_e << "Integer overflow detected.  This model is too big for 32-bit code."; throw UTIL_e; } while (0); } } while (0);
  return value;
}

template <> inline std::size_t CheckOverflowInternal<8>(uint64_t value) {
  return value;
}

inline std::size_t CheckOverflow(uint64_t value) {
  return CheckOverflowInternal<sizeof(std::size_t)>(value);
}
# 157 "./util/exception.hh"
}
# 7 "./lm/lm_exception.hh" 2





namespace lm {

typedef enum {THROW_UP, COMPLAIN, SILENT} WarningAction;

class ConfigException : public util::Exception {
  public:
    ConfigException() throw();
    ~ConfigException() throw();
};

class LoadException : public util::Exception {
   public:
      virtual ~LoadException() throw();

   protected:
      LoadException() throw();
};

class FormatLoadException : public LoadException {
  public:
    FormatLoadException() throw();
    ~FormatLoadException() throw();
};

class VocabLoadException : public LoadException {
  public:
    virtual ~VocabLoadException() throw();
    VocabLoadException() throw();
};

class SpecialWordMissingException : public VocabLoadException {
  public:
    explicit SpecialWordMissingException() throw();
    ~SpecialWordMissingException() throw();
};

}
# 5 "./lm/config.hh" 2
# 1 "./util/mmap.hh" 1
# 11 "./util/mmap.hh"
namespace util {

class scoped_fd;

std::size_t SizePage();


class scoped_mmap {
  public:
    scoped_mmap() : data_((void*)-1), size_(0) {}
    scoped_mmap(void *data, std::size_t size) : data_(data), size_(size) {}
    ~scoped_mmap();

    void *get() const { return data_; }

    const char *begin() const { return reinterpret_cast<char*>(data_); }
    char *begin() { return reinterpret_cast<char*>(data_); }
    const char *end() const { return reinterpret_cast<char*>(data_) + size_; }
    char *end() { return reinterpret_cast<char*>(data_) + size_; }
    std::size_t size() const { return size_; }

    void reset(void *data, std::size_t size) {
      scoped_mmap other(data_, size_);
      data_ = data;
      size_ = size;
    }

    void reset() {
      reset((void*)-1, 0);
    }

    void *steal() {
      void *ret = data_;
      data_ = (void*)-1;
      size_ = 0;
      return ret;
    }

  private:
    void *data_;
    std::size_t size_;

    scoped_mmap(const scoped_mmap &);
    scoped_mmap &operator=(const scoped_mmap &);
};




class scoped_memory {
  public:
    typedef enum {
      MMAP_ROUND_UP_ALLOCATED,
      MMAP_ALLOCATED,
      MALLOC_ALLOCATED,
      NONE_ALLOCATED
    } Alloc;

    scoped_memory(void *data, std::size_t size, Alloc source)
      : data_(data), size_(size), source_(source) {}

    scoped_memory() : data_(
# 72 "./util/mmap.hh" 3 4
                           __null
# 72 "./util/mmap.hh"
                               ), size_(0), source_(NONE_ALLOCATED) {}


    scoped_memory(std::size_t to, bool zero_new);
# 84 "./util/mmap.hh"
    ~scoped_memory() { reset(); }

    void *get() const { return data_; }

    const char *begin() const { return reinterpret_cast<char*>(data_); }
    char *begin() { return reinterpret_cast<char*>(data_); }
    const char *end() const { return reinterpret_cast<char*>(data_) + size_; }
    char *end() { return reinterpret_cast<char*>(data_) + size_; }
    std::size_t size() const { return size_; }

    Alloc source() const { return source_; }

    void reset() { reset(
# 96 "./util/mmap.hh" 3 4
                        __null
# 96 "./util/mmap.hh"
                            , 0, NONE_ALLOCATED); }

    void reset(void *data, std::size_t size, Alloc from);

    void *steal() {
      void *ret = data_;
      data_ = 
# 102 "./util/mmap.hh" 3 4
             __null
# 102 "./util/mmap.hh"
                 ;
      size_ = 0;
      source_ = NONE_ALLOCATED;
      return ret;
    }

  private:
    void *data_;
    std::size_t size_;

    Alloc source_;

    scoped_memory(const scoped_memory &);
    scoped_memory &operator=(const scoped_memory &);
};

extern const int kFileFlags;


void *MapOrThrow(std::size_t size, bool for_write, int flags, bool prefault, int fd, uint64_t offset = 0);


void SyncOrThrow(void *start, size_t length);


void UnmapOrThrow(void *start, size_t length);




void HugeMalloc(std::size_t size, bool zeroed, scoped_memory &to);







void HugeRealloc(std::size_t size, bool new_zeroed, scoped_memory &mem);

enum LoadMethod {

  LAZY,

  POPULATE_OR_LAZY,

  POPULATE_OR_READ,

  READ,

  PARALLEL_READ,
};

void MapRead(LoadMethod method, int fd, uint64_t offset, std::size_t size, scoped_memory &out);


void *MapZeroedWrite(int fd, std::size_t size);
void *MapZeroedWrite(const char *name, std::size_t size, scoped_fd &file);


class Rolling {
  public:
    Rolling() {}

    explicit Rolling(void *data) { Init(data); }

    Rolling(const Rolling &copy_from, uint64_t increase = 0);
    Rolling &operator=(const Rolling &copy_from);


    explicit Rolling(int fd, bool for_write, std::size_t block, std::size_t read_bound, uint64_t offset, uint64_t amount);


    void Init(void *data) {
      ptr_ = data;
      current_end_ = std::numeric_limits<uint64_t>::max();
      current_begin_ = 0;

      fd_ = -1;
    }

    void IncreaseBase(uint64_t by) {
      file_begin_ += by;
      ptr_ = static_cast<uint8_t*>(ptr_) + by;
      if (!IsPassthrough()) current_end_ = 0;
    }

    void DecreaseBase(uint64_t by) {
      file_begin_ -= by;
      ptr_ = static_cast<uint8_t*>(ptr_) - by;
      if (!IsPassthrough()) current_end_ = 0;
    }

    void *ExtractNonRolling(scoped_memory &out, uint64_t index, std::size_t size);


    void *get() const { return ptr_; }


    void *CheckedBase(uint64_t index) {
      if (index >= current_end_ || index < current_begin_) {
        Roll(index);
      }
      return ptr_;
    }


    void *CheckedIndex(uint64_t index) {
      return static_cast<uint8_t*>(CheckedBase(index)) + index;
    }

  private:
    void Roll(uint64_t index);


    bool IsPassthrough() const { return fd_ == -1; }

    void *ptr_;
    uint64_t current_begin_;
    uint64_t current_end_;

    scoped_memory mem_;

    int fd_;
    uint64_t file_begin_;
    uint64_t file_end_;

    bool for_write_;
    std::size_t block_;
    std::size_t read_bound_;
};

}
# 6 "./lm/config.hh" 2



# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/vector" 1 3
# 58 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/vector" 3
       
# 59 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/vector" 3




# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_uninitialized.h" 1 3
# 59 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_uninitialized.h" 3

# 59 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_uninitialized.h" 3
namespace std
{


  template<bool _TrivialValueTypes>
    struct __uninitialized_copy
    {
      template<typename _InputIterator, typename _ForwardIterator>
        static _ForwardIterator
        __uninit_copy(_InputIterator __first, _InputIterator __last,
        _ForwardIterator __result)
        {
   _ForwardIterator __cur = __result;
   try
     {
       for (; __first != __last; ++__first, ++__cur)
  std::_Construct(std::__addressof(*__cur), *__first);
       return __cur;
     }
   catch(...)
     {
       std::_Destroy(__result, __cur);
       throw;
     }
 }
    };

  template<>
    struct __uninitialized_copy<true>
    {
      template<typename _InputIterator, typename _ForwardIterator>
        static _ForwardIterator
        __uninit_copy(_InputIterator __first, _InputIterator __last,
        _ForwardIterator __result)
        { return std::copy(__first, __last, __result); }
    };
# 105 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_uninitialized.h" 3
  template<typename _InputIterator, typename _ForwardIterator>
    inline _ForwardIterator
    uninitialized_copy(_InputIterator __first, _InputIterator __last,
         _ForwardIterator __result)
    {
      typedef typename iterator_traits<_InputIterator>::value_type
 _ValueType1;
      typedef typename iterator_traits<_ForwardIterator>::value_type
 _ValueType2;

      const bool __assignable = true;







      return std::__uninitialized_copy<__is_trivial(_ValueType1)
           && __is_trivial(_ValueType2)
           && __assignable>::
 __uninit_copy(__first, __last, __result);
    }


  template<bool _TrivialValueType>
    struct __uninitialized_fill
    {
      template<typename _ForwardIterator, typename _Tp>
        static void
        __uninit_fill(_ForwardIterator __first, _ForwardIterator __last,
        const _Tp& __x)
        {
   _ForwardIterator __cur = __first;
   try
     {
       for (; __cur != __last; ++__cur)
  std::_Construct(std::__addressof(*__cur), __x);
     }
   catch(...)
     {
       std::_Destroy(__first, __cur);
       throw;
     }
 }
    };

  template<>
    struct __uninitialized_fill<true>
    {
      template<typename _ForwardIterator, typename _Tp>
        static void
        __uninit_fill(_ForwardIterator __first, _ForwardIterator __last,
        const _Tp& __x)
        { std::fill(__first, __last, __x); }
    };
# 171 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_uninitialized.h" 3
  template<typename _ForwardIterator, typename _Tp>
    inline void
    uninitialized_fill(_ForwardIterator __first, _ForwardIterator __last,
         const _Tp& __x)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
 _ValueType;

      const bool __assignable = true;





      std::__uninitialized_fill<__is_trivial(_ValueType) && __assignable>::
 __uninit_fill(__first, __last, __x);
    }


  template<bool _TrivialValueType>
    struct __uninitialized_fill_n
    {
      template<typename _ForwardIterator, typename _Size, typename _Tp>
        static _ForwardIterator
        __uninit_fill_n(_ForwardIterator __first, _Size __n,
   const _Tp& __x)
        {
   _ForwardIterator __cur = __first;
   try
     {
       for (; __n > 0; --__n, ++__cur)
  std::_Construct(std::__addressof(*__cur), __x);
       return __cur;
     }
   catch(...)
     {
       std::_Destroy(__first, __cur);
       throw;
     }
 }
    };

  template<>
    struct __uninitialized_fill_n<true>
    {
      template<typename _ForwardIterator, typename _Size, typename _Tp>
        static _ForwardIterator
        __uninit_fill_n(_ForwardIterator __first, _Size __n,
   const _Tp& __x)
        { return std::fill_n(__first, __n, __x); }
    };
# 234 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_uninitialized.h" 3
  template<typename _ForwardIterator, typename _Size, typename _Tp>
    inline _ForwardIterator
    uninitialized_fill_n(_ForwardIterator __first, _Size __n, const _Tp& __x)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
 _ValueType;

      const bool __assignable = true;




      return __uninitialized_fill_n<__is_trivial(_ValueType) && __assignable>::
 __uninit_fill_n(__first, __n, __x);
    }







  template<typename _InputIterator, typename _ForwardIterator,
    typename _Allocator>
    _ForwardIterator
    __uninitialized_copy_a(_InputIterator __first, _InputIterator __last,
      _ForwardIterator __result, _Allocator& __alloc)
    {
      _ForwardIterator __cur = __result;
      try
 {
   typedef __gnu_cxx::__alloc_traits<_Allocator> __traits;
   for (; __first != __last; ++__first, ++__cur)
     __traits::construct(__alloc, std::__addressof(*__cur), *__first);
   return __cur;
 }
      catch(...)
 {
   std::_Destroy(__result, __cur, __alloc);
   throw;
 }
    }

  template<typename _InputIterator, typename _ForwardIterator, typename _Tp>
    inline _ForwardIterator
    __uninitialized_copy_a(_InputIterator __first, _InputIterator __last,
      _ForwardIterator __result, allocator<_Tp>&)
    { return std::uninitialized_copy(__first, __last, __result); }

  template<typename _InputIterator, typename _ForwardIterator,
    typename _Allocator>
    inline _ForwardIterator
    __uninitialized_move_a(_InputIterator __first, _InputIterator __last,
      _ForwardIterator __result, _Allocator& __alloc)
    {
      return std::__uninitialized_copy_a((__first),
      (__last),
      __result, __alloc);
    }

  template<typename _InputIterator, typename _ForwardIterator,
    typename _Allocator>
    inline _ForwardIterator
    __uninitialized_move_if_noexcept_a(_InputIterator __first,
           _InputIterator __last,
           _ForwardIterator __result,
           _Allocator& __alloc)
    {
      return std::__uninitialized_copy_a
 ((__first),
  (__last), __result, __alloc);
    }

  template<typename _ForwardIterator, typename _Tp, typename _Allocator>
    void
    __uninitialized_fill_a(_ForwardIterator __first, _ForwardIterator __last,
      const _Tp& __x, _Allocator& __alloc)
    {
      _ForwardIterator __cur = __first;
      try
 {
   typedef __gnu_cxx::__alloc_traits<_Allocator> __traits;
   for (; __cur != __last; ++__cur)
     __traits::construct(__alloc, std::__addressof(*__cur), __x);
 }
      catch(...)
 {
   std::_Destroy(__first, __cur, __alloc);
   throw;
 }
    }

  template<typename _ForwardIterator, typename _Tp, typename _Tp2>
    inline void
    __uninitialized_fill_a(_ForwardIterator __first, _ForwardIterator __last,
      const _Tp& __x, allocator<_Tp2>&)
    { std::uninitialized_fill(__first, __last, __x); }

  template<typename _ForwardIterator, typename _Size, typename _Tp,
    typename _Allocator>
    _ForwardIterator
    __uninitialized_fill_n_a(_ForwardIterator __first, _Size __n,
        const _Tp& __x, _Allocator& __alloc)
    {
      _ForwardIterator __cur = __first;
      try
 {
   typedef __gnu_cxx::__alloc_traits<_Allocator> __traits;
   for (; __n > 0; --__n, ++__cur)
     __traits::construct(__alloc, std::__addressof(*__cur), __x);
   return __cur;
 }
      catch(...)
 {
   std::_Destroy(__first, __cur, __alloc);
   throw;
 }
    }

  template<typename _ForwardIterator, typename _Size, typename _Tp,
    typename _Tp2>
    inline _ForwardIterator
    __uninitialized_fill_n_a(_ForwardIterator __first, _Size __n,
        const _Tp& __x, allocator<_Tp2>&)
    { return std::uninitialized_fill_n(__first, __n, __x); }
# 370 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_uninitialized.h" 3
  template<typename _InputIterator1, typename _InputIterator2,
    typename _ForwardIterator, typename _Allocator>
    inline _ForwardIterator
    __uninitialized_copy_move(_InputIterator1 __first1,
         _InputIterator1 __last1,
         _InputIterator2 __first2,
         _InputIterator2 __last2,
         _ForwardIterator __result,
         _Allocator& __alloc)
    {
      _ForwardIterator __mid = std::__uninitialized_copy_a(__first1, __last1,
          __result,
          __alloc);
      try
 {
   return std::__uninitialized_move_a(__first2, __last2, __mid, __alloc);
 }
      catch(...)
 {
   std::_Destroy(__result, __mid, __alloc);
   throw;
 }
    }





  template<typename _InputIterator1, typename _InputIterator2,
    typename _ForwardIterator, typename _Allocator>
    inline _ForwardIterator
    __uninitialized_move_copy(_InputIterator1 __first1,
         _InputIterator1 __last1,
         _InputIterator2 __first2,
         _InputIterator2 __last2,
         _ForwardIterator __result,
         _Allocator& __alloc)
    {
      _ForwardIterator __mid = std::__uninitialized_move_a(__first1, __last1,
          __result,
          __alloc);
      try
 {
   return std::__uninitialized_copy_a(__first2, __last2, __mid, __alloc);
 }
      catch(...)
 {
   std::_Destroy(__result, __mid, __alloc);
   throw;
 }
    }




  template<typename _ForwardIterator, typename _Tp, typename _InputIterator,
    typename _Allocator>
    inline _ForwardIterator
    __uninitialized_fill_move(_ForwardIterator __result, _ForwardIterator __mid,
         const _Tp& __x, _InputIterator __first,
         _InputIterator __last, _Allocator& __alloc)
    {
      std::__uninitialized_fill_a(__result, __mid, __x, __alloc);
      try
 {
   return std::__uninitialized_move_a(__first, __last, __mid, __alloc);
 }
      catch(...)
 {
   std::_Destroy(__result, __mid, __alloc);
   throw;
 }
    }




  template<typename _InputIterator, typename _ForwardIterator, typename _Tp,
    typename _Allocator>
    inline void
    __uninitialized_move_fill(_InputIterator __first1, _InputIterator __last1,
         _ForwardIterator __first2,
         _ForwardIterator __last2, const _Tp& __x,
         _Allocator& __alloc)
    {
      _ForwardIterator __mid2 = std::__uninitialized_move_a(__first1, __last1,
           __first2,
           __alloc);
      try
 {
   std::__uninitialized_fill_a(__mid2, __last2, __x, __alloc);
 }
      catch(...)
 {
   std::_Destroy(__first2, __mid2, __alloc);
   throw;
 }
    }
# 685 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_uninitialized.h" 3

}
# 64 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/vector" 2 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 1 3
# 66 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
namespace std
{



  template<typename _Tp, typename _Alloc>
    struct _Vector_base
    {
      typedef typename __gnu_cxx::__alloc_traits<_Alloc>::template
        rebind<_Tp>::other _Tp_alloc_type;
      typedef typename __gnu_cxx::__alloc_traits<_Tp_alloc_type>::pointer
        pointer;

      struct _Vector_impl
      : public _Tp_alloc_type
      {
 pointer _M_start;
 pointer _M_finish;
 pointer _M_end_of_storage;

 _Vector_impl()
 : _Tp_alloc_type(), _M_start(), _M_finish(), _M_end_of_storage()
 { }

 _Vector_impl(_Tp_alloc_type const& __a)
 : _Tp_alloc_type(__a), _M_start(), _M_finish(), _M_end_of_storage()
 { }
# 101 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
 void _M_swap_data(_Vector_impl& __x)
 {
   std::swap(_M_start, __x._M_start);
   std::swap(_M_finish, __x._M_finish);
   std::swap(_M_end_of_storage, __x._M_end_of_storage);
 }
      };

    public:
      typedef _Alloc allocator_type;

      _Tp_alloc_type&
      _M_get_Tp_allocator()
      { return *static_cast<_Tp_alloc_type*>(&this->_M_impl); }

      const _Tp_alloc_type&
      _M_get_Tp_allocator() const
      { return *static_cast<const _Tp_alloc_type*>(&this->_M_impl); }

      allocator_type
      get_allocator() const
      { return allocator_type(_M_get_Tp_allocator()); }

      _Vector_base()
      : _M_impl() { }

      _Vector_base(const allocator_type& __a)
      : _M_impl(__a) { }

      _Vector_base(size_t __n)
      : _M_impl()
      { _M_create_storage(__n); }

      _Vector_base(size_t __n, const allocator_type& __a)
      : _M_impl(__a)
      { _M_create_storage(__n); }
# 159 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      ~_Vector_base()
      { _M_deallocate(this->_M_impl._M_start, this->_M_impl._M_end_of_storage
        - this->_M_impl._M_start); }

    public:
      _Vector_impl _M_impl;

      pointer
      _M_allocate(size_t __n)
      {
 typedef __gnu_cxx::__alloc_traits<_Tp_alloc_type> _Tr;
 return __n != 0 ? _Tr::allocate(_M_impl, __n) : pointer();
      }

      void
      _M_deallocate(pointer __p, size_t __n)
      {
 typedef __gnu_cxx::__alloc_traits<_Tp_alloc_type> _Tr;
 if (__p)
   _Tr::deallocate(_M_impl, __p, __n);
      }

    private:
      void
      _M_create_storage(size_t __n)
      {
 this->_M_impl._M_start = this->_M_allocate(__n);
 this->_M_impl._M_finish = this->_M_impl._M_start;
 this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __n;
      }
    };
# 213 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
  template<typename _Tp, typename _Alloc = std::allocator<_Tp> >
    class vector : protected _Vector_base<_Tp, _Alloc>
    {

      typedef typename _Alloc::value_type _Alloc_value_type;
     
     

      typedef _Vector_base<_Tp, _Alloc> _Base;
      typedef typename _Base::_Tp_alloc_type _Tp_alloc_type;
      typedef __gnu_cxx::__alloc_traits<_Tp_alloc_type> _Alloc_traits;

    public:
      typedef _Tp value_type;
      typedef typename _Base::pointer pointer;
      typedef typename _Alloc_traits::const_pointer const_pointer;
      typedef typename _Alloc_traits::reference reference;
      typedef typename _Alloc_traits::const_reference const_reference;
      typedef __gnu_cxx::__normal_iterator<pointer, vector> iterator;
      typedef __gnu_cxx::__normal_iterator<const_pointer, vector>
      const_iterator;
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
      typedef std::reverse_iterator<iterator> reverse_iterator;
      typedef size_t size_type;
      typedef ptrdiff_t difference_type;
      typedef _Alloc allocator_type;

    protected:
      using _Base::_M_allocate;
      using _Base::_M_deallocate;
      using _Base::_M_impl;
      using _Base::_M_get_Tp_allocator;

    public:






      vector()



      : _Base() { }





      explicit
      vector(const allocator_type& __a)
      : _Base(__a) { }
# 302 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      explicit
      vector(size_type __n, const value_type& __value = value_type(),
      const allocator_type& __a = allocator_type())
      : _Base(__n, __a)
      { _M_fill_initialize(__n, __value); }
# 318 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      vector(const vector& __x)
      : _Base(__x.size(),
        _Alloc_traits::_S_select_on_copy(__x._M_get_Tp_allocator()))
      { this->_M_impl._M_finish =
   std::__uninitialized_copy_a(__x.begin(), __x.end(),
          this->_M_impl._M_start,
          _M_get_Tp_allocator());
      }
# 406 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      template<typename _InputIterator>
        vector(_InputIterator __first, _InputIterator __last,
        const allocator_type& __a = allocator_type())
 : _Base(__a)
        {

   typedef typename std::__is_integer<_InputIterator>::__type _Integral;
   _M_initialize_dispatch(__first, __last, _Integral());
 }
# 423 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      ~vector()
      { std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
        _M_get_Tp_allocator()); }
# 435 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      vector&
      operator=(const vector& __x);
# 487 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      void
      assign(size_type __n, const value_type& __val)
      { _M_fill_assign(__n, __val); }
# 510 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      template<typename _InputIterator>
        void
        assign(_InputIterator __first, _InputIterator __last)
        {

   typedef typename std::__is_integer<_InputIterator>::__type _Integral;
   _M_assign_dispatch(__first, __last, _Integral());
 }
# 538 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      using _Base::get_allocator;







      iterator
      begin()
      { return iterator(this->_M_impl._M_start); }






      const_iterator
      begin() const
      { return const_iterator(this->_M_impl._M_start); }






      iterator
      end()
      { return iterator(this->_M_impl._M_finish); }






      const_iterator
      end() const
      { return const_iterator(this->_M_impl._M_finish); }






      reverse_iterator
      rbegin()
      { return reverse_iterator(end()); }






      const_reverse_iterator
      rbegin() const
      { return const_reverse_iterator(end()); }






      reverse_iterator
      rend()
      { return reverse_iterator(begin()); }






      const_reverse_iterator
      rend() const
      { return const_reverse_iterator(begin()); }
# 653 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      size_type
      size() const
      { return size_type(this->_M_impl._M_finish - this->_M_impl._M_start); }


      size_type
      max_size() const
      { return _Alloc_traits::max_size(_M_get_Tp_allocator()); }
# 712 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      void
      resize(size_type __new_size, value_type __x = value_type())
      {
 if (__new_size > size())
   insert(end(), __new_size - size(), __x);
 else if (__new_size < size())
   _M_erase_at_end(this->_M_impl._M_start + __new_size);
      }
# 733 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      size_type
      capacity() const
      { return size_type(this->_M_impl._M_end_of_storage
    - this->_M_impl._M_start); }





      bool
      empty() const
      { return begin() == end(); }
# 763 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      void
      reserve(size_type __n);
# 778 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      reference
      operator[](size_type __n)
      { return *(this->_M_impl._M_start + __n); }
# 793 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      const_reference
      operator[](size_type __n) const
      { return *(this->_M_impl._M_start + __n); }

    protected:

      void
      _M_range_check(size_type __n) const
      {
 if (__n >= this->size())
   __throw_out_of_range_fmt(("vector::_M_range_check: __n " "(which is %zu) >= this->size() " "(which is %zu)")

                            ,
       __n, this->size());
      }

    public:
# 821 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      reference
      at(size_type __n)
      {
 _M_range_check(__n);
 return (*this)[__n];
      }
# 839 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      const_reference
      at(size_type __n) const
      {
 _M_range_check(__n);
 return (*this)[__n];
      }





      reference
      front()
      { return *begin(); }





      const_reference
      front() const
      { return *begin(); }





      reference
      back()
      { return *(end() - 1); }





      const_reference
      back() const
      { return *(end() - 1); }
# 888 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      pointer

      data()
      { return _M_data_ptr(this->_M_impl._M_start); }




      const_pointer

      data() const
      { return _M_data_ptr(this->_M_impl._M_start); }
# 912 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      void
      push_back(const value_type& __x)
      {
 if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
   {
     _Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish,
                              __x);
     ++this->_M_impl._M_finish;
   }
 else



   _M_insert_aux(end(), __x);

      }
# 948 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      void
      pop_back()
      {
 --this->_M_impl._M_finish;
 _Alloc_traits::destroy(this->_M_impl, this->_M_impl._M_finish);
      }
# 997 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      iterator
      insert(iterator __position, const value_type& __x);
# 1071 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      void
      insert(iterator __position, size_type __n, const value_type& __x)
      { _M_fill_insert(__position, __n, __x); }
# 1118 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      template<typename _InputIterator>
        void
        insert(iterator __position, _InputIterator __first,
        _InputIterator __last)
        {

   typedef typename std::__is_integer<_InputIterator>::__type _Integral;
   _M_insert_dispatch(__position, __first, __last, _Integral());
 }
# 1144 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      iterator




      erase(iterator __position)
      { return _M_erase(__position); }
# 1171 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      iterator
# 1180 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      erase(iterator __first, iterator __last)
      { return _M_erase(__first, __last); }
# 1193 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      void
      swap(vector& __x)



      {
 this->_M_impl._M_swap_data(__x._M_impl);
 _Alloc_traits::_S_on_swap(_M_get_Tp_allocator(),
                           __x._M_get_Tp_allocator());
      }







      void
      clear()
      { _M_erase_at_end(this->_M_impl._M_start); }

    protected:




      template<typename _ForwardIterator>
        pointer
        _M_allocate_and_copy(size_type __n,
        _ForwardIterator __first, _ForwardIterator __last)
        {
   pointer __result = this->_M_allocate(__n);
   try
     {
       std::__uninitialized_copy_a(__first, __last, __result,
       _M_get_Tp_allocator());
       return __result;
     }
   catch(...)
     {
       _M_deallocate(__result, __n);
       throw;
     }
 }
# 1245 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      template<typename _Integer>
        void
        _M_initialize_dispatch(_Integer __n, _Integer __value, __true_type)
        {
   this->_M_impl._M_start = _M_allocate(static_cast<size_type>(__n));
   this->_M_impl._M_end_of_storage =
     this->_M_impl._M_start + static_cast<size_type>(__n);
   _M_fill_initialize(static_cast<size_type>(__n), __value);
 }


      template<typename _InputIterator>
        void
        _M_initialize_dispatch(_InputIterator __first, _InputIterator __last,
          __false_type)
        {
   typedef typename std::iterator_traits<_InputIterator>::
     iterator_category _IterCategory;
   _M_range_initialize(__first, __last, _IterCategory());
 }


      template<typename _InputIterator>
        void
        _M_range_initialize(_InputIterator __first,
       _InputIterator __last, std::input_iterator_tag)
        {
   for (; __first != __last; ++__first)



     push_back(*__first);

 }


      template<typename _ForwardIterator>
        void
        _M_range_initialize(_ForwardIterator __first,
       _ForwardIterator __last, std::forward_iterator_tag)
        {
   const size_type __n = std::distance(__first, __last);
   this->_M_impl._M_start = this->_M_allocate(__n);
   this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __n;
   this->_M_impl._M_finish =
     std::__uninitialized_copy_a(__first, __last,
     this->_M_impl._M_start,
     _M_get_Tp_allocator());
 }



      void
      _M_fill_initialize(size_type __n, const value_type& __value)
      {
 this->_M_impl._M_finish =
   std::__uninitialized_fill_n_a(this->_M_impl._M_start, __n, __value,
     _M_get_Tp_allocator());
      }
# 1323 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      template<typename _Integer>
        void
        _M_assign_dispatch(_Integer __n, _Integer __val, __true_type)
        { _M_fill_assign(__n, __val); }


      template<typename _InputIterator>
        void
        _M_assign_dispatch(_InputIterator __first, _InputIterator __last,
      __false_type)
        {
   typedef typename std::iterator_traits<_InputIterator>::
     iterator_category _IterCategory;
   _M_assign_aux(__first, __last, _IterCategory());
 }


      template<typename _InputIterator>
        void
        _M_assign_aux(_InputIterator __first, _InputIterator __last,
        std::input_iterator_tag);


      template<typename _ForwardIterator>
        void
        _M_assign_aux(_ForwardIterator __first, _ForwardIterator __last,
        std::forward_iterator_tag);



      void
      _M_fill_assign(size_type __n, const value_type& __val);
# 1363 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      template<typename _Integer>
        void
        _M_insert_dispatch(iterator __pos, _Integer __n, _Integer __val,
      __true_type)
        { _M_fill_insert(__pos, __n, __val); }


      template<typename _InputIterator>
        void
        _M_insert_dispatch(iterator __pos, _InputIterator __first,
      _InputIterator __last, __false_type)
        {
   typedef typename std::iterator_traits<_InputIterator>::
     iterator_category _IterCategory;
   _M_range_insert(__pos, __first, __last, _IterCategory());
 }


      template<typename _InputIterator>
        void
        _M_range_insert(iterator __pos, _InputIterator __first,
   _InputIterator __last, std::input_iterator_tag);


      template<typename _ForwardIterator>
        void
        _M_range_insert(iterator __pos, _ForwardIterator __first,
   _ForwardIterator __last, std::forward_iterator_tag);



      void
      _M_fill_insert(iterator __pos, size_type __n, const value_type& __x);
# 1408 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      void
      _M_insert_aux(iterator __position, const value_type& __x);
# 1421 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      size_type
      _M_check_len(size_type __n, const char* __s) const
      {
 if (max_size() - size() < __n)
   __throw_length_error((__s));

 const size_type __len = size() + std::max(size(), __n);
 return (__len < size() || __len > max_size()) ? max_size() : __len;
      }





      void
      _M_erase_at_end(pointer __pos)
      {
 std::_Destroy(__pos, this->_M_impl._M_finish, _M_get_Tp_allocator());
 this->_M_impl._M_finish = __pos;
      }

      iterator
      _M_erase(iterator __position);

      iterator
      _M_erase(iterator __first, iterator __last);
# 1491 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
      template<typename _Ptr>
 _Ptr
 _M_data_ptr(_Ptr __ptr) const
 { return __ptr; }

    };
# 1509 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
  template<typename _Tp, typename _Alloc>
    inline bool
    operator==(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
    { return (__x.size() == __y.size()
       && std::equal(__x.begin(), __x.end(), __y.begin())); }
# 1526 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_vector.h" 3
  template<typename _Tp, typename _Alloc>
    inline bool
    operator<(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
    { return std::lexicographical_compare(__x.begin(), __x.end(),
       __y.begin(), __y.end()); }


  template<typename _Tp, typename _Alloc>
    inline bool
    operator!=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
    { return !(__x == __y); }


  template<typename _Tp, typename _Alloc>
    inline bool
    operator>(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
    { return __y < __x; }


  template<typename _Tp, typename _Alloc>
    inline bool
    operator<=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
    { return !(__y < __x); }


  template<typename _Tp, typename _Alloc>
    inline bool
    operator>=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
    { return !(__x < __y); }


  template<typename _Tp, typename _Alloc>
    inline void
    swap(vector<_Tp, _Alloc>& __x, vector<_Tp, _Alloc>& __y)
    { __x.swap(__y); }


}
# 65 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/vector" 2 3
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_bvector.h" 1 3
# 63 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_bvector.h" 3
namespace std
{


  typedef unsigned long _Bit_type;
  enum { _S_word_bit = int(8 * sizeof(_Bit_type)) };

  struct _Bit_reference
  {
    _Bit_type * _M_p;
    _Bit_type _M_mask;

    _Bit_reference(_Bit_type * __x, _Bit_type __y)
    : _M_p(__x), _M_mask(__y) { }

    _Bit_reference() : _M_p(0), _M_mask(0) { }

    operator bool() const
    { return !!(*_M_p & _M_mask); }

    _Bit_reference&
    operator=(bool __x)
    {
      if (__x)
 *_M_p |= _M_mask;
      else
 *_M_p &= ~_M_mask;
      return *this;
    }

    _Bit_reference&
    operator=(const _Bit_reference& __x)
    { return *this = bool(__x); }

    bool
    operator==(const _Bit_reference& __x) const
    { return bool(*this) == bool(__x); }

    bool
    operator<(const _Bit_reference& __x) const
    { return !bool(*this) && bool(__x); }

    void
    flip()
    { *_M_p ^= _M_mask; }
  };
# 136 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_bvector.h" 3
  struct _Bit_iterator_base
  : public std::iterator<std::random_access_iterator_tag, bool>
  {
    _Bit_type * _M_p;
    unsigned int _M_offset;

    _Bit_iterator_base(_Bit_type * __x, unsigned int __y)
    : _M_p(__x), _M_offset(__y) { }

    void
    _M_bump_up()
    {
      if (_M_offset++ == int(_S_word_bit) - 1)
 {
   _M_offset = 0;
   ++_M_p;
 }
    }

    void
    _M_bump_down()
    {
      if (_M_offset-- == 0)
 {
   _M_offset = int(_S_word_bit) - 1;
   --_M_p;
 }
    }

    void
    _M_incr(ptrdiff_t __i)
    {
      difference_type __n = __i + _M_offset;
      _M_p += __n / int(_S_word_bit);
      __n = __n % int(_S_word_bit);
      if (__n < 0)
 {
   __n += int(_S_word_bit);
   --_M_p;
 }
      _M_offset = static_cast<unsigned int>(__n);
    }

    bool
    operator==(const _Bit_iterator_base& __i) const
    { return _M_p == __i._M_p && _M_offset == __i._M_offset; }

    bool
    operator<(const _Bit_iterator_base& __i) const
    {
      return _M_p < __i._M_p
      || (_M_p == __i._M_p && _M_offset < __i._M_offset);
    }

    bool
    operator!=(const _Bit_iterator_base& __i) const
    { return !(*this == __i); }

    bool
    operator>(const _Bit_iterator_base& __i) const
    { return __i < *this; }

    bool
    operator<=(const _Bit_iterator_base& __i) const
    { return !(__i < *this); }

    bool
    operator>=(const _Bit_iterator_base& __i) const
    { return !(*this < __i); }
  };

  inline ptrdiff_t
  operator-(const _Bit_iterator_base& __x, const _Bit_iterator_base& __y)
  {
    return (int(_S_word_bit) * (__x._M_p - __y._M_p)
     + __x._M_offset - __y._M_offset);
  }

  struct _Bit_iterator : public _Bit_iterator_base
  {
    typedef _Bit_reference reference;
    typedef _Bit_reference* pointer;
    typedef _Bit_iterator iterator;

    _Bit_iterator() : _Bit_iterator_base(0, 0) { }

    _Bit_iterator(_Bit_type * __x, unsigned int __y)
    : _Bit_iterator_base(__x, __y) { }

    iterator
    _M_const_cast() const
    { return *this; }

    reference
    operator*() const
    { return reference(_M_p, 1UL << _M_offset); }

    iterator&
    operator++()
    {
      _M_bump_up();
      return *this;
    }

    iterator
    operator++(int)
    {
      iterator __tmp = *this;
      _M_bump_up();
      return __tmp;
    }

    iterator&
    operator--()
    {
      _M_bump_down();
      return *this;
    }

    iterator
    operator--(int)
    {
      iterator __tmp = *this;
      _M_bump_down();
      return __tmp;
    }

    iterator&
    operator+=(difference_type __i)
    {
      _M_incr(__i);
      return *this;
    }

    iterator&
    operator-=(difference_type __i)
    {
      *this += -__i;
      return *this;
    }

    iterator
    operator+(difference_type __i) const
    {
      iterator __tmp = *this;
      return __tmp += __i;
    }

    iterator
    operator-(difference_type __i) const
    {
      iterator __tmp = *this;
      return __tmp -= __i;
    }

    reference
    operator[](difference_type __i) const
    { return *(*this + __i); }
  };

  inline _Bit_iterator
  operator+(ptrdiff_t __n, const _Bit_iterator& __x)
  { return __x + __n; }

  struct _Bit_const_iterator : public _Bit_iterator_base
  {
    typedef bool reference;
    typedef bool const_reference;
    typedef const bool* pointer;
    typedef _Bit_const_iterator const_iterator;

    _Bit_const_iterator() : _Bit_iterator_base(0, 0) { }

    _Bit_const_iterator(_Bit_type * __x, unsigned int __y)
    : _Bit_iterator_base(__x, __y) { }

    _Bit_const_iterator(const _Bit_iterator& __x)
    : _Bit_iterator_base(__x._M_p, __x._M_offset) { }

    _Bit_iterator
    _M_const_cast() const
    { return _Bit_iterator(_M_p, _M_offset); }

    const_reference
    operator*() const
    { return _Bit_reference(_M_p, 1UL << _M_offset); }

    const_iterator&
    operator++()
    {
      _M_bump_up();
      return *this;
    }

    const_iterator
    operator++(int)
    {
      const_iterator __tmp = *this;
      _M_bump_up();
      return __tmp;
    }

    const_iterator&
    operator--()
    {
      _M_bump_down();
      return *this;
    }

    const_iterator
    operator--(int)
    {
      const_iterator __tmp = *this;
      _M_bump_down();
      return __tmp;
    }

    const_iterator&
    operator+=(difference_type __i)
    {
      _M_incr(__i);
      return *this;
    }

    const_iterator&
    operator-=(difference_type __i)
    {
      *this += -__i;
      return *this;
    }

    const_iterator
    operator+(difference_type __i) const
    {
      const_iterator __tmp = *this;
      return __tmp += __i;
    }

    const_iterator
    operator-(difference_type __i) const
    {
      const_iterator __tmp = *this;
      return __tmp -= __i;
    }

    const_reference
    operator[](difference_type __i) const
    { return *(*this + __i); }
  };

  inline _Bit_const_iterator
  operator+(ptrdiff_t __n, const _Bit_const_iterator& __x)
  { return __x + __n; }

  inline void
  __fill_bvector(_Bit_iterator __first, _Bit_iterator __last, bool __x)
  {
    for (; __first != __last; ++__first)
      *__first = __x;
  }

  inline void
  fill(_Bit_iterator __first, _Bit_iterator __last, const bool& __x)
  {
    if (__first._M_p != __last._M_p)
      {
 std::fill(__first._M_p + 1, __last._M_p, __x ? ~0 : 0);
 __fill_bvector(__first, _Bit_iterator(__first._M_p + 1, 0), __x);
 __fill_bvector(_Bit_iterator(__last._M_p, 0), __last, __x);
      }
    else
      __fill_bvector(__first, __last, __x);
  }

  template<typename _Alloc>
    struct _Bvector_base
    {
      typedef typename __gnu_cxx::__alloc_traits<_Alloc>::template
        rebind<_Bit_type>::other _Bit_alloc_type;
      typedef typename __gnu_cxx::__alloc_traits<_Bit_alloc_type>
 _Bit_alloc_traits;
      typedef typename _Bit_alloc_traits::pointer _Bit_pointer;

      struct _Bvector_impl
      : public _Bit_alloc_type
      {
 _Bit_iterator _M_start;
 _Bit_iterator _M_finish;
 _Bit_pointer _M_end_of_storage;

 _Bvector_impl()
 : _Bit_alloc_type(), _M_start(), _M_finish(), _M_end_of_storage()
 { }

 _Bvector_impl(const _Bit_alloc_type& __a)
 : _Bit_alloc_type(__a), _M_start(), _M_finish(), _M_end_of_storage()
 { }
# 441 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_bvector.h" 3
 _Bit_type*
 _M_end_addr() const
 {
   if (_M_end_of_storage)
     return std::__addressof(_M_end_of_storage[-1]) + 1;
   return 0;
 }
      };

    public:
      typedef _Alloc allocator_type;

      _Bit_alloc_type&
      _M_get_Bit_allocator()
      { return *static_cast<_Bit_alloc_type*>(&this->_M_impl); }

      const _Bit_alloc_type&
      _M_get_Bit_allocator() const
      { return *static_cast<const _Bit_alloc_type*>(&this->_M_impl); }

      allocator_type
      get_allocator() const
      { return allocator_type(_M_get_Bit_allocator()); }

      _Bvector_base()
      : _M_impl() { }

      _Bvector_base(const allocator_type& __a)
      : _M_impl(__a) { }
# 484 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_bvector.h" 3
      ~_Bvector_base()
      { this->_M_deallocate(); }

    protected:
      _Bvector_impl _M_impl;

      _Bit_pointer
      _M_allocate(size_t __n)
      { return _Bit_alloc_traits::allocate(_M_impl, _S_nword(__n)); }

      void
      _M_deallocate()
      {
 if (_M_impl._M_start._M_p)
   {
     const size_t __n = _M_impl._M_end_addr() - _M_impl._M_start._M_p;
     _Bit_alloc_traits::deallocate(_M_impl,
       _M_impl._M_end_of_storage - __n,
       __n);
   }
      }

      static size_t
      _S_nword(size_t __n)
      { return (__n + int(_S_word_bit) - 1) / int(_S_word_bit); }
    };


}




namespace std
{

# 540 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_bvector.h" 3
template<typename _Alloc>
  class vector<bool, _Alloc> : protected _Bvector_base<_Alloc>
  {
    typedef _Bvector_base<_Alloc> _Base;
    typedef typename _Base::_Bit_pointer _Bit_pointer;
    typedef typename _Base::_Bit_alloc_traits _Bit_alloc_traits;





  public:
    typedef bool value_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef _Bit_reference reference;
    typedef bool const_reference;
    typedef _Bit_reference* pointer;
    typedef const bool* const_pointer;
    typedef _Bit_iterator iterator;
    typedef _Bit_const_iterator const_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef _Alloc allocator_type;

    allocator_type get_allocator() const
    { return _Base::get_allocator(); }

  protected:
    using _Base::_M_allocate;
    using _Base::_M_deallocate;
    using _Base::_S_nword;
    using _Base::_M_get_Bit_allocator;

  public:
    vector()



    : _Base() { }

    explicit
    vector(const allocator_type& __a)
    : _Base(__a) { }
# 600 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_bvector.h" 3
    explicit
    vector(size_type __n, const bool& __value = bool(),
    const allocator_type& __a = allocator_type())
    : _Base(__a)
    {
      _M_initialize(__n);
      std::fill(this->_M_impl._M_start._M_p, this->_M_impl._M_end_addr(),
  __value ? ~0 : 0);
    }


    vector(const vector& __x)
    : _Base(_Bit_alloc_traits::_S_select_on_copy(__x._M_get_Bit_allocator()))
    {
      _M_initialize(__x.size());
      _M_copy_aligned(__x.begin(), __x.end(), this->_M_impl._M_start);
    }
# 667 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_bvector.h" 3
    template<typename _InputIterator>
      vector(_InputIterator __first, _InputIterator __last,
      const allocator_type& __a = allocator_type())
      : _Base(__a)
      {
 typedef typename std::__is_integer<_InputIterator>::__type _Integral;
 _M_initialize_dispatch(__first, __last, _Integral());
      }


    ~vector() { }

    vector&
    operator=(const vector& __x)
    {
      if (&__x == this)
 return *this;
# 699 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_bvector.h" 3
      if (__x.size() > capacity())
 {
   this->_M_deallocate();
   _M_initialize(__x.size());
 }
      this->_M_impl._M_finish = _M_copy_aligned(__x.begin(), __x.end(),
      begin());
      return *this;
    }
# 752 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_bvector.h" 3
    void
    assign(size_type __n, const bool& __x)
    { _M_fill_assign(__n, __x); }
# 763 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_bvector.h" 3
    template<typename _InputIterator>
      void
      assign(_InputIterator __first, _InputIterator __last)
      {
 typedef typename std::__is_integer<_InputIterator>::__type _Integral;
 _M_assign_dispatch(__first, __last, _Integral());
      }
# 778 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_bvector.h" 3
    iterator
    begin()
    { return this->_M_impl._M_start; }

    const_iterator
    begin() const
    { return this->_M_impl._M_start; }

    iterator
    end()
    { return this->_M_impl._M_finish; }

    const_iterator
    end() const
    { return this->_M_impl._M_finish; }

    reverse_iterator
    rbegin()
    { return reverse_iterator(end()); }

    const_reverse_iterator
    rbegin() const
    { return const_reverse_iterator(end()); }

    reverse_iterator
    rend()
    { return reverse_iterator(begin()); }

    const_reverse_iterator
    rend() const
    { return const_reverse_iterator(begin()); }
# 828 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_bvector.h" 3
    size_type
    size() const
    { return size_type(end() - begin()); }

    size_type
    max_size() const
    {
      const size_type __isize =
 __gnu_cxx::__numeric_traits<difference_type>::__max
 - int(_S_word_bit) + 1;
      const size_type __asize
 = _Bit_alloc_traits::max_size(_M_get_Bit_allocator());
      return (__asize <= __isize / int(_S_word_bit)
       ? __asize * int(_S_word_bit) : __isize);
    }

    size_type
    capacity() const
    { return size_type(const_iterator(this->_M_impl._M_end_addr(), 0)
         - begin()); }

    bool
    empty() const
    { return begin() == end(); }

    reference
    operator[](size_type __n)
    {
      return *iterator(this->_M_impl._M_start._M_p
         + __n / int(_S_word_bit), __n % int(_S_word_bit));
    }

    const_reference
    operator[](size_type __n) const
    {
      return *const_iterator(this->_M_impl._M_start._M_p
        + __n / int(_S_word_bit), __n % int(_S_word_bit));
    }

  protected:
    void
    _M_range_check(size_type __n) const
    {
      if (__n >= this->size())
 __throw_out_of_range_fmt(("vector<bool>::_M_range_check: __n " "(which is %zu) >= this->size() " "(which is %zu)")

                          ,
     __n, this->size());
    }

  public:
    reference
    at(size_type __n)
    { _M_range_check(__n); return (*this)[__n]; }

    const_reference
    at(size_type __n) const
    { _M_range_check(__n); return (*this)[__n]; }

    void
    reserve(size_type __n)
    {
      if (__n > max_size())
 __throw_length_error(("vector::reserve"));
      if (capacity() < __n)
 _M_reallocate(__n);
    }

    reference
    front()
    { return *begin(); }

    const_reference
    front() const
    { return *begin(); }

    reference
    back()
    { return *(end() - 1); }

    const_reference
    back() const
    { return *(end() - 1); }






    void
    data() { }

    void
    push_back(bool __x)
    {
      if (this->_M_impl._M_finish._M_p != this->_M_impl._M_end_addr())
        *this->_M_impl._M_finish++ = __x;
      else
        _M_insert_aux(end(), __x);
    }

    void
    swap(vector& __x)



    {
      std::swap(this->_M_impl._M_start, __x._M_impl._M_start);
      std::swap(this->_M_impl._M_finish, __x._M_impl._M_finish);
      std::swap(this->_M_impl._M_end_of_storage,
  __x._M_impl._M_end_of_storage);
      _Bit_alloc_traits::_S_on_swap(_M_get_Bit_allocator(),
        __x._M_get_Bit_allocator());
    }


    static void
    swap(reference __x, reference __y)
    {
      bool __tmp = __x;
      __x = __y;
      __y = __tmp;
    }

    iterator



    insert(iterator __position, const bool& __x = bool())

    {
      const difference_type __n = __position - begin();
      if (this->_M_impl._M_finish._M_p != this->_M_impl._M_end_addr()
   && __position == end())
        *this->_M_impl._M_finish++ = __x;
      else
        _M_insert_aux(__position._M_const_cast(), __x);
      return begin() + __n;
    }
# 981 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_bvector.h" 3
    template<typename _InputIterator>
      void
      insert(iterator __position,
      _InputIterator __first, _InputIterator __last)
      {
 typedef typename std::__is_integer<_InputIterator>::__type _Integral;
 _M_insert_dispatch(__position, __first, __last, _Integral());
      }
# 1000 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_bvector.h" 3
    void
    insert(iterator __position, size_type __n, const bool& __x)
    { _M_fill_insert(__position, __n, __x); }
# 1011 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_bvector.h" 3
    void
    pop_back()
    { --this->_M_impl._M_finish; }

    iterator



    erase(iterator __position)

    { return _M_erase(__position._M_const_cast()); }

    iterator



    erase(iterator __first, iterator __last)

    { return _M_erase(__first._M_const_cast(), __last._M_const_cast()); }

    void
    resize(size_type __new_size, bool __x = bool())
    {
      if (__new_size < size())
        _M_erase_at_end(begin() + difference_type(__new_size));
      else
        insert(end(), __new_size - size(), __x);
    }







    void
    flip()
    {
      _Bit_type * const __end = this->_M_impl._M_end_addr();
      for (_Bit_type * __p = this->_M_impl._M_start._M_p; __p != __end; ++__p)
        *__p = ~*__p;
    }

    void
    clear()
    { _M_erase_at_end(begin()); }
# 1070 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_bvector.h" 3
  protected:

    iterator
    _M_copy_aligned(const_iterator __first, const_iterator __last,
      iterator __result)
    {
      _Bit_type* __q = std::copy(__first._M_p, __last._M_p, __result._M_p);
      return std::copy(const_iterator(__last._M_p, 0), __last,
         iterator(__q, 0));
    }

    void
    _M_initialize(size_type __n)
    {
      _Bit_pointer __q = this->_M_allocate(__n);
      this->_M_impl._M_end_of_storage = __q + _S_nword(__n);
      this->_M_impl._M_start = iterator(std::__addressof(*__q), 0);
      this->_M_impl._M_finish = this->_M_impl._M_start + difference_type(__n);
    }

    void
    _M_reallocate(size_type __n);
# 1102 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_bvector.h" 3
    template<typename _Integer>
      void
      _M_initialize_dispatch(_Integer __n, _Integer __x, __true_type)
      {
 _M_initialize(static_cast<size_type>(__n));
 std::fill(this->_M_impl._M_start._M_p,
    this->_M_impl._M_end_addr(), __x ? ~0 : 0);
      }

    template<typename _InputIterator>
      void
      _M_initialize_dispatch(_InputIterator __first, _InputIterator __last,
        __false_type)
      { _M_initialize_range(__first, __last,
       std::__iterator_category(__first)); }

    template<typename _InputIterator>
      void
      _M_initialize_range(_InputIterator __first, _InputIterator __last,
     std::input_iterator_tag)
      {
 for (; __first != __last; ++__first)
   push_back(*__first);
      }

    template<typename _ForwardIterator>
      void
      _M_initialize_range(_ForwardIterator __first, _ForwardIterator __last,
     std::forward_iterator_tag)
      {
 const size_type __n = std::distance(__first, __last);
 _M_initialize(__n);
 std::copy(__first, __last, this->_M_impl._M_start);
      }



    template<typename _Integer>
      void
      _M_assign_dispatch(_Integer __n, _Integer __val, __true_type)
      { _M_fill_assign(__n, __val); }

    template<class _InputIterator>
      void
      _M_assign_dispatch(_InputIterator __first, _InputIterator __last,
    __false_type)
      { _M_assign_aux(__first, __last, std::__iterator_category(__first)); }

    void
    _M_fill_assign(size_t __n, bool __x)
    {
      if (__n > size())
 {
   std::fill(this->_M_impl._M_start._M_p,
      this->_M_impl._M_end_addr(), __x ? ~0 : 0);
   insert(end(), __n - size(), __x);
 }
      else
 {
   _M_erase_at_end(begin() + __n);
   std::fill(this->_M_impl._M_start._M_p,
      this->_M_impl._M_end_addr(), __x ? ~0 : 0);
 }
    }

    template<typename _InputIterator>
      void
      _M_assign_aux(_InputIterator __first, _InputIterator __last,
      std::input_iterator_tag)
      {
 iterator __cur = begin();
 for (; __first != __last && __cur != end(); ++__cur, ++__first)
   *__cur = *__first;
 if (__first == __last)
   _M_erase_at_end(__cur);
 else
   insert(end(), __first, __last);
      }

    template<typename _ForwardIterator>
      void
      _M_assign_aux(_ForwardIterator __first, _ForwardIterator __last,
      std::forward_iterator_tag)
      {
 const size_type __len = std::distance(__first, __last);
 if (__len < size())
   _M_erase_at_end(std::copy(__first, __last, begin()));
 else
   {
     _ForwardIterator __mid = __first;
     std::advance(__mid, size());
     std::copy(__first, __mid, begin());
     insert(end(), __mid, __last);
   }
      }





    template<typename _Integer>
      void
      _M_insert_dispatch(iterator __pos, _Integer __n, _Integer __x,
    __true_type)
      { _M_fill_insert(__pos, __n, __x); }

    template<typename _InputIterator>
      void
      _M_insert_dispatch(iterator __pos,
    _InputIterator __first, _InputIterator __last,
    __false_type)
      { _M_insert_range(__pos, __first, __last,
   std::__iterator_category(__first)); }

    void
    _M_fill_insert(iterator __position, size_type __n, bool __x);

    template<typename _InputIterator>
      void
      _M_insert_range(iterator __pos, _InputIterator __first,
        _InputIterator __last, std::input_iterator_tag)
      {
 for (; __first != __last; ++__first)
   {
     __pos = insert(__pos, *__first);
     ++__pos;
   }
      }

    template<typename _ForwardIterator>
      void
      _M_insert_range(iterator __position, _ForwardIterator __first,
        _ForwardIterator __last, std::forward_iterator_tag);

    void
    _M_insert_aux(iterator __position, bool __x);

    size_type
    _M_check_len(size_type __n, const char* __s) const
    {
      if (max_size() - size() < __n)
 __throw_length_error((__s));

      const size_type __len = size() + std::max(size(), __n);
      return (__len < size() || __len > max_size()) ? max_size() : __len;
    }

    void
    _M_erase_at_end(iterator __pos)
    { this->_M_impl._M_finish = __pos; }

    iterator
    _M_erase(iterator __pos);

    iterator
    _M_erase(iterator __first, iterator __last);
  };


}
# 66 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/vector" 2 3



# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/vector.tcc" 1 3
# 59 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/vector.tcc" 3
namespace std
{


  template<typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
    reserve(size_type __n)
    {
      if (__n > this->max_size())
 __throw_length_error(("vector::reserve"));
      if (this->capacity() < __n)
 {
   const size_type __old_size = size();
   pointer __tmp = _M_allocate_and_copy(__n,
     (this->_M_impl._M_start),
     (this->_M_impl._M_finish));
   std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
   _M_get_Tp_allocator());
   _M_deallocate(this->_M_impl._M_start,
   this->_M_impl._M_end_of_storage
   - this->_M_impl._M_start);
   this->_M_impl._M_start = __tmp;
   this->_M_impl._M_finish = __tmp + __old_size;
   this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __n;
 }
    }
# 105 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/vector.tcc" 3
  template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::iterator
    vector<_Tp, _Alloc>::



    insert(iterator __position, const value_type& __x)

    {
      const size_type __n = __position - begin();
      if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage
   && __position == end())
 {
   _Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish, __x);
   ++this->_M_impl._M_finish;
 }
      else
 {
# 133 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/vector.tcc" 3
     _M_insert_aux(__position, __x);

 }
      return iterator(this->_M_impl._M_start + __n);
    }

  template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::iterator
    vector<_Tp, _Alloc>::
    _M_erase(iterator __position)
    {
      if (__position + 1 != end())
 std::copy(__position + 1, end(), __position);
      --this->_M_impl._M_finish;
      _Alloc_traits::destroy(this->_M_impl, this->_M_impl._M_finish);
      return __position;
    }

  template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::iterator
    vector<_Tp, _Alloc>::
    _M_erase(iterator __first, iterator __last)
    {
      if (__first != __last)
 {
   if (__last != end())
     std::copy(__last, end(), __first);
   _M_erase_at_end(__first.base() + (end() - __last));
 }
      return __first;
    }

  template<typename _Tp, typename _Alloc>
    vector<_Tp, _Alloc>&
    vector<_Tp, _Alloc>::
    operator=(const vector<_Tp, _Alloc>& __x)
    {
      if (&__x != this)
 {
# 191 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/vector.tcc" 3
   const size_type __xlen = __x.size();
   if (__xlen > capacity())
     {
       pointer __tmp = _M_allocate_and_copy(__xlen, __x.begin(),
         __x.end());
       std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
       _M_get_Tp_allocator());
       _M_deallocate(this->_M_impl._M_start,
       this->_M_impl._M_end_of_storage
       - this->_M_impl._M_start);
       this->_M_impl._M_start = __tmp;
       this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __xlen;
     }
   else if (size() >= __xlen)
     {
       std::_Destroy(std::copy(__x.begin(), __x.end(), begin()),
       end(), _M_get_Tp_allocator());
     }
   else
     {
       std::copy(__x._M_impl._M_start, __x._M_impl._M_start + size(),
   this->_M_impl._M_start);
       std::__uninitialized_copy_a(__x._M_impl._M_start + size(),
       __x._M_impl._M_finish,
       this->_M_impl._M_finish,
       _M_get_Tp_allocator());
     }
   this->_M_impl._M_finish = this->_M_impl._M_start + __xlen;
 }
      return *this;
    }

  template<typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
    _M_fill_assign(size_t __n, const value_type& __val)
    {
      if (__n > capacity())
 {
   vector __tmp(__n, __val, _M_get_Tp_allocator());
   __tmp._M_impl._M_swap_data(this->_M_impl);
 }
      else if (__n > size())
 {
   std::fill(begin(), end(), __val);
   this->_M_impl._M_finish =
     std::__uninitialized_fill_n_a(this->_M_impl._M_finish,
       __n - size(), __val,
       _M_get_Tp_allocator());
 }
      else
        _M_erase_at_end(std::fill_n(this->_M_impl._M_start, __n, __val));
    }

  template<typename _Tp, typename _Alloc>
    template<typename _InputIterator>
      void
      vector<_Tp, _Alloc>::
      _M_assign_aux(_InputIterator __first, _InputIterator __last,
      std::input_iterator_tag)
      {
 pointer __cur(this->_M_impl._M_start);
 for (; __first != __last && __cur != this->_M_impl._M_finish;
      ++__cur, ++__first)
   *__cur = *__first;
 if (__first == __last)
   _M_erase_at_end(__cur);
 else
   insert(end(), __first, __last);
      }

  template<typename _Tp, typename _Alloc>
    template<typename _ForwardIterator>
      void
      vector<_Tp, _Alloc>::
      _M_assign_aux(_ForwardIterator __first, _ForwardIterator __last,
      std::forward_iterator_tag)
      {
 const size_type __len = std::distance(__first, __last);

 if (__len > capacity())
   {
     pointer __tmp(_M_allocate_and_copy(__len, __first, __last));
     std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
     _M_get_Tp_allocator());
     _M_deallocate(this->_M_impl._M_start,
     this->_M_impl._M_end_of_storage
     - this->_M_impl._M_start);
     this->_M_impl._M_start = __tmp;
     this->_M_impl._M_finish = this->_M_impl._M_start + __len;
     this->_M_impl._M_end_of_storage = this->_M_impl._M_finish;
   }
 else if (size() >= __len)
   _M_erase_at_end(std::copy(__first, __last, this->_M_impl._M_start));
 else
   {
     _ForwardIterator __mid = __first;
     std::advance(__mid, size());
     std::copy(__first, __mid, this->_M_impl._M_start);
     this->_M_impl._M_finish =
       std::__uninitialized_copy_a(__mid, __last,
       this->_M_impl._M_finish,
       _M_get_Tp_allocator());
   }
      }
# 324 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/vector.tcc" 3
  template<typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
    _M_insert_aux(iterator __position, const _Tp& __x)

    {
      if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
 {
   _Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish,
              (*(this->_M_impl._M_finish - 1))
                            );
   ++this->_M_impl._M_finish;

   _Tp __x_copy = __x;

   std::copy_backward(__position.base(), this->_M_impl._M_finish - 2, this->_M_impl._M_finish - 1)

                                  ;

   *__position = __x_copy;



 }
      else
 {
   const size_type __len =
     _M_check_len(size_type(1), "vector::_M_insert_aux");
   const size_type __elems_before = __position - begin();
   pointer __new_start(this->_M_allocate(__len));
   pointer __new_finish(__new_start);
   try
     {




       _Alloc_traits::construct(this->_M_impl,
                         __new_start + __elems_before,



                                __x);

       __new_finish = pointer();

       __new_finish
  = std::__uninitialized_move_if_noexcept_a
  (this->_M_impl._M_start, __position.base(),
   __new_start, _M_get_Tp_allocator());

       ++__new_finish;

       __new_finish
  = std::__uninitialized_move_if_noexcept_a
  (__position.base(), this->_M_impl._M_finish,
   __new_finish, _M_get_Tp_allocator());
     }
          catch(...)
     {
       if (!__new_finish)
  _Alloc_traits::destroy(this->_M_impl,
                         __new_start + __elems_before);
       else
  std::_Destroy(__new_start, __new_finish, _M_get_Tp_allocator());
       _M_deallocate(__new_start, __len);
       throw;
     }
   std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
   _M_get_Tp_allocator());
   _M_deallocate(this->_M_impl._M_start,
   this->_M_impl._M_end_of_storage
   - this->_M_impl._M_start);
   this->_M_impl._M_start = __new_start;
   this->_M_impl._M_finish = __new_finish;
   this->_M_impl._M_end_of_storage = __new_start + __len;
 }
    }
# 447 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/vector.tcc" 3
  template<typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
    _M_fill_insert(iterator __position, size_type __n, const value_type& __x)
    {
      if (__n != 0)
 {
   if (size_type(this->_M_impl._M_end_of_storage
   - this->_M_impl._M_finish) >= __n)
     {
       value_type __x_copy = __x;
       const size_type __elems_after = end() - __position;
       pointer __old_finish(this->_M_impl._M_finish);
       if (__elems_after > __n)
  {
    std::__uninitialized_move_a(this->_M_impl._M_finish - __n,
           this->_M_impl._M_finish,
           this->_M_impl._M_finish,
           _M_get_Tp_allocator());
    this->_M_impl._M_finish += __n;
    std::copy_backward(__position.base(), __old_finish - __n, __old_finish)
                                        ;
    std::fill(__position.base(), __position.base() + __n,
       __x_copy);
  }
       else
  {
    this->_M_impl._M_finish =
      std::__uninitialized_fill_n_a(this->_M_impl._M_finish,
        __n - __elems_after,
        __x_copy,
        _M_get_Tp_allocator());
    std::__uninitialized_move_a(__position.base(), __old_finish,
           this->_M_impl._M_finish,
           _M_get_Tp_allocator());
    this->_M_impl._M_finish += __elems_after;
    std::fill(__position.base(), __old_finish, __x_copy);
  }
     }
   else
     {
       const size_type __len =
  _M_check_len(__n, "vector::_M_fill_insert");
       const size_type __elems_before = __position - begin();
       pointer __new_start(this->_M_allocate(__len));
       pointer __new_finish(__new_start);
       try
  {

    std::__uninitialized_fill_n_a(__new_start + __elems_before,
      __n, __x,
      _M_get_Tp_allocator());
    __new_finish = pointer();

    __new_finish
      = std::__uninitialized_move_if_noexcept_a
      (this->_M_impl._M_start, __position.base(),
       __new_start, _M_get_Tp_allocator());

    __new_finish += __n;

    __new_finish
      = std::__uninitialized_move_if_noexcept_a
      (__position.base(), this->_M_impl._M_finish,
       __new_finish, _M_get_Tp_allocator());
  }
       catch(...)
  {
    if (!__new_finish)
      std::_Destroy(__new_start + __elems_before,
      __new_start + __elems_before + __n,
      _M_get_Tp_allocator());
    else
      std::_Destroy(__new_start, __new_finish,
      _M_get_Tp_allocator());
    _M_deallocate(__new_start, __len);
    throw;
  }
       std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
       _M_get_Tp_allocator());
       _M_deallocate(this->_M_impl._M_start,
       this->_M_impl._M_end_of_storage
       - this->_M_impl._M_start);
       this->_M_impl._M_start = __new_start;
       this->_M_impl._M_finish = __new_finish;
       this->_M_impl._M_end_of_storage = __new_start + __len;
     }
 }
    }
# 599 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/vector.tcc" 3
  template<typename _Tp, typename _Alloc>
    template<typename _InputIterator>
      void
      vector<_Tp, _Alloc>::
      _M_range_insert(iterator __pos, _InputIterator __first,
        _InputIterator __last, std::input_iterator_tag)
      {
 for (; __first != __last; ++__first)
   {
     __pos = insert(__pos, *__first);
     ++__pos;
   }
      }

  template<typename _Tp, typename _Alloc>
    template<typename _ForwardIterator>
      void
      vector<_Tp, _Alloc>::
      _M_range_insert(iterator __position, _ForwardIterator __first,
        _ForwardIterator __last, std::forward_iterator_tag)
      {
 if (__first != __last)
   {
     const size_type __n = std::distance(__first, __last);
     if (size_type(this->_M_impl._M_end_of_storage
     - this->_M_impl._M_finish) >= __n)
       {
  const size_type __elems_after = end() - __position;
  pointer __old_finish(this->_M_impl._M_finish);
  if (__elems_after > __n)
    {
      std::__uninitialized_move_a(this->_M_impl._M_finish - __n,
      this->_M_impl._M_finish,
      this->_M_impl._M_finish,
      _M_get_Tp_allocator());
      this->_M_impl._M_finish += __n;
      std::copy_backward(__position.base(), __old_finish - __n, __old_finish)
                                          ;
      std::copy(__first, __last, __position);
    }
  else
    {
      _ForwardIterator __mid = __first;
      std::advance(__mid, __elems_after);
      std::__uninitialized_copy_a(__mid, __last,
      this->_M_impl._M_finish,
      _M_get_Tp_allocator());
      this->_M_impl._M_finish += __n - __elems_after;
      std::__uninitialized_move_a(__position.base(),
      __old_finish,
      this->_M_impl._M_finish,
      _M_get_Tp_allocator());
      this->_M_impl._M_finish += __elems_after;
      std::copy(__first, __mid, __position);
    }
       }
     else
       {
  const size_type __len =
    _M_check_len(__n, "vector::_M_range_insert");
  pointer __new_start(this->_M_allocate(__len));
  pointer __new_finish(__new_start);
  try
    {
      __new_finish
        = std::__uninitialized_move_if_noexcept_a
        (this->_M_impl._M_start, __position.base(),
         __new_start, _M_get_Tp_allocator());
      __new_finish
        = std::__uninitialized_copy_a(__first, __last,
          __new_finish,
          _M_get_Tp_allocator());
      __new_finish
        = std::__uninitialized_move_if_noexcept_a
        (__position.base(), this->_M_impl._M_finish,
         __new_finish, _M_get_Tp_allocator());
    }
  catch(...)
    {
      std::_Destroy(__new_start, __new_finish,
      _M_get_Tp_allocator());
      _M_deallocate(__new_start, __len);
      throw;
    }
  std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
         _M_get_Tp_allocator());
  _M_deallocate(this->_M_impl._M_start,
         this->_M_impl._M_end_of_storage
         - this->_M_impl._M_start);
  this->_M_impl._M_start = __new_start;
  this->_M_impl._M_finish = __new_finish;
  this->_M_impl._M_end_of_storage = __new_start + __len;
       }
   }
      }



  template<typename _Alloc>
    void
    vector<bool, _Alloc>::
    _M_reallocate(size_type __n)
    {
      _Bit_pointer __q = this->_M_allocate(__n);
      iterator __start(std::__addressof(*__q), 0);
      this->_M_impl._M_finish = _M_copy_aligned(begin(), end(), __start);
      this->_M_deallocate();
      this->_M_impl._M_start = __start;
      this->_M_impl._M_end_of_storage = __q + _S_nword(__n);
    }

  template<typename _Alloc>
    void
    vector<bool, _Alloc>::
    _M_fill_insert(iterator __position, size_type __n, bool __x)
    {
      if (__n == 0)
 return;
      if (capacity() - size() >= __n)
 {
   std::copy_backward(__position, end(),
        this->_M_impl._M_finish + difference_type(__n));
   std::fill(__position, __position + difference_type(__n), __x);
   this->_M_impl._M_finish += difference_type(__n);
 }
      else
 {
   const size_type __len =
     _M_check_len(__n, "vector<bool>::_M_fill_insert");
   _Bit_pointer __q = this->_M_allocate(__len);
   iterator __start(std::__addressof(*__q), 0);
   iterator __i = _M_copy_aligned(begin(), __position, __start);
   std::fill(__i, __i + difference_type(__n), __x);
   this->_M_impl._M_finish = std::copy(__position, end(),
           __i + difference_type(__n));
   this->_M_deallocate();
   this->_M_impl._M_end_of_storage = __q + _S_nword(__len);
   this->_M_impl._M_start = __start;
 }
    }

  template<typename _Alloc>
    template<typename _ForwardIterator>
      void
      vector<bool, _Alloc>::
      _M_insert_range(iterator __position, _ForwardIterator __first,
        _ForwardIterator __last, std::forward_iterator_tag)
      {
 if (__first != __last)
   {
     size_type __n = std::distance(__first, __last);
     if (capacity() - size() >= __n)
       {
  std::copy_backward(__position, end(),
       this->_M_impl._M_finish
       + difference_type(__n));
  std::copy(__first, __last, __position);
  this->_M_impl._M_finish += difference_type(__n);
       }
     else
       {
  const size_type __len =
    _M_check_len(__n, "vector<bool>::_M_insert_range");
  _Bit_pointer __q = this->_M_allocate(__len);
  iterator __start(std::__addressof(*__q), 0);
  iterator __i = _M_copy_aligned(begin(), __position, __start);
  __i = std::copy(__first, __last, __i);
  this->_M_impl._M_finish = std::copy(__position, end(), __i);
  this->_M_deallocate();
  this->_M_impl._M_end_of_storage = __q + _S_nword(__len);
  this->_M_impl._M_start = __start;
       }
   }
      }

  template<typename _Alloc>
    void
    vector<bool, _Alloc>::
    _M_insert_aux(iterator __position, bool __x)
    {
      if (this->_M_impl._M_finish._M_p != this->_M_impl._M_end_addr())
 {
   std::copy_backward(__position, this->_M_impl._M_finish,
        this->_M_impl._M_finish + 1);
   *__position = __x;
   ++this->_M_impl._M_finish;
 }
      else
 {
   const size_type __len =
     _M_check_len(size_type(1), "vector<bool>::_M_insert_aux");
   _Bit_pointer __q = this->_M_allocate(__len);
   iterator __start(std::__addressof(*__q), 0);
   iterator __i = _M_copy_aligned(begin(), __position, __start);
   *__i++ = __x;
   this->_M_impl._M_finish = std::copy(__position, end(), __i);
   this->_M_deallocate();
   this->_M_impl._M_end_of_storage = __q + _S_nword(__len);
   this->_M_impl._M_start = __start;
 }
    }

  template<typename _Alloc>
    typename vector<bool, _Alloc>::iterator
    vector<bool, _Alloc>::
    _M_erase(iterator __position)
    {
      if (__position + 1 != end())
        std::copy(__position + 1, end(), __position);
      --this->_M_impl._M_finish;
      return __position;
    }

  template<typename _Alloc>
    typename vector<bool, _Alloc>::iterator
    vector<bool, _Alloc>::
    _M_erase(iterator __first, iterator __last)
    {
      if (__first != __last)
 _M_erase_at_end(std::copy(__last, end(), __first));
      return __first;
    }
# 840 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/vector.tcc" 3

}
# 70 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/vector" 2 3
# 10 "./lm/config.hh" 2




# 13 "./lm/config.hh"
namespace lm {

class EnumerateVocab;

namespace ngram {

struct Config {



  bool show_progress;



  std::ostream *messages;

  std::ostream *ProgressMessages() const {
    return show_progress ? messages : 0;
  }





  EnumerateVocab *enumerate_vocab;





  WarningAction unknown_missing;


  WarningAction sentence_marker_missing;



  WarningAction positive_log_probability;



  float unknown_missing_logprob;






  float probing_multiplier;




  std::size_t building_memory;





  std::string temporary_directory_prefix;


  enum ARPALoadComplain {ALL, EXPENSIVE, NONE};
  ARPALoadComplain arpa_complain;



  const char *write_mmap;

  enum WriteMethod {
    WRITE_MMAP,
    WRITE_AFTER
  };
  WriteMethod write_method;


  bool include_vocab;



  enum RestFunction {
    REST_MAX,
    REST_LOWER,
  };
  RestFunction rest_function;

  std::vector<std::string> rest_lower_files;





  uint8_t prob_bits, backoff_bits;


  uint8_t pointer_bhiksha_bits;






  util::LoadMethod load_method;



  Config();
};

} }
# 5 "./lm/binary_format.hh" 2

# 1 "./lm/read_arpa.hh" 1






# 1 "./util/file_piece.hh" 1



# 1 "./util/ersatz_progress.hh" 1



# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/iostream" 1 3
# 36 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/iostream" 3
       
# 37 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/iostream" 3



# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 1 3
# 36 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
       
# 37 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3





# 41 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
namespace std
{

# 57 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
  template<typename _CharT, typename _Traits>
    class basic_istream : virtual public basic_ios<_CharT, _Traits>
    {
    public:

      typedef _CharT char_type;
      typedef typename _Traits::int_type int_type;
      typedef typename _Traits::pos_type pos_type;
      typedef typename _Traits::off_type off_type;
      typedef _Traits traits_type;


      typedef basic_streambuf<_CharT, _Traits> __streambuf_type;
      typedef basic_ios<_CharT, _Traits> __ios_type;
      typedef basic_istream<_CharT, _Traits> __istream_type;
      typedef num_get<_CharT, istreambuf_iterator<_CharT, _Traits> >
        __num_get_type;
      typedef ctype<_CharT> __ctype_type;

    protected:





      streamsize _M_gcount;

    public:







      explicit
      basic_istream(__streambuf_type* __sb)
      : _M_gcount(streamsize(0))
      { this->init(__sb); }






      virtual
      ~basic_istream()
      { _M_gcount = streamsize(0); }


      class sentry;
      friend class sentry;
# 119 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
      __istream_type&
      operator>>(__istream_type& (*__pf)(__istream_type&))
      { return __pf(*this); }

      __istream_type&
      operator>>(__ios_type& (*__pf)(__ios_type&))
      {
 __pf(*this);
 return *this;
      }

      __istream_type&
      operator>>(ios_base& (*__pf)(ios_base&))
      {
 __pf(*this);
 return *this;
      }
# 167 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
      __istream_type&
      operator>>(bool& __n)
      { return _M_extract(__n); }

      __istream_type&
      operator>>(short& __n);

      __istream_type&
      operator>>(unsigned short& __n)
      { return _M_extract(__n); }

      __istream_type&
      operator>>(int& __n);

      __istream_type&
      operator>>(unsigned int& __n)
      { return _M_extract(__n); }

      __istream_type&
      operator>>(long& __n)
      { return _M_extract(__n); }

      __istream_type&
      operator>>(unsigned long& __n)
      { return _M_extract(__n); }


      __istream_type&
      operator>>(long long& __n)
      { return _M_extract(__n); }

      __istream_type&
      operator>>(unsigned long long& __n)
      { return _M_extract(__n); }
# 213 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
      __istream_type&
      operator>>(float& __f)
      { return _M_extract(__f); }

      __istream_type&
      operator>>(double& __f)
      { return _M_extract(__f); }

      __istream_type&
      operator>>(long double& __f)
      { return _M_extract(__f); }
# 234 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
      __istream_type&
      operator>>(void*& __p)
      { return _M_extract(__p); }
# 258 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
      __istream_type&
      operator>>(__streambuf_type* __sb);
# 268 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
      streamsize
      gcount() const
      { return _M_gcount; }
# 301 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
      int_type
      get();
# 315 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
      __istream_type&
      get(char_type& __c);
# 342 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
      __istream_type&
      get(char_type* __s, streamsize __n, char_type __delim);
# 353 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
      __istream_type&
      get(char_type* __s, streamsize __n)
      { return this->get(__s, __n, this->widen('\n')); }
# 376 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
      __istream_type&
      get(__streambuf_type& __sb, char_type __delim);
# 386 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
      __istream_type&
      get(__streambuf_type& __sb)
      { return this->get(__sb, this->widen('\n')); }
# 415 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
      __istream_type&
      getline(char_type* __s, streamsize __n, char_type __delim);
# 426 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
      __istream_type&
      getline(char_type* __s, streamsize __n)
      { return this->getline(__s, __n, this->widen('\n')); }
# 450 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
      __istream_type&
      ignore(streamsize __n, int_type __delim);

      __istream_type&
      ignore(streamsize __n);

      __istream_type&
      ignore();
# 467 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
      int_type
      peek();
# 485 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
      __istream_type&
      read(char_type* __s, streamsize __n);
# 504 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
      streamsize
      readsome(char_type* __s, streamsize __n);
# 521 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
      __istream_type&
      putback(char_type __c);
# 537 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
      __istream_type&
      unget();
# 555 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
      int
      sync();
# 570 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
      pos_type
      tellg();
# 585 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
      __istream_type&
      seekg(pos_type);
# 601 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
      __istream_type&
      seekg(off_type, ios_base::seekdir);


    protected:
      basic_istream()
      : _M_gcount(streamsize(0))
      { this->init(0); }
# 639 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
      template<typename _ValueT>
 __istream_type&
 _M_extract(_ValueT& __v);
    };


  template<>
    basic_istream<char>&
    basic_istream<char>::
    getline(char_type* __s, streamsize __n, char_type __delim);

  template<>
    basic_istream<char>&
    basic_istream<char>::
    ignore(streamsize __n);

  template<>
    basic_istream<char>&
    basic_istream<char>::
    ignore(streamsize __n, int_type __delim);


  template<>
    basic_istream<wchar_t>&
    basic_istream<wchar_t>::
    getline(char_type* __s, streamsize __n, char_type __delim);

  template<>
    basic_istream<wchar_t>&
    basic_istream<wchar_t>::
    ignore(streamsize __n);

  template<>
    basic_istream<wchar_t>&
    basic_istream<wchar_t>::
    ignore(streamsize __n, int_type __delim);
# 685 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
  template<typename _CharT, typename _Traits>
    class basic_istream<_CharT, _Traits>::sentry
    {

      bool _M_ok;

    public:

      typedef _Traits traits_type;
      typedef basic_streambuf<_CharT, _Traits> __streambuf_type;
      typedef basic_istream<_CharT, _Traits> __istream_type;
      typedef typename __istream_type::__ctype_type __ctype_type;
      typedef typename _Traits::int_type __int_type;
# 721 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
      explicit
      sentry(basic_istream<_CharT, _Traits>& __is, bool __noskipws = false);
# 734 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
      operator bool() const
      { return _M_ok; }
    };
# 750 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __in, _CharT& __c);

  template<class _Traits>
    inline basic_istream<char, _Traits>&
    operator>>(basic_istream<char, _Traits>& __in, unsigned char& __c)
    { return (__in >> reinterpret_cast<char&>(__c)); }

  template<class _Traits>
    inline basic_istream<char, _Traits>&
    operator>>(basic_istream<char, _Traits>& __in, signed char& __c)
    { return (__in >> reinterpret_cast<char&>(__c)); }
# 792 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __in, _CharT* __s);


  template<>
    basic_istream<char>&
    operator>>(basic_istream<char>& __in, char* __s);

  template<class _Traits>
    inline basic_istream<char, _Traits>&
    operator>>(basic_istream<char, _Traits>& __in, unsigned char* __s)
    { return (__in >> reinterpret_cast<char*>(__s)); }

  template<class _Traits>
    inline basic_istream<char, _Traits>&
    operator>>(basic_istream<char, _Traits>& __in, signed char* __s)
    { return (__in >> reinterpret_cast<char*>(__s)); }
# 823 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
  template<typename _CharT, typename _Traits>
    class basic_iostream
    : public basic_istream<_CharT, _Traits>,
      public basic_ostream<_CharT, _Traits>
    {
    public:



      typedef _CharT char_type;
      typedef typename _Traits::int_type int_type;
      typedef typename _Traits::pos_type pos_type;
      typedef typename _Traits::off_type off_type;
      typedef _Traits traits_type;


      typedef basic_istream<_CharT, _Traits> __istream_type;
      typedef basic_ostream<_CharT, _Traits> __ostream_type;







      explicit
      basic_iostream(basic_streambuf<_CharT, _Traits>* __sb)
      : __istream_type(__sb), __ostream_type(__sb) { }




      virtual
      ~basic_iostream() { }

    protected:
      basic_iostream()
      : __istream_type(), __ostream_type() { }
# 884 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
    };
# 906 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    ws(basic_istream<_CharT, _Traits>& __is);
# 931 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 3

}

# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/istream.tcc" 1 3
# 37 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/istream.tcc" 3
       
# 38 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/istream.tcc" 3



namespace std
{


  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>::sentry::
    sentry(basic_istream<_CharT, _Traits>& __in, bool __noskip) : _M_ok(false)
    {
      ios_base::iostate __err = ios_base::goodbit;
      if (__in.good())
 {
   if (__in.tie())
     __in.tie()->flush();
   if (!__noskip && bool(__in.flags() & ios_base::skipws))
     {
       const __int_type __eof = traits_type::eof();
       __streambuf_type* __sb = __in.rdbuf();
       __int_type __c = __sb->sgetc();

       const __ctype_type& __ct = __check_facet(__in._M_ctype);
       while (!traits_type::eq_int_type(__c, __eof)
       && __ct.is(ctype_base::space,
    traits_type::to_char_type(__c)))
  __c = __sb->snextc();




       if (traits_type::eq_int_type(__c, __eof))
  __err |= ios_base::eofbit;
     }
 }

      if (__in.good() && __err == ios_base::goodbit)
 _M_ok = true;
      else
 {
   __err |= ios_base::failbit;
   __in.setstate(__err);
 }
    }

  template<typename _CharT, typename _Traits>
    template<typename _ValueT>
      basic_istream<_CharT, _Traits>&
      basic_istream<_CharT, _Traits>::
      _M_extract(_ValueT& __v)
      {
 sentry __cerb(*this, false);
 if (__cerb)
   {
     ios_base::iostate __err = ios_base::goodbit;
     try
       {
  const __num_get_type& __ng = __check_facet(this->_M_num_get);
  __ng.get(*this, 0, *this, __err, __v);
       }
     catch(__cxxabiv1::__forced_unwind&)
       {
  this->_M_setstate(ios_base::badbit);
  throw;
       }
     catch(...)
       { this->_M_setstate(ios_base::badbit); }
     if (__err)
       this->setstate(__err);
   }
 return *this;
      }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    operator>>(short& __n)
    {


      sentry __cerb(*this, false);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       long __l;
       const __num_get_type& __ng = __check_facet(this->_M_num_get);
       __ng.get(*this, 0, *this, __err, __l);



       if (__l < __gnu_cxx::__numeric_traits<short>::__min)
  {
    __err |= ios_base::failbit;
    __n = __gnu_cxx::__numeric_traits<short>::__min;
  }
       else if (__l > __gnu_cxx::__numeric_traits<short>::__max)
  {
    __err |= ios_base::failbit;
    __n = __gnu_cxx::__numeric_traits<short>::__max;
  }
       else
  __n = short(__l);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    operator>>(int& __n)
    {


      sentry __cerb(*this, false);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       long __l;
       const __num_get_type& __ng = __check_facet(this->_M_num_get);
       __ng.get(*this, 0, *this, __err, __l);



       if (__l < __gnu_cxx::__numeric_traits<int>::__min)
  {
    __err |= ios_base::failbit;
    __n = __gnu_cxx::__numeric_traits<int>::__min;
  }
       else if (__l > __gnu_cxx::__numeric_traits<int>::__max)
  {
    __err |= ios_base::failbit;
    __n = __gnu_cxx::__numeric_traits<int>::__max;
  }
       else
  __n = int(__l);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    operator>>(__streambuf_type* __sbout)
    {
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this, false);
      if (__cerb && __sbout)
 {
   try
     {
       bool __ineof;
       if (!__copy_streambufs_eof(this->rdbuf(), __sbout, __ineof))
  __err |= ios_base::failbit;
       if (__ineof)
  __err |= ios_base::eofbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::failbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::failbit); }
 }
      else if (!__sbout)
 __err |= ios_base::failbit;
      if (__err)
 this->setstate(__err);
      return *this;
    }

  template<typename _CharT, typename _Traits>
    typename basic_istream<_CharT, _Traits>::int_type
    basic_istream<_CharT, _Traits>::
    get(void)
    {
      const int_type __eof = traits_type::eof();
      int_type __c = __eof;
      _M_gcount = 0;
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   try
     {
       __c = this->rdbuf()->sbumpc();

       if (!traits_type::eq_int_type(__c, __eof))
  _M_gcount = 1;
       else
  __err |= ios_base::eofbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
 }
      if (!_M_gcount)
 __err |= ios_base::failbit;
      if (__err)
 this->setstate(__err);
      return __c;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    get(char_type& __c)
    {
      _M_gcount = 0;
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   try
     {
       const int_type __cb = this->rdbuf()->sbumpc();

       if (!traits_type::eq_int_type(__cb, traits_type::eof()))
  {
    _M_gcount = 1;
    __c = traits_type::to_char_type(__cb);
  }
       else
  __err |= ios_base::eofbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
 }
      if (!_M_gcount)
 __err |= ios_base::failbit;
      if (__err)
 this->setstate(__err);
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    get(char_type* __s, streamsize __n, char_type __delim)
    {
      _M_gcount = 0;
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   try
     {
       const int_type __idelim = traits_type::to_int_type(__delim);
       const int_type __eof = traits_type::eof();
       __streambuf_type* __sb = this->rdbuf();
       int_type __c = __sb->sgetc();

       while (_M_gcount + 1 < __n
       && !traits_type::eq_int_type(__c, __eof)
       && !traits_type::eq_int_type(__c, __idelim))
  {
    *__s++ = traits_type::to_char_type(__c);
    ++_M_gcount;
    __c = __sb->snextc();
  }
       if (traits_type::eq_int_type(__c, __eof))
  __err |= ios_base::eofbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
 }


      if (__n > 0)
 *__s = char_type();
      if (!_M_gcount)
 __err |= ios_base::failbit;
      if (__err)
 this->setstate(__err);
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    get(__streambuf_type& __sb, char_type __delim)
    {
      _M_gcount = 0;
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   try
     {
       const int_type __idelim = traits_type::to_int_type(__delim);
       const int_type __eof = traits_type::eof();
       __streambuf_type* __this_sb = this->rdbuf();
       int_type __c = __this_sb->sgetc();
       char_type __c2 = traits_type::to_char_type(__c);

       while (!traits_type::eq_int_type(__c, __eof)
       && !traits_type::eq_int_type(__c, __idelim)
       && !traits_type::eq_int_type(__sb.sputc(__c2), __eof))
  {
    ++_M_gcount;
    __c = __this_sb->snextc();
    __c2 = traits_type::to_char_type(__c);
  }
       if (traits_type::eq_int_type(__c, __eof))
  __err |= ios_base::eofbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
 }
      if (!_M_gcount)
 __err |= ios_base::failbit;
      if (__err)
 this->setstate(__err);
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    getline(char_type* __s, streamsize __n, char_type __delim)
    {
      _M_gcount = 0;
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this, true);
      if (__cerb)
        {
          try
            {
              const int_type __idelim = traits_type::to_int_type(__delim);
              const int_type __eof = traits_type::eof();
              __streambuf_type* __sb = this->rdbuf();
              int_type __c = __sb->sgetc();

              while (_M_gcount + 1 < __n
                     && !traits_type::eq_int_type(__c, __eof)
                     && !traits_type::eq_int_type(__c, __idelim))
                {
                  *__s++ = traits_type::to_char_type(__c);
                  __c = __sb->snextc();
                  ++_M_gcount;
                }
              if (traits_type::eq_int_type(__c, __eof))
                __err |= ios_base::eofbit;
              else
                {
                  if (traits_type::eq_int_type(__c, __idelim))
                    {
                      __sb->sbumpc();
                      ++_M_gcount;
                    }
                  else
                    __err |= ios_base::failbit;
                }
            }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
          catch(...)
            { this->_M_setstate(ios_base::badbit); }
        }


      if (__n > 0)
 *__s = char_type();
      if (!_M_gcount)
        __err |= ios_base::failbit;
      if (__err)
        this->setstate(__err);
      return *this;
    }




  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    ignore(void)
    {
      _M_gcount = 0;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       const int_type __eof = traits_type::eof();
       __streambuf_type* __sb = this->rdbuf();

       if (traits_type::eq_int_type(__sb->sbumpc(), __eof))
  __err |= ios_base::eofbit;
       else
  _M_gcount = 1;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    ignore(streamsize __n)
    {
      _M_gcount = 0;
      sentry __cerb(*this, true);
      if (__cerb && __n > 0)
        {
          ios_base::iostate __err = ios_base::goodbit;
          try
            {
              const int_type __eof = traits_type::eof();
              __streambuf_type* __sb = this->rdbuf();
              int_type __c = __sb->sgetc();
# 513 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/istream.tcc" 3
       bool __large_ignore = false;
       while (true)
  {
    while (_M_gcount < __n
    && !traits_type::eq_int_type(__c, __eof))
      {
        ++_M_gcount;
        __c = __sb->snextc();
      }
    if (__n == __gnu_cxx::__numeric_traits<streamsize>::__max
        && !traits_type::eq_int_type(__c, __eof))
      {
        _M_gcount =
   __gnu_cxx::__numeric_traits<streamsize>::__min;
        __large_ignore = true;
      }
    else
      break;
  }

       if (__large_ignore)
  _M_gcount = __gnu_cxx::__numeric_traits<streamsize>::__max;

       if (traits_type::eq_int_type(__c, __eof))
                __err |= ios_base::eofbit;
            }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
          catch(...)
            { this->_M_setstate(ios_base::badbit); }
          if (__err)
            this->setstate(__err);
        }
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    ignore(streamsize __n, int_type __delim)
    {
      _M_gcount = 0;
      sentry __cerb(*this, true);
      if (__cerb && __n > 0)
        {
          ios_base::iostate __err = ios_base::goodbit;
          try
            {
              const int_type __eof = traits_type::eof();
              __streambuf_type* __sb = this->rdbuf();
              int_type __c = __sb->sgetc();


       bool __large_ignore = false;
       while (true)
  {
    while (_M_gcount < __n
    && !traits_type::eq_int_type(__c, __eof)
    && !traits_type::eq_int_type(__c, __delim))
      {
        ++_M_gcount;
        __c = __sb->snextc();
      }
    if (__n == __gnu_cxx::__numeric_traits<streamsize>::__max
        && !traits_type::eq_int_type(__c, __eof)
        && !traits_type::eq_int_type(__c, __delim))
      {
        _M_gcount =
   __gnu_cxx::__numeric_traits<streamsize>::__min;
        __large_ignore = true;
      }
    else
      break;
  }

       if (__large_ignore)
  _M_gcount = __gnu_cxx::__numeric_traits<streamsize>::__max;

              if (traits_type::eq_int_type(__c, __eof))
                __err |= ios_base::eofbit;
       else if (traits_type::eq_int_type(__c, __delim))
  {
    if (_M_gcount
        < __gnu_cxx::__numeric_traits<streamsize>::__max)
      ++_M_gcount;
    __sb->sbumpc();
  }
            }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
          catch(...)
            { this->_M_setstate(ios_base::badbit); }
          if (__err)
            this->setstate(__err);
        }
      return *this;
    }

  template<typename _CharT, typename _Traits>
    typename basic_istream<_CharT, _Traits>::int_type
    basic_istream<_CharT, _Traits>::
    peek(void)
    {
      int_type __c = traits_type::eof();
      _M_gcount = 0;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       __c = this->rdbuf()->sgetc();
       if (traits_type::eq_int_type(__c, traits_type::eof()))
  __err |= ios_base::eofbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return __c;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    read(char_type* __s, streamsize __n)
    {
      _M_gcount = 0;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       _M_gcount = this->rdbuf()->sgetn(__s, __n);
       if (_M_gcount != __n)
  __err |= (ios_base::eofbit | ios_base::failbit);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return *this;
    }

  template<typename _CharT, typename _Traits>
    streamsize
    basic_istream<_CharT, _Traits>::
    readsome(char_type* __s, streamsize __n)
    {
      _M_gcount = 0;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {

       const streamsize __num = this->rdbuf()->in_avail();
       if (__num > 0)
  _M_gcount = this->rdbuf()->sgetn(__s, std::min(__num, __n));
       else if (__num == -1)
  __err |= ios_base::eofbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return _M_gcount;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    putback(char_type __c)
    {


      _M_gcount = 0;

      this->clear(this->rdstate() & ~ios_base::eofbit);
      sentry __cerb(*this, true);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       const int_type __eof = traits_type::eof();
       __streambuf_type* __sb = this->rdbuf();
       if (!__sb
    || traits_type::eq_int_type(__sb->sputbackc(__c), __eof))
  __err |= ios_base::badbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    unget(void)
    {


      _M_gcount = 0;

      this->clear(this->rdstate() & ~ios_base::eofbit);
      sentry __cerb(*this, true);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       const int_type __eof = traits_type::eof();
       __streambuf_type* __sb = this->rdbuf();
       if (!__sb
    || traits_type::eq_int_type(__sb->sungetc(), __eof))
  __err |= ios_base::badbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return *this;
    }

  template<typename _CharT, typename _Traits>
    int
    basic_istream<_CharT, _Traits>::
    sync(void)
    {


      int __ret = -1;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       __streambuf_type* __sb = this->rdbuf();
       if (__sb)
  {
    if (__sb->pubsync() == -1)
      __err |= ios_base::badbit;
    else
      __ret = 0;
  }
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return __ret;
    }

  template<typename _CharT, typename _Traits>
    typename basic_istream<_CharT, _Traits>::pos_type
    basic_istream<_CharT, _Traits>::
    tellg(void)
    {


      pos_type __ret = pos_type(-1);
      sentry __cerb(*this, true);
      if (__cerb)
 {
   try
     {
       if (!this->fail())
  __ret = this->rdbuf()->pubseekoff(0, ios_base::cur,
        ios_base::in);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
 }
      return __ret;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    seekg(pos_type __pos)
    {



      this->clear(this->rdstate() & ~ios_base::eofbit);
      sentry __cerb(*this, true);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       if (!this->fail())
  {

    const pos_type __p = this->rdbuf()->pubseekpos(__pos,
         ios_base::in);


    if (__p == pos_type(off_type(-1)))
      __err |= ios_base::failbit;
  }
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    seekg(off_type __off, ios_base::seekdir __dir)
    {



      this->clear(this->rdstate() & ~ios_base::eofbit);
      sentry __cerb(*this, true);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       if (!this->fail())
  {

    const pos_type __p = this->rdbuf()->pubseekoff(__off, __dir,
         ios_base::in);


    if (__p == pos_type(off_type(-1)))
      __err |= ios_base::failbit;
  }
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return *this;
    }


  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __in, _CharT& __c)
    {
      typedef basic_istream<_CharT, _Traits> __istream_type;
      typedef typename __istream_type::int_type __int_type;

      typename __istream_type::sentry __cerb(__in, false);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       const __int_type __cb = __in.rdbuf()->sbumpc();
       if (!_Traits::eq_int_type(__cb, _Traits::eof()))
  __c = _Traits::to_char_type(__cb);
       else
  __err |= (ios_base::eofbit | ios_base::failbit);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       __in._M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { __in._M_setstate(ios_base::badbit); }
   if (__err)
     __in.setstate(__err);
 }
      return __in;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __in, _CharT* __s)
    {
      typedef basic_istream<_CharT, _Traits> __istream_type;
      typedef basic_streambuf<_CharT, _Traits> __streambuf_type;
      typedef typename _Traits::int_type int_type;
      typedef _CharT char_type;
      typedef ctype<_CharT> __ctype_type;

      streamsize __extracted = 0;
      ios_base::iostate __err = ios_base::goodbit;
      typename __istream_type::sentry __cerb(__in, false);
      if (__cerb)
 {
   try
     {

       streamsize __num = __in.width();
       if (__num <= 0)
  __num = __gnu_cxx::__numeric_traits<streamsize>::__max;

       const __ctype_type& __ct = use_facet<__ctype_type>(__in.getloc());

       const int_type __eof = _Traits::eof();
       __streambuf_type* __sb = __in.rdbuf();
       int_type __c = __sb->sgetc();

       while (__extracted < __num - 1
       && !_Traits::eq_int_type(__c, __eof)
       && !__ct.is(ctype_base::space,
     _Traits::to_char_type(__c)))
  {
    *__s++ = _Traits::to_char_type(__c);
    ++__extracted;
    __c = __sb->snextc();
  }
       if (_Traits::eq_int_type(__c, __eof))
  __err |= ios_base::eofbit;



       *__s = char_type();
       __in.width(0);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       __in._M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { __in._M_setstate(ios_base::badbit); }
 }
      if (!__extracted)
 __err |= ios_base::failbit;
      if (__err)
 __in.setstate(__err);
      return __in;
    }


  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    ws(basic_istream<_CharT, _Traits>& __in)
    {
      typedef basic_istream<_CharT, _Traits> __istream_type;
      typedef basic_streambuf<_CharT, _Traits> __streambuf_type;
      typedef typename __istream_type::int_type __int_type;
      typedef ctype<_CharT> __ctype_type;

      const __ctype_type& __ct = use_facet<__ctype_type>(__in.getloc());
      const __int_type __eof = _Traits::eof();
      __streambuf_type* __sb = __in.rdbuf();
      __int_type __c = __sb->sgetc();

      while (!_Traits::eq_int_type(__c, __eof)
      && __ct.is(ctype_base::space, _Traits::to_char_type(__c)))
 __c = __sb->snextc();

       if (_Traits::eq_int_type(__c, __eof))
  __in.setstate(ios_base::eofbit);
      return __in;
    }




  extern template class basic_istream<char>;
  extern template istream& ws(istream&);
  extern template istream& operator>>(istream&, char&);
  extern template istream& operator>>(istream&, char*);
  extern template istream& operator>>(istream&, unsigned char&);
  extern template istream& operator>>(istream&, signed char&);
  extern template istream& operator>>(istream&, unsigned char*);
  extern template istream& operator>>(istream&, signed char*);

  extern template istream& istream::_M_extract(unsigned short&);
  extern template istream& istream::_M_extract(unsigned int&);
  extern template istream& istream::_M_extract(long&);
  extern template istream& istream::_M_extract(unsigned long&);
  extern template istream& istream::_M_extract(bool&);

  extern template istream& istream::_M_extract(long long&);
  extern template istream& istream::_M_extract(unsigned long long&);

  extern template istream& istream::_M_extract(float&);
  extern template istream& istream::_M_extract(double&);
  extern template istream& istream::_M_extract(long double&);
  extern template istream& istream::_M_extract(void*&);

  extern template class basic_iostream<char>;


  extern template class basic_istream<wchar_t>;
  extern template wistream& ws(wistream&);
  extern template wistream& operator>>(wistream&, wchar_t&);
  extern template wistream& operator>>(wistream&, wchar_t*);

  extern template wistream& wistream::_M_extract(unsigned short&);
  extern template wistream& wistream::_M_extract(unsigned int&);
  extern template wistream& wistream::_M_extract(long&);
  extern template wistream& wistream::_M_extract(unsigned long&);
  extern template wistream& wistream::_M_extract(bool&);

  extern template wistream& wistream::_M_extract(long long&);
  extern template wistream& wistream::_M_extract(unsigned long long&);

  extern template wistream& wistream::_M_extract(float&);
  extern template wistream& wistream::_M_extract(double&);
  extern template wistream& wistream::_M_extract(long double&);
  extern template wistream& wistream::_M_extract(void*&);

  extern template class basic_iostream<wchar_t>;




}
# 935 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/istream" 2 3
# 41 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/iostream" 2 3

namespace std
{

# 60 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/iostream" 3
  extern istream cin;
  extern ostream cout;
  extern ostream cerr;
  extern ostream clog;


  extern wistream wcin;
  extern wostream wcout;
  extern wostream wcerr;
  extern wostream wclog;




  static ios_base::Init __ioinit;


}
# 5 "./util/ersatz_progress.hh" 2







# 11 "./util/ersatz_progress.hh"
namespace util {

extern const char kProgressBanner[];

class ErsatzProgress {
  public:

    ErsatzProgress();


    explicit ErsatzProgress(uint64_t complete, std::ostream *to = &std::cerr, const std::string &message = "");
# 30 "./util/ersatz_progress.hh"
    ~ErsatzProgress();

    ErsatzProgress &operator++() {
      if (++current_ >= next_) Milestone();
      return *this;
    }

    ErsatzProgress &operator+=(uint64_t amount) {
      if ((current_ += amount) >= next_) Milestone();
      return *this;
    }

    void Set(uint64_t to) {
      if ((current_ = to) >= next_) Milestone();
    }

    void Finished() {
      Set(complete_);
    }

  private:
    void Milestone();

    uint64_t current_, next_, complete_;
    unsigned char stones_written_;
    std::ostream *out_;


    ErsatzProgress(const ErsatzProgress &other);
    ErsatzProgress &operator=(const ErsatzProgress &other);
};

}
# 5 "./util/file_piece.hh" 2

# 1 "./util/file.hh" 1




# 1 "./util/scoped.hh" 1






# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstdlib" 1 3
# 39 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstdlib" 3
       
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstdlib" 3
# 8 "./util/scoped.hh" 2

namespace util {

class MallocException : public ErrnoException {
  public:
    explicit MallocException(std::size_t requested) throw();
    ~MallocException() throw();
};

void *MallocOrThrow(std::size_t requested);
void *CallocOrThrow(std::size_t requested);





template <class T, class Closer> class scoped_base {
  public:
    explicit scoped_base(T *p = 
# 26 "./util/scoped.hh" 3 4
                               __null
# 26 "./util/scoped.hh"
                                   ) : p_(p) {}

    ~scoped_base() { Closer::Close(p_); }







    void reset(T *p = 
# 36 "./util/scoped.hh" 3 4
                     __null
# 36 "./util/scoped.hh"
                         ) {
      scoped_base other(p_);
      p_ = p;
    }

    T *get() { return p_; }
    const T *get() const { return p_; }

    T *operator->() { return p_; }
    const T *operator->() const { return p_; }

    T *release() {
      T *ret = p_;
      p_ = 
# 49 "./util/scoped.hh" 3 4
          __null
# 49 "./util/scoped.hh"
              ;
      return ret;
    }

  protected:
    T *p_;






  private:
    scoped_base(const scoped_base &);
    scoped_base &operator=(const scoped_base &);

};

template <class T, class Closer> class scoped : public scoped_base<T, Closer> {
  public:
    explicit scoped(T *p = 
# 69 "./util/scoped.hh" 3 4
                          __null
# 69 "./util/scoped.hh"
                              ) : scoped_base<T, Closer>(p) {}

    T &operator*() { return *scoped_base<T, Closer>::p_; }
    const T&operator*() const { return *scoped_base<T, Closer>::p_; }
};

template <class Closer> class scoped<void, Closer> : public scoped_base<void, Closer> {
  public:
    explicit scoped(void *p = 
# 77 "./util/scoped.hh" 3 4
                             __null
# 77 "./util/scoped.hh"
                                 ) : scoped_base<void, Closer>(p) {}
};


template <class T, void (*clean)(T*)> struct scoped_c_forward {
  static void Close(T *p) { clean(p); }
};

template <class T, void (*clean)(T*)> class scoped_c : public scoped<T, scoped_c_forward<T, clean> > {
  public:
    explicit scoped_c(T *p = 
# 87 "./util/scoped.hh" 3 4
                            __null
# 87 "./util/scoped.hh"
                                ) : scoped<T, scoped_c_forward<T, clean> >(p) {}
};

class scoped_malloc : public scoped_c<void, std::free> {
  public:
    explicit scoped_malloc(void *p = 
# 92 "./util/scoped.hh" 3 4
                                    __null
# 92 "./util/scoped.hh"
                                        ) : scoped_c<void, std::free>(p) {}

    explicit scoped_malloc(std::size_t size) : scoped_c<void, std::free>(MallocOrThrow(size)) {}

    void call_realloc(std::size_t to);
};


struct scoped_delete_array_forward {
  template <class T> static void Close(T *p) { delete [] p; }
};

template <class T> class scoped_array : public scoped<T, scoped_delete_array_forward> {
  public:
    explicit scoped_array(T *p = 
# 106 "./util/scoped.hh" 3 4
                                __null
# 106 "./util/scoped.hh"
                                    ) : scoped<T, scoped_delete_array_forward>(p) {}

    T &operator[](std::size_t idx) { return scoped<T, scoped_delete_array_forward>::p_[idx]; }
    const T &operator[](std::size_t idx) const { return scoped<T, scoped_delete_array_forward>::p_[idx]; }
};


struct scoped_delete_forward {
  template <class T> static void Close(T *p) { delete p; }
};
template <class T> class scoped_ptr : public scoped<T, scoped_delete_forward> {
  public:
    explicit scoped_ptr(T *p = 
# 118 "./util/scoped.hh" 3 4
                              __null
# 118 "./util/scoped.hh"
                                  ) : scoped<T, scoped_delete_forward>(p) {}
};

void AdviseHugePages(const void *addr, std::size_t size);

}
# 6 "./util/file.hh" 2



# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstdio" 1 3
# 39 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstdio" 3
       
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstdio" 3


# 1 "/usr/include/stdio.h" 1 3 4
# 36 "/usr/include/stdio.h" 3 4
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/stddef.h" 1 3 4
# 37 "/usr/include/stdio.h" 2 3 4



# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/stdarg.h" 1 3 4
# 41 "/usr/include/stdio.h" 2 3 4
# 63 "/usr/include/stdio.h" 3 4

# 63 "/usr/include/stdio.h" 3 4
extern "C" {







typedef _fpos64_t fpos_t;







# 1 "/usr/include/sys/stdio.h" 1 3 4
# 33 "/usr/include/sys/stdio.h" 3 4
extern "C" {

ssize_t __attribute__((__cdecl__)) getline (char **, size_t *, FILE *);
ssize_t __attribute__((__cdecl__)) getdelim (char **, size_t *, int, FILE *);

}
# 80 "/usr/include/stdio.h" 2 3 4
# 181 "/usr/include/stdio.h" 3 4
char * __attribute__((__cdecl__)) ctermid (char *);




FILE * __attribute__((__cdecl__)) tmpfile (void);
char * __attribute__((__cdecl__)) tmpnam (char *);

char * __attribute__((__cdecl__)) tempnam (const char *, const char *);

int __attribute__((__cdecl__)) fclose (FILE *);
int __attribute__((__cdecl__)) fflush (FILE *);
FILE * __attribute__((__cdecl__)) freopen (const char *, const char *, FILE *);
void __attribute__((__cdecl__)) setbuf (FILE *, char *);
int __attribute__((__cdecl__)) setvbuf (FILE *, char *, int, size_t);
int __attribute__((__cdecl__)) fprintf (FILE *, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;
int __attribute__((__cdecl__)) fscanf (FILE *, const char *, ...) __attribute__ ((__format__ (__scanf__, 2, 3)))
                                                           ;
int __attribute__((__cdecl__)) printf (const char *, ...) __attribute__ ((__format__ (__printf__, 1, 2)))
                                                            ;
int __attribute__((__cdecl__)) scanf (const char *, ...) __attribute__ ((__format__ (__scanf__, 1, 2)))
                                                           ;
int __attribute__((__cdecl__)) sscanf (const char *, const char *, ...) __attribute__ ((__format__ (__scanf__, 2, 3)))
                                                           ;
int __attribute__((__cdecl__)) vfprintf (FILE *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;
int __attribute__((__cdecl__)) vprintf (const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 1, 0)))
                                                            ;
int __attribute__((__cdecl__)) vsprintf (char *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;
int __attribute__((__cdecl__)) fgetc (FILE *);
char * __attribute__((__cdecl__)) fgets (char *, int, FILE *);
int __attribute__((__cdecl__)) fputc (int, FILE *);
int __attribute__((__cdecl__)) fputs (const char *, FILE *);
int __attribute__((__cdecl__)) getc (FILE *);
int __attribute__((__cdecl__)) getchar (void);
char * __attribute__((__cdecl__)) gets (char *);
int __attribute__((__cdecl__)) putc (int, FILE *);
int __attribute__((__cdecl__)) putchar (int);
int __attribute__((__cdecl__)) puts (const char *);
int __attribute__((__cdecl__)) ungetc (int, FILE *);
size_t __attribute__((__cdecl__)) fread (void * , size_t _size, size_t _n, FILE *);
size_t __attribute__((__cdecl__)) fwrite (const void * , size_t _size, size_t _n, FILE *);



int __attribute__((__cdecl__)) fgetpos (FILE *, fpos_t *);

int __attribute__((__cdecl__)) fseek (FILE *, long, int);



int __attribute__((__cdecl__)) fsetpos (FILE *, const fpos_t *);

long __attribute__((__cdecl__)) ftell ( FILE *);
void __attribute__((__cdecl__)) rewind (FILE *);
void __attribute__((__cdecl__)) clearerr (FILE *);
int __attribute__((__cdecl__)) feof (FILE *);
int __attribute__((__cdecl__)) ferror (FILE *);
void __attribute__((__cdecl__)) perror (const char *);

FILE * __attribute__((__cdecl__)) fopen (const char * _name, const char * _type);
int __attribute__((__cdecl__)) sprintf (char *, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;
int __attribute__((__cdecl__)) remove (const char *);
int __attribute__((__cdecl__)) rename (const char *, const char *);
# 257 "/usr/include/stdio.h" 3 4
int __attribute__((__cdecl__)) fseeko (FILE *, off_t, int);
off_t __attribute__((__cdecl__)) ftello ( FILE *);







int __attribute__((__cdecl__)) snprintf (char *, size_t, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
int __attribute__((__cdecl__)) vsnprintf (char *, size_t, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int __attribute__((__cdecl__)) vfscanf (FILE *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 2, 0)))
                                                           ;
int __attribute__((__cdecl__)) vscanf (const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 1, 0)))
                                                           ;
int __attribute__((__cdecl__)) vsscanf (const char *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 2, 0)))
                                                           ;
# 284 "/usr/include/stdio.h" 3 4
int __attribute__((__cdecl__)) asiprintf (char **, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;
char * __attribute__((__cdecl__)) asniprintf (char *, size_t *, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
char * __attribute__((__cdecl__)) asnprintf (char *, size_t *, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;

int __attribute__((__cdecl__)) diprintf (int, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;

int __attribute__((__cdecl__)) fiprintf (FILE *, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;
int __attribute__((__cdecl__)) fiscanf (FILE *, const char *, ...) __attribute__ ((__format__ (__scanf__, 2, 3)))
                                                           ;
int __attribute__((__cdecl__)) iprintf (const char *, ...) __attribute__ ((__format__ (__printf__, 1, 2)))
                                                            ;
int __attribute__((__cdecl__)) iscanf (const char *, ...) __attribute__ ((__format__ (__scanf__, 1, 2)))
                                                           ;
int __attribute__((__cdecl__)) siprintf (char *, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;
int __attribute__((__cdecl__)) siscanf (const char *, const char *, ...) __attribute__ ((__format__ (__scanf__, 2, 3)))
                                                           ;
int __attribute__((__cdecl__)) sniprintf (char *, size_t, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
int __attribute__((__cdecl__)) vasiprintf (char **, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;
char * __attribute__((__cdecl__)) vasniprintf (char *, size_t *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
char * __attribute__((__cdecl__)) vasnprintf (char *, size_t *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int __attribute__((__cdecl__)) vdiprintf (int, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;
int __attribute__((__cdecl__)) vfiprintf (FILE *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;
int __attribute__((__cdecl__)) vfiscanf (FILE *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 2, 0)))
                                                           ;
int __attribute__((__cdecl__)) viprintf (const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 1, 0)))
                                                            ;
int __attribute__((__cdecl__)) viscanf (const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 1, 0)))
                                                           ;
int __attribute__((__cdecl__)) vsiprintf (char *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;
int __attribute__((__cdecl__)) vsiscanf (const char *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 2, 0)))
                                                           ;
int __attribute__((__cdecl__)) vsniprintf (char *, size_t, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
# 339 "/usr/include/stdio.h" 3 4
FILE * __attribute__((__cdecl__)) fdopen (int, const char *);

int __attribute__((__cdecl__)) fileno (FILE *);


int __attribute__((__cdecl__)) pclose (FILE *);
FILE * __attribute__((__cdecl__)) popen (const char *, const char *);



void __attribute__((__cdecl__)) setbuffer (FILE *, char *, int);
int __attribute__((__cdecl__)) setlinebuf (FILE *);



int __attribute__((__cdecl__)) getw (FILE *);
int __attribute__((__cdecl__)) putw (int, FILE *);


int __attribute__((__cdecl__)) getc_unlocked (FILE *);
int __attribute__((__cdecl__)) getchar_unlocked (void);
void __attribute__((__cdecl__)) flockfile (FILE *);
int __attribute__((__cdecl__)) ftrylockfile (FILE *);
void __attribute__((__cdecl__)) funlockfile (FILE *);
int __attribute__((__cdecl__)) putc_unlocked (int, FILE *);
int __attribute__((__cdecl__)) putchar_unlocked (int);
# 374 "/usr/include/stdio.h" 3 4
int __attribute__((__cdecl__)) dprintf (int, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;

FILE * __attribute__((__cdecl__)) fmemopen (void *, size_t, const char *);


FILE * __attribute__((__cdecl__)) open_memstream (char **, size_t *);
int __attribute__((__cdecl__)) vdprintf (int, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;



int __attribute__((__cdecl__)) renameat (int, const char *, int, const char *);






int __attribute__((__cdecl__)) _asiprintf_r (struct _reent *, char **, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
char * __attribute__((__cdecl__)) _asniprintf_r (struct _reent *, char *, size_t *, const char *, ...) __attribute__ ((__format__ (__printf__, 4, 5)))
                                                            ;
char * __attribute__((__cdecl__)) _asnprintf_r (struct _reent *, char *, size_t *, const char *, ...) __attribute__ ((__format__ (__printf__, 4, 5)))
                                                            ;
int __attribute__((__cdecl__)) _asprintf_r (struct _reent *, char **, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
int __attribute__((__cdecl__)) _diprintf_r (struct _reent *, int, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
int __attribute__((__cdecl__)) _dprintf_r (struct _reent *, int, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
int __attribute__((__cdecl__)) _fclose_r (struct _reent *, FILE *);
int __attribute__((__cdecl__)) _fcloseall_r (struct _reent *);
FILE * __attribute__((__cdecl__)) _fdopen_r (struct _reent *, int, const char *);
int __attribute__((__cdecl__)) _fflush_r (struct _reent *, FILE *);
int __attribute__((__cdecl__)) _fgetc_r (struct _reent *, FILE *);
int __attribute__((__cdecl__)) _fgetc_unlocked_r (struct _reent *, FILE *);
char * __attribute__((__cdecl__)) _fgets_r (struct _reent *, char *, int, FILE *);
char * __attribute__((__cdecl__)) _fgets_unlocked_r (struct _reent *, char *, int, FILE *);




int __attribute__((__cdecl__)) _fgetpos_r (struct _reent *, FILE *, fpos_t *);
int __attribute__((__cdecl__)) _fsetpos_r (struct _reent *, FILE *, const fpos_t *);

int __attribute__((__cdecl__)) _fiprintf_r (struct _reent *, FILE *, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
int __attribute__((__cdecl__)) _fiscanf_r (struct _reent *, FILE *, const char *, ...) __attribute__ ((__format__ (__scanf__, 3, 4)))
                                                           ;
FILE * __attribute__((__cdecl__)) _fmemopen_r (struct _reent *, void *, size_t, const char *);
FILE * __attribute__((__cdecl__)) _fopen_r (struct _reent *, const char *, const char *);
FILE * __attribute__((__cdecl__)) _freopen_r (struct _reent *, const char *, const char *, FILE *);
int __attribute__((__cdecl__)) _fprintf_r (struct _reent *, FILE *, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
int __attribute__((__cdecl__)) _fpurge_r (struct _reent *, FILE *);
int __attribute__((__cdecl__)) _fputc_r (struct _reent *, int, FILE *);
int __attribute__((__cdecl__)) _fputc_unlocked_r (struct _reent *, int, FILE *);
int __attribute__((__cdecl__)) _fputs_r (struct _reent *, const char *, FILE *);
int __attribute__((__cdecl__)) _fputs_unlocked_r (struct _reent *, const char *, FILE *);
size_t __attribute__((__cdecl__)) _fread_r (struct _reent *, void * , size_t _size, size_t _n, FILE *);
size_t __attribute__((__cdecl__)) _fread_unlocked_r (struct _reent *, void * , size_t _size, size_t _n, FILE *);
int __attribute__((__cdecl__)) _fscanf_r (struct _reent *, FILE *, const char *, ...) __attribute__ ((__format__ (__scanf__, 3, 4)))
                                                           ;
int __attribute__((__cdecl__)) _fseek_r (struct _reent *, FILE *, long, int);
int __attribute__((__cdecl__)) _fseeko_r (struct _reent *, FILE *, _off_t, int);
long __attribute__((__cdecl__)) _ftell_r (struct _reent *, FILE *);
_off_t __attribute__((__cdecl__)) _ftello_r (struct _reent *, FILE *);
void __attribute__((__cdecl__)) _rewind_r (struct _reent *, FILE *);
size_t __attribute__((__cdecl__)) _fwrite_r (struct _reent *, const void * , size_t _size, size_t _n, FILE *);
size_t __attribute__((__cdecl__)) _fwrite_unlocked_r (struct _reent *, const void * , size_t _size, size_t _n, FILE *);
int __attribute__((__cdecl__)) _getc_r (struct _reent *, FILE *);
int __attribute__((__cdecl__)) _getc_unlocked_r (struct _reent *, FILE *);
int __attribute__((__cdecl__)) _getchar_r (struct _reent *);
int __attribute__((__cdecl__)) _getchar_unlocked_r (struct _reent *);
char * __attribute__((__cdecl__)) _gets_r (struct _reent *, char *);
int __attribute__((__cdecl__)) _iprintf_r (struct _reent *, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;
int __attribute__((__cdecl__)) _iscanf_r (struct _reent *, const char *, ...) __attribute__ ((__format__ (__scanf__, 2, 3)))
                                                           ;
FILE * __attribute__((__cdecl__)) _open_memstream_r (struct _reent *, char **, size_t *);
void __attribute__((__cdecl__)) _perror_r (struct _reent *, const char *);
int __attribute__((__cdecl__)) _printf_r (struct _reent *, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;
int __attribute__((__cdecl__)) _putc_r (struct _reent *, int, FILE *);
int __attribute__((__cdecl__)) _putc_unlocked_r (struct _reent *, int, FILE *);
int __attribute__((__cdecl__)) _putchar_unlocked_r (struct _reent *, int);
int __attribute__((__cdecl__)) _putchar_r (struct _reent *, int);
int __attribute__((__cdecl__)) _puts_r (struct _reent *, const char *);
int __attribute__((__cdecl__)) _remove_r (struct _reent *, const char *);
int __attribute__((__cdecl__)) _rename_r (struct _reent *, const char *_old, const char *_new)
                                          ;
int __attribute__((__cdecl__)) _scanf_r (struct _reent *, const char *, ...) __attribute__ ((__format__ (__scanf__, 2, 3)))
                                                           ;
int __attribute__((__cdecl__)) _siprintf_r (struct _reent *, char *, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
int __attribute__((__cdecl__)) _siscanf_r (struct _reent *, const char *, const char *, ...) __attribute__ ((__format__ (__scanf__, 3, 4)))
                                                           ;
int __attribute__((__cdecl__)) _sniprintf_r (struct _reent *, char *, size_t, const char *, ...) __attribute__ ((__format__ (__printf__, 4, 5)))
                                                            ;
int __attribute__((__cdecl__)) _snprintf_r (struct _reent *, char *, size_t, const char *, ...) __attribute__ ((__format__ (__printf__, 4, 5)))
                                                            ;
int __attribute__((__cdecl__)) _sprintf_r (struct _reent *, char *, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
int __attribute__((__cdecl__)) _sscanf_r (struct _reent *, const char *, const char *, ...) __attribute__ ((__format__ (__scanf__, 3, 4)))
                                                           ;
char * __attribute__((__cdecl__)) _tempnam_r (struct _reent *, const char *, const char *);
FILE * __attribute__((__cdecl__)) _tmpfile_r (struct _reent *);
char * __attribute__((__cdecl__)) _tmpnam_r (struct _reent *, char *);
int __attribute__((__cdecl__)) _ungetc_r (struct _reent *, int, FILE *);
int __attribute__((__cdecl__)) _vasiprintf_r (struct _reent *, char **, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
char * __attribute__((__cdecl__)) _vasniprintf_r (struct _reent*, char *, size_t *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 4, 0)))
                                                            ;
char * __attribute__((__cdecl__)) _vasnprintf_r (struct _reent*, char *, size_t *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 4, 0)))
                                                            ;
int __attribute__((__cdecl__)) _vasprintf_r (struct _reent *, char **, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int __attribute__((__cdecl__)) _vdiprintf_r (struct _reent *, int, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int __attribute__((__cdecl__)) _vdprintf_r (struct _reent *, int, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int __attribute__((__cdecl__)) _vfiprintf_r (struct _reent *, FILE *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int __attribute__((__cdecl__)) _vfiscanf_r (struct _reent *, FILE *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 3, 0)))
                                                           ;
int __attribute__((__cdecl__)) _vfprintf_r (struct _reent *, FILE *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int __attribute__((__cdecl__)) _vfscanf_r (struct _reent *, FILE *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 3, 0)))
                                                           ;
int __attribute__((__cdecl__)) _viprintf_r (struct _reent *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;
int __attribute__((__cdecl__)) _viscanf_r (struct _reent *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 2, 0)))
                                                           ;
int __attribute__((__cdecl__)) _vprintf_r (struct _reent *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;
int __attribute__((__cdecl__)) _vscanf_r (struct _reent *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 2, 0)))
                                                           ;
int __attribute__((__cdecl__)) _vsiprintf_r (struct _reent *, char *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int __attribute__((__cdecl__)) _vsiscanf_r (struct _reent *, const char *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 3, 0)))
                                                           ;
int __attribute__((__cdecl__)) _vsniprintf_r (struct _reent *, char *, size_t, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 4, 0)))
                                                            ;
int __attribute__((__cdecl__)) _vsnprintf_r (struct _reent *, char *, size_t, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 4, 0)))
                                                            ;
int __attribute__((__cdecl__)) _vsprintf_r (struct _reent *, char *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int __attribute__((__cdecl__)) _vsscanf_r (struct _reent *, const char *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 3, 0)))
                                                           ;



int __attribute__((__cdecl__)) fpurge (FILE *);
ssize_t __attribute__((__cdecl__)) __getdelim (char **, size_t *, int, FILE *);
ssize_t __attribute__((__cdecl__)) __getline (char **, size_t *, FILE *);


void __attribute__((__cdecl__)) clearerr_unlocked (FILE *);
int __attribute__((__cdecl__)) feof_unlocked (FILE *);
int __attribute__((__cdecl__)) ferror_unlocked (FILE *);
int __attribute__((__cdecl__)) fileno_unlocked (FILE *);
int __attribute__((__cdecl__)) fflush_unlocked (FILE *);
int __attribute__((__cdecl__)) fgetc_unlocked (FILE *);
int __attribute__((__cdecl__)) fputc_unlocked (int, FILE *);
size_t __attribute__((__cdecl__)) fread_unlocked (void * , size_t _size, size_t _n, FILE *);
size_t __attribute__((__cdecl__)) fwrite_unlocked (const void * , size_t _size, size_t _n, FILE *);
# 574 "/usr/include/stdio.h" 3 4
int __attribute__((__cdecl__)) __srget_r (struct _reent *, FILE *);
int __attribute__((__cdecl__)) __swbuf_r (struct _reent *, int, FILE *);







FILE *__attribute__((__cdecl__)) funopen (const void * __cookie, int (*__readfn)(void * __c, char *__buf, size_t __n), int (*__writefn)(void * __c, const char *__buf, size_t __n), _fpos64_t (*__seekfn)(void * __c, _fpos64_t __off, int __whence), int (*__closefn)(void * __c))





                              ;
FILE *__attribute__((__cdecl__)) _funopen_r (struct _reent *, const void * __cookie, int (*__readfn)(void * __c, char *__buf, size_t __n), int (*__writefn)(void * __c, const char *__buf, size_t __n), _fpos64_t (*__seekfn)(void * __c, _fpos64_t __off, int __whence), int (*__closefn)(void * __c))





                              ;
# 664 "/usr/include/stdio.h" 3 4
extern __inline__ __attribute__ ((__always_inline__)) int __sgetc_r(struct _reent *__ptr, FILE *__p);

extern __inline__ __attribute__ ((__always_inline__)) int __sgetc_r(struct _reent *__ptr, FILE *__p)
  {
    int __c = (--(__p)->_r < 0 ? __srget_r(__ptr, __p) : (int)(*(__p)->_p++));
    if ((__p->_flags & 0x4000) && (__c == '\r'))
      {
      int __c2 = (--(__p)->_r < 0 ? __srget_r(__ptr, __p) : (int)(*(__p)->_p++));
      if (__c2 == '\n')
        __c = __c2;
      else
        ungetc(__c2, __p);
      }
    return __c;
  }





extern __inline__ __attribute__ ((__always_inline__)) int __sputc_r(struct _reent *_ptr, int _c, FILE *_p) {

 if ((_p->_flags & 0x4000) && _c == '\n')
   __sputc_r (_ptr, '\r', _p);

 if (--_p->_w >= 0 || (_p->_w >= _p->_lbfsize && (char)_c != '\n'))
  return (*_p->_p++ = _c);
 else
  return (__swbuf_r(_ptr, _c, _p));
}
# 767 "/usr/include/stdio.h" 3 4
}
# 43 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstdio" 2 3
# 96 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstdio" 3
namespace std
{
  using ::FILE;
  using ::fpos_t;

  using ::clearerr;
  using ::fclose;
  using ::feof;
  using ::ferror;
  using ::fflush;
  using ::fgetc;
  using ::fgetpos;
  using ::fgets;
  using ::fopen;
  using ::fprintf;
  using ::fputc;
  using ::fputs;
  using ::fread;
  using ::freopen;
  using ::fscanf;
  using ::fseek;
  using ::fsetpos;
  using ::ftell;
  using ::fwrite;
  using ::getc;
  using ::getchar;


  using ::gets;

  using ::perror;
  using ::printf;
  using ::putc;
  using ::putchar;
  using ::puts;
  using ::remove;
  using ::rename;
  using ::rewind;
  using ::scanf;
  using ::setbuf;
  using ::setvbuf;
  using ::sprintf;
  using ::sscanf;
  using ::tmpfile;

  using ::tmpnam;

  using ::ungetc;
  using ::vfprintf;
  using ::vprintf;
  using ::vsprintf;
}
# 157 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstdio" 3
namespace __gnu_cxx
{
# 175 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstdio" 3
  using ::snprintf;
  using ::vfscanf;
  using ::vscanf;
  using ::vsnprintf;
  using ::vsscanf;

}

namespace std
{
  using ::__gnu_cxx::snprintf;
  using ::__gnu_cxx::vfscanf;
  using ::__gnu_cxx::vscanf;
  using ::__gnu_cxx::vsnprintf;
  using ::__gnu_cxx::vsscanf;
}
# 10 "./util/file.hh" 2




# 13 "./util/file.hh"
namespace util {

class scoped_fd {
  public:
    scoped_fd() : fd_(-1) {}

    explicit scoped_fd(int fd) : fd_(fd) {}

    ~scoped_fd();







    void reset(int to = -1) {
      scoped_fd other(fd_);
      fd_ = to;
    }

    int get() const { return fd_; }

    int operator*() const { return fd_; }

    int release() {
      int ret = fd_;
      fd_ = -1;
      return ret;
    }

  private:
    int fd_;

    scoped_fd(const scoped_fd &);
    scoped_fd &operator=(const scoped_fd &);
};

struct scoped_FILE_closer {
  static void Close(std::FILE *file);
};
typedef scoped<std::FILE, scoped_FILE_closer> scoped_FILE;


class FDException : public ErrnoException {
  public:
    explicit FDException(int fd) throw();

    virtual ~FDException() throw();


    int FD() const { return fd_; }


    const std::string &NameGuess() const { return name_guess_; }

  private:
    int fd_;

    std::string name_guess_;
};


class EndOfFileException : public Exception {
  public:
    EndOfFileException() throw();
    ~EndOfFileException() throw();
};

class UnsupportedOSException : public Exception {};


int OpenReadOrThrow(const char *name);

int CreateOrThrow(const char *name);
# 98 "./util/file.hh"
bool InputPathIsStdin(StringPiece path);
# 109 "./util/file.hh"
bool OutputPathIsStdout(StringPiece path);


const uint64_t kBadSize = (uint64_t)-1;
uint64_t SizeFile(int fd);
uint64_t SizeOrThrow(int fd);

void ResizeOrThrow(int fd, uint64_t to);



void HolePunch(int fd, uint64_t offset, uint64_t size);

std::size_t PartialRead(int fd, void *to, std::size_t size);
void ReadOrThrow(int fd, void *to, std::size_t size);
std::size_t ReadOrEOF(int fd, void *to_void, std::size_t size);

void WriteOrThrow(int fd, const void *data_void, std::size_t size);
void WriteOrThrow(FILE *to, const void *data, std::size_t size);
# 136 "./util/file.hh"
void ErsatzPRead(int fd, void *to, std::size_t size, uint64_t off);
void ErsatzPWrite(int fd, const void *data_void, std::size_t size, uint64_t off);

void FSyncOrThrow(int fd);


uint64_t SeekOrThrow(int fd, uint64_t off);
uint64_t AdvanceOrThrow(int fd, int64_t off);
uint64_t SeekEnd(int fd);

std::FILE *FDOpenOrThrow(scoped_fd &file);
std::FILE *FDOpenReadOrThrow(scoped_fd &file);



void NormalizeTempPrefix(std::string &base);
int MakeTemp(const StringPiece &prefix);
std::FILE *FMakeTemp(const StringPiece &prefix);


std::string DefaultTempDirectory();


int DupOrThrow(int fd);





std::string NameFromFD(int fd);

}
# 7 "./util/file_piece.hh" 2

# 1 "./util/read_compressed.hh" 1
# 10 "./util/read_compressed.hh"
namespace util {

class CompressedException : public Exception {
  public:
    CompressedException() throw();
    virtual ~CompressedException() throw();
};

class GZException : public CompressedException {
  public:
    GZException() throw();
    ~GZException() throw();
};

class BZException : public CompressedException {
  public:
    BZException() throw();
    ~BZException() throw();
};

class XZException : public CompressedException {
  public:
    XZException() throw();
    ~XZException() throw();
};

class ReadCompressed;

class ReadBase {
  public:
    virtual ~ReadBase() {}

    virtual std::size_t Read(void *to, std::size_t amount, ReadCompressed &thunk) = 0;

  protected:
    static void ReplaceThis(ReadBase *with, ReadCompressed &thunk);

    ReadBase *Current(ReadCompressed &thunk);

    static uint64_t &ReadCount(ReadCompressed &thunk);
};

class ReadCompressed {
  public:
    static const std::size_t kMagicSize = 6;

    static bool DetectCompressedMagic(const void *from);


    explicit ReadCompressed(int fd);



    explicit ReadCompressed(std::istream &in);


    ReadCompressed();


    void Reset(int fd);


    void Reset(std::istream &in);

    std::size_t Read(void *to, std::size_t amount);



    std::size_t ReadOrEOF(void *const to, std::size_t amount);

    uint64_t RawAmount() const { return raw_amount_; }

  private:
    friend class ReadBase;

    scoped_ptr<ReadBase> internal_;

    uint64_t raw_amount_;
};

}
# 9 "./util/file_piece.hh" 2
# 1 "./util/spaces.hh" 1





namespace util {

extern const bool kSpaces[256];

}
# 10 "./util/file_piece.hh" 2





# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 1 3
# 41 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 3
       
# 42 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 3

# 1 "/usr/include/assert.h" 1 3 4






# 6 "/usr/include/assert.h" 3 4
extern "C" {
# 39 "/usr/include/assert.h" 3 4
void __attribute__((__cdecl__)) __assert (const char *, int, const char *) __attribute__ ((__noreturn__))
                                 ;
void __attribute__((__cdecl__)) __assert_func (const char *, int, const char *, const char *) __attribute__ ((__noreturn__))
                                 ;






}
# 43 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 2 3
# 16 "./util/file_piece.hh" 2



# 18 "./util/file_piece.hh"
namespace util {

class ParseNumberException : public Exception {
  public:
    explicit ParseNumberException(StringPiece value) throw();
    ~ParseNumberException() throw() {}
};

class FilePiece;





class LineIterator {
  public:
    LineIterator() : backing_(
# 34 "./util/file_piece.hh" 3 4
                             __null
# 34 "./util/file_piece.hh"
                                 ) {}

    explicit LineIterator(FilePiece &f, char delim = '\n') : backing_(&f), delim_(delim) {
      ++*this;
    }

    LineIterator &operator++();

    bool operator==(const LineIterator &other) const {
      return backing_ == other.backing_;
    }

    bool operator!=(const LineIterator &other) const {
      return backing_ != other.backing_;
    }

    operator bool() const { return backing_ != 
# 50 "./util/file_piece.hh" 3 4
                                              __null
# 50 "./util/file_piece.hh"
                                                  ; }

    StringPiece operator*() const { return line_; }
    const StringPiece *operator->() const { return &line_; }

  private:
    FilePiece *backing_;
    StringPiece line_;
    char delim_;
};


class FilePiece {
  public:

    explicit FilePiece(const char *file, std::ostream *show_progress = 
# 65 "./util/file_piece.hh" 3 4
                                                                      __null
# 65 "./util/file_piece.hh"
                                                                          , std::size_t min_buffer = 1048576);

    explicit FilePiece(int fd, const char *name = 
# 67 "./util/file_piece.hh" 3 4
                                                 __null
# 67 "./util/file_piece.hh"
                                                     , std::ostream *show_progress = 
# 67 "./util/file_piece.hh" 3 4
                                                                                     __null
# 67 "./util/file_piece.hh"
                                                                                         , std::size_t min_buffer = 1048576);






    explicit FilePiece(std::istream &stream, const char *name = 
# 74 "./util/file_piece.hh" 3 4
                                                               __null
# 74 "./util/file_piece.hh"
                                                                   , std::size_t min_buffer = 1048576);

    LineIterator begin() {
      return LineIterator(*this);
    }

    LineIterator end() {
      return LineIterator();
    }

    char get() {
      if (position_ == position_end_) {
        Shift();
        if (at_end_) throw EndOfFileException();
      }
      return *(position_++);
    }


    StringPiece ReadDelimited(const bool *delim = kSpaces) {
      SkipSpaces(delim);
      return Consume(FindDelimiterOrEOF(delim));
    }


    bool ReadWordSameLine(StringPiece &to, const bool *delim = kSpaces) {
      
# 100 "./util/file_piece.hh" 3 4
     ((
# 100 "./util/file_piece.hh"
     delim[static_cast<unsigned char>('\n')]
# 100 "./util/file_piece.hh" 3 4
     ) ? (void)0 : __assert_func ("./util/file_piece.hh", 100, __PRETTY_FUNCTION__, 
# 100 "./util/file_piece.hh"
     "delim[static_cast<unsigned char>('\\n')]"
# 100 "./util/file_piece.hh" 3 4
     ))
# 100 "./util/file_piece.hh"
                                                    ;

      for (; ; ++position_) {
        if (position_ == position_end_) {
          try {
            Shift();
          } catch (const util::EndOfFileException &e) { return false; }

          if (position_ == position_end_) return false;
        }
        if (!delim[static_cast<unsigned char>(*position_)]) break;
        if (*position_ == '\n') return false;
      }

      to = Consume(FindDelimiterOrEOF(delim));
      return true;
    }
# 130 "./util/file_piece.hh"
    StringPiece ReadLine(char delim = '\n', bool strip_cr = true);
# 141 "./util/file_piece.hh"
    bool ReadLineOrEOF(StringPiece &to, char delim = '\n', bool strip_cr = true);

    float ReadFloat();
    double ReadDouble();
    long int ReadLong();
    unsigned long int ReadULong();


    void SkipSpaces(const bool *delim = kSpaces) {
      
# 150 "./util/file_piece.hh" 3 4
     ((
# 150 "./util/file_piece.hh"
     position_ <= position_end_
# 150 "./util/file_piece.hh" 3 4
     ) ? (void)0 : __assert_func ("./util/file_piece.hh", 150, __PRETTY_FUNCTION__, 
# 150 "./util/file_piece.hh"
     "position_ <= position_end_"
# 150 "./util/file_piece.hh" 3 4
     ))
# 150 "./util/file_piece.hh"
                                       ;
      for (; ; ++position_) {
        if (position_ == position_end_) {
          Shift();

          if (position_ == position_end_) return;
        }
        
# 157 "./util/file_piece.hh" 3 4
       ((
# 157 "./util/file_piece.hh"
       position_ < position_end_
# 157 "./util/file_piece.hh" 3 4
       ) ? (void)0 : __assert_func ("./util/file_piece.hh", 157, __PRETTY_FUNCTION__, 
# 157 "./util/file_piece.hh"
       "position_ < position_end_"
# 157 "./util/file_piece.hh" 3 4
       ))
# 157 "./util/file_piece.hh"
                                        ;
        if (!delim[static_cast<unsigned char>(*position_)]) return;
      }
    }

    uint64_t Offset() const {
      return position_ - data_.begin() + mapped_offset_;
    }

    const std::string &FileName() const { return file_name_; }


    void UpdateProgress();

  private:
    void InitializeNoRead(const char *name, std::size_t min_buffer);

    void Initialize(const char *name, std::ostream *show_progress, std::size_t min_buffer);

    template <class T> T ReadNumber();

    StringPiece Consume(const char *to) {
      
# 179 "./util/file_piece.hh" 3 4
     ((
# 179 "./util/file_piece.hh"
     to >= position_
# 179 "./util/file_piece.hh" 3 4
     ) ? (void)0 : __assert_func ("./util/file_piece.hh", 179, __PRETTY_FUNCTION__, 
# 179 "./util/file_piece.hh"
     "to >= position_"
# 179 "./util/file_piece.hh" 3 4
     ))
# 179 "./util/file_piece.hh"
                            ;
      StringPiece ret(position_, to - position_);
      position_ = to;
      return ret;
    }

    const char *FindDelimiterOrEOF(const bool *delim = kSpaces);

    void Shift();

    void MMapShift(uint64_t desired_begin);

    void TransitionToRead();
    void ReadShift();

    const char *position_, *last_space_, *position_end_;

    scoped_fd file_;
    const uint64_t total_size_;

    std::size_t default_map_size_;
    uint64_t mapped_offset_;


    scoped_memory data_;

    bool at_end_;
    bool fallback_to_read_;

    ErsatzProgress progress_;

    std::string file_name_;

    ReadCompressed fell_back_;
};

}
# 8 "./lm/read_arpa.hh" 2





namespace lm {

void ReadARPACounts(util::FilePiece &in, std::vector<uint64_t> &number);
void ReadNGramHeader(util::FilePiece &in, unsigned int length);

void ReadBackoff(util::FilePiece &in, Prob &weights);
void ReadBackoff(util::FilePiece &in, float &backoff);
inline void ReadBackoff(util::FilePiece &in, ProbBackoff &weights) {
  ReadBackoff(in, weights.backoff);
}
inline void ReadBackoff(util::FilePiece &in, RestWeights &weights) {
  ReadBackoff(in, weights.backoff);
}

void ReadEnd(util::FilePiece &in);

extern const bool kARPASpaces[256];


class PositiveProbWarn {
  public:
    PositiveProbWarn() : action_(THROW_UP) {}

    explicit PositiveProbWarn(WarningAction action) : action_(action) {}

    void Warn(float prob);

  private:
    WarningAction action_;
};

template <class Voc, class Weights> void Read1Gram(util::FilePiece &f, Voc &vocab, Weights *unigrams, PositiveProbWarn &warn) {
  try {
    float prob = f.ReadFloat();
    if (prob > 0.0) {
      warn.Warn(prob);
      prob = 0.0;
    }
    do { if (__builtin_expect (!!(f.get() != '\t'), 0)) { do { FormatLoadException UTIL_e ; UTIL_e.SetLocation("./lm/read_arpa.hh", 51, __PRETTY_FUNCTION__, "FormatLoadException", "f.get() != '\\t'"); UTIL_e << "Expected tab after probability"; throw UTIL_e; } while (0); } } while (0);
    WordIndex word = vocab.Insert(f.ReadDelimited(kARPASpaces));
    Weights &w = unigrams[word];
    w.prob = prob;
    ReadBackoff(f, w);
  } catch(util::Exception &e) {
    e << " in the 1-gram at byte " << f.Offset();
    throw;
  }
}

template <class Voc, class Weights> void Read1Grams(util::FilePiece &f, std::size_t count, Voc &vocab, Weights *unigrams, PositiveProbWarn &warn) {
  ReadNGramHeader(f, 1);
  for (std::size_t i = 0; i < count; ++i) {
    Read1Gram(f, vocab, unigrams, warn);
  }
  vocab.FinishedLoading(unigrams);
}


template <class Voc, class Weights, class Iterator> void ReadNGram(util::FilePiece &f, const unsigned char n, const Voc &vocab, Iterator indices_out, Weights &weights, PositiveProbWarn &warn) {
  try {
    weights.prob = f.ReadFloat();
    if (weights.prob > 0.0) {
      warn.Warn(weights.prob);
      weights.prob = 0.0;
    }
    for (unsigned char i = 0; i < n; ++i, ++indices_out) {
      StringPiece word(f.ReadDelimited(kARPASpaces));
      WordIndex index = vocab.Index(word);
      *indices_out = index;

      do { if (__builtin_expect (!!(index == 0 && (word != StringPiece("<unk>", 5)) && (word != StringPiece("<UNK>", 5))), 0)) { do { FormatLoadException UTIL_e ; UTIL_e.SetLocation(
                                                                                                                                                "./lm/read_arpa.hh"
# 83 "./lm/read_arpa.hh"
      ,
                                                                                                                                                84
# 83 "./lm/read_arpa.hh"
      , __PRETTY_FUNCTION__, "FormatLoadException", "index == 0 && (word != StringPiece(\"<unk>\", 5)) && (word != StringPiece(\"<UNK>\", 5))"); UTIL_e << "Word " << word << " was not seen in the unigrams (which are supposed to list the entire vocabulary) but appears"; throw UTIL_e; } while (0); } } while (0)
                                                                                                                                                 ;
    }
    ReadBackoff(f, weights);
  } catch(util::Exception &e) {
    e << " in the " << static_cast<unsigned int>(n) << "-gram at byte " << f.Offset();
    throw;
  }
}

}
# 7 "./lm/binary_format.hh" 2
# 17 "./lm/binary_format.hh"
namespace lm {
namespace ngram {

extern const char *kModelNames[6];





bool RecognizeBinary(const char *file, ModelType &recognized);

struct FixedWidthParameters {
  unsigned char order;
  float probing_multiplier;

  ModelType model_type;

  bool has_vocabulary;
  unsigned int search_version;
};





struct Parameters {
  FixedWidthParameters fixed;
  std::vector<uint64_t> counts;
};

class BinaryFormat {
  public:
    explicit BinaryFormat(const Config &config);



    void InitializeBinary(int fd, ModelType model_type, unsigned int search_version, Parameters &params);

    void ReadForConfig(void *to, std::size_t amount, uint64_t offset_excluding_header) const;

    void *LoadBinary(std::size_t size);

    uint64_t VocabStringReadingOffset() const {
      
# 60 "./lm/binary_format.hh" 3 4
     ((
# 60 "./lm/binary_format.hh"
     vocab_string_offset_ != kInvalidOffset
# 60 "./lm/binary_format.hh" 3 4
     ) ? (void)0 : __assert_func ("./lm/binary_format.hh", 60, __PRETTY_FUNCTION__, 
# 60 "./lm/binary_format.hh"
     "vocab_string_offset_ != kInvalidOffset"
# 60 "./lm/binary_format.hh" 3 4
     ))
# 60 "./lm/binary_format.hh"
                                                   ;
      return vocab_string_offset_;
    }



    void *SetupJustVocab(std::size_t memory_size, uint8_t order);

    void *GrowForSearch(std::size_t memory_size, std::size_t vocab_pad, void *&vocab_base);

    void WriteVocabWords(const std::string &buffer, void *&vocab_base, void *&search_base);

    void FinishFile(const Config &config, ModelType model_type, unsigned int search_version, const std::vector<uint64_t> &counts);

  private:
    void MapFile(void *&vocab_base, void *&search_base);


    const Config::WriteMethod write_method_;
    const char *write_mmap_;
    util::LoadMethod load_method_;


    util::scoped_fd file_;


    util::scoped_memory mapping_;




    util::scoped_memory memory_vocab_, memory_search_;



    std::size_t header_size_, vocab_size_, vocab_pad_;

    uint64_t vocab_string_offset_;

    static const uint64_t kInvalidOffset = (uint64_t)-1;
};

bool IsBinaryFormat(int fd);

}
}
# 6 "lm/model.hh" 2

# 1 "./lm/facade.hh" 1



# 1 "./lm/virtual_interface.hh" 1



# 1 "./lm/return.hh" 1





namespace lm {

struct FullScoreReturn {

  float prob;
# 28 "./lm/return.hh"
  unsigned char ngram_length;





  bool independent_left;
  uint64_t extend_left;


  float rest;
};

}
# 5 "./lm/virtual_interface.hh" 2




# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstring" 1 3
# 39 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstring" 3
       
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstring" 3
# 10 "./lm/virtual_interface.hh" 2

namespace lm {
namespace base {

template <class T, class U, class V> class ModelFacade;
# 29 "./lm/virtual_interface.hh"
class Vocabulary {
  public:
    virtual ~Vocabulary();

    WordIndex BeginSentence() const { return begin_sentence_; }
    WordIndex EndSentence() const { return end_sentence_; }
    WordIndex NotFound() const { return not_found_; }





    virtual WordIndex Index(const StringPiece &str) const = 0;
    virtual WordIndex Index(const std::string &str) const {
      return Index(StringPiece(str));
    }
    virtual WordIndex Index(const char *str) const {
      return Index(StringPiece(str));
    }

  protected:

    Vocabulary() {}

    Vocabulary(WordIndex begin_sentence, WordIndex end_sentence, WordIndex not_found) {
      SetSpecial(begin_sentence, end_sentence, not_found);
    }

    void SetSpecial(WordIndex begin_sentence, WordIndex end_sentence, WordIndex not_found);

    WordIndex begin_sentence_, end_sentence_, not_found_;

  private:


    Vocabulary(const Vocabulary &);
    Vocabulary &operator=(const Vocabulary &);
};
# 117 "./lm/virtual_interface.hh"
class Model {
  public:
    virtual ~Model();

    size_t StateSize() const { return state_size_; }
    const void *BeginSentenceMemory() const { return begin_sentence_memory_; }
    void BeginSentenceWrite(void *to) const { memcpy(to, begin_sentence_memory_, StateSize()); }
    const void *NullContextMemory() const { return null_context_memory_; }
    void NullContextWrite(void *to) const { memcpy(to, null_context_memory_, StateSize()); }


    virtual float BaseScore(const void *in_state, const WordIndex new_word, void *out_state) const = 0;


    virtual FullScoreReturn BaseFullScore(const void *in_state, const WordIndex new_word, void *out_state) const = 0;


    virtual FullScoreReturn BaseFullScoreForgotState(const WordIndex *context_rbegin, const WordIndex *context_rend, const WordIndex new_word, void *out_state) const = 0;

    unsigned char Order() const { return order_; }

    const Vocabulary &BaseVocabulary() const { return *base_vocab_; }

  private:
    template <class T, class U, class V> friend class ModelFacade;
    explicit Model(size_t state_size) : state_size_(state_size) {}

    const size_t state_size_;
    const void *begin_sentence_memory_, *null_context_memory_;

    const Vocabulary *base_vocab_;

    unsigned char order_;



    Model(const Model &);
    Model &operator=(const Model &);
};

}
}
# 5 "./lm/facade.hh" 2




namespace lm {
namespace base {



template <class Child, class StateT, class VocabularyT> class ModelFacade : public Model {
  public:
    typedef StateT State;
    typedef VocabularyT Vocabulary;


    FullScoreReturn BaseFullScore(const void *in_state, const WordIndex new_word, void *out_state) const {
      return static_cast<const Child*>(this)->FullScore(
          *reinterpret_cast<const State*>(in_state),
          new_word,
          *reinterpret_cast<State*>(out_state));
    }

    FullScoreReturn BaseFullScoreForgotState(const WordIndex *context_rbegin, const WordIndex *context_rend, const WordIndex new_word, void *out_state) const {
      return static_cast<const Child*>(this)->FullScoreForgotState(
          context_rbegin,
          context_rend,
          new_word,
          *reinterpret_cast<State*>(out_state));
    }


    float Score(const State &in_state, const WordIndex new_word, State &out_state) const {
      return static_cast<const Child*>(this)->FullScore(in_state, new_word, out_state).prob;
    }

    float BaseScore(const void *in_state, const WordIndex new_word, void *out_state) const {
      return static_cast<const Child*>(this)->Score(
          *reinterpret_cast<const State*>(in_state),
          new_word,
          *reinterpret_cast<State*>(out_state));
    }

    const State &BeginSentenceState() const { return begin_sentence_; }
    const State &NullContextState() const { return null_context_; }
    const Vocabulary &GetVocabulary() const { return *static_cast<const Vocabulary*>(&BaseVocabulary()); }

  protected:
    ModelFacade() : Model(sizeof(State)) {}

    virtual ~ModelFacade() {}


    void Init(const State &begin_sentence, const State &null_context, const Vocabulary &vocab, unsigned char order) {
      begin_sentence_ = begin_sentence;
      null_context_ = null_context;
      begin_sentence_memory_ = &begin_sentence_;
      null_context_memory_ = &null_context_;
      base_vocab_ = &vocab;
      order_ = order;
    }

  private:
    State begin_sentence_, null_context_;
};

}
}
# 8 "lm/model.hh" 2
# 1 "./lm/quantize.hh" 1



# 1 "./lm/blank.hh" 1





# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cmath" 1 3
# 39 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cmath" 3
       
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cmath" 3




# 1 "/usr/include/math.h" 1 3 4






# 1 "/usr/include/machine/ieeefp.h" 1 3 4
# 8 "/usr/include/math.h" 2 3 4



# 10 "/usr/include/math.h" 3 4
extern "C" {




union __dmath
{
  double d;
  __ULong i[2];
};

union __fmath
{
  float f;
  __ULong i[1];
};


union __ldmath
{
  long double ld;
  __ULong i[4];
};
# 109 "/usr/include/math.h" 3 4
extern double atan (double);
extern double cos (double);
extern double sin (double);
extern double tan (double);
extern double tanh (double);
extern double frexp (double, int *);
extern double modf (double, double *);
extern double ceil (double);
extern double fabs (double);
extern double floor (double);






extern double acos (double);
extern double asin (double);
extern double atan2 (double, double);
extern double cosh (double);
extern double sinh (double);
extern double exp (double);
extern double ldexp (double, int);
extern double log (double);
extern double log10 (double);
extern double pow (double, double);
extern double sqrt (double);
extern double fmod (double, double);




extern int finite (double);
extern int finitef (float);
extern int finitel (long double);
extern int isinff (float);
extern int isnanf (float);

extern int isinfl (long double);
extern int isnanl (long double);


extern int isinf (double);




extern int isnan (double);
# 173 "/usr/include/math.h" 3 4
    typedef float float_t;
    typedef double double_t;
# 217 "/usr/include/math.h" 3 4
extern int __isinff (float x);
extern int __isinfd (double x);
extern int __isnanf (float x);
extern int __isnand (double x);
extern int __fpclassifyf (float x);
extern int __fpclassifyd (double x);
extern int __signbitf (float x);
extern int __signbitd (double x);
# 313 "/usr/include/math.h" 3 4
extern double infinity (void);
extern double nan (const char *);
extern double copysign (double, double);
extern double logb (double);
extern int ilogb (double);

extern double asinh (double);
extern double cbrt (double);
extern double nextafter (double, double);
extern double rint (double);
extern double scalbn (double, int);

extern double exp2 (double);
extern double scalbln (double, long int);
extern double tgamma (double);
extern double nearbyint (double);
extern long int lrint (double);
extern long long int llrint (double);
extern double round (double);
extern long int lround (double);
extern long long int llround (double);
extern double trunc (double);
extern double remquo (double, double, int *);
extern double fdim (double, double);
extern double fmax (double, double);
extern double fmin (double, double);
extern double fma (double, double, double);


extern double log1p (double);
extern double expm1 (double);



extern double acosh (double);
extern double atanh (double);
extern double remainder (double, double);
extern double gamma (double);
extern double lgamma (double);
extern double erf (double);
extern double erfc (double);
extern double log2 (double);





extern double hypot (double, double);






extern float atanf (float);
extern float cosf (float);
extern float sinf (float);
extern float tanf (float);
extern float tanhf (float);
extern float frexpf (float, int *);
extern float modff (float, float *);
extern float ceilf (float);
extern float fabsf (float);
extern float floorf (float);


extern float acosf (float);
extern float asinf (float);
extern float atan2f (float, float);
extern float coshf (float);
extern float sinhf (float);
extern float expf (float);
extern float ldexpf (float, int);
extern float logf (float);
extern float log10f (float);
extern float powf (float, float);
extern float sqrtf (float);
extern float fmodf (float, float);




extern float exp2f (float);
extern float scalblnf (float, long int);
extern float tgammaf (float);
extern float nearbyintf (float);
extern long int lrintf (float);
extern long long int llrintf (float);
extern float roundf (float);
extern long int lroundf (float);
extern long long int llroundf (float);
extern float truncf (float);
extern float remquof (float, float, int *);
extern float fdimf (float, float);
extern float fmaxf (float, float);
extern float fminf (float, float);
extern float fmaf (float, float, float);

extern float infinityf (void);
extern float nanf (const char *);
extern float copysignf (float, float);
extern float logbf (float);
extern int ilogbf (float);

extern float asinhf (float);
extern float cbrtf (float);
extern float nextafterf (float, float);
extern float rintf (float);
extern float scalbnf (float, int);
extern float log1pf (float);
extern float expm1f (float);


extern float acoshf (float);
extern float atanhf (float);
extern float remainderf (float, float);
extern float gammaf (float);
extern float lgammaf (float);
extern float erff (float);
extern float erfcf (float);
extern float log2f (float);
extern float hypotf (float, float);
# 445 "/usr/include/math.h" 3 4
extern long double atanl (long double);
extern long double cosl (long double);
extern long double sinl (long double);
extern long double tanl (long double);
extern long double tanhl (long double);
extern long double frexpl (long double, int *);
extern long double modfl (long double, long double *);
extern long double ceill (long double);
extern long double fabsl (long double);
extern long double floorl (long double);
extern long double log1pl (long double);
extern long double expm1l (long double);




extern long double acosl (long double);
extern long double asinl (long double);
extern long double atan2l (long double, long double);
extern long double coshl (long double);
extern long double sinhl (long double);
extern long double expl (long double);
extern long double ldexpl (long double, int);
extern long double logl (long double);
extern long double log10l (long double);
extern long double powl (long double, long double);
extern long double sqrtl (long double);
extern long double fmodl (long double, long double);
extern long double hypotl (long double, long double);


extern long double copysignl (long double, long double);
extern long double nanl (const char *);
extern int ilogbl (long double);
extern long double asinhl (long double);
extern long double cbrtl (long double);
extern long double nextafterl (long double, long double);
extern float nexttowardf (float, long double);
extern double nexttoward (double, long double);
extern long double nexttowardl (long double, long double);
extern long double logbl (long double);
extern long double log2l (long double);
extern long double rintl (long double);
extern long double scalbnl (long double, int);
extern long double exp2l (long double);
extern long double scalblnl (long double, long);
extern long double tgammal (long double);
extern long double nearbyintl (long double);
extern long int lrintl (long double);
extern long long int llrintl (long double);
extern long double roundl (long double);
extern long lroundl (long double);
extern long long int llroundl (long double);
extern long double truncl (long double);
extern long double remquol (long double, long double, int *);
extern long double fdiml (long double, long double);
extern long double fmaxl (long double, long double);
extern long double fminl (long double, long double);
extern long double fmal (long double, long double, long double);

extern long double acoshl (long double);
extern long double atanhl (long double);
extern long double remainderl (long double, long double);
extern long double lgammal (long double);
extern long double erfl (long double);
extern long double erfcl (long double);
# 526 "/usr/include/math.h" 3 4
extern double drem (double, double);
extern float dremf (float, float);

extern float dreml (long double, long double);

extern double gamma_r (double, int *);
extern double lgamma_r (double, int *);
extern float gammaf_r (float, int *);
extern float lgammaf_r (float, int *);



extern double y0 (double);
extern double y1 (double);
extern double yn (int, double);
extern double j0 (double);
extern double j1 (double);
extern double jn (int, double);



extern float y0f (float);
extern float y1f (float);
extern float ynf (int, float);
extern float j0f (float);
extern float j1f (float);
extern float jnf (int, float);
# 588 "/usr/include/math.h" 3 4
extern int *__signgam (void);
# 599 "/usr/include/math.h" 3 4
struct __exception



{
  int type;
  char *name;
  double arg1;
  double arg2;
  double retval;
  int err;
};


extern int matherr (struct __exception *e);
# 665 "/usr/include/math.h" 3 4
enum __fdlibm_version
{
  __fdlibm_ieee = -1,
  __fdlibm_svid,
  __fdlibm_xopen,
  __fdlibm_posix
};




extern __attribute__((dllimport)) enum __fdlibm_version __fdlib_version;
# 685 "/usr/include/math.h" 3 4
}
# 45 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cmath" 2 3
# 75 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cmath" 3
namespace std
{



  inline double
  abs(double __x)
  { return __builtin_fabs(__x); }



  inline float
  abs(float __x)
  { return __builtin_fabsf(__x); }

  inline long double
  abs(long double __x)
  { return __builtin_fabsl(__x); }


  template<typename _Tp>
    inline
    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                    double>::__type
    abs(_Tp __x)
    { return __builtin_fabs(__x); }

  using ::acos;


  inline float
  acos(float __x)
  { return __builtin_acosf(__x); }

  inline long double
  acos(long double __x)
  { return __builtin_acosl(__x); }


  template<typename _Tp>
    inline
    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                    double>::__type
    acos(_Tp __x)
    { return __builtin_acos(__x); }

  using ::asin;


  inline float
  asin(float __x)
  { return __builtin_asinf(__x); }

  inline long double
  asin(long double __x)
  { return __builtin_asinl(__x); }


  template<typename _Tp>
    inline
    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                    double>::__type
    asin(_Tp __x)
    { return __builtin_asin(__x); }

  using ::atan;


  inline float
  atan(float __x)
  { return __builtin_atanf(__x); }

  inline long double
  atan(long double __x)
  { return __builtin_atanl(__x); }


  template<typename _Tp>
    inline
    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                    double>::__type
    atan(_Tp __x)
    { return __builtin_atan(__x); }

  using ::atan2;


  inline float
  atan2(float __y, float __x)
  { return __builtin_atan2f(__y, __x); }

  inline long double
  atan2(long double __y, long double __x)
  { return __builtin_atan2l(__y, __x); }


  template<typename _Tp, typename _Up>
    inline
    typename __gnu_cxx::__promote_2<_Tp, _Up>::__type
    atan2(_Tp __y, _Up __x)
    {
      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
      return atan2(__type(__y), __type(__x));
    }

  using ::ceil;


  inline float
  ceil(float __x)
  { return __builtin_ceilf(__x); }

  inline long double
  ceil(long double __x)
  { return __builtin_ceill(__x); }


  template<typename _Tp>
    inline
    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                    double>::__type
    ceil(_Tp __x)
    { return __builtin_ceil(__x); }

  using ::cos;


  inline float
  cos(float __x)
  { return __builtin_cosf(__x); }

  inline long double
  cos(long double __x)
  { return __builtin_cosl(__x); }


  template<typename _Tp>
    inline
    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                    double>::__type
    cos(_Tp __x)
    { return __builtin_cos(__x); }

  using ::cosh;


  inline float
  cosh(float __x)
  { return __builtin_coshf(__x); }

  inline long double
  cosh(long double __x)
  { return __builtin_coshl(__x); }


  template<typename _Tp>
    inline
    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                    double>::__type
    cosh(_Tp __x)
    { return __builtin_cosh(__x); }

  using ::exp;


  inline float
  exp(float __x)
  { return __builtin_expf(__x); }

  inline long double
  exp(long double __x)
  { return __builtin_expl(__x); }


  template<typename _Tp>
    inline
    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                    double>::__type
    exp(_Tp __x)
    { return __builtin_exp(__x); }

  using ::fabs;


  inline float
  fabs(float __x)
  { return __builtin_fabsf(__x); }

  inline long double
  fabs(long double __x)
  { return __builtin_fabsl(__x); }


  template<typename _Tp>
    inline
    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                    double>::__type
    fabs(_Tp __x)
    { return __builtin_fabs(__x); }

  using ::floor;


  inline float
  floor(float __x)
  { return __builtin_floorf(__x); }

  inline long double
  floor(long double __x)
  { return __builtin_floorl(__x); }


  template<typename _Tp>
    inline
    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                    double>::__type
    floor(_Tp __x)
    { return __builtin_floor(__x); }

  using ::fmod;


  inline float
  fmod(float __x, float __y)
  { return __builtin_fmodf(__x, __y); }

  inline long double
  fmod(long double __x, long double __y)
  { return __builtin_fmodl(__x, __y); }


  template<typename _Tp, typename _Up>
    inline
    typename __gnu_cxx::__promote_2<_Tp, _Up>::__type
    fmod(_Tp __x, _Up __y)
    {
      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
      return fmod(__type(__x), __type(__y));
    }

  using ::frexp;


  inline float
  frexp(float __x, int* __exp)
  { return __builtin_frexpf(__x, __exp); }

  inline long double
  frexp(long double __x, int* __exp)
  { return __builtin_frexpl(__x, __exp); }


  template<typename _Tp>
    inline
    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                    double>::__type
    frexp(_Tp __x, int* __exp)
    { return __builtin_frexp(__x, __exp); }

  using ::ldexp;


  inline float
  ldexp(float __x, int __exp)
  { return __builtin_ldexpf(__x, __exp); }

  inline long double
  ldexp(long double __x, int __exp)
  { return __builtin_ldexpl(__x, __exp); }


  template<typename _Tp>
    inline
    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                    double>::__type
    ldexp(_Tp __x, int __exp)
    { return __builtin_ldexp(__x, __exp); }

  using ::log;


  inline float
  log(float __x)
  { return __builtin_logf(__x); }

  inline long double
  log(long double __x)
  { return __builtin_logl(__x); }


  template<typename _Tp>
    inline
    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                    double>::__type
    log(_Tp __x)
    { return __builtin_log(__x); }

  using ::log10;


  inline float
  log10(float __x)
  { return __builtin_log10f(__x); }

  inline long double
  log10(long double __x)
  { return __builtin_log10l(__x); }


  template<typename _Tp>
    inline
    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                    double>::__type
    log10(_Tp __x)
    { return __builtin_log10(__x); }

  using ::modf;


  inline float
  modf(float __x, float* __iptr)
  { return __builtin_modff(__x, __iptr); }

  inline long double
  modf(long double __x, long double* __iptr)
  { return __builtin_modfl(__x, __iptr); }


  using ::pow;


  inline float
  pow(float __x, float __y)
  { return __builtin_powf(__x, __y); }

  inline long double
  pow(long double __x, long double __y)
  { return __builtin_powl(__x, __y); }




  inline double
  pow(double __x, int __i)
  { return __builtin_powi(__x, __i); }

  inline float
  pow(float __x, int __n)
  { return __builtin_powif(__x, __n); }

  inline long double
  pow(long double __x, int __n)
  { return __builtin_powil(__x, __n); }



  template<typename _Tp, typename _Up>
    inline
    typename __gnu_cxx::__promote_2<_Tp, _Up>::__type
    pow(_Tp __x, _Up __y)
    {
      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
      return pow(__type(__x), __type(__y));
    }

  using ::sin;


  inline float
  sin(float __x)
  { return __builtin_sinf(__x); }

  inline long double
  sin(long double __x)
  { return __builtin_sinl(__x); }


  template<typename _Tp>
    inline
    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                    double>::__type
    sin(_Tp __x)
    { return __builtin_sin(__x); }

  using ::sinh;


  inline float
  sinh(float __x)
  { return __builtin_sinhf(__x); }

  inline long double
  sinh(long double __x)
  { return __builtin_sinhl(__x); }


  template<typename _Tp>
    inline
    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                    double>::__type
    sinh(_Tp __x)
    { return __builtin_sinh(__x); }

  using ::sqrt;


  inline float
  sqrt(float __x)
  { return __builtin_sqrtf(__x); }

  inline long double
  sqrt(long double __x)
  { return __builtin_sqrtl(__x); }


  template<typename _Tp>
    inline
    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                    double>::__type
    sqrt(_Tp __x)
    { return __builtin_sqrt(__x); }

  using ::tan;


  inline float
  tan(float __x)
  { return __builtin_tanf(__x); }

  inline long double
  tan(long double __x)
  { return __builtin_tanl(__x); }


  template<typename _Tp>
    inline
    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                    double>::__type
    tan(_Tp __x)
    { return __builtin_tan(__x); }

  using ::tanh;


  inline float
  tanh(float __x)
  { return __builtin_tanhf(__x); }

  inline long double
  tanh(long double __x)
  { return __builtin_tanhl(__x); }


  template<typename _Tp>
    inline
    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                    double>::__type
    tanh(_Tp __x)
    { return __builtin_tanh(__x); }


}
# 555 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cmath" 3
namespace std
{

# 831 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cmath" 3
  template<typename _Tp>
    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
        int>::__type
    fpclassify(_Tp __f)
    {
      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
      return __builtin_fpclassify(0, 1, 4,
      3, 2, __type(__f));
    }

  template<typename _Tp>
    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
        int>::__type
    isfinite(_Tp __f)
    {
      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
      return __builtin_isfinite(__type(__f));
    }

  template<typename _Tp>
    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
        int>::__type
    isinf(_Tp __f)
    {
      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
      return __builtin_isinf(__type(__f));
    }

  template<typename _Tp>
    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
        int>::__type
    isnan(_Tp __f)
    {
      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
      return __builtin_isnan(__type(__f));
    }

  template<typename _Tp>
    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
        int>::__type
    isnormal(_Tp __f)
    {
      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
      return __builtin_isnormal(__type(__f));
    }

  template<typename _Tp>
    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
        int>::__type
    signbit(_Tp __f)
    {
      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
      return sizeof(__type) == sizeof(float)
 ? __builtin_signbitf(__type(__f))
 : sizeof(__type) == sizeof(double)
 ? __builtin_signbit(__type(__f))
 : __builtin_signbitl(__type(__f));
    }

  template<typename _Tp>
    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
        int>::__type
    isgreater(_Tp __f1, _Tp __f2)
    {
      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
      return __builtin_isgreater(__type(__f1), __type(__f2));
    }

  template<typename _Tp>
    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
        int>::__type
    isgreaterequal(_Tp __f1, _Tp __f2)
    {
      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
      return __builtin_isgreaterequal(__type(__f1), __type(__f2));
    }

  template<typename _Tp>
    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
        int>::__type
    isless(_Tp __f1, _Tp __f2)
    {
      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
      return __builtin_isless(__type(__f1), __type(__f2));
    }

  template<typename _Tp>
    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
        int>::__type
    islessequal(_Tp __f1, _Tp __f2)
    {
      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
      return __builtin_islessequal(__type(__f1), __type(__f2));
    }

  template<typename _Tp>
    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
        int>::__type
    islessgreater(_Tp __f1, _Tp __f2)
    {
      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
      return __builtin_islessgreater(__type(__f1), __type(__f2));
    }

  template<typename _Tp>
    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
        int>::__type
    isunordered(_Tp __f1, _Tp __f2)
    {
      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
      return __builtin_isunordered(__type(__f1), __type(__f2));
    }




}
# 7 "./lm/blank.hh" 2


# 8 "./lm/blank.hh"
namespace lm {
namespace ngram {
# 22 "./lm/blank.hh"
const float kNoExtensionBackoff = -0.0;
const float kExtensionBackoff = 0.0;
const uint64_t kNoExtensionQuant = 0;
const uint64_t kExtensionQuant = 1;

inline void SetExtension(float &backoff) {
  if (backoff == kNoExtensionBackoff) backoff = kExtensionBackoff;
}


inline bool HasExtension(const float &backoff) {
  typedef union { float f; uint32_t i; } UnionValue;
  UnionValue compare, interpret;
  compare.f = kNoExtensionBackoff;
  interpret.f = backoff;
  return compare.i != interpret.i;
}

}
}
# 5 "./lm/quantize.hh" 2

# 1 "./lm/max_order.hh" 1
# 7 "./lm/quantize.hh" 2
# 17 "./lm/quantize.hh"
namespace lm {
namespace ngram {

struct Config;
class BinaryFormat;


class DontQuantize {
  public:
    static const ModelType kModelTypeAdd = static_cast<ModelType>(0);
    static void UpdateConfigFromBinary(const BinaryFormat &, uint64_t, Config &) {}
    static uint64_t Size(uint8_t , const Config & ) { return 0; }
    static uint8_t MiddleBits(const Config & ) { return 63; }
    static uint8_t LongestBits(const Config & ) { return 31; }

    class MiddlePointer {
      public:
        MiddlePointer(const DontQuantize & , unsigned char , util::BitAddress address) : address_(address) {}

        MiddlePointer() : address_(
# 36 "./lm/quantize.hh" 3 4
                                  __null
# 36 "./lm/quantize.hh"
                                      , 0) {}

        bool Found() const {
          return address_.base != 
# 39 "./lm/quantize.hh" 3 4
                                 __null
# 39 "./lm/quantize.hh"
                                     ;
        }

        float Prob() const {
          return util::ReadNonPositiveFloat31(address_.base, address_.offset);
        }

        float Backoff() const {
          return util::ReadFloat32(address_.base, address_.offset + 31);
        }

        float Rest() const { return Prob(); }

        void Write(float prob, float backoff) {
          util::WriteNonPositiveFloat31(address_.base, address_.offset, prob);
          util::WriteFloat32(address_.base, address_.offset + 31, backoff);
        }

      private:
        util::BitAddress address_;
    };

    class LongestPointer {
      public:
        explicit LongestPointer(const DontQuantize & , util::BitAddress address) : address_(address) {}

        LongestPointer() : address_(
# 65 "./lm/quantize.hh" 3 4
                                   __null
# 65 "./lm/quantize.hh"
                                       , 0) {}

        bool Found() const {
          return address_.base != 
# 68 "./lm/quantize.hh" 3 4
                                 __null
# 68 "./lm/quantize.hh"
                                     ;
        }

        float Prob() const {
          return util::ReadNonPositiveFloat31(address_.base, address_.offset);
        }

        void Write(float prob) {
          util::WriteNonPositiveFloat31(address_.base, address_.offset, prob);
        }

      private:
        util::BitAddress address_;
    };

    DontQuantize() {}

    void SetupMemory(void * , unsigned char , const Config & ) {}

    static const bool kTrain = false;

    void Train(uint8_t , std::vector<float> & , std::vector<float> & ) {}
    void TrainProb(uint8_t, std::vector<float> & ) {}

    void FinishedLoading(const Config &) {}
};

class SeparatelyQuantize {
  private:
    class Bins {
      public:

        Bins() {}

        Bins(uint8_t bits, float *begin) : begin_(begin), end_(begin_ + (1ULL << bits)), bits_(bits), mask_((1ULL << bits) - 1) {}

        float *Populate() { return begin_; }

        uint64_t EncodeProb(float value) const {
          return Encode(value, 0);
        }

        uint64_t EncodeBackoff(float value) const {
          if (value == 0.0) {
            return HasExtension(value) ? kExtensionQuant : kNoExtensionQuant;
          }
          return Encode(value, 2);
        }

        float Decode(std::size_t off) const { return begin_[off]; }

        uint8_t Bits() const { return bits_; }

        uint64_t Mask() const { return mask_; }

      private:
        uint64_t Encode(float value, size_t reserved) const {
          const float *above = std::lower_bound(static_cast<const float*>(begin_) + reserved, end_, value);
          if (above == begin_ + reserved) return reserved;
          if (above == end_) return end_ - begin_ - 1;
          return above - begin_ - (value - *(above - 1) < *above - value);
        }

        float *begin_;
        const float *end_;
        uint8_t bits_;
        uint64_t mask_;
    };

  public:
    static const ModelType kModelTypeAdd = kQuantAdd;

    static void UpdateConfigFromBinary(const BinaryFormat &file, uint64_t offset, Config &config);

    static uint64_t Size(uint8_t order, const Config &config) {
      uint64_t longest_table = (static_cast<uint64_t>(1) << static_cast<uint64_t>(config.prob_bits)) * sizeof(float);
      uint64_t middle_table = (static_cast<uint64_t>(1) << static_cast<uint64_t>(config.backoff_bits)) * sizeof(float) + longest_table;

      return (order - 2) * middle_table + longest_table + 8;
    }

    static uint8_t MiddleBits(const Config &config) { return config.prob_bits + config.backoff_bits; }
    static uint8_t LongestBits(const Config &config) { return config.prob_bits; }

    class MiddlePointer {
      public:
        MiddlePointer(const SeparatelyQuantize &quant, unsigned char order_minus_2, const util::BitAddress &address) : bins_(quant.GetTables(order_minus_2)), address_(address) {}

        MiddlePointer() : address_(
# 156 "./lm/quantize.hh" 3 4
                                  __null
# 156 "./lm/quantize.hh"
                                      , 0) {}

        bool Found() const { return address_.base != 
# 158 "./lm/quantize.hh" 3 4
                                                    __null
# 158 "./lm/quantize.hh"
                                                        ; }

        float Prob() const {
          return ProbBins().Decode(util::ReadInt25(address_.base, address_.offset + BackoffBins().Bits(), ProbBins().Bits(), ProbBins().Mask()));
        }

        float Backoff() const {
          return BackoffBins().Decode(util::ReadInt25(address_.base, address_.offset, BackoffBins().Bits(), BackoffBins().Mask()));
        }

        float Rest() const { return Prob(); }

        void Write(float prob, float backoff) const {
          util::WriteInt57(address_.base, address_.offset, ProbBins().Bits() + BackoffBins().Bits(),
              (ProbBins().EncodeProb(prob) << BackoffBins().Bits()) | BackoffBins().EncodeBackoff(backoff));
        }

      private:
        const Bins &ProbBins() const { return bins_[0]; }
        const Bins &BackoffBins() const { return bins_[1]; }
        const Bins *bins_;

        util::BitAddress address_;
    };

    class LongestPointer {
      public:
        LongestPointer(const SeparatelyQuantize &quant, const util::BitAddress &address) : table_(&quant.LongestTable()), address_(address) {}

        LongestPointer() : address_(
# 187 "./lm/quantize.hh" 3 4
                                   __null
# 187 "./lm/quantize.hh"
                                       , 0) {}

        bool Found() const { return address_.base != 
# 189 "./lm/quantize.hh" 3 4
                                                    __null
# 189 "./lm/quantize.hh"
                                                        ; }

        void Write(float prob) const {
          util::WriteInt25(address_.base, address_.offset, table_->Bits(), table_->EncodeProb(prob));
        }

        float Prob() const {
          return table_->Decode(util::ReadInt25(address_.base, address_.offset, table_->Bits(), table_->Mask()));
        }

      private:
        const Bins *table_;
        util::BitAddress address_;
    };

    SeparatelyQuantize() {}

    void SetupMemory(void *start, unsigned char order, const Config &config);

    static const bool kTrain = true;

    void Train(uint8_t order, std::vector<float> &prob, std::vector<float> &backoff);

    void TrainProb(uint8_t order, std::vector<float> &prob);

    void FinishedLoading(const Config &config);

    const Bins *GetTables(unsigned char order_minus_2) const { return tables_[order_minus_2]; }

    const Bins &LongestTable() const { return longest_; }

  private:
    Bins tables_[KENLM_MAX_ORDER - 1][2];

    Bins longest_;

    uint8_t *actual_base_;

    uint8_t prob_bits_, backoff_bits_;
};

}
}
# 9 "lm/model.hh" 2
# 1 "./lm/search_hashed.hh" 1
# 11 "./lm/search_hashed.hh"
# 1 "./util/probing_hash_table.hh" 1
# 9 "./util/probing_hash_table.hh"
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/functional" 1 3
# 46 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/functional" 3
       
# 47 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/functional" 3
# 10 "./util/probing_hash_table.hh" 2


# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 1 3
# 41 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 3
       
# 42 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 3

# 1 "/usr/include/assert.h" 1 3 4






# 6 "/usr/include/assert.h" 3 4
extern "C" {
# 39 "/usr/include/assert.h" 3 4
void __attribute__((__cdecl__)) __assert (const char *, int, const char *) __attribute__ ((__noreturn__))
                                 ;
void __attribute__((__cdecl__)) __assert_func (const char *, int, const char *, const char *) __attribute__ ((__noreturn__))
                                 ;






}
# 43 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 2 3
# 13 "./util/probing_hash_table.hh" 2



# 15 "./util/probing_hash_table.hh"
namespace util {


class ProbingSizeException : public Exception {
  public:
    ProbingSizeException() throw() {}
    ~ProbingSizeException() throw() {}
};


struct IdentityHash {
  template <class T> T operator()(T arg) const { return arg; }
};

class DivMod {
  public:
    explicit DivMod(std::size_t buckets) : buckets_(buckets) {}

    static std::size_t RoundBuckets(std::size_t from) {
      return from;
    }

    template <class It> It Ideal(It begin, uint64_t hash) const {
      return begin + (hash % buckets_);
    }

    template <class BaseIt, class OutIt> void Next(BaseIt begin, BaseIt end, OutIt &it) const {
      if (++it == end) it = begin;
    }

    void Double() {
      buckets_ *= 2;
    }

  private:
    std::size_t buckets_;
};

class Power2Mod {
  public:
    explicit Power2Mod(std::size_t buckets) {
      do { if (__builtin_expect (!!(!buckets || (((buckets - 1) & buckets))), 0)) { do { ProbingSizeException UTIL_e ; UTIL_e.SetLocation("./util/probing_hash_table.hh", 56, __PRETTY_FUNCTION__, "ProbingSizeException", "!buckets || (((buckets - 1) & buckets))"); UTIL_e << "Size " << buckets << " is not a power of 2."; throw UTIL_e; } while (0); } } while (0);
      mask_ = buckets - 1;
    }


    static std::size_t RoundBuckets(std::size_t from) {
      --from;
      from |= from >> 1;
      from |= from >> 2;
      from |= from >> 4;
      from |= from >> 8;
      from |= from >> 16;
      from |= from >> 32;
      return from + 1;
    }

    template <class It> It Ideal(It begin, uint64_t hash) const {
      return begin + (hash & mask_);
    }

    template <class BaseIt, class OutIt> void Next(BaseIt begin, BaseIt , OutIt &it) const {
      it = begin + ((it - begin + 1) & mask_);
    }

    void Double() {
      mask_ = (mask_ << 1) | 1;
    }

  private:
    std::size_t mask_;
};

template <class EntryT, class HashT, class EqualT> class AutoProbing;
# 98 "./util/probing_hash_table.hh"
template <class EntryT, class HashT, class EqualT = std::equal_to<typename EntryT::Key>, class ModT = DivMod> class ProbingHashTable {
  public:
    typedef EntryT Entry;
    typedef typename Entry::Key Key;
    typedef const Entry *ConstIterator;
    typedef Entry *MutableIterator;
    typedef HashT Hash;
    typedef EqualT Equal;
    typedef ModT Mod;

    static uint64_t Size(uint64_t entries, float multiplier) {
      uint64_t buckets = Mod::RoundBuckets(std::max(entries + 1, static_cast<uint64_t>(multiplier * static_cast<float>(entries))));
      return buckets * sizeof(Entry);
    }


    ProbingHashTable() : mod_(1), entries_(0)



    {}

    ProbingHashTable(void *start, std::size_t allocated, const Key &invalid = Key(), const Hash &hash_func = Hash(), const Equal &equal_func = Equal())
      : begin_(reinterpret_cast<MutableIterator>(start)),
        end_(begin_ + allocated / sizeof(Entry)),
        buckets_(end_ - begin_),
        invalid_(invalid),
        hash_(hash_func),
        equal_(equal_func),
        mod_(end_ - begin_),
        entries_(0)



    {}

    void Relocate(void *new_base) {
      begin_ = reinterpret_cast<MutableIterator>(new_base);
      end_ = begin_ + buckets_;
    }

    MutableIterator Ideal(const Key key) {
      return mod_.Ideal(begin_, hash_(key));
    }
    ConstIterator Ideal(const Key key) const {
      return mod_.Ideal(begin_, hash_(key));
    }

    template <class T> MutableIterator Insert(const T &t) {



      do { if (__builtin_expect (!!(++entries_ >= buckets_), 0)) { do { ProbingSizeException UTIL_e ; UTIL_e.SetLocation("./util/probing_hash_table.hh", 150, __PRETTY_FUNCTION__, "ProbingSizeException", "++entries_ >= buckets_"); UTIL_e << "Hash table with " << buckets_ << " buckets is full."; throw UTIL_e; } while (0); } } while (0);
      return UncheckedInsert(t);
    }


    template <class T> bool FindOrInsert(const T &t, MutableIterator &out) {



      for (MutableIterator i = Ideal(t.GetKey());;mod_.Next(begin_, end_, i)) {
        Key got(i->GetKey());
        if (equal_(got, t.GetKey())) { out = i; return true; }
        if (equal_(got, invalid_)) {
          do { if (__builtin_expect (!!(++entries_ >= buckets_), 0)) { do { ProbingSizeException UTIL_e ; UTIL_e.SetLocation("./util/probing_hash_table.hh", 163, __PRETTY_FUNCTION__, "ProbingSizeException", "++entries_ >= buckets_"); UTIL_e << "Hash table with " << buckets_ << " buckets is full."; throw UTIL_e; } while (0); } } while (0);
          *i = t;
          out = i;
          return false;
        }
      }
    }

    void FinishedInserting() {}


    template <class Key> bool UnsafeMutableFind(const Key key, MutableIterator &out) {



      for (MutableIterator i(Ideal(key));; mod_.Next(begin_, end_, i)) {
        Key got(i->GetKey());
        if (equal_(got, key)) { out = i; return true; }
        if (equal_(got, invalid_)) return false;
      }
    }


    template <class Key> MutableIterator UnsafeMutableMustFind(const Key key) {
      for (MutableIterator i(Ideal(key));; mod_.Next(begin_, end_, i)) {
        Key got(i->GetKey());
        if (equal_(got, key)) { return i; }
        
# 190 "./util/probing_hash_table.hh" 3 4
       ((
# 190 "./util/probing_hash_table.hh"
       !equal_(got, invalid_)
# 190 "./util/probing_hash_table.hh" 3 4
       ) ? (void)0 : __assert_func ("./util/probing_hash_table.hh", 190, __PRETTY_FUNCTION__, 
# 190 "./util/probing_hash_table.hh"
       "!equal_(got, invalid_)"
# 190 "./util/probing_hash_table.hh" 3 4
       ))
# 190 "./util/probing_hash_table.hh"
                                     ;
      }
    }


    template <class Key> bool FindFromIdeal(const Key key, ConstIterator &i) const {



      for (;; mod_.Next(begin_, end_, i)) {
        Key got(i->GetKey());
        if (equal_(got, key)) return true;
        if (equal_(got, invalid_)) return false;
      }
    }

    template <class Key> bool Find(const Key key, ConstIterator &out) const {
      out = Ideal(key);
      return FindFromIdeal(key, out);
    }


    template <class Key> ConstIterator MustFind(const Key key) const {
      for (ConstIterator i(Ideal(key));; mod_.Next(begin_, end_, i)) {
        Key got(i->GetKey());
        if (equal_(got, key)) { return i; }
        
# 216 "./util/probing_hash_table.hh" 3 4
       ((
# 216 "./util/probing_hash_table.hh"
       !equal_(got, invalid_)
# 216 "./util/probing_hash_table.hh" 3 4
       ) ? (void)0 : __assert_func ("./util/probing_hash_table.hh", 216, __PRETTY_FUNCTION__, 
# 216 "./util/probing_hash_table.hh"
       "!equal_(got, invalid_)"
# 216 "./util/probing_hash_table.hh" 3 4
       ))
# 216 "./util/probing_hash_table.hh"
                                     ;
      }
    }

    void Clear() {
      Entry invalid;
      invalid.SetKey(invalid_);
      std::fill(begin_, end_, invalid);
      entries_ = 0;
    }


    std::size_t SizeNoSerialization() const {
      return entries_;
    }


    std::size_t DoubleTo() const {
      return buckets_ * 2 * sizeof(Entry);
    }




    void Double(void *new_base, bool clear_new = true) {
      begin_ = static_cast<MutableIterator>(new_base);
      MutableIterator old_end = begin_ + buckets_;
      buckets_ *= 2;
      end_ = begin_ + buckets_;
      mod_.Double();
      if (clear_new) {
        Entry invalid;
        invalid.SetKey(invalid_);
        std::fill(old_end, end_, invalid);
      }
      std::vector<Entry> rolled_over;

      for (MutableIterator i = begin_; i != old_end && !equal_(i->GetKey(), invalid_); ++i) {
        rolled_over.push_back(*i);
        i->SetKey(invalid_);
      }






      Entry temp;
      for (MutableIterator i = begin_; i != old_end; ++i) {
        if (!equal_(i->GetKey(), invalid_)) {
          temp = *i;
          i->SetKey(invalid_);
          UncheckedInsert(temp);
        }
      }

      for (typename std::vector<Entry>::const_iterator i(rolled_over.begin()); i != rolled_over.end(); ++i) {
        UncheckedInsert(*i);
      }
    }


    void CheckConsistency() {
      MutableIterator last;
      for (last = end_ - 1; last >= begin_ && !equal_(last->GetKey(), invalid_); --last) {}
      do { if (__builtin_expect (!!(last == begin_), 0)) { do { ProbingSizeException UTIL_e ; UTIL_e.SetLocation("./util/probing_hash_table.hh", 281, __PRETTY_FUNCTION__, "ProbingSizeException", "last == begin_"); UTIL_e << "Completely full"; throw UTIL_e; } while (0); } } while (0);
      MutableIterator i;

      for (i = begin_; !equal_(i->GetKey(), invalid_); ++i) {
        MutableIterator ideal = Ideal(i->GetKey());
        do { if (__builtin_expect (!!(ideal > i && ideal <= last), 0)) { do { Exception UTIL_e ; UTIL_e.SetLocation("./util/probing_hash_table.hh", 286, __PRETTY_FUNCTION__, "Exception", "ideal > i && ideal <= last"); UTIL_e << "Inconsistency at position " << (i - begin_) << " should be at " << (ideal - begin_); throw UTIL_e; } while (0); } } while (0);
      }
      MutableIterator pre_gap = i;
      for (; i != end_; ++i) {
        if (equal_(i->GetKey(), invalid_)) {
          pre_gap = i;
          continue;
        }
        MutableIterator ideal = Ideal(i->GetKey());
        do { if (__builtin_expect (!!(ideal > i || ideal <= pre_gap), 0)) { do { Exception UTIL_e ; UTIL_e.SetLocation("./util/probing_hash_table.hh", 295, __PRETTY_FUNCTION__, "Exception", "ideal > i || ideal <= pre_gap"); UTIL_e << "Inconsistency at position " << (i - begin_) << " with ideal " << (ideal - begin_); throw UTIL_e; } while (0); } } while (0);
      }
    }

    ConstIterator RawBegin() const {
      return begin_;
    }
    ConstIterator RawEnd() const {
      return end_;
    }

  private:
    friend class AutoProbing<Entry, Hash, Equal>;

    template <class T> MutableIterator UncheckedInsert(const T &t) {
      for (MutableIterator i(Ideal(t.GetKey()));; mod_.Next(begin_, end_, i)) {
        if (equal_(i->GetKey(), invalid_)) { *i = t; return i; }
      }
    }

    MutableIterator begin_;
    MutableIterator end_;
    std::size_t buckets_;
    Key invalid_;
    Hash hash_;
    Equal equal_;
    Mod mod_;

    std::size_t entries_;



};


template <class EntryT, class HashT, class EqualT = std::equal_to<typename EntryT::Key> > class AutoProbing {
  private:
    typedef ProbingHashTable<EntryT, HashT, EqualT, Power2Mod> Backend;
  public:
    static std::size_t MemUsage(std::size_t size, float multiplier = 1.5) {
      return Backend::Size(size, multiplier);
    }

    typedef EntryT Entry;
    typedef typename Entry::Key Key;
    typedef const Entry *ConstIterator;
    typedef Entry *MutableIterator;
    typedef HashT Hash;
    typedef EqualT Equal;

    AutoProbing(std::size_t initial_size = 5, const Key &invalid = Key(), const Hash &hash_func = Hash(), const Equal &equal_func = Equal()) :
      allocated_(Backend::Size(initial_size, 1.2)), mem_(allocated_, KeyIsRawZero(invalid)), backend_(mem_.get(), allocated_, invalid, hash_func, equal_func) {
      threshold_ = std::min<std::size_t>(backend_.buckets_ - 1, backend_.buckets_ * 0.9);
      if (!KeyIsRawZero(invalid)) {
        Clear();
      }
    }


    template <class T> MutableIterator Insert(const T &t) {
      ++backend_.entries_;
      DoubleIfNeeded();
      return backend_.UncheckedInsert(t);
    }

    template <class T> bool FindOrInsert(const T &t, MutableIterator &out) {
      DoubleIfNeeded();
      return backend_.FindOrInsert(t, out);
    }

    template <class Key> bool UnsafeMutableFind(const Key key, MutableIterator &out) {
      return backend_.UnsafeMutableFind(key, out);
    }

    template <class Key> MutableIterator UnsafeMutableMustFind(const Key key) {
      return backend_.UnsafeMutableMustFind(key);
    }

    template <class Key> bool Find(const Key key, ConstIterator &out) const {
      return backend_.Find(key, out);
    }

    template <class Key> ConstIterator MustFind(const Key key) const {
      return backend_.MustFind(key);
    }

    std::size_t Size() const {
      return backend_.SizeNoSerialization();
    }

    void Clear() {
      backend_.Clear();
    }

    ConstIterator RawBegin() const {
      return backend_.RawBegin();
    }
    ConstIterator RawEnd() const {
      return backend_.RawEnd();
    }

  private:
    void DoubleIfNeeded() {
      if (__builtin_expect (!!(Size() < threshold_), 1))
        return;
      HugeRealloc(backend_.DoubleTo(), KeyIsRawZero(backend_.invalid_), mem_);
      allocated_ = backend_.DoubleTo();
      backend_.Double(mem_.get(), !KeyIsRawZero(backend_.invalid_));
      threshold_ = std::min<std::size_t>(backend_.buckets_ - 1, backend_.buckets_ * 0.9);
    }

    bool KeyIsRawZero(const Key &key) {
      for (const uint8_t *i = reinterpret_cast<const uint8_t*>(&key); i < reinterpret_cast<const uint8_t*>(&key) + sizeof(Key); ++i) {
        if (*i) return false;
      }
      return true;
    }

    std::size_t allocated_;
    util::scoped_memory mem_;
    Backend backend_;
    std::size_t threshold_;
};

}
# 12 "./lm/search_hashed.hh" 2





namespace util { class FilePiece; }

namespace lm {
namespace ngram {
class BinaryFormat;
class ProbingVocabulary;
namespace detail {

inline uint64_t CombineWordHash(uint64_t current, const WordIndex next) {
  uint64_t ret = (current * 8978948897894561157ULL) ^ (static_cast<uint64_t>(1 + next) * 17894857484156487943ULL);
  return ret;
}

#pragma pack(push)
#pragma pack(4)
struct ProbEntry {
  uint64_t key;
  Prob value;
  typedef uint64_t Key;
  typedef Prob Value;
  uint64_t GetKey() const {
    return key;
  }
};

#pragma pack(pop)

class LongestPointer {
  public:
    explicit LongestPointer(const float &to) : to_(&to) {}

    LongestPointer() : to_(
# 48 "./lm/search_hashed.hh" 3 4
                          __null
# 48 "./lm/search_hashed.hh"
                              ) {}

    bool Found() const {
      return to_ != 
# 51 "./lm/search_hashed.hh" 3 4
                   __null
# 51 "./lm/search_hashed.hh"
                       ;
    }

    float Prob() const {
      return *to_;
    }

  private:
    const float *to_;
};

template <class Value> class HashedSearch {
  public:
    typedef uint64_t Node;

    typedef typename Value::ProbingProxy UnigramPointer;
    typedef typename Value::ProbingProxy MiddlePointer;
    typedef ::lm::ngram::detail::LongestPointer LongestPointer;

    static const ModelType kModelType = Value::kProbingModelType;
    static const bool kDifferentRest = Value::kDifferentRest;
    static const unsigned int kVersion = 0;


    static void UpdateConfigFromBinary(const BinaryFormat &, const std::vector<uint64_t> &, uint64_t, Config &) {}

    static uint64_t Size(const std::vector<uint64_t> &counts, const Config &config) {
      uint64_t ret = Unigram::Size(counts[0]);
      for (unsigned char n = 1; n < counts.size() - 1; ++n) {
        ret += Middle::Size(counts[n], config.probing_multiplier);
      }
      return ret + Longest::Size(counts.back(), config.probing_multiplier);
    }

    uint8_t *SetupMemory(uint8_t *start, const std::vector<uint64_t> &counts, const Config &config);

    void InitializeFromARPA(const char *file, util::FilePiece &f, const std::vector<uint64_t> &counts, const Config &config, ProbingVocabulary &vocab, BinaryFormat &backing);

    unsigned char Order() const {
      return middle_.size() + 2;
    }

    typename Value::Weights &UnknownUnigram() { return unigram_.Unknown(); }

    UnigramPointer LookupUnigram(WordIndex word, Node &next, bool &independent_left, uint64_t &extend_left) const {
      extend_left = static_cast<uint64_t>(word);
      next = extend_left;
      UnigramPointer ret(unigram_.Lookup(word));
      independent_left = ret.IndependentLeft();
      return ret;
    }

    MiddlePointer Unpack(uint64_t extend_pointer, unsigned char extend_length, Node &node) const {
      node = extend_pointer;
      return MiddlePointer(middle_[extend_length - 2].MustFind(extend_pointer)->value);
    }

    MiddlePointer LookupMiddle(unsigned char order_minus_2, WordIndex word, Node &node, bool &independent_left, uint64_t &extend_pointer) const {
      node = CombineWordHash(node, word);
      typename Middle::ConstIterator found;
      if (!middle_[order_minus_2].Find(node, found)) {
        independent_left = true;
        return MiddlePointer();
      }
      extend_pointer = node;
      MiddlePointer ret(found->value);
      independent_left = ret.IndependentLeft();
      return ret;
    }

    LongestPointer LookupLongest(WordIndex word, const Node &node) const {

      typename Longest::ConstIterator found;
      if (!longest_.Find(CombineWordHash(node, word), found)) return LongestPointer();
      return LongestPointer(found->value.prob);
    }



    bool FastMakeNode(const WordIndex *begin, const WordIndex *end, Node &node) const {
      
# 131 "./lm/search_hashed.hh" 3 4
     ((
# 131 "./lm/search_hashed.hh"
     begin != end
# 131 "./lm/search_hashed.hh" 3 4
     ) ? (void)0 : __assert_func ("./lm/search_hashed.hh", 131, __PRETTY_FUNCTION__, 
# 131 "./lm/search_hashed.hh"
     "begin != end"
# 131 "./lm/search_hashed.hh" 3 4
     ))
# 131 "./lm/search_hashed.hh"
                         ;
      node = static_cast<Node>(*begin);
      for (const WordIndex *i = begin + 1; i < end; ++i) {
        node = CombineWordHash(node, *i);
      }
      return true;
    }

  private:

    void DispatchBuild(util::FilePiece &f, const std::vector<uint64_t> &counts, const Config &config, const ProbingVocabulary &vocab, PositiveProbWarn &warn);

    template <class Build> void ApplyBuild(util::FilePiece &f, const std::vector<uint64_t> &counts, const ProbingVocabulary &vocab, PositiveProbWarn &warn, const Build &build);

    class Unigram {
      public:
        Unigram() {}

        Unigram(void *start, uint64_t count) :
          unigram_(static_cast<typename Value::Weights*>(start))



      {}

        static uint64_t Size(uint64_t count) {
          return (count + 1) * sizeof(typename Value::Weights);
        }

        const typename Value::Weights &Lookup(WordIndex index) const {



          return unigram_[index];
        }

        typename Value::Weights &Unknown() { return unigram_[0]; }


        typename Value::Weights *Raw() { return unigram_; }

      private:
        typename Value::Weights *unigram_;



    };

    Unigram unigram_;

    typedef util::ProbingHashTable<typename Value::ProbingEntry, util::IdentityHash> Middle;
    std::vector<Middle> middle_;

    typedef util::ProbingHashTable<ProbEntry, util::IdentityHash> Longest;
    Longest longest_;
};

}
}
}
# 10 "lm/model.hh" 2
# 1 "./lm/search_trie.hh" 1
# 14 "./lm/search_trie.hh"
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstdlib" 1 3
# 39 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstdlib" 3
       
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstdlib" 3
# 15 "./lm/search_trie.hh" 2
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 1 3
# 41 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 3
       
# 42 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 3

# 1 "/usr/include/assert.h" 1 3 4






# 6 "/usr/include/assert.h" 3 4
extern "C" {
# 39 "/usr/include/assert.h" 3 4
void __attribute__((__cdecl__)) __assert (const char *, int, const char *) __attribute__ ((__noreturn__))
                                 ;
void __attribute__((__cdecl__)) __assert_func (const char *, int, const char *, const char *) __attribute__ ((__noreturn__))
                                 ;






}
# 43 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 2 3
# 16 "./lm/search_trie.hh" 2


# 17 "./lm/search_trie.hh"
namespace lm {
namespace ngram {
class BinaryFormat;
class SortedVocabulary;
namespace trie {

template <class Quant, class Bhiksha> class TrieSearch;
class SortedFiles;
template <class Quant, class Bhiksha> void BuildTrie(SortedFiles &files, std::vector<uint64_t> &counts, const Config &config, TrieSearch<Quant, Bhiksha> &out, Quant &quant, SortedVocabulary &vocab, BinaryFormat &backing);

template <class Quant, class Bhiksha> class TrieSearch {
  public:
    typedef NodeRange Node;

    typedef ::lm::ngram::trie::UnigramPointer UnigramPointer;
    typedef typename Quant::MiddlePointer MiddlePointer;
    typedef typename Quant::LongestPointer LongestPointer;

    static const bool kDifferentRest = false;

    static const ModelType kModelType = static_cast<ModelType>(TRIE_SORTED + Quant::kModelTypeAdd + Bhiksha::kModelTypeAdd);

    static const unsigned int kVersion = 1;

    static void UpdateConfigFromBinary(const BinaryFormat &file, const std::vector<uint64_t> &counts, uint64_t offset, Config &config) {
      Quant::UpdateConfigFromBinary(file, offset, config);

      if (counts.size() > 2)
        Bhiksha::UpdateConfigFromBinary(file, offset + Quant::Size(counts.size(), config) + Unigram::Size(counts[0]), config);
    }

    static uint64_t Size(const std::vector<uint64_t> &counts, const Config &config) {
      uint64_t ret = Quant::Size(counts.size(), config) + Unigram::Size(counts[0]);
      for (unsigned char i = 1; i < counts.size() - 1; ++i) {
        ret += Middle::Size(Quant::MiddleBits(config), counts[i], counts[0], counts[i+1], config);
      }
      return ret + Longest::Size(Quant::LongestBits(config), counts.back(), counts[0]);
    }

    TrieSearch() : middle_begin_(
# 56 "./lm/search_trie.hh" 3 4
                                __null
# 56 "./lm/search_trie.hh"
                                    ), middle_end_(
# 56 "./lm/search_trie.hh" 3 4
                                                   __null
# 56 "./lm/search_trie.hh"
                                                       ) {}

    ~TrieSearch() { FreeMiddles(); }

    uint8_t *SetupMemory(uint8_t *start, const std::vector<uint64_t> &counts, const Config &config);

    void InitializeFromARPA(const char *file, util::FilePiece &f, std::vector<uint64_t> &counts, const Config &config, SortedVocabulary &vocab, BinaryFormat &backing);

    unsigned char Order() const {
      return middle_end_ - middle_begin_ + 2;
    }

    ProbBackoff &UnknownUnigram() { return unigram_.Unknown(); }

    UnigramPointer LookupUnigram(WordIndex word, Node &next, bool &independent_left, uint64_t &extend_left) const {
      extend_left = static_cast<uint64_t>(word);
      UnigramPointer ret(unigram_.Find(word, next));
      independent_left = (next.begin == next.end);
      return ret;
    }

    MiddlePointer Unpack(uint64_t extend_pointer, unsigned char extend_length, Node &node) const {
      return MiddlePointer(quant_, extend_length - 2, middle_begin_[extend_length - 2].ReadEntry(extend_pointer, node));
    }

    MiddlePointer LookupMiddle(unsigned char order_minus_2, WordIndex word, Node &node, bool &independent_left, uint64_t &extend_left) const {
      util::BitAddress address(middle_begin_[order_minus_2].Find(word, node, extend_left));
      independent_left = (address.base == 
# 83 "./lm/search_trie.hh" 3 4
                                         __null
# 83 "./lm/search_trie.hh"
                                             ) || (node.begin == node.end);
      return MiddlePointer(quant_, order_minus_2, address);
    }

    LongestPointer LookupLongest(WordIndex word, const Node &node) const {
      return LongestPointer(quant_, longest_.Find(word, node));
    }

    bool FastMakeNode(const WordIndex *begin, const WordIndex *end, Node &node) const {
      
# 92 "./lm/search_trie.hh" 3 4
     ((
# 92 "./lm/search_trie.hh"
     begin != end
# 92 "./lm/search_trie.hh" 3 4
     ) ? (void)0 : __assert_func ("./lm/search_trie.hh", 92, __PRETTY_FUNCTION__, 
# 92 "./lm/search_trie.hh"
     "begin != end"
# 92 "./lm/search_trie.hh" 3 4
     ))
# 92 "./lm/search_trie.hh"
                         ;
      bool independent_left;
      uint64_t ignored;
      LookupUnigram(*begin, node, independent_left, ignored);
      for (const WordIndex *i = begin + 1; i < end; ++i) {
        if (independent_left || !LookupMiddle(i - begin - 1, *i, node, independent_left, ignored).Found()) return false;
      }
      return true;
    }

  private:
    friend void BuildTrie<Quant, Bhiksha>(SortedFiles &files, std::vector<uint64_t> &counts, const Config &config, TrieSearch<Quant, Bhiksha> &out, Quant &quant, SortedVocabulary &vocab, BinaryFormat &backing);


    void FreeMiddles() {
      for (const Middle *i = middle_begin_; i != middle_end_; ++i) {
        i->~Middle();
      }
      std::free(middle_begin_);
    }

    typedef trie::BitPackedMiddle<Bhiksha> Middle;

    typedef trie::BitPackedLongest Longest;
    Longest longest_;

    Middle *middle_begin_, *middle_end_;
    Quant quant_;

    typedef ::lm::ngram::trie::Unigram Unigram;
    Unigram unigram_;
};

}
}
}
# 11 "lm/model.hh" 2
# 1 "./lm/state.hh" 1





# 1 "./util/murmur_hash.hh" 1





namespace util {


uint64_t MurmurHash64A(const void * key, std::size_t len, uint64_t seed = 0);

uint64_t MurmurHash64B(const void * key, std::size_t len, uint64_t seed = 0);


uint64_t MurmurHashNative(const void * key, std::size_t len, uint64_t seed = 0);

}
# 7 "./lm/state.hh" 2

# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstring" 1 3
# 39 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstring" 3
       
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstring" 3
# 9 "./lm/state.hh" 2

namespace lm {
namespace ngram {



class State {
  public:
    bool operator==(const State &other) const {
      if (length != other.length) return false;
      return !memcmp(words, other.words, length * sizeof(WordIndex));
    }


    int Compare(const State &other) const {
      if (length != other.length) return length < other.length ? -1 : 1;
      return memcmp(words, other.words, length * sizeof(WordIndex));
    }

    bool operator<(const State &other) const {
      if (length != other.length) return length < other.length;
      return memcmp(words, other.words, length * sizeof(WordIndex)) < 0;
    }


    void ZeroRemaining() {
      for (unsigned char i = length; i < KENLM_MAX_ORDER - 1; ++i) {
        words[i] = 0;
        backoff[i] = 0.0;
      }
    }

    unsigned char Length() const { return length; }



    WordIndex words[KENLM_MAX_ORDER - 1];
    float backoff[KENLM_MAX_ORDER - 1];
    unsigned char length;
};

typedef State Right;

inline uint64_t hash_value(const State &state, uint64_t seed = 0) {
  return util::MurmurHashNative(state.words, sizeof(WordIndex) * state.length, seed);
}

struct Left {
  bool operator==(const Left &other) const {
    return
      length == other.length &&
      (!length || (pointers[length - 1] == other.pointers[length - 1] && full == other.full));
  }

  int Compare(const Left &other) const {
    if (length < other.length) return -1;
    if (length > other.length) return 1;
    if (length == 0) return 0;
    if (pointers[length - 1] > other.pointers[length - 1]) return 1;
    if (pointers[length - 1] < other.pointers[length - 1]) return -1;
    return (int)full - (int)other.full;
  }

  bool operator<(const Left &other) const {
    return Compare(other) == -1;
  }

  void ZeroRemaining() {
    for (uint64_t * i = pointers + length; i < pointers + KENLM_MAX_ORDER - 1; ++i)
      *i = 0;
  }

  uint64_t pointers[KENLM_MAX_ORDER - 1];
  unsigned char length;
  bool full;
};

inline uint64_t hash_value(const Left &left) {
  unsigned char add[2];
  add[0] = left.length;
  add[1] = left.full;
  return util::MurmurHashNative(add, 2, left.length ? left.pointers[left.length - 1] : 0);
}

struct ChartState {
  bool operator==(const ChartState &other) const {
    return (right == other.right) && (left == other.left);
  }

  int Compare(const ChartState &other) const {
    int lres = left.Compare(other.left);
    if (lres) return lres;
    return right.Compare(other.right);
  }

  bool operator<(const ChartState &other) const {
    return Compare(other) < 0;
  }

  void ZeroRemaining() {
    left.ZeroRemaining();
    right.ZeroRemaining();
  }

  Left left;
  State right;
};

inline uint64_t hash_value(const ChartState &state) {
  return hash_value(state.right, hash_value(state.left));
}


}
}
# 12 "lm/model.hh" 2
# 1 "./lm/value.hh" 1





# 1 "./lm/value_build.hh" 1
# 10 "./lm/value_build.hh"
namespace lm {
namespace ngram {

struct Config;
struct BackoffValue;
struct RestValue;

class NoRestBuild {
  public:
    typedef BackoffValue Value;

    NoRestBuild() {}

    void SetRest(const WordIndex *, unsigned int, const Prob & ) const {}
    void SetRest(const WordIndex *, unsigned int, const ProbBackoff &) const {}

    template <class Second> bool MarkExtends(ProbBackoff &weights, const Second &) const {
      util::UnsetSign(weights.prob);
      return false;
    }


    const static bool kMarkEvenLower = false;
};

class MaxRestBuild {
  public:
    typedef RestValue Value;

    MaxRestBuild() {}

    void SetRest(const WordIndex *, unsigned int, const Prob & ) const {}
    void SetRest(const WordIndex *, unsigned int, RestWeights &weights) const {
      weights.rest = weights.prob;
      util::SetSign(weights.rest);
    }

    bool MarkExtends(RestWeights &weights, const RestWeights &to) const {
      util::UnsetSign(weights.prob);
      if (weights.rest >= to.rest) return false;
      weights.rest = to.rest;
      return true;
    }
    bool MarkExtends(RestWeights &weights, const Prob &to) const {
      util::UnsetSign(weights.prob);
      if (weights.rest >= to.prob) return false;
      weights.rest = to.prob;
      return true;
    }


    const static bool kMarkEvenLower = true;
};

template <class Model> class LowerRestBuild {
  public:
    typedef RestValue Value;

    LowerRestBuild(const Config &config, unsigned int order, const typename Model::Vocabulary &vocab);

    ~LowerRestBuild();

    void SetRest(const WordIndex *, unsigned int, const Prob & ) const {}
    void SetRest(const WordIndex *vocab_ids, unsigned int n, RestWeights &weights) const {
      typename Model::State ignored;
      if (n == 1) {
        weights.rest = unigrams_[*vocab_ids];
      } else {
        weights.rest = models_[n-2]->FullScoreForgotState(vocab_ids + 1, vocab_ids + n, *vocab_ids, ignored).prob;
      }
    }

    template <class Second> bool MarkExtends(RestWeights &weights, const Second &) const {
      util::UnsetSign(weights.prob);
      return false;
    }

    const static bool kMarkEvenLower = false;

    std::vector<float> unigrams_;

    std::vector<const Model*> models_;
};

}
}
# 7 "./lm/value.hh" 2





namespace lm {
namespace ngram {


template <class Weights> class GenericProbingProxy {
  public:
    explicit GenericProbingProxy(const Weights &to) : to_(&to) {}

    GenericProbingProxy() : to_(0) {}

    bool Found() const { return to_ != 0; }

    float Prob() const {
      util::FloatEnc enc;
      enc.f = to_->prob;
      enc.i |= util::kSignBit;
      return enc.f;
    }

    float Backoff() const { return to_->backoff; }

    bool IndependentLeft() const {
      util::FloatEnc enc;
      enc.f = to_->prob;
      return enc.i & util::kSignBit;
    }

  protected:
    const Weights *to_;
};


template <class Weights> class GenericTrieUnigramProxy {
  public:
    explicit GenericTrieUnigramProxy(const Weights &to) : to_(&to) {}

    GenericTrieUnigramProxy() : to_(0) {}

    bool Found() const { return to_ != 0; }
    float Prob() const { return to_->prob; }
    float Backoff() const { return to_->backoff; }
    float Rest() const { return Prob(); }

  protected:
    const Weights *to_;
};

struct BackoffValue {
  typedef ProbBackoff Weights;
  static const ModelType kProbingModelType = PROBING;

  class ProbingProxy : public GenericProbingProxy<Weights> {
    public:
      explicit ProbingProxy(const Weights &to) : GenericProbingProxy<Weights>(to) {}
      ProbingProxy() {}
      float Rest() const { return Prob(); }
  };

  class TrieUnigramProxy : public GenericTrieUnigramProxy<Weights> {
    public:
      explicit TrieUnigramProxy(const Weights &to) : GenericTrieUnigramProxy<Weights>(to) {}
      TrieUnigramProxy() {}
      float Rest() const { return Prob(); }
  };

  struct ProbingEntry {
    typedef uint64_t Key;
    typedef Weights Value;
    uint64_t key;
    ProbBackoff value;
    uint64_t GetKey() const { return key; }
  };

  struct TrieUnigramValue {
    Weights weights;
    uint64_t next;
    uint64_t Next() const { return next; }
  };

  const static bool kDifferentRest = false;

  template <class Model, class C> void Callback(const Config &, unsigned int, typename Model::Vocabulary &, C &callback) {
    NoRestBuild build;
    callback(build);
  }
};

struct RestValue {
  typedef RestWeights Weights;
  static const ModelType kProbingModelType = REST_PROBING;

  class ProbingProxy : public GenericProbingProxy<RestWeights> {
    public:
      explicit ProbingProxy(const Weights &to) : GenericProbingProxy<RestWeights>(to) {}
      ProbingProxy() {}
      float Rest() const { return to_->rest; }
  };

  class TrieUnigramProxy : public GenericTrieUnigramProxy<Weights> {
    public:
      explicit TrieUnigramProxy(const Weights &to) : GenericTrieUnigramProxy<Weights>(to) {}
      TrieUnigramProxy() {}
      float Rest() const { return to_->rest; }
  };


#pragma pack(push)
#pragma pack(4)
  struct ProbingEntry {
    typedef uint64_t Key;
    typedef Weights Value;
    Key key;
    Value value;
    Key GetKey() const { return key; }
  };

  struct TrieUnigramValue {
    Weights weights;
    uint64_t next;
    uint64_t Next() const { return next; }
  };
#pragma pack(pop)

  const static bool kDifferentRest = true;

  template <class Model, class C> void Callback(const Config &config, unsigned int order, typename Model::Vocabulary &vocab, C &callback) {
    switch (config.rest_function) {
      case Config::REST_MAX:
        {
          MaxRestBuild build;
          callback(build);
        }
        break;
      case Config::REST_LOWER:
        {
          LowerRestBuild<Model> build(config, order, vocab);
          callback(build);
        }
        break;
    }
  }
};

}
}
# 13 "lm/model.hh" 2
# 1 "./lm/vocab.hh" 1



# 1 "./lm/enumerate_vocab.hh" 1






namespace lm {







class EnumerateVocab {
  public:
    virtual ~EnumerateVocab() {}

    virtual void Add(WordIndex index, const StringPiece &str) = 0;

  protected:
    EnumerateVocab() {}
};

}
# 5 "./lm/vocab.hh" 2


# 1 "./util/file_stream.hh" 1
# 11 "./util/file_stream.hh"
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 1 3
# 41 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 3
       
# 42 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 3

# 1 "/usr/include/assert.h" 1 3 4






# 6 "/usr/include/assert.h" 3 4
extern "C" {
# 39 "/usr/include/assert.h" 3 4
void __attribute__((__cdecl__)) __assert (const char *, int, const char *) __attribute__ ((__noreturn__))
                                 ;
void __attribute__((__cdecl__)) __assert_func (const char *, int, const char *, const char *) __attribute__ ((__noreturn__))
                                 ;






}
# 43 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 2 3
# 12 "./util/file_stream.hh" 2
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstring" 1 3
# 39 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstring" 3
       
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstring" 3
# 13 "./util/file_stream.hh" 2




# 16 "./util/file_stream.hh"
namespace util {

class FileStream : public FakeOStream<FileStream> {
  public:
    explicit FileStream(int out = -1, std::size_t buffer_size = 8192)
      : buf_(util::MallocOrThrow(std::max<std::size_t>(buffer_size, kToStringMaxBytes))),
        current_(static_cast<char*>(buf_.get())),
        end_(current_ + std::max<std::size_t>(buffer_size, kToStringMaxBytes)),
        fd_(out) {}
# 33 "./util/file_stream.hh"
    ~FileStream() {
      flush();
    }

    void SetFD(int to) {
      flush();
      fd_ = to;
    }

    FileStream &flush() {
      if (current_ != buf_.get()) {
        util::WriteOrThrow(fd_, buf_.get(), current_ - (char*)buf_.get());
        current_ = static_cast<char*>(buf_.get());
      }
      return *this;
    }


    FileStream &write(const void *data, std::size_t length) {
      if (__builtin_expect (!!(current_ + length <= end_), 1)) {
        std::memcpy(current_, data, length);
        current_ += length;
        return *this;
      }
      flush();
      if (current_ + length <= end_) {
        std::memcpy(current_, data, length);
        current_ += length;
      } else {
        util::WriteOrThrow(fd_, data, length);
      }
      return *this;
    }

    FileStream &seekp(uint64_t to) {
      flush();
      util::SeekOrThrow(fd_, to);
      return *this;
    }

  protected:
    friend class FakeOStream<FileStream>;

    char *Ensure(std::size_t amount) {
      if (__builtin_expect (!!(current_ + amount > end_), 0)) {
        flush();
        
# 79 "./util/file_stream.hh" 3 4
       ((
# 79 "./util/file_stream.hh"
       current_ + amount <= end_
# 79 "./util/file_stream.hh" 3 4
       ) ? (void)0 : __assert_func ("./util/file_stream.hh", 79, __PRETTY_FUNCTION__, 
# 79 "./util/file_stream.hh"
       "current_ + amount <= end_"
# 79 "./util/file_stream.hh" 3 4
       ))
# 79 "./util/file_stream.hh"
                                        ;
      }
      return current_;
    }

    void AdvanceTo(char *to) {
      current_ = to;
      
# 86 "./util/file_stream.hh" 3 4
     ((
# 86 "./util/file_stream.hh"
     current_ <= end_
# 86 "./util/file_stream.hh" 3 4
     ) ? (void)0 : __assert_func ("./util/file_stream.hh", 86, __PRETTY_FUNCTION__, 
# 86 "./util/file_stream.hh"
     "current_ <= end_"
# 86 "./util/file_stream.hh" 3 4
     ))
# 86 "./util/file_stream.hh"
                             ;
    }

  private:
    util::scoped_malloc buf_;
    char *current_, *end_;
    int fd_;
};

}
# 8 "./lm/vocab.hh" 2

# 1 "./util/pool.hh" 1



# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 1 3
# 41 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 3
       
# 42 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 3

# 1 "/usr/include/assert.h" 1 3 4






# 6 "/usr/include/assert.h" 3 4
extern "C" {
# 39 "/usr/include/assert.h" 3 4
void __attribute__((__cdecl__)) __assert (const char *, int, const char *) __attribute__ ((__noreturn__))
                                 ;
void __attribute__((__cdecl__)) __assert_func (const char *, int, const char *, const char *) __attribute__ ((__noreturn__))
                                 ;






}
# 43 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cassert" 2 3
# 5 "./util/pool.hh" 2
# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstring" 1 3
# 39 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstring" 3
       
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstring" 3
# 6 "./util/pool.hh" 2





# 10 "./util/pool.hh"
namespace util {




class Pool {
  public:
    Pool();

    ~Pool();

    void *Allocate(std::size_t size) {
      void *ret = current_;
      current_ += size;
      if (current_ > current_end_) {
        ret = More(size);
      }



      return ret;
    }
# 45 "./util/pool.hh"
    bool Continue(void *&base, std::ptrdiff_t additional) {



      current_ += additional;
      if (current_ > current_end_) {
        std::size_t new_total = current_ - static_cast<uint8_t*>(base);
        void *new_base = More(new_total);
        std::memcpy(new_base, base, new_total - additional);
        base = new_base;



        return true;
      }
      return false;
    }

    void FreeAll();

  private:
    void *More(std::size_t size);

    std::vector<void *> free_list_;

    uint8_t *current_, *current_end_;







    Pool(const Pool &);
    Pool &operator=(const Pool &);
};






class FreePool {
  public:
    explicit FreePool(std::size_t element_size)
      : free_list_(
# 90 "./util/pool.hh" 3 4
                  __null
# 90 "./util/pool.hh"
                      ), element_size_(element_size) {}

    void *Allocate() {
      if (free_list_) {
        void *ret = free_list_;
        free_list_ = *reinterpret_cast<void**>(free_list_);
        return ret;
      } else {
        return backing_.Allocate(element_size_);
      }
    }

    void Free(void *ptr) {
      *reinterpret_cast<void**>(ptr) = free_list_;
      free_list_ = ptr;
    }

    std::size_t ElementSize() const { return element_size_; }

  private:
    void *free_list_;

    Pool backing_;

    const std::size_t element_size_;
};

}
# 10 "./lm/vocab.hh" 2
# 18 "./lm/vocab.hh"
namespace lm {
struct ProbBackoff;
class EnumerateVocab;

namespace ngram {
struct Config;

namespace detail {
uint64_t HashForVocab(const char *str, std::size_t len);
inline uint64_t HashForVocab(const StringPiece &str) {
  return HashForVocab(str.data(), str.length());
}
struct ProbingVocabularyHeader;
}



class ImmediateWriteWordsWrapper : public EnumerateVocab {
  public:
    ImmediateWriteWordsWrapper(EnumerateVocab *inner, int fd, uint64_t start);

    void Add(WordIndex index, const StringPiece &str) {
      stream_ << str << '\0';
      if (inner_) inner_->Add(index, str);
    }

  private:
    EnumerateVocab *inner_;

    util::FileStream stream_;
};


class WriteWordsWrapper : public EnumerateVocab {
  public:
    WriteWordsWrapper(EnumerateVocab *inner);

    void Add(WordIndex index, const StringPiece &str);

    const std::string &Buffer() const { return buffer_; }
    void Write(int fd, uint64_t start);

  private:
    EnumerateVocab *inner_;

    std::string buffer_;
};


class SortedVocabulary : public base::Vocabulary {
  public:
    SortedVocabulary();

    WordIndex Index(const StringPiece &str) const {
      const uint64_t *found;
      if (util::BoundedSortedUniformFind<const uint64_t*, util::IdentityAccessor<uint64_t>, util::Pivot64>(
            util::IdentityAccessor<uint64_t>(),
            begin_ - 1, 0,
            end_, std::numeric_limits<uint64_t>::max(),
            detail::HashForVocab(str), found)) {
        return found - begin_ + 1;
      } else {
        return 0;
      }
    }


    static uint64_t Size(uint64_t entries, const Config &config);





    static void ComputeRenumbering(WordIndex types, int from_words, int to_words, std::vector<WordIndex> &mapping);


    WordIndex Bound() const { return bound_; }


    void SetupMemory(void *start, std::size_t allocated, std::size_t entries, const Config &config);

    void Relocate(void *new_start);

    void ConfigureEnumerate(EnumerateVocab *to, std::size_t max_entries);


    WordIndex Insert(const StringPiece &str);

    void FinishedLoading(ProbBackoff *reorder_vocab);


    std::size_t UnkCountChangePadding() const { return SawUnk() ? 0 : sizeof(uint64_t); }

    bool SawUnk() const { return saw_unk_; }

    void LoadedBinary(bool have_words, int fd, EnumerateVocab *to, uint64_t offset);

    uint64_t *&EndHack() { return end_; }

    void Populated();

  private:
    template <class T> void GenericFinished(T *reorder);

    uint64_t *begin_, *end_;

    WordIndex bound_;

    bool saw_unk_;

    EnumerateVocab *enumerate_;


    util::Pool string_backing_;

    std::vector<StringPiece> strings_to_enumerate_;
};

#pragma pack(push)
#pragma pack(4)
struct ProbingVocabularyEntry {
  uint64_t key;
  WordIndex value;

  typedef uint64_t Key;
  uint64_t GetKey() const { return key; }
  void SetKey(uint64_t to) { key = to; }

  static ProbingVocabularyEntry Make(uint64_t key, WordIndex value) {
    ProbingVocabularyEntry ret;
    ret.key = key;
    ret.value = value;
    return ret;
  }
};
#pragma pack(pop)


class ProbingVocabulary : public base::Vocabulary {
  public:
    ProbingVocabulary();

    WordIndex Index(const StringPiece &str) const {
      Lookup::ConstIterator i;
      return lookup_.Find(detail::HashForVocab(str), i) ? i->value : 0;
    }

    static uint64_t Size(uint64_t entries, float probing_multiplier);

    static uint64_t Size(uint64_t entries, const Config &config);


    WordIndex Bound() const { return bound_; }


    void SetupMemory(void *start, std::size_t allocated);
    void SetupMemory(void *start, std::size_t allocated, std::size_t , const Config & ) {
      SetupMemory(start, allocated);
    }

    void Relocate(void *new_start);

    void ConfigureEnumerate(EnumerateVocab *to, std::size_t max_entries);

    WordIndex Insert(const StringPiece &str);

    template <class Weights> void FinishedLoading(Weights * ) {
      InternalFinishedLoading();
    }

    std::size_t UnkCountChangePadding() const { return 0; }

    bool SawUnk() const { return saw_unk_; }

    void LoadedBinary(bool have_words, int fd, EnumerateVocab *to, uint64_t offset);

  private:
    void InternalFinishedLoading();

    typedef util::ProbingHashTable<ProbingVocabularyEntry, util::IdentityHash> Lookup;

    Lookup lookup_;

    WordIndex bound_;

    bool saw_unk_;

    EnumerateVocab *enumerate_;

    detail::ProbingVocabularyHeader *header_;
};

void MissingUnknown(const Config &config) throw(SpecialWordMissingException);
void MissingSentenceMarker(const Config &config, const char *str) throw(SpecialWordMissingException);

template <class Vocab> void CheckSpecials(const Config &config, const Vocab &vocab) throw(SpecialWordMissingException) {
  if (!vocab.SawUnk()) MissingUnknown(config);
  if (vocab.BeginSentence() == vocab.NotFound()) MissingSentenceMarker(config, "<s>");
  if (vocab.EndSentence() == vocab.NotFound()) MissingSentenceMarker(config, "</s>");
}

class WriteUniqueWords {
  public:
    explicit WriteUniqueWords(int fd) : word_list_(fd) {}

    void operator()(const StringPiece &word) {
      word_list_ << word << '\0';
    }

  private:
    util::FileStream word_list_;
};

class NoOpUniqueWords {
  public:
    NoOpUniqueWords() {}
    void operator()(const StringPiece &word) {}
};

template <class NewWordAction = NoOpUniqueWords> class GrowableVocab {
  public:
    static std::size_t MemUsage(WordIndex content) {
      return Lookup::MemUsage(content > 2 ? content : 2);
    }


    template <class NewWordConstruct> GrowableVocab(WordIndex initial_size, const NewWordConstruct &new_word_construct = NewWordAction())
      : lookup_(initial_size), new_word_(new_word_construct) {
      FindOrInsert("<unk>");
      FindOrInsert("<s>");
      FindOrInsert("</s>");
    }

    WordIndex Index(const StringPiece &str) const {
      Lookup::ConstIterator i;
      return lookup_.Find(detail::HashForVocab(str), i) ? i->value : 0;
    }

    WordIndex FindOrInsert(const StringPiece &word) {
      ProbingVocabularyEntry entry = ProbingVocabularyEntry::Make(util::MurmurHashNative(word.data(), word.size()), Size());
      Lookup::MutableIterator it;
      if (!lookup_.FindOrInsert(entry, it)) {
        new_word_(word);
        do { if (__builtin_expect (!!(Size() >= std::numeric_limits<lm::WordIndex>::max()), 0)) { do { VocabLoadException UTIL_e ; UTIL_e.SetLocation("./lm/vocab.hh", 261, __PRETTY_FUNCTION__, "VocabLoadException", "Size() >= std::numeric_limits<lm::WordIndex>::max()"); UTIL_e << "Too many vocabulary words.  Change WordIndex to uint64_t in lm/word_index.hh"; throw UTIL_e; } while (0); } } while (0);
      }
      return it->value;
    }

    WordIndex Size() const { return lookup_.Size(); }

    bool IsSpecial(WordIndex word) const {
      return word <= 2;
    }

  private:
    typedef util::AutoProbing<ProbingVocabularyEntry, util::IdentityHash> Lookup;

    Lookup lookup_;

    NewWordAction new_word_;
};

}
}
# 14 "lm/model.hh" 2






# 1 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstring" 1 3
# 39 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstring" 3
       
# 40 "/usr/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/cstring" 3
# 21 "lm/model.hh" 2

namespace util { class FilePiece; }

namespace lm {
namespace ngram {
namespace detail {



template <class Search, class VocabularyT> class GenericModel : public base::ModelFacade<GenericModel<Search, VocabularyT>, State, VocabularyT> {
  private:
    typedef base::ModelFacade<GenericModel<Search, VocabularyT>, State, VocabularyT> P;
  public:

    static const ModelType kModelType;

    static const unsigned int kVersion = Search::kVersion;





    static uint64_t Size(const std::vector<uint64_t> &counts, const Config &config = Config());







    explicit GenericModel(const char *file, const Config &config = Config());





    FullScoreReturn FullScore(const State &in_state, const WordIndex new_word, State &out_state) const;
# 66 "lm/model.hh"
    FullScoreReturn FullScoreForgotState(const WordIndex *context_rbegin, const WordIndex *context_rend, const WordIndex new_word, State &out_state) const;
# 76 "lm/model.hh"
    void GetState(const WordIndex *context_rbegin, const WordIndex *context_rend, State &out_state) const;





    FullScoreReturn ExtendLeft(

        const WordIndex *add_rbegin, const WordIndex *add_rend,

        const float *backoff_in,

        uint64_t extend_pointer,

        unsigned char extend_length,

        float *backoff_out,

        unsigned char &next_use) const;





    float UnRest(const uint64_t *pointers_begin, const uint64_t *pointers_end, unsigned char first_length) const {

      return Search::kDifferentRest ? InternalUnRest(pointers_begin, pointers_end, first_length) : 0.0;
    }

  private:
    FullScoreReturn ScoreExceptBackoff(const WordIndex *const context_rbegin, const WordIndex *const context_rend, const WordIndex new_word, State &out_state) const;


    void ResumeScore(const WordIndex *context_rbegin, const WordIndex *const context_rend, unsigned char starting_order_minus_2, typename Search::Node &node, float *backoff_out, unsigned char &next_use, FullScoreReturn &ret) const;


    void SetupMemory(void *start, const std::vector<uint64_t> &counts, const Config &config);

    void InitializeFromARPA(int fd, const char *file, const Config &config);

    float InternalUnRest(const uint64_t *pointers_begin, const uint64_t *pointers_end, unsigned char first_length) const;

    BinaryFormat backing_;

    VocabularyT vocab_;

    Search search_;
};

}
# 136 "lm/model.hh"
class ProbingModel : public detail::GenericModel<detail::HashedSearch<BackoffValue> , ProbingVocabulary> { public: ProbingModel(const char *file, const Config &config = Config()) : detail::GenericModel<detail::HashedSearch<BackoffValue> , ProbingVocabulary>(file, config) {}};;
class RestProbingModel : public detail::GenericModel<detail::HashedSearch<RestValue> , ProbingVocabulary> { public: RestProbingModel(const char *file, const Config &config = Config()) : detail::GenericModel<detail::HashedSearch<RestValue> , ProbingVocabulary>(file, config) {}};;
class TrieModel : public detail::GenericModel<trie::TrieSearch<DontQuantize , trie::DontBhiksha> , SortedVocabulary> { public: TrieModel(const char *file, const Config &config = Config()) : detail::GenericModel<trie::TrieSearch<DontQuantize , trie::DontBhiksha> , SortedVocabulary>(file, config) {}};;
class ArrayTrieModel : public detail::GenericModel<trie::TrieSearch<DontQuantize , trie::ArrayBhiksha> , SortedVocabulary> { public: ArrayTrieModel(const char *file, const Config &config = Config()) : detail::GenericModel<trie::TrieSearch<DontQuantize , trie::ArrayBhiksha> , SortedVocabulary>(file, config) {}};;
class QuantTrieModel : public detail::GenericModel<trie::TrieSearch<SeparatelyQuantize , trie::DontBhiksha> , SortedVocabulary> { public: QuantTrieModel(const char *file, const Config &config = Config()) : detail::GenericModel<trie::TrieSearch<SeparatelyQuantize , trie::DontBhiksha> , SortedVocabulary>(file, config) {}};;
class QuantArrayTrieModel : public detail::GenericModel<trie::TrieSearch<SeparatelyQuantize , trie::ArrayBhiksha> , SortedVocabulary> { public: QuantArrayTrieModel(const char *file, const Config &config = Config()) : detail::GenericModel<trie::TrieSearch<SeparatelyQuantize , trie::ArrayBhiksha> , SortedVocabulary>(file, config) {}};;


typedef ::lm::ngram::ProbingVocabulary Vocabulary;
typedef ProbingModel Model;




base::Model *LoadVirtual(const char *file_name, const Config &config = Config(), ModelType if_arpa = PROBING);

}
}
