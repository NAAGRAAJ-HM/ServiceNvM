/******************************************************************************/
/* File   : Table.cpp                                                         */
/* Author : Nagaraja HULIYAPURADA-MATA                                        */
/* Date   : 01.02.1982                                                        */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "types.hpp"

#include "Table.hpp"

#include "Mat.hpp" //TBD: remove
#include "ApplSwcFoc_tbd.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define  Table_lScale(Value) ((uint16)((((float)Value) * EMO_CFG_FOC_TABLE_SCALE) + 0.5))

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
const sint16 Table_Sin[TABLE_SIZE_SIN_COS + (TABLE_SIZE_SIN_COS / 4u)] ={
          0,    201,    402,    603,    804,   1005,   1206,   1407
   ,   1608,   1809,   2009,   2210,   2411,   2611,   2811,   3012
   ,   3212,   3412,   3612,   3812,   4011,   4211,   4410,   4609
   ,   4808,   5007,   5205,   5404,   5602,   5800,   5998,   6195
   ,   6393,   6590,   6787,   6983,   7180,   7376,   7571,   7767
   ,   7962,   8157,   8351,   8546,   8740,   8933,   9127,   9319
   ,   9512,   9704,   9896,  10088,  10279,  10469,  10660,  10850
   ,  11039,  11228,  11417,  11605,  11793,  11980,  12167,  12354
   ,  12540,  12725,  12910,  13095,  13279,  13463,  13646,  13828
   ,  14010,  14192,  14373,  14553,  14733,  14912,  15091,  15269
   ,  15447,  15624,  15800,  15976,  16151,  16326,  16500,  16673
   ,  16846,  17018,  17190,  17361,  17531,  17700,  17869,  18037
   ,  18205,  18372,  18538,  18703,  18868,  19032,  19195,  19358
   ,  19520,  19681,  19841,  20001,  20160,  20318,  20475,  20632
   ,  20788,  20943,  21097,  21251,  21403,  21555,  21706,  21856
   ,  22006,  22154,  22302,  22449,  22595,  22740,  22884,  23028
   ,  23170,  23312,  23453,  23593,  23732,  23870,  24008,  24144
   ,  24279,  24414,  24548,  24680,  24812,  24943,  25073,  25202
   ,  25330,  25457,  25583,  25708,  25833,  25956,  26078,  26199
   ,  26320,  26439,  26557,  26674,  26791,  26906,  27020,  27133
   ,  27246,  27357,  27467,  27576,  27684,  27791,  27897,  28002
   ,  28106,  28209,  28311,  28411,  28511,  28610,  28707,  28803
   ,  28899,  28993,  29086,  29178,  29269,  29359,  29448,  29535
   ,  29622,  29707,  29792,  29875,  29957,  30038,  30118,  30196
   ,  30274,  30350,  30425,  30499,  30572,  30644,  30715,  30784
   ,  30853,  30920,  30986,  31050,  31114,  31177,  31238,  31298
   ,  31357,  31415,  31471,  31527,  31581,  31634,  31686,  31737
   ,  31786,  31834,  31881,  31927,  31972,  32015,  32058,  32099
   ,  32138,  32177,  32214,  32251,  32286,  32319,  32352,  32383
   ,  32413,  32442,  32470,  32496,  32522,  32546,  32568,  32590
   ,  32610,  32629,  32647,  32664,  32679,  32693,  32706,  32718
   ,  32729,  32738,  32746,  32753,  32758,  32762,  32766,  32767
   ,  32767,  32767,  32766,  32762,  32758,  32753,  32746,  32738
   ,  32729,  32718,  32706,  32693,  32679,  32664,  32647,  32629
   ,  32610,  32590,  32568,  32546,  32522,  32496,  32470,  32442
   ,  32413,  32383,  32352,  32319,  32286,  32251,  32214,  32177
   ,  32138,  32099,  32058,  32015,  31972,  31927,  31881,  31834
   ,  31786,  31737,  31686,  31634,  31581,  31527,  31471,  31415
   ,  31357,  31298,  31238,  31177,  31114,  31050,  30986,  30920
   ,  30853,  30784,  30715,  30644,  30572,  30499,  30425,  30350
   ,  30274,  30196,  30118,  30038,  29957,  29875,  29792,  29707
   ,  29622,  29535,  29448,  29359,  29269,  29178,  29086,  28993
   ,  28899,  28803,  28707,  28610,  28511,  28411,  28311,  28209
   ,  28106,  28002,  27897,  27791,  27684,  27576,  27467,  27357
   ,  27246,  27133,  27020,  26906,  26791,  26674,  26557,  26439
   ,  26320,  26199,  26078,  25956,  25833,  25708,  25583,  25457
   ,  25330,  25202,  25073,  24943,  24812,  24680,  24548,  24414
   ,  24279,  24144,  24008,  23870,  23732,  23593,  23453,  23312
   ,  23170,  23028,  22884,  22740,  22595,  22449,  22302,  22154
   ,  22006,  21856,  21706,  21555,  21403,  21251,  21097,  20943
   ,  20788,  20632,  20475,  20318,  20160,  20001,  19841,  19681
   ,  19520,  19358,  19195,  19032,  18868,  18703,  18538,  18372
   ,  18205,  18037,  17869,  17700,  17531,  17361,  17190,  17018
   ,  16846,  16673,  16500,  16326,  16151,  15976,  15800,  15624
   ,  15447,  15269,  15091,  14912,  14733,  14553,  14373,  14192
   ,  14010,  13828,  13646,  13463,  13279,  13095,  12910,  12725
   ,  12540,  12354,  12167,  11980,  11793,  11605,  11417,  11228
   ,  11039,  10850,  10660,  10469,  10279,  10088,   9896,   9704
   ,   9512,   9319,   9127,   8933,   8740,   8546,   8351,   8157
   ,   7962,   7767,   7571,   7376,   7180,   6983,   6787,   6590
   ,   6393,   6195,   5998,   5800,   5602,   5404,   5205,   5007
   ,   4808,   4609,   4410,   4211,   4011,   3812,   3612,   3412
   ,   3212,   3012,   2811,   2611,   2411,   2210,   2009,   1809
   ,   1608,   1407,   1206,   1005,    804,    603,    402,    201
   ,      0,   -200,   -401,   -602,   -803,  -1004,  -1205,  -1406
   ,  -1607,  -1808,  -2008,  -2209,  -2410,  -2610,  -2810,  -3011
   ,  -3211,  -3411,  -3611,  -3811,  -4010,  -4210,  -4409,  -4608
   ,  -4807,  -5006,  -5204,  -5403,  -5601,  -5799,  -5997,  -6194
   ,  -6392,  -6589,  -6786,  -6982,  -7179,  -7375,  -7570,  -7766
   ,  -7961,  -8156,  -8350,  -8545,  -8739,  -8932,  -9126,  -9318
   ,  -9511,  -9703,  -9895, -10087, -10278, -10468, -10659, -10849
   , -11038, -11227, -11416, -11604, -11792, -11979, -12166, -12353
   , -12539, -12724, -12909, -13094, -13278, -13462, -13645, -13827
   , -14009, -14191, -14372, -14552, -14732, -14911, -15090, -15268
   , -15446, -15623, -15799, -15975, -16150, -16325, -16499, -16672
   , -16845, -17017, -17189, -17360, -17530, -17699, -17868, -18036
   , -18204, -18371, -18537, -18702, -18867, -19031, -19194, -19357
   , -19519, -19680, -19840, -20000, -20159, -20317, -20474, -20631
   , -20787, -20942, -21096, -21250, -21402, -21554, -21705, -21855
   , -22005, -22153, -22301, -22448, -22594, -22739, -22883, -23027
   , -23169, -23311, -23452, -23592, -23731, -23869, -24007, -24143
   , -24278, -24413, -24547, -24679, -24811, -24942, -25072, -25201
   , -25329, -25456, -25582, -25707, -25832, -25955, -26077, -26198
   , -26319, -26438, -26556, -26673, -26790, -26905, -27019, -27132
   , -27245, -27356, -27466, -27575, -27683, -27790, -27896, -28001
   , -28105, -28208, -28310, -28410, -28510, -28609, -28706, -28802
   , -28898, -28992, -29085, -29177, -29268, -29358, -29447, -29534
   , -29621, -29706, -29791, -29874, -29956, -30037, -30117, -30195
   , -30273, -30349, -30424, -30498, -30571, -30643, -30714, -30783
   , -30852, -30919, -30985, -31049, -31113, -31176, -31237, -31297
   , -31356, -31414, -31470, -31526, -31580, -31633, -31685, -31736
   , -31785, -31833, -31880, -31926, -31971, -32014, -32057, -32098
   , -32137, -32176, -32213, -32250, -32285, -32318, -32351, -32382
   , -32412, -32441, -32469, -32495, -32521, -32545, -32567, -32589
   , -32609, -32628, -32646, -32663, -32678, -32692, -32705, -32717
   , -32728, -32737, -32745, -32752, -32757, -32761, -32765, -32766
   , -32767, -32766, -32765, -32761, -32757, -32752, -32745, -32737
   , -32728, -32717, -32705, -32692, -32678, -32663, -32646, -32628
   , -32609, -32589, -32567, -32545, -32521, -32495, -32469, -32441
   , -32412, -32382, -32351, -32318, -32285, -32250, -32213, -32176
   , -32137, -32098, -32057, -32014, -31971, -31926, -31880, -31833
   , -31785, -31736, -31685, -31633, -31580, -31526, -31470, -31414
   , -31356, -31297, -31237, -31176, -31113, -31049, -30985, -30919
   , -30852, -30783, -30714, -30643, -30571, -30498, -30424, -30349
   , -30273, -30195, -30117, -30037, -29956, -29874, -29791, -29706
   , -29621, -29534, -29447, -29358, -29268, -29177, -29085, -28992
   , -28898, -28802, -28706, -28609, -28510, -28410, -28310, -28208
   , -28105, -28001, -27896, -27790, -27683, -27575, -27466, -27356
   , -27245, -27132, -27019, -26905, -26790, -26673, -26556, -26438
   , -26319, -26198, -26077, -25955, -25832, -25707, -25582, -25456
   , -25329, -25201, -25072, -24942, -24811, -24679, -24547, -24413
   , -24278, -24143, -24007, -23869, -23731, -23592, -23452, -23311
   , -23169, -23027, -22883, -22739, -22594, -22448, -22301, -22153
   , -22005, -21855, -21705, -21554, -21402, -21250, -21096, -20942
   , -20787, -20631, -20474, -20317, -20159, -20000, -19840, -19680
   , -19519, -19357, -19194, -19031, -18867, -18702, -18537, -18371
   , -18204, -18036, -17868, -17699, -17530, -17360, -17189, -17017
   , -16845, -16672, -16499, -16325, -16150, -15975, -15799, -15623
   , -15446, -15268, -15090, -14911, -14732, -14552, -14372, -14191
   , -14009, -13827, -13645, -13462, -13278, -13094, -12909, -12724
   , -12539, -12353, -12166, -11979, -11792, -11604, -11416, -11227
   , -11038, -10849, -10659, -10468, -10278, -10087,  -9895,  -9703
   ,  -9511,  -9318,  -9126,  -8932,  -8739,  -8545,  -8350,  -8156
   ,  -7961,  -7766,  -7570,  -7375,  -7179,  -6982,  -6786,  -6589
   ,  -6392,  -6194,  -5997,  -5799,  -5601,  -5403,  -5204,  -5006
   ,  -4807,  -4608,  -4409,  -4210,  -4010,  -3811,  -3611,  -3411
   ,  -3211,  -3011,  -2810,  -2610,  -2410,  -2209,  -2008,  -1808
   ,  -1607,  -1406,  -1205,  -1004,   -803,   -602,   -401,   -200
   ,      0,    201,    402,    603,    804,   1005,   1206,   1407
   ,   1608,   1809,   2009,   2210,   2411,   2611,   2811,   3012
   ,   3212,   3412,   3612,   3812,   4011,   4211,   4410,   4609
   ,   4808,   5007,   5205,   5404,   5602,   5800,   5998,   6195
   ,   6393,   6590,   6787,   6983,   7180,   7376,   7571,   7767
   ,   7962,   8157,   8351,   8546,   8740,   8933,   9127,   9319
   ,   9512,   9704,   9896,  10088,  10279,  10469,  10660,  10850
   ,  11039,  11228,  11417,  11605,  11793,  11980,  12167,  12354
   ,  12540,  12725,  12910,  13095,  13279,  13463,  13646,  13828
   ,  14010,  14192,  14373,  14553,  14733,  14912,  15091,  15269
   ,  15447,  15624,  15800,  15976,  16151,  16326,  16500,  16673
   ,  16846,  17018,  17190,  17361,  17531,  17700,  17869,  18037
   ,  18205,  18372,  18538,  18703,  18868,  19032,  19195,  19358
   ,  19520,  19681,  19841,  20001,  20160,  20318,  20475,  20632
   ,  20788,  20943,  21097,  21251,  21403,  21555,  21706,  21856
   ,  22006,  22154,  22302,  22449,  22595,  22740,  22884,  23028
   ,  23170,  23312,  23453,  23593,  23732,  23870,  24008,  24144
   ,  24279,  24414,  24548,  24680,  24812,  24943,  25073,  25202
   ,  25330,  25457,  25583,  25708,  25833,  25956,  26078,  26199
   ,  26320,  26439,  26557,  26674,  26791,  26906,  27020,  27133
   ,  27246,  27357,  27467,  27576,  27684,  27791,  27897,  28002
   ,  28106,  28209,  28311,  28411,  28511,  28610,  28707,  28803
   ,  28899,  28993,  29086,  29178,  29269,  29359,  29448,  29535
   ,  29622,  29707,  29792,  29875,  29957,  30038,  30118,  30196
   ,  30274,  30350,  30425,  30499,  30572,  30644,  30715,  30784
   ,  30853,  30920,  30986,  31050,  31114,  31177,  31238,  31298
   ,  31357,  31415,  31471,  31527,  31581,  31634,  31686,  31737
   ,  31786,  31834,  31881,  31927,  31972,  32015,  32058,  32099
   ,  32138,  32177,  32214,  32251,  32286,  32319,  32352,  32383
   ,  32413,  32442,  32470,  32496,  32522,  32546,  32568,  32590
   ,  32610,  32629,  32647,  32664,  32679,  32693,  32706,  32718
   ,  32729,  32738,  32746,  32753,  32758,  32762,  32766,  32767
};

