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

/////////////////
//Constants
/////////////////
#if BOOST_HACKS
float RPMLockWGDC BOOSTDATA = 3000.0f;
float ThrottleLockWGDC BOOSTDATA = 85.0f;
float ValetModeMaxBoost BOOSTDATA = 1174;

#if SWITCH_HACKS
TableGroup PGWGTableGroup BOOSTDATA = {
	{&PGWGTable1i,
	&PGWGTable1s,
	&PGWGTable1ss},
	{&PGWGTable1i,
	&PGWGTable2s,
	&PGWGTable2ss}
};

TableGroup PGTBTableGroup BOOSTDATA = {
	{&PGTBTable1i,
	&PGTBTable1s,
	&PGTBTable1ss},
	{&PGTBTable1i,
	&PGTBTable2s,
	&PGTBTable2ss}
};

/*
TableGroup WGDCInitialTableGroup BOOSTDATA = {
	{&WGDCInitialTable1i,
	&WGDCInitialTable1s,
	&WGDCInitialTable1ss},
	{&WGDCInitialTable1i,
	&WGDCInitialTable2s,
	&WGDCInitialTable2ss}
};
*/

/*
TableGroup WGDCMaxTableGroup BOOSTDATA = {
	{&WGDCMaxTable1i,
	&WGDCMaxTable1s,
	&WGDCMaxTable1ss},
	{&WGDCMaxTable1i,
	&WGDCMaxTable2s,
	&WGDCMaxTable2ss}
};*/

TableGroup TargetBoostTableGroup BOOSTDATA = {
	{&TargetBoostTable1i,
	&TargetBoostTable1s,
	&TargetBoostTable1ss},
	{&TargetBoostTable1i,
	&TargetBoostTable2s,
	&TargetBoostTable2ss}
};
#endif 

///////////////
//PGWG TABLE 1 i
///////////////
ThreeDTable PGWGTable1i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
float PGWGCols1i[6] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{1,2,3,4,5,6};
float PGWGRows1i[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200};
short PGWGData1i[96] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120};

ThreeDTable PGWGTable1i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 6,
	.rowCount = 16,
	.columnHeaderArray = PGWGCols1i,
	.rowHeaderArray = PGWGRows1i,
	.tableCells = PGWGData1i,
	.tableType = UInt16Table3D,
	.multiplier =  0.00390625f,//0x3B800000
	.offset = 0 };	
	
	
	
#if SWITCH_HACKS
///////////////
//PGWG TABLE 1 s
///////////////
ThreeDTable PGWGTable1s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
float PGWGCols1s[6] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{1,2,3,4,5,6};
float PGWGRows1s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200};
short PGWGData1s[96] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120};

ThreeDTable PGWGTable1s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 6,
	.rowCount = 16,
	.columnHeaderArray = PGWGCols1s,
	.rowHeaderArray = PGWGRows1s,
	.tableCells = PGWGData1s,
	.tableType = UInt16Table3D,
	.multiplier =  0.00390625f,//0x3B800000
	.offset = 0 };	
	
	
///////////////
//PGWG TABLE 2 s
///////////////
ThreeDTable PGWGTable2s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
float PGWGCols2s[6] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{1,2,3,4,5,6};
float PGWGRows2s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200};
short PGWGData2s[96] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120,
0,25120,25120,25120,25120,25120};

ThreeDTable PGWGTable2s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 6,
	.rowCount = 16,
	.columnHeaderArray = PGWGCols2s,
	.rowHeaderArray = PGWGRows2s,
	.tableCells = PGWGData2s,
	.tableType = UInt16Table3D,
	.multiplier = 0.00390625f,//0x3B800000	
	.offset = 0 };	
	
///////////////
//PGWG TABLE 1 ss
///////////////
ThreeDTable PGWGTable1ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
float PGWGCols1ss[6] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{1,2,3,4,5,6};
float PGWGRows1ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200};
short PGWGData1ss[96] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{0,0,5120,5120,5120,5120,
0,0,5120,5120,5120,5120,
0,0,2560,2560,2560,2560,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0};

