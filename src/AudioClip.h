
#include "Bridges.h"
#include "AudioChannel.h"
#include "wave.h"
#include <math.h>
#include "rapidjson/stringbuffer.h"
#include "base64.h"
#include <string>
#include <fstream>

#include <iostream>
using namespace std;

namespace bridges {
	namespace datastructure {
		class AudioClip : public DataStructure {
			private:
				int sampleCount;
				int numChannels;
				int sampleRate;
				int sampleBits;
				vector<AudioChannel *> channels;

				union ShortByteUnion {
					signed short asShort;
					unsigned char asBytes[2];
				};

			public:
				AudioClip(int sampleCount, int numChannels, int sampleBits, int sampleRate) {
					if (sampleCount > 1000000000) {
						throw "sampleCount must be less than 1 million";
					}

					this->sampleCount = sampleCount;
					this->numChannels = numChannels;
					this->channels = vector<AudioChannel *>(numChannels);

					for (int i = 0; i < numChannels; i++) {
						this->channels[i] = new AudioChannel(sampleCount);

						for (int j = 0; j < sampleCount; j++) {
							this->channels[i]->setSample(j, 0);
						}
					}

					this->sampleRate = sampleRate;
					this->sampleBits = sampleBits;
				}

				virtual const string getDStype() const override {
					return "Audio";
				}

				// creates an audio clip from a file in WAVE format
				AudioClip(string wave_file) {
					parseWaveFile (wave_file);

				}

				virtual const string getDataStructureRepresentation() const override final {
					using bridges::JSONUtil::JSONencode;

					int len = numChannels * sampleCount * (sampleBits / 8);
					std::vector<BYTE> byteBuff;

					int checkSampleBits = sampleBits;

					for (int i = 0; i < sampleCount; i++) {
						for (int c = 0; c < numChannels; c++) {
							int num = getSample(c, i);
							//uint32_t s = ((num>>24)&0xff) | ((num<<8)&0xff0000) | ((num>>8)&0xff00) | ((num<<24)&0xff000000);
							if (this->sampleBits == 8) {
								byteBuff.push_back(num & 0x000000FF);
							}
							else if (this->sampleBits == 16) {
								ShortByteUnion sbu;
								sbu.asShort = (uint16_t)num;
								byteBuff.push_back(sbu.asBytes[0]);
								byteBuff.push_back(sbu.asBytes[1]);
							}
							else if (this->sampleBits == 32 || this->sampleBits == 24) {
								// Some browsers cannot play 32 bit audio files so use 16
								int minmax = (int)((pow(2, sampleBits) / 2) - 1);
								int minmax16 = (int)((pow(2, 16) / 2) - 1);

								num = (int)((num / (float)minmax) * minmax16) & 0xFFFF;

								ShortByteUnion sbu;
								sbu.asShort = (uint16_t)num;
								byteBuff.push_back(sbu.asBytes[0]);
								byteBuff.push_back(sbu.asBytes[1]);
								checkSampleBits = 16;
							}
						}
					}

					string b64str = "";

					int numBits = 3;
					int count = 0;
					for (int i = 0; i < byteBuff.size(); i += numBits) {
						b64str += base64::encode(&(byteBuff[i]), 3);
						count++;
					}

					string jsonString = QUOTE + "encoding" + QUOTE + COLON + QUOTE + "RAW" + QUOTE + COMMA +
						QUOTE + "numChannels" + QUOTE + COLON + JSONencode(this->numChannels) + COMMA +
						QUOTE + "sampleRate" + QUOTE + COLON + JSONencode(this->sampleRate) + COMMA +
						QUOTE + "bitsPerSample" + QUOTE + COLON + JSONencode(checkSampleBits) + COMMA +
						QUOTE + "numSamples" + QUOTE + COLON + JSONencode(this->sampleCount) + COMMA +
						QUOTE + "samples" + QUOTE + COLON + QUOTE + b64str + QUOTE + CLOSE_CURLY;

					return jsonString;
				}

				int getNumChannels() const {
					return this->numChannels;
				}

				int getSampleRate() const {
					return this->sampleRate;
				}

				int getSampleCount() const {
					return this->sampleCount;
				}

				int getSampleBits() const {
					return this->sampleBits;
				}

				int getSample(int channel, int index) const {
					return channels.at(channel)->getSample(index);
				}

