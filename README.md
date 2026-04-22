# Source to HTML Converter – Syntax Highlighter

This project implements a Source to HTML Converter developed using the C programming language. The application reads a C source code file and converts it into an HTML formatted output with syntax highlighting, allowing the code to be viewed clearly inside a web browser.

The converter identifies different programming elements such as keywords, identifiers, strings, comments, operators, preprocessor directives, and numerical constants, and applies predefined HTML styling to improve readability similar to modern code editors.

The project demonstrates concepts of lexical analysis, token classification, file processing, and basic compiler design techniques.

Features:
- Converts C source code into HTML format
- Syntax highlighting for programming elements
- Recognition of reserved keywords
- Preprocessor directive highlighting
- String and comment detection
- Numerical constant identification
- Operator and symbol classification
- Browser-readable HTML output
- CSS-based styling support

Technologies Used:
- C Programming Language
- Lexical Analysis Concepts
- File I/O Operations
- Tokenization Techniques
- HTML and CSS
- GCC Compiler
- Linux Environment

Project Structure:
source_to_html/
lexer.c  
tokenizer.c  
html_generator.c  
styles.css  
input.c  
output.html  
README.md  

Compilation:
gcc *.c -o source2html

Execution:
./source2html input.c

The program generates an HTML file that can be opened in any web browser.

Working Principle:
The program reads the input C source file character by character and performs lexical analysis. Each token is classified into categories such as keywords, strings, comments, operators, or identifiers. Based on token type, corresponding HTML tags and CSS classes are added. The final output is a styled HTML document representing highlighted source code.

Learning Outcomes:
- Understanding lexical analyzer design
- Token classification techniques
- File parsing and processing
- Syntax highlighting implementation
- Basics of compiler construction
- HTML generation using C programs

Future Improvements:
- Support for multiple programming languages
- Advanced parser integration
- Theme customization
- Line numbering support
- Web-based interface

Author:
Aswathi E P  
Embedded Systems Engineer  
Email: aswathigopinath20@gmail.com  
LinkedIn: https://www.linkedin.com/in/aswathi-ep-by0256  
GitHub: https://github.com/aswathi-gopinath  

License:
This project is developed for educational and learning purposes.
