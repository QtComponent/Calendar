#include "LunarCalendar.h"

#define FROMLOCAL8BIT QString::fromLocal8Bit

/* 除夕等变化日另算 */
const QMap<QString,QString> m_lunarFestivalMap = {
    {FROMLOCAL8BIT("正月初一"),FROMLOCAL8BIT("春节")},
    {FROMLOCAL8BIT("正月十五"),FROMLOCAL8BIT("元宵节")},
    {FROMLOCAL8BIT("三月初三"),FROMLOCAL8BIT("上巳节")},
    {FROMLOCAL8BIT("五月初五"),FROMLOCAL8BIT("端午节")},
    {FROMLOCAL8BIT("七月初七"),FROMLOCAL8BIT("七夕节")},
    {FROMLOCAL8BIT("七月十五"),FROMLOCAL8BIT("中元节")},
    {FROMLOCAL8BIT("八月十五"),FROMLOCAL8BIT("中秋节")},
    {FROMLOCAL8BIT("九月初九"),FROMLOCAL8BIT("重阳节")},
    {FROMLOCAL8BIT("十月初一"),FROMLOCAL8BIT("寒衣节")},
    {FROMLOCAL8BIT("十月十五"),FROMLOCAL8BIT("下元节")},
    {FROMLOCAL8BIT("腊月初八"),FROMLOCAL8BIT("腊八节")},
    {FROMLOCAL8BIT("腊月廿三"),FROMLOCAL8BIT("祭灶节")},
};

const QStringList m_termList = {
    FROMLOCAL8BIT("小寒"),FROMLOCAL8BIT("大寒"),
    FROMLOCAL8BIT("立春"),FROMLOCAL8BIT("雨水"),
    FROMLOCAL8BIT("惊蛰"),FROMLOCAL8BIT("春分"),
    FROMLOCAL8BIT("清明"),FROMLOCAL8BIT("谷雨"),
    FROMLOCAL8BIT("立夏"),FROMLOCAL8BIT("小满"),
    FROMLOCAL8BIT("芒种"),FROMLOCAL8BIT("夏至"),
    FROMLOCAL8BIT("小暑"),FROMLOCAL8BIT("大暑"),
    FROMLOCAL8BIT("立秋"),FROMLOCAL8BIT("处暑"),
    FROMLOCAL8BIT("白露"),FROMLOCAL8BIT("秋分"),
    FROMLOCAL8BIT("寒露"),FROMLOCAL8BIT("霜降"),
    FROMLOCAL8BIT("立冬"),FROMLOCAL8BIT("小雪"),
    FROMLOCAL8BIT("大雪"),FROMLOCAL8BIT("冬至")
};

