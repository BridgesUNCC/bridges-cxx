
#include <vector>

class AudioChannel {
	private:
		std::vector<int> data;

	public:
		AudioChannel(int sampleCount) {
			data = std::vector<int>(sampleCount);
		}

		int getChannelSize() {
			return sampleCount;
		}

		int getSample(int index) {
			return data[index];
		}

		void setSample(int index, int val) {
			data[index] = val;
		}
};