ThreeDTable PGWGTable1ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 6,
	.rowCount = 16,
	.columnHeaderArray = PGWGCols1ss,
	.rowHeaderArray = PGWGRows1ss,
	.tableCells = PGWGData1ss,
	.tableType = UInt16Table3D,
	.multiplier =  0.00390625f,//0x3B800000
	.offset = 0 };	
	
	
///////////////
//PGWG TABLE 2 ss
///////////////
ThreeDTable PGWGTable2ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
float PGWGCols2ss[6] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{1,2,3,4,5,6};
float PGWGRows2ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200};
short PGWGData2ss[96] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{0,0,5120,5120,5120,5120,
0,0,5120,5120,5120,5120,
0,0,2560,2560,2560,2560,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0};

ThreeDTable PGWGTable2ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 6,
	.rowCount = 16,
	.columnHeaderArray = PGWGCols2ss,
	.rowHeaderArray = PGWGRows2ss,
	.tableCells = PGWGData2ss,
	.tableType = UInt16Table3D,
	.multiplier = 0.00390625f,//0x3B800000	
	.offset = 0 };	
#endif

///////////////
//PGWG RAM LUT
///////////////
#if PGWG_RAMTUNING
ThreeDTable PGWGRamTable __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 6,
	.rowCount = 16,
	.columnHeaderArray = &(pRamVariables->PGWGRamCols),
	.rowHeaderArray = &(pRamVariables->PGWGRamRows),
	.tableCells = &(pRamVariables->PGWGRamData),
	.tableType = UInt16Table3D,
	.multiplier = 0.00390625f,//0x3B800000	
	.offset = 0 };
#endif

///////////////
//PGTB TABLE 1i
///////////////
ThreeDTable PGTBTable1i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
float PGTBCols1i[6] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{1,2,3,4,5,6};
float PGTBRows1i[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200};
short PGTBData1i[96] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{760,760,760,760,760,760,
863,863,863,863,863,863,
967,967,967,967,967,967,
1070,1070,1070,1070,1070,1070,
1174,1174,1174,1174,1174,1174,
1174,1174,1174,1174,1174,1174,
1174,1174,1225,1225,1225,1225,
1174,1174,1277,1277,1277,1277,
1174,1174,1277,1277,1277,1277,
1174,1174,1277,1277,1277,1277,
1174,1174,1277,1277,1277,1277,
1174,1174,1277,1277,1277,1277,
1174,1174,1277,1277,1277,1277,
1174,1174,1277,1277,1277,1277,
1174,1174,1277,1277,1277,1277,
1174,1174,1277,1277,1277,1277};

ThreeDTable PGTBTable1i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 6,
	.rowCount = 16,
	.columnHeaderArray = PGTBCols1i,
	.rowHeaderArray = PGTBRows1i,
	.tableCells = PGTBData1i,
	.tableType = UInt16Table3D,
	.multiplier = 1.0f,//0x3F800000	
	.offset = 0 };	
	
	

#if SWITCH_HACKS
///////////////
//PGTB TABLE 1s
///////////////
ThreeDTable PGTBTable1s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
float PGTBCols1s[6] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{1,2,3,4,5,6};
float PGTBRows1s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200};
short PGTBData1s[96] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{1174,1174,1174,1174,1174,1174,
1174,1174,1174,1174,1174,1174,
1174,1174,1174,1174,1174,1174,
1277,1277,1277,1277,1277,1277,
1381,1381,1381,1381,1381,1381,
1381,1381,1381,1381,1381,1381,
1381,1484,1484,1484,1484,1484,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536};

ThreeDTable PGTBTable1s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 6,
	.rowCount = 16,
	.columnHeaderArray = PGTBCols1s,
	.rowHeaderArray = PGTBRows1s,
	.tableCells = PGTBData1s,
	.tableType = UInt16Table3D,
	.multiplier = 1.0f,//0x3F800000	
	.offset = 0 };	
	
	
