/* -*- c-basic-offset: 8 -*-
   rdesktop: A Remote Desktop Protocol client.
   Protocol services - RDP5 short form PDU processing
   Copyright (C) Matthew Chapman <matthewc.unsw.edu.au> 1999-2008
   Copyright 2003-2008 Erik Forsberg <forsberg@cendio.se> for Cendio AB

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "rdesktop.h"
#include <time.h>
#include <sys/time.h>

//zhongbin
extern RD_BOOL NOT_END;
extern RD_BOOL Toggled; 
/*order type processed by process_orders() orders.c line 1309*/
uint16 order_count = 0;
uint16 destblt_count = 0;
uint16 patblt_count = 0;
uint16 screenblt_count = 0;
uint16 line_count = 0;
uint16 rect_count = 0;
uint16 desksave_count = 0;
uint16 memblt_count = 0;
uint16 triblt_count = 0;
uint16 polygon_count = 0;
uint16 polygon2_count = 0;
uint16 polyline_count = 0;
uint16 ellipse_count = 0;
uint16 ellipse2_count = 0;
uint16 text2_count = 0;

//uint16 second_order_count = 0;

extern uint8 *g_next_packet;

extern RDPCOMP g_mppc_dict;

void
rdp5_process(STREAM s)
{
	uint16 length, count, x, y;
	uint8 type, ctype;
	uint8 *next;

	uint32 roff, rlen;
	struct stream *ns = &(g_mppc_dict.ns);
	struct stream *ts;
/*print the rdp5 data if uncommented*/
//#if 0
	//if((s->end - s->p) < 25){
	//if( Toggled && NOT_END && ((s->end - s->p) < 25)){
	//	printf("##RDP5 data##\n");
	//	hexdump(s->p, s->end - s->p);
	//}
//#endif

	ui_begin_update();
//	order_count = 0;//zhongbin
//	second_order_count = 0;
//	if(Toggled && NOT_END){
//		printf("rdp5_process was called at time %d\n", time((time_t *)NULL));//zhongbin
//		printf("rdp5_process was called(stream length:%d)\n", s->end - s->p);//zhongbin
//	}
	while (s->p < s->end)
	{
		in_uint8(s, type);
		if (type & RDP5_COMPRESSED)
		{
			in_uint8(s, ctype);
			in_uint16_le(s, length);
			type ^= RDP5_COMPRESSED;
		}
		else
		{
			ctype = 0;
			in_uint16_le(s, length);
		}
		g_next_packet = next = s->p + length;

		if (ctype & RDP_MPPC_COMPRESSED)
		{
			if (mppc_expand(s->p, length, ctype, &roff, &rlen) == -1)
				error("error while decompressing packet\n");

			/* allocate memory and copy the uncompressed data into the temporary stream */
			ns->data = (uint8 *) xrealloc(ns->data, rlen);

			memcpy((ns->data), (unsigned char *) (g_mppc_dict.hist + roff), rlen);

			ns->size = rlen;
			ns->end = (ns->data + ns->size);
			ns->p = ns->data;
			ns->rdp_hdr = ns->p;

			ts = ns;
		}
		else
			ts = s;
		switch (type)
		{
			case 0:	/* update orders */
			//	if(Toggled && NOT_END){
			//		printf("	update orders\n");//zhongbin
			//	}
				in_uint16_le(ts, count);
				process_orders(ts, count);
				break;
			case 1:	/* update bitmap */
		//		if(Toggled && NOT_END){
		//			printf("	update bitmap\n");//zhongbin
		//		}
				in_uint8s(ts, 2);	/* part length */
				process_bitmap_updates(ts);
				break;
			case 2:	/* update palette */
				if(Toggled && NOT_END){
					printf("	update palette\n");//zhongbin
				}
				in_uint8s(ts, 2);	/* uint16 = 2 */
				process_palette(ts);
				break;
			case 3:	/* update synchronize */
//				if(Toggled && NOT_END){
//					printf("	update synchronize\n");//zhongbin
//				}
				break;
			case 5:	/* null pointer */
				if(Toggled && NOT_END){
					printf("	null pointer, once a time\n");//zhongbin
				}
				ui_set_null_cursor();
				break;
			case 6:	/* default pointer */
				if(Toggled && NOT_END){
					printf("	default pointer\n");//zhongbin
				}
				break;
			case 8:	/* pointer position */
				if(Toggled && NOT_END){
					printf("	pointer position\n");//zhongbin
				}
				in_uint16_le(ts, x);
				in_uint16_le(ts, y);
				if (s_check(ts)){
					ui_move_pointer(x, y);
					//printf("move pointer by rdp5\n");//zhongbin
				}
				break;
			case 9:	/* color pointer */
				if(Toggled && NOT_END){
					printf("	color pointer, once a time\n");//zhongbin
				}
				process_colour_pointer_pdu(ts);
				break;
			case 10:	/* cached pointer */
		//		if(Toggled && NOT_END){
		//			printf("	cached pointer, once a time\n");//zhongbin
		//		}
				process_cached_pointer_pdu(ts);
				break;
			case 11:/*process a new pointer pdu*/
				if(Toggled && NOT_END){
					printf("	new pointer, once a time\n");//zhongbin
				}
				process_new_pointer_pdu(ts);
				break;
			default:
				if(Toggled && NOT_END){
					printf("	unimplement rdp5 opcode\n");//zhongbin
				}
				unimpl("RDP5 opcode %d\n", type);
		}

		s->p = next;
	}
	ui_end_update();
	if(Toggled && NOT_END){
		//printf("rdp5_process was called at time %d\n", time((time_t *)NULL));//zhongbin
		//printf("#### order_count:%d	second_order_count:%d\n\n", order_count, second_order_count);//zhongbin
	}
}