//1900-2100年节气表
const QStringList m_termsInfoList = {
    FROMLOCAL8BIT("9778397bd097c36b0b6fc9274c91aa"),FROMLOCAL8BIT("97b6b97bd19801ec9210c965cc920e"),FROMLOCAL8BIT("97bcf97c3598082c95f8c965cc920f"),
    FROMLOCAL8BIT("97bd0b06bdb0722c965ce1cfcc920f"),FROMLOCAL8BIT("b027097bd097c36b0b6fc9274c91aa"),FROMLOCAL8BIT("97b6b97bd19801ec9210c965cc920e"),
    FROMLOCAL8BIT("97bcf97c359801ec95f8c965cc920f"),FROMLOCAL8BIT("97bd0b06bdb0722c965ce1cfcc920f"),FROMLOCAL8BIT("b027097bd097c36b0b6fc9274c91aa"),
    FROMLOCAL8BIT("97b6b97bd19801ec9210c965cc920e"),FROMLOCAL8BIT("97bcf97c359801ec95f8c965cc920f"), FROMLOCAL8BIT("97bd0b06bdb0722c965ce1cfcc920f"),
    FROMLOCAL8BIT("b027097bd097c36b0b6fc9274c91aa"),FROMLOCAL8BIT("9778397bd19801ec9210c965cc920e"),FROMLOCAL8BIT("97b6b97bd19801ec95f8c965cc920f"),
    FROMLOCAL8BIT("97bd09801d98082c95f8e1cfcc920f"),FROMLOCAL8BIT("97bd097bd097c36b0b6fc9210c8dc2"),FROMLOCAL8BIT("9778397bd197c36c9210c9274c91aa"),
    FROMLOCAL8BIT("97b6b97bd19801ec95f8c965cc920e"),FROMLOCAL8BIT("97bd09801d98082c95f8e1cfcc920f"), FROMLOCAL8BIT("97bd097bd097c36b0b6fc9210c8dc2"),
    FROMLOCAL8BIT("9778397bd097c36c9210c9274c91aa"),FROMLOCAL8BIT("97b6b97bd19801ec95f8c965cc920e"),FROMLOCAL8BIT("97bcf97c3598082c95f8e1cfcc920f"),
    FROMLOCAL8BIT("97bd097bd097c36b0b6fc9210c8dc2"),FROMLOCAL8BIT("9778397bd097c36c9210c9274c91aa"),FROMLOCAL8BIT("97b6b97bd19801ec9210c965cc920e"),
    FROMLOCAL8BIT("97bcf97c3598082c95f8c965cc920f"),FROMLOCAL8BIT("97bd097bd097c35b0b6fc920fb0722"),FROMLOCAL8BIT("9778397bd097c36b0b6fc9274c91aa"),
    FROMLOCAL8BIT("97b6b97bd19801ec9210c965cc920e"),FROMLOCAL8BIT("97bcf97c3598082c95f8c965cc920f"), FROMLOCAL8BIT("97bd097bd097c35b0b6fc920fb0722"),
    FROMLOCAL8BIT("9778397bd097c36b0b6fc9274c91aa"),FROMLOCAL8BIT("97b6b97bd19801ec9210c965cc920e"),FROMLOCAL8BIT("97bcf97c359801ec95f8c965cc920f"),
    FROMLOCAL8BIT("97bd097bd097c35b0b6fc920fb0722"),FROMLOCAL8BIT("9778397bd097c36b0b6fc9274c91aa"),FROMLOCAL8BIT("97b6b97bd19801ec9210c965cc920e"),
    FROMLOCAL8BIT("97bcf97c359801ec95f8c965cc920f"),FROMLOCAL8BIT("97bd097bd097c35b0b6fc920fb0722"),FROMLOCAL8BIT("9778397bd097c36b0b6fc9274c91aa"),
    FROMLOCAL8BIT("97b6b97bd19801ec9210c965cc920e"),FROMLOCAL8BIT("97bcf97c359801ec95f8c965cc920f"), FROMLOCAL8BIT("97bd097bd07f595b0b6fc920fb0722"),
    FROMLOCAL8BIT("9778397bd097c36b0b6fc9210c8dc2"),FROMLOCAL8BIT("9778397bd19801ec9210c9274c920e"),FROMLOCAL8BIT("97b6b97bd19801ec95f8c965cc920f"),
    FROMLOCAL8BIT("97bd07f5307f595b0b0bc920fb0722"),FROMLOCAL8BIT("7f0e397bd097c36b0b6fc9210c8dc2"),FROMLOCAL8BIT("9778397bd097c36c9210c9274c920e"),
    FROMLOCAL8BIT("97b6b97bd19801ec95f8c965cc920f"),FROMLOCAL8BIT("97bd07f5307f595b0b0bc920fb0722"),FROMLOCAL8BIT("7f0e397bd097c36b0b6fc9210c8dc2"),
    FROMLOCAL8BIT("9778397bd097c36c9210c9274c91aa"),FROMLOCAL8BIT("97b6b97bd19801ec9210c965cc920e"),FROMLOCAL8BIT("97bd07f1487f595b0b0bc920fb0722"),
    FROMLOCAL8BIT("7f0e397bd097c36b0b6fc9210c8dc2"),FROMLOCAL8BIT("9778397bd097c36b0b6fc9274c91aa"),FROMLOCAL8BIT("97b6b97bd19801ec9210c965cc920e"),
    FROMLOCAL8BIT("97bcf7f1487f595b0b0bb0b6fb0722"),FROMLOCAL8BIT("7f0e397bd097c35b0b6fc920fb0722"), FROMLOCAL8BIT("9778397bd097c36b0b6fc9274c91aa"),
    FROMLOCAL8BIT("97b6b97bd19801ec9210c965cc920e"),FROMLOCAL8BIT("97bcf7f1487f595b0b0bb0b6fb0722"),FROMLOCAL8BIT("7f0e397bd097c35b0b6fc920fb0722"),
    FROMLOCAL8BIT("9778397bd097c36b0b6fc9274c91aa"),FROMLOCAL8BIT("97b6b97bd19801ec9210c965cc920e"),FROMLOCAL8BIT("97bcf7f1487f531b0b0bb0b6fb0722"),
    FROMLOCAL8BIT("7f0e397bd097c35b0b6fc920fb0722"),FROMLOCAL8BIT("9778397bd097c36b0b6fc9274c91aa"),FROMLOCAL8BIT("97b6b97bd19801ec9210c965cc920e"),
    FROMLOCAL8BIT("97bcf7f1487f531b0b0bb0b6fb0722"),FROMLOCAL8BIT("7f0e397bd07f595b0b6fc920fb0722"), FROMLOCAL8BIT("9778397bd097c36b0b6fc9274c91aa"),
    FROMLOCAL8BIT("97b6b97bd19801ec9210c9274c920e"),FROMLOCAL8BIT("97bcf7f0e47f531b0b0bb0b6fb0722"),FROMLOCAL8BIT("7f0e397bd07f595b0b0bc920fb0722"),
    FROMLOCAL8BIT("9778397bd097c36b0b6fc9210c91aa"),FROMLOCAL8BIT("97b6b97bd197c36c9210c9274c920e"),FROMLOCAL8BIT("97bcf7f0e47f531b0b0bb0b6fb0722"),
    FROMLOCAL8BIT("7f0e397bd07f595b0b0bc920fb0722"),FROMLOCAL8BIT("9778397bd097c36b0b6fc9210c8dc2"),FROMLOCAL8BIT("9778397bd097c36c9210c9274c920e"),
    FROMLOCAL8BIT("97b6b7f0e47f531b0723b0b6fb0722"),FROMLOCAL8BIT("7f0e37f5307f595b0b0bc920fb0722"), FROMLOCAL8BIT("7f0e397bd097c36b0b6fc9210c8dc2"),
    FROMLOCAL8BIT("9778397bd097c36b0b70c9274c91aa"),FROMLOCAL8BIT("97b6b7f0e47f531b0723b0b6fb0721"),FROMLOCAL8BIT("7f0e37f1487f595b0b0bb0b6fb0722"),
    FROMLOCAL8BIT("7f0e397bd097c35b0b6fc9210c8dc2"),FROMLOCAL8BIT("9778397bd097c36b0b6fc9274c91aa"),FROMLOCAL8BIT("97b6b7f0e47f531b0723b0b6fb0721"),
    FROMLOCAL8BIT("7f0e27f1487f595b0b0bb0b6fb0722"),FROMLOCAL8BIT("7f0e397bd097c35b0b6fc920fb0722"), FROMLOCAL8BIT("9778397bd097c36b0b6fc9274c91aa"),
    FROMLOCAL8BIT("97b6b7f0e47f531b0723b0b6fb0721"),FROMLOCAL8BIT("7f0e27f1487f531b0b0bb0b6fb0722"),FROMLOCAL8BIT("7f0e397bd097c35b0b6fc920fb0722"),
    FROMLOCAL8BIT("9778397bd097c36b0b6fc9274c91aa"),FROMLOCAL8BIT("97b6b7f0e47f531b0723b0b6fb0721"),FROMLOCAL8BIT("7f0e27f1487f531b0b0bb0b6fb0722"),
    FROMLOCAL8BIT("7f0e397bd097c35b0b6fc920fb0722"),FROMLOCAL8BIT("9778397bd097c36b0b6fc9274c91aa"),FROMLOCAL8BIT("97b6b7f0e47f531b0723b0b6fb0721"),
    FROMLOCAL8BIT("7f0e27f1487f531b0b0bb0b6fb0722"),FROMLOCAL8BIT("7f0e397bd07f595b0b0bc920fb0722"), FROMLOCAL8BIT("9778397bd097c36b0b6fc9274c91aa"),
    FROMLOCAL8BIT("97b6b7f0e47f531b0723b0787b0721"),FROMLOCAL8BIT("7f0e27f0e47f531b0b0bb0b6fb0722"),FROMLOCAL8BIT("7f0e397bd07f595b0b0bc920fb0722"),
    FROMLOCAL8BIT("9778397bd097c36b0b6fc9210c91aa"),FROMLOCAL8BIT("97b6b7f0e47f149b0723b0787b0721"),FROMLOCAL8BIT("7f0e27f0e47f531b0723b0b6fb0722"),
    FROMLOCAL8BIT("7f0e397bd07f595b0b0bc920fb0722"),FROMLOCAL8BIT("9778397bd097c36b0b6fc9210c8dc2"),FROMLOCAL8BIT("977837f0e37f149b0723b0787b0721"),
    FROMLOCAL8BIT("7f07e7f0e47f531b0723b0b6fb0722"),FROMLOCAL8BIT("7f0e37f5307f595b0b0bc920fb0722"),FROMLOCAL8BIT("7f0e397bd097c35b0b6fc9210c8dc2"),
    FROMLOCAL8BIT("977837f0e37f14998082b0787b0721"),FROMLOCAL8BIT("7f07e7f0e47f531b0723b0b6fb0721"),FROMLOCAL8BIT("7f0e37f1487f595b0b0bb0b6fb0722"),
    FROMLOCAL8BIT("7f0e397bd097c35b0b6fc9210c8dc2"),FROMLOCAL8BIT("977837f0e37f14998082b0787b06bd"),FROMLOCAL8BIT("7f07e7f0e47f531b0723b0b6fb0721"),
    FROMLOCAL8BIT("7f0e27f1487f531b0b0bb0b6fb0722"),FROMLOCAL8BIT("7f0e397bd097c35b0b6fc920fb0722"),FROMLOCAL8BIT("977837f0e37f14998082b0787b06bd"),
    FROMLOCAL8BIT("7f07e7f0e47f531b0723b0b6fb0721"),FROMLOCAL8BIT("7f0e27f1487f531b0b0bb0b6fb0722"),FROMLOCAL8BIT("7f0e397bd097c35b0b6fc920fb0722"),
    FROMLOCAL8BIT("977837f0e37f14998082b0787b06bd"),FROMLOCAL8BIT("7f07e7f0e47f531b0723b0b6fb0721"),FROMLOCAL8BIT("7f0e27f1487f531b0b0bb0b6fb0722"),
    FROMLOCAL8BIT("7f0e397bd07f595b0b0bc920fb0722"),FROMLOCAL8BIT("977837f0e37f14998082b0787b06bd"),FROMLOCAL8BIT("7f07e7f0e47f531b0723b0b6fb0721"),
    FROMLOCAL8BIT("7f0e27f1487f531b0b0bb0b6fb0722"),FROMLOCAL8BIT("7f0e397bd07f595b0b0bc920fb0722"), FROMLOCAL8BIT("977837f0e37f14998082b0787b06bd"),
    FROMLOCAL8BIT("7f07e7f0e47f149b0723b0787b0721"),FROMLOCAL8BIT("7f0e27f0e47f531b0b0bb0b6fb0722"),FROMLOCAL8BIT("7f0e397bd07f595b0b0bc920fb0722"),
    FROMLOCAL8BIT("977837f0e37f14998082b0723b06bd"),FROMLOCAL8BIT("7f07e7f0e37f149b0723b0787b0721"),FROMLOCAL8BIT("7f0e27f0e47f531b0723b0b6fb0722"),
    FROMLOCAL8BIT("7f0e397bd07f595b0b0bc920fb0722"),FROMLOCAL8BIT("977837f0e37f14898082b0723b02d5"),FROMLOCAL8BIT("7ec967f0e37f14998082b0787b0721"),
    FROMLOCAL8BIT("7f07e7f0e47f531b0723b0b6fb0722"),FROMLOCAL8BIT("7f0e37f1487f595b0b0bb0b6fb0722"),FROMLOCAL8BIT("7f0e37f0e37f14898082b0723b02d5"),
    FROMLOCAL8BIT("7ec967f0e37f14998082b0787b0721"),FROMLOCAL8BIT("7f07e7f0e47f531b0723b0b6fb0722"),FROMLOCAL8BIT("7f0e37f1487f531b0b0bb0b6fb0722"),
    FROMLOCAL8BIT("7f0e37f0e37f14898082b0723b02d5"),FROMLOCAL8BIT("7ec967f0e37f14998082b0787b06bd"),FROMLOCAL8BIT("7f07e7f0e47f531b0723b0b6fb0721"),
    FROMLOCAL8BIT("7f0e37f1487f531b0b0bb0b6fb0722"),FROMLOCAL8BIT("7f0e37f0e37f14898082b072297c35"),FROMLOCAL8BIT("7ec967f0e37f14998082b0787b06bd"),
    FROMLOCAL8BIT("7f07e7f0e47f531b0723b0b6fb0721"),FROMLOCAL8BIT("7f0e27f1487f531b0b0bb0b6fb0722"),FROMLOCAL8BIT("7f0e37f0e37f14898082b072297c35"),
    FROMLOCAL8BIT("7ec967f0e37f14998082b0787b06bd"),FROMLOCAL8BIT("7f07e7f0e47f531b0723b0b6fb0721"), FROMLOCAL8BIT("7f0e27f1487f531b0b0bb0b6fb0722"),
    FROMLOCAL8BIT("7f0e37f0e366aa89801eb072297c35"),FROMLOCAL8BIT("7ec967f0e37f14998082b0787b06bd"),FROMLOCAL8BIT("7f07e7f0e47f149b0723b0787b0721"),
    FROMLOCAL8BIT("7f0e27f1487f531b0b0bb0b6fb0722"),FROMLOCAL8BIT("7f0e37f0e366aa89801eb072297c35"),FROMLOCAL8BIT("7ec967f0e37f14998082b0723b06bd"),
    FROMLOCAL8BIT("7f07e7f0e47f149b0723b0787b0721"),FROMLOCAL8BIT("7f0e27f0e47f531b0723b0b6fb0722"),FROMLOCAL8BIT("7f0e37f0e366aa89801eb072297c35"),
    FROMLOCAL8BIT("7ec967f0e37f14998082b0723b06bd"),FROMLOCAL8BIT("7f07e7f0e37f14998083b0787b0721"),FROMLOCAL8BIT("7f0e27f0e47f531b0723b0b6fb0722"),
    FROMLOCAL8BIT("7f0e37f0e366aa89801eb072297c35"),FROMLOCAL8BIT("7ec967f0e37f14898082b0723b02d5"),FROMLOCAL8BIT("7f07e7f0e37f14998082b0787b0721"),
    FROMLOCAL8BIT("7f07e7f0e47f531b0723b0b6fb0722"),FROMLOCAL8BIT("7f0e36665b66aa89801e9808297c35"), FROMLOCAL8BIT("665f67f0e37f14898082b0723b02d5"),
    FROMLOCAL8BIT("7ec967f0e37f14998082b0787b0721"),FROMLOCAL8BIT("7f07e7f0e47f531b0723b0b6fb0722"), FROMLOCAL8BIT("7f0e36665b66a449801e9808297c35"),
    FROMLOCAL8BIT("665f67f0e37f14898082b0723b02d5"),FROMLOCAL8BIT("7ec967f0e37f14998082b0787b06bd"),FROMLOCAL8BIT("7f07e7f0e47f531b0723b0b6fb0721"),
    FROMLOCAL8BIT("7f0e36665b66a449801e9808297c35"),FROMLOCAL8BIT("665f67f0e37f14898082b072297c35"), FROMLOCAL8BIT("7ec967f0e37f14998082b0787b06bd"),
    FROMLOCAL8BIT("7f07e7f0e47f531b0723b0b6fb0721"),FROMLOCAL8BIT("7f0e26665b66a449801e9808297c35"), FROMLOCAL8BIT("665f67f0e37f1489801eb072297c35"),
    FROMLOCAL8BIT("7ec967f0e37f14998082b0787b06bd"),FROMLOCAL8BIT("7f07e7f0e47f531b0723b0b6fb0721"), FROMLOCAL8BIT("7f0e27f1487f531b0b0bb0b6fb0722"),
};

 /* max 有效性判断 */