const uint16 Table_ArcTan[1025] ={
         0u,   10u,   20u,   31u,   41u,   51u,   61u,   71u
   ,    81u,   92u,  102u,  112u,  122u,  132u,  143u,  153u
   ,   163u,  173u,  183u,  194u,  204u,  214u,  224u,  234u
   ,   244u,  255u,  265u,  275u,  285u,  295u,  305u,  316u
   ,   326u,  336u,  346u,  356u,  367u,  377u,  387u,  397u
   ,   407u,  417u,  428u,  438u,  448u,  458u,  468u,  478u
   ,   489u,  499u,  509u,  519u,  529u,  539u,  550u,  560u
   ,   570u,  580u,  590u,  600u,  610u,  621u,  631u,  641u
   ,   651u,  661u,  671u,  681u,  692u,  702u,  712u,  722u
   ,   732u,  742u,  752u,  763u,  773u,  783u,  793u,  803u
   ,   813u,  823u,  833u,  844u,  854u,  864u,  874u,  884u
   ,   894u,  904u,  914u,  924u,  935u,  945u,  955u,  965u
   ,   975u,  985u,  995u, 1005u, 1015u, 1025u, 1036u, 1046u
   ,  1056u, 1066u, 1076u, 1086u, 1096u, 1106u, 1116u, 1126u
   ,  1136u, 1146u, 1156u, 1166u, 1177u, 1187u, 1197u, 1207u
   ,  1217u, 1227u, 1237u, 1247u, 1257u, 1267u, 1277u, 1287u
   ,  1297u, 1307u, 1317u, 1327u, 1337u, 1347u, 1357u, 1367u
   ,  1377u, 1387u, 1397u, 1407u, 1417u, 1427u, 1437u, 1447u
   ,  1457u, 1467u, 1477u, 1487u, 1497u, 1507u, 1517u, 1527u
   ,  1537u, 1547u, 1557u, 1567u, 1577u, 1587u, 1597u, 1607u
   ,  1617u, 1627u, 1637u, 1646u, 1656u, 1666u, 1676u, 1686u
   ,  1696u, 1706u, 1716u, 1726u, 1736u, 1746u, 1756u, 1765u
   ,  1775u, 1785u, 1795u, 1805u, 1815u, 1825u, 1835u, 1845u
   ,  1854u, 1864u, 1874u, 1884u, 1894u, 1904u, 1914u, 1923u
   ,  1933u, 1943u, 1953u, 1963u, 1973u, 1982u, 1992u, 2002u
   ,  2012u, 2022u, 2031u, 2041u, 2051u, 2061u, 2071u, 2080u
   ,  2090u, 2100u, 2110u, 2120u, 2129u, 2139u, 2149u, 2159u
   ,  2168u, 2178u, 2188u, 2198u, 2207u, 2217u, 2227u, 2237u
   ,  2246u, 2256u, 2266u, 2275u, 2285u, 2295u, 2305u, 2314u
   ,  2324u, 2334u, 2343u, 2353u, 2363u, 2372u, 2382u, 2392u
   ,  2401u, 2411u, 2421u, 2430u, 2440u, 2450u, 2459u, 2469u
   ,  2478u, 2488u, 2498u, 2507u, 2517u, 2526u, 2536u, 2546u
   ,  2555u, 2565u, 2574u, 2584u, 2594u, 2603u, 2613u, 2622u
   ,  2632u, 2641u, 2651u, 2660u, 2670u, 2679u, 2689u, 2699u
   ,  2708u, 2718u, 2727u, 2737u, 2746u, 2756u, 2765u, 2775u
   ,  2784u, 2793u, 2803u, 2812u, 2822u, 2831u, 2841u, 2850u
   ,  2860u, 2869u, 2879u, 2888u, 2897u, 2907u, 2916u, 2926u
   ,  2935u, 2944u, 2954u, 2963u, 2973u, 2982u, 2991u, 3001u
   ,  3010u, 3019u, 3029u, 3038u, 3047u, 3057u, 3066u, 3075u
   ,  3085u, 3094u, 3103u, 3113u, 3122u, 3131u, 3141u, 3150u
   ,  3159u, 3168u, 3178u, 3187u, 3196u, 3206u, 3215u, 3224u
   ,  3233u, 3243u, 3252u, 3261u, 3270u, 3279u, 3289u, 3298u
   ,  3307u, 3316u, 3325u, 3335u, 3344u, 3353u, 3362u, 3371u
   ,  3380u, 3390u, 3399u, 3408u, 3417u, 3426u, 3435u, 3444u
   ,  3453u, 3463u, 3472u, 3481u, 3490u, 3499u, 3508u, 3517u
   ,  3526u, 3535u, 3544u, 3553u, 3562u, 3571u, 3580u, 3589u
   ,  3599u, 3608u, 3617u, 3626u, 3635u, 3644u, 3653u, 3662u
   ,  3670u, 3679u, 3688u, 3697u, 3706u, 3715u, 3724u, 3733u
   ,  3742u, 3751u, 3760u, 3769u, 3778u, 3787u, 3796u, 3804u
   ,  3813u, 3822u, 3831u, 3840u, 3849u, 3858u, 3867u, 3875u
   ,  3884u, 3893u, 3902u, 3911u, 3920u, 3928u, 3937u, 3946u
   ,  3955u, 3964u, 3972u, 3981u, 3990u, 3999u, 4007u, 4016u
   ,  4025u, 4034u, 4042u, 4051u, 4060u, 4069u, 4077u, 4086u
   ,  4095u, 4103u, 4112u, 4121u, 4129u, 4138u, 4147u, 4155u
   ,  4164u, 4173u, 4181u, 4190u, 4199u, 4207u, 4216u, 4224u
   ,  4233u, 4242u, 4250u, 4259u, 4267u, 4276u, 4284u, 4293u
   ,  4302u, 4310u, 4319u, 4327u, 4336u, 4344u, 4353u, 4361u
   ,  4370u, 4378u, 4387u, 4395u, 4404u, 4412u, 4421u, 4429u
   ,  4438u, 4446u, 4454u, 4463u, 4471u, 4480u, 4488u, 4497u
   ,  4505u, 4513u, 4522u, 4530u, 4539u, 4547u, 4555u, 4564u
   ,  4572u, 4580u, 4589u, 4597u, 4605u, 4614u, 4622u, 4630u
   ,  4639u, 4647u, 4655u, 4663u, 4672u, 4680u, 4688u, 4697u
   ,  4705u, 4713u, 4721u, 4730u, 4738u, 4746u, 4754u, 4762u
   ,  4771u, 4779u, 4787u, 4795u, 4803u, 4812u, 4820u, 4828u
   ,  4836u, 4844u, 4852u, 4860u, 4869u, 4877u, 4885u, 4893u
   ,  4901u, 4909u, 4917u, 4925u, 4933u, 4941u, 4949u, 4958u
   ,  4966u, 4974u, 4982u, 4990u, 4998u, 5006u, 5014u, 5022u
   ,  5030u, 5038u, 5046u, 5054u, 5062u, 5070u, 5078u, 5086u
   ,  5094u, 5101u, 5109u, 5117u, 5125u, 5133u, 5141u, 5149u
   ,  5157u, 5165u, 5173u, 5181u, 5188u, 5196u, 5204u, 5212u
   ,  5220u, 5228u, 5235u, 5243u, 5251u, 5259u, 5267u, 5275u
   ,  5282u, 5290u, 5298u, 5306u, 5313u, 5321u, 5329u, 5337u
   ,  5344u, 5352u, 5360u, 5368u, 5375u, 5383u, 5391u, 5398u
   ,  5406u, 5414u, 5421u, 5429u, 5437u, 5444u, 5452u, 5460u
   ,  5467u, 5475u, 5483u, 5490u, 5498u, 5505u, 5513u, 5521u
   ,  5528u, 5536u, 5543u, 5551u, 5559u, 5566u, 5574u, 5581u
   ,  5589u, 5596u, 5604u, 5611u, 5619u, 5626u, 5634u, 5641u
   ,  5649u, 5656u, 5664u, 5671u, 5679u, 5686u, 5694u, 5701u
   ,  5708u, 5716u, 5723u, 5731u, 5738u, 5745u, 5753u, 5760u
   ,  5768u, 5775u, 5782u, 5790u, 5797u, 5804u, 5812u, 5819u
   ,  5826u, 5834u, 5841u, 5848u, 5856u, 5863u, 5870u, 5878u
   ,  5885u, 5892u, 5899u, 5907u, 5914u, 5921u, 5928u, 5936u
   ,  5943u, 5950u, 5957u, 5964u, 5972u, 5979u, 5986u, 5993u
   ,  6000u, 6008u, 6015u, 6022u, 6029u, 6036u, 6043u, 6050u
   ,  6058u, 6065u, 6072u, 6079u, 6086u, 6093u, 6100u, 6107u
   ,  6114u, 6121u, 6128u, 6135u, 6142u, 6150u, 6157u, 6164u
   ,  6171u, 6178u, 6185u, 6192u, 6199u, 6206u, 6213u, 6220u
   ,  6227u, 6234u, 6240u, 6247u, 6254u, 6261u, 6268u, 6275u
   ,  6282u, 6289u, 6296u, 6303u, 6310u, 6317u, 6323u, 6330u
   ,  6337u, 6344u, 6351u, 6358u, 6365u, 6371u, 6378u, 6385u
   ,  6392u, 6399u, 6406u, 6412u, 6419u, 6426u, 6433u, 6440u
   ,  6446u, 6453u, 6460u, 6467u, 6473u, 6480u, 6487u, 6493u
   ,  6500u, 6507u, 6514u, 6520u, 6527u, 6534u, 6540u, 6547u
   ,  6554u, 6560u, 6567u, 6574u, 6580u, 6587u, 6594u, 6600u
   ,  6607u, 6613u, 6620u, 6627u, 6633u, 6640u, 6646u, 6653u
   ,  6660u, 6666u, 6673u, 6679u, 6686u, 6692u, 6699u, 6705u
   ,  6712u, 6718u, 6725u, 6731u, 6738u, 6744u, 6751u, 6757u
   ,  6764u, 6770u, 6777u, 6783u, 6790u, 6796u, 6803u, 6809u
   ,  6815u, 6822u, 6828u, 6835u, 6841u, 6848u, 6854u, 6860u
   ,  6867u, 6873u, 6879u, 6886u, 6892u, 6898u, 6905u, 6911u
   ,  6917u, 6924u, 6930u, 6936u, 6943u, 6949u, 6955u, 6962u
   ,  6968u, 6974u, 6980u, 6987u, 6993u, 6999u, 7005u, 7012u
   ,  7018u, 7024u, 7030u, 7037u, 7043u, 7049u, 7055u, 7061u
   ,  7068u, 7074u, 7080u, 7086u, 7092u, 7098u, 7105u, 7111u
   ,  7117u, 7123u, 7129u, 7135u, 7141u, 7147u, 7154u, 7160u
   ,  7166u, 7172u, 7178u, 7184u, 7190u, 7196u, 7202u, 7208u
   ,  7214u, 7220u, 7226u, 7232u, 7238u, 7244u, 7250u, 7256u
   ,  7262u, 7268u, 7274u, 7280u, 7286u, 7292u, 7298u, 7304u
   ,  7310u, 7316u, 7322u, 7328u, 7334u, 7340u, 7346u, 7352u
   ,  7358u, 7363u, 7369u, 7375u, 7381u, 7387u, 7393u, 7399u
   ,  7405u, 7411u, 7416u, 7422u, 7428u, 7434u, 7440u, 7446u
   ,  7451u, 7457u, 7463u, 7469u, 7475u, 7480u, 7486u, 7492u
   ,  7498u, 7503u, 7509u, 7515u, 7521u, 7526u, 7532u, 7538u
   ,  7544u, 7549u, 7555u, 7561u, 7566u, 7572u, 7578u, 7584u
   ,  7589u, 7595u, 7601u, 7606u, 7612u, 7618u, 7623u, 7629u
   ,  7635u, 7640u, 7646u, 7651u, 7657u, 7663u, 7668u, 7674u
   ,  7679u, 7685u, 7691u, 7696u, 7702u, 7707u, 7713u, 7718u
   ,  7724u, 7730u, 7735u, 7741u, 7746u, 7752u, 7757u, 7763u
   ,  7768u, 7774u, 7779u, 7785u, 7790u, 7796u, 7801u, 7807u
   ,  7812u, 7818u, 7823u, 7828u, 7834u, 7839u, 7845u, 7850u
   ,  7856u, 7861u, 7866u, 7872u, 7877u, 7883u, 7888u, 7893u
   ,  7899u, 7904u, 7910u, 7915u, 7920u, 7926u, 7931u, 7936u
   ,  7942u, 7947u, 7952u, 7958u, 7963u, 7968u, 7974u, 7979u
   ,  7984u, 7990u, 7995u, 8000u, 8005u, 8011u, 8016u, 8021u
   ,  8026u, 8032u, 8037u, 8042u, 8047u, 8053u, 8058u, 8063u
   ,  8068u, 8074u, 8079u, 8084u, 8089u, 8094u, 8100u, 8105u
   ,  8110u, 8115u, 8120u, 8125u, 8131u, 8136u, 8141u, 8146u
   ,  8151u, 8156u, 8161u, 8166u, 8172u, 8177u, 8182u, 8187u
   ,  8192u
};

