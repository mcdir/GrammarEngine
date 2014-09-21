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
  , /*80*/ 0x20AC
  , /*81*/ 0x0000
  , /*82*/ 0x0000
  , /*83*/ 0x0000
  , /*84*/ 0x0000
  , /*85*/ 0x2026
  , /*86*/ 0x0000
  , /*87*/ 0x0000
  , /*88*/ 0x0000
  , /*89*/ 0x0000
  , /*8a*/ 0x0000
  , /*8b*/ 0x0000
  , /*8c*/ 0x0000
  , /*8d*/ 0x0000
  , /*8e*/ 0x0000
  , /*8f*/ 0x0000
  , /*90*/ 0x0000
  , /*91*/ 0x0000
  , /*92*/ 0x2019
  , /*93*/ 0x201C
  , /*94*/ 0x201D
  , /*95*/ 0x2022
  , /*96*/ 0x2013
  , /*97*/ 0x2014
  , /*98*/ 0x0000
  , /*99*/ 0x0000
  , /*9a*/ 0x0000
  , /*9b*/ 0x0000
  , /*9c*/ 0x0000
  , /*9d*/ 0x0000
  , /*9e*/ 0x0000
  , /*9f*/ 0x0000
  , /*a0*/ 0x00A0
  , /*a1*/ 0x0E01
  , /*a2*/ 0x0E02
  , /*a3*/ 0x0E03
  , /*a4*/ 0x0E04
  , /*a5*/ 0x0E05
  , /*a6*/ 0x0E06
  , /*a7*/ 0x0E07
  , /*a8*/ 0x0E08
  , /*a9*/ 0x0E09
  , /*aa*/ 0x0E0A
  , /*ab*/ 0x0E0B
  , /*ac*/ 0x0E0C
  , /*ad*/ 0x0E0D
  , /*ae*/ 0x0E0E
  , /*af*/ 0x0E0F
  , /*b0*/ 0x0E10
  , /*b1*/ 0x0E11
  , /*b2*/ 0x0E12
  , /*b3*/ 0x0E13
  , /*b4*/ 0x0E14
  , /*b5*/ 0x0E15
  , /*b6*/ 0x0E16
  , /*b7*/ 0x0E17
  , /*b8*/ 0x0E18
  , /*b9*/ 0x0E19
  , /*ba*/ 0x0E1A
  , /*bb*/ 0x0E1B
  , /*bc*/ 0x0E1C
  , /*bd*/ 0x0E1D
  , /*be*/ 0x0E1E
  , /*bf*/ 0x0E1F
  , /*c0*/ 0x0E20
  , /*c1*/ 0x0E21
  , /*c2*/ 0x0E22
  , /*c3*/ 0x0E23
  , /*c4*/ 0x0E24
  , /*c5*/ 0x0E25
  , /*c6*/ 0x0E26
  , /*c7*/ 0x0E27
  , /*c8*/ 0x0E28
  , /*c9*/ 0x0E29
  , /*ca*/ 0x0E2A
  , /*cb*/ 0x0E2B
  , /*cc*/ 0x0E2C
  , /*cd*/ 0x0E2D
  , /*ce*/ 0x0E2E
  , /*cf*/ 0x0E2F
  , /*d0*/ 0x0E30
  , /*d1*/ 0x0E31
  , /*d2*/ 0x0E32
  , /*d3*/ 0x0E33
  , /*d4*/ 0x0E34
  , /*d5*/ 0x0E35
  , /*d6*/ 0x0E36
  , /*d7*/ 0x0E37
  , /*d8*/ 0x0E38
  , /*d9*/ 0x0E39
  , /*da*/ 0x0E3A
  , /*db*/ 0x0000
  , /*dc*/ 0x0000
  , /*dd*/ 0x0000
  , /*de*/ 0x0000
  , /*df*/ 0x0E3F
  , /*e0*/ 0x0E40
  , /*e1*/ 0x0E41
  , /*e2*/ 0x0E42
  , /*e3*/ 0x0E43
  , /*e4*/ 0x0E44
  , /*e5*/ 0x0E45
  , /*e6*/ 0x0E46
  , /*e7*/ 0x0E47
  , /*e8*/ 0x0E48
  , /*e9*/ 0x0E49
  , /*ea*/ 0x0E4A
  , /*eb*/ 0x0E4B
  , /*ec*/ 0x0E4C
  , /*ed*/ 0x0E4D
  , /*ee*/ 0x0E4E
  , /*ef*/ 0x0E4F
  , /*f0*/ 0x0E50
  , /*f1*/ 0x0E51
  , /*f2*/ 0x0E52
  , /*f3*/ 0x0E53
  , /*f4*/ 0x0E54
  , /*f5*/ 0x0E55
  , /*f6*/ 0x0E56
  , /*f7*/ 0x0E57
  , /*f8*/ 0x0E58
  , /*f9*/ 0x0E59
  , /*fa*/ 0x0E5A
  , /*fb*/ 0x0E5B
  , /*fc*/ 0x0000
  , /*fd*/ 0x0000
  , /*fe*/ 0x0000
 };

CP_874::CP_874(void) : SBCodeConverter(874,ua)
{}

#endif