///////////////
//PGTB TABLE 2s
///////////////
ThreeDTable PGTBTable2s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
float PGTBCols2s[6] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{1,2,3,4,5,6};
float PGTBRows2s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200};
short PGTBData2s[96] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{1174,1174,1174,1174,1174,1174,
1174,1174,1174,1174,1174,1174,
1174,1174,1174,1174,1174,1174,
1277,1277,1277,1277,1277,1277,
1381,1381,1381,1381,1381,1381,
1381,1381,1381,1381,1381,1381,
1381,1484,1484,1484,1484,1484,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536};

ThreeDTable PGTBTable2s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 6,
	.rowCount = 16,
	.columnHeaderArray = PGTBCols2s,
	.rowHeaderArray = PGTBRows2s,
	.tableCells = PGTBData2s,
	.tableType = UInt16Table3D,
	.multiplier = 1.0f,//0x3F800000	
	.offset = 0 };


///////////////
//PGTB TABLE 1ss
///////////////
ThreeDTable PGTBTable1ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
float PGTBCols1ss[6] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{1,2,3,4,5,6};
float PGTBRows1ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200};
short PGTBData1ss[96] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{1174,1174,1174,1174,1174,1174,
1174,1174,1174,1174,1174,1174,
1174,1174,1174,1174,1174,1174,
1277,1277,1277,1277,1277,1277,
1381,1381,1381,1381,1381,1381,
1381,1381,1381,1381,1381,1381,
1381,1484,1484,1484,1484,1484,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536};

ThreeDTable PGTBTable1ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 6,
	.rowCount = 16,
	.columnHeaderArray = PGTBCols1ss,
	.rowHeaderArray = PGTBRows1ss,
	.tableCells = PGTBData1ss,
	.tableType = UInt16Table3D,
	.multiplier = 1.0f,//0x3F800000	
	.offset = 0 };	
	
	
///////////////
//PGTB TABLE 2ss
///////////////
ThreeDTable PGTBTable2ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
float PGTBCols2ss[6] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{1,2,3,4,5,6};
float PGTBRows2ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200};
short PGTBData2ss[96] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{1174,1174,1174,1174,1174,1174,
1174,1174,1174,1174,1174,1174,
1174,1174,1174,1174,1174,1174,
1277,1277,1277,1277,1277,1277,
1381,1381,1381,1381,1381,1381,
1381,1381,1381,1381,1381,1381,
1381,1484,1484,1484,1484,1484,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536,
1381,1536,1536,1536,1536,1536};

ThreeDTable PGTBTable2ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 6,
	.rowCount = 16,
	.columnHeaderArray = PGTBCols2ss,
	.rowHeaderArray = PGTBRows2ss,
	.tableCells = PGTBData2ss,
	.tableType = UInt16Table3D,
	.multiplier = 1.0f,//0x3F800000	
	.offset = 0 };
#endif

///////////////
//PGTB RAM LUT
///////////////
#if PGWG_RAMTUNING
ThreeDTable PGTBRamTable __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 6,
	.rowCount = 16,
	.columnHeaderArray = &(pRamVariables->PGTBRamCols),
	.rowHeaderArray = &(pRamVariables->PGTBRamRows),
	.tableCells = &(pRamVariables->PGTBRamData),
	.tableType = UInt16Table3D,
	.multiplier = 1.0,//0x3B800000
	.offset = 0 };	
#endif


