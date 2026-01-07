//
// Created by Purv Patel on 1/6/26.
//
#include "core/PdfParser.h"
#include "poppler-document.h"
#include "poppler-page.h"
#include <iostream>
#include <utf8proc.h>


// TODO: Implement PDF parsing logic
std::string core::PdfParser::parseToString(const std::string &filepath) const {

    std::string result = "";

    // Attempt to open the documet
    poppler::document * doc = poppler::document::load_from_file(filepath);

    if (doc == nullptr || doc -> is_locked()) {
        std::cerr << "Error: Could not open or lock the document " << filepath << std::endl;

        return nullptr;
    }

    //Loop through all pages and gather text
    int numPages = doc->pages();
    for (int i = 0; i<numPages; i++) {
        poppler::page * cur_page = doc->create_page(i);

        result += normalize(cur_page->text().to_latin1());
    }

    return result;
}

std::vector<std::string> core::PdfParser::parsePages(const std::string &filepath) const {
    std::vector<std::string> result = {};

    // Attempt to open the documet
    poppler::document * doc = poppler::document::load_from_file(filepath);

    if (doc == nullptr || doc -> is_locked()) {
        std::cerr << "Error: Could not open or lock the document " << filepath << std::endl;

        return result;
    }

    //Loop through all pages and gather text
    int numPages = doc->pages();
    for (int i = 0; i<numPages; i++) {
        poppler::page * cur_page = doc->create_page(i);

        result.push_back(normalize(cur_page->text().to_latin1()));
    }


    return result;

}

std::string core::PdfParser::normalize(const std::string& text) {
    utf8proc_uint8_t *result;
    const auto opt = static_cast<utf8proc_option_t>(UTF8PROC_NULLTERM | UTF8PROC_STABLE | UTF8PROC_COMPOSE | UTF8PROC_COMPAT | UTF8PROC_CASEFOLD);

    utf8proc_map((utf8proc_uint8_t*)text.c_str(), 0, &result, opt);

    std::string output(reinterpret_cast<char *>(result));
    free(result);
    return output;
}
