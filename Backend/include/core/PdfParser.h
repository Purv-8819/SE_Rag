//
// Created by Purv Patel on 1/6/26.
//

#ifndef SE_RAG_PDFPARSER_H
#define SE_RAG_PDFPARSER_H

#include <string>
#include <vector>
#include <stdexcept>

namespace core {

    class PdfParser {
    public:
        PdfParser() = default;
        ~PdfParser() = default;

        /**
         * Parses a PDF file and extracts text page by page.
         * * @param filepath The absolute or relative path to the PDF file.
         * @return A vector of strings, where index 0 is Page 1, index 1 is Page 2, etc.
         * @throws std::runtime_error if the file cannot be opened or parsed.
         */
        [[nodiscard]] std::vector<std::string> parsePages(const std::string& filepath) const;

        /**
         * Convenience method to get the entire PDF content as a single blob of text.
         */
        [[nodiscard]] std::string parseToString(const std::string& filepath) const;
    };

}

#endif //SE_RAG_PDFPARSER_H