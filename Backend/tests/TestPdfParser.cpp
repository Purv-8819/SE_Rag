//
// Created by Purv Patel on 1/6/26.
//

#include <gtest/gtest.h>
#include "core/PdfParser.h"
#include <string>

class PdfParserTest : public ::testing::Test {
protected:
    // Ensure this path matches where you placed the PDF relative to your build executable
    std::string test_pdf_path = "../tests/data/test_doc.pdf";

    void SetUp() override {
        // We assume tests/data/test_doc.pdf exists (generated from your LaTeX)
    }
};

TEST_F(PdfParserTest, ReturnsCorrectPageCount) {
    core::PdfParser parser;
    auto pages = parser.parsePages(test_pdf_path);

    // The LaTeX file has exactly 2 pages (\newpage used once)
    ASSERT_EQ(pages.size(), 2) << "PDF should have exactly 2 pages.";
}

TEST_F(PdfParserTest, ExtractsPage1Content) {
    core::PdfParser parser;
    auto pages = parser.parsePages(test_pdf_path);

    // Content from LaTeX: "It contains some Expected Content for the parser."
    std::string pageOne = pages[0];

    // Verify specific unique phrases exist
    EXPECT_NE(pageOne.find("This is page 1 content"), std::string::npos);
    EXPECT_NE(pageOne.find("Expected Content"), std::string::npos);

    // Verify the page starts correctly (assuming no weird whitespace artifacts)
    // Note: Poppler might leave leading whitespace depending on your normalization logic
    // so finding the substring is safer than checking pageOne.front() for now.
    EXPECT_NE(pageOne.find("This is page 1"), std::string::npos);
}

TEST_F(PdfParserTest, ExtractsPage2Content) {
    core::PdfParser parser;
    auto pages = parser.parsePages(test_pdf_path);

    // Content from LaTeX: "Here is a Hyphenated-word example..."
    std::string pageTwo = pages[1];

    EXPECT_NE(pageTwo.find("This is page 2 content"), std::string::npos);

    // Crucial check: Verify the hyphenated word was extracted
    EXPECT_NE(pageTwo.find("Hyphenated-word"), std::string::npos);

    // Verify the end of the document text
    EXPECT_NE(pageTwo.find("End of document"), std::string::npos);
}

TEST_F(PdfParserTest, ThrowsOnMissingFile) {
    core::PdfParser parser;
    // Verify that the parser correctly identifies a non-existent file
    EXPECT_THROW(parser.parsePages("non_existent_file_123.pdf"), std::runtime_error);
}