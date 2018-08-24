//          Copyright Emil Fresk 2015-2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE.md or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include "serialpipe.hpp"

using namespace std;

void test(const std::vector<uint8_t> &data);

int main()
{
    /* Create serial pipe */
    serialpipe::bridge sp("/dev/ttyUSB0", 57600, 10, true);

    /* serialpipe usage:
     *
     * serialpipe("port",
     *            baudrate,
     *            timeout (in ms),              (optional, 1000 default)
     *            string data (true / false)    (optional, true default)
     *            string termination);          (optional, "\n" default)
     */

    /* Register a callback */
    sp.registerCallback(test);

    /* Open the serial port */
    sp.openPort();

    /* Transmit some data... */
    sp.serialTransmit("test test test");

    cin.get();

    /* Close port */
    sp.closePort();

    return 0;
}

/* Print incoming data... */
void test(const std::vector<uint8_t> &data)
{
    cout << "Data received: ";
    for (const uint8_t &ch : data)
    {
        cout << static_cast<char>( ch );
    }

    cout << endl;
}