const QDate m_maxDate(2099,12,31);

/* min 有效性判断 */
const QDate m_minDate(1901,1,1);

const QStringList m_lunarDList = {FROMLOCAL8BIT("*"),
                             FROMLOCAL8BIT("初一"),
                             FROMLOCAL8BIT("初二"),
                             FROMLOCAL8BIT("初三"),
                             FROMLOCAL8BIT("初四"),
                             FROMLOCAL8BIT("初五"),
                             FROMLOCAL8BIT("初六"),
                             FROMLOCAL8BIT("初七"),
                             FROMLOCAL8BIT("初八"),
                             FROMLOCAL8BIT("初九"),
                             FROMLOCAL8BIT("初十"),
                             FROMLOCAL8BIT("十一"),
                             FROMLOCAL8BIT("十二"),
                             FROMLOCAL8BIT("十三"),
                             FROMLOCAL8BIT("十四"),
                             FROMLOCAL8BIT("十五"),
                             FROMLOCAL8BIT("十六"),
                             FROMLOCAL8BIT("十七"),
                             FROMLOCAL8BIT("十八"),
                             FROMLOCAL8BIT("十九"),
                             FROMLOCAL8BIT("二十"),
                             FROMLOCAL8BIT("廿一"),
                             FROMLOCAL8BIT("廿二"),
                             FROMLOCAL8BIT("廿三"),
                             FROMLOCAL8BIT("廿四"),
                             FROMLOCAL8BIT("廿五"),
                             FROMLOCAL8BIT("廿六"),
                             FROMLOCAL8BIT("廿七"),
                             FROMLOCAL8BIT("廿八"),
                             FROMLOCAL8BIT("廿九"),
                             FROMLOCAL8BIT("三十")
                            };

