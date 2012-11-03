#include "ultrastarparser.h"

namespace SoS
{
	namespace Core
	{
		void assign(int& var, std::string const& str)
		{
			try
			{
				var = atoi(str.c_str());
			}
			catch (...)
			{
				//throw std::runtime_error(L"\"" + str + L"\" is not valid integer value");
			}
		}

		void assign(double& var, std::string str)
		{
			std::replace(str.begin(), str.end(), L',', L'.'); // Fix decimal separators
			try
			{
				var = atof(str.c_str());
			} catch (...)
			{
				//throw std::runtime_error("\"" + str + "\" is not valid floating point value");
			}
		}

		void assign(bool& var, std::string const& str)
		{
			if (str == "YES" || str == "yes" || str == "1") var = true;
			else if (str == "NO" || str == "no" || str == "0") var = false;
			else throw std::runtime_error("Invalid boolean value: " + str);
		}

		void eraseLast(std::string& s, char ch)
		{
			if (!s.empty() && *s.rbegin() == ch) s.erase(s.size() - 1);
		}

		bool fileExists(std::string filename)
		{
			FILE* fp = fopen(filename.c_str(), "r");
			if(fp)
			{
				fclose(fp);
				return true;
			}

			return false;
		}

		std::string UltraStarParser::GetMusicFile(std::string type)
		{
			return parsed ? music[type] : "";
		}

		std::string UltraStarParser::GetPath()
		{
			return parsed ? path : "";
		}

		UltraStarParser::UltraStarParser(ISongSettings *settings, Song *s, std::string filename, std::map<std::string,std::string> &properties):
			m_linenum(),
			m_relative(),
			m_gap(),
			m_bpm(),
			m_prevtime(),
			m_prevts(),
			m_relativeShift(),
			m_maxScore(),
			m_tsPerBeat(),
			m_tsEnd(),
			_settings(settings),
			parsed(false),
			lyricLine(0),
			music(properties)
		{
			Parse(s, filename);
		}

		void UltraStarParser::Parse(Song* s, std::string filename)
		{
			enum { NONE, TXT, INI, SM } type = NONE;
			// Read the file, determine the type and do some initial validation checks

			music.clear();
			std::string ext = "";
			std::string filenameNoext = "";
			size_t sep = filename.find_last_of("\\/");
			if (sep != std::string::npos)
			{
				path = filename.substr(0, sep + 1);
				music["filename"] = filename.substr(sep+1, filename.size() - sep - 1);
			}

			sep = filename.find_last_of(".");
			if (sep != std::string::npos)
			{
				ext = filename.substr(sep + 1, filename.size() - sep - 1);
				filenameNoext = filename.substr(0, sep+1);
			}

			// This works a bit different then the original Performous parser. We assume we're given an audio
			// stream file, and look for a .txt file with the same name in the same directory
			music["background"] = filename;

			filename = filenameNoext+"txt";
			std::ifstream f((filename).c_str(), std::ios::binary);

			if (!f.is_open())
				return; //throw SongParserException("Could not open song file", 0);

			f.seekg(0, std::ios::end);
			size_t size = f.tellg();
			if (size < 10 || size > 100000)
				return; // throw SongParserException("Does not look like a song file (wrong size)", 1, true);

			f.seekg(0);
			std::vector<char> data(size);

			if (!f.read(&data[0], size))
				return; //throw SongParserException("Unexpected I/O error", 0);

			if (txtCheck(data)) type = TXT;
			//else if (iniCheck(data)) type = INI;
			else
				return; //throw SongParserException("Does not look like a song file (wrong header)", 1, true);

			m_ss.write(&data[0], size);

			try
			{
				if (type == TXT) txtParse(s);
				//else if (type == INI) iniParse();
			}
			catch (std::runtime_error& e)
			{
				return; //throw SongParserException(e.what(), m_linenum);
			}
			finalize(s); // Do some adjusting to the notes

			return;

			/*
			// Remove bogus entries
			if (!boost::filesystem::exists(m_song.path + m_song.cover)) m_song.cover = "";
			if (!boost::filesystem::exists(m_song.path + m_song.background)) m_song.background = "";
			if (!boost::filesystem::exists(m_song.path + m_song.video)) m_song.video = "";

			// In case no images/videos were specified, try to guess them
			if (m_song.cover.empty() || m_song.background.empty() || m_song.video.empty()) {
				boost::regex coverfile("((cover|album|label|\\[co\\])\\.(png|jpeg|jpg|svg))$", boost::regex_constants::icase);
				boost::regex backgroundfile("((background|bg||\\[bg\\])\\.(png|jpeg|jpg|svg))$", boost::regex_constants::icase);
				boost::regex videofile("(.*\\.(avi|mpg|mpeg|flv|mov|mp4))$", boost::regex_constants::icase);
				boost::cmatch match;

				for (boost::filesystem::directory_iterator dirIt(s.path), dirEnd; dirIt != dirEnd; ++dirIt) {
					boost::filesystem::path p = dirIt->path();
					std::string name = p.leaf(); // File basename
					if (m_song.cover.empty() && regex_match(name.c_str(), match, coverfile)) {
						m_song.cover = name;
					} else if (m_song.background.empty() && regex_match(name.c_str(), match, backgroundfile)) {
						m_song.background = name;
					} else if (m_song.video.empty() && regex_match(name.c_str(), match, videofile)) {
						m_song.video = name;
					}
				}
			}
			*/
		}


