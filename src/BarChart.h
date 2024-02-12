#ifndef BAR_CHART_H
#define BAR_CHART_H

#include <unordered_map>
#include <vector>
#include <string>
#include <DataStructure.h>
#include <JSONutil.h>

namespace bridges {
	namespace datastructure {

		class BarChart : public DataStructure {
			private:
				std::string xLabel;
				std::string yLabel;
				std::string plotTitle;
				std::string plotSubTitle;
				unordered_map<string, vector<double>> seriesData;
				std::vector<std::string> seriesBins;

			public:
				BarChart() {
					plotTitle = "";
					plotSubTitle = "";
					yLabel = "";
					xLabel = "";
				}

				/**
				 * @brief Get the data type
				 * @return name of the data type (used internally)
				 */
				virtual const string getDStype() const override {
					return "BarChart";
				}

				/**
				 * @brief Title of the plot
				 *
				 * @param t the title to be shown
				 **/
				void setTitle(std::string t) {
					plotTitle = t;
				}

				/**
				 * @brief Title of the plot
				 *
				 * @return the title to be shown
				 **/
				std::string getTitle() const {
					return plotTitle;
				}

				/**
				 * @brief Subtitle of the plot
				 *
				 * @param s the subtitle to be shown
				 **/
				void setSubTitle(std::string s) {
					plotSubTitle = s;
				}

				/**
				 * @brief Subtitle of the plot
				 *
				 * @return the subtitle to be shown
				 **/
				std::string getSubTitle() const {
					return plotSubTitle;
				}

				/**
				 * @brief Change the label for the Y-axis
				 *
				 * @param yaxisName label to show for the Y-axis
				 **/
				void setYLabel(std::string yaxisName) {
					yLabel = yaxisName;
				}

				/**
				 * @brief Returns the label for the Y-axis
				 *
				 * @return label shown for the Y-axis
				 **/
				std::string getYLabel() const {
					return yLabel;
				}

				/**
				 * @brief Change the label for the X-axis
				 *
				 * @param xaxisName label to use for the X-axis
				 **/
				void setXLabel(std::string xaxisName) {
					xLabel = xaxisName;
				}

				/**
				 * @brief Returns the label for the Y-axis
				 *
				 * @return label shown for the Y-axis
				 **/
				std::string getXLabel() const {
					return xLabel;
				}

				void setSeriesBins(std::vector<std::string> bins) {
					seriesBins = bins;
				}

				/**
				 * @brief Add a series (or update it)
				 *
				 * @param seriesName indicates the series to add (or change)
				 * @param xdata the X data in the series
				 * @param ydata the Y data in the series
				 **/
				void addDataSeries(std::string seriesName, std::vector<double> data) {
					seriesData[seriesName] = data;
				}

				virtual const std::string getDataStructureRepresentation() const override {
					using bridges::JSONUtil::JSONencode;
					std::string bins = "";
					bins += JSONencode("xAxis") + COLON + OPEN_CURLY + JSONencode("categories") + COLON + OPEN_BOX;
					for (auto& entry : seriesBins) {
						bins += JSONencode(entry) + COMMA;
					}
					bins = bins.erase(bins.length() - 1);
					bins += CLOSE_BOX + CLOSE_CURLY;

					std::string series = "";
					series += JSONencode("series") + COLON + OPEN_BOX;
					for (auto& entry : seriesData) {
						series += OPEN_CURLY;
						std::string key = entry.first;
						std::vector<double> value = entry.second;

						series += JSONencode("name") + COLON + JSONencode(key) + COMMA + JSONencode("data") + COLON + OPEN_BOX;
						for (int i = 0; i < value.size(); i++) {
							series += JSONencode(value[i]) + COMMA;
						}
						series = series.erase(series.length() - 1);
						series += CLOSE_BOX + CLOSE_CURLY + COMMA;
					}
					series = series.erase(series.length() - 1);
					series += CLOSE_BOX;

					std::string json_str = JSONencode("plot_title") + COLON +  JSONencode(getTitle()) + COMMA +
						JSONencode("subtitle") + COLON + JSONencode(getSubTitle())  + COMMA +
						JSONencode("xLabel") + COLON + JSONencode(getXLabel()) +  COMMA +
						JSONencode("yLabel") + COLON + JSONencode(getYLabel()) + COMMA +
//						JSONencode("tooltipSuffix") + COLON + JSONencode(getTooltipSuffix()) + COMMA +
//						JSONencode("alignment") + COLON + JSONencode(getBarAlignment()) + COMMA +
						JSONencode("xaxis_data") + COLON + OPEN_CURLY + bins + CLOSE_CURLY + COMMA +
						JSONencode("yaxis_data") + COLON + OPEN_CURLY + series + CLOSE_CURLY + CLOSE_CURLY;

cout << json_str;
					return json_str;
				}
		};
	}

}
#endif
