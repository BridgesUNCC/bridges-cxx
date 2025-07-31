#ifndef BAR_CHART_H
#define BAR_CHART_H

#include <unordered_map>
#include <vector>
#include <string>
#include <DataStructure.h>
#include <JSONutil.h>


namespace bridges {
	namespace datastructure {
	  /**
	   * @brief Support for drawing Bar charts.
	   *
	   * Bar charts (https://en.wikipedia.org/wiki/Bar_chart) are used to
	   * represent categorical data as a series of rectangular bars with length
	   * proportional to the values they represent.
	   *
	   * Series in a bar chart provides data for a number of categories
	   * (sometimes called bins). Categories are defined using
	   * setCategories() and the series are added using addDataSeries().
	   * The series are rendered in the order in which they were added. Once
	   * a series has been added, it can not be modified.
	   *
	   * One should always define the categories before adding data. Changing the
	   * categories after series have been added will throw exceptions;
	   * adding series with different number of values than the number of
	   * categories will throw an exception.
	   *
	   * The Bar charts can have a title, subtitle. The charts can be
	   * horizontal or vertically oriented, using setBarOrientation().
	   *
	   * A tooltip indicating the value of a series in a particular bin is
	   * displayed by hovering on a bar. One can append a string to the
	   * value using setTooltipSuffix() to specify units in the tooltip if desired.
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
	  class BarChart : public DataStructure {
			private:
				std::string cLabel;
				std::string vLabel;
				std::string title;
				std::string subTitle;
				std::string tooltipSuffix;
				std::string orientation;

				std::vector<std::pair<string, vector<double >>>  seriesData; //name, data
				std::vector<std::string> categories;

			public:
	    /**
	     * @brief makes an empty BarChart
	     **/
				BarChart() {
					title = "";
					subTitle = "";
					vLabel = "";
					cLabel = "";
					tooltipSuffix = "";
					orientation = "horizontal";
				}

				/**
				 * @brief Get the data type
				 *
				 * This is an internal function to BRIDGES. There are little reasons to call this function directly.
				 *
				 * @return name of the data type (used internally)
				 */
				virtual const string getDStype() const override {
					return "BarChart";
				}

				/**
				 * @brief Set title of the plot
				 *
				 * @param t the title of the BarChart
				 **/
				void setTitle(std::string t) {
					title = t;
				}

				/**
				 * @brief Get title of the plot
				 *
				 * @return the title of the BarChart
				 **/
				std::string getTitle() const {
					return title;
				}

				/**
				 * @brief set subtitle of the plot
				 *
				 * @param s the subtitle of the BarChart
				 **/
				void setSubTitle(const std::string& s) {
					subTitle = s;
				}

				/**
				 * @brief get the subtitle of the plot
				 *
				 * @return the subtitle of the BarChart
				 **/
				std::string getSubTitle() const {
					return subTitle;
				}

				/**
				 * @brief Set the label for the value axis
				 *
				 * @param vAxisName label for the value axis
				 **/
				void setValueLabel(const std::string& vAxisName) {
					vLabel = vAxisName;
				}

				/**
				 * @brief Returns the label for the value axis
				 *
				 * @return label for the value axis
				 **/
				std::string getValueLabel() const {
					return vLabel;
				}

				/**
				 * @brief Change the label for category axis
				 *
				 * @param cAxisName label for the category axis
				 **/
				void setCategoriesLabel(const std::string& cAxisName) {
					cLabel = cAxisName;
				}

				/**
				 * @brief Returns the axis label for the categories
				 *
				 * @return label for the categories
				 **/
				std::string getCategoriesLabel() const {
					return cLabel;
				}

				/**
				 * @brief sets the bar chart orientation
				 *
				 * @param orient can be 'horizontal' or 'vertical'. (Throws exception on other values)
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
				 * This appends a string to the values in the hover tooltip.
				 *
				 * @param suffix
				 **/
				void setTooltipSuffix(const std::string& suffix) {
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
				 *  @brief set the categories for this bar chart
				 *
				 * Will throw an exception if there are already data series defined.
				 *
				 *  @param categories Names of different categories
				 */
				void setCategories(const std::vector<std::string>& categories) {
					if (seriesData.size() > 0)
						throw std::runtime_error ("Can't change categoriess after series have been added.");
					this->categories = categories;
				}

				/**
				 * @brief Add a series of data
				 *
				 * This will throw an exception if the
				 * data vector does not have the same
				 * size as the number of categories.
				 *
				 * This will throw exceptions if two series have the same name.
				 *
				 * @param seriesName indicates the name of the data to add
				 * @param data values of that serie for each category
				 **/
				void addDataSeries(std::string seriesName, std::vector<double> data) {
					if (data.size() != categories.size())
						throw std::runtime_error ("The data vector should have the same size as the number of categories.");

					for (auto& entry : seriesData) {
						std::string key = entry.first;
						if (key == seriesName)
							throw std::runtime_error ("Can't have two series with the same name.");
					}

					seriesData.push_back(std::make_pair(seriesName, data));
				}

				/**
				 * @brief get the data structure representation as a JSON
				 *
				 * This is an internal function to BRIDGES. There are little reasons to call this function directly.
				 *
				 */
				virtual const std::string getDataStructureRepresentation() const override {
					using bridges::JSONUtil::JSONencode;
					std::string bins = "";
					bins += JSONencode("xAxis") + COLON + OPEN_CURLY + JSONencode("categories") + COLON + OPEN_BOX;
					for (auto& entry : categories) {
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
						JSONencode("xLabel") + COLON + JSONencode(getCategoriesLabel()) +  COMMA +
						JSONencode("yLabel") + COLON + JSONencode(getValueLabel()) + COMMA +
						JSONencode("tooltipSuffix") + COLON + JSONencode(getTooltipSuffix()) + COMMA +
						JSONencode("alignment") + COLON + JSONencode(getBarOrientation()) + COMMA +
						JSONencode("xaxis_data") + COLON + OPEN_CURLY + bins + CLOSE_CURLY + COMMA +
						JSONencode("yaxis_data") + COLON + OPEN_CURLY + series + CLOSE_CURLY + CLOSE_CURLY;

					return json_str;
				}
		};
	};
}
#endif
