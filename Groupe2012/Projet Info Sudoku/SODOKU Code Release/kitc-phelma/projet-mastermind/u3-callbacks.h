// u3-callbacks.h
// Sentinelle d'inclusion
#ifndef _u3_callbacks_h
#define _u3_callbacks_h

// Declarations externes
#include <FL/Fl_Widget.H>

// Declaration des sous-programmes generaux
void TraiterCycleCB() ;
void ZoneDessinSourisCB( Fl_Widget* widget, void* data ) ;
void ZoneDessinClavierCB( Fl_Widget* widget, void* data ) ;
void BoutonQuitterCB( Fl_Widget* w, void* data ) ;
// Declaration des sous-programmes mastermind, callback des boutons
void BoutonRejouerCB(Fl_Widget* w, void* data);
void BoutonValiderCB( Fl_Widget* w, void* data ) ;
void BoutonSolutionCB( Fl_Widget* w, void* data ) ;

#endif // _u3_callbacks_h
