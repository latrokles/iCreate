# iCreate
A simple iphone app to control an irobot create.

The project is composed of the iphone app written in [openFrameworks](http://openframeworks.cc/ "oF") that
sends instructions (as strings) in udp packets to the second part of the equation, a short udp server 
connected to the robot that will interpret these instructions and use them to control the create platform
using [libcreateoi](http://code.google.com/p/libcreateoi/ "libcreateoi").

## dependencies
In order to compile the iphone app, you will need openFrameworks for iPhone, preferrably v0062, which is
available [here](http://www.openframeworks.cc/download/) as well as the iphone SDK (and a dev license if
you wish to load it to the device).

As for the udp control server, you will need to obtain and install libcreateoi, available 
[here](http://code.google.com/p/libcreateoi/source/checkout). The server works on OS X and should work
on most linux distributions (haven't tested it yet, but I will).

TODO:
- Add buttons to the left sidebar to have the create play a tune or something like that.
- I would love to incorporate audio transmission so that the create can send and receive audio from the
  iphone, not too sure how to do this yet, but hopefully I can figure it out.
- The same as above, but with video. Thinking about having the udp server launch a vlc streaming process
  using a webcam attached to the controlling computer, but not sure how to play live streaming video on
  the iphone... expecting quite a challenge there. We will see if I can get this far.
