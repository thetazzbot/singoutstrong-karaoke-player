/** @file audioanalyzer.h
 * Header file that switches the between the AudioAnalyzer classes to be used depending on the values in the implementations.h file
*/

#ifndef AUDIOANALYZER_H
#define AUDIOANALYZER_H

#include "../../implementations.h"

#ifdef SOS_AUBIO_ANALYZER
#include "AubioAnalyzer/AubioAnalyzer.h"
typedef SoS::Core::AubioAnalyzer AudioAnalyzer;
#endif

#endif // AUDIOANALYZER_H