const QStringList m_lunarMList = {FROMLOCAL8BIT("*"),
                               FROMLOCAL8BIT("正"),
                               FROMLOCAL8BIT("二"),
                               FROMLOCAL8BIT("三"),
                               FROMLOCAL8BIT("四"),
                               FROMLOCAL8BIT("五"),
                               FROMLOCAL8BIT("六"),
                               FROMLOCAL8BIT("七"),
                               FROMLOCAL8BIT("八"),
                               FROMLOCAL8BIT("九"),
                               FROMLOCAL8BIT("十"),
                               FROMLOCAL8BIT("十一"),
                               FROMLOCAL8BIT("腊")
                              };
/*天干名称*/
const QStringList m_celestialStem = {
    FROMLOCAL8BIT("甲"),
    FROMLOCAL8BIT("乙"),
    FROMLOCAL8BIT("丙"),
    FROMLOCAL8BIT("丁"),
    FROMLOCAL8BIT("戊"),
    FROMLOCAL8BIT("己"),
    FROMLOCAL8BIT("庚"),
    FROMLOCAL8BIT("辛"),
    FROMLOCAL8BIT("壬"),
    FROMLOCAL8BIT("癸")
};

/*地支名称*/
const QStringList m_terrestrialBranch = {
    FROMLOCAL8BIT("子"),FROMLOCAL8BIT("丑"),
    FROMLOCAL8BIT("寅"),FROMLOCAL8BIT("卯"),
    FROMLOCAL8BIT("辰"),FROMLOCAL8BIT("巳"),
    FROMLOCAL8BIT("午"),FROMLOCAL8BIT("未"),
    FROMLOCAL8BIT("申"),FROMLOCAL8BIT("酉"),
    FROMLOCAL8BIT("戌"),FROMLOCAL8BIT("亥")
};

