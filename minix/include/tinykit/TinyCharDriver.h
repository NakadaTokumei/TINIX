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

protected:
    TinyCharDriver() :
        _running(false)
    {}

    virtual int
    Open(
        devminor_t minor,
        int access,
        endpoint_t userEndpt
    ) = 0;

    virtual int
    Close(
        devminor_t minor
    ) = 0;

    virtual ssize_t
    Read(
        devminor_t minor,
        u64_t pos,
        endpoint_t endpt,
        cp_grant_id_t grant,
        size_t size,
        int flags,
        TinyCharDevID id
    ) = 0;

    virtual ssize_t
    Write(
        devminor_t minor,
        u64_t pos,
        endpoint_t endpt,
        cp_grant_id_t grant,
        size_t size,
        int flags,
        TinyCharDevID id
    ) = 0;

    virtual int
    Ioctl(
        devminor_t minor,
        unsigned long request,
        endpoint_t endpt,
        cp_grant_id_t grant,
        int flags,
        endpoint_t userEndpt,
        TinyCharDevID id
    ) = 0;

    virtual int
    Cancel(
        devminor_t minor,
        endpoint_t endpt,
        TinyCharDevID id
    ) = 0;

    virtual int
    Select(
        devminor_t minor,
        unsigned int ops,
        endpoint_t endpt
    ) = 0;

    virtual void
    Intr(
        unsigned int mask
    ) = 0;
    
    virtual void
    Alarm(
        clock_t stamp
    ) = 0;

    virtual void
    Other(
        message* pMsg,
        int ipcStatus
    ) = 0;

public:
    void Task(void) final;
};

#endif