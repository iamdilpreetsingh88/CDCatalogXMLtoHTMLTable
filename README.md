# CD Catalog to HTML Table Converter
This C++ program is designed to take an input XML file as parameter and generates an HTML file corresponding to the CD catalogs given in that XML file, formatted as a table. The output HTML file name is an optional parameter and the name “cd_catalog.html” is used by default.

**Requirements**

•	C++ compiler that supports C++11 or later.

•	Input XML file (e.g., cd_catalog.xml).

•	(Optional) Output HTML file name (default: cd_catalog.html).

**Usage**
1.	Compile the Program:
   
    g++ -std=c++11 cd_catalog_converter.cpp -o cd_catalog_converter 
2.	Run the Program:

  	./cd_catalog_converter <input_xml_file> [output_html_file]

    •	<input_xml_file> (Required): Name of the input XML file.

    •	[output_html_file] (Optional): Name of the output HTML file. If not provided, the default name is cd_catalog.html.
4.	Example:
   
     ./cd_catalog_converter  cd_catalog.xml   output.html

**Code Files Description**

  •	cd_catalog_converter.cpp: The main C++ source code file.

  •	styles.css: CSS file for styling the generated HTML file.

**About Classes**
1.	CD Class:
   
     •	Represents an item in each CD block.
   
     •	Attributes: title, artist, company, country, price, year.
   
2.	XmlParser Class:

  	  •	Parses the input XML file and extracts CD elements.
  	
  	  •	Method: parseCds() returns a vector of CD objects.
   
4.	HtmlGenerator Class:

     •	Generates the HTML file from a vector of CD objects.
   
     •	Method: generateHtml() takes a vector of CDs and writes to the output HTML file.

**Notes**

•	This solution was written and tested in Windows environment, on MS Visual Studio 2022. Additionally, it is tested OK on command window.

•	Sorting of CD elements is not performed.

**Known Limitations**

•	The code assumes that the provided XML file is pre-validated and doesn't perform checks such as ensuring that all corresponding tags are properly opened and closed.

•	The implementation relies on the assumption that CD elements are individually present on separate lines.

•	To incorporate additional functionalities into the application, it could be useful to utilize libraries like pugixml.


Kindly feel free to reach out to me at dilpreetsingh95@gmail.com for any questions or comments.

Dilpreet Singh
