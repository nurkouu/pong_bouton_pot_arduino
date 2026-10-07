#include <Arduino.h>

#include <Bounce2.h>
Bounce2::Button but0;

#include <MicroOscSlip.h>
MicroOscSlip<128> monOsc(&Serial); 

#include <Chrono.h>
Chrono chronoPotentio;


void setup()
{
    Serial.begin(115200);

    but0.attach(2, INPUT_PULLUP);
    but0.setPressedState(LOW);

    pinMode(3, OUTPUT);

}

void loop()
{
    // CODE POUR LE BOUTON ARCADE
    but0.update();

    if (but0.pressed()) { // Bouton vient d’être appuyé
        
        // Ancienne méthode d’envoi ASCII 
        // Serial.print("but0");
        // Serial.print(" ");
        // Serial.print(1);
        // Serial.println();
        
        monOsc.sendInt("/but0", 1); //Nouvelle méthode d’envoi OSC
    }

    if (but0.released()) { // Bouton vient d’être relâché
        
        // Ancienne méthode d’envoi ASCII 
        // Serial.print("but0");
        // Serial.print(" ");
        // Serial.print(0);
        //Serial.println();
       
        monOsc.sendInt("/but0", 0); //Nouvelle méthode d’envoi OSC
    }

    if (but0.isPressed()) { // Bouton maintenu
        digitalWrite( 3 , HIGH );
    } else {
        digitalWrite( 3 , LOW );
    }



    // CODE POUR LE POTENTIOMÈTRE
    if ( chronoPotentio.hasPassed(20)) { // SI LE CHRONO DÉPASSE 20 MILLISECONDES
    chronoPotentio.restart(); // REPARTIR LE CHRONO

    int valeur = analogRead(2); // LECTURE DE LA TENSION ENTRE 0 ET 1023

    monOsc.sendInt("/pot", valeur); // ENVOYER LA VALEUR
}


}