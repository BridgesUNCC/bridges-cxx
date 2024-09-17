#ifndef BAR_CHART_H
#define BAR_CHART_H

#include <unordered_map>
#include <vector>
#include <string>
#include <DataStructure.h>
#include <JSONutil.h>

/**
 * @brief Support for drawing Bar charts.
 *
 * Bar charts (https://en.wikipedia.org/wiki/Bar_chart) are used to
 * represent categorical data as a series of rectangular bars with length
 * proportional to the values they represent.
 *  
 * Series in a bar chart provides data for a number of categories,
 * called bins. Bins are defined using setSeriesBins() and the series
 * are added using addDataSeries(). 
 *
 * One should always define the bins before adding data. Changing the
 * bins after series have been added will throw an exceptions and
 * adding series with different number of values than the number of
 * bins will throw an exception.
 *      
 * The Bar charts can have a title, subtitle. The charts can be
 * horizontal or vertically aligned using setBarOrientation().
 * 
 * A tooltip indicating the value of a series in a particular bin is
 * displayed by hovering on a bar. One can append a string to the
 * value using setTooltipSuffix() to specify units in the tooltip if desired.
 *  
 * 
 *
 * @sa See tutorial on using BarChart at:
 *      https://bridgesuncc.github.io/tutorials/BarChart.html
 *
 * @author Matthew Mcquaigue, Kalpathi Subramanian, Erik Saule
 *
 * @date 09/15/24 (updated)
 *
 **/


namespace bridges {
	namespace datastructure {

		class BarChart : public DataStructure {
			private:
				std::string bLabel;
				std::string vLabel;
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
					vLabel = "";
					bLabel = "";
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
				void setSubTitle(const std::string& s) {
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
				 * @brief Change the label for the value axis
				 *
				 * @param yaxisName label to show for the value axis
				 **/
				void setValueLabel(const std::string& vAxisName) {
					vLabel = vAxisName;
				}

				/**
				 * @brief Returns the label for the value axis
				 *
				 * @return label shown for the value axis
				 **/
				std::string getValueLabel() const {
					return vLabel;
				}

				/**
				 * @brief Change the label for bins
				 *
				 * @param xaxisName label to use for the bins
				 **/
				void setBinsLabel(std::string bAxisName) {
					bLabel = bAxisName;
				}

				/**
				 * @brief Returns the label for the bins
				 *
				 * @return label shown for the bins
				 **/
				std::string getBinsLabel() const {
					return bLabel;
				}

				/**
				 * @brief sets the bar chart orientation
				 *
				 * @param orient can be 'horizontal' or 'vertical'
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
				 * Will throw an exception if there are already data series defined. 
				 *
				 *  @param bins Names of different bins
				 */
				void setSeriesBins(std::vector<std::string> bins) {
				  if (seriesData.size() > 0)
				    throw std::runtime_error ("Can't change bins after series have been added.");
				  seriesBins = bins;
				}

				/**
				 * @brief Add a series of data
				 *
				 * This will throw an exception if the data vector does not have the same size as the number of bins.
				 *
				 * @param seriesName indicates the name of the data to add
				 * @param data values of that serie for each  bin
				 **/
				void addDataSeries(std::string seriesName, std::vector<double> data) {
				  if (data.size() != seriesBins.size())
				    throw std::runtime_error ("The data vector should have the same size as the number of bins.");
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
						JSONencode("yLabel") + COLON + JSONencode(getValueLabel()) + COMMA +
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