/*
///////////////////
//WGDC Initial Table 1i LUT
///////////////////
ThreeDTable WGDCInitialTable1i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
float WGDCInitialCols1i[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{100,120,130,140,160,170,190,210,230,240,260,280,300,320,340,350};
float WGDCInitialRows1i[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200};
short WGDCInitialData1i[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,164,
0,0,0,0,197,235,235,470,522,581,645,681,717,796,885,885,
0,0,0,0,394,470,470,940,1045,1161,1290,1362,1434,1593,1770,1770,
0,0,0,0,590,706,706,1410,1567,1742,1935,2042,2150,2389,2654,2654,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2723,2866,3185,3539,3539,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2723,2866,3185,3670,3670,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3493,3801,3801,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3558,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3558,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3558,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3539,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3539,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3539,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3539,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3539,3932,3932,
0,0,0,0,786,1151,1516,1881,2090,2322,2580,2866,3185,3539,3932,3932};

ThreeDTable WGDCInitialTable1i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = WGDCInitialCols1i,
	.rowHeaderArray = WGDCInitialRows1i,
	.tableCells = WGDCInitialData1i,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)


#if SWITCH_HACKS
///////////////////
//WGDC Initial Table 1s LUT
///////////////////
ThreeDTable WGDCInitialTable1s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
float WGDCInitialCols1s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{100,120,130,140,160,170,190,210,230,240,260,280,300,320,340,350};
float WGDCInitialRows1s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200};
short WGDCInitialData1s[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,164,
0,0,0,0,197,235,235,470,522,581,645,681,717,796,885,885,
0,0,0,0,394,470,470,940,1045,1161,1290,1362,1434,1593,1770,1770,
0,0,0,0,590,706,706,1410,1567,1742,1935,2042,2150,2389,2654,2654,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2723,2866,3185,3539,3539,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2723,2866,3185,3670,3670,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3493,3801,3801,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3558,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3558,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3558,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3539,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3539,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3539,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3539,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3539,3932,3932,
0,0,0,0,786,1151,1516,1881,2090,2322,2580,2866,3185,3539,3932,3932};

ThreeDTable WGDCInitialTable1s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = WGDCInitialCols1s,
	.rowHeaderArray = WGDCInitialRows1s,
	.tableCells = WGDCInitialData1s,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)

///////////////////
//WGDC Initial Table 2s LUT
///////////////////
ThreeDTable WGDCInitialTable2s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
float WGDCInitialCols2s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{100,120,130,140,160,170,190,210,230,240,260,280,300,320,340,350};
float WGDCInitialRows2s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200};
short WGDCInitialData2s[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,164,
0,0,0,0,197,235,235,470,522,581,645,681,717,796,885,885,
0,0,0,0,394,470,470,940,1045,1161,1290,1362,1434,1593,1770,1770,
0,0,0,0,590,706,706,1410,1567,1742,1935,2042,2150,2389,2654,2654,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2723,2866,3185,3539,3539,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2723,2866,3185,3670,3670,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3493,3801,3801,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3558,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3558,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3558,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3539,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3539,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3539,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3539,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3539,3932,3932,
0,0,0,0,786,1151,1516,1881,2090,2322,2580,2866,3185,3539,3932,3932};

ThreeDTable WGDCInitialTable2s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = WGDCInitialCols2s,
	.rowHeaderArray = WGDCInitialRows2s,
	.tableCells = WGDCInitialData2s,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,	
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)

///////////////////
//WGDC Initial Table 1ss LUT
///////////////////
ThreeDTable WGDCInitialTable1ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
float WGDCInitialCols1ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{100,120,130,140,160,170,190,210,230,240,260,280,300,320,340,350};
float WGDCInitialRows1ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200};
short WGDCInitialData1ss[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,164,
0,0,0,0,197,235,235,470,522,581,645,681,717,796,885,885,
0,0,0,0,394,470,470,940,1045,1161,1290,1362,1434,1593,1770,1770,
0,0,0,0,590,706,706,1410,1567,1742,1935,2042,2150,2389,2654,2654,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2723,2866,3185,3539,3539,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2723,2866,3185,3670,3670,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3493,3801,3801,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3558,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3558,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3558,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3539,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3539,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3539,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3539,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3539,3932,3932,
0,0,0,0,786,1151,1516,1881,2090,2322,2580,2866,3185,3539,3932,3932};

ThreeDTable WGDCInitialTable1ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = WGDCInitialCols1ss,
	.rowHeaderArray = WGDCInitialRows1ss,
	.tableCells = WGDCInitialData1ss,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)

///////////////////
//WGDC Initial Table 2ss LUT
///////////////////
ThreeDTable WGDCInitialTable2ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
float WGDCInitialCols2ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{100,120,130,140,160,170,190,210,230,240,260,280,300,320,340,350};
float WGDCInitialRows2ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200};
short WGDCInitialData2ss[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,164,
0,0,0,0,197,235,235,470,522,581,645,681,717,796,885,885,
0,0,0,0,394,470,470,940,1045,1161,1290,1362,1434,1593,1770,1770,
0,0,0,0,590,706,706,1410,1567,1742,1935,2042,2150,2389,2654,2654,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2723,2866,3185,3539,3539,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2723,2866,3185,3670,3670,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3493,3801,3801,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3558,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3558,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3558,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3539,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3539,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3539,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3539,3932,3932,
0,0,0,0,786,940,1410,1881,2090,2322,2580,2866,3185,3539,3932,3932,
0,0,0,0,786,1151,1516,1881,2090,2322,2580,2866,3185,3539,3932,3932};

ThreeDTable WGDCInitialTable2ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = WGDCInitialCols2ss,
	.rowHeaderArray = WGDCInitialRows2ss,
	.tableCells = WGDCInitialData2ss,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,	
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)
#endif

///////////////
//WGDC Initial RAM LUT
///////////////
#if WGDC_RAMTUNING
ThreeDTable WGDCInitialRamTable __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = &(pRamVariables->WGDCInitialRamCols),
	.rowHeaderArray = &(pRamVariables->WGDCInitialRamRows),
	.tableCells = &(pRamVariables->WGDCInitialRamData),
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,
	.offset = 0 };				//! /32767  (0- range, 16bit precision)
#endif

///////////////////
//WGDC Max Table 1i LUT
///////////////////
ThreeDTable WGDCMaxTable1i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
float WGDCMaxCols1i[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{100,120,130,140,160,170,190,210,230,240,260,280,300,320,340,350};
float WGDCMaxRows1i[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200};
short WGDCMaxData1i[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,295,353,353,706,784,871,967,1021,1075,1194,1327,1327,
0,0,0,0,590,706,706,1410,1567,1741,1934,2042,2150,2389,2654,2654,
0,0,0,0,884,1058,1058,2116,2351,2612,2903,3064,3224,3583,3982,3982,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4085,4300,4777,5309,5309,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4085,4300,4777,5506,5506,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5239,5701,5701,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5338,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5338,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5338,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1727,2274,2821,3134,3484,3870,4300,4777,5309,5898,5898};

ThreeDTable WGDCMaxTable1i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = WGDCMaxCols1i,
	.rowHeaderArray = WGDCMaxRows1i,
	.tableCells = WGDCMaxData1i,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)


#if SWITCH_HACKS
///////////////////
//WGDC Max Table 1s LUT
///////////////////
ThreeDTable WGDCMaxTable1s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
float WGDCMaxCols1s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{100,120,130,140,160,170,190,210,230,240,260,280,300,320,340,350};
float WGDCMaxRows1s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200};
short WGDCMaxData1s[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,295,353,353,706,784,871,967,1021,1075,1194,1327,1327,
0,0,0,0,590,706,706,1410,1567,1741,1934,2042,2150,2389,2654,2654,
0,0,0,0,884,1058,1058,2116,2351,2612,2903,3064,3224,3583,3982,3982,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4085,4300,4777,5309,5309,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4085,4300,4777,5506,5506,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5239,5701,5701,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5338,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5338,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5338,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1727,2274,2821,3134,3484,3870,4300,4777,5309,5898,5898};

ThreeDTable WGDCMaxTable1s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = WGDCMaxCols1s,
	.rowHeaderArray = WGDCMaxRows1s,
	.tableCells = WGDCMaxData1s,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)
	
///////////////////
//WGDC Max Table 2s LUT
///////////////////
ThreeDTable WGDCMaxTable2s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
float WGDCMaxCols2s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{100,120,130,140,160,170,190,210,230,240,260,280,300,320,340,350};
float WGDCMaxRows2s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200};
short WGDCMaxData2s[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,295,353,353,706,784,871,967,1021,1075,1194,1327,1327,
0,0,0,0,590,706,706,1410,1567,1741,1934,2042,2150,2389,2654,2654,
0,0,0,0,884,1058,1058,2116,2351,2612,2903,3064,3224,3583,3982,3982,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4085,4300,4777,5309,5309,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4085,4300,4777,5506,5506,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5239,5701,5701,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5338,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5338,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5338,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1727,2274,2821,3134,3484,3870,4300,4777,5309,5898,5898};

ThreeDTable WGDCMaxTable2s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = WGDCMaxCols2s,
	.rowHeaderArray = WGDCMaxRows2s,
	.tableCells = WGDCMaxData2s,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)
	
///////////////////
//WGDC Max Table 1ss LUT
///////////////////
ThreeDTable WGDCMaxTable1ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
float WGDCMaxCols1ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{100,120,130,140,160,170,190,210,230,240,260,280,300,320,340,350};
float WGDCMaxRows1ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200};
short WGDCMaxData1ss[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,295,353,353,706,784,871,967,1021,1075,1194,1327,1327,
0,0,0,0,590,706,706,1410,1567,1741,1934,2042,2150,2389,2654,2654,
0,0,0,0,884,1058,1058,2116,2351,2612,2903,3064,3224,3583,3982,3982,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4085,4300,4777,5309,5309,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4085,4300,4777,5506,5506,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5239,5701,5701,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5338,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5338,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5338,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1727,2274,2821,3134,3484,3870,4300,4777,5309,5898,5898};

ThreeDTable WGDCMaxTable1ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = WGDCMaxCols1ss,
	.rowHeaderArray = WGDCMaxRows1ss,
	.tableCells = WGDCMaxData1ss,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)
	
///////////////////
//WGDC Max Table 2ss LUT
///////////////////
ThreeDTable WGDCMaxTable2ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
float WGDCMaxCols2ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{100,120,130,140,160,170,190,210,230,240,260,280,300,320,340,350};
float WGDCMaxRows2ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200};
short WGDCMaxData2ss[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,295,353,353,706,784,871,967,1021,1075,1194,1327,1327,
0,0,0,0,590,706,706,1410,1567,1741,1934,2042,2150,2389,2654,2654,
0,0,0,0,884,1058,1058,2116,2351,2612,2903,3064,3224,3583,3982,3982,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4085,4300,4777,5309,5309,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4085,4300,4777,5506,5506,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5239,5701,5701,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5338,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5338,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5338,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1727,2274,2821,3134,3484,3870,4300,4777,5309,5898,5898};

ThreeDTable WGDCMaxTable2ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = WGDCMaxCols2ss,
	.rowHeaderArray = WGDCMaxRows2ss,
	.tableCells = WGDCMaxData2ss,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)
#endif

///////////////
//WGDC Max RAM LUT
///////////////
#if WGDC_RAMTUNING
ThreeDTable WGDCMaxRamTable __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = &(pRamVariables->WGDCMaxRamCols),
	.rowHeaderArray = &(pRamVariables->WGDCMaxRamRows),
	.tableCells = &(pRamVariables->WGDCMaxRamData),
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,
	.offset = 0 };				//! /32767  (0- range, 16bit precision)
#endif
*/



