// u3-callbacks.h
// Sentinelle d'inclusion
#ifndef _u3_callbacks_h
#define _u3_callbacks_h

// Declarations externes
#include <FL/Fl_Widget.H>

// Declaration des sous-programmes des CallBacks
void TraiterCycleCB() ;
void ZoneDessinSourisCB( Fl_Widget* widget, void* data ) ;
void ZoneDessinClavierCB( Fl_Widget* widget, void* data ) ;
void BoutonQuitterCB( Fl_Widget* w, void* data ) ;
void BoutonChuckCB( Fl_Widget* w, void* data ) ;
void CaseRebondCB( Fl_Widget* w, void* data ) ;
void BoutonAideCB( Fl_Widget* w, void* data ) ;
void BoutonRecommencerCB( Fl_Widget* w, void* data ) ;
void BoutonSolutionCB ( Fl_Widget* w, void* data) ;
void BoutonKonamiCB (Fl_Widget* w, void* data) ;
void ChampNumCB (Fl_Widget* w, void* data) ;
void ChampSaisieNumCB( Fl_Widget* w, void* data );
void BoutonFacileCB ( Fl_Widget* w, void* data ) ;
void BoutonMoyenCB ( Fl_Widget* w, void* data ) ;
void BoutonExpertCB ( Fl_Widget* w, void* data ) ;
void BoutonChercherSolutionsCB ( Fl_Widget* w, void* data ) ;
void BoutonVadorCB ( Fl_Widget* w, void* data ) ;

#endif // _u3_callbacks_h
