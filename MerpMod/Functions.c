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

float Abs(float input)
{
	if(input > 0.0f)
		return input;
	else
		return input * -1.0f;
}

unsigned char limit_u8(float input)
{
	if(input <0) return 0;
	else if(input > 255) return 255;
	else return (unsigned char)input;	
}

unsigned short limit_u16(float input)
{
	if(input <0) return 0;
	else if(input > 65535) return 65535;
	else return (unsigned short)input;	
}

unsigned long limit_u32(float input)
{
	if(input <0) return 0;
	else if(input > 4294967295) return 4294967295;
	else return (unsigned long)input;	
}
