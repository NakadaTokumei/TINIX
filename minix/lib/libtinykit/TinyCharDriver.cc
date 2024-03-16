#include <tinykit/TinyCharDriver.h>

void
TinyCharDriver::Task()
{
    /* TODO */

    int result;
    int ipcStatus;

    message msg;

    _running = true;

    while(_running)
    {
        result = sef_receive_status(
            ANY,
            &mess,
            &ipcStatus
        ); 
        if(result != OK)
        {
            if((result == EINTR) && 
                (!_running))
            {
                break;
            }
        }
        else
        {
            /* TODO Process */
        }
    }
}