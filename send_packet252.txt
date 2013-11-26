#define AUS_pkt_Size     37
xmem void send_packet_252();

/* AUS Students Project */

xmem void send_packet_252(){

   	auto uint8 AUS_pkt[AUS_pkt_Size];
   	auto int16 temp_int,heading;
   	auto uint16 temp_uint;

      AUS_pkt[0] = 0xff;
      AUS_pkt[1] = 252; // pkt type

      //Add GPS Lat
      memcpy(&AUS_pkt[2], &m_floats[MF_GPS_LAT], 4);
      //Add GPS Lon
      memcpy(&AUS_pkt[6], &m_floats[MF_GPS_LON], 4);
      //Add Roll
   	temp_int=(int16)((m_floats[MF_PHI])*1000);
		memcpy(&AUS_pkt[10],  &temp_int, sizeof(int16));
      //Add Pitch
		temp_int=(int16)((m_floats[MF_THETA])*1000);
		memcpy(&AUS_pkt[12],  &temp_int, sizeof(int16));
      //Heading
      temp_int=(int16)(m_floats[MF_TRUE_PSI]*1000);
		if(temp_int<0)
		temp_int+=6283; // To make sure it is always between 2 and 2*pi.

		memcpy(&AUS_pkt[14],  &temp_int, sizeof(int16));

      //Speed
      temp_uint=(uint16)((sensors[DIFPRES].calibrated+10)*20);
		memcpy(&AUS_pkt[16],  &temp_uint, 2);
      //Time
      AUS_pkt[18]=(unsigned char)g_UAV_state_UTC_time.tStamp.tm_year;    //utc year
		AUS_pkt[19]=(unsigned char)g_UAV_state_UTC_time.tStamp.tm_mon;    //utc month
		AUS_pkt[20]=(unsigned char)g_UAV_state_UTC_time.tStamp.tm_mday;    //utc day
		AUS_pkt[21]=(unsigned char)g_UAV_state_UTC_time.tStamp.tm_hour;     //utc hour
		AUS_pkt[22]=(unsigned char)g_UAV_state_UTC_time.tStamp.tm_min;    //utc min

		temp_uint=(uint16)g_UAV_state_UTC_time.tStamp.tm_sec*1000+g_UAV_state_UTC_time.msec;

      memcpy(&AUS_pkt[23],  &temp_uint, 2);
      //IMU Reading
      temp_int=(int16)((m_floats[MF_AX])*1000); 	// Accel. Ax
		memcpy(&AUS_pkt[25],  &temp_int, sizeof(int16));
		temp_int=(int16)((m_floats[MF_AY])*1000);		// Accel. Ay
		memcpy(&AUS_pkt[27],  &temp_int, sizeof(int16));
		temp_int=(int16)((m_floats[MF_AZ])*1000);			// Accel. Az
		memcpy(&AUS_pkt[29],  &temp_int, sizeof(int16));
		temp_int=(int16)((m_floats[MF_GYRO_P])*1000); // Gyro Rx
		memcpy(&AUS_pkt[31],  &temp_int, sizeof(int16));
		temp_int=(int16)((m_floats[MF_GYRO_Q])*1000); // Gyro Ry
		memcpy(&AUS_pkt[33],  &temp_int, sizeof(int16));
		temp_int=(int16)((m_floats[MF_GYRO_R])*1000); // Gyro Rz
		memcpy(&AUS_pkt[35],  &temp_int, sizeof(int16));


      send_response_packet(AUS_pkt, AUS_pkt_Size); // Send packet!

}