const uint16 Table_Amp[] ={
      32768u, 32768u, 32768u, 32768u, 32768u, 32768u, 32769u, 32769u
   ,  32769u, 32769u, 32770u, 32770u, 32770u, 32771u, 32771u, 32772u
   ,  32772u, 32773u, 32773u, 32774u, 32774u, 32775u, 32776u, 32776u
   ,  32777u, 32778u, 32779u, 32779u, 32780u, 32781u, 32782u, 32783u
   ,  32784u, 32785u, 32786u, 32787u, 32788u, 32789u, 32791u, 32792u
   ,  32793u, 32794u, 32796u, 32797u, 32798u, 32800u, 32801u, 32802u
   ,  32804u, 32805u, 32807u, 32809u, 32810u, 32812u, 32814u, 32815u
   ,  32817u, 32819u, 32821u, 32822u, 32824u, 32826u, 32828u, 32830u
   ,  32832u, 32834u, 32836u, 32838u, 32840u, 32842u, 32844u, 32847u
   ,  32849u, 32851u, 32853u, 32856u, 32858u, 32861u, 32863u, 32865u
   ,  32868u, 32870u, 32873u, 32875u, 32878u, 32881u, 32883u, 32886u
   ,  32889u, 32892u, 32894u, 32897u, 32900u, 32903u, 32906u, 32909u
   ,  32912u, 32915u, 32918u, 32921u, 32924u, 32927u, 32930u, 32933u
   ,  32937u, 32940u, 32943u, 32946u, 32950u, 32953u, 32957u, 32960u
   ,  32963u, 32967u, 32970u, 32974u, 32978u, 32981u, 32985u, 32989u
   ,  32992u, 32996u, 33000u, 33004u, 33007u, 33011u, 33015u, 33019u
   ,  33023u, 33027u, 33031u, 33035u, 33039u, 33043u, 33047u, 33052u
   ,  33056u, 33060u, 33064u, 33069u, 33073u, 33077u, 33082u, 33086u
   ,  33090u, 33095u, 33099u, 33104u, 33108u, 33113u, 33118u, 33122u
   ,  33127u, 33132u, 33136u, 33141u, 33146u, 33151u, 33156u, 33161u
   ,  33166u, 33171u, 33176u, 33181u, 33186u, 33191u, 33196u, 33201u
   ,  33206u, 33211u, 33216u, 33222u, 33227u, 33232u, 33238u, 33243u
   ,  33248u, 33254u, 33259u, 33265u, 33270u, 33276u, 33282u, 33287u
   ,  33293u, 33298u, 33304u, 33310u, 33316u, 33321u, 33327u, 33333u
   ,  33339u, 33345u, 33351u, 33357u, 33363u, 33369u, 33375u, 33381u
   ,  33387u, 33393u, 33399u, 33406u, 33412u, 33418u, 33424u, 33431u
   ,  33437u, 33444u, 33450u, 33456u, 33463u, 33469u, 33476u, 33482u
   ,  33489u, 33496u, 33502u, 33509u, 33516u, 33522u, 33529u, 33536u
   ,  33543u, 33550u, 33557u, 33563u, 33570u, 33577u, 33584u, 33591u
   ,  33598u, 33606u, 33613u, 33620u, 33627u, 33634u, 33641u, 33649u
   ,  33656u, 33663u, 33671u, 33678u, 33685u, 33693u, 33700u, 33708u
   ,  33715u, 33723u, 33730u, 33738u, 33746u, 33753u, 33761u, 33769u
   ,  33776u, 33784u, 33792u, 33800u, 33808u, 33816u, 33824u, 33832u
   ,  33839u, 33847u, 33856u, 33864u, 33872u, 33880u, 33888u, 33896u
   ,  33904u, 33913u, 33921u, 33929u, 33937u, 33946u, 33954u, 33962u
   ,  33971u, 33979u, 33988u, 33996u, 34005u, 34013u, 34022u, 34031u
   ,  34039u, 34048u, 34057u, 34065u, 34074u, 34083u, 34092u, 34101u
   ,  34110u, 34118u, 34127u, 34136u, 34145u, 34154u, 34163u, 34172u
   ,  34182u, 34191u, 34200u, 34209u, 34218u, 34227u, 34237u, 34246u
   ,  34255u, 34265u, 34274u, 34283u, 34293u, 34302u, 34312u, 34321u
   ,  34331u, 34340u, 34350u, 34359u, 34369u, 34379u, 34388u, 34398u
   ,  34408u, 34418u, 34428u, 34437u, 34447u, 34457u, 34467u, 34477u
   ,  34487u, 34497u, 34507u, 34517u, 34527u, 34537u, 34547u, 34557u
   ,  34568u, 34578u, 34588u, 34598u, 34609u, 34619u, 34629u, 34640u
   ,  34650u, 34660u, 34671u, 34681u, 34692u, 34702u, 34713u, 34723u
   ,  34734u, 34745u, 34755u, 34766u, 34777u, 34787u, 34798u, 34809u
   ,  34820u, 34831u, 34841u, 34852u, 34863u, 34874u, 34885u, 34896u
   ,  34907u, 34918u, 34929u, 34940u, 34952u, 34963u, 34974u, 34985u
   ,  34996u, 35007u, 35019u, 35030u, 35041u, 35053u, 35064u, 35076u
   ,  35087u, 35098u, 35110u, 35121u, 35133u, 35144u, 35156u, 35168u
   ,  35179u, 35191u, 35203u, 35214u, 35226u, 35238u, 35250u, 35261u
   ,  35273u, 35285u, 35297u, 35309u, 35321u, 35333u, 35345u, 35357u
   ,  35369u, 35381u, 35393u, 35405u, 35417u, 35429u, 35441u, 35454u
   ,  35466u, 35478u, 35490u, 35503u, 35515u, 35527u, 35540u, 35552u
   ,  35565u, 35577u, 35590u, 35602u, 35615u, 35627u, 35640u, 35652u
   ,  35665u, 35678u, 35690u, 35703u, 35716u, 35728u, 35741u, 35754u
   ,  35767u, 35780u, 35792u, 35805u, 35818u, 35831u, 35844u, 35857u
   ,  35870u, 35883u, 35896u, 35909u, 35922u, 35936u, 35949u, 35962u
   ,  35975u, 35988u, 36002u, 36015u, 36028u, 36041u, 36055u, 36068u
   ,  36081u, 36095u, 36108u, 36122u, 36135u, 36149u, 36162u, 36176u
   ,  36189u, 36203u, 36217u, 36230u, 36244u, 36258u, 36271u, 36285u
   ,  36299u, 36313u, 36326u, 36340u, 36354u, 36368u, 36382u, 36396u
   ,  36410u, 36424u, 36438u, 36452u, 36466u, 36480u, 36494u, 36508u
   ,  36522u, 36536u, 36550u, 36564u, 36579u, 36593u, 36607u, 36621u
   ,  36636u, 36650u, 36664u, 36679u, 36693u, 36708u, 36722u, 36736u
   ,  36751u, 36765u, 36780u, 36795u, 36809u, 36824u, 36838u, 36853u
   ,  36868u, 36882u, 36897u, 36912u, 36926u, 36941u, 36956u, 36971u
   ,  36986u, 37000u, 37015u, 37030u, 37045u, 37060u, 37075u, 37090u
   ,  37105u, 37120u, 37135u, 37150u, 37165u, 37180u, 37195u, 37211u
   ,  37226u, 37241u, 37256u, 37271u, 37287u, 37302u, 37317u, 37333u
   ,  37348u, 37363u, 37379u, 37394u, 37410u, 37425u, 37440u, 37456u
   ,  37471u, 37487u, 37503u, 37518u, 37534u, 37549u, 37565u, 37581u
   ,  37596u, 37612u, 37628u, 37643u, 37659u, 37675u, 37691u, 37707u
   ,  37722u, 37738u, 37754u, 37770u, 37786u, 37802u, 37818u, 37834u
   ,  37850u, 37866u, 37882u, 37898u, 37914u, 37930u, 37946u, 37963u
   ,  37979u, 37995u, 38011u, 38027u, 38044u, 38060u, 38076u, 38092u
   ,  38109u, 38125u, 38141u, 38158u, 38174u, 38191u, 38207u, 38224u
   ,  38240u, 38257u, 38273u, 38290u, 38306u, 38323u, 38339u, 38356u
   ,  38373u, 38389u, 38406u, 38423u, 38439u, 38456u, 38473u, 38490u
   ,  38507u, 38523u, 38540u, 38557u, 38574u, 38591u, 38608u, 38625u
   ,  38642u, 38659u, 38676u, 38693u, 38710u, 38727u, 38744u, 38761u
   ,  38778u, 38795u, 38812u, 38829u, 38846u, 38864u, 38881u, 38898u
   ,  38915u, 38933u, 38950u, 38967u, 38985u, 39002u, 39019u, 39037u
   ,  39054u, 39071u, 39089u, 39106u, 39124u, 39141u, 39159u, 39176u
   ,  39194u, 39211u, 39229u, 39247u, 39264u, 39282u, 39300u, 39317u
   ,  39335u, 39353u, 39370u, 39388u, 39406u, 39424u, 39442u, 39459u
   ,  39477u, 39495u, 39513u, 39531u, 39549u, 39567u, 39585u, 39603u
   ,  39620u, 39638u, 39657u, 39675u, 39693u, 39711u, 39729u, 39747u
   ,  39765u, 39783u, 39801u, 39819u, 39838u, 39856u, 39874u, 39892u
   ,  39911u, 39929u, 39947u, 39965u, 39984u, 40002u, 40020u, 40039u
   ,  40057u, 40076u, 40094u, 40113u, 40131u, 40149u, 40168u, 40187u
   ,  40205u, 40224u, 40242u, 40261u, 40279u, 40298u, 40317u, 40335u
   ,  40354u, 40373u, 40391u, 40410u, 40429u, 40448u, 40466u, 40485u
   ,  40504u, 40523u, 40542u, 40560u, 40579u, 40598u, 40617u, 40636u
   ,  40655u, 40674u, 40693u, 40712u, 40731u, 40750u, 40769u, 40788u
   ,  40807u, 40826u, 40845u, 40864u, 40883u, 40902u, 40922u, 40941u
   ,  40960u, 40979u, 40998u, 41018u, 41037u, 41056u, 41075u, 41095u
   ,  41114u, 41133u, 41153u, 41172u, 41192u, 41211u, 41230u, 41250u
   ,  41269u, 41289u, 41308u, 41328u, 41347u, 41367u, 41386u, 41406u
   ,  41425u, 41445u, 41465u, 41484u, 41504u, 41523u, 41543u, 41563u
   ,  41582u, 41602u, 41622u, 41642u, 41661u, 41681u, 41701u, 41721u
   ,  41741u, 41760u, 41780u, 41800u, 41820u, 41840u, 41860u, 41880u
   ,  41900u, 41920u, 41940u, 41960u, 41980u, 42000u, 42020u, 42040u
   ,  42060u, 42080u, 42100u, 42120u, 42140u, 42160u, 42180u, 42200u
   ,  42221u, 42241u, 42261u, 42281u, 42301u, 42322u, 42342u, 42362u
   ,  42382u, 42403u, 42423u, 42443u, 42464u, 42484u, 42505u, 42525u
   ,  42545u, 42566u, 42586u, 42607u, 42627u, 42648u, 42668u, 42689u
   ,  42709u, 42730u, 42750u, 42771u, 42791u, 42812u, 42832u, 42853u
   ,  42874u, 42894u, 42915u, 42936u, 42956u, 42977u, 42998u, 43018u
   ,  43039u, 43060u, 43081u, 43102u, 43122u, 43143u, 43164u, 43185u
   ,  43206u, 43227u, 43247u, 43268u, 43289u, 43310u, 43331u, 43352u
   ,  43373u, 43394u, 43415u, 43436u, 43457u, 43478u, 43499u, 43520u
   ,  43541u, 43562u, 43583u, 43604u, 43625u, 43647u, 43668u, 43689u
   ,  43710u, 43731u, 43752u, 43774u, 43795u, 43816u, 43837u, 43859u
   ,  43880u, 43901u, 43923u, 43944u, 43965u, 43986u, 44008u, 44029u
   ,  44051u, 44072u, 44093u, 44115u, 44136u, 44158u, 44179u, 44201u
   ,  44222u, 44244u, 44265u, 44287u, 44308u, 44330u, 44351u, 44373u
   ,  44394u, 44416u, 44438u, 44459u, 44481u, 44503u, 44524u, 44546u
   ,  44568u, 44589u, 44611u, 44633u, 44654u, 44676u, 44698u, 44720u
   ,  44741u, 44763u, 44785u, 44807u, 44829u, 44851u, 44872u, 44894u
   ,  44916u, 44938u, 44960u, 44982u, 45004u, 45026u, 45048u, 45070u
   ,  45092u, 45114u, 45136u, 45158u, 45180u, 45202u, 45224u, 45246u
   ,  45268u, 45290u, 45312u, 45334u, 45356u, 45378u, 45401u, 45423u
   ,  45445u, 45467u, 45489u, 45511u, 45534u, 45556u, 45578u, 45600u
   ,  45623u, 45645u, 45667u, 45689u, 45712u, 45734u, 45756u, 45779u
   ,  45801u, 45823u, 45846u, 45868u, 45891u, 45913u, 45935u, 45958u
   ,  45980u, 46003u, 46025u, 46048u, 46070u, 46093u, 46115u, 46138u
   ,  46160u, 46183u, 46205u, 46228u, 46251u, 46273u, 46296u, 46318u
   ,  46341u, 46364u, 46386u, 46409u, 46432u, 46454u, 46477u, 46500u
   ,  46522u, 46545u
};

