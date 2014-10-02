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

void loop()
{
	findArtist();
}

void findArtist() 
{
	String inp = intartista();
	int cont=0;
	uint8_t track_n;
	while(cont==0)
	{
	bool match = false;
	int counter = 0;
	
	while(!match)
	{
		randomSeed(millis());
		track_n = (uint8_t)random(1,11);
	    MP3player.playTrack(track_n);
		char buffer[16];
		MP3player.trackArtist(buffer);
		MP3player.stopTrack();
		if(String(buffer) == inp)
		{
			match = true;
		}
	}

	while(match)
	{
	
	MP3player.playTrack(track_n);
	Serial.print("Track ");
	Serial.print(track_n);
	char buffer[16];
	MP3player.trackTitle(buffer);
	Serial.print(" - ");
	Serial.println(buffer);

	while(MP3player.isPlaying())
	{
		String repro=readString();
		if(repro=="pausa")
		{
			MP3player.pauseMusic();
		}
		if(repro=="play")
		{
			MP3player.resumeMusic();
		}
		if(repro=="next")
		{
			match=false;
		}
		if(repro=="artista")
		{
			match=false;
			cont=1;
 			MP3player.stopTrack();
 			
		}
	}
	}
	}
}



String intartista()
{
  Serial.println("Que artista desea escuchar?? ");
  Serial.println("Escoge entre Calvin Harris, Shakira, Juanes");
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
  }
  return output;
}