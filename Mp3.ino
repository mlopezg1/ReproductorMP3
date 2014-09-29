#include <SPI.h>					// Import SPI Lib
#include <SdFat.h>					// Import SD card Lib
#include <SdFatUtil.h>				
#include <SFEMP3Shield.h>			// Import MP3 Shield Lib

#include <Wire.h>					// Import TWI lib

SdFat sd;							// SD Card Object		
SFEMP3Shield MP3player;				// MP3 Shield Object	

const int chipSelect = 9;

#define cv_min 1 					// min numero de canciones de carlos vives
#define cv_max 3					//max numero de canciones de carlos vives

#define s_min 4						// min numero de canciones de shakira
#define s_max 7 					//max numero de canciones de shakira

#define j_min 8  					//min numero de canciones de juanes
#define j_max 10 					//max numero de canciones de juanes

int cv_number=0;
int cv_last=0;

int s_number=0;
int s_last=0;

int j_number=0;
int j_last=0;

int32_t t_pos;

String intartista()
{
	Serial.println("Que artista desea escuchar?? ");
	Serial.println("Escoge entre Calvin, Shakira, Juanes");
	String tipo = "";
	while(tipo == "")
	{
		tipo = readString();
	}
	return tipo;
}


String readString()
{
	String output="";
	while(output=="")
	{
	  	output.concat(char(Serial.read()));
	  	delay(10);
	}
	return output;
}

String intervenir()
{
 String int_user= readString();
   if (int_user=="pausa")
 {
  t_pos = MP3player.currentPosition();	//guarda la posicion actual
  MP3player.stopTrack();
 }
 if (int_user=="play")
 {
  MP3player.skipTo(t_pos);
 }

  /*if (int_user=="next")
 {
  // MP3player.skip();
 }
  if (int_user=="artista")
 {
   //reproductor();
 }
   if (int_user!="artista" && int_user!="play" && int_user!="pausa" && int_user!="next")
 {
  //continue
 }*/
}

void setup ()
{
  Serial.begin(115200);
  MP3player.begin();
  
}

void loop ()
{
  reproductor();
  delay(200);
}

int reproductor()
{
  bool playing=false;
  String art_elegido=intartista();
    
  if(art_elegido== "Calvin")
  {
    cv_number=random(cv_min,cv_max+1);
    while(cv_number == cv_last)
        {								// para tomar una selección difente a la ultima
	cv_number = int(random(cv_min,cv_max+0.99));
	}
    cv_last = cv_number;
    										// Store the gretings number into the last gretings number
    MP3player.playTrack(cv_number);
     playing=true;
  }
  
    if(art_elegido== "Shakira")
  {
    cv_number=random(s_min,s_max+1);
    while(s_number == s_last)
        {								// para tomar una selección difente a la ultima
	  s_number = int(random(s_min,s_max+0.99));
	}
    s_last = s_number;
    										// Store the gretings number into the last gretings number
    MP3player.playTrack(s_number);
    playing=true;
  }
  
    if(art_elegido== "Juanes")
  {
    cv_number=random(j_min,j_max+1);
    while(j_number == j_last)
        {								// para tomar una selección difente a la ultima
	  j_number = int(random(j_min,j_max+0.99));
	}
    j_last = j_number;
    										// Store the gretings number into the last gretings number
    MP3player.playTrack(j_number);
    // String titulo=MP3player.trackTitle(j_number);    //como ponerle el titulo??
    //Serial.print(titulo);
    playing=true;
 }
 
   if(art_elegido!="Calvin"&& art_elegido!="Shakira" && art_elegido!="Juanes")
  {
    Serial.println("No tienes canciones de este artista");
    art_elegido=intartista();
   }
 
    while(playing==true)
    {
      intervenir();  
    }  
}

