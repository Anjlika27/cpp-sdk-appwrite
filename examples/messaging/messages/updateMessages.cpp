#include "Appwrite.hpp"
#include <iostream>

int main() {
    std::string projectId = "<YOUR_PROJECT_ID>";
    std::string apiKey = "<YOUR_API_KEY>";
    Appwrite appwrite(projectId, apiKey);

    std::string messageId = "<YOUR_SMS_MESSAGE_ID>"; // existing draft message

    try {
        std::string response = appwrite.getMessaging().updateSms(
            messageId,
            {"topic1", "topic2"},    // topics
            {"user1"},               // users
            {"target1"},             // targets
            "Updated SMS content",   // content
            false,                   // draft
            "2025-08-16T10:00:00Z"   // scheduledAt
        );
        std::cout << "SMS Updated! \nResponse: " << response << std::endl;
    } catch (const AppwriteException &ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }

    return 0;
}
