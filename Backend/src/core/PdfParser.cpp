//
// Created by Purv Patel on 1/6/26.
//
#include "core/PdfParser.h"
#include "poppler-document.h"
#include "poppler-page.h"
#include <iostream>
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

        result += cur_page->text().to_latin1();
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

        result.push_back(cur_page->text().to_latin1());
    }


    return result;

}
