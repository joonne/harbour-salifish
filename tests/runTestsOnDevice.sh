#!/bin/bash

# Script for running tests. That's for specifying just one argument in QtCreator's configuration
/usr/bin/tst-harbour-salifish -input /usr/share/tst-harbour-salifish

# When you'll get some QML components in the main app, you'll need to import them to the test run
# /usr/bin/tst-harbour-salifish -input /usr/share/tst-harbour-salifish -import /usr/share/harbour-salifish/qml/components