/*属相名称*/
const QStringList m_animal = {
    FROMLOCAL8BIT("鼠"),FROMLOCAL8BIT("牛"),
    FROMLOCAL8BIT("虎"),FROMLOCAL8BIT("兔"),
    FROMLOCAL8BIT("龙"),FROMLOCAL8BIT("蛇"),
    FROMLOCAL8BIT("马"),FROMLOCAL8BIT("羊"),
    FROMLOCAL8BIT("猴"),FROMLOCAL8BIT("鸡"),
    FROMLOCAL8BIT("狗"),FROMLOCAL8BIT("猪")
};

const unsigned int m_lunarCalendarTable[199] = { //年份特征值
                                                 0x04AE53,0x0A5748,0x5526BD,0x0D2650,0x0D9544,0x46AAB9,0x056A4D,0x09AD42,0x24AEB6,0x04AE4A,/*1901-1910*/
                                                 0x6A4DBE,0x0A4D52,0x0D2546,0x5D52BA,0x0B544E,0x0D6A43,0x296D37,0x095B4B,0x749BC1,0x049754,/*1911-1920*/
                                                 0x0A4B48,0x5B25BC,0x06A550,0x06D445,0x4ADAB8,0x02B64D,0x095742,0x2497B7,0x04974A,0x664B3E,/*1921-1930*/
                                                 0x0D4A51,0x0EA546,0x56D4BA,0x05AD4E,0x02B644,0x393738,0x092E4B,0x7C96BF,0x0C9553,0x0D4A48,/*1931-1940*/
                                                 0x6DA53B,0x0B554F,0x056A45,0x4AADB9,0x025D4D,0x092D42,0x2C95B6,0x0A954A,0x7B4ABD,0x06CA51,/*1941-1950*/
                                                 0x0B5546,0x555ABB,0x04DA4E,0x0A5B43,0x352BB8,0x052B4C,0x8A953F,0x0E9552,0x06AA48,0x6AD53C,/*1951-1960*/
                                                 0x0AB54F,0x04B645,0x4A5739,0x0A574D,0x052642,0x3E9335,0x0D9549,0x75AABE,0x056A51,0x096D46,/*1961-1970*/
                                                 0x54AEBB,0x04AD4F,0x0A4D43,0x4D26B7,0x0D254B,0x8D52BF,0x0B5452,0x0B6A47,0x696D3C,0x095B50,/*1971-1980*/
                                                 0x049B45,0x4A4BB9,0x0A4B4D,0xAB25C2,0x06A554,0x06D449,0x6ADA3D,0x0AB651,0x095746,0x5497BB,/*1981-1990*/
                                                 0x04974F,0x064B44,0x36A537,0x0EA54A,0x86B2BF,0x05AC53,0x0AB647,0x5936BC,0x092E50,0x0C9645,/*1991-2000*/
                                                 0x4D4AB8,0x0D4A4C,0x0DA541,0x25AAB6,0x056A49,0x7AADBD,0x025D52,0x092D47,0x5C95BA,0x0A954E,/*2001-2010*/
                                                 0x0B4A43,0x4B5537,0x0AD54A,0x955ABF,0x04BA53,0x0A5B48,0x652BBC,0x052B50,0x0A9345,0x474AB9,/*2011-2020*/
                                                 0x06AA4C,0x0AD541,0x24DAB6,0x04B64A,0x69573D,0x0A4E51,0x0D2646,0x5E933A,0x0D534D,0x05AA43,/*2021-2030*/
                                                 0x36B537,0x096D4B,0xB4AEBF,0x04AD53,0x0A4D48,0x6D25BC,0x0D254F,0x0D5244,0x5DAA38,0x0B5A4C,/*2031-2040*/
                                                 0x056D41,0x24ADB6,0x049B4A,0x7A4BBE,0x0A4B51,0x0AA546,0x5B52BA,0x06D24E,0x0ADA42,0x355B37,/*2041-2050*/
                                                 0x09374B,0x8497C1,0x049753,0x064B48,0x66A53C,0x0EA54F,0x06B244,0x4AB638,0x0AAE4C,0x092E42,/*2051-2060*/
                                                 0x3C9735,0x0C9649,0x7D4ABD,0x0D4A51,0x0DA545,0x55AABA,0x056A4E,0x0A6D43,0x452EB7,0x052D4B,/*2061-2070*/
                                                 0x8A95BF,0x0A9553,0x0B4A47,0x6B553B,0x0AD54F,0x055A45,0x4A5D38,0x0A5B4C,0x052B42,0x3A93B6,/*2071-2080*/
                                                 0x069349,0x7729BD,0x06AA51,0x0AD546,0x54DABA,0x04B64E,0x0A5743,0x452738,0x0D264A,0x8E933E,/*2081-2090*/
                                                 0x0D5252,0x0DAA47,0x66B53B,0x056D4F,0x04AE45,0x4A4EB9,0x0A4D4C,0x0D1541,0x2D92B5          /*2091-2099*/
                                               };