///////////////////
//WGDC Initial Table
///////////////////
ThreeDTable tInitialWasteGate __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
float tInitialWasteGateCol[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{760,1070.289672851562,1122.004638671875,1173.71960449218,1225.4345703125,1277.1494140625,1328.864379882812,1380.579345703125,1432.294311523438,1484.00927734375,1535.724243164062,1587.439208984375,1639.154052734375,1690.869018554688,1742.583984375,1794.298950195312};
float tInitialWasteGateRow[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200};
short tInitialWasteGateData[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,295,353,353,706,784,871,967,1021,1075,1194,1327,1327,
0,0,0,0,590,706,706,1410,1567,1741,1934,2042,2150,2389,2654,2654,
0,0,0,0,884,1058,1058,2116,2351,2612,2903,3064,3224,3583,3982,3982,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4085,4300,4777,5309,5309,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4085,4300,4777,5506,5506,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5239,5701,5701,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5338,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5338,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5338,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1727,2274,2821,3134,3484,3870,4300,4777,5309,5898,5898};

ThreeDTable tInitialWasteGate __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = tInitialWasteGateCol,
	.rowHeaderArray = tInitialWasteGateRow,
	.tableCells = tInitialWasteGateData,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,
	.offset = 0 };	

///////////////////
//WGDC Max Table
///////////////////
ThreeDTable tMaximumWasteGate __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
ThreeDTable tMaximumWasteGate __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
float tMaximumWasteGateCol[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{760,1070.289672851562,1122.004638671875,1173.71960449218,1225.4345703125,1277.1494140625,1328.864379882812,1380.579345703125,1432.294311523438,1484.00927734375,1535.724243164062,1587.439208984375,1639.154052734375,1690.869018554688,1742.583984375,1794.298950195312};
float tMaximumWasteGateRow[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200};
short tMaximumWasteGateData[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,295,353,353,706,784,871,967,1021,1075,1194,1327,1327,
0,0,0,0,590,706,706,1410,1567,1741,1934,2042,2150,2389,2654,2654,
0,0,0,0,884,1058,1058,2116,2351,2612,2903,3064,3224,3583,3982,3982,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4085,4300,4777,5309,5309,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4085,4300,4777,5506,5506,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5239,5701,5701,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5338,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5338,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5338,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1410,2116,2821,3134,3484,3870,4300,4777,5309,5898,5898,
0,0,0,0,1180,1727,2274,2821,3134,3484,3870,4300,4777,5309,5898,5898};

ThreeDTable tMaximumWasteGate __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = tMaximumWasteGateCol,
	.rowHeaderArray = tMaximumWasteGateRow,
	.tableCells = tMaximumWasteGateData,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,
	.offset = 0 };		

