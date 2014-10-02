#include <SPI.h>					// Import SPI Lib
#include <SdFat.h>					// Import SD card Lib
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>			// Import MP3 Shield Lib

SdFat sd;							// SD Card Object
SFEMP3Shield MP3player;				// MP3 Shield Object

const int chipSelect = 9;

#define c_min 1 					// min numero de canciones en sd
#define c_max 10					//max numero de canciones en sd

uint8_t v_min= 70;
uint8_t v_max= 20;
int track_n= 0;
int track_l= 0;

void setup() {

	Serial.begin(115200);
	sd.begin(chipSelect,SPI_HALF_SPEED);
	MP3player.begin();
	MP3player.setVolume(v_min);
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
		track_n = (random(c_min,c_max+1));
    	while (track_n == track_l)
    	{ 
      		track_n = int(random(c_min, c_max + 0.99));  
    	}
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
		Serial.print("\nTrack ");
		Serial.print(track_n);
		track_l=track_n;
		char buffer[16];
		MP3player.trackTitle(buffer);
		Serial.print(" - ");
		Serial.println(buffer);
		Serial.println("\n¿¿¿¿AYUDA????: \n Escribe 'ayuda' para intervenir en la reproducción :)");


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
				MP3player.stopTrack();
			}
			if(repro=="-")
			{
				v_min=v_min+10;
				MP3player.setVolume(v_min);
			}
			if(repro=="+")
			{
					v_min=v_min-10;
					MP3player.setVolume(v_min);		

			}
			if(repro=="artista")
			{
				match=false;
				cont=1;
	 			MP3player.stopTrack();	
			}
			if(repro=="ayuda")
			{
				Serial.println("\n¿QUE DESEAS HACER?");
				Serial.println("\nSubir o bajar Volumen: Escriba '+' o '-'");
				Serial.println("Cambiar de artista: Escriba 'artista'");
				Serial.println("Pausar la cancion: Escriba 'pausa'");
				Serial.println("Cambiar la cancion: Escriba 'next'");
			}
		}

		if(!MP3player.isPlaying())
		{
			match=false;
		}
	}
	}
}



String intartista()
{
  Serial.println("\nQue artista desea escuchar?? ");
  Serial.println("Escoge entre: Calvin Harris, Shakira, Juanes");
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