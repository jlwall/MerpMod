/*
	Copyright (C) 2012-2013 Merrill A. Myers III merrillamyersiii@gmail.com
	
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

#include "EcuHacks.h"

#if SD_HACKS
unsigned char StartOfSpeedDensityTables SPEEDDENSITYDATA = 0x00;

float DefaultBlend SPEEDDENSITYDATA = 0.7f;

//SPEED DENSITY CONSTANTS
unsigned char DefaultMafMode SPEEDDENSITYDATA
 = MafModeSensor;
float CelsiusToKelvin SPEEDDENSITYDATA
 = 273.15;
float SpeedDensityConstant SPEEDDENSITYDATA
 = 0.003871098;
float Displacement SPEEDDENSITYDATA
 = 2.46;

#if SWITCH_HACKS
TableGroup VETableGroup SPEEDDENSITYDATA = {
	{&VolumetricEfficiencyTable1,
	&VolumetricEfficiencyTable1,
	&VolumetricEfficiencyTable1},
	{&VolumetricEfficiencyTable2,
	&VolumetricEfficiencyTable2,
	&VolumetricEfficiencyTable2}
};
#endif

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!! VE table 1
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

float VE_COLS1[24] SPEEDDENSITYDATA = 
{100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400};

float VE_ROWS1[24] SPEEDDENSITYDATA =
{500,800,1200,1600,2000,2400,2800,3200,3600,4000,4200,4400,4600,4800,5000,5200,5400,5600,5800,6000,6400,6800,7200,7600};

short VE_DATA1[576] SPEEDDENSITYDATA =
{7150,	7449,	9958,	10351,	10665,	10794,	10943,	11089,	11177,	11242,	11307,	11383,	11459,	11535,	11611,	11687,	11763,	11839,	11915,	11991,	12067,	12143,	12219,	12295,
7398,	7646,	9694,	10132,	10499,	10716,	10956,	11076,	11190,	11255,	11320,	11396,	11472,	11548,	11624,	11700,	11776,	11852,	11928,	12004,	12080,	12156,	12232,	12308,
8081,	8447,	9658,	10002,	10486,	10716,	10813,	10959,	11207,	11272,	11346,	11422,	11498,	11574,	11650,	11726,	11802,	11878,	11954,	12030,	12106,	12182,	12258,	12334,
8456,	8796,	9659,	10001,	10497,	10742,	10853,	10998,	11229,	11301,	11385,	11474,	11563,	11651.9999999999,	11740.9999999999,	11829.9999999999,	11918.9999999999,	12007.9999999998,	12096.9999999998,	12185.9999999998,	12274.9999999998,	12363.9999999998,	12452.9999999998,	12541.9999999997,
8627,	8928,	9659,	10042,	10499,	10768,	10917,	11037,	11281,	11371,	11474,	11578,	11682,	11786,	11890.0000000001,	11994.0000000001,	12098.0000000001,	12202.0000000001,	12306.0000000002,	12410.0000000002,	12514.0000000002,	12618.0000000002,	12722.0000000002,	12826.0000000003,
8749,	9024,	9676,	10121,	10512,	10795,	10995,	11186,	11468,	11668,	11864,	12058,	12252,	12446,	12640.0000000001,	12834.0000000001,	13028.0000000001,	13222.0000000001,	13416.0000000002,	13610.0000000002,	13804.0000000002,	13998.0000000002,	14192.0000000002,	14386.0000000002,
8854,	9128,	9793,	10224,	10537,	10848,	11152,	11475,	11805,	12323,	12580,	12710,	12840,	12969.9999999999,	13099.9999999999,	13229.9999999999,	13359.9999999999,	13489.9999999998,	13619.9999999998,	13749.9999999998,	13879.9999999998,	14009.9999999998,	14139.9999999997,	14269.9999999997,
9073,	9333.99999999998,	9946,	10365,	10653,	10986,	11398,	11864,	12388,	12983,	13176,	13240,	13304,	13368,	13432,	13496,	13560,	13624,	13688,	13752,	13816,	13880,	13944,	14008,
9383,	9620,	10233,	10738,	11191,	11716,	12322,	12721,	13043,	13291,	13410,	13501,	13592,	13683,	13774,	13865,	13956,	14047,	14138,	14229,	14320,	14411,	14502,	14593,
9576,	9821,	10422,	10978,	11481,	11999,	12439,	12800,	13095,	13305,	13410,	13501,	13592,	13683,	13774,	13865,	13956,	14047,	14138,	14229,	14320,	14411,	14502,	14593,
9538,	9777,	10396,	10953,	11441,	11968,	12369,	12749,	13008,	13199,	13305,	13370,	13435,	13500,	13565.0000000001,	13630.0000000001,	13695.0000000001,	13760.0000000001,	13825.0000000002,	13890.0000000002,	13955.0000000002,	14020.0000000002,	14085.0000000002,	14150.0000000003,
9488,	9736,	10316,	10884,	11359,	11860,	12261,	12607,	12875,	13047,	13099,	13139,	13179,	13219,	13259,	13299,	13339,	13379,	13419,	13459,	13499,	13539,	13579,	13619,
9428,	9668,	10238,	10789,	11265,	11740,	12115,	12435,	12677,	12815,	12854,	12842,	12830,	12818,	12806,	12794,	12782,	12770,	12758,	12746,	12734,	12722,	12710,	12698,
9374,	9593,	10152,	10682,	11157,	11606,	11956,	12220,	12414,	12517,	12531,	12454,	12377,	12299.9999999999,	12222.9999999999,	12145.9999999999,	12068.9999999999,	11991.9999999998,	11914.9999999998,	11837.9999999998,	11760.9999999998,	11683.9999999998,	11606.9999999998,	11529.9999999997,
9308,	9528,	10061,	10572,	11022,	11420,	11733,	11936,	12090,	12130,	12080,	11951,	11822,	11693,	11564,	11435,	11306,	11177,	11048,	10919,	10790,	10661,	10532,	10403,
9242,	9464,	9972,	10452,	10853,	11215,	11477,	11630,	11706,	11679,	11564,	11435,	11306,	11177,	11048,	10919,	10790,	10661,	10532,	10403,	10274,	10145,	10016,	9886.99999999998,
9166,	9375,	9856,	10312,	10653,	10966,	11149,	11240,	11227,	11151,	11035,	10906,	10777,	10648,	10519.0000000001,	10390.0000000001,	10261.0000000001,	10132.0000000001,	10003.0000000002,	9874.00000000017,	9745.0000000002,	9616.00000000022,	9487.00000000024,	9358.00000000024,
9078,	9298,	9741,	10160,	10461,	10684,	10814,	10817,	10752,	10659,	10530,	10402,	10274,	10146,	10018,	9890,	9762,	9634,	9506,	9378,	9250,	9122,	8994,	8866,
8990,	9221,	9626,	10008,	10269,	10402,	10479,	10394,	10277,	10167,	10025,	9898,	9770.99999999998,	9643.99999999996,	9516.99999999993,	9389.99999999991,	9262.99999999989,	9135.99999999987,	9008.99999999985,	8881.99999999983,	8754.9999999998,	8627.99999999978,	8500.99999999976,	8373.99999999976,
8902,	9144,	9511,	9856.00000000004,	10077,	10119.9999999999,	10144,	9971.00000000005,	9802,	9675,	9520.00000000004,	9394,	9267.99999999996,	9141.99999999991,	9015.99999999987,	8889.99999999983,	8763.99999999978,	8637.99999999974,	8511.99999999969,	8385.99999999965,	8259.99999999961,	8133.99999999956,	8007.99999999952,	7881.99999999952,
8814,	9067,	9396,	9704.00000000007,	9885,	9837.99999999991,	9809,	9548.00000000007,	9327,	9183,	9015.00000000007,	8890,	8764.99999999993,	8639.99999999987,	8514.9999999998,	8389.99999999974,	8264.99999999967,	8139.99999999961,	8014.99999999954,	7889.99999999948,	7764.99999999941,	7639.99999999935,	7514.99999999928,	7389.99999999928,
8726,	8990,	9281,	9552.00000000009,	9693,	9555.99999999989,	9474,	9125.00000000009,	8852,	8691,	8510.00000000009,	8386,	8261.99999999991,	8137.99999999983,	8013.99999999974,	7889.99999999965,	7765.99999999956,	7641.99999999948,	7517.99999999939,	7393.9999999993,	7269.99999999921,	7145.99999999913,	7021.99999999904,	6897.99999999904,
8638,	8913,	9166,	9400.00000000011,	9501,	9273.99999999987,	9139,	8702.00000000011,	8377,	8199,	8005.00000000011,	7882,	7758.99999999989,	7635.99999999978,	7512.99999999967,	7389.99999999956,	7266.99999999946,	7143.99999999934,	7020.99999999924,	6897.99999999913,	6774.99999999902,	6651.99999999891,	6528.9999999988,	6405.9999999988,
8550,	8836,	9051,	9248.00000000013,	9309,	8991.99999999985,	8804,	8279.00000000013,	7902,	7707,	7500.00000000013,	7378,	7255.99999999987,	7133.99999999974,	7011.99999999961,	6889.99999999948,	6767.99999999935,	6645.99999999921,	6523.99999999908,	6401.99999999895,	6279.99999999882,	6157.99999999869,	6035.99999999856,	5913.99999999856
};

ThreeDTable VolumetricEfficiencyTable1  SPEEDDENSITYDATA = {
	.columnCount = 24,
	.rowCount = 24,
	.columnHeaderArray = VE_COLS1,
	.rowHeaderArray = VE_ROWS1,
	.tableCells = VE_DATA1,
	.tableType = UInt16Table3D,
	.multiplier = 0.0000457763672f,	
	.offset = 0.0 };
//! 1.5/32767  (0-2.00 range, 16bit precision)

#if SWITCH_HACKS
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!! VE table 2
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

float VE_COLS2[24] SPEEDDENSITYDATA = 
{100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400};

float VE_ROWS2[24] SPEEDDENSITYDATA =
{500,800,1200,1600,2000,2400,2800,3200,3600,4000,4200,4400,4600,4800,5000,5200,5400,5600,5800,6000,6400,6800,7200,7600};

short VE_DATA2[576] SPEEDDENSITYDATA =
{7150,	7449,	9958,	10351,	10665,	10794,	10943,	11089,	11177,	11242,	11307,	11383,	11459,	11535,	11611,	11687,	11763,	11839,	11915,	11991,	12067,	12143,	12219,	12295,
7398,	7646,	9694,	10132,	10499,	10716,	10956,	11076,	11190,	11255,	11320,	11396,	11472,	11548,	11624,	11700,	11776,	11852,	11928,	12004,	12080,	12156,	12232,	12308,
8081,	8447,	9658,	10002,	10486,	10716,	10813,	10959,	11207,	11272,	11346,	11422,	11498,	11574,	11650,	11726,	11802,	11878,	11954,	12030,	12106,	12182,	12258,	12334,
8456,	8796,	9659,	10001,	10497,	10742,	10853,	10998,	11229,	11301,	11385,	11474,	11563,	11651.9999999999,	11740.9999999999,	11829.9999999999,	11918.9999999999,	12007.9999999998,	12096.9999999998,	12185.9999999998,	12274.9999999998,	12363.9999999998,	12452.9999999998,	12541.9999999997,
8627,	8928,	9659,	10042,	10499,	10768,	10917,	11037,	11281,	11371,	11474,	11578,	11682,	11786,	11890.0000000001,	11994.0000000001,	12098.0000000001,	12202.0000000001,	12306.0000000002,	12410.0000000002,	12514.0000000002,	12618.0000000002,	12722.0000000002,	12826.0000000003,
8749,	9024,	9676,	10121,	10512,	10795,	10995,	11186,	11468,	11668,	11864,	12058,	12252,	12446,	12640.0000000001,	12834.0000000001,	13028.0000000001,	13222.0000000001,	13416.0000000002,	13610.0000000002,	13804.0000000002,	13998.0000000002,	14192.0000000002,	14386.0000000002,
8854,	9128,	9793,	10224,	10537,	10848,	11152,	11475,	11805,	12323,	12580,	12710,	12840,	12969.9999999999,	13099.9999999999,	13229.9999999999,	13359.9999999999,	13489.9999999998,	13619.9999999998,	13749.9999999998,	13879.9999999998,	14009.9999999998,	14139.9999999997,	14269.9999999997,
9073,	9333.99999999998,	9946,	10365,	10653,	10986,	11398,	11864,	12388,	12983,	13176,	13240,	13304,	13368,	13432,	13496,	13560,	13624,	13688,	13752,	13816,	13880,	13944,	14008,
9383,	9620,	10233,	10738,	11191,	11716,	12322,	12721,	13043,	13291,	13410,	13501,	13592,	13683,	13774,	13865,	13956,	14047,	14138,	14229,	14320,	14411,	14502,	14593,
9576,	9821,	10422,	10978,	11481,	11999,	12439,	12800,	13095,	13305,	13410,	13501,	13592,	13683,	13774,	13865,	13956,	14047,	14138,	14229,	14320,	14411,	14502,	14593,
9538,	9777,	10396,	10953,	11441,	11968,	12369,	12749,	13008,	13199,	13305,	13370,	13435,	13500,	13565.0000000001,	13630.0000000001,	13695.0000000001,	13760.0000000001,	13825.0000000002,	13890.0000000002,	13955.0000000002,	14020.0000000002,	14085.0000000002,	14150.0000000003,
9488,	9736,	10316,	10884,	11359,	11860,	12261,	12607,	12875,	13047,	13099,	13139,	13179,	13219,	13259,	13299,	13339,	13379,	13419,	13459,	13499,	13539,	13579,	13619,
9428,	9668,	10238,	10789,	11265,	11740,	12115,	12435,	12677,	12815,	12854,	12842,	12830,	12818,	12806,	12794,	12782,	12770,	12758,	12746,	12734,	12722,	12710,	12698,
9374,	9593,	10152,	10682,	11157,	11606,	11956,	12220,	12414,	12517,	12531,	12454,	12377,	12299.9999999999,	12222.9999999999,	12145.9999999999,	12068.9999999999,	11991.9999999998,	11914.9999999998,	11837.9999999998,	11760.9999999998,	11683.9999999998,	11606.9999999998,	11529.9999999997,
9308,	9528,	10061,	10572,	11022,	11420,	11733,	11936,	12090,	12130,	12080,	11951,	11822,	11693,	11564,	11435,	11306,	11177,	11048,	10919,	10790,	10661,	10532,	10403,
9242,	9464,	9972,	10452,	10853,	11215,	11477,	11630,	11706,	11679,	11564,	11435,	11306,	11177,	11048,	10919,	10790,	10661,	10532,	10403,	10274,	10145,	10016,	9886.99999999998,
9166,	9375,	9856,	10312,	10653,	10966,	11149,	11240,	11227,	11151,	11035,	10906,	10777,	10648,	10519.0000000001,	10390.0000000001,	10261.0000000001,	10132.0000000001,	10003.0000000002,	9874.00000000017,	9745.0000000002,	9616.00000000022,	9487.00000000024,	9358.00000000024,
9078,	9298,	9741,	10160,	10461,	10684,	10814,	10817,	10752,	10659,	10530,	10402,	10274,	10146,	10018,	9890,	9762,	9634,	9506,	9378,	9250,	9122,	8994,	8866,
8990,	9221,	9626,	10008,	10269,	10402,	10479,	10394,	10277,	10167,	10025,	9898,	9770.99999999998,	9643.99999999996,	9516.99999999993,	9389.99999999991,	9262.99999999989,	9135.99999999987,	9008.99999999985,	8881.99999999983,	8754.9999999998,	8627.99999999978,	8500.99999999976,	8373.99999999976,
8902,	9144,	9511,	9856.00000000004,	10077,	10119.9999999999,	10144,	9971.00000000005,	9802,	9675,	9520.00000000004,	9394,	9267.99999999996,	9141.99999999991,	9015.99999999987,	8889.99999999983,	8763.99999999978,	8637.99999999974,	8511.99999999969,	8385.99999999965,	8259.99999999961,	8133.99999999956,	8007.99999999952,	7881.99999999952,
8814,	9067,	9396,	9704.00000000007,	9885,	9837.99999999991,	9809,	9548.00000000007,	9327,	9183,	9015.00000000007,	8890,	8764.99999999993,	8639.99999999987,	8514.9999999998,	8389.99999999974,	8264.99999999967,	8139.99999999961,	8014.99999999954,	7889.99999999948,	7764.99999999941,	7639.99999999935,	7514.99999999928,	7389.99999999928,
8726,	8990,	9281,	9552.00000000009,	9693,	9555.99999999989,	9474,	9125.00000000009,	8852,	8691,	8510.00000000009,	8386,	8261.99999999991,	8137.99999999983,	8013.99999999974,	7889.99999999965,	7765.99999999956,	7641.99999999948,	7517.99999999939,	7393.9999999993,	7269.99999999921,	7145.99999999913,	7021.99999999904,	6897.99999999904,
8638,	8913,	9166,	9400.00000000011,	9501,	9273.99999999987,	9139,	8702.00000000011,	8377,	8199,	8005.00000000011,	7882,	7758.99999999989,	7635.99999999978,	7512.99999999967,	7389.99999999956,	7266.99999999946,	7143.99999999934,	7020.99999999924,	6897.99999999913,	6774.99999999902,	6651.99999999891,	6528.9999999988,	6405.9999999988,
8550,	8836,	9051,	9248.00000000013,	9309,	8991.99999999985,	8804,	8279.00000000013,	7902,	7707,	7500.00000000013,	7378,	7255.99999999987,	7133.99999999974,	7011.99999999961,	6889.99999999948,	6767.99999999935,	6645.99999999921,	6523.99999999908,	6401.99999999895,	6279.99999999882,	6157.99999999869,	6035.99999999856,	5913.99999999856
};

ThreeDTable VolumetricEfficiencyTable2  SPEEDDENSITYDATA = {
	.columnCount = 24,
	.rowCount = 24,
	.columnHeaderArray = VE_COLS2,
	.rowHeaderArray = VE_ROWS2,
	.tableCells = VE_DATA2,
	.tableType = UInt16Table3D,
	.multiplier = 0.0000457763672f,	
	.offset = 0.0 };
//! 1.5/32767  (0-2.00 range, 16bit precision)
#endif

#if SD_DMAP

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!! Delta Map compensation table
//!! Compensate SD-calculated MAF values based on delta map
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

float DMAP_COLS[7] SPEEDDENSITYDATA = 
{0, 333, 666, 1000, 1333, 1666, 2000};

float DMAP_ROWS[7] SPEEDDENSITYDATA = 
{500,800,1000,1200,2000,3000,6000};

short DMAP_DATA[49] SPEEDDENSITYDATA = 
{16384,16384,16384,16384,16384,16384,16384,
16384,16384,16384,16384,16384,16384,16384,
16384,16384,16384,16384,16384,16384,16384,
16384,16384,16384,16384,16384,16384,16384,
16384,16384,16384,16384,16384,16384,16384,
16384,16384,16384,16384,16384,16384,16384,
16384,16384,16384,16384,16384,16384,16384,};

ThreeDTable SDDeltaMapTable SPEEDDENSITYDATA = {
	.columnCount = 7,
	.rowCount = 7,
	.columnHeaderArray = DMAP_COLS,
	.rowHeaderArray = DMAP_ROWS,
	.tableCells = DMAP_DATA,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,
	.offset = 0 };
	//! 2/32767  (0-2.00 range, 16bit precision)
#endif

#if VE_RAMTUNING
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!! VE RAM table
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
ThreeDTable VolumetricEfficiencyRamTable  SPEEDDENSITYDATA = {
	.columnCount = 24,
	.rowCount = 24,
	.columnHeaderArray = &(pRamVariables.VERamCols),
	.rowHeaderArray = &(pRamVariables.VERamRows),
	.tableCells = &(pRamVariables.VERamData),
	.tableType = UInt16Table3D,
	.multiplier = 0.0000457763672f,	
	.offset = 0.0 };
//! 1.5/32767  (0-2.00 range, 16bit precision)
#endif

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!! Atmospheric compensation table
//!! Compensate SD-calculated MAF values based on atmospheric pressure and MAF.
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

float AC_COLS[7] SPEEDDENSITYDATA = 
{0, 333, 666, 1000, 1333, 1666, 2000};

float AC_ROWS[7] SPEEDDENSITYDATA = 
{465,525,585,645,705,765,825};

short AC_DATA[49] SPEEDDENSITYDATA = 
{16384,16384,16384,16384,16384,16384,16384,
16384,16384,16384,16384,16384,16384,16384,
16384,16384,16384,16384,16384,16384,16384,
16384,16384,16384,16384,16384,16384,16384,
16384,16384,16384,16384,16384,16384,16384,
16384,16384,16384,16384,16384,16384,16384,
16384,16384,16384,16384,16384,16384,16384,};

ThreeDTable AtmosphericCompensationTable SPEEDDENSITYDATA = {
	.columnCount = 7,
	.rowCount = 7,
	.columnHeaderArray = AC_COLS,
	.rowHeaderArray = AC_ROWS,
	.tableCells = AC_DATA,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,
	.offset = 0 };
	//! 2/32767  (0-2.00 range, 16bit precision)


      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    ////!! Blending Table                                                           
  //////!! Compensate SD-calculated MAF values based on atmospheric pressure and MAF.
////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

float BT_COLS[10] SPEEDDENSITYDATA =
{465,525,585,645,705,765,825,885,945,1005};

float BT_ROWS[10] SPEEDDENSITYDATA =
{0, 500, 1000, 1250, 1500, 2000, 2500, 3000, 3500, 4000};

unsigned char BT_DATA[100] SPEEDDENSITYDATA =
{0, 0, 0, 50, 150, 250, 250, 250, 250, 250,
0, 0, 0, 50, 150, 250, 250, 250, 250, 250,
0, 0, 0, 50, 150, 250, 250, 250, 250, 250,
0, 0, 0, 50, 150, 250, 250, 250, 250, 250,
0, 0, 0, 50, 150, 250, 250, 250, 250, 250,
0, 0, 0, 50, 150, 250, 250, 250, 250, 250,
0, 0, 0, 50, 150, 250, 250, 250, 250, 250,
0, 0, 0, 50, 150, 250, 250, 250, 250, 250,
0, 0, 0, 50, 150, 250, 250, 250, 250, 250,
0, 0, 0, 50, 150, 250, 250, 250, 250, 250};

ThreeDTable SDBlendingTable SPEEDDENSITYDATA = {
	.columnCount = 10,
	.rowCount = 10,
	.columnHeaderArray = BT_COLS,
	.rowHeaderArray = BT_ROWS,
	.tableCells = (short*)BT_DATA,
	.tableType = UInt8Table3D,
	.multiplier = 0.003921568627451f,
	.offset = 0 };
	//! 1.0/255  (0-1.00 range, 8bit precision)


#endif