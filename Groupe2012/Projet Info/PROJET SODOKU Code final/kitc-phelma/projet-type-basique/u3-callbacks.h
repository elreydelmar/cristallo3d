// u3-callbacks.h
// Sentinelle d'inclusion
#ifndef _u3_callbacks_h
#define _u3_callbacks_h

// Declarations externes
#include <FL/Fl_Widget.H>

// Declaration des sous-programmes
void TraiterCycleCB() ;
void ZoneDessinSourisCB( Fl_Widget* widget, void* data ) ;
void ZoneDessinClavierCB( Fl_Widget* widget, void* data ) ;
void BoutonQuitterCB( Fl_Widget* w, void* data ) ;
void CaseRebondCB( Fl_Widget* w, void* data ) ;
void BoutonAideCB( Fl_Widget* w, void* data ) ;
void SolutionCB ( Fl_Widget* w, void* data) ;
void BoutonKonamiCB (Fl_Widget* w, void* data) ;
void ChampNumCB (Fl_Widget* w, void* data) ;

#endif // _u3_callbacks_h
