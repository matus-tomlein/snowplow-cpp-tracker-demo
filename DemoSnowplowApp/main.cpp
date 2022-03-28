//
//  main.cpp
//  DemoSnowplowApp
//
//  Created by Matus Tomlein on 28/03/2022.
//

#include <iostream>

#include "tracker.hpp"

using namespace snowplow;

int main(int argc, const char * argv[]) {
    // Emitter is responsible for sending events to a Snowplow Collector
    Emitter emitter("com.acme.collector", Emitter::Method::POST, Emitter::Protocol::HTTP, 500, 52000, 52000, "sp.db");
    // Subject defines additional information about your application's environment and user
    Subject subject;
    subject.set_user_id("a-user-id");
    // Client session keeps track of user sessions
    ClientSession client_session("sp.db", 5000, 5000);

    string platform = "pc"; // platform the tracker is running on
    string app_id = "openage"; // application ID
    string name_space = "sp-pc"; // the name of the tracker instance
    bool base64 = false; // whether to enable base 64 encoding
    bool desktop_context = true; // add a context entity to events with information about the device

    Tracker *tracker = Tracker::init(emitter, &subject, &client_session, &platform, &app_id, &name_space, &base64, &desktop_context);
    assert(tracker != nullptr);
    
    Tracker::close();
    std::cout << "Done!\n";
    return 0;
}
