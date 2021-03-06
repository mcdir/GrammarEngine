#if defined LEM_UNICODE_EX2

#include <lem/unicode.h>

using namespace lem;

static wchar_t ua[256]=
{
    /* 0*/ 0x0000
  , /* 1*/ 0x0001
  , /* 2*/ 0x0002
  , /* 3*/ 0x0003
  , /* 4*/ 0x0004
  , /* 5*/ 0x0005
  , /* 6*/ 0x0006
  , /* 7*/ 0x0007
  , /* 8*/ 0x0008
  , /* 9*/ 0x0009
  , /* a*/ 0x000A
  , /* b*/ 0x000B
  , /* c*/ 0x000C
  , /* d*/ 0x000D
  , /* e*/ 0x000E
  , /* f*/ 0x000F
  , /*10*/ 0x0010
  , /*11*/ 0x0011
  , /*12*/ 0x0012
  , /*13*/ 0x0013
  , /*14*/ 0x0014
  , /*15*/ 0x0015
  , /*16*/ 0x0016
  , /*17*/ 0x0017
  , /*18*/ 0x0018
  , /*19*/ 0x0019
  , /*1a*/ 0x001A
  , /*1b*/ 0x001B
  , /*1c*/ 0x001C
  , /*1d*/ 0x001D
  , /*1e*/ 0x001E
  , /*1f*/ 0x001F
  , /*20*/ 0x0020
  , /*21*/ 0x0021
  , /*22*/ 0x0022
  , /*23*/ 0x0023
  , /*24*/ 0x0024
  , /*25*/ 0x0025
  , /*26*/ 0x0026
  , /*27*/ 0x0027
  , /*28*/ 0x0028
  , /*29*/ 0x0029
  , /*2a*/ 0x002A
  , /*2b*/ 0x002B
  , /*2c*/ 0x002C
  , /*2d*/ 0x002D
  , /*2e*/ 0x002E
  , /*2f*/ 0x002F
  , /*30*/ 0x0030
  , /*31*/ 0x0031
  , /*32*/ 0x0032
  , /*33*/ 0x0033
  , /*34*/ 0x0034
  , /*35*/ 0x0035
  , /*36*/ 0x0036
  , /*37*/ 0x0037
  , /*38*/ 0x0038
  , /*39*/ 0x0039
  , /*3a*/ 0x003A
  , /*3b*/ 0x003B
  , /*3c*/ 0x003C
  , /*3d*/ 0x003D
  , /*3e*/ 0x003E
  , /*3f*/ 0x003F
  , /*40*/ 0x0040
  , /*41*/ 0x0041
  , /*42*/ 0x0042
  , /*43*/ 0x0043
  , /*44*/ 0x0044
  , /*45*/ 0x0045
  , /*46*/ 0x0046
  , /*47*/ 0x0047
  , /*48*/ 0x0048
  , /*49*/ 0x0049
  , /*4a*/ 0x004A
  , /*4b*/ 0x004B
  , /*4c*/ 0x004C
  , /*4d*/ 0x004D
  , /*4e*/ 0x004E
  , /*4f*/ 0x004F
  , /*50*/ 0x0050
  , /*51*/ 0x0051
  , /*52*/ 0x0052
  , /*53*/ 0x0053
  , /*54*/ 0x0054
  , /*55*/ 0x0055
  , /*56*/ 0x0056
  , /*57*/ 0x0057
  , /*58*/ 0x0058
  , /*59*/ 0x0059
  , /*5a*/ 0x005A
  , /*5b*/ 0x005B
  , /*5c*/ 0x005C
  , /*5d*/ 0x005D
  , /*5e*/ 0x005E
  , /*5f*/ 0x005F
  , /*60*/ 0x0060
  , /*61*/ 0x0061
  , /*62*/ 0x0062
  , /*63*/ 0x0063
  , /*64*/ 0x0064
  , /*65*/ 0x0065
  , /*66*/ 0x0066
  , /*67*/ 0x0067
  , /*68*/ 0x0068
  , /*69*/ 0x0069
  , /*6a*/ 0x006A
  , /*6b*/ 0x006B
  , /*6c*/ 0x006C
  , /*6d*/ 0x006D
  , /*6e*/ 0x006E
  , /*6f*/ 0x006F
  , /*70*/ 0x0070
  , /*71*/ 0x0071
  , /*72*/ 0x0072
  , /*73*/ 0x0073
  , /*74*/ 0x0074
  , /*75*/ 0x0075
  , /*76*/ 0x0076
  , /*77*/ 0x0077
  , /*78*/ 0x0078
  , /*79*/ 0x0079
  , /*7a*/ 0x007A
  , /*7b*/ 0x007B
  , /*7c*/ 0x007C
  , /*7d*/ 0x007D
  , /*7e*/ 0x007E
  , /*7f*/ 0x007F
  , /*80*/ 0x0080
  , /*81*/ 0x0081
  , /*82*/ 0x0082
  , /*83*/ 0x0083
  , /*84*/ 0x0084
  , /*85*/ 0x0085
  , /*86*/ 0x0086
  , /*87*/ 0x0087
  , /*88*/ 0x0088
  , /*89*/ 0x0089
  , /*8a*/ 0x008A
  , /*8b*/ 0x008B
  , /*8c*/ 0x008C
  , /*8d*/ 0x008D
  , /*8e*/ 0x008E
  , /*8f*/ 0x008F
  , /*90*/ 0x0090
  , /*91*/ 0x0091
  , /*92*/ 0x0092
  , /*93*/ 0x0093
  , /*94*/ 0x0094
  , /*95*/ 0x0095
  , /*96*/ 0x0096
  , /*97*/ 0x0097
  , /*98*/ 0x0098
  , /*99*/ 0x0099
  , /*9a*/ 0x009A
  , /*9b*/ 0x009B
  , /*9c*/ 0x009C
  , /*9d*/ 0x009D
  , /*9e*/ 0x009E
  , /*9f*/ 0x009F
  , /*a0*/ 0x00A0
  , /*a1*/ 0x06F0
  , /*a2*/ 0x06F1
  , /*a3*/ 0x06F2
  , /*a4*/ 0x06F3
  , /*a5*/ 0x06F4
  , /*a6*/ 0x06F5
  , /*a7*/ 0x06F6
  , /*a8*/ 0x06F7
  , /*a9*/ 0x06F8
  , /*aa*/ 0x06F9
  , /*ab*/ 0x060C
  , /*ac*/ 0x061B
  , /*ad*/ 0x00AD
  , /*ae*/ 0x061F
  , /*af*/ 0xFE81
  , /*b0*/ 0xFE8D
  , /*b1*/ 0xFE8E
  , /*b2*/ 0xFE8E
  , /*b3*/ 0xFE8F
  , /*b4*/ 0xFE91
  , /*b5*/ 0xFB56
  , /*b6*/ 0xFB58
  , /*b7*/ 0xFE93
  , /*b8*/ 0xFE95
  , /*b9*/ 0xFE97
  , /*ba*/ 0xFB66
  , /*bb*/ 0xFB68
  , /*bc*/ 0xFE99
  , /*bd*/ 0xFE9B
  , /*be*/ 0xFE9D
  , /*bf*/ 0xFE9F
  , /*c0*/ 0xFB7A
  , /*c1*/ 0xFB7C
  , /*c2*/ 0xFEA1
  , /*c3*/ 0xFEA3
  , /*c4*/ 0xFEA5
  , /*c5*/ 0xFEA7
  , /*c6*/ 0xFEA9
  , /*c7*/ 0xFB84
  , /*c8*/ 0xFEAB
  , /*c9*/ 0xFEAD
  , /*ca*/ 0xFB8C
  , /*cb*/ 0xFEAF
  , /*cc*/ 0xFB8A
  , /*cd*/ 0xFEB1
  , /*ce*/ 0xFEB3
  , /*cf*/ 0xFEB5
  , /*d0*/ 0xFEB7
  , /*d1*/ 0xFEB9
  , /*d2*/ 0xFEBB
  , /*d3*/ 0xFEBD
  , /*d4*/ 0xFEBF
  , /*d5*/ 0xFEC1
  , /*d6*/ 0xFEC5
  , /*d7*/ 0xFEC9
  , /*d8*/ 0xFECA
  , /*d9*/ 0xFECB
  , /*da*/ 0xFECC
  , /*db*/ 0xFECD
  , /*dc*/ 0xFECE
  , /*dd*/ 0xFECF
  , /*de*/ 0xFED0
  , /*df*/ 0xFED1
  , /*e0*/ 0xFED3
  , /*e1*/ 0xFED5
  , /*e2*/ 0xFED7
  , /*e3*/ 0xFED9
  , /*e4*/ 0xFEDB
  , /*e5*/ 0xFB92
  , /*e6*/ 0xFB94
  , /*e7*/ 0xFEDD
  , /*e8*/ 0xFEDF
  , /*e9*/ 0xFEE0
  , /*ea*/ 0xFEE1
  , /*eb*/ 0xFEE3
  , /*ec*/ 0xFB9E
  , /*ed*/ 0xFEE5
  , /*ee*/ 0xFEE7
  , /*ef*/ 0xFE85
  , /*f0*/ 0xFEED
  , /*f1*/ 0xFBA6
  , /*f2*/ 0xFBA8
  , /*f3*/ 0xFBA9
  , /*f4*/ 0xFBAA
  , /*f5*/ 0xFE80
  , /*f6*/ 0xFE89
  , /*f7*/ 0xFE8A
  , /*f8*/ 0xFE8B
  , /*f9*/ 0xFEF1
  , /*fa*/ 0xFEF2
  , /*fb*/ 0xFEF3
  , /*fc*/ 0xFBB0
  , /*fd*/ 0xFBAE
  , /*fe*/ 0xFE7C
  , /*ff*/ 0xFE7D
 };

CP_1006::CP_1006(void) : SBCodeConverter(1006,ua)
{}

#endif
