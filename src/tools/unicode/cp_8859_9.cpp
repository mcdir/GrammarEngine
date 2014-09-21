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
  , /*a1*/ 0x00A1
  , /*a2*/ 0x00A2
  , /*a3*/ 0x00A3
  , /*a4*/ 0x00A4
  , /*a5*/ 0x00A5
  , /*a6*/ 0x00A6
  , /*a7*/ 0x00A7
  , /*a8*/ 0x00A8
  , /*a9*/ 0x00A9
  , /*aa*/ 0x00AA
  , /*ab*/ 0x00AB
  , /*ac*/ 0x00AC
  , /*ad*/ 0x00AD
  , /*ae*/ 0x00AE
  , /*af*/ 0x00AF
  , /*b0*/ 0x00B0
  , /*b1*/ 0x00B1
  , /*b2*/ 0x00B2
  , /*b3*/ 0x00B3
  , /*b4*/ 0x00B4
  , /*b5*/ 0x00B5
  , /*b6*/ 0x00B6
  , /*b7*/ 0x00B7
  , /*b8*/ 0x00B8
  , /*b9*/ 0x00B9
  , /*ba*/ 0x00BA
  , /*bb*/ 0x00BB
  , /*bc*/ 0x00BC
  , /*bd*/ 0x00BD
  , /*be*/ 0x00BE
  , /*bf*/ 0x00BF
  , /*c0*/ 0x00C0
  , /*c1*/ 0x00C1
  , /*c2*/ 0x00C2
  , /*c3*/ 0x00C3
  , /*c4*/ 0x00C4
  , /*c5*/ 0x00C5
  , /*c6*/ 0x00C6
  , /*c7*/ 0x00C7
  , /*c8*/ 0x00C8
  , /*c9*/ 0x00C9
  , /*ca*/ 0x00CA
  , /*cb*/ 0x00CB
  , /*cc*/ 0x00CC
  , /*cd*/ 0x00CD
  , /*ce*/ 0x00CE
  , /*cf*/ 0x00CF
  , /*d0*/ 0x011E
  , /*d1*/ 0x00D1
  , /*d2*/ 0x00D2
  , /*d3*/ 0x00D3
  , /*d4*/ 0x00D4
  , /*d5*/ 0x00D5
  , /*d6*/ 0x00D6
  , /*d7*/ 0x00D7
  , /*d8*/ 0x00D8
  , /*d9*/ 0x00D9
  , /*da*/ 0x00DA
  , /*db*/ 0x00DB
  , /*dc*/ 0x00DC
  , /*dd*/ 0x0130
  , /*de*/ 0x015E
  , /*df*/ 0x00DF
  , /*e0*/ 0x00E0
  , /*e1*/ 0x00E1
  , /*e2*/ 0x00E2
  , /*e3*/ 0x00E3
  , /*e4*/ 0x00E4
  , /*e5*/ 0x00E5
  , /*e6*/ 0x00E6
  , /*e7*/ 0x00E7
  , /*e8*/ 0x00E8
  , /*e9*/ 0x00E9
  , /*ea*/ 0x00EA
  , /*eb*/ 0x00EB
  , /*ec*/ 0x00EC
  , /*ed*/ 0x00ED
  , /*ee*/ 0x00EE
  , /*ef*/ 0x00EF
  , /*f0*/ 0x011F
  , /*f1*/ 0x00F1
  , /*f2*/ 0x00F2
  , /*f3*/ 0x00F3
  , /*f4*/ 0x00F4
  , /*f5*/ 0x00F5
  , /*f6*/ 0x00F6
  , /*f7*/ 0x00F7
  , /*f8*/ 0x00F8
  , /*f9*/ 0x00F9
  , /*fa*/ 0x00FA
  , /*fb*/ 0x00FB
  , /*fc*/ 0x00FC
  , /*fd*/ 0x0131
  , /*fe*/ 0x015F
  , /*ff*/ 0x00FF
 };

CP_8859_9::CP_8859_9(void) : SBCodeConverter(28599,ua)
{}

#endif