/* 月天数特征值 */
const int m_monthDayCharacteristics[12] = {0,31,59,90,120,151,181,212,243,273,304,334};

LunarCalendar::LunarCalendar(QObject *parent) : QObject(parent)
{
    init();
}

void LunarCalendar::init()
{
    m_lunarMD = "";
    m_lunarM = "";
    m_lunarD = "";
    m_lunarYear = "";
    m_lunarMonth = "";
    m_lunarDay = "";
    m_lunarTerms = "";
    m_lunarFestival = "";
    m_festivals.clear();
    m_festival = "";
    m_isFestival = false;
}

void LunarCalendar::getLunarDate(QDate date)
{
    bool success = _getLunarDay(date,
                                m_lunarMD,
                                m_lunarM,
                                m_lunarD,
                                m_lunarYear,
                                m_lunarMonth,
                                m_lunarDay,
                                m_lunarTerms,
                                m_lunarFestival);
    if (!success) {
        init();
        qDebug()<<"GetLunarDate failed!";
    }
    else {
        m_festivals.clear();
        m_festivals.append(this->getChinaAndWestFestival(date));
        if (m_lunarFestival != "")
            m_festivals.append(m_lunarFestival);

        if (m_lunarTerms != "")
            m_festivals.append(m_lunarTerms);

        if (m_lunarD != "")
            m_festivals.append(m_lunarD);
        if (m_festivals.count() > 1) {
            m_isFestival = true;
            m_festival = m_festivals.at(0);
        }
        else {
            m_isFestival = false;
            m_festival = "";
        }
    }

    emit statusChanged();
}

bool LunarCalendar::_getSolarTerms(QDate date,
                                   unsigned int &a1,
                                   unsigned int &a2){
    //确定日期有效性
    if((!date.isValid())||(date < m_minDate)||(date > m_maxDate)) return false;
    int year  = date.year();
    int month = date.month();

    QString Info = m_termsInfoList[year - 1900];
    bool ok = false;
    QString Info1 = Info.mid(((month-1)/2)*5,5);
    unsigned int t = Info1.toInt(&ok,16);
    if(!ok) return ok;
    QString m2;
    m2.setNum(t);
    m2 = m2.mid(((month%2)?0:1)*3,3);
    a1 = m2.mid(0,1).toInt(&ok);
    if(!ok) return ok;
    a2 = m2.mid(1,2).toInt(&ok);
    return  ok;
}