		void UltraStarParser::finalize(Song* s)
		{
			for(std::vector<Track*>::const_iterator it = s->tracks.begin() ; it != s->tracks.end() ; ++it)
			{
				// Adjust negative notes
				Track* vocal = *it;
				if (vocal->bottomNote <= 0)
				{
					unsigned int shift = (1 - vocal->bottomNote / 12) * 12;
					vocal->bottomNote += shift;
					vocal->topNote += shift;

					for (std::vector<Note*>::iterator n_it = vocal->notes.begin(); n_it != vocal->notes.end(); ++n_it)
					{
						(*n_it)->notePitch += shift;
					}
				}
			}
			if (m_tsPerBeat)
			{
				// Add song beat markers
				//for (unsigned ts = 0; ts < m_tsEnd; ts += m_tsPerBeat) s.beats.push_back(tsTime(ts));
			}
		}

		/// 'Magick' to check if this file looks like correct format
		bool UltraStarParser::txtCheck(std::vector<char> const& data)
		{
			return data[0] == '#' && data[1] >= 'A' && data[1] <= 'Z';
		}

		/// Parse header data for Songs screen
		void UltraStarParser::txtParseHeader(Song* s)
		{
			std::string line;

			while (getline(line) && txtParseField(s, line)) {}

			//|| s.artist.empty()
			if (s->name.empty()) throw std::runtime_error("Required header fields missing");
			if (m_bpm != 0.0) addBPM(0, m_bpm);
		}

		/// Parse notes
		void UltraStarParser::txtParse(Song* s)
		{
			std::string line;
			Track* vocal = new Track();

			while (getline(line) && txtParseField(s, line)) {} // Parse the header again

			if (m_bpm != 0.0)
				addBPM(0, m_bpm);

			while (txtParseNote(line, vocal) && getline(line)) {} // Parse notes

			// Workaround for the terminating : 1 0 0 line, written by some converters
			if (!vocal->notes.empty() && vocal->notes.back()->type != Note::SLEEP
					&& vocal->notes.back()->startTime == vocal->notes.back()->stopTime)
			{
				delete vocal->notes.back();
				vocal->notes.pop_back();
			}

			s->tracks.push_back(vocal);
		}

		std::string trim(std::string str)
		{
			str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
			str.erase(str.find_last_not_of(' ')+1);         //surfixing spaces
			return str;
		}

		bool UltraStarParser::txtParseField(Song* s, std::string const& line)
		{
			if (line.empty())
				return true;

			if (line[0] != '#')
				return false;

			std::string::size_type pos = line.find(':');

			if (pos == std::string::npos)
				throw std::runtime_error("Invalid txt format, should be #key:value");

			std::string key = trim(line.substr(1, pos - 1));
			std::string value = trim(line.substr(pos + 1));

			if (value.empty())
				return true;

			if (key == "TITLE") music["title"] = value.substr(value.find_first_not_of(" :"));
			else if (key == "ARTIST") music["artist"] =  value.substr(value.find_first_not_of(" "));
			//else if (key == "EDITION") m_song.edition = value.substr(value.find_first_not_of(" "));
			//else if (key == "GENRE") m_song.genre = value.substr(value.find_first_not_of(" "));
			//else if (key == "CREATOR") m_song.creator = value.substr(value.find_first_not_of(" "));
			//else if (key == "COVER") m_song.cover = value;
			//else if (key == "MP3") music["background"] = path + value;
			else if (key == "VOCALS") music["vocals"] = path + value;
			//else if (key == "VIDEO") m_song.video = value;
			//else if (key == "BACKGROUND") m_song.background = value;
			//else if (key == "START") assign(m_song.start, value);
			//else if (key == "VIDEOGAP") assign(m_song.videoGap, value);
			//else if (key == "PREVIEWSTART") assign(m_song.preview_start, value);
			//else if (key == "RELATIVE") assign(m_relative, value);
			else if (key == "GAP") { assign(m_gap, value); m_gap *= 1e-3; }
			else if (key == "BPM") assign(m_bpm, value);
			//else if (key == "LANGUAGE") m_song.language= value.substr(value.find_first_not_of(" "));
			return true;
		}

