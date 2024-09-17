#ifndef BAR_CHART_H
#define BAR_CHART_H

#include <unordered_map>
#include <vector>
#include <string>
#include <DataStructure.h>
#include <JSONutil.h>

/**
 * @brief Support for drawing Bar charts 
 *
 * Bar charts (https://en.wikipedia.org/wiki/Bar_chart) are used to
 * represent categorical data as a series of rectangular bars with heights
 * proportional to the values they represent
 *  
 * A series is represented by two arrays xdata and ydata. The x axis
 * data is a series of equal sized bins, while the y axis data represents 
 * the value of that bin (or count).  Bins are added using setSeriesBins() and
 * their values are added using addDataSeries(). Labels are associated with 
 * the datasets
 *      
 * The Bar charts  can have a title, subtitle, and a tooltip indicating the
 * the bin values. The charts can be horizontal or vertically aligned
 *  
 * @sa See tutorial on using BarChart at:
 *      https://bridgesuncc.github.io/tutorials/BarChart.html
 *
 * @author Matthew Mcquaigue, Kalpathi Subramanian
 *
 * @date 09/15/24 (updated)
 *
 **/


namespace bridges {
	namespace datastructure {

		class BarChart : public DataStructure {
			private:
				std::string xLabel;
				std::string yLabel;
				std::string plotTitle;
				std::string plotSubTitle;
				std::string tooltipSuffix;
				std::string orientation;

				unordered_map<string, vector<double>> seriesData;
				std::vector<std::string> seriesBins;

			public:
				BarChart() {
					plotTitle = "";
					plotSubTitle = "";
					yLabel = "";
					xLabel = "";
					tooltipSuffix = "";
					orientation = "horizontal";
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
				void setSeriesLabel(std::string yaxisName) {
					yLabel = yaxisName;
				}

				/**
				 * @brief Returns the label for the Y-axis
				 *
				 * @return label shown for the Y-axis
				 **/
				std::string getSeriesLabel() const {
					return yLabel;
				}

				/**
				 * @brief Change the label for the X-axis
				 *
				 * @param xaxisName label to use for the X-axis
				 **/
				void setBinsLabel(std::string xaxisName) {
					xLabel = xaxisName;
				}

				/**
				 * @brief Returns the label for the Y-axis
				 *
				 * @return label shown for the Y-axis
				 **/
				std::string getBinsLabel() const {
					return xLabel;
				}

				/**
				 * @brief sets the bar chart orientation
				 *
				 * Bar charts can be 'horizontal' or 'vertical'
				 *
				 * @param align 
				 **/
				void setBarOrientation(const std::string& orient) {
				  if (orient != "horizontal" && orient != "vertical")
				    throw std::invalid_argument("Orientation should be \"horizontal\" or \"vertical\".");
				  orientation = orient;
				}

				/**
				 * @brief gets the bar chart orientation
				 *
				 * @return orientation (either "horizontal" or "vertical")
				 **/
				std::string getBarOrientation() const {
					return orientation;
				}

				/**
				 * @brief sets the tooltip suffix
				 *
				 * This prints a string that is more informative of the values
				 * represented by the bars
				 *
				 * @param suffix 
				 **/
				void setTooltipSuffix(std::string suffix) {
					tooltipSuffix = suffix;
				}

				/**
				* @brief gets the tooltip suffix
				*
				* @return suffix 
				**/
				std::string getTooltipSuffix() const {
					return tooltipSuffix;
				}

				/**
				 *  @brief set the bins for this bar chart
				 *
				 *  @param bins
				 */
				void setSeriesBins(std::vector<std::string> bins) {
					seriesBins = bins;
				}

				/**
				 * @brief Add data values for the bins
				 *
				 * @param seriesName indicates the name of the data to add
				 * @param data values of the bins
				 **/
				void addDataSeries(std::string seriesName, std::vector<double> data) {
					seriesData[seriesName] = data;
				}

				/**
				 * @brief get the data structure representation as a JSON
				 */
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
						JSONencode("xLabel") + COLON + JSONencode(getBinsLabel()) +  COMMA +
						JSONencode("yLabel") + COLON + JSONencode(getSeriesLabel()) + COMMA +
						JSONencode("tooltipSuffix") + COLON + JSONencode(getTooltipSuffix()) + COMMA +
						JSONencode("alignment") + COLON + JSONencode(getBarOrientation()) + COMMA +
						JSONencode("xaxis_data") + COLON + OPEN_CURLY + bins + CLOSE_CURLY + COMMA +
						JSONencode("yaxis_data") + COLON + OPEN_CURLY + series + CLOSE_CURLY + CLOSE_CURLY;

					return json_str;
				}
		};
	}

}
#endif