bool LunarCalendar::_getLunarDay(QDate date,                 /* 公历日期 */
                                 QString &outLunarMD,        /* 农历: xx月xx日 */
                                 QString &outLunarM,         /* 农历: xx月 */
                                 QString &outLunarD,         /* 农历: xx日 */
                                 QString &outLunarYear,      /* 农历：天支年[属相]*/
                                 QString &outLunarMonth,     /* 农历：天支月 */
                                 QString &outLunarDay,       /* 农历：天支日 */
                                 QString &outLunarTerms,     /* 二十四节气 */
                                 QString &outLunarFestival)  /* 农历节日 */
{


    //确定日期有效性
    if((!date.isValid())||(date < m_minDate)||(date > m_maxDate))
        return false;

    /* 计算用 */
    unsigned int lunarCalendarDay = 0;

    int year  = date.year();

    int month = date.month();

    int day = date.day();

    /* spring_NY 记录春节离当年元旦的天数。 */
    int spring_NY = 0;

    /* sun_NY 记录阳历日离当年元旦的天数。*/
    int sun_NY = 0;
    int staticDayCount = 0;

    int index = 0;

    int flag = 0;

    /* 实际计算的月次数，用于区分闰月的第一个月份 */
    int monthCount = 1;
    unsigned int sa1,sa2;
    int nTheMonth;

    /* 计算二十四节气 */
    _getSolarTerms(date,sa1,sa2);
    if(day>=(int)sa1){
        nTheMonth = (year- 1901) * 12 - 2 + month;
    }else{
        nTheMonth = (year- 1901) * 12 - 2 + month -1;
    }
    outLunarMonth = m_celestialStem[(nTheMonth + 6) % 10] + m_terrestrialBranch[(nTheMonth + 2) % 12] + FROMLOCAL8BIT("月");

    /*---计算到初始时间1900年1月31日的天数：1921-1-31(正月初一)---*/
    int nTheDate = abs(date.daysTo(QDate(1900,1,30))); //(year - 1900) *365 + (year - 1900)/4  + mMonthAdd[month - 1] + day - 30;
    //if((!(year % 4)) && (month > 2)) nTheDate = nTheDate + 1;
    outLunarDay = m_celestialStem[(nTheDate + 9) % 10] + m_terrestrialBranch[(nTheDate + 3) % 12]+ FROMLOCAL8BIT("日");

    if( ((m_lunarCalendarTable[year-1901] & 0x0060) >> 5) == 1)
        spring_NY = (m_lunarCalendarTable[year-1901] & 0x001F) - 1;
    else
        spring_NY = (m_lunarCalendarTable[year-1901] & 0x001F) - 1 + 31;

    sun_NY = m_monthDayCharacteristics[month-1] + day - 1;

    if( (!(year % 4)) && (month > 2))
        sun_NY++;

    //staticDayCount记录大小月的天数 29 或30
    //index 记录从哪个月开始来计算。
    //flag 是用来对闰月的特殊处理。


    //判断阳历日在春节前还是春节后
    if (sun_NY >= spring_NY)//阳历日在春节后（含春节那天）
    {
        sun_NY -= spring_NY;
        month = 1;
        index = 1;
        flag = 0;
        if( ( m_lunarCalendarTable[year - 1901] & (0x80000 >> (index-1)) ) ==0)
            staticDayCount = 29;
        else
            staticDayCount = 30;
        while(sun_NY >= staticDayCount)
        {
            sun_NY -= staticDayCount;
            index++;
            if(month == (int)((m_lunarCalendarTable[year - 1901] & 0xF00000) >> 20))
            {
                flag = ~flag;
                if(flag == 0)
                    month++;
            }
            else
                month++;
            if( ( m_lunarCalendarTable[year - 1901] & (0x80000 >> (index-1)) ) ==0)
                staticDayCount=29;
            else
                staticDayCount=30;
            monthCount++;
        }
        day = sun_NY + 1;
    }
    else//阳历日在春节前
    {
        spring_NY -= sun_NY;
        year--;
        month = 12;
        if(year>=1901){     //仅处理1901年1月
            if ( ((m_lunarCalendarTable[year - 1901] & 0xF00000) >> 20) == 0)
                index = 12;
            else
                index = 13;
            flag = 0;
            if( ( m_lunarCalendarTable[year - 1901] & (0x80000 >> (index-1)) ) ==0)
                staticDayCount = 29;
            else
                staticDayCount = 30;
        }else{
            index = 12;
            staticDayCount = 30;
        }
        while(spring_NY > staticDayCount)
        {
            spring_NY -= staticDayCount;
            index--;
            if(flag == 0)
                month--;
            if(month == (int)((m_lunarCalendarTable[year - 1901] & 0xF00000) >> 20))
                flag = ~flag;
            if( ( m_lunarCalendarTable[year - 1901] & (0x80000 >> (index-1)) ) ==0)
                staticDayCount = 29;
            else
                staticDayCount = 30;
            monthCount++;
        }
        day = staticDayCount - spring_NY + 1;
    }

    outLunarYear = m_celestialStem[((year - 4) % 60) % 10] +\
            m_terrestrialBranch[((year - 4) % 60) % 12] +\
            FROMLOCAL8BIT("年 【") +\
            m_animal[((year - 4) % 60) % 12] +\
            FROMLOCAL8BIT("年】");

    lunarCalendarDay |= day;
    lunarCalendarDay |= (month << 6);

    if((month == (int)((m_lunarCalendarTable[year - 1901] & 0xF00000) >> 20))&&(month!=monthCount)){
        outLunarMD = FROMLOCAL8BIT("闰");
        outLunarMD.append(m_lunarMList[(lunarCalendarDay & 0x3C0) >> 6]);
    }else{
        outLunarMD = m_lunarMList[(lunarCalendarDay & 0x3C0) >> 6];
    }
    outLunarMD.append(FROMLOCAL8BIT("月"));
    outLunarM = outLunarMD;
    outLunarD = m_lunarDList[lunarCalendarDay & 0x3F];
    outLunarMD.append(outLunarD);
    outLunarTerms.clear();
    outLunarFestival.clear();
    if( date.day()==(int)sa1){
        outLunarTerms.append(m_termList[(date.month()-1)*2]);
    }
    if( date.day()==(int)sa2){
        outLunarTerms.append(m_termList[(date.month()-1)*2 + 1]);
    }
    if((staticDayCount==29)&&(outLunarMD==FROMLOCAL8BIT("腊月廿九"))){
        outLunarFestival.append(FROMLOCAL8BIT("除夕"));
    }
    if((staticDayCount==30)&&(outLunarMD==FROMLOCAL8BIT("腊月三十"))){
        outLunarFestival.append(FROMLOCAL8BIT("除夕"));
    }
    if((date.day()==(int)(sa1-1))&&(date.month()==4)){
        outLunarFestival.append(FROMLOCAL8BIT("寒食节"));
    }
    outLunarFestival.append(m_lunarFestivalMap[outLunarMD]);
    return true;
}