///////////////////
//Target Boost Table 1i
///////////////////
ThreeDTable TargetBoostTable1i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
float TBCols1i[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{100,120,130,140,160,170,190,210,230,240,260,280,300,320,340,350};
float TBRows1i[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200};
short TBData1i[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,819,980,980,1959,2177,2419,2687,2837,2986,3318,3687,3687,
0,0,0,0,1639,1959,1959,3918,4354,4838,5375,5673,5972,6636,7373,7373,
0,0,0,0,2458,2939,2939,5878,6531,7256,8062,8510,8958,9953,11060,11060,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11347,11944,13271,14746,14746,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11347,11944,13271,15292,15292,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14554,15838,15838,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14828,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14828,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14828,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14746,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14746,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14746,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14746,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14746,16384,16384,
0,0,0,0,3277,4797,6317,7837,8708,9675,10750,11944,13271,14746,16384,16384};

ThreeDTable TargetBoostTable1i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = TBCols1i,
	.rowHeaderArray = TBRows1i,
	.tableCells = TBData1i,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,	
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)
	

#if SWITCH_HACKS
///////////////////
//Target Boost Table 1s
///////////////////
ThreeDTable TargetBoostTable1s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
float TBCols1s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{100,120,130,140,160,170,190,210,230,240,260,280,300,320,340,350};
float TBRows1s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200};
short TBData1s[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,819,980,980,1959,2177,2419,2687,2837,2986,3318,3687,3687,
0,0,0,0,1639,1959,1959,3918,4354,4838,5375,5673,5972,6636,7373,7373,
0,0,0,0,2458,2939,2939,5878,6531,7256,8062,8510,8958,9953,11060,11060,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11347,11944,13271,14746,14746,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11347,11944,13271,15292,15292,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14554,15838,15838,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14828,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14828,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14828,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14746,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14746,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14746,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14746,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14746,16384,16384,
0,0,0,0,3277,4797,6317,7837,8708,9675,10750,11944,13271,14746,16384,16384};

