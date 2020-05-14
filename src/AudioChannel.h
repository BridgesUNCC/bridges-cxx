
#include <vector>

class AudioChannel {
	private:
		std::vector<int> data;
		int sampleCount;

	public:
		AudioChannel(int sampleCount) {
			data = std::vector<int>(sampleCount);
			this->sampleCount = sampleCount;
		}

		int getChannelSize() {
			return sampleCount;
		}

		int getSample(int index) {
			return data[index];
		}

		void setSample(int index, int sample) {
			data[index] = sample;
		}
};