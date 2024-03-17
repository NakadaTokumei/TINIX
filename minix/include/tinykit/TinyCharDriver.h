#ifndef __TINY_CHAR_DRIVER_H__
#define __TINY_CHAR_DRIVER_H__

extern "C"
{

#include <minix/driver.h>

}

using TinyCharDevID = unsigned int;

class TinyCharDriver
{
    bool _running;

    void
    Process(
        message& message,
        int ipcStatus
    );

    void
    Reply(
        message& msg,
        int ipcStatus,
        int result
    );

    void
    SendReply(
        endpoint_t endpt,
        message& msg,
        int ipcStatus
    );

    int
    OpenOperatioon(
        message& msg
    );

    int
    CloseOperation(
        message& msg
    );

    int
    ReadOperation(
        message& msg
    );

protected:
    TinyCharDriver() :
        _running(false)
    {}

    virtual int
    Open(
        devminor_t minor,
        int access,
        endpoint_t userEndpt
    ) { return OK; }

    virtual int
    Close(
        devminor_t minor
    ) { return OK; }

    virtual ssize_t
    Read(
        devminor_t minor,
        u64_t pos,
        endpoint_t endpt,
        cp_grant_id_t grant,
        size_t size,
        int flags,
        TinyCharDevID id
    ) { return OK; }

    virtual ssize_t
    Write(
        devminor_t minor,
        u64_t pos,
        endpoint_t endpt,
        cp_grant_id_t grant,
        size_t size,
        int flags,
        TinyCharDevID id
    ) { return OK; }

    virtual int
    Ioctl(
        devminor_t minor,
        unsigned long request,
        endpoint_t endpt,
        cp_grant_id_t grant,
        int flags,
        endpoint_t userEndpt,
        TinyCharDevID id
    ) { return OK; }

    virtual int
    Cancel(
        devminor_t minor,
        endpoint_t endpt,
        TinyCharDevID id
    ) { return OK; }

    virtual int
    Select(
        devminor_t minor,
        unsigned int ops,
        endpoint_t endpt
    ) { return OK; }

    virtual void
    Intr(
        unsigned int mask
    ) { return OK; }
    
    virtual void
    Alarm(
        clock_t stamp
    ) { return OK; }

    virtual void
    Other(
        message& pMsg,
        int ipcStatus
    ) { return OK; }

public:
    virtual void 
    Start(void);
};

#endif