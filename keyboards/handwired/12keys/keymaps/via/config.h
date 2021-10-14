/*
Copyright 2021 greyhatmiddleman

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


// the following condition is used to overwrite vendor and product id
// so that via only locates this specific devices
#ifdef VENDOR_ID
#undef VENDOR_ID
#define VENDOR_ID    0xFEED
#endif

#ifdef PRODUCT_ID
#undef PRODUCT_ID
#define PRODUCT_ID   0x1121
#endif

// #define TAPPING_TERM 175
