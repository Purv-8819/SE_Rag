//
// Created by Purv Patel on 1/6/26.
//
#include <iostream>
#include <nlohmann/json.hpp>
#include "core/OllamaClient.h" // You'll create this header next

using json = nlohmann::json;

int main() {
    std::cout << "Starting GraphRAG Ingestion..." << std::endl;

    // Test JSON dependency
    json test = {{"status", "running"}, {"module", "ingestion"}};
    std::cout << test.dump(4) << std::endl;

    // TODO: Instantiate generic PDF parser here
    // TODO: Connect to Neo4j here

    return 0;
}