		bool UltraStarParser::txtParseNote(std::string line, Track *vocal)
		{
			if (line.empty() || line == "\r") return true;
			if (line[0] == '#') throw std::runtime_error("Key found in the middle of notes");
			if (line[line.size() - 1] == '\r') line.erase(line.size() - 1);
			if (line[0] == 'E') return false;
			std::istringstream iss(line);
			if (line[0] == 'B') {
				unsigned int ts;
				double bpm;
				iss.ignore();
				if (!(iss >> ts >> bpm)) throw std::runtime_error("Invalid BPM line format");
				addBPM(ts, bpm);
				return true;
			}
			if (line[0] == 'P') return true; //We ignore player information for now (multiplayer hack)
			Note* n = new Note();
			n->type = Note::Type(iss.get());
			unsigned int ts = m_prevts;
			switch (n->type)
			{
			case Note::NORMAL:
			case Note::FREESTYLE:
			case Note::GOLDEN:
			{
				unsigned int length = 0;
				int note = 0;
				std::string lyric;

				if (!(iss >> ts >> length >> note))
					throw std::runtime_error("Invalid note line format");
				else n->notePitch = note;
				//n->notePrev = n->note; // No slide notes in TXT yet.
				if (m_relative) ts += m_relativeShift;
				if (iss.get() == ' ')
				{
					std::getline(iss, lyric);
					TextData* textData = new TextData();
					textData->type = TextData::LYRIC_TEXT;
					textData->text = lyric;
					textData->time = tsTime(ts) * 1000;
					textData->paragraphNo = 0;
					textData->lineNo = lyricLine;

					vocal->textData[TextData::LYRIC_TEXT].push_back(textData);
				}
				n->stopTime = tsTime(ts + length) * 1000;
			}
				break;
			case Note::SLEEP:
			{
				unsigned int end;
				if (!(iss >> ts >> end)) end = ts;
				if (m_relative) {
					ts += m_relativeShift;
					end += m_relativeShift;
					m_relativeShift = end;
				}
				n->stopTime = tsTime(end) * 1000;
				lyricLine++;
			}
				break;
			default: throw std::runtime_error("Unknown note type");
			}

			n->startTime = tsTime(ts) * 1000;

			//			Notes& notes = vocal->notes;
			if (m_relative && vocal->notes.empty()) m_relativeShift = ts;
			m_prevts = ts;
			if (n->startTime < 0) //m_prevtime)
			{
				throw std::runtime_error("The note has negative timestamp");
				/*
				// Oh no, overlapping notes (b0rked file)
				// Can't do this because too many songs are b0rked: throw std::runtime_error("Note overlaps with previous note");
				if (notes.size() >= 1) {
					Note& p = notes.back();
					// Workaround for songs that use semi-random timestamps for sleep
					if (p.type == Note::SLEEP) {
						p.end = p.begin;
						Notes::reverse_iterator it = notes.rbegin();
						Note& p2 = *++it;
						if (p2.end < n->begin) p.begin = p.end = n->begin;
					}
					// Can we just make the previous note shorter?
					if (p.begin <= n->begin) p.end = n->begin;
					else { // Nothing to do, warn and skip
						std::ostringstream oss;
						oss << "Skipping overlapping note in " << m_song.path << m_song.filename << std::endl;
						std::clog << "songparser/warning: " << oss.str(); // More likely to be atomic when written as one string
						return true;
					}
				} else */
			}

			double prevtime = m_prevtime;
			m_prevtime = n->stopTime;

			if (n->type == Note::SLEEP)
			{
				delete n;
				return true;
			}

			if (n->type != Note::SLEEP && n->stopTime > n->startTime)
			{
				vocal->bottomNote = std::min(vocal->bottomNote, n->notePitch);
				vocal->topNote = std::max(vocal->topNote, n->notePitch);
			}
			vocal->notes.push_back(n);
			return true;
		}

	}
}
