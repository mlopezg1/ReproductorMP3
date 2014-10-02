#include <SPI.h>					// Import SPI Lib
#include <SdFat.h>					// Import SD card Lib
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>			// Import MP3 Shield Lib

SdFat sd;							// SD Card Object
SFEMP3Shield MP3player;				// MP3 Shield Object

const int chipSelect = 9;

void setup() {

	Serial.begin(115200);
	sd.begin(chipSelect,SPI_HALF_SPEED);
	MP3player.begin();

}

void loop() {
	String inp = intartista();
	bool match = false;
	int counter = 0;
	uint8_t track_n;
	while(!match || counter > 20){
		track_n = (uint8_t)random(1,11);
	    MP3player.playTrack(track_n);
		char buffer[16];
		MP3player.trackArtist(buffer);
		MP3player.stopTrack();
		if(String(buffer) == inp){
			match = true;
		}
	}
	Serial.println(track_n);
	MP3player.playTrack(track_n);
	while(MP3player.isPlaying()){
		;
	}
}

String intartista()
{
  Serial.println("Que artista desea escuchar?? ");
  Serial.println("Escoge entre calvin, shakira, juanes");
  String tipo = "";
  while (tipo == "")
  {
      tipo = readString();
  }
  return tipo;
}


String readString()
{
  String output = "";
  while (Serial.available())
  {
    output.concat(char(Serial.read()));
    delay(10);
   Serial.println("entre1"); 
  }
  return output;
}