				void setSample(int channel, int index, int value) {
				  if (value >= pow(2, getSampleBits()-1) ||
				      value <  -pow(2, getSampleBits()-1))
				      throw "Audio value Out of Bound";
				      
				  channels[channel]->setSample(index, value);
				}
		private:
			void parseWaveFile (string wave_file) {
 				// Read and parse an audio file in WAVE format

				// open file
				ifstream infile;
				infile.open (wave_file.c_str(), ios::binary|ios::in);
				if (infile.fail()) {
					cout << "Couldnt open " << wave_file << endl;
					return;
				}

				// read the header data of the input WAVE file
				WaveHeader wave_header = readWaveHeader(infile);

				long size_of_each_sample = (wave_header.channels * 
									wave_header.bits_per_sample)/8;

				// read the audio data 
				if (this->sampleCount > 1000000000) {
					throw "sampleCount must be less than 1 million";
				}

				// create storage for the audio data
				this->channels.resize(this->numChannels);
				for (int i = 0; i < numChannels; i++) {
					this->channels[i] = new AudioChannel(this->sampleCount);
				}

				// read sample data by chunks, if PCM
				if (wave_header.format_type == 1) { // Only PCM handled
					long i =0;
					char data_buffer[size_of_each_sample];
					int  size_is_correct = true;

					// make sure that the bytes-per-sample is completely divisible 
					// by num.of channels
					long bytes_in_each_channel = (size_of_each_sample / wave_header.channels);
					if ((bytes_in_each_channel*wave_header.channels) != size_of_each_sample) {
						cout << "Error: Incorrect chunk size.. " <<  bytes_in_each_channel
						<< ", " <<  wave_header.channels <<", " <<  size_of_each_sample << "\n";
						size_is_correct = false;
					}
			 
					if (size_is_correct) { 
						// the valid amplitude range for values based on the bits per sample
						long low_limit = 0l;
						long high_limit = 0l;

						switch (wave_header.bits_per_sample) {
							case 8:
								low_limit = -128;
								high_limit = 127;
								break;
							case 16:
								low_limit = -32768;
								high_limit = 32767;
								break;
							case 32:
								low_limit = -2147483648;
								high_limit = 2147483647;
								break;
						}					
						for (int sample = 0; sample < this->sampleCount; 
														sample++) {
							int amplitude;
							if (!infile.fail()) {
								for (int ch = 0; ch < wave_header.channels; 
															ch++ ) {
									// read signal amplitude
									infile.read(data_buffer, 2);
									// convert data from big endian to little
									// endian based on bytes in each channel sample
									switch (bytes_in_each_channel) {
										case 1:
											amplitude = data_buffer[0];
											break;
										case 2:
											amplitude = 
												(data_buffer[0] & 0x00ff)|
												(data_buffer[1] << 8);
											break;
										case 4:
											amplitude= 
												data_buffer[0]|
												(data_buffer[1]<<8) | 
												(data_buffer[2]<<16) | 
												(data_buffer[3]<<24);
											break;
									}
									this->channels[ch]->setSample(sample, amplitude);
									// check if value was in range
									if (amplitude < low_limit || 
											amplitude > high_limit)
										cout << "**value out of range!" << "\n";

								}
							}
							else {
								cout << "Error reading file\n.";
								break;
							}
						} 
					} 
				} 
				infile.close();
			}
			WaveHeader readWaveHeader(ifstream& infile) {

				// read file header
				WaveHeader  wave_header;
			 
				infile.read ((char *)wave_header.riff, 4);

				unsigned char *buffer = new  unsigned char[4];
				infile.read ((char*) buffer,  4);

				// convert little endian to big endian 4 byte int
				wave_header.overall_size  = buffer[0] | (buffer[1]<<8) | 
									(buffer[2]<<16) | (buffer[3]<<24);

				
				infile.read ((char*) wave_header.wave,  4);

				infile.read ((char*) wave_header.fmt_chunk_marker,  4);
				infile.read ((char *) buffer, 4);
				wave_header.length_of_fmt = buffer[0] | (buffer[1] << 8) |
										(buffer[2] << 16) | (buffer[3] << 24);

				char *buffer2 = new  char[2];
				infile.read (buffer2, 2);
				wave_header.format_type = buffer2[0] | (buffer2[1] << 8);

				string format_name = "";
				switch (wave_header.format_type) {
					case 1 : format_name = "PCM"; break;
					case 6 : format_name = "A-law"; break;
					case 7 : format_name = "Mu-law"; break;
				}

				infile.read (buffer2, 2);
				wave_header.channels = buffer2[0] | (buffer2[1] << 8);
				this->numChannels = wave_header.channels;

				infile.read ((char *) buffer, 4);
				wave_header.sample_rate = buffer[0] | (buffer[1] << 8)|
								(buffer[2] << 16) | (buffer[3] << 24);
				this->sampleRate = wave_header.sample_rate;

				infile.read ((char *) buffer, 4);
				wave_header.byterate = buffer[0] | (buffer[1] << 8)|
								(buffer[2] << 16) | (buffer[3] << 24);

				infile.read (buffer2, 2);
				wave_header.block_align = buffer2[0] | (buffer2[1] << 8);

				infile.read (buffer2, 2);
				wave_header.bits_per_sample = buffer2[0] | (buffer2[1] << 8);

				this->sampleBits = wave_header.bits_per_sample;

				infile.read ((char *)wave_header.data_chunk_header, 4);

				infile.read ((char *) buffer, 4);
				wave_header.data_size = buffer[0] | (buffer[1] << 8)|
								(buffer[2] << 16) | (buffer[3] << 24);

				// calculate no.of samples
				long num_samples = (8*wave_header.data_size)/
					(wave_header.channels*wave_header.bits_per_sample);
				this->sampleCount = num_samples;

				long size_of_each_sample = (wave_header.channels * 
								wave_header.bits_per_sample)/8;

				return wave_header;
			}
	public:
			void getRange() {
				int max = -32768, min = 32767;
				for (int i = 0; i < this->sampleCount; i++)
				for (int c = 0; c < this->numChannels; c++) {
					int val = this->getSample(c, i);
					if (val < min) min = val;
					if (val > max) max = val;
				}
			}
		};
	}
}
