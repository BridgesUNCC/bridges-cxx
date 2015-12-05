#ifndef VALIDATION_H
#define VALIDATION_H

#include <string> //string
#include <unordered_set> //unordered_set

using namespace std;

namespace bridges{
/**
 * @brief This class performs certain validation checks to ensure the
 *  robustness of the BRIDGES  system.
 *
 * Validatoin checks are made for legal specification of visual properties
 * such as color, element size, opacity values,
 * the maximum number of BRIDGES elements (currently set at 5000).
 *
 * BRIDGES supports these shapes:
 * "circle","square","diamond","cross","triangle-down", and "triangle-up"
 *
 * @author Kalpathi Subramanian(C++ port),
 * @date 6/22/15
 */
namespace Validation
{
    const unordered_set<string>
        NodeShapes
        ({
            "circle",
            "square",
            "diamond",
            "cross",
            "triangle-down",
            "triangle-up"
        });
    /** This variable holds the maximum number of nodes allowed */
    constexpr int MAX_ELEMENTS_ALLOWED = 5000;
    /**
     * Determines if value passed is an acceptable value to
     * set a RGBA channel to. [0,255]
     *
     * @param channel Input channel value
     *
     * @throw string Thrown if channel value is invalid
     */
    static void validateRGBAchannel(const int& channel)
    {
        if(channel<0 || 255<channel)
        {
            throw "Invalid channel parameter: " + to_string(channel) + " Must be in the [0,255] range";
        }
    }
    /**
     * Determines if the shape is supported.
     *
     * @param shape Input shape
     * @throw string Thrown if shape is invalid
     */
    void validateShape(string shape)
    {
        for (char& c: shape){c=tolower(c);} //gets lowercase version
        if (NodeShapes.find(shape) == NodeShapes.end())
        {
            string error_str = "Invalid shape.." + shape +".\n Must be  one of..";
            for (const auto& elem: NodeShapes)
            {
                error_str += elem + ",";
            }
            error_str += "\n";
            throw error_str;
        }
    }
    /**
     * Determines if the value passed is an acceptable value to set
     * the size to.[10,50]
     *
     * @param val Input size
     * @throw string Thrown if val is invalid
     */
    void validateSize(const double& val)
    {
        if(val < 10 || 50 < val)
        {
            throw "Invalid Size Value.. " + to_string(val) + " Must be in the [10.0,50.0] range";
        }
    }
    /**
     * Determines if the value passed is an acceptable value to set
     * the thickness to. [0,10]
     *
     * @param val Input thickness
     * @throw string Thrown if val is invalid
     */
    void validateThickness(const double& val)
    {
        if(val < 0 || 10 < val)
        {
            throw "Invalid Thickness Value.. " + to_string(val) + " Must be in the [0.0,10.0] range";
        }
    }
    /**
     * Determines if the value passed is an acceptable value to set
     * the weight to. [0,inf)
     *
     * @param val Input weight
     * @throw string Thrown if val is invalid
     */
    void validateWeight(const double& val)
    {
        if(val < 0)
        {
            throw "Invalid Weight Value.. " + to_string(val) + " Must be positive";
        }
    }
    /**
     * Determines if the value passed is an acceptable value to set
     * the max number of elements in the data structure.
     *
     * @param val Input number of elements
     * @throw string Thrown if val is invalid
     */
    void validate_ADT_size(const int& max_elements)
    {
        if (max_elements < 0 || MAX_ELEMENTS_ALLOWED <= max_elements)
        {
            throw "Max allowed elements (for visualization) exceeded.. " + to_string(max_elements) + " Must be less than " + to_string(MAX_ELEMENTS_ALLOWED);
        }
    }
}//end of Validation namespace
}//end of bridges namespace
#endif