ThreeDTable TargetBoostTable1s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = TBCols1s,
	.rowHeaderArray = TBRows1s,
	.tableCells = TBData1s,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,	
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)
	
///////////////////
//Target Boost Table 2s
///////////////////
ThreeDTable TargetBoostTable2s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
float TBCols2s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{100,120,130,140,160,170,190,210,230,240,260,280,300,320,340,350};
float TBRows2s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200};
short TBData2s[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,819,980,980,1959,2177,2419,2687,2837,2986,3318,3687,3687,
0,0,0,0,1639,1959,1959,3918,4354,4838,5375,5673,5972,6636,7373,7373,
0,0,0,0,2458,2939,2939,5878,6531,7256,8062,8510,8958,9953,11060,11060,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11347,11944,13271,14746,14746,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11347,11944,13271,15292,15292,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14554,15838,15838,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14828,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14828,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14828,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14746,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14746,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14746,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14746,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14746,16384,16384,
0,0,0,0,3277,4797,6317,7837,8708,9675,10750,11944,13271,14746,16384,16384};

ThreeDTable TargetBoostTable2s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = TBCols2s,
	.rowHeaderArray = TBRows2s,
	.tableCells = TBData2s,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,	
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)

///////////////////
//Target Boost Table 1ss
///////////////////
ThreeDTable TargetBoostTable1ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
float TBCols1ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{100,120,130,140,160,170,190,210,230,240,260,280,300,320,340,350};
float TBRows1ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200};
short TBData1ss[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,819,980,980,1959,2177,2419,2687,2837,2986,3318,3687,3687,
0,0,0,0,1639,1959,1959,3918,4354,4838,5375,5673,5972,6636,7373,7373,
0,0,0,0,2458,2939,2939,5878,6531,7256,8062,8510,8958,9953,11060,11060,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11347,11944,13271,14746,14746,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11347,11944,13271,15292,15292,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14554,15838,15838,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14828,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14828,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14828,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14746,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14746,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14746,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14746,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14746,16384,16384,
0,0,0,0,3277,4797,6317,7837,8708,9675,10750,11944,13271,14746,16384,16384};

