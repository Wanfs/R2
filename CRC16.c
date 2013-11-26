/* Fast CRC-16 Created by AUS students */

   /* Assemble 16-bits tuples*/

	L = (unsigned char)pktInfo.length - 1; // Total pkt length without 0xFF
	if((L%2) != 0){
		temp_data_16[0] = tmp_packet[1];
		j++;
		for(i=1; i<(L/2 + L%2); i++){
			temp_data_16[i] = (tmp_packet[j]<<8) + tmp_packet[j+1];
			j += 2;
		}

	}else{
		for(i=0; i<(L/2 + L%2); i++){
			temp_data_16[i] = (tmp_packet[j]<<8) + tmp_packet[j+1];
			j += 2;
		}
	}

   // Calculate CRC-16 of the packet.
	for(i=0; i<((L/2) + L%2); i++){
		A = B ^ temp_data_16[i];

		// 1st iteration

		if((A&0x8000) == 0)
			C = A<<1;
		else
			C = (A<<1) ^ crc16;

		// 2nd Iteration

		if((C&0x8000) == 0)
			B = C << 1;
		else
			B = (C<<1) ^ crc16;

		B = B ^ C ^ A;

	}
	P = B;

   if(tmp_packet[1] == 252){ // AUS pkt
        tmp_packet[pktInfo.length] = (unsigned char)P; // lower byte of crc
        tmp_packet[pktInfo.length+1] = (unsigned char)(P >> 8);  // upper byte of crc

        pktInfo.length += 2;
   }