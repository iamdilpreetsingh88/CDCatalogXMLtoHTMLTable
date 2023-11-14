/********************************************************************
* Assignment as part of the interview process for the position of
* Lead Software Developer at OpenText.
*
* Problem Statement: You are given a vector of floating-point values.
* Write a simple C++ console program that takes cd_catalog.xml, as input
* and converts it to an HTML file.
* Requirements:
*   1.	It should be a single executable that takes the file name as input.
*   2.  The output HTML should be formatted as a "table" element.
*   3.  Sorting is not important for this challenge
*   4.  There are no other constraints.
*
* Solution details: The code in this source file is self-explanatory with
* the comments written against almost every important step. However, please
* take a look at the README file provided with this code file for details
* about the approach, platform used and the instructions to run it.
*
* Author : Dilpreet Singh
**********************************************************************/


#include <iostream>  // For using IO operations like cout, cerr etc.
#include <fstream>   // For using file operations.
#include <string>    // For using std::string
#include <vector>    // For using std::vector
#include <cstdlib>   // For using EXIT_SUCCESS and EXIT_FAILURE statuses
#include <stdexcept> // For exceptions like runtime_error and invalid_argument

// Class to represent a items in each CD block
class CD {
public:
    std::string title;
    std::string artist;
    std::string company;
    std::string country;
    std::string price;
    std::string year;
};

// Class to parse input XML file
class XmlParser {
public:
    // Constructor
    XmlParser(const std::string& filename);
    
    // Function to populate a CD object from a single CD element
    // and return the CD object.
    CD parseCdElement(const std::string& cdElement);

    // Function to read and parse CD elements from the XML file.
    std::vector<CD> parseCds();

    // Destructor
    ~XmlParser();

private:
    // file handle for input XML file.
    std::ifstream xmlFile;
};

// Class to generate HTML file using a vector of CD objects.
class HtmlGenerator {
public:
    // Constructor
    HtmlGenerator(const std::string& filename);

    // Function to generate the HTML file from a vector of CDs
    void generateHtml(const std::vector<CD>& cds);

    // Destructor
    ~HtmlGenerator();

private:
    // file handle for output HTML file.
    std::ofstream htmlFile;
};

// Implementation of XmlParser class
XmlParser::XmlParser(const std::string& filename) : xmlFile(filename) {
    if (!xmlFile.is_open()) {  // RAII
        throw std::runtime_error("Error opening input XML file!");
    }
}

// Implementation of the function to populate a CD object from
// a single CD element as a string.
CD XmlParser::parseCdElement(const std::string& cdElement) {
    CD cd;
    size_t startPos, endPos;

    // Parse TITLE
    startPos = cdElement.find("<TITLE>") + 7;
    endPos = cdElement.find("</TITLE>");
    cd.title = cdElement.substr(startPos, endPos - startPos);

    // Parse ARTIST
    startPos = cdElement.find("<ARTIST>") + 8;
    endPos = cdElement.find("</ARTIST>");
    cd.artist = cdElement.substr(startPos, endPos - startPos);

    // Parse COMPANY
    startPos = cdElement.find("<COMPANY>") + 9;
    endPos = cdElement.find("</COMPANY>");
    cd.company = cdElement.substr(startPos, endPos - startPos);

    // Parse COUNTRY
    startPos = cdElement.find("<COUNTRY>") + 9;
    endPos = cdElement.find("</COUNTRY>");
    cd.country = cdElement.substr(startPos, endPos - startPos);

    // Parse PRICE
    startPos = cdElement.find("<PRICE>") + 7;
    endPos = cdElement.find("</PRICE>");
    cd.price = cdElement.substr(startPos, endPos - startPos);

    // Parse YEAR
    startPos = cdElement.find("<YEAR>") + 6;
    endPos = cdElement.find("</YEAR>");
    cd.year = cdElement.substr(startPos, endPos - startPos);
    return cd;
}

// Implementation of function to parse the XML file and return a
// vector of CD objects corresponding to each <CD>..</CD> block.
std::vector<CD> XmlParser::parseCds() {
    std::vector<CD> cds;
    std::string line;
    std::string cdElement;

    while (std::getline(xmlFile, line)) {
        if (line.find("<CD>") != std::string::npos) {
            cdElement = line;
            while (std::getline(xmlFile, line) && line.find("</CD>") == std::string::npos) {
                cdElement += "\n" + line;
            }
            cdElement += "\n</CD>";
            cds.push_back(parseCdElement(cdElement));
        }
    }

    return cds;
}

// Destructor implementation
XmlParser::~XmlParser() {
    if (xmlFile.is_open()) {
        xmlFile.close(); // Close the file if it is still open
    }
}

// Implementation of HtmlGenerator class
HtmlGenerator::HtmlGenerator(const std::string& filename) : htmlFile(filename) {
    if (!htmlFile.is_open()) { // RAII
        throw std::runtime_error("Error opening output HTML file!");
    }
}

// Main function to write the content of the output HTML file.
void HtmlGenerator::generateHtml(const std::vector<CD>& cds) {
    // This HTML code uses a separate styles.css file to define table's format
    // on the html page.
    htmlFile << "<!DOCTYPE html>\n<html>\n<head>\n"
        "<title>CD Catalog</title>\n"
        "<link rel=\"stylesheet\" type=\"text/css\" href=\"styles.css\">\n"  // Linking a separate styles.css file
        "</head>\n<body>\n"
        "<table>\n"
        "<tr><th>Title</th><th>Artist</th><th>Company</th>"
        "<th>Country</th><th>Price</th><th>Year</th></tr>\n";

    // Iterate over each CD element, and add it to the table.
    for (const auto& cd : cds) {
        htmlFile << "<tr>"
            << "<td>" << cd.title << "</td>"
            << "<td>" << cd.artist << "</td>"
            << "<td>" << cd.company << "</td>"
            << "<td>" << cd.country << "</td>"
            << "<td>" << cd.price << "</td>"
            << "<td>" << cd.year << "</td>"
            << "</tr>\n";
    }

    htmlFile << "</table>\n</body>\n</html>";
}

// Destructor implementation
HtmlGenerator ::~HtmlGenerator() {
    if (htmlFile.is_open()) {
        htmlFile.close(); // Close the file if it is still open
    }
}

// The main() function. Expects two or three parameters.
//  1. argv[0] is the program's binary name.
//  2. argv[1] is manadatory parameter to get the name of input XML file.
//  3. argv[2] is an optional parameter to get the name of output HTML file. Default value
//     is "cd_catalog.html"
// This function is responsible for driving the logic to parse the input xml file
// generate the output HTML file.
int main(int argc, char* argv[]) {
    try {
        if (argc < 2 && argc > 3) {
            // throw an error if required parameters aren't provided when running this application.
            throw std::invalid_argument("Usage: " + std::string(argv[0]) + " <input_xml_file_name>  <output_html_file_name>");
        }
        // Get name of input xml file.
        const std::string inputFilename = argv[1];
        // Parse the input xml file.
        XmlParser xmlParser(inputFilename);
        std::vector<CD> cds = xmlParser.parseCds();

        // Get name of output html file. Using argv[2] if provided when running
        // this application; else, use default name "cd_catalog.html".
        const std::string outputFilename = (argc == 3) ? argv[2] : "cd_catalog.html";
        // Generate the HTML file.
        HtmlGenerator htmlGenerator(outputFilename);
        htmlGenerator.generateHtml(cds);

        std::cout << "HTML file generated successfully!" << std::endl;
        // Program succeeded.
        return EXIT_SUCCESS;
    }
    catch (const std::exception& e) {
        // Catch any exception if occured.
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
