#include "Appwrite.hpp"
#include <iostream>

int main() {
    std::string projectId = "66fbb5a100070a3a1d19";
    std::string apiKey = "";
    std::string fileId = "example.txt";
    std::string bucketId = "bucketnew";

    Appwrite appwrite(projectId, apiKey);
    
    try {
        std::string response = appwrite.getStorage().getFileView(bucketId, fileId);
        std::cout << "File fetched successfully! \n\nResponse: " << response << std::endl;
    } catch (const AppwriteException& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }

    return 0;
}
