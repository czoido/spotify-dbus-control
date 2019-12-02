#include <iostream>
#include "dbus.h"

int main()
{
    DBus::Log::setLevel(DBus::Log::WARNING);
    DBus::Log::write(DBus::Log::INFO, "System bus: %s\n", DBus::Platform::getSystemBus().c_str());
    DBus::Log::write(DBus::Log::INFO, "Session bus: %s\n", DBus::Platform::getSessionBus().c_str());
    DBus::Native native(DBus::Platform::getSessionBus());

    native.BeginAuth(DBus::AuthenticationProtocol::AUTH_BASIC); // AUTH_BASIC or AUTH_NEGOTIATE_UNIX_FD

    printf("Send hello message...\n");

    native.registerSignalHandler("org.freedesktop.DBus.NameAcquired", [&](const DBus::Message::Signal& signal) {
        // Knowing the type is 's' we can be safe in assuming asString will work
        std::string signalName = DBus::Type::asString(signal.getParameter(0));
        printf("RCV signalName : NameAcquired : %s\n", signalName.c_str());
    });

    native.registerSignalHandler("org.freedesktop.DBus.NameOwnerChanged", [&](const DBus::Message::Signal& signal) {
        std::string signalName = DBus::Type::asString(signal.getParameter(0));
        printf("RCV signalName : NameOwnerChanged : %s\n", signalName.c_str());
    });

    native.callHello([](const DBus::Message::MethodReturn& msg) {
		std::string signalName = DBus::Type::asString(msg.getParameter(0));
		printf("REPLY FROM HELLO : This is our unique name : %s\n", signalName.c_str()); },
        [](const DBus::Message::Error& msg) {
            printf("ERROR FROM HELLO : %s\n", msg.getMessage().c_str());
        });

    DBus::Message::MethodCall method(DBus::Message::MethodCallIdentifier("/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.Player", "PlayPause"));
    native.sendMethodCall("org.mpris.MediaPlayer2.spotify", method, 
        [](const DBus::Message::MethodReturn& msg) { 
            std::cout << DBus::Type::asString(msg.getParameter(0)) << std::endl; 
        },
        [](const DBus::Message::Error& msg) {
            std::cout << msg.getMessage() << std::endl;
        });

    return 0;
}