QStringList LunarCalendar::getChinaAndWestFestival(QDate date)
{
    int month = date.month(), day = date.day();
    int temp = (month << 8) | day;

    QStringList chinaAndWestFestival;
    chinaAndWestFestival.clear();

    switch (temp) {
    case 0x0101: chinaAndWestFestival.append(FROMLOCAL8BIT("元旦"));  break;
    case 0x020E: chinaAndWestFestival.append(FROMLOCAL8BIT("情人节")); break;
    case 0x0308: chinaAndWestFestival.append(FROMLOCAL8BIT("妇女节")); break;
    case 0x0401: chinaAndWestFestival.append(FROMLOCAL8BIT("愚人节")); break;
    case 0x0501: chinaAndWestFestival.append(FROMLOCAL8BIT("劳动节")); break;
    case 0x0504: chinaAndWestFestival.append(FROMLOCAL8BIT("青年节")); break;
    case 0x0601: chinaAndWestFestival.append(FROMLOCAL8BIT("儿童节")); break;
    case 0x0701: chinaAndWestFestival.append(FROMLOCAL8BIT("建党节")); break;
    case 0x0801: chinaAndWestFestival.append(FROMLOCAL8BIT("建军节")); break;
    case 0x090A: chinaAndWestFestival.append(FROMLOCAL8BIT("教师节")); break;
    case 0x0A01: chinaAndWestFestival.append(FROMLOCAL8BIT("国庆节")); break;
    case 0x0C18: chinaAndWestFestival.append(FROMLOCAL8BIT("圣诞节")); break;
    default: break;
    }

    if (isEasterDay(date))
        chinaAndWestFestival.append(FROMLOCAL8BIT("复活节"));

    if (isMothersDay(date))
        chinaAndWestFestival.append(FROMLOCAL8BIT("母亲节"));

    if (isFathersDay(date))
        chinaAndWestFestival.append(FROMLOCAL8BIT("父亲节"));

    if (isThanksgivingDay(date))
        chinaAndWestFestival.append(FROMLOCAL8BIT("感恩节"));

    return chinaAndWestFestival;
}

bool LunarCalendar::isEasterDay(QDate date)
{
    int offset;
    int leap;
    int day;
    int day1;
    int month;
    int year = date.year();
    int temp1;
    int temp2;
    int temp3;
    int total;

    offset = year - 1900;
    leap = offset % 19;
    day1 = offset / 4;
    temp1 = (7 * leap + 1)/19;
    temp2 = (11 * leap + 4 - temp1)%29;
    temp3 = (offset + day1 + 31 - temp2)%7;
    total = 25 - temp2 - temp3;

    if (total > 0) {
        month = 4;
        day = total ;
    }
    else {
        if (total == 0) {
            month = 3;
            day = 31;
        }
        else {
            month = 3;
            day = 31+total;
        }

    }

    QDate easterDay = QDate(year, month, day);

    return easterDay == date;
}

/* 每年5月份的第2个星期日 */
bool LunarCalendar::isMothersDay(QDate date)
{
    return isDay(date, 5, 2, 7);
}

/* 每年6月份的第3个星期日 */
bool LunarCalendar::isFathersDay(QDate date)
{
    return isDay(date, 6, 3, 7);
}

/* 每年11月最后一个星期四 */
bool LunarCalendar::isThanksgivingDay(QDate date)
{
    if (date.month() != 11)
        return false;

    QDate startDate(date.year(), date.month(), date.daysInMonth());
    QDate endDate(date.year(), date.month(), 1);
    for (; startDate >= endDate; startDate = startDate.addDays(-1)) {
        /* Returns the weekday (1 = Monday to 7 = Sunday) for this date. */
        if (startDate.dayOfWeek() == 4) {
            break;
        }
    }

    return startDate == date;
}

bool LunarCalendar::isDay(QDate targetDate, int month, int weekOfMonth, int week)
{
    QDate date = targetDate;
    if (date.month() != month)
        return false;

    int weekFlag = 0;
    QDate endDate(date.year(), date.month(), date.daysInMonth());
    QDate startDate(date.year(), date.month(), 1);
    for (; startDate <= endDate; startDate = startDate.addDays(1)) {
        /* Returns the weekday (1 = Monday to 7 = Sunday) for this date. */
        if (startDate.dayOfWeek() == week) {
            weekFlag++;
            if (weekFlag == weekOfMonth)
                break;
        }
    }

    return startDate == date;
}