ThreeDTable TargetBoostTable1ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = TBCols1ss,
	.rowHeaderArray = TBRows1ss,
	.tableCells = TBData1ss,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,	
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)
	
///////////////////
//Target Boost Table 2ss
///////////////////
ThreeDTable TargetBoostTable2ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
float TBCols2ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{100,120,130,140,160,170,190,210,230,240,260,280,300,320,340,350};
float TBRows2ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200};
short TBData2ss[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,819,980,980,1959,2177,2419,2687,2837,2986,3318,3687,3687,
0,0,0,0,1639,1959,1959,3918,4354,4838,5375,5673,5972,6636,7373,7373,
0,0,0,0,2458,2939,2939,5878,6531,7256,8062,8510,8958,9953,11060,11060,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11347,11944,13271,14746,14746,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11347,11944,13271,15292,15292,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14554,15838,15838,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14828,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14828,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14828,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14746,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14746,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14746,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14746,16384,16384,
0,0,0,0,3277,3918,5878,7837,8708,9675,10750,11944,13271,14746,16384,16384,
0,0,0,0,3277,4797,6317,7837,8708,9675,10750,11944,13271,14746,16384,16384};

ThreeDTable TargetBoostTable2ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = TBCols2ss,
	.rowHeaderArray = TBRows2ss,
	.tableCells = TBData2ss,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,	
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)
#endif
	
#endif