const uint16 Table_sqrtmqu[] ={
      256,    256,    256,    256,    256,    256,    256,    256
   ,  256,    256,    256,    256,    256,    256,    256,    256
   ,  255,    255,    255,    255,    255,    255,    255,    255
   ,  255,    255,    255,    255,    254,    254,    254,    254
   ,  254,    254,    254,    254,    253,    253,    253,    253
   ,  253,    253,    253,    252,    252,    252,    252,    252
   ,  251,    251,    251,    251,    251,    250,    250,    250
   ,  250,    250,    249,    249,    249,    249,    248,    248
   ,  248,    248,    247,    247,    247,    247,    246,    246
   ,  246,    245,    245,    245,    244,    244,    244,    244
   ,  243,    243,    243,    242,    242,    241,    241,    241
   ,  240,    240,    240,    239,    239,    239,    238,    238
   ,  237,    237,    236,    236,    236,    235,    235,    234
   ,  234,    233,    233,    233,    232,    232,    231,    231
   ,  230,    230,    229,    229,    228,    228,    227,    227
   ,  226,    226,    225,    225,    224,    223,    223,    222
   ,  222,    221,    221,    220,    219,    219,    218,    218
   ,  217,    216,    216,    215,    214,    214,    213,    212
   ,  212,    211,    210,    210,    209,    208,    207,    207
   ,  206,    205,    204,    204,    203,    202,    201,    201
   ,  200,    199,    198,    197,    197,    196,    195,    194
   ,  193,    192,    191,    191,    190,    189,    188,    187
   ,  186,    185,    184,    183,    182,    181,    180,    179
   ,  178,    177,    176,    175,    174,    173,    172,    170
   ,  169,    168,    167,    166,    165,    163,    162,    161
   ,  160,    159,    157,    156,    155,    153,    152,    151
   ,  149,    148,    146,    145,    143,    142,    140,    139
   ,  137,    136,    134,    133,    131,    129,    127,    126
   ,  124,    122,    120,    118,    116,    114,    112,    110
   ,  108,    106,    104,    102,    99,     97,     94,     92
   ,  89,     86,     83,     81,     77,     74,     71,     67
   ,  63,     59,     55,     50,     45,     39,     32,     23
   ,  0
};

const uint16 Table_Sin60[] ={
                      0, Table_lScale(  134), Table_lScale(  268), Table_lScale(  402)
  , Table_lScale(  536), Table_lScale(  670), Table_lScale(  804), Table_lScale(  938)
  , Table_lScale( 1072), Table_lScale( 1206), Table_lScale( 1340), Table_lScale( 1473)
  , Table_lScale( 1607), Table_lScale( 1741), Table_lScale( 1875), Table_lScale( 2009)
  , Table_lScale( 2143), Table_lScale( 2276), Table_lScale( 2410), Table_lScale( 2544)
  , Table_lScale( 2677), Table_lScale( 2811), Table_lScale( 2944), Table_lScale( 3078)
  , Table_lScale( 3211), Table_lScale( 3345), Table_lScale( 3478), Table_lScale( 3611)
  , Table_lScale( 3744), Table_lScale( 3878), Table_lScale( 4011), Table_lScale( 4144)
  , Table_lScale( 4277), Table_lScale( 4409), Table_lScale( 4542), Table_lScale( 4675)
  , Table_lScale( 4808), Table_lScale( 4940), Table_lScale( 5073), Table_lScale( 5205)
  , Table_lScale( 5337), Table_lScale( 5469), Table_lScale( 5602), Table_lScale( 5734)
  , Table_lScale( 5866), Table_lScale( 5997), Table_lScale( 6129), Table_lScale( 6261)
  , Table_lScale( 6392), Table_lScale( 6524), Table_lScale( 6655), Table_lScale( 6786)
  , Table_lScale( 6917), Table_lScale( 7048), Table_lScale( 7179), Table_lScale( 7310)
  , Table_lScale( 7440), Table_lScale( 7571), Table_lScale( 7701), Table_lScale( 7831)
  , Table_lScale( 7961), Table_lScale( 8091), Table_lScale( 8221), Table_lScale( 8351)
  , Table_lScale( 8480), Table_lScale( 8610), Table_lScale( 8739), Table_lScale( 8868)
  , Table_lScale( 8997), Table_lScale( 9126), Table_lScale( 9255), Table_lScale( 9383)
  , Table_lScale( 9512), Table_lScale( 9640), Table_lScale( 9768), Table_lScale( 9896)
  , Table_lScale(10023), Table_lScale(10151), Table_lScale(10278), Table_lScale(10405)
  , Table_lScale(10532), Table_lScale(10659), Table_lScale(10786), Table_lScale(10912)
  , Table_lScale(11039), Table_lScale(11165), Table_lScale(11291), Table_lScale(11416)
  , Table_lScale(11542), Table_lScale(11667), Table_lScale(11793), Table_lScale(11918)
  , Table_lScale(12042), Table_lScale(12167), Table_lScale(12291), Table_lScale(12415)
  , Table_lScale(12539), Table_lScale(12663), Table_lScale(12787), Table_lScale(12910)
  , Table_lScale(13033), Table_lScale(13156), Table_lScale(13278), Table_lScale(13401)
  , Table_lScale(13523), Table_lScale(13645), Table_lScale(13767), Table_lScale(13888)
  , Table_lScale(14010), Table_lScale(14131), Table_lScale(14251), Table_lScale(14372)
  , Table_lScale(14492), Table_lScale(14613), Table_lScale(14732), Table_lScale(14852)
  , Table_lScale(14971), Table_lScale(15090), Table_lScale(15209), Table_lScale(15328)
  , Table_lScale(15446), Table_lScale(15564), Table_lScale(15682), Table_lScale(15800)
  , Table_lScale(15917), Table_lScale(16034), Table_lScale(16151), Table_lScale(16267)
  , Table_lScale(16384), Table_lScale(16499), Table_lScale(16615), Table_lScale(16731)
  , Table_lScale(16846), Table_lScale(16960), Table_lScale(17075), Table_lScale(17189)
  , Table_lScale(17303), Table_lScale(17417), Table_lScale(17530), Table_lScale(17643)
  , Table_lScale(17756), Table_lScale(17869), Table_lScale(17981), Table_lScale(18093)
  , Table_lScale(18204), Table_lScale(18316), Table_lScale(18427), Table_lScale(18537)
  , Table_lScale(18648), Table_lScale(18758), Table_lScale(18868), Table_lScale(18977)
  , Table_lScale(19086), Table_lScale(19195), Table_lScale(19303), Table_lScale(19412)
  , Table_lScale(19519), Table_lScale(19627), Table_lScale(19734), Table_lScale(19841)
  , Table_lScale(19947), Table_lScale(20054), Table_lScale(20159), Table_lScale(20265)
  , Table_lScale(20370), Table_lScale(20475), Table_lScale(20579), Table_lScale(20684)
  , Table_lScale(20787), Table_lScale(20891), Table_lScale(20994), Table_lScale(21097)
  , Table_lScale(21199), Table_lScale(21301), Table_lScale(21403), Table_lScale(21504)
  , Table_lScale(21605), Table_lScale(21706), Table_lScale(21806), Table_lScale(21906)
  , Table_lScale(22005), Table_lScale(22104), Table_lScale(22203), Table_lScale(22301)
  , Table_lScale(22399), Table_lScale(22497), Table_lScale(22594), Table_lScale(22691)
  , Table_lScale(22788), Table_lScale(22884), Table_lScale(22980), Table_lScale(23075)
  , Table_lScale(23170), Table_lScale(23265), Table_lScale(23359), Table_lScale(23453)
  , Table_lScale(23546), Table_lScale(23639), Table_lScale(23732), Table_lScale(23824)
  , Table_lScale(23916), Table_lScale(24007), Table_lScale(24098), Table_lScale(24189)
  , Table_lScale(24279), Table_lScale(24369), Table_lScale(24458), Table_lScale(24547)
  , Table_lScale(24636), Table_lScale(24724), Table_lScale(24812), Table_lScale(24899)
  , Table_lScale(24986), Table_lScale(25073), Table_lScale(25159), Table_lScale(25244)
  , Table_lScale(25330), Table_lScale(25414), Table_lScale(25499), Table_lScale(25583)
  , Table_lScale(25666), Table_lScale(25749), Table_lScale(25832), Table_lScale(25914)
  , Table_lScale(25996), Table_lScale(26077), Table_lScale(26158), Table_lScale(26239)
  , Table_lScale(26319), Table_lScale(26399), Table_lScale(26478), Table_lScale(26557)
  , Table_lScale(26635), Table_lScale(26713), Table_lScale(26790), Table_lScale(26867)
  , Table_lScale(26944), Table_lScale(27020), Table_lScale(27095), Table_lScale(27170)
  , Table_lScale(27245), Table_lScale(27319), Table_lScale(27393), Table_lScale(27466)
  , Table_lScale(27539), Table_lScale(27612), Table_lScale(27684), Table_lScale(27755)
  , Table_lScale(27826), Table_lScale(27897), Table_lScale(27967), Table_lScale(28036)
  , Table_lScale(28106), Table_lScale(28174), Table_lScale(28242), Table_lScale(28310)
};

const sint16 *pTable_Cos = Table_Sin + (TABLE_SIZE_SIN_COS / 4u);

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

