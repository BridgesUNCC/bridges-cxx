
#include "Bridges.h"
#include "AudioChannel.h"
#include <math.h>
#include "rapidjson/stringbuffer.h"
#include "base64.h"

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
                if (sampleCount > 1000000000)
                {
                    throw "sampleCount must be less than 1 million";
                }
                
                this->sampleCount = sampleCount;
                this->numChannels = numChannels;
                this->channels = vector<AudioChannel *>(numChannels);
                
                for (int i = 0; i < numChannels; i++)
                {
                    this->channels[i] = new AudioChannel(sampleCount);
                    
                    for (int j = 0; j < sampleCount; j++)
                    {
                        this->channels[i]->setSample(j, 0);
                    }
                }
                
                this->sampleRate = sampleRate;
                this->sampleBits = sampleBits;
            }

            virtual const string getDStype() const override {
                return "Audio";
            }

            virtual const string getDataStructureRepresentation() const override final {
                using bridges::JSONUtil::JSONencode;

                int len = numChannels * sampleCount * (sampleBits / 8);
                std::vector<BYTE> byteBuff;
                
		        int checkSampleBits = sampleBits;

                for (int i = 0; i < sampleCount; i++)
                    {
                        for (int c = 0; c < numChannels; c++) {
                            int num = getSample(c, i);
                            //uint32_t s = ((num>>24)&0xff) | ((num<<8)&0xff0000) | ((num>>8)&0xff00) | ((num<<24)&0xff000000);
                            if (this->sampleBits == 8) {
                                byteBuff.push_back(num & 0xFF);
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

                string jsonString = OPEN_CURLY + QUOTE + "encoding" + QUOTE + COLON + QUOTE + "RAW" + QUOTE + COMMA + 
                    QUOTE + "numChannels" + QUOTE + COLON + JSONencode(this->numChannels) + COMMA + 
                    QUOTE + "sampleRate" + QUOTE + COLON + JSONencode(this->sampleRate) + COMMA + 
                    QUOTE + "bitsPerSample" + QUOTE + COLON + JSONencode(checkSampleBits) + COMMA + 
                    QUOTE + "numSamples" + QUOTE + COLON + JSONencode(this->sampleCount) + COMMA + 
                    QUOTE + "samples" + QUOTE + COLON + QUOTE + b64str + QUOTE + CLOSE_CURLY;

                return jsonString;
            }

            int getNumChannels() {
                return this->numChannels;
            }

            int getSampleRate() {
                return this->sampleRate;
            }

            int getSampleCount() {
                return this->sampleCount;
            }

            int getSampleBits() {
                return this->sampleBits;
            }

            int getSample(int channel, int index) const {
                return channels.at(channel)->getSample(index);
            }
                
            void setSample(int channel, int index, int value) {
                channels[channel]->setSample(index, value);
            }
        };
    }
}