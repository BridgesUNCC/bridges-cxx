// WAVE file header format
struct WaveHeader {
	unsigned char *riff;				// RIFF string
	unsigned int overall_size	;		// overall size of file in bytes
	unsigned char *wave;				// WAVE string
	unsigned char *fmt_chunk_marker;	// fmt string with trailing null char
	unsigned int length_of_fmt;			// length of the format data
	unsigned int format_type;			// format type. 1-PCM, 3- IEEE float, 6 - 8bit A law, 7 - 8bit mu law
	unsigned int channels;				// no.of channels
	unsigned int sample_rate;			// sampling rate (blocks per second)
	unsigned int byterate;				// SampleRate * NumChannels * BitsPerSample/8
	unsigned int block_align;			// NumChannels * BitsPerSample/8
	unsigned int bits_per_sample;		// bits per sample, 8- 8bits, 16- 16 bits etc
	unsigned char *data_chunk_header;	// DATA string or FLLR string
	unsigned int data_size;				// NumSamples * NumChannels * 
										// BitsPerSample/8 - size of the 
										// next chunk that will be read


	WaveHeader() {
		riff = new unsigned char[4];
		wave = new unsigned char[4];
		fmt_chunk_marker = new unsigned char[4];
		data_chunk_header = new unsigned char[4];
	}

	~WaveHeader() {
		delete[] riff;
		delete[] wave;
		delete[] fmt_chunk_marker;
		delete[] data_chunk_header;
	}
};
