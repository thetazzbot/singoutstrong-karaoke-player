/** @file ultrastarparser.h
 * Header file with the UltraStarParser class \n
 * Code shamelessly lifted from the Performous project: http://performous.org/
*/

#ifndef ULTRASTARPARSER_H
#define ULTRASTARPARSER_H

#include "../../song/song.h"
#include "../include/isongsettings.h"
#include <log.h>
#include <stdexcept>
#include <map>
#include <fstream>

/*!
 *  \addtogroup SoS
 *  @{
 */

//! Main SingOutStrong namespace
namespace SoS
{
	/*!
	 *  \addtogroup Core
	 *  @{
	 */

	//! Core functionalisties: loading files, audio processing, playback control, etc.
	namespace Core
	{
		/**
		 * @brief Parser for UltraStar text files
		 *
		 * Code shamelessly lifted from the Performous project: http://performous.org/
		 */
		class UltraStarParser
		{
			public:
				/// constructor
				UltraStarParser(ISongSettings* settings, Song* s);

				void Parse(Song* s);

				//std::string GetMusicFile(std::string type);
				//std::string GetPath();

			private:
				void finalize(Song* s);

				const ISongSettings* _settings;
				bool parsed;
				int lyricLine;

				std::stringstream m_ss;
				unsigned int m_linenum;
				bool getline(std::string& line) { ++m_linenum; return std::getline(m_ss, line);}
				bool m_relative;
				double m_gap;
				double m_bpm;

				bool txtCheck(std::vector<char> const& data);
				void txtParseHeader(Song* s);
				void txtParse(Song* s);
				bool txtParseField(Song* s, std::string const& line);
				bool txtParseNote(std::string line, Track *vocal);

				bool iniCheck(std::vector<char> const& data);
				void iniParseHeader();
				void iniParse();

				double m_prevtime;
				unsigned int m_prevts;
				unsigned int m_relativeShift;
				double m_maxScore;

				/**
				 * @brief Struct for storing time in the Beats per minute format, and info that helps convert it to seconds
				 *
				 */
				struct BPM {
						BPM(double _begin, double _ts, double bpm): begin(_begin), step(0.25 * 60.0 / bpm), ts(_ts) {}
						double begin; ///< @brief Time in seconds
						double step; ///< @brief Seconds per quarter note
						double ts;
				};
				typedef std::vector<BPM> bpms_t;
				bpms_t m_bpms;
				unsigned m_tsPerBeat;  ///< The ts increment per beat
				unsigned m_tsEnd;  ///< The ending ts of the song
				void addBPM(double ts, double bpm) {
					if (!(bpm >= 1.0 && bpm < 1e12)) throw std::runtime_error("Invalid BPM value");
					if (!m_bpms.empty() && m_bpms.back().ts >= ts) {
						if (m_bpms.back().ts < ts) throw std::runtime_error("Invalid BPM timestamp");
						m_bpms.pop_back(); // Some ITG songs contain repeated BPM definitions...
					}
					m_bpms.push_back(BPM(tsTime(ts), ts, bpm));
				}
				/// Convert a timestamp (beats) into time (miliseconds)
				double tsTime(double ts) const {
					if (m_bpms.empty()) {
						if (ts != 0) throw std::runtime_error("BPM data missing");
						return m_gap;
					}
					for (std::vector<BPM>::const_reverse_iterator it = m_bpms.rbegin(); it != m_bpms.rend(); ++it) {
						if (it->ts <= ts) return (it->begin + (ts - it->ts) * it->step);
					}
					throw std::logic_error("INTERNAL ERROR: BPM data invalid");
				}
				/// Stops stored in <ts, duration> format
//				Song::Stops m_stops;
				/// Convert a stop into <time, duration> (as stored in the song)
				std::pair<double, double> stopConvert(std::pair<double, double> s) {
					s.first = tsTime(s.first);
					return s;
				}
		};
	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group SoS*